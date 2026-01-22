# software

The Atrduino sketch <a href="teensy_pump_simple.ino">teensy_pump_simple.ino</a> directs the automatic operation of the pump. Prior to deployment, the user  specifies the following variables: startDelay, pumpTime, startupPWM, and data filename. Then, when the program is activated, pumping begins after startDelay (seconds), operates at a speed corresponding to startupPWM (microseconds), and stops after pumpTime (seconds). Data is recorded every minute to filename.dat.  

Given below are step-by-step instructions for installing the required software, pump operation, and data retrieval.

## Download Instructions

### Step 1: Install *Arduino IDE*
To write the code and upload it to the Teensy 4.1, you will have to use a free software called
Arduino Integrated Development Environment (*Arduino IDE*).
1. Visit https://www.arduino.cc/en/software/ and scroll down until you see Arduino IDE and
download the latest release.
2. Once download finishes, right-click on the file and select “run as administrator”.
3. Follow the pop-ups and select your preferences, then click install.
4. Once installed, open the application.

### Step 2: Install required libraries
To be able to program different components which will be used in the pump, we will need to
install various libraries, Teensyduino to be able to code onto the Teensy board, BlueRobotics
MS5837 Library for the Bar30 pressure sensor, and MTP_Teensy to download the data log after
a run. All the steps below are to be done through the Arduino IDE application.
1. To install Teensyduino, navigate to Files and select preferences.
2. Once the preferences window pops up, you may need to scroll down to even if no
scrollbar appears, in "Additional boards manager URLs" copy the link below then click
OK:
https://www.pjrc.com/teensy/package_teensy_index.json
3. Go back to the main Arduino window and select Boards Manager on the left side.
4. 4. Search Teensy and click install. Now you have the necessary library to operate on the
Teensy.
5. To install the Bar30 pressure sensor library, select Library Manager.
6. 6. Search “BlueRobotics MS5837”.
7. Click install.
8. To install the MTP_Teensy library, visit the link below:
https://github.com/KurtE/MTP_Teensy
9. Click on the green “Code” button and select “Download ZIP”.
10. Once the ZIP file has been downloaded, open your file explorer.
11. Copy the MTP_Teensy file into your Arduino > libraries folder.

### Step 3: Upload Code
The code to run the pump is provided in a .ino file to open on Arduino IDE and upload to the
board. To find this file, go to the GitHub repository, click on the software folder and download
the teensy_pump_simple.ino file. After downloaded, follow the steps below to upload.
1. Connect the cobalt series bulkhead 4-pin cable to the connector on the water tight
enclosure end cap.
2. Open the .ino file with the Arduino IDE application.
3. Select the “Tools” tab on the top left corner of the window.
4. Click on “Board” and select Teensy 4.1.
5. In the same “Tools” tab, click on “Port” and select the correct port corresponding to
where the Teensy is connected.
6. Go back to main window and click “Upload” (the arrow pointing to the right on the top
left of the window).

### Step 4: Retrieving Data
Once you have run the pump you can retrieve data and download it to your computer. The data
includes, date, run time, voltage and current usage, gallons pumped, PWM speed, and depth
(meters).
1. Connect Teensy to your computer through the cobalt series bulkhead 4-pin cable.
2. Select “File” on top left and click “Examples”.
3. Scroll down until you find MTP_Teensy and select mtp-test.
4. Once open, select the “Tools” tab and go to “USB Type”.
5. Select “MTP Disk Experimental”
