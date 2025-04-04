/*
twc : Trace Width Calculator.
Copyright (C) 2024 Yiannis Michael (ymich9963)

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "twc.h"

int get_options(int argc, char** restrict argv, ip_t* restrict ip)
{
    double val = 0.0f; /* Temporary value to store the argument */
    dbl_t conversion = {0}; /* Store the conversion */

    if (argc == 1) {
        printf(WELCOME_STR);

        return 1;
    }

    for (int i = 1; i < argc; i++) {
        /* Check these options before anything else */
        if (!(strcmp("-h", argv[i])) || !(strcmp("--help", argv[i]))) {
            output_help();

            return 1;
        }

        if (!(strcmp("--version", argv[i]))) {
            printf(VERSION_STR);

            return 1;
        }

        if (!(strcmp("-n", argv[i])) || !(strcmp("--note", argv[i]))) {
            strcpy(ip->note, argv[i + 1]); 
            i++;
            continue;
        }

        if (!(strcmp("-o", argv[i])) || !(strcmp("--output", argv[i]))) {
            ip->ofile.oflag = 1;
            set_output_file(&ip->ofile, argv[i + 1]);
            i++;
            continue;
        }

        if (!(strcmp("-c", argv[i])) || !(strcmp("--current", argv[i]))) {
            CHECK_RET(assign_values_units_metric(&ip->current, argv[i + 1], 'A'));
            i++;
            continue;
        }

        if (!(strcmp("-w", argv[i])) || !(strcmp("--copper-weight", argv[i]))) {
            CHECK_RET(assign_values_units_metric(&ip->copper_weight, argv[i + 1], 'm'));
            ip->copper_weight.val = CONV_M_TO_OZFT2(ip->copper_weight.val);
            i++;
            continue;
        }

        if (!(strcmp("-w-oz", argv[i])) || !(strcmp("--copper-weight-oz", argv[i]))) {
            CHECK_RET(assign_values_units_imperial(&ip->copper_weight, argv[i + 1], "oz/ft^2"));
            i++;
            continue;
        }

        if (!(strcmp("-w-mil", argv[i])) || !(strcmp("--copper-weight-mil", argv[i]))) {
            CHECK_RET(assign_values_units_imperial(&ip->copper_weight, argv[i + 1], "mil"));
            ip->copper_weight.val = CONV_MIL_TO_OZFT2(ip->copper_weight.val); /* Convert back to oz/ft^2 for the calculations to work */
            i++;
            continue;
        }

        if (!(strcmp("-r", argv[i])) || !(strcmp("-r-C", argv[i])) || !(strcmp("--temperature-rise", argv[i]))) {
            CHECK_RET(assign_values_units_metric(&ip->temp_rise, argv[i + 1], 'C'));
            i++;
            continue;
        }

        if (!(strcmp("-r-F", argv[i])) || !(strcmp("--temperature-rise-F", argv[i]))) {
            CHECK_RET(assign_values_units_metric(&ip->temp_rise, argv[i + 1], 'F'));
            ip->temp_rise.val = CONV_FAHR_TO_CELS(ip->temp_rise.val);
            i++;
            continue;
        }

        if (!(strcmp("-a", argv[i])) || !(strcmp("-a-C", argv[i])) || !(strcmp("--temperature-ambient", argv[i]))) {
            CHECK_RET(assign_values_units_metric(&ip->temp_ambient, argv[i + 1], 'C'));
            i++;
            continue;
        }

        if (!(strcmp("-a-F", argv[i])) || !(strcmp("--temperature-ambient-F", argv[i]))) {
            CHECK_RET(assign_values_units_metric(&ip->temp_ambient, argv[i + 1], 'F'));
            ip->temp_ambient.val = CONV_FAHR_TO_CELS(ip->temp_ambient.val);
            i++;
            continue;
        }

        if (!(strcmp("-l", argv[i])) || !(strcmp("--trace-length", argv[i]))) {
            CHECK_RET(assign_values_units_metric(&ip->trace_length, argv[i + 1], 'm'));
            i++;
            continue;
        }

        if (!(strcmp("-l-mil", argv[i])) || !(strcmp("--trace-length-mil", argv[i]))) {
            CHECK_RET(assign_values_units_imperial(&ip->trace_length, argv[i + 1], "mil"));
            ip->trace_length.val = CONV_MIL_TO_MM(ip->trace_length.val);
            i++;
            continue;
        }

        if (!(strcmp("-l-in", argv[i])) || !(strcmp("--trace-length-mil", argv[i]))) {
            CHECK_RET(assign_values_units_imperial(&ip->trace_length, argv[i + 1], "in"));
            ip->trace_length.val = CONV_IN_TO_MM(ip->trace_length.val);
            i++;
            continue;
        }

        if (!(strcmp("-t", argv[i])) || !(strcmp("--pcb-thickness", argv[i]))) {
            CHECK_RET(assign_values_units_metric(&ip->pcb_thickness, argv[i + 1], 'm'));
            ip->pcb_thickness.val = CONV_M_TO_MIL(ip->pcb_thickness.val);
            i++;
            continue;
        }

        if (!(strcmp("-t-mil", argv[i])) || !(strcmp("--pcb-thickness-mil", argv[i]))) {
            CHECK_RET(assign_values_units_imperial(&ip->pcb_thickness, argv[i + 1], "mil"));
            i++;
            continue;
        }

        if (!(strcmp("-t-in", argv[i])) || !(strcmp("--pcb-thickness-mil", argv[i]))) {
            CHECK_RET(assign_values_units_imperial(&ip->pcb_thickness, argv[i + 1], "mil"));
            ip->pcb_thickness.val = CONV_IN_TO_MIL(ip->pcb_thickness.val);
            i++;
            continue;
        }

        if (!(strcmp("-e", argv[i])) || !(strcmp("--pcb-thermal-conductivity", argv[i]))) {
            CHECK_RET(assign_values_units_imperial(&ip->pcb_thermal_cond, argv[i + 1], "W/mK"));
            ip->pcb_thermal_cond.val = CONV_WmK_TO_BTUhftF(ip->pcb_thermal_cond.val);
            i++;
            continue;
        }

        if (!(strcmp("-p", argv[i])) || !(strcmp("--plane-area", argv[i]))) {
            CHECK_RET(assign_values_units_metric_area(&ip->plane_area, argv[i + 1], 'm'));
            ip->plane_area.val = CONV_M2_TO_IN2(ip->plane_area.val);
            i++;
            continue;
        }

        if (!(strcmp("-p-in2", argv[i])) || !(strcmp("--plane-area-in2", argv[i]))) {
            CHECK_RET(assign_values_units_imperial(&ip->plane_area, argv[i + 1], "in^2"));
            i++;
            continue;
        }

        if (!(strcmp("-p-mil2", argv[i])) || !(strcmp("--plane-area-mil2", argv[i]))) {
            CHECK_RET(assign_values_units_metric_area(&ip->plane_area, argv[i + 1], 'm'));
            ip->plane_area.val = CONV_MIL2_TO_IN2(ip->plane_area.val);
            i++;
            continue;
        }

        if (!(strcmp("-d", argv[i])) || !(strcmp("--plane-distance", argv[i]))) {
            CHECK_RET(assign_values_units_metric_area(&ip->plane_distance, argv[i + 1], 'm'));
            ip->plane_distance.val = CONV_M_TO_MIL(ip->plane_distance.val);
            i++;
            continue;
        }

        if (!(strcmp("-d-mil", argv[i])) || !(strcmp("--plane-distance-mil", argv[i]))) {
            CHECK_RET(assign_values_units_imperial(&ip->plane_distance, argv[i + 1], "mil"));
            i++;
            continue;
        }

        if (!(strcmp("-d-in", argv[i])) || !(strcmp("--plane-distance-in", argv[i]))) {
            CHECK_RET(assign_values_units_imperial(&ip->plane_distance, argv[i + 1], "mil"));
            ip->plane_distance.val = CONV_IN_TO_MIL(ip->plane_distance.val);
            i++;
            continue;
        }

        if (!(strcmp("--resistivity", argv[i]))) {
            CHECK_RET(assign_values_units_imperial(&ip->resistivity, argv[i + 1], "\0"));
            i++;
            continue;
        }

        if (!(strcmp("--temperature-coefficient", argv[i]))) {
            CHECK_RET(assign_values_units_imperial(&ip->a, argv[i + 1], "\0"));
            i++;
            continue;
        }

        if (!(strcmp("-m", argv[i])) || !(strcmp("--metric", argv[i]))) {
            ip->uflag = 'm';
            continue;
        }

        if (!(strcmp("-i", argv[i])) || !(strcmp("--imperial", argv[i]))) {
            ip->uflag = 'i';
            continue;
        }

        /* Conversions */
        if (!(strcmp("--convert-m-to-ozft2", argv[i]))) {
            CHECK_RET(assign_values_units_metric_area(&conversion, argv[i + 1], '\0'));
            printf("\n%lf\n\n", CONV_M_TO_OZFT2(val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-m-to-mil", argv[i]))) {
            CHECK_RET(assign_values_units_metric_area(&conversion, argv[i + 1], '\0'));
            printf("\n%lf\n\n", CONV_M_TO_MIL(val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-m2-to-in2", argv[i]))) {
            CHECK_RET(assign_values_units_metric_area(&conversion, argv[i + 1], '\0'));
            printf("\n%lf\n\n", (conversion.val));
            printf("\n%lf\n\n", CONV_M2_TO_IN2(conversion.val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-m2-to-mil2", argv[i]))) {
            CHECK_RET(assign_values_units_metric_area(&conversion, argv[i + 1], '\0'));
            printf("\n%lf\n\n", (conversion.val));
            printf("\n%lf\n\n", CONV_M2_TO_MIL2(conversion.val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-mil-to-mm", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%lf", &val));
            CHECK_LIMITS(val);
            printf("\n%lf\n\n", CONV_MIL_TO_MM(val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-mil-to-ozft2", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%lf", &val));
            CHECK_LIMITS(val);
            printf("\n%lf\n\n", CONV_MIL_TO_OZFT2(val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-mil2-to-cm2", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%lf", &val));
            CHECK_LIMITS(val);
            printf("\n%lf\n\n", CONV_MIL2_TO_CM2(val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-mil2-to-mm2", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%lf", &val));
            CHECK_LIMITS(val);
            printf("\n%lf\n\n", CONV_MIL2_TO_MM2(val));
            printf("Converted using the TWC.\n");

            return 1;
        }
        if (!(strcmp("--convert-ozft2-to-mil", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%lf", &val));
            CHECK_LIMITS(val);
            printf("\n%lf\n\n", CONV_OZFT2_TO_MIL(val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-ozft2-to-mm", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%lf", &val));
            CHECK_LIMITS(val);
            printf("\n%lf\n\n", CONV_OZFT2_TO_MM(val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-ozft2-to-um", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%lf", &val));
            CHECK_LIMITS(val);
            printf("\n%lf\n\n", CONV_OZFT2_TO_UM(val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-F-to-C", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%lf", &val));
            CHECK_LIMITS(val);
            printf("\n%lf\n\n", CONV_FAHR_TO_CELS(val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-C-to-F", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%lf", &val));
            CHECK_LIMITS(val);
            printf("\n%lf\n\n", CONV_CELS_TO_FAHR(val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-WmK-to-BTUhftF", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%lf", &val));
            CHECK_LIMITS(val);
            printf("\n%lf\n\n", CONV_WmK_TO_BTUhftF(val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        if (!(strcmp("--convert-BTUhftF-to-WmK", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%lf", &val));
            CHECK_LIMITS(val);
            printf("\n%lf\n\n", CONV_BTUhftF_TO_WmK(val));
            printf("Converted using the TWC.\n");

            return 1;
        }

        /* Just ignore these two since they are checked before */
        if (!(strcmp("--standard", argv[i]))) {
            i++;
            continue;
        }

        if (!(strcmp("--method", argv[i]))) {
            i++;
            continue;
        }

        /* Error checking */
        fprintf(stderr, "\nUnknown option '%s', exiting.\n", argv[i]);

        return 1;
    }

    /* At least current and copper weight should be entered */
    if ((ip->current.val == 0) || ip->copper_weight.val == 0) {
        fprintf(stderr, "\nPlease input at least the Current and the Copper Weight.\n\n");

        return 1;
    }

    return 0;
}

int assign_values_units_metric(dbl_t* ip_dbl, char* optstring, char SI_derived_units)
{
    char SI_prefix = '\0';
    double val = 0.0f;
    double outval = 0.0f;

    int ret = sscanf(optstring, "%lf%c", &val, &SI_prefix);
    outval = val;

    switch(SI_prefix) {
        case '\0':
            break;
        case 'T':
            val *= 1e12;
            break;
        case 'G':
            val *= 1e9;
            break;
        case 'M':
            val *= 1e6;
            break;
        case 'K':
            val *= 1e3;
            break;
        case 'c':
            val *= 1e-2;
            break;
        case 'm':
            val *= 1e-3;
            break;
        case 'u':
            val *= 1e-6;
            break;
        case 'n':
            val *= 1e-9;
            break;
        case 'p':
            val *= 1e-12;
            break;
        default:
            fprintf(stderr, "Unknown SI prefix '%c'.", SI_prefix);
            return 1;
    }

    CHECK_LIMITS(val);
    
    ip_dbl->units = malloc(3 * sizeof(char));
    switch(ret) {
        case 0:
            fprintf(stderr, "\nIssue with parsing input value '%s'.\n", optstring);
            return 1;
        case 1:
            sprintf(ip_dbl->units, "%c",  SI_derived_units);
            break;
        case 2:
            sprintf(ip_dbl->units, "%c%c", SI_prefix, SI_derived_units);
            break;
        default:
            break;
    }

    ip_dbl->val = val;
    ip_dbl->outval = outval;

    return 0;
}

int assign_values_units_metric_area(dbl_t* ip_dbl, char* optstring, char SI_derived_units)
{
    char SI_prefix = '\0';
    double val = 0.0f;
    double outval = 0.0f;

    sscanf(optstring, "%lf%c", &val, &SI_prefix);
    outval = val;

    switch(SI_prefix) {
        case '\0':
            break;
        case 'T':
            val *= 1e12 * 1e12;
            break;
        case 'G':
            val *= 1e9 * 1e9;
            break;
        case 'M':
            val *= 1e6 * 1e6;
            break;
        case 'K':
            val *= 1e3 * 1e3;
            break;
        case 'c':
            val *= 1e-2 * 1e-2;
            break;
        case 'm':
            val *= 1e-3 * 1e-3;
            break;
        case 'u':
            val *= 1e-6 * 1e-6;
            break;
        case 'n':
            val *= 1e-9 * 1e-9;
            break;
        case 'p':
            val *= 1e-12 * 1e-12;
            break;
        default:
            fprintf(stderr, "Unknown SI prefix '%c'.", SI_prefix);
            return 1;
    }

    CHECK_LIMITS(val);

    sprintf(ip_dbl->units, "%c%c%s", SI_derived_units, SI_prefix, "^2");
    ip_dbl->val = val;
    ip_dbl->outval = outval;

    return 0;
}

int assign_values_units_imperial(dbl_t* ip_dbl, char* optstring, char* units)
{
    double val = 0.0f;
    CHECK_RES(sscanf(optstring, "%lf", &val));
    CHECK_LIMITS(val);
    ip_dbl->outval = val;
    ip_dbl->val = val;
    ip_dbl->units = units;

    return 0;
}

int get_standard_method(int argc, char** restrict argv, ip_t* restrict ip)
{
    const char* standard_arr[] = { "IPC2221", "IPC2152", "afko" }; /* Standard names array */
    const int standard_const[] = { IPC2221, IPC2152, 666 }; /* Number representation of the standards */
    const char method_arr[] = { 'A', 'B' }; /* Method array */
    char strval[10] = { "\0" }; /* Temp value for the string argument */

    /* Get the sizes of the arrays */
    const unsigned char ssize = sizeof(standard_arr) / sizeof(standard_arr[0]);
    const unsigned char msize = sizeof(method_arr) / sizeof(method_arr[0]);

    /* Index where the input was matched to the available standards */
    unsigned char index;

    for (int i = 1; i < argc; i++) {
        if (!(strcmp("--standard", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%s", strval));
            CHECK_RET(check_standard(strval, standard_arr, ssize, &index));
            strcpy(ip->standard.str, strval); 
            ip->standard.num = standard_const[index];
            i++;
            continue;
        }

        if (!(strcmp("--method", argv[i]))) {
            CHECK_RES(sscanf(argv[i + 1], "%s", strval));
            CHECK_RET(check_method(strval[0],  method_arr, msize));
            ip->method = strval[0];
            i++;
            continue;
        }
    }

    /* Sets up the string when not specifying standard */
    if (ip->standard.num == IPC2152 && ip->standard.str[0] == '\0') {
            strcpy(ip->standard.str, "IPC2152"); 
    }

    /* Sets up the string when not specifying method */
    if (ip->standard.num == IPC2152 && ip->method == '\0') {
            ip->method = 'A'; 
    }

    return 0;
}

int check_standard(char* restrict strval, const char** standard_arr, unsigned int size, unsigned char* restrict index)
{
    uint8_t okflag = 0;

    for (int i = 0; i < size; i++) {
        if (!(strcmp(strval, standard_arr[i]))) {
            *index = i;
            okflag = 1;
            break;
        }
    }

    /* In the case where no match is made */
    if (!okflag) {
        fprintf(stderr, "\nUnknown standard (%s) used...\n", strval);

        return 1;
    }

    return 0;
}

int check_method(char chrval, const char* restrict method_arr, unsigned int size)
{
    uint8_t okflag = 0;

    for (int i = 0; i < size; i++) {
        if (chrval == method_arr[i]) {
            okflag = 1;
            break;
        }
    }

    if (!okflag) {
        fprintf(stderr, "\nUnknown method (%c) used...\n", chrval);

        return 1;
    }

    return 0;
}

int set_outu_IPC2221(ip_t* restrict ip, op_t* restrict op)
{
    switch (ip->uflag) {
        case 'm':
            op->extl.cs_area.units = "mm^2";
            op->extl.cs_area.val = CONV_MIL2_TO_MM2(op->extl.cs_area.val);
            op->extl.trace_width.units = "mm";
            op->extl.trace_width.val = CONV_MIL_TO_MM(op->extl.trace_width.val);

            op->intl.cs_area.units = "mm^2";
            op->intl.cs_area.val = CONV_MIL2_TO_MM2(op->intl.cs_area.val);
            op->intl.trace_width.units = "mm";
            op->intl.trace_width.val = CONV_MIL_TO_MM(op->intl.trace_width.val);
            break;
        case 'i':
            op->extl.cs_area.units = "mil^2";
            op->extl.trace_width.units = "mil";
            op->intl.cs_area.units = "mil^2";
            op->intl.trace_width.units = "mil";
            break;
        default:
            fprintf(stderr, "\nShould be impossible to reach this condition...\n");

            return 1;
    }

    return 0;
}

int set_outu_IPC2152(ip_t* restrict ip, op_t* restrict op)
{
    switch (ip->uflag) {
        case 'm':
            op->layer.cs_area.units = "mm^2";
            op->layer.cs_area.val = CONV_MIL2_TO_MM2(op->layer.cs_area.val);
            op->layer.trace_width.units = "mm";
            op->layer.trace_width.val = CONV_MIL_TO_MM(op->layer.trace_width.val);
            op->layer.corr_cs_area.units = "mm^2";
            op->layer.corr_cs_area.val = CONV_MIL2_TO_MM2(op->layer.corr_cs_area.val);
            op->layer.corr_trace_width.units = "mm";
            op->layer.corr_trace_width.val = CONV_MIL_TO_MM(op->layer.corr_trace_width.val);
            break;
        case 'i':
            op->layer.cs_area.units = "mil^2";
            op->layer.trace_width.units = "mil";
            op->layer.corr_cs_area.units = "mil^2";
            op->layer.corr_trace_width.units = "mil";
            break;
        default:
            fprintf(stderr, "\nShould be impossible to reach this condition...\n");

            return 1;
    }

    return 0;
}

void set_defv_IPC2221(ip_t* restrict ip)
{
    ip->current.outval = 0;
    ip->current.val = 0;
    ip->current.units = "\0";

    ip->copper_weight.outval = 0;
    ip->copper_weight.val = 0;
    ip->copper_weight.units = "\0";

    ip->temp_rise.outval = 10;
    ip->temp_rise.val = 10;
    ip->temp_rise.units = "C";

    ip->temp_ambient.outval = 25;
    ip->temp_ambient.val = 25;
    ip->temp_ambient.units = "C";

    ip->trace_length.outval = 0;
    ip->trace_length.val = 0;
    ip->trace_length.units = "\0";

    ip->resistivity.outval = 1.72e-8; // Annealed copper
    ip->resistivity.val = 1.72e-8;
    ip->resistivity.units = "Ohm m";

    ip->a.outval = 0.00393; // Annealed copper
    ip->a.val = 0.00393;
    ip->a.units = "1/C";
}

void set_defv_IPC2152_A(ip_t* restrict ip)
{
    ip->current.outval = 0;
    ip->current.val = 0;
    ip->current.units = "\0";

    ip->copper_weight.outval = 0;
    ip->copper_weight.val = 0;
    ip->copper_weight.units = "\0";

    ip->temp_rise.outval = 10;
    ip->temp_rise.val = 10;
    ip->temp_rise.units = "C";

    ip->trace_length.outval = 0;
    ip->trace_length.val = 0;
    ip->trace_length.units = "\0";

    ip->plane_area.outval = 0;
    ip->plane_area.val = 0;
    ip->plane_area.units = "\0";

    ip->plane_distance.outval = 0;
    ip->plane_distance.val = 0;
    ip->plane_distance.units = "\0";

    ip->pcb_thickness.outval = 1.6;
    ip->pcb_thickness.val = CONV_M_TO_MIL(1.6 * 1e-3);
    ip->pcb_thickness.units = "mm";

    ip->resistivity.outval = 1.72e-8; // Annealed copper
    ip->resistivity.val = 1.72e-8;
    ip->resistivity.units = "Ohm m";

    ip->a.outval = 0.00393;
    ip->a.val = 0.00393;
    ip->a.units = "1/C";

    /* Set modifier defaults */
    ip->cf.copper_weight = 1;
    ip->cf.temp_rise = 1;
    ip->cf.plane_area = 1;
    ip->cf.pcb_thickness = 1;
    ip->cf.plane_distance = 1;
}

void set_defv_IPC2152_B(ip_t* restrict ip)
{
    /* Set input value defaults */
    ip->current.outval = 0;
    ip->current.val = 0;
    ip->current.units = "\0";

    ip->copper_weight.outval = 0;
    ip->copper_weight.val = 0;
    ip->copper_weight.units = "\0";

    ip->temp_rise.outval = 10;
    ip->temp_rise.val = 10;
    ip->temp_rise.units = "C";

    ip->trace_length.outval = 0;
    ip->trace_length.val = 0;
    ip->trace_length.units = "\0";

    ip->plane_distance.outval = 0;
    ip->plane_distance.val = 0;
    ip->plane_distance.units = "\0";

    ip->pcb_thermal_cond.outval = 0.20;
    ip->pcb_thermal_cond.val = CONV_WmK_TO_BTUhftF(0.20);
    ip->pcb_thermal_cond.units = "W/mK";

    ip->pcb_thickness.outval = 1.6;
    ip->pcb_thickness.val = CONV_M_TO_MIL(1.6 * 1e-3);
    ip->pcb_thickness.units = "mm";

    ip->resistivity.outval = 1.72e-8; // Annealed copper
    ip->resistivity.val = 1.72e-8;
    ip->resistivity.units = "Ohm m";

    ip->a.outval = 0.00393;
    ip->a.val = 0.00393;
    ip->a.units = "1/C";

    /* Set modifier defaults */
    ip->cf.copper_weight = 0;
    ip->cf.pcb_thickness = 1;
    ip->cf.plane_distance = 1;
    ip->cf.pcb_thermal_cond = 1;
}

int sel_functions(ip_t* restrict ip)
{
    switch (ip->standard.num) {
        case IPC2221:

            switch (ip->method) {
                default:
                    ip->defv = &set_defv_IPC2221;
                    ip->proc = &calcs_IPC2221;
                    ip->outu = &set_outu_IPC2221;
                    ip->outp = &output_results_IPC2221;
                    break;
            }

            break;
        case IPC2152:

            switch (ip->method) {
                case 'A':
                    ip->defv = &set_defv_IPC2152_B;
                    ip->proc = &calcs_IPC2152_B;
                    ip->outu = &set_outu_IPC2152;
                    ip->outp = &output_results_IPC2152_B;
                    break;
                case 'B':
                    ip->defv = &set_defv_IPC2152_A;
                    ip->proc = &calcs_IPC2152_A;
                    ip->outu = &set_outu_IPC2152;
                    ip->outp = &output_results_IPC2152_A;
                    break;
                default:
                    fprintf(stderr, "\nMethod %c for the IPC-%d doesn't exist.\n", ip->method, ip->standard.num);

                    return 1;
            }

            break;
        default:
            fprintf(stderr, "\nStandard IPC-%d doesn't exist.\n", ip->standard.num);

            return 1;
    }

    return 0;
}

char* get_time()
{
    time_t time_since_epoch = time(NULL);
    struct tm* tm = localtime(&time_since_epoch);
    static char s[13];
    strftime(s, sizeof(s), "%d%m%y%H%M%S", tm);

    return s;
}

void autogen_file_name(char* restrict fname)
{
    strcpy(fname, "twc-output-");
    strcat(fname, get_time());
    strcat(fname, ".txt");
}

void set_output_file(ofile_t* restrict ofile, char* restrict optarg)
{
    // TODO: Make the path, destination, and file name sizes, dynamically change.
    const size_t len = strlen(optarg);

    /* If given a '.' use autogenerate a file name based on the current date/time */
    if (optarg[0] == '.' && len <= 2) {
        autogen_file_name(ofile->fname);
        strcpy(ofile->path, "\0");
        /* If given a path with no name, autogenerate the name at that path */
    } else if ((optarg[len - 1] == '/') || (optarg[len - 1] == '\\')) {
        autogen_file_name(ofile->fname);
        strcpy(ofile->path, optarg);
        /* Last case is a file name */
    } else {
        strcpy(ofile->fname, optarg);
        strcpy(ofile->path, "\0");
    }

    sprintf(ofile->path, "%s%s", ofile->path, ofile->fname);
}

void calcs_IPC2221(ip_t* restrict ip, op_t* restrict op)
{
    op->extl.cs_area.val = pow(ip->current.val / (k_EXT * pow(ip->temp_rise.val, 0.44)), 1 / 0.725);
    calc_width_res_vdrop_ploss(ip, &op->extl);

    op->intl.cs_area.val = pow(ip->current.val / (k_INT * pow(ip->temp_rise.val, 0.44)), 1 / 0.725);
    calc_width_res_vdrop_ploss(ip, &op->intl);
}

void calcs_IPC2152_A(ip_t* restrict ip, op_t* restrict op)
{
    /* Different one on the website, and different one in the website code */
    op->layer.cs_area.val = (110.515 * pow(ip->temp_rise.val, -0.871) + 0.803) * pow(ip->current.val, 0.868 * pow(ip->temp_rise.val, -0.102) + 1.129);
    // op->layer.cs_area.val = (117.555 * pow(ip->temp_rise.val, -0.913) + 1.15) * pow(ip->current.val, 0.84 * pow(ip->temp_rise.val, -0.018) + 1.159); 

    /* Copper weight correction factor */
    if (ip->copper_weight.val == 2) {
        ip->cf.copper_weight = -0.0185 * log(ip->current.val) + 0.9861;
    } else if (ip->copper_weight.val == 3) {
        ip->cf.copper_weight = 1;
    } else {
        ip->cf.copper_weight = -0.0318 * log(ip->current.val) + 0.9128;
    }

    /* PCB thickness correction factor */
    if (ip->pcb_thickness.val != 0) {
        ip->cf.pcb_thickness = 25.959 * pow(ip->pcb_thickness.val, -0.7666);
    }

    /* Plane area correction factor */
    if (ip->plane_area.val >= 40) {
        ip->cf.plane_area = 0.89;
    } else if (ip->plane_area.val >= 20) {
        ip->cf.plane_area = 0.94;
    } else {
        ip->cf.plane_area = 1;
    } // Plane Area in inch^2 but must be >=20 for it to be modified? sus...

    /* Plane distance correction factor */
    if (ip->plane_distance.val > 125) {
        ip->cf.plane_distance = 1;
    } else {
        ip->cf.plane_distance = 0.0031 * ip->plane_distance.val + 0.4054;
    }

    /* Calculate the corrected temperature rise */
    ip->cf.temp_rise = ip->temp_rise.val / (ip->cf.copper_weight * ip->cf.pcb_thickness * ip->cf.plane_distance * ip->cf.plane_area);

    /* Calculate the corrected CS area */
    op->layer.corr_cs_area.val = (110.515 * pow(ip->cf.temp_rise, -0.871) + 0.803) * pow(ip->current.val, 0.868 * pow(ip->cf.temp_rise, -0.102) + 1.129);

    /* Corrected Trace Width */
    op->layer.corr_trace_width.val = 0.7692 * calc_trace_width_mils(ip, op->layer.corr_cs_area.val) * 1.378; // multiply by 1.378 to remove the conversion inside the function

    calc_width_res_vdrop_ploss(ip, &op->layer);

    op->layer.trace_width.val = 0.7692 * calc_trace_width_mils(ip, op->layer.cs_area.val) * 1.378; // overwrites the result from calc_width_res_vdrop_ploss()
}

void calcs_IPC2152_B(ip_t* restrict ip, op_t* restrict op)
{
    op->layer.cs_area.val = pow(ip->current.val / (0.089710902134 * pow(ip->temp_rise.val, 0.39379253898)), 1 / (0.50382053698 * pow(ip->temp_rise.val, 0.038495772461)));

    /* Coefficients array */
    double coeff_arr[6][4] = {
        { 0.98453567795,     -0.22281787548,     0.20061423196,      -0.041541116264 },
        { -0.01657194921,     0.00017520059279, -0.0050615234096,     0.002281483634 },
        { 0.00088711317661,   0.0013631745743,  -0.0002237330971,    -0.00010974218613 },
        { -66729255031e-16,  -0.00014976736827,  58082340133e-15,    -24728159584e-16 },
        { -7.9576264561e-7,   55788354958e-16,  -24912026388e-16,     2.4000295954e-7 },
        { 1.6619678738e-8,   -7.1122635445e-8,   3.3800191741e-8,    -3.9797591878e-9 }
    };

    for (int i = 0; i < 6; i++) {
        for (int c = 0; c < 4; c++) {
            /* Copper weight here must be in oz/ft2 */
            ip->cf.copper_weight += coeff_arr[i][c] * pow(ip->copper_weight.val, c) * pow(ip->current.val, i);
        }
    }

    /* PCB Thickness must be in mil */
    ip->cf.pcb_thickness = 24.929779905 * pow(ip->pcb_thickness.val, -0.75501997929);

    /* Plane Distance must be in mil */
    if (ip->plane_distance.val != 0) {
        ip->cf.plane_distance = 0.0031298662911 * ip->plane_distance.val + 0.40450883823;
    }

    /* PCB Thermal Conductivity must be in BTU/h*ft*F */
    ip->cf.pcb_thermal_cond = -1.4210148167 * ip->pcb_thermal_cond.val + 1.1958174134;

    /* Corrected CS area */
    op->layer.corr_cs_area.val = op->layer.cs_area.val * ip->cf.copper_weight * ip->cf.pcb_thickness * ip->cf.plane_distance * ip->cf.pcb_thermal_cond;

    /* Corrected Trace Width */
    op->layer.corr_trace_width.val = calc_trace_width_mils(ip, op->layer.corr_cs_area.val);

    calc_width_res_vdrop_ploss(ip, &op->layer);
}

void calc_width_res_vdrop_ploss(ip_t* restrict ip, layer_t* restrict layer)
{
    layer->trace_width.val = calc_trace_width_mils(ip, layer->cs_area.val);

    if (ip->trace_length.val > 0) {
        layer->resistance.val = calc_resistance(ip, layer->cs_area.val);
    }

    layer->voltage_drop.val = calc_vdrop(ip, layer->resistance.val);
    layer->power_loss.val = calc_power_loss(ip, layer->voltage_drop.val);
}

double calc_trace_width_mils(ip_t* restrict ip, double cs_area)
{
    return cs_area / CONV_OZFT2_TO_MIL(ip->copper_weight.val);
}

double calc_resistance(ip_t* restrict ip, double cs_area)
{
    return ((ip->trace_length.val * ip->resistivity.val) / (CONV_MIL2_TO_CM2(cs_area))) * (1 + (ip->a.val * ((ip->temp_rise.val + ip->temp_ambient.val) - ip->temp_ambient.val)));
}

double calc_vdrop(ip_t* restrict ip, double resistance)
{
    return ip->current.val * resistance;
}

double calc_power_loss(ip_t* ip, double vdrop)
{
    return ip->current.val * vdrop;
}

int output_results_IPC2221(ip_t* restrict ip, op_t* restrict op, FILE* file)
{
    fprintf(file, ip->note[0] == '\0' ? "\r" : "\nNote:\n%s\n", ip->note);

    fprintf(file,
            "\n"
            "Current:\t\t%lf\t[%s]\n"
            "Copper Weight:\t\t%lf\t[%s]\n"
            "Temperature, Rise:\t%lf\t[%s]\n"
            "Temperature, Ambient:\t%lf\t[%s]\n"
            "Trace Length:\t\t%lf\t[%s]\n",
            ip->current.outval, ip->current.units, ip->copper_weight.outval, ip->copper_weight.units, ip->temp_rise.outval, ip->temp_rise.units, ip->temp_ambient.val, ip->temp_ambient.units, ip->trace_length.outval, ip->trace_length.units);

    fprintf(file,
            "\n\n"
            "        External Layers\n"
            "Area: \t\t\t%lf\t[%s]\n"
            "Width:\t\t\t%lf\t[%s]\n"
            , op->extl.cs_area.val, op->extl.cs_area.units, op->extl.trace_width.val, op->extl.trace_width.units);

    fprintf(file,
            ip->trace_length.val > 0 ?
            "Resistance:\t\t%lf\t[Ohm]\n"
            "Voltage Drop:\t\t%lf\t[V]\n"
            "Power Loss:\t\t%lf\t[W]\n" : "\r",
            op->extl.resistance.val, op->extl.voltage_drop.val, op->extl.power_loss.val);

    fprintf(file, "\n\n");

    fprintf(file,
            "        Internal Layers\n"
            "Area: \t\t\t%lf\t[%s]\n"
            "Width:\t\t\t%lf\t[%s]\n"
            , op->intl.cs_area.val, op->intl.cs_area.units, op->intl.trace_width.val, op->intl.trace_width.units);

    fprintf(file,
            ip->trace_length.val > 0 ?
            "Resistance:\t\t%lf\t[Ohm]\n"
            "Voltage Drop:\t\t%lf\t[V]\n"
            "Power Loss:\t\t%lf\t[W]\n" : "\r",
            op->intl.resistance.val, op->intl.voltage_drop.val, op->intl.power_loss.val);

    fprintf(file, "\n");

    fprintf(file,
            "\n- Values of k used in calculating the cs_area:\n\n"
            "\tk = %.7lf (Internal layers)\n"
            "\tk = %.7lf (External layers)\n",
            k_INT, k_EXT);

    fprintf(file, ip->trace_length.val == 0 ?
            "\n- Use trace length with '-l' to get voltage, resistance and power calculations.\n" :
            "\n- Constants used for the P/I/V calculations were,\n\n"
            "\ta = %.7lf\t[%s] (Temperature Coefficient)\n"
            "%srho = %.12lf\t[%s] (Resistivity)\n",
            ip->a.outval, ip->a.units, " ", ip->resistivity.outval, ip->resistivity.units);

    fprintf(file,
            "\n- Calculations limitations are listed below, with inputs outside these limitations being more error prone,\n"
            "\t+ Currents up to 35 A external and 17.5 A internal. \n"
            "\t+ Temperature rises from 10 C to 100 C.\n"
            "\t+ Trace widths between 0 and 10.16mm.\n"
            "\t+ Copper weights between 0.5 and 3 oz/ft^2.\n"
            "\t+ No vias along the length of the trace.\n");

    fprintf(file,
            "\n- Constants and method used were derived from http://circuitcalculator.com/wordpress/2006/03/12/pcb-via-calculator/.\n");

    fprintf(file,
            "\n- TWC used the %s standard.\n", ip->standard.str);

    fprintf(file, DISCLAIMER_STR);

    return EXIT_SUCCESS;
}

int output_results_IPC2152_A(ip_t* restrict ip, op_t* restrict op, FILE* file)
{
    fprintf(file, ip->note[0] == '\0' ? "\r" : "\nNote:\n%s\n", ip->note);

    fprintf(file,
            "\n"
            "Current:\t\t%lf\t[%s]\n"
            "Copper Weight:\t\t%lf\t[%s]\n"
            "Temperature, Rise:\t%lf\t[%s]\n"
            "Trace Length:\t\t%lf\t[%s]\n"
            "PCB Thickness:\t\t%lf\t[%s]\n"
            "Plane Distance:\t\t%lf\t[%s]\n"
            "Plane Area:\t\t%lf\t[%s]\n",
            ip->current.outval, ip->current.units, ip->copper_weight.outval, ip->copper_weight.units, ip->temp_rise.outval, ip->temp_rise.units, ip->trace_length.outval, ip->trace_length.units, ip->pcb_thickness.outval, ip->pcb_thickness.units, ip->plane_distance.outval, ip->plane_distance.units, ip->plane_area.outval, ip->plane_area.units);

    fprintf(file,
            "\n"
            "Area: \t\t\t%lf\t[%s]\n"
            "Corrected Area: \t%lf\t[%s]\n"
            "Width:\t\t\t%lf\t[%s]\n"
            "Corrected Width: \t%lf\t[%s]\n",
            op->layer.cs_area.val, op->layer.cs_area.units, op->layer.corr_cs_area.val, op->layer.corr_cs_area.units, op->layer.trace_width.val, op->layer.trace_width.units, op->layer.corr_trace_width.val, op->layer.corr_trace_width.units);

    fprintf(file,
            ip->trace_length.val > 0 ?
            "Resistance:\t\t%lf\t[Ohm]\n"
            "Voltage Drop:\t\t%lf\t[V]\n"
            "Power Loss:\t\t%lf\t[W]\n" : "\r",
            op->layer.resistance.val, op->layer.voltage_drop.val, op->layer.power_loss.val);

    fprintf(file,
            "\n"
            "Copper Weight CF:\t%lf\t[units]\n"
            "PCB Thickness CF:\t%lf\t[units]\n"
            "Plane Area CF:\t\t%lf\t[units]\n"
            "Plane Distance CF:\t%lf\t[units]\n"
            "Temperature Rise CF:\t%lf\t[units]\n",
            ip->cf.copper_weight, ip->cf.pcb_thickness, ip->cf.plane_area, ip->cf.plane_distance, ip->cf.temp_rise);

    fprintf(file, ip->trace_length.val == 0 ?
            "\n- Use trace length with '-l' to get voltage, resistance and power calculations.\n" :
            "\n- Constants used for the P/I/V calculations were,\n\n"
            "\ta = %.7lf\t[%s] (Temperature Coefficient)\n"
            "%srho = %.12lf\t[%s] (Resistivity)\n",
            ip->a.outval, ip->a.units, " ", ip->resistivity.outval, ip->resistivity.units);

    fprintf(file,
            "\n- Constants and method used were derived from https://www.smps.us/pcb-calculator.html.\n");

    fprintf(file,
            "\n- TWC used the %s standard, Method %c.\n", ip->standard.str, ip->method);

    fprintf(file, DISCLAIMER_STR);

    return EXIT_SUCCESS;
}

int output_results_IPC2152_B(ip_t* restrict ip, op_t* restrict op, FILE* file)
{
    fprintf(file, ip->note[0] == '\0' ? "\r" : "\nNote:\n%s\n", ip->note);

    fprintf(file,
            "\n"
            "Current:\t\t%lf\t[%s]\n"
            "Copper Weight:\t\t%lf\t[%s]\n"
            "Temperature, Rise:\t%lf\t[%s]\n"
            "Trace Length:\t\t%lf\t[%s]\n"
            "PCB Thickness:\t\t%lf\t[%s]\n"
            "Plane Distance:\t\t%lf\t[%s]\n"
            "PCB Thermal Cond.:\t%lf\t[%s]\n",
            ip->current.outval, ip->current.units, ip->copper_weight.outval, ip->copper_weight.units, ip->temp_rise.outval, ip->temp_rise.units, ip->trace_length.outval, ip->trace_length.units, ip->pcb_thickness.outval, ip->pcb_thickness.units, ip->plane_distance.outval, ip->plane_distance.units, ip->pcb_thermal_cond.outval, ip->pcb_thermal_cond.units);

    fprintf(file,
            "\n"
            "Area: \t\t\t%lf\t[%s]\n"
            "Corrected Area: \t%lf\t[%s]\n"
            "Width:\t\t\t%lf\t[%s]\n"
            "Corrected Width: \t%lf\t[%s]\n",
            op->layer.cs_area.val, op->layer.cs_area.units, op->layer.corr_cs_area.val, op->layer.corr_cs_area.units, op->layer.trace_width.val, op->layer.trace_width.units, op->layer.corr_trace_width.val, op->layer.corr_trace_width.units);

    fprintf(file,
            ip->trace_length.val > 0 ?
            "Resistance:\t\t%lf\t[Ohm]\n"
            "Voltage Drop:\t\t%lf\t[V]\n"
            "Power Loss:\t\t%lf\t[W]\n" : "\r",
            op->layer.resistance.val, op->layer.voltage_drop.val, op->layer.power_loss.val);

    fprintf(file,
            "\n"
            "Copper Weight CF:\t%lf\t[units]\n"
            "PCB Thickness CF:\t%lf\t[units]\n"
            "PCB Thermal Cond. CF:\t%lf\t[units]\n"
            "Plane Distance CF:\t%lf\t[units]\n",
            ip->cf.copper_weight, ip->cf.pcb_thickness, ip->cf.pcb_thermal_cond, ip->cf.plane_distance);

    fprintf(file, ip->trace_length.val == 0 ?
            "\n- Use trace length with '-l' to get voltage, resistance and power calculations.\n" :
            "\n- Constants used for the P/I/V calculations were,\n\n"
            "\ta = %.7lf\t[%s] (Temperature Coefficient)\n"
            "%srho = %.12lf\t[%s] (Resistivity)\n",
            ip->a.outval, ip->a.units, " ", ip->resistivity.outval, ip->resistivity.units);

    fprintf(file,
            "\n- Constants and method used were derived from https://ninjacalc.mbedded.ninja/calculators/electronics/pcb-design/track-current-ipc2152.\n");

    fprintf(file,
            "\n- TWC used the %s standard, Method %c.\n", ip->standard.str, ip->method);

    fprintf(file, DISCLAIMER_STR);

    return EXIT_SUCCESS;
}

// TODO: Create help for each option?
int output_help()
{
    printf("\nHelp for the Trace Width Calculator (TWC). Specify units with the long options, listed below the short options."
            "\n\t-n,\t\t--note \"<Text>\"\t\t\t\t= Add a note to the start of the output. Make sure to put the note between quotes.\n"
            "\n\t-c,\t\t--current <Current [A]>\t\t\t\t= Input the trace current in Amps.\n"
            "\n\t-w,\t--copper-weight <Copper Weight [m]>\t= Input the copper weight in meters. Use the other options below for imperial units.\n"
            "\t-w-mil,\t\t--copper-weight-mil\n"
            "\t-w-oz,\t\t--copper-weight-oz\n"
            "\n\t-r[-C],\t\t--temperature-rise <Temperature Rise [C]>\t= Input the maximum allowed temperature rise in C.\n"
            "\t-r-F,\t\t--temperature-rise-F\n"
            "\n\t-a[-C],\t\t--temperature-ambient <Ambient Temperature [C]>\t= Input the ambient temperature of the trace in C.\n"
            "\t-r-F,\t\t--temperature-ambient-F\n"
            "\n\t-l,\t--trace--length <Trace Length [m]>\t\t= Input the trace length in centimeters. Use the other options below for imperial units.\n"
            "\t-l,\t\t--trace--length-mm\n"
            "\t-l-mil,\t\t--trace--length-mil\n"
            "\t-l-in,\t\t--trace--length-inches\n"
            "\n\t-t,\t--pcb-thickness <Thickness [m]>\t\t= Input the PCB thickness in meters. Use the other options below for imperial units.\n"
            "\t-t-mil,\t\t--pcb-thickness-mil\n"
            "\t-t-in,\t\t--pcb-thickness-in\n"
            "\n\t-e,\t\t--pcb-thermal-conductivity <Therm. Con. [W/mK]>\t= Input the PCB thermal conductivity in Watts per meter Kelvin.\n"
            "\n\t-p,\t--plane-cs-area <Plane Area [m^2]>\t\t= Input the plane cross sectional area in meters squared. Use the other options below for imperial units.\n"
            "\t-p-in2,\t\t--plane-cs-area-in2\n"
            "\t-p-mil2,\t\t--plane-cs-area-mil2\n"
            "\n\t-d,\t--plane-distance <Plane Distance [m]>\t\t= Input the plane distance in meters. Use the other options below for imperial units.\n"
            "\t-d-mil,\t\t--plane-distance-mil\n"
            "\t-d-in,\t\t--plane-distance-inches\n"
            "\n\t\t--resistivity <Resistivity [Ohm m]>\t\t\t= Input the resistivity in Ohm meters.\n"
            "\n\t\t--temperature-coefficient <Temp. Coefficient [1/C]>\t= Input the temperature coefficient.\n"
            "\n\t-o,\t\t--output <File Name>\t\t\t\t= Write the name of the outputted file. Use '.txt' to create a text file. Use a single '.' to auto-generate\n\t\t\t\t\t\t\t\t\t  the name based on date/time. Can also write the full path to the file, e.g. 'C:/Users/user/output.txt'\n\t\t\t\t\t\t\t\t\t  or stop at 'C:/Users/user/' to use the auto-generated file name.\n"
            "\n\t-m, \t\t--metric\t\t\t\t\t= Make the output units be metric.\n"
            "\n\t-i, \t\t--imperial\t\t\t\t\t= Make the output units be imperial. Default behaviour, therefore just implemented for completion.\n"
            "\n\n\t\t\tCONVERSIONS\n"
            "\nUsage example 'twc --conversion-m-to-ozft2 <Value>'. Can use an SI prefix in the input when converting from meters.\n"
            "\n\t--convert-m-to-ozft2\t= From meters to ox per foot sq."
            "\n\t--convert-m-to-mil\t= From meters to mil."
            "\n\t--convert-m2-to-in2\t= From meters sq. to inches sq."
            "\n\t--convert-m2-to-mil2\t= From meters sq. to mil sq."
            "\n\t--convert-mil-to-mm\t= From mils to milimeters."
            "\n\t--convert-mil-to-ozft2\t= From mils to ounce per foot sq."
            "\n\t--convert-mil2-to-cm2\t= From mils sq. to centimeters sq."
            "\n\t--convert-mil2-to-mm2\t= From mils sq. to milimeters sq."
            "\n\t--convert-ozft2-to-mil\t= From ounce per foot sq. to mils."
            "\n\t--convert-ozft2-to-mm\t= From ounce per foot sq. to milimeters."
            "\n\t--convert-ozft2-to-um\t= From ounce per foot sq. to micrometers."
            "\n\t--convert-F-to-C\t\t= From Fahrenheit to Celsius."
            "\n\t--convert-C-to-F\t\t= From Celsius to Fahrenheit."
            "\n\t--convert-WmK-to-BTUhftF\t= From Watts per mili Kelvin to BTU/h*ft*F."
            "\n\t--convert-BTUhftF-to-WmK\t= From BTU/h*ft*F to Watts per mili Kelvin."
            "\n\n");

    return EXIT_SUCCESS;
}
