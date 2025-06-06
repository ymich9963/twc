/*
    twc : Trace Width Calculator.
    Copyright (C) 2024 Yiannis Michael (ymich9963)

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <time.h>

/* Constants */
#define MAX_NOTE_CHAR_COUNT 301
#define MAX_UNITS_STR 7
#define	k_INT 0.024f
#define	k_EXT 0.048f
#define	VAL_MAX 9999.999999999999999f
#define	VAL_MIN 0.0f
#define	STD_NAME_LEN 8
#define	METHOD_STR_LEN 2
#define	OUT_FILE_LEN 30
#define	PATH_LEN 255
#define	WELCOME_STR "\nTrace Width Calculator, Made by Yiannis Michael (2024).\n\nType 'twc -c <Current [A]> -w-oz <Copper Weight [oz/ft^2]>' to get output results.\nUse '--help' for explanation of the options.\n\nThis tool should only be used to assist design decisions and not be used to replace professional advice. Developer(s) have no liability whatsoever.\n\n" "This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\nSee the GNU General Public License for more details.\n"
#define	FEW_ARGS_STR "\nAn input of at least current and copper weight is required. Use no arguments to get the welcome message and either '-h' or '--help' to get the list of commands.\n"
#define	VERSION_STR "\nTrace Width Calculator (TWC)\nVersion 1.2.0.\n"
#define	DISCLAIMER_STR "Design assistance by the TWC tool is provided with no liability whatsover.\nFor final decisions on electronics designs, please consult an actual qualified person.\n"

/* Links to online calculators */
#define LINK_CIRCUIT_CALCULATOR "https://circuitcalculator.com/wordpress/2006/01/31/pcb-trace-width-calculator/"
#define LINK_NINJA_CALC         "https://ninjacalc.mbedded.ninja/calculators/electronics/pcb-design/track-current-ipc2152"
#define LINK_SMPS               "https://www.smps.us/pcb-calculator.html"
#define LINK_SIERRA_CIRCUITS    "https://twcalculator.app.protoexpress.com/"

/* Conversion macros */

/* Meters to X */
#define	CONV_M_TO_IN(x)     ((x) * 39.370078740157)
#define	CONV_M_TO_MIL(x)    ((x) * 39370.078740157)
#define	CONV_M_TO_OZFT2(x)  ((x) * 39370.078740157 / 1.378)
#define	CONV_M2_TO_MIL2(x)  ((x) * 1e7 / (2.54 * 2.54))
#define	CONV_M2_TO_IN2(x)   ((x) * 1e4 / (2.54 * 2.54))

/* Inches to X */
#define	CONV_IN_TO_M(x)     ((x) * 0.0254)
#define	CONV_IN_TO_MM(x)    ((x) * 25.4)
#define	CONV_IN_TO_MIL(x)   ((x) * 1e3)

/* Mils to X */
#define	CONV_MIL_TO_M(x)    ((x) * 0.0000254)
#define	CONV_MIL_TO_MM(x)   ((x) * 0.0254)
#define	CONV_MIL_TO_OZFT2(x) ((x) / 1.378)   // most sources say 1.37, few others say 1.378.
#define	CONV_MIL2_TO_M2(x)  ((x) * 0.0000254 * 0.0000254)
#define	CONV_MIL2_TO_CM2(x) ((x) * 0.00254 * 0.00254)
#define	CONV_MIL2_TO_MM2(x) ((x) * 0.0254 * 0.0254)
#define	CONV_MIL2_TO_IN2(x) ((x) * 0.000001)

/* Oz/ft^2 to X */
#define	CONV_OZFT2_TO_MIL(x) ((x) * 1.378)
#define	CONV_OZFT2_TO_M(x)  ((x) * 1.378 * 0.0000254)
#define	CONV_OZFT2_TO_MM(x) ((x) * 1.378 * 0.0254)
#define	CONV_OZFT2_TO_UM(x) ((x) * 1.378 * 25.4)

/* Other to X */
#define	CONV_FAHR_TO_CELS(x) (((x) - 32) / 1.8)
#define	CONV_CELS_TO_FAHR(x) (((x) * 1.8) + 32)
#define	CONV_WmK_TO_BTUhftF(x) ((x) / 1.730735)
#define	CONV_BTUhftF_TO_WmK(x) ((x) * 1.730735)

/* Check macros */

/* Check response from sscanf */
#define	CHECK_RES(x) ({ if (!(x)) { \
							fprintf(stderr, "Argument entered was wrong...\n"); \
							return 1; \
						} \
					  })

