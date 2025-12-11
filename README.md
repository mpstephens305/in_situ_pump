# in_situ_pump
A low cost, open source in situ pump for marine and freshwater sampling.

![Pump deployment aboard RV Walton Smith in October 2025](docs/Pump_deployment_Walton_Smith_cruise_cropped2.jpg)

<P><b>Motivation: </b>b>In situ pumps allow for simultaneous sampling at multiple depths. However, commercially available units can cost tens of thousands of dollars. For applications involving shallow deployments, a more feasible solution is desirable.
</P>

## Features
3D printed pump unit driven by a Blue Robotics subsea motor.

Controlled by a Teensy 4.1 development board.

Electronics and power supply inside watertight enclosure.

Adaptable to various filter media (cartridges, GFF, acrylic fiber, etc.).

Adaptable to sampling different chemical and isotopic species in the dissolved and particulate phases in seawater and freshwater.

Simple operation.

Easily programmable start delay, sampling duration, and motor speed.

<img width="4242" height="1240" alt="image" src="https://github.com/user-attachments/assets/aca9b331-d454-4bb0-bf71-1da4869d08f4" />


[Teensy 4.1](https://www.pjrc.com/store/teensy41.html) development board

## How to Get One


## Hardware
	(drawing)
	(frame)
	(Pump)
	(electronics assembly)
	(filter holder assembly)

## Software
<table>
<TR>
<TD>
<a href="https://www.arduino.cc/en/software/">Arduino IDE</a>
the <a href="https://www.pjrc.com/teensy/teensyduino.html")Teensyduino</a> add-on for Arduino IDE
KurtE <a href="https://github.com/KurtE/MTP_Teensy")MTP_Teensy</a> library
the <a href="https://github.com/bluerobotics/BlueRobotics_MS5837_Library">Blue Robotics_MS5837_Library</a>
</TD>
<TD>
<img src="docs/Arduino_Pump_flow_chart.jpg" width=450 border=1>
</td>
</tr>
</table>

## Deployments

### South Florida Test Cruise
in_situ_pump first-ever deplyments were in the Gulf Stream on a cruise aboard R/V Walton Smith, October 7-9, 2025. 

<img src="docs/Pump_deployment_Walton_Smith_cruise.jpg" width=250> | <img src="docs/Filter_change_Walton_Smith_Cruise.jpg" width=315> 

## Acknowledgements
This project is supported by the U.S.National Science Foundation (Grant # OCE). We are grateful for technical support and advice provided at Florida International University's Applied research Center (FIU-ARC) from the following individuals: Dr Yipeng He, Theophile Pierre, and Gabriel Cerioni.  Emily Jackson and Sahaira Paz assisted with testing the device and operations on the South Florida cruise. We thank the captain and crew of research vessel F.G. Walton Smith. Emily Jackson and Clint Miller provided photographs.
