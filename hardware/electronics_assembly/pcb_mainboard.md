# pcb_mainboard
 	 
pcb_mainboard contains the [Teensy 4.1](https://www.pjrc.com/store/teensy41.html) microprocessor and connections for external components including the motor electronic speed controller (ESC), pressure sensor, switches and LEDs, and the USB port. A Buck converter module regulates the voltage supplied to Teensy (5V). A coin cell battery holder powers Teensy’s real time clock (RTC) when the unit is powered down. Teensy’s built-in microSD card slot allows for data logging. Optional components include an INA219 current sensor (to monitor amps consumed by the motor) and a Hall effect flowmeter connection. pcb_mainboard is mounted on the pcb_tray_part via four mounting holes.  
<P><table>
<tr>
<td width=355>
<img src="Images/PCB_mainboard_assembled.jpg" width=350>
</td>
<td width=355>
<img src="Images/PCB_mainboard_with_Teensy.jpg" width=350>
</td>
</tr>
<tr>
<td align=center>
Assembled PCB mainboard
</td>
<td align=center valign=top>
Assemble PCB mainboard with with teensy 4.1
</td>
</tr>
</table></p>

> [!NOTE]
> Pins Int2 is unused as of the pump’s current state.

## Assembly (approximate time: 30 minutes):  
> [!IMPORTANT]
> * Solder pins onto all four vias on back side of voltage regulator.
> * Remove terminal block included in current sensor and replace with pins, and solder the other six pins onto the remaining vias.
> * All components mount to the top of the Mainboard.

1.	Insert pin headers, battery holder, JST-XH connectors, screw terminal block connectors, voltage regulator, and current sensor to PCB board.
2.	Solder all pins.
3.	Insert Teensy 4.1 with Micro SD into headers.
4.	Insert coin battery.

<P><img src="Images/PCB_mainboard_BOM.jpg"></P>

### Gerber files
Gerber files for PCB production can be found in the <a href="Gerbers/">Gerber files directory</a>.
<P><table>
<tr>
<td width=355>
<img src="Images/PCB_mainboard_with_current_sensor.jpg" width=350>
</td>
<td width=355>
<img src="Images/PCB_mainboard_without_current_sensor.jpg" width=350>
</td>
</tr>
<tr>
<td align=center>
PCB mainboard with current sensor
</td>
<td align=center valign=top>
PCB mainboard without current sensor
</td>
</tr>
</table></p>