/* Check if value is between numerical limits */
#define	CHECK_LIMITS(x) ({ if ((x) > VAL_MAX || (x) < VAL_MIN) { \
							   fprintf(stderr, "Detected numbers out of range. Please check inputs and enter numbers between, \n%.15lf and %.15lf", VAL_MIN, VAL_MAX); \
							   return 1; \
						   } \
						 })

/* Check if an error occured to exit program */
#define	CHECK_ERR(x) ({ if ((x)) { \
							exit(EXIT_FAILURE); \
						} \
					  })

/* Check if a function returns failure */
#define	CHECK_RET(x) ({ if ((x)) { \
							return 1; \
						} \
					  })

typedef struct Dbl {
	double val;
	double outval;
	char units[MAX_UNITS_STR];
} dbl_t; /* Struct for inputs of type double */

typedef struct Std {
	char str[STD_NAME_LEN];
	uint16_t num;
} std_t; /* Struct for the standards */

typedef struct Layer {
	dbl_t trace_width;         // [mils]
	dbl_t resistance;          // [Ohms]
	dbl_t voltage_drop;        // [V]
	dbl_t power_loss;          // [W]
	dbl_t trace_temperature;   // [Celsius]
	dbl_t cs_area;             // [mils^2]
	dbl_t corr_cs_area;        // [mils^2]
	dbl_t corr_trace_width;    // [mils]
} layer_t; /* Outputs Structures */

typedef layer_t extl_t;
typedef layer_t intl_t;

typedef struct OFile {
	char fname[OUT_FILE_LEN];
	char path[PATH_LEN];
	uint8_t oflag;                // Output file flag
} ofile_t; /* Output file strcture */

typedef struct OP {
	intl_t intl;
	extl_t extl;
	layer_t layer;
} op_t; /* Output struct */

typedef struct CF {
	double copper_weight;
	double pcb_thickness;
	double plane_area;
	double plane_distance;
	double temp_rise;
	double pcb_thermal_cond;
} cf_t; /* Correction Factors Struct */

typedef struct IP ip_t;


typedef struct IP {
	/* Mandatory Inputs */
	dbl_t current;             // [A]
	dbl_t copper_weight;       // [oz/ft^2]

	/* Optional Inputs */
	char note[MAX_NOTE_CHAR_COUNT]; // Add a note about this output 
	std_t standard;             // IPC standard
	char method[METHOD_STR_LEN];// Method to use for calculations. Single character.
	dbl_t temp_rise;            // [Celsius]
	dbl_t temp_ambient;         // [Celsius]
	dbl_t trace_length;         // [cm]
	dbl_t pcb_thickness;        // [mm]
	dbl_t pcb_thermal_cond;     // [W/mK]
	dbl_t plane_area;           // [in^2]
	dbl_t plane_distance;       // [mils]
	dbl_t a;                    // [1/C] :resistivity temperature coefficient at 20C
	dbl_t resistivity;          // [Ohm*cm] :resistivity coefficient at 20C
	cf_t cf;                    // Correction Factors
	ofile_t ofile;              // Output file properties
	char uflag;                 // Units flag
    uint8_t precision;          // Decimal precision for outputs
    uint8_t width;              // Width of the outputted number in characters
    uint8_t no_colour_flag;     // Flag set when colour is ignored
    uint8_t quiet_flag;         // Quiet flag to remove appendix from output

	void (*defv)(ip_t*);        // Set default values
	void (*proc)(ip_t*, op_t*); // Calculation procedure
	int (*outp)(ip_t*, op_t*, FILE* file); // Output function
	int (*outu)(ip_t*, op_t*);  // Set output units
} ip_t; /* Input Struct */

enum {
	IPC2152 = 2152,
	IPC2221 = 2221,
}; /* Standards Enumeration */

/**
 * @brief Set the default values on the struct members used by all standards and methods.
 *
 * @param ip Input struct.
 */
void set_universal_defaults(ip_t* ip);

/**
 * @brief Set default values needed for the IPC2221 calculations.
 *
 * @param ip Input struct to store the inputs.
 */
void set_defv_IPC2221(ip_t* ip);

/**
 * @brief Set default values needed for the IPC2152, Method A calculations.
 *
 * @param ip Input struct to store the inputs.
 */
void set_defv_IPC2152_A(ip_t* ip);

/**
 * @brief Set default values needed for the IPC2152, Method B calculations.
 *
 * @param ip Input struct to store the inputs.
 */
void set_defv_IPC2152_B(ip_t* ip);

/**
 * @brief Set default values needed for the IPC2152, Method C calculations.
 *
 * @param ip Input struct to store the inputs.
 */
void set_defv_IPC2152_C(ip_t* ip);

/**
 * @brief Get the options and arguments provided.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param ip Input struct to store the inputs.
 *
 * @return Success or failure.
 */
