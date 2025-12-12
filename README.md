# in_situ_pump
```diff
-This site is under construction and will be fully functional in February, 2026.
```
<P>A low cost, open source in situ pump for marine and freshwater sampling being developed at Florida International University by Mark Stephens and Andres Martinez.</P>

![Pump deployment aboard RV Walton Smith in October 2025](docs/Pump_deployment_Walton_Smith_cruise_cropped2.jpg)

<P><b>Motivation: </b>In situ pumps allow for simultaneous sampling at multiple depths. However, commercially available units can cost tens of thousands of dollars. For applications involving shallow deployments, a more feasible solution is desirable. Our intention is to provide a complete step-by-step guide for building, programming, and operating the in_situ_pump. The system is adaptable for use in a variety of environments and projects. Community input and collaborations are most welcome. 
</P>

## Features
* 3D printed pump unit driven by a [Blue Robotics subsea motor](https://bluerobotics.com/store/thrusters/t100-t200-thrusters/m200-motor/).
* Controlled by a [Teensy 4.1](https://www.pjrc.com/store/teensy41.html) development board.
* Electronics and power supply inside watertight enclosure.
* Adaptable to various filter media (cartridges, GFF, acrylic fiber, etc.).
* Adaptable to sampling different chemical and isotopic species in the dissolved and particulate phases in seawater and freshwater.
* Simple operation.
* Easily programmable start delay, sampling duration, and motor speed.

## Fact Sheet:
* Materials cost: ~$2000 US.
* Power supply: c-cell batteries (can be adapted to other batteries including lithium).
* Maximum depth: 300 m.
* Sensors: pressure (depth), temperature, flow rate, voltage, DC current.
* Data storage: microSD card.
* Communications: USB.
* Dimensions: 24 x 18 x 12 in.
* Weight: 40 lb.
  



## How to Get One


### Hardware
<table>
<TR>
<TD>
<img src="docs/Pump_Photo_labeled.jpg" width=550 border=1>
	
For step-by-step build instructions for each component, use the following links: <a href="hardware/frame_assembly/frame_assembly.pdf">frame_assembly</a>, 
<a href="hardware/pump_unit/Pump_Unit.pdf">pump_unit</a>, <a href="">electronics_assembly</a>, and <a href="">filter_holder_assembly</a>. In addition,  
we provide CAD files for manufacture of the <a href="hardware/wire_clamp/Wire_clamp.pdf">wire clamp</a>. 
</td></tr></table>

### Software
<table>
<TR>
<TD style="width: 50%;">
Pump operation is controlled by the Arduino sketch "teensy_p[ump_simple.ino". Prior to deployment, the user specifies the pump delay, pump duration, motor speed, and data filename. At the start of a deployment, the program is initialized, and then the countdown to pump start up (i.e., pump delay) begins. The motor then spins up and operates for the specified pump duration.  See the flowchart at the right for the full sequence.
<a href="https://www.arduino.cc/en/software/">Arduino IDE</a>
the <a href="https://www.pjrc.com/teensy/teensyduino.html")Teensyduino</a> add-on for Arduino IDE
KurtE <a href="https://github.com/KurtE/MTP_Teensy")MTP_Teensy</a> library
the <a href="https://github.com/bluerobotics/BlueRobotics_MS5837_Library">Blue Robotics_MS5837_Library</a>
</TD>
<TD style="width: 50%;">
<img src="docs/Arduino_Pump_flow_chart.jpg" width=450 border=1>
</td>
</tr>
</table>

## Deployments

### South Florida Test Cruise
The first ever deployments of the in_situ_pump were conducted  in the Gulf Stream offshore South Florida and the Florida Keys on a cruise aboard R/V Walton Smith, October 7-9, 2025. Additional cruises are planned for 2026 in the Sargasso Sea.

<p>A few issues were identified during the this cruise. First, we found that on some deployments the microcontroller repeatedly shut down and rebooted. We identified the issue: the unit was losing power when it swung on the hydrowire during deployment because the springs in the battery compartment were too weak. So we replaced them with more robust springs.  Second, there were a two instances where the outlet of the pump head fractured. In order to address this, we are now using a tougher resin to print these parts. And third, the extraction efficiency of Be-7 from seawater was lower than expected.  In order to address this we are conducting tests using different flow rates and larger masses of filtering material.
	
<img src="docs/Pump_deployment_Walton_Smith_cruise.jpg" width=250> | <img src="docs/Filter_change_Walton_Smith_Cruise.jpg" width=315> 

## Acknowledgements
*This project is supported by the U.S.National Science Foundation (Grant # NSF-OCE-2446521). We are grateful for technical support and advice provided at Florida International University's Applied Research Center (FIU-ARC) from the following individuals: Dr Yipeng He, Theophile Pierre, Gabriel Cerioni, and Anthony Abrahao.  Emily Jackson and Sahaira Paz assisted with testing the device and operations on the South Florida cruise. We thank the captain and crew of research vessel F.G. Walton Smith. Photo credits: Emily Jackson and Clint Miller.*

