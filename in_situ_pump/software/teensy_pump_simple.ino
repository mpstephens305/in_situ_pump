// 10 July 2025
// Code for automatic control of pump with set start delay
// BlueRobotic motor with flowMeter, Teensy 4.1 RTC & microSd Card, Bar30 Pressure sensor, Switch Interrupt 
// User inputs: pumpTime, filename, startDelay 

int pumpTime = 25;            // How long pump will run, in seconds
int startDelay=35;            // Time, in seconds, after switch2 is closed to start pumping 
const char filename[] = "test001.txt";

#include <SD.h>               // Load SD library, (for microSD card reader)
#include <SPI.h>              // Load SPI communications library, for SD card reader
#include <TimeLib.h>          // Time library for Teensy
#include <Servo.h>            // Load servo library (for BLDC motor ESC)
#include "MS5837.h"           // library for BlueRobotics MS5837 pressure sensor
#include <Wire.h>             // Wire library is needed for the pressure sensor

byte servoPin = A9;           // pwm signal pin for the ESC
Servo servo;
MS5837 sensor;                // Bar30 pressure sensor

File myFile;
const int chipSelect = BUILTIN_SDCARD;  // chipSelect pin for SD card reader
int stopPWM=1500;             // The stop pwm value, in microswconds, for BLDC motor
int startupPWM = 1620;        // Pump will initially run at this PWM during pumping mode
int pwmVal=stopPWM;           // pwm value to be sent to the ESC 
float gallons=0;              // Set gallons counter to zero
int flowClicks=0;             // flowClicks increments flowmeter pulses
int endFlag = 0;              // endFlag will be set to 1 when pumping is complete
int redLEDx=17;               // external red LED
int greenLEDx=16;             // external green LED
int flowPin = 29;             // pin for flowmeter
int buttonPin = 41;           // pin for timing switch
int recordData1;              // Function to record data to SD card
int val = 0;                  // buttonPin input (LOW=0 or HIGH=1)
int switchClicked = 0;        // = 0 (false) until switch has been clicked
int numIntervals;

String runMode= "Standby";
int int1Flag=0;          // Interrupt1 Flag values: 0 = no input received yet (standby) 
//                          red LED on,
//                       // 1 = input received, countdown underway, green LED flashes 
//                          to indicate time until pump starts), 
//                       //  2 = pump is running, green LED on, 
//                       // 3 = pumping finished, flashing red LED

int dt=250;              // Variables for delays
int dt2000=2000;
int dt250 = 250;
int dt50=50;
int dt100=100;
int dt500=500;
int dt750=750;
int dt30000=30000;
uint32_t recordDelay = 5000;      // delay in milliseconds between record data during pumping

time_t t;                         // unix time, seconds elapsed since 1/1/1970
time_t tempTime;                  // can assign time for printing different event times
uint32_t currentMillis = 0;       // millis() is the onboard timer in millisecond
uint32_t lastMillis = 0;
uint32_t lastflowMillis = millis();
uint32_t startTime;
uint32_t timeInit;
uint32_t timeNow;
uint32_t endTime;

void setup() {

servo.attach(servoPin);
servo.writeMicroseconds(pwmVal);     // Set to 1500, that is the stop position
delay(7000);                         // Give time for arming of BLDC
Wire.begin();

setSyncProvider(getTeensy3Time);
Serial.begin(9600);

Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
    // open the file. 
  myFile = SD.open(filename, FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Opening file ...");
    
    myFile.println("runMode Time Date dbar meters decG pwmVal flowClicks Gallons");
	  myFile.close();
    Serial.println("done.");
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }

Serial.print("Initializing Bar30 pressure sensor...");
sensor.setModel(MS5837::MS5837_30BA); // pressure sensor
sensor.setFluidDensity(1029);         // kg/m^3 (997 for freshwater, 1029 for seawater)
// Initialize pressure sensor
// Returns true if initialization was successful
// We can't continue with the rest of the program unless 
// we can initialize the sensor (red LED indicates success)
while (!sensor.init()) {
    Serial.println("Init failed!");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    delay(5000);
}
Serial.println("done");

pinMode(redLEDx,OUTPUT);
pinMode(greenLEDx,OUTPUT);
pinMode(flowPin, INPUT_PULLDOWN);
pinMode(buttonPin,INPUT_PULLDOWN);

Serial.print("Standby mode initiated @"); // Standby mode, it stays here while int1Flag equals 0
tempTime = now();
displaytempTime(tempTime);
Serial.println("-----------------------------------------------------------------------");
Serial.println("runMode Time Date dbar meters degC pwmVal flowClicks Gallons");
sensor.read();                      //read pressure sensor 
recordData();
digitalWrite(greenLEDx,LOW);
digitalWrite(redLEDx,HIGH);

attachInterrupt(digitalPinToInterrupt(flowPin), flowMeter, RISING);   // Interrupt2
}

