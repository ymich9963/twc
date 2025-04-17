# Trace Width Calculator (TWC)
![badge](https://badgen.net/badge/Coverage/100/blue) 
<a href="https://scan.coverity.com/projects/ymich9963-twc">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/31168/badge.svg"/>
</a>

A calculator tool used to assist designing rigid PCB traces. Implements both the IPC2221 and IPC2152 standards and has the ability to choose between the two, with the latter having three methods available. Each method used for the standards was derived from one of the various websites that claim to implement an trace width calculator. More information regarding certain formulas used are under `docs/`.

## Features
- Four total methods for calculating trace widths in rigid PCBs, listed in the next section.
- Default units are metric. Choose to change units for any input and change the output units from imperial to metric.
- Convert any value used in the tool with the conversion functions (use `--help` to list them or see below).
- Optionally output the results to a file for saving.

## Motivation
I always found confusing how an open-source tool for this type of electronics design use didn't exist. Therefore I decided to make one! The initial purpose of this tool was to collect most of the available online trace width calculator information and implementations, and try to improve on them, while implementing them on an open-source offline command-line tool. The completely different implementations of the IPC2152 standard does put in question the validity of these calculators and their implementations. Thankfully, due to the open-source nature of the project, the differences between the implementations are clearly viewable, and the user can freely choose the one that seems best. Future development is definitely to encourage the creation of a TWC implementation of the IPC2152 method.

## Methods
One method is implemented for IPC2221 and three methods for IPC2152. The tool defaults to the IPC2152 standard, Method A.

### IPC2221
- Method: The ubiquitous way of calculating trace widths. Derived from [The CircuitCalculator.com Blog](https://circuitcalculator.com/wordpress/2006/01/31/pcb-trace-width-calculator/) and [Omni Calculator](https://www.omnicalculator.com/other/pcb-trace-width#how-to-calculate-the-width-of-a-pcb-trace). This is the only available method with this standard

### IPC2152
- Method A: Derived from [NinjaCalc](https://ninjacalc.mbedded.ninja/calculators/electronics/pcb-design/track-current-ipc2152). Default method for the TWC.
- Method B: Derived from [SMPS.us](https://www.smps.us/pcb-calculator.html) which was also posted on the [Altium Resources](https://resources.altium.com/p/using-ipc-2152-calculator-designing-standards).
- Method C: Derived from [Sierra Circuits](https://twcalculator.app.protoexpress.com/).

## Installing
To install and use the `twc` command. Make sure to have the latest version, place it in a folder, and add that folder path to your Enviroment Variables.

## Using
Mandatory inputs to get any kind of output are *Copper Weight* and *Current* specified with `-w` and `-c` respectively. TWC defaults to metric units for input and output, as well as the IPC2152 standard using Method A. TWC accepts SI prefixes on all SI units used in the software (Amps, metres, etc.) from Terrra (T) down to pico (p).

See the `--help` output below for the available options, as well as some example uses below,
```
Help for the Trace Width Calculator (TWC). Specify units with the long options, listed below the short options.
                --standard <Standard>                           = Choose the standard to use to calculate trace widths. Options are 'IPC2221' and `IPC2152`.

                --method <Method>                               = Choose the method for the desired standard. Currently only used by the IPC2152 procedure with method options 'A', 'B', and 'C'.

        -n,     --note "<Text>"                                 = Add a note to the start of the output. Make sure to put the note between quotes.

        -c,     --current <Current [A]>                         = Input the trace current in Amps.

        -w,     --copper-weight <Copper Weight [m]>             = Input the copper weight in meters. Use the other options below for imperial units.
        -w-mil, --copper-weight-mil
        -w-oz,  --copper-weight-oz

        -r[-C], --temperature-rise <Temp. Rise [C]>             = Input the maximum allowed temperature rise in C.
        -r-F,   --temperature-rise-F

        -a[-C], --temperature-ambient <Temp. Ambient  [C]>      = Input the ambient temperature of the trace in C.
        -r-F,   --temperature-ambient-F

        -l,     --trace--length <Trace Length [m]>              = Input the trace length in centimeters. Use the other options below for imperial units.
        -l,     --trace--length-mm
        -l-mil, --trace--length-mil
        -l-in,  --trace--length-inches

        -t,     --pcb-thickness <Thickness [m]>                 = Input the PCB thickness in meters. Use the other options below for imperial units.
        -t-mil, --pcb-thickness-mil
        -t-in,  --pcb-thickness-in

        -e,     --pcb-thermal-conductivity <Therm. Con. [W/mK]> = Input the PCB thermal conductivity in Watts per meter Kelvin.

        -p,     --plane-area <Plane Area [m^2]>              = Input the plane cross sectional area in meters squared. Use the other options below for imperial units.
        -p-in2, --plane-area-in2
        -p-mil2,--plane-area-mil2

        -d,     --plane-distance <Plane Distance [m]>           = Input the plane distance in meters. Use the other options below for imperial units.
        -d-mil, --plane-distance-mil
        -d-in,  --plane-distance-inches

                --resistivity <Resistivity [Ohm m]>             = Input the resistivity in Ohm meters.

                --temperature-coefficient <Temp. Coef. [1/C]>   = Input the temperature coefficient.

        -o,     --output <File Name>                            = Write the name of the outputted file. Use '.txt' to create a text file. Use a single '.' to auto-generate
                                                                  the name based on date/time. Can also write the full path to the file, e.g. 'C:/Users/user/output.txt'
                                                                  or stop at 'C:/Users/user/' to use the auto-generated file name.

        -m,     --metric                                        = Make the output units be metric.

        -i,     --imperial                                      = Make the output units be imperial. Default behaviour, therefore just implemented for completion.


                        CONVERSIONS

Usage example 'twc --conversion-m-to-ozft2 <Value>'. Can use an SI prefix in the input when converting from meters.

        --convert-m-to-ozft2    = From meters to oz per foot sq.
        --convert-m-to-mil      = From meters to mil.
        --convert-m2-to-in2     = From meters sq. to inches sq.
        --convert-m2-to-mil2    = From meters sq. to mil sq.
        --convert-mil-to-mm     = From mils to milimeters.
        --convert-mil-to-ozft2  = From mils to ounce per foot sq.
        --convert-mil2-to-cm2   = From mils sq. to centimeters sq.
        --convert-mil2-to-mm2   = From mils sq. to milimeters sq.
        --convert-ozft2-to-mil  = From ounce per foot sq. to mils.
        --convert-ozft2-to-mm   = From ounce per foot sq. to milimeters.
        --convert-ozft2-to-um   = From ounce per foot sq. to micrometers.
        --convert-F-to-C        = From Fahrenheit to Celsius.
        --convert-C-to-F        = From Celsius to Fahrenheit.
        --convert-WmK-to-BTUhftF        = From Watts per mili Kelvin to BTU/h*ft*F.
        --convert-BTUhftF-to-WmK        = From BTU/h*ft*F to Watts per mili Kelvin.

```

### Example Uses 
Most basic type of output where the current is 1 A and the copper weight is the 35 um standard, 
```
twc -c 1 -w 35u
```
Changing standards can be done with the `--standard` and `--method` flags. For example to use the IPC2221 standard,
```
twc -c 1 -w 35u --standard IPC2221
```
Can instead use imperial inputs like oz/ft^2 to specify the copper weight. This can be done for all the options listed in the `--help`,
```
twc -c 1 -w-oz 1 --standard IPC2221
```
Feel free to add more options for use with the desired method. Some options won't have any effect on other methods, and that's easy to figure out from the output or the details in the `--help` option. Example below shows how to use trace length and plane distance in IPC2152, Method A,
```
twc -c 1 -w-oz 1 -l 2c -d 1c
```
Choose to place a small note at the top of your output to remind yourself what this output is for,
```
twc -c 1 -w-oz 1 -l 2c -d 1c --note "Example note!"
```
Output from that command is shown below,
```
Note:
Example note!

Current:                1.000000        [A]
Copper Weight:          1.000000        [oz/ft^2]
Temperature, Rise:      10.000000       [C]
Trace Length:           2.000000        [cm]
PCB Thickness:          1.600000        [mm]
Plane Distance:         1.000000        [cm]
PCB Thermal Cond.:      0.200000        [W/mK]

Area:                   0.009919        [mm^2]
Corrected Area:         0.016523        [mm^2]

- Constants used for the P/I/V calculations were,

        a = 0.0039300   [1/C] (Temperature Coefficient)
 rho = 0.000000017200   [Ohm m] (Resistivity)

- Constants and method used were derived from https://ninjacalc.mbedded.ninja/calculators
/electronics/pcb-design/track-current-ipc2152.

- TWC used the IPC2152 standard, Method A.

Design assistance by the TWC tool is provided with no liability whatsover. For final deci
sions on electronics designs, please consult an actual qualified person.
```
Choose to output this to a text file by using the `-o` option and by either inputting a name or a '.' to use the autogenerated output.
```
twc -c 1 -w-oz 1 -l 2c -d 1c --note "Example note!" -o .
```
The internal conversion functions are also available for quick and easy conversion for some of the inputs to the TWC, for example convert um to oz/ft^2.
```
twc --convert-m-to-ozft2 35u
```

## Building
Clone the repository and got to this directory. Using `make` simply run in a command line,
```
make
```
And `twc` should be build in a new `build/` directory. Check the `docs\` for info on how to contribute to the project.

## Tests and Coverage
Running the tests or coverage can be done by running,
```
make test
```
```
make coverage
```
Testing suite used is [Unity](https://github.com/ThrowTheSwitch/Unity) and LLVM-COV for coverage.

## Sources
Some sources for creating the tool are listed below, 
- Trace Width Calculators,
	- [Advanced PCB](https://www.advancedpcb.com/en-us/tools/trace-width-calculator/)
	- [Circuit Calculator](https://circuitcalculator.com/wordpress/2006/01/31/pcb-trace-width-calculator/)
	- [Omnicalculator](https://www.omnicalculator.com/other/pcb-trace-width#how-to-calculate-the-width-of-a-pcb-trace)
	- [SMP.us](https://www.smps.us/pcb-calculator.html)
	- [NinjaCalc - IPC2152](https://ninjacalc.mbedded.ninja/calculators/electronics/pcb-design/track-current-ipc2152)
    - [NinjaCalc - IPC2221a](https://ninjacalc.mbedded.ninja/calculators/electronics/pcb-design/track-current-ipc2221a)
    - [Sierra Circuits](https://twcalculator.app.protoexpress.com/)
    - [Sierra Circuits (same as above?)](https://designertools.app.protoexpress.com/?appid=TWCCCAL)
- Conversion calculators,
	- [Convert-me](https://www.convert-me.com/en/convert/area/?u=mm2&v=0.0111) for area conversion
	- [UnitConverters](https://www.unitconverters.net/length/mil-to-millimeter.htm)
	- [Convert-measurement-units](https://www.convert-measurement-units.com/conversion-calculator-quick.php)
	- [Metric Conversions](https://www.metric-conversions.org/temperature/fahrenheit-to-celsius.htm) C to F conversion
- Other Resources
	- [Resistivity/Temperature Coefficients](https://www.engineeringtoolbox.com/resistivity-conductivity-d_418.html)
	- [Standard PCB Thickness – An Important Role in PCB Function](https://www.nextpcb.com/blog/standard-pcb-thickness)
	- [What is the Thermal Conductivity of Different PCBs](https://www.pcbonline.com/blog/pcb-thermal-conductivity.html)
	- [How Thick is 1 oz Copper](https://pcbprime.com/pcb-tips/how-thick-is-1oz-copper/)
	- [PCB Universe](https://www.pcbuniverse.com/pcbu-tech-tips.php?a=4)
	- [Resistivity and Temp coefficient source](http://hyperphysics.phy-astr.gsu.edu/hbase/Tables/rstiv.html)