int get_options(int argc, char** argv, ip_t* ip);

/**
 * @brief Used to correctly split the input and to scale the value depending on the SI prefix.
 *
 * @param ip_dbl dbl_t struct.
 * @param optstirng String that contains the value.
 * @param SI_derived_units Character for the SI derived units.
 *
 * @return Success or failure.
 */
int assign_values_units_metric(dbl_t* ip_dbl, char* optstring, char SI_derived_units);

/**
 * @brief Same as above but for the area.
 *
 * @param ip_dbl dbl_t struct.
 * @param optstirng String that contains the value.
 * @param SI_derived_units Character for the SI derived units.
 *
 * @return Success or failure.
 */
int assign_values_units_metric_area(dbl_t* ip_dbl, char* optstring, char SI_derived_units);

/**
 * @brief Used to assign the option values to the correct struct members. Difference between this function and `assign_values_units_metric` is that it simply assigns the values instead of converting them based on a prefix. Therefore it is also used to simply assign the correct values and units.
 *
 * @param ip_dbl dbl_t struct.
 * @param val Variable to store the value.
 * @param units String to use to set the units
 *
 * @return Success or failure.
 */
int assign_values_units_imperial(dbl_t* ip_dbl, char* optstring, char* units);

/**
 * @brief Calculate using the IPC2221 standard, sourced from http://circuitcalculator.com/wordpress/2006/03/12/pcb-via-calculator/.
 *
 * @param ip Input struct to store the inputs.
 * @param op Output struct to store the outputs.
 */
void calcs_IPC2221(ip_t* ip, op_t* op);

/**
 * @brief Calculate using the IPC2152 standard, Method A which is sourced from https://ninjacalc.mbedded.ninja/calculators/electronics/pcb-design/track-current-ipc2152.
 *
 * @param ip Input struct to store the inputs.
 * @param op Output struct to store the outputs.
 */
void calcs_IPC2152_A(ip_t* ip, op_t* op);

/**
 * @brief Calculate using the IPC2152 standard, Method B which is sourced from https://www.smps.us/pcb-calculator.html.
 *
 * @param ip Input struct to store the inputs.
 * @param op Output struct to store the outputs.
 */
void calcs_IPC2152_B(ip_t* ip, op_t* op);

/**
 * @brief Calculate using the IPC2152 standard, Method C which is sourced from https://twcalculator.app.protoexpress.com/.
 *
 * @param ip Input struct to store the inputs.
 * @param op Output struct to store the outputs.
 */
void calcs_IPC2152_C(ip_t* ip, op_t* op);

/**
 * @brief Set the units for the IPC2221 outputs.
 *
 * @param ip Input struct to store the inputs.
 * @param op Output struct to store the outputs.
 *
 * @return Success or failure.
 */
int set_outu_IPC2221(ip_t* ip, op_t* op);

/**
 * @brief Set the units for the IPC2152 Method A outputs.
 *
 * @param ip Input struct to store the inputs.
 * @param op Output struct to store the outputs.
 *
 * @return Success or failure.
 */
int set_outu_IPC2152_A(ip_t* ip, op_t* op);

/**
 * @brief Set the units for the IPC2152 Method B outputs.
 *
 * @param ip Input struct to store the inputs.
 * @param op Output struct to store the outputs.
 *
 * @return Success or failure.
 */

int set_outu_IPC2152_B(ip_t* ip, op_t* op);
/**
 * @brief Set the units for the IPC2152 Methods C output. This implementation doesn't any correction so it's much more similar to the IPC2221 implementation.
 *
 * @param ip Input struct to store the inputs.
 * @param op Output struct to store the outputs.
 *
 * @return Success or failure.
 */
int set_outu_IPC2152_C(ip_t* ip, op_t* op);

/**
 * @brief Get the chosen standard and method from the input options. Called before get_options() so that the correct default variables are set.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param ip Input struct to store the inputs.
 *
 * @return Success or failure.
 */
int get_standard_method(int argc, char** argv, ip_t* ip);

/**
 * @brief Used to check the inputted standard option string, with the array containing the names of the standards. Index is used to set the standard numerical representation.
 *
 * @param strval String value to compare to the array containing the standard names.
 * @param standard_arr Array containing the standard names.
 * @param size Size of the array.
 * @param index Index when the string value matches an entry in the array.
 *
 * @return Success or failure.
 */
int check_standard(char* strval, const char** standard_arr, const unsigned int size, unsigned char* index);

/**
 * @brief Used to check the inputted method agains an array containing the existing method codes/characters. No need to use the index since it's just characters.
 *
 * @param chrval Inputted character argumen.
 * @param method_arr Array containing the method characters.
 * @param size Size of the array.
 *
 * @return Success or failure.
 */