void loop() {

while(int1Flag == 0){
  val = digitalRead(buttonPin);
  if (val == 1){                 // When button clicked, go into countdown mode...
   switchClicked = 1;
   timeInit = now();
   startTime = startDelay + timeInit;
   endTime=startTime+pumpTime;
   Serial.print("Countdown mode initiated @");
   tempTime = timeInit;
   displaytempTime(tempTime);
   Serial.print("Pump start time = ");
   tempTime = startTime;
   displaytempTime(tempTime);
   Serial.print("Pump end time = ");
   tempTime = endTime;
   displaytempTime(tempTime);
   runMode="Countdown";
   sensor.read();                        //read pressure sensor
   Serial.println("-----------------------------------------------------------------------");
   Serial.println("runMode Time Date dbar meters degC pwmVal flowClicks Gallons");
   recordData();
   digitalWrite(redLEDx,LOW);
   int1Flag = 1;
  }
}

while(startTime-timeNow>20){                       // Countdown mode
 timeNow=now();   
 numIntervals = (startTime - timeNow) / startDelay;
  for (int i=0; i<numIntervals+1;i++){
  digitalWrite(greenLEDx,HIGH);
  delay(2*dt100);
  digitalWrite(greenLEDx,LOW);
  delay(2*dt100);
  }
 delay(10*dt100);
}

Serial.println("Final countdown mode initiated.");    // It's the FINAL COUNTDOWN!!
runMode="FinalCountdown";                          
sensor.read();                                     
Serial.println("-----------------------------------------------------------------------");
Serial.println("runMode Time Date dbar meters degC pwmVal flowClicks Gallons");
recordData();
timeNow=now(); 
//Flash green LED rapidly when countdown is in final 20 seconds
  while(startTime-timeNow<20 && startTime>=timeNow){ 
  timeNow=now(); 
  digitalWrite(greenLEDx,HIGH);
  delay(dt50);
  digitalWrite(greenLEDx,LOW);
  delay(dt50);
  }

timeNow=now(); 
if (startTime < timeNow){                        // It's time to start the pump
 Serial.print("Pump startup initiated @ ");
 tempTime = startTime;
 displaytempTime(tempTime);
 runMode="Pumping";
 sensor.read();                   
 Serial.println("-----------------------------------------------------------------------");
 Serial.println("runMode Time Date dbar meters degC pwmVal flowClicks Gallons");
 recordData();
 digitalWrite(greenLEDx,HIGH);
 int1Flag=2;                                    // Begin run mode
}

// Start motor, spin up stepwise to pwmVal = startupPWM
while (pwmVal<startupPWM){        
  for(pwmVal=1500; pwmVal<startupPWM; pwmVal = pwmVal+5){
  servo.writeMicroseconds(pwmVal);
  delay(dt250);                                   // dt250=250
  }
}

while(timeNow<endTime){
timeNow = now();
currentMillis = millis();
  if (currentMillis - lastMillis >= recordDelay) {    // record data every recordDelay milliseconds
   sensor.read();                               
   recordData(); 
   lastMillis = currentMillis;
  }
}

int1Flag=3;
digitalWrite(greenLEDx,LOW);
pwmVal=stopPWM;
servo.writeMicroseconds(pwmVal);                     // shut off motor 
delay(dt2000);
Serial.print("Pumping finished @ ");
tempTime = now();
displaytempTime(tempTime);
runMode="End/Stopped";
sensor.read();                   
recordData();
endFlag=1;

while(int1Flag == 3){    
digitalWrite(redLEDx,HIGH);                          // Flashing red LED when pumping is finished
delay(2*dt);
digitalWrite(redLEDx,LOW);
delay(2*dt);
}
}

void flowMeter()          
{  
//Interrupt Service Routine (ISR) 
//When flowMeter switch clicks, increment count and calculate volume  
if(millis() > lastflowMillis + 100) {      // debounce flow signal, ignore if les than 1/10 sec since last signal          
  flowClicks=flowClicks+1;    
  gallons=flowClicks*0.05;  
  lastflowMillis = millis();
}
}

void recordData(){
  myFile = SD.open(filename, FILE_WRITE);
  myFile.print(runMode);
  myFile.print(" ");
  myFile.print(hour());
  recordDigits(minute());
  recordDigits(second());
  myFile.print(" ");
  myFile.print(month());
  myFile.print("/");
  myFile.print(day());
  myFile.print("/");
  myFile.print(year()); 
  myFile.print(" ");      
  myFile.print(sensor.pressure());    // Print pressure and depth
  myFile.print(" ");     
  myFile.print(sensor.depth()); 
  myFile.print(" "); 
  myFile.print(sensor.temperature()); // Print pressure and depth
  myFile.print(" ");     
  myFile.print(pwmVal);               // Print motor PWM value (1500 = stopped, 1900 max)
  myFile.print(" ");
  myFile.print(flowClicks);           // Print cumulative flowmeter revolutions (0.05 gal/rev)
  myFile.print(" ");
  myFile.println(gallons);              // Print gallons pumped
  myFile.close();
  Serial.print(runMode);
  Serial.print(" ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(month());
  Serial.print("/");
  Serial.print(day());
  Serial.print("/");
  Serial.print(year()); 
  Serial.print(" ");      
  Serial.print(sensor.pressure());    // Print pressure and depth
  Serial.print(" ");     
  Serial.print(sensor.depth()); 
  Serial.print(" "); 
  Serial.print(sensor.temperature());  // Print pressure and depth
  Serial.print(" ");     
  Serial.print(pwmVal);               // Print motor PWM value (1500 = stopped, 1900 max)
  Serial.print(" ");
  Serial.print(flowClicks);           // Print cumulative flowmeter revolutions (0.05 gal/rev)
  Serial.print(" ");
  Serial.println(gallons);            // Print gallons pumped
}

void displayTime(){
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(month());
  Serial.print("/");
  Serial.print(day());
  Serial.print("/");
  Serial.print(year()); 
}

void displaytempTime(time_t tempTime){
  Serial.print(hour(tempTime));
  printDigits(minute(tempTime));
  printDigits(second(tempTime));
  Serial.print(" ");
  Serial.print(month(tempTime));
  Serial.print("/");
  Serial.print(day(tempTime));
  Serial.print("/");
  Serial.print(year(tempTime)); 
  Serial.println(" ");
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void recordDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  myFile.print(":");
  if(digits < 10)
  myFile.print('0');
  myFile.print(digits);
}
