# TWC Methods
Methods used in the TWC were derived from already existing online calculators by examining the source code and their behaviours by inputting various values. Improvements were made such as better naming of variables, less rounding, and better code structure. Default behaviour of the program is metric for all available inputs and outputs, as well as the IPC-2152 standard, Method A.

## IPC2221
The most used standard for determining rigid PCB trace widths up until now was the [IPC-2221](https://www-eng.lbl.gov/~shuman/NEXT/CURRENT_DESIGN/TP/MATERIALS/IPC_2221.pdf) (1998), with revisions [IPC-2221A](https://www-eng.lbl.gov/~shuman/NEXT/CURRENT_DESIGN/TP/MATERIALS/IPC-2221A(L).pdf) (2003), [IPC-2221B](https://www.ipc.org/TOC/IPC-2221B.pdf) (2012), and [IPC-2221C](https://shop.ipc.org/ipc-2221/ipc-2221-standard-only/Revision-c/english) (2023). 

### Method
To find the current use, 

   $I = k \times \Delta T^{0.44} \times A^{0.725}$ 

which then can be rearranged in terms of the area,

   $A = (\frac{I}{k \times \Delta T^{0.44}})^{0.725}$

Dividing the result by the height (or weight in this case) of the trace, the width is derived,

   $w = (\frac{I}{k \times \Delta T^{0.44}})^{0.725}) / h$

In the above equations,
   - $A$ is the area in $mils^{2}$, with $h$ being the height and $w$ being the width.
   - $I$ is the current in the trace in Amperes $A$.
   - $\Delta T$ is the temperature rise of the trace. 
- Constant $k$ is $0.024$ for internal traces and $0.048$ for external traces.

Constraints to this method include,
   - Currents up to 35 A external and 17.5 A internal.
   - Temperature rises from 10 C to 100 C.
   - Trace widths between 0 and 10.16mm.
   - Copper weights between 0.5 and 3 oz/ft^2.
   - No vias along the length of the trace.

## IPC2152
I have not looked at the standards document directly and I do not have an understanding of how to actually implement the IPC2152, therefore any comments I make in this section are about the implementations.

### Method A
Derived from the [NinjsCalc](https://ninjacalc.mbedded.ninja/calculators/electronics/pcb-design/track-current-ipc2152.) WebApp which also has a [GitHub repository](https://github.com/gbmhunter/NinjaCalc). This implementation is the only one that uses a 2-D coefficient array to calculate a copper weight correction factor. It also uses correction factors for PCB thickness, plane distance, and PCB thermal conductivity. Using these correction factors it outputs a corrected trace width and corss-sectional area.

### Method B
Derived from [SMPS.us](https://www.smps.us/pcb-calculator.html), which was also cited by [Altium Resources](https://resources.altium.com/p/using-ipc-2152-calculator-designing-standards). The website lists a different equation for area whereas in the source code they use a different one. In this implementation they also used correction factors for copper weight, PCB thickness, plane area, plane distance, and temperature rise. These correction factors are then used similarly to Method A, as it outputs a corrected trace width and corss-sectional area.

### Method C
Derived from [Sierra Circuits](https://twcalculator.app.protoexpress.com/). Another version of this also exists in this link [here](https://designertools.app.protoexpress.com/?appid=TWCCCAL). External and internal trace width calculations only exist in this method and it is the only method not using any correction factors. It is also using a wrong resistivity value for the resistance calculation.