int check_method(char chrval, const char* method_arr, unsigned int size);

/**
 * @brief Set the default, process, output unit, and output print set functions based on the standard and the method chosen.
 *
 * @param ip Input struct to check the method and the standard.
 *
 * @return Success or failure.
 */
int sel_functions(ip_t* ip);

/**
 * @brief Set the path and file for the outputs to be saved in.
 *
 * @param ofile Output file struct containing everything necessary to save the file.
 * @param optarg Input used by the option.
 */
void set_output_file(ofile_t* ofile, char* optarg);

/**
 * @brief Auto-generate the file name using the current date and time. Concatinate the strings together to form the full name.
 *
 * @param fname File name to use in the concatination.
 */
void autogen_file_name(char* fname);

/**
 * @brief Get the date in time as a string.
 *
 * @return String of the date and time joined together.
 */
char* get_time();

/**
 * @brief Calculate Resistance, Voltage drop, and Power loss.
 *
 * @param ip Input struct to get the inputs used in the calculation.
 * @param layer Output layer struct to store the results.
 */
void calc_resistance_vdrop_ploss(ip_t* ip, layer_t* layer);

/**
 * @brief Used to calculate the width of the trace.
 *
 * @param ip Input struct to get the required values.
 * @param cs_area Cross sectional area of the trace.
 * @return Trace width in type double.
 */
double calc_trace_width_mils(ip_t* ip, double cs_area);

/**
 * @brief Calculate the resistance of the trace. The constants were copied from https://en.wikipedia.org/wiki/Electrical_resistivity_and_conductivity#Resistivity_and_conductivity_of_various_materials which also gave the reference temperature of 20C. 
 *
 * @param ip Input struct to get the required values.
 * @param cs_area Cross sectional area of the trace.
 * @return Resistance in type double.
 */
double calc_resistance(ip_t* ip, double cs_area);

/**
 * @brief Calculate the Voltage drop.
 *
 * @param ip Input struct to get the values.
 * @param resistance Resistance in Ohms.
 * @return Voltage drop in type double.
 */
double calc_vdrop(ip_t* ip, double resistance);

/**
 * @brief Calculate the power loss.
 *
 * @param ip Input struct to get the values.
 * @param vdrop Voltage drop in V.
 * @return Power loss in type double.
 */
double calc_power_loss(ip_t* ip, double vdrop);

/**
 * @brief Get the specified text with the specified ANSI colours.
 *
 * @param str Text to be returned with ANSI colours.
 * @param FG FG or foreground value of the ANSI colour.
 * @param BG BG or background value of the ANSI colour.
 * @param ignore_flag Flag to ignore setting the colours for the string.
 * @return The specified text with the ANSI colours.
 */
char* get_text_ansi_colours(char* str, int FG, int BG, uint8_t ignore_flag);

/**
 * @brief Print the credits string which is after the appendix.
 *
 * @param file Pointer to output file.
 * @param standard Standard string.
 * @param method Method character (techincally string).
 * @param link Link to the online calculator.
 * @param no_colour_flag Flag to specify no ANSI colour.
 */
void print_credits_string(FILE* file, char* standard, char* method, char* link, uint8_t no_colour_flag);

/**
 * @brief Print the disclaimer string at the end of the output.
 *
 * @param file Pointer to output file.
 * @param no_colour_flag Flag to specify no ANSI colour.
 */
void print_disclaimer_string(FILE* file, uint8_t no_colour_flag);

/**
 * @brief Outputted results when using the IPC2221.
 *
 * @param ip Input struct to store the inputs.
 * @param op Output struct to store the outputs.
 * @param file Buffer to output the strings.
 */
int output_results_IPC2221(ip_t* ip, op_t* op, FILE* file);

/**
 * @brief Outputted results when using the IPC2152, Method A.
 *
 * @param ip Input struct to store the inputs.
 * @param op Output struct to store the outputs.
 * @param file Buffer to output the strings.
 */
int output_results_IPC2152_A(ip_t* ip, op_t* op, FILE* file);

/**
 * @brief Outputted results when using the IPC2152, Method B.
 *
 * @param ip Input struct to store the inputs.
 * @param op Output struct to store the outputs.
 * @param file Buffer to output the strings.
 */
int output_results_IPC2152_B(ip_t* ip, op_t* op, FILE* file);

/**
 * @brief Outputted results when using the IPC2152, Method C.
 *
 * @param ip Input struct to store the inputs.
 * @param op Output struct to store the outputs.
 * @param file Buffer to output the strings.
 */
int output_results_IPC2152_C(ip_t* ip, op_t* op, FILE* file);

/**
 * @brief Output the help string to the terminal.
 */
int output_help();
