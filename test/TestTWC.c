#include "unity/unity.h"
#include "../twc.h"
#include "unity/unity_internals.h"
#include <stdio.h>
#include <string.h>

void setUp()
{}

void tearDown() 
{
    fflush(stdout);
}

void test_output_help()
{
    TEST_ASSERT_EQUAL_INT(0, output_help());
}

void test_output_results_IPC2221()
{
    ip_t ip = {
        .standard.str = "IPC2221",
        .method = 'A',
        .current = {
            .val = 1,
            .units = "test"
        },
        .copper_weight = {
            .val = 1,
            .units = "test"
        },
        .temp_rise = {
            .val = 1,
            .units = "test"
        },
        .temp_ambient = {
            .val = 1,
            .units = "test"
        },
        .trace_length = {
            .val = 1,
            .units = "test"
        },
        .resistivity.val = 1,
        .a.val = 1,
    };

    op_t op = {
        .extl = {
            .cs_area = {
                .val = 1,
                .units = "test"
            },
            .trace_width = {
                .val = 1,
                .units = "test"
            },
            .resistance = {
                .val = 1,
                .units = "test"
            },
            .voltage_drop = {
                .val = 1,
                .units = "test"
            },
            .power_loss = {
                .val = 1,
                .units = "test"
            },
        },
        .intl = {
            .cs_area = {
                .val = 1,
                .units = "test"
            },
            .trace_width = {
                .val = 1,
                .units = "test"
            },
            .resistance = {
                .val = 1,
                .units = "test"
            },
            .voltage_drop = {
                .val = 1,
                .units = "test"
            },
            .power_loss = {
                .val = 1,
                .units = "test"
            },
        }
    };

    TEST_ASSERT_EQUAL_INT(0, output_results_IPC2221(&ip, &op, stdout));
}

void test_output_results_IPC2152_C()
{
    ip_t ip = {
        .standard.str = "IPC2152",
        .method = 'C',
        .current = {
            .val = 1,
            .units = "test"
        },
        .copper_weight = {
            .val = 1,
            .units = "test"
        },
        .temp_rise = {
            .val = 1,
            .units = "test"
        },
        .temp_ambient = {
            .val = 1,
            .units = "test"
        },
        .trace_length = {
            .val = 1,
            .units = "test"
        },
        .resistivity.val = 1,
        .a.val = 1,
    };

    op_t op = {
        .extl = {
            .cs_area = {
                .val = 1,
                .units = "test"
            },
            .trace_width = {
                .val = 1,
                .units = "test"
            },
            .resistance = {
                .val = 1,
                .units = "test"
            },
            .voltage_drop = {
                .val = 1,
                .units = "test"
            },
            .power_loss = {
                .val = 1,
                .units = "test"
            },
        },
        .intl = {
            .cs_area = {
                .val = 1,
                .units = "test"
            },
            .trace_width = {
                .val = 1,
                .units = "test"
            },
            .resistance = {
                .val = 1,
                .units = "test"
            },
            .voltage_drop = {
                .val = 1,
                .units = "test"
            },
            .power_loss = {
                .val = 1,
                .units = "test"
            },
        }
    };

    TEST_ASSERT_EQUAL_INT(0, output_results_IPC2152_C(&ip, &op, stdout));
}

void test_output_results_IPC2152_B()
{
    ip_t ip = {
        .standard.str = "IPC2152",
        .method = 'B',
        .current = {
            .val = 1,
            .units = "test"
        },
        .copper_weight = {
            .val = 1,
            .units = "test"
        },
        .temp_rise = {
            .val = 1,
            .units = "test"
        },
        .trace_length = {
            .val = 1,
            .units = "test"
        },
        .pcb_thickness = {
            .val = 1,
            .units = "test"
        },
        .plane_distance = {
            .val = 1,
            .units = "test"
        },
        .pcb_thermal_cond = {
            .val = 1,
            .units = "test"
        },
        .cf = {
            .copper_weight = 1,
            .pcb_thickness = 1,
            .pcb_thermal_cond = 1,
            .plane_distance = 1,
        },
        .resistivity.val = 1,
        .a.val = 1,
    };

    op_t op = {
        .layer = {
            .cs_area = {
                .val = 1,
                .units = "test"
            },
            .corr_cs_area = {
                .val = 1,
                .units = "test"
            },
            .trace_width = {
                .val = 1,
                .units = "test"
            },
            .corr_trace_width = {
                .val = 1,
                .units = "test"
            },
            .resistance = {
                .val = 1,
                .units = "test"
            },
            .voltage_drop = {
                .val = 1,
                .units = "test"
            },
            .power_loss = {
                .val = 1,
                .units = "test"
            },
        },
    };

    TEST_ASSERT_EQUAL_INT(0, output_results_IPC2152_B(&ip, &op, stdout));
}

void test_output_results_IPC2152_A()
{
    ip_t ip = {
        .standard.str = "IPC2152",
        .method = 'A',
        .current = {
            .outval = 1,
            .units = "test"
        },
        .copper_weight = {
            .outval = 1,
            .units = "test"
        },
        .temp_rise = {
            .outval = 1,
            .units = "test"
        },
        .trace_length = {
            .outval = 1,
            .units = "test"
        },
        .pcb_thickness = {
            .outval = 1,
            .units = "test"
        },
        .plane_distance = {
            .outval = 1,
            .units = "test"
        },
        .plane_area= {
            .outval = 1,
            .units = "test"
        },
        .cf = {
            .copper_weight = 1,
            .pcb_thickness = 1,
            .plane_area = 1,
            .plane_distance = 1,
            .temp_rise = 1,
        },
        .resistivity.val = 1,
        .a.val = 1,
    };

    op_t op = {
        .layer = {
            .cs_area = {
                .val = 1,
                .units = "test"
            },
            .corr_cs_area = {
                .val = 1,
                .units = "test"
            },
            .trace_width = {
                .val = 1,
                .units = "test"
            },
            .corr_trace_width = {
                .val = 1,
                .units = "test"
            },
            .resistance = {
                .val = 1,
                .units = "test"
            },
            .voltage_drop = {
                .val = 1,
                .units = "test"
            },
            .power_loss = {
                .val = 1,
                .units = "test"
            },
        },
    };

    TEST_ASSERT_EQUAL_INT(0, output_results_IPC2152_A(&ip, &op, stdout));
}

void test_vdrop()
{
    ip_t ip = {.current.val = 1.0};
    double resistance = 1.0;
    TEST_ASSERT_EQUAL_DOUBLE(1.0, calc_vdrop(&ip, resistance));
}

void test_pow_loss()
{
    ip_t ip = {.current.val = 1.0};
    double resistance = 1.0;
    double vdrop = calc_vdrop(&ip, resistance);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, calc_power_loss(&ip, vdrop));
}

void test_resistance()
{
    ip_t ip = {
        .temp_rise.val = 1,
        .temp_ambient.val = 25,
        .trace_length.val = 0.01,
        .resistivity.val = 1.72e-8,
        .a.val = 0.00393,
    };
    double area = 1;
    TEST_ASSERT_DOUBLE_WITHIN(1e-9, 0.272886974, calc_resistance(&ip, area));
}

void test_trace_width_mils()
{
    ip_t ip = {
        .copper_weight.val = 1.0,
    };
    double area = 1;
    TEST_ASSERT_DOUBLE_WITHIN(1e-9, 0.72568940493468795355587808417997, calc_trace_width_mils(&ip, area));
}

void test_resistance_vdrop_ploss()
{
    ip_t ip = {
        .copper_weight.val = 1.0,
        .current.val = 1.0,
        .temp_rise.val = 1,
        .temp_ambient.val = 25,
        .trace_length.val = 0.001,
        .resistivity.val = 1.72e-8,
        .a.val = 0.00393,
    };
    layer_t layer = {
        .cs_area.val = 1,
    };
    calc_resistance_vdrop_ploss(&ip, &layer);

    TEST_ASSERT_DOUBLE_WITHIN(1e-10, 0.0272886974, layer.resistance.val);
    TEST_ASSERT_DOUBLE_WITHIN(1e-10, 0.0272886974, layer.voltage_drop.val);
    TEST_ASSERT_DOUBLE_WITHIN(1e-10, 0.0272886974, layer.power_loss.val);
}

void test_calcs_IPC2152_C()
{
    ip_t ip = {
        .current = {
            .val = 1,
            .units = "test"
        },
        .copper_weight = {
            .val = 1,
            .units = "test"
        },
        .temp_rise = {
            .val = 1,
            .units = "test"
        },
        .temp_ambient = {
            .val = 1,
            .units = "test"
        },
        .trace_length = {
            .val = 1,
            .units = "test"
        },
        .resistivity.val = 1,
        .a.val = 1,
    };

    op_t op;

    calcs_IPC2152_C(&ip, &op);

    TEST_ASSERT_DOUBLE_WITHIN(1e-2, 80.84, op.extl.trace_width.val);
    TEST_ASSERT_DOUBLE_WITHIN(1e-2, 88.36, op.intl.trace_width.val);
}

void test_calcs_IPC2152_B()
{
    ip_t ip = {
        .current = {
            .val = 1,
            .units = "test"
        },
        .copper_weight = {
            .val = 1,
            .units = "test"
        },
        .temp_rise = {
            .val = 1,
            .units = "test"
        },
        .trace_length = {
            .val = 1,
            .units = "test"
        },
        .pcb_thickness = {
            .val = 1,
            .units = "test"
        },
        .plane_distance = {
            .val = 1,
            .units = "test"
        },
        .plane_area= {
            .val = 1,
            .units = "test"
        },
        .cf = {
            .copper_weight = 1,
            .pcb_thickness = 1,
            .plane_area = 1,
            .plane_distance = 1,
            .temp_rise = 1,
        },
        .resistivity.val = 1,
        .a.val = 1,
    };

    op_t op;

    calcs_IPC2152_B(&ip, &op);

    /* Expected values are from the website of which the method was extracted from */
    TEST_ASSERT_DOUBLE_WITHIN(1e-2, 0.91, ip.cf.copper_weight);
    TEST_ASSERT_DOUBLE_WITHIN(1e-2, 25.96, ip.cf.pcb_thickness);
    TEST_ASSERT_DOUBLE_WITHIN(1e-2, 0.41, ip.cf.plane_distance);
    TEST_ASSERT_DOUBLE_WITHIN(1, 1, ip.cf.plane_area);
    TEST_ASSERT_DOUBLE_WITHIN(1e-2, 0.1, ip.cf.temp_rise);
    TEST_ASSERT_DOUBLE_WITHIN(1e-1, 111.3, op.layer.cs_area.val);
    TEST_ASSERT_DOUBLE_WITHIN(1, 799, op.layer.corr_cs_area.val);
    TEST_ASSERT_DOUBLE_WITHIN(1e-1, 85.6, op.layer.trace_width.val);
    TEST_ASSERT_DOUBLE_WITHIN(1e-1, 614.6, op.layer.corr_trace_width.val);

    /* Only checking the trace width for these other values */
    ip.copper_weight.val = 2;
    ip.plane_area.val = 40;
    ip.plane_distance.val = 126;
    calcs_IPC2152_B(&ip, &op);
    TEST_ASSERT_DOUBLE_WITHIN(1e-1, 647.3, op.layer.corr_trace_width.val);

    ip.copper_weight.val = 3;
    ip.plane_area.val = 20;
    ip.plane_distance.val = 1;
    calcs_IPC2152_B(&ip, &op);
    TEST_ASSERT_DOUBLE_WITHIN(1e-1, 210.2, op.layer.corr_trace_width.val);
}

void test_calcs_IPC2152_A()
{
    ip_t ip = {
        .current = {
            .val = 1,
            .units = "test"
        },
        .copper_weight = {
            .val = 1,
            .units = "test"
        },
        .temp_rise = {
            .val = 1,
            .units = "test"
        },
        .trace_length = {
            .val = 1,
            .units = "test"
        },
        .pcb_thickness = {
            .val = 1,
            .units = "test"
        },
        .plane_distance = {
            .val = 1,
            .units = "test"
        },
        .pcb_thermal_cond = {
            .val = CONV_WmK_TO_BTUhftF(1),
            .units = "test"
        },
        .cf = {
            .copper_weight = 0,
            .pcb_thickness = 1,
            .pcb_thermal_cond = 1,
            .plane_distance = 1,
        },
        .resistivity.val = 1,
        .a.val = 1,
    };

    op_t op;

    calcs_IPC2152_A(&ip, &op);

    /* Expected values are from the website of which the method was extracted from */
    TEST_ASSERT_DOUBLE_WITHIN(1e-2, CONV_M2_TO_MIL2(0.00007729), op.layer.cs_area.val);
    TEST_ASSERT_DOUBLE_WITHIN(1e-3, 0.903, ip.cf.copper_weight);
    TEST_ASSERT_DOUBLE_WITHIN(1e-1, 24.9, ip.cf.pcb_thickness);
    TEST_ASSERT_DOUBLE_WITHIN(1e-3, 0.408, ip.cf.plane_distance);
    TEST_ASSERT_DOUBLE_WITHIN(1e-2, 0.374, ip.cf.pcb_thermal_cond);
    TEST_ASSERT_DOUBLE_WITHIN(1, CONV_M2_TO_MIL2(0.000266), op.layer.corr_cs_area.val);
    TEST_ASSERT_DOUBLE_WITHIN(1, 299, op.layer.corr_trace_width.val);
}

void test_calcs_IPC2221()
{
    ip_t ip = {
        .current = {
            .val = 1,
            .units = "test"
        },
        .copper_weight = {
            .val = 1,
            .units = "test"
        },
        .temp_rise = {
            .val = 1,
            .units = "test"
        },
        .temp_ambient = {
            .val = 1,
            .units = "test"
        },
        .trace_length = {
            .val = 1,
            .units = "test"
        },
        .resistivity.val = 1,
        .a.val = 1,
    };

    op_t op;

    calcs_IPC2221(&ip, &op);

    TEST_ASSERT_DOUBLE_WITHIN(1e-1, 47.8, op.extl.trace_width.val);
    TEST_ASSERT_DOUBLE_WITHIN(1, 124, op.intl.trace_width.val);
}

void test_set_output_file()
{
    char* optarg[3] = {".", "C:/", "file.txt"};

    ofile_t ofile1;
    set_output_file(&ofile1, optarg[0]);
    TEST_ASSERT_EQUAL_INT(27, strlen(ofile1.path));

    ofile_t ofile2;
    set_output_file(&ofile2, optarg[1]);
    TEST_ASSERT_EQUAL_INT(30, strlen(ofile2.path));

    ofile_t ofile3;
    set_output_file(&ofile3, optarg[2]);
    TEST_ASSERT_EQUAL_INT(8, strlen(ofile3.path));
}

void test_autogen_file_name()
{
    char* fname = malloc(sizeof(char) * OUT_FILE_LEN);
    autogen_file_name(fname);
    TEST_ASSERT_EQUAL_INT(27, strlen(fname));
    free(fname);
}

void test_get_time()
{
    char* time = get_time();
    TEST_ASSERT_EQUAL_INT(12, strlen(time));
}

void test_sel_functions()
{
    ip_t ip;

    ip.standard.num = IPC2221;
    memcpy(ip.standard.str, "IPC2221", 8);
    ip.method = 'A';
    TEST_ASSERT_EQUAL_INT(0, sel_functions(&ip));

    ip.standard.num = IPC2152;
    memcpy(ip.standard.str, "IPC2152", 8);
    ip.method = 'A';
    TEST_ASSERT_EQUAL_INT(0, sel_functions(&ip));

    ip.standard.num = IPC2152;
    memcpy(ip.standard.str, "IPC2152", 8); 
    ip.method = 'B';
    TEST_ASSERT_EQUAL_INT(0, sel_functions(&ip));

    ip.standard.num = IPC2152;
    memcpy(ip.standard.str, "IPC2152", 8); 
    ip.method = 'C';
    TEST_ASSERT_EQUAL_INT(0, sel_functions(&ip));

    ip.standard.num = 12345;
    TEST_ASSERT_EQUAL_INT(1, sel_functions(&ip));

    ip.standard.num = IPC2152;
    ip.method = 'F';
    TEST_ASSERT_EQUAL_INT(1, sel_functions(&ip));

    ip.standard.num = IPC2221;
    ip.method = 'F';
    TEST_ASSERT_EQUAL_INT(0, sel_functions(&ip));
}

void test_set_defv()
{
    /* I don't have the energy to test whether every single value was assigned and checking if a 0/1 was returned is redundant...so these are just called for completion's sake */
    ip_t ip;

    set_universal_defaults(&ip);
    set_defv_IPC2221(&ip);
    set_defv_IPC2152_A(&ip);
    set_defv_IPC2152_B(&ip);
    set_defv_IPC2152_C(&ip);
}

void test_set_outu()
{
    ip_t ip;
    op_t op;

    ip.uflag = 'm';
    TEST_ASSERT_EQUAL_INT(0, set_outu_IPC2152_A(&ip, &op));
    TEST_ASSERT_EQUAL_INT(0, set_outu_IPC2152_B(&ip, &op));
    TEST_ASSERT_EQUAL_INT(0, set_outu_IPC2152_C(&ip, &op));
    TEST_ASSERT_EQUAL_INT(0, set_outu_IPC2221(&ip, &op));

    ip.uflag = 'i';
    TEST_ASSERT_EQUAL_INT(0, set_outu_IPC2152_A(&ip, &op));
    TEST_ASSERT_EQUAL_INT(0, set_outu_IPC2152_B(&ip, &op));
    TEST_ASSERT_EQUAL_INT(0, set_outu_IPC2152_C(&ip, &op));
    TEST_ASSERT_EQUAL_INT(0, set_outu_IPC2221(&ip, &op));

    ip.uflag = 'g';
    TEST_ASSERT_EQUAL_INT(1, set_outu_IPC2152_A(&ip, &op));
    TEST_ASSERT_EQUAL_INT(1, set_outu_IPC2152_B(&ip, &op));
    TEST_ASSERT_EQUAL_INT(1, set_outu_IPC2152_C(&ip, &op));
    TEST_ASSERT_EQUAL_INT(1, set_outu_IPC2221(&ip, &op));
}

void test_check_method()
{
    char chrval = 'a';
    const char* method_arr = "ab";
    unsigned int size = 2;

    TEST_ASSERT_EQUAL_INT(0, check_method(chrval, method_arr, size));

    chrval = 'c';
    TEST_ASSERT_EQUAL_INT(1, check_method(chrval, method_arr, size));
}

void test_check_standard()
{

    char* strval = "test";
    const char* standard_arr[] = {"hey", "test"};
    unsigned int size = 2;
    unsigned char index;

    TEST_ASSERT_EQUAL_INT(0, check_standard(strval, standard_arr, size, &index));

    strval = "hello";
    TEST_ASSERT_EQUAL_INT(1, check_standard(strval, standard_arr, size, &index));
}

void test_get_standard_method()
{
    int argc = 9;
    char* argv[] = {"first", "-c", "1", "-w", "2", "--standard", "IPC2152", "--method", "B"};
    ip_t ip;

    TEST_ASSERT_EQUAL_INT(0, get_standard_method(argc, argv, &ip));
}

void split(char* cmd, char** argv, int* argc)
{
    char* token = strtok(cmd," "); 
    *argc = 0;
    while(token != NULL) {
        argv[*argc] = token; 
        token = strtok(NULL," "); 
        *argc = *argc + 1;
    }
}

void reset(char** argv, ip_t* ip, int size)
{
    for(int i = 0; i < size; i++) {
        argv[i] = "\0";
    }
    ip_t x = { 0 };
    *ip = x;
}

void test_get_options()
{
    int argc;
    char* argv[30];
    ip_t ip = {0};

    argc = 1;
    argv[0] = "first";
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));

    argc = 2;
    argv[1] = "-h";
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));

    argc = 2;
    argv[1] = "--version";
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));

    argc = 2;
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd1[] = "first -c 1 -w 1 -r 10 -a 25 -l 1 -t 1.6 -e 1 -p 1 -d 1 -i -m -n 'hey'";
    split(cmd1, argv, &argc);
    TEST_ASSERT_EQUAL_INT(0, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd2[] = "first -w 1 --current 1";
    split(cmd2, argv, &argc);
    TEST_ASSERT_EQUAL_INT(0, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd3[] = "first -c 1 --copper-weight 1 -w-oz 1 --copper-weight-oz 1 -w-mil 1 --copper-weight-mil 1";
    split(cmd3, argv, &argc);
    TEST_ASSERT_EQUAL_INT(0, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd4[] = "first -c 1 -w 1 --temperature-rise 1 --temperature-rise-F 1 --temperature-ambient 1 --temperature-ambient-F 1";
    split(cmd4, argv, &argc);
    TEST_ASSERT_EQUAL_INT(0, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd5[] = "first -c 1 -w 1 -l 1 --trace-length 1 -l-mil 1 --trace-length-mil 1 -l-in 1 --trace-length-in 1";
    split(cmd5, argv, &argc);
    TEST_ASSERT_EQUAL_INT(0, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd6[] = "first -c 1 -w 1 -t 1 --pcb-thickness 1 -t-mil 1 --pcb-thickness-mil 1 -t-in 1 --pcb-thickness-in 1";
    split(cmd6, argv, &argc);
    TEST_ASSERT_EQUAL_INT(0, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd7[] = "first -c 1 -w 1 --pcb-thermal-conductivity 1 --plane-area 1 --plane-area-in2 1 --plane-area-mil2 1 --plane-distance 1 --plane-distance-mil 1 --plane-distance-in 1 --resistivity 1 --temperature-coefficient 1";
    split(cmd7, argv, &argc);
    TEST_ASSERT_EQUAL_INT(0, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd8[] = "first -c 1 -w 1 --metric --imperial --standard IPC2221 --method A";
    split(cmd8, argv, &argc);
    TEST_ASSERT_EQUAL_INT(0, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd9[] = "first -g -b";
    split(cmd9, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd10[] = "first -c 1";
    split(cmd10, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd11[] = "first -c";
    split(cmd11, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd12[] = "first -c 1 -w 1 -o C:/ -o . -o C:/. --output C:/ --output . --output C:/.";
    split(cmd12, argv, &argc);
    TEST_ASSERT_EQUAL_INT(0, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd13[] = "first -c 1 -w 1 --note 'hey'";
    split(cmd13, argv, &argc);
    TEST_ASSERT_EQUAL_INT(0, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);

    char cmd14[] = "first -c 1 -w 1 --note '";
    char note_test[] = "'Testing the limits of the --note option. Ut officia velit impedit. Voluptate rerum nobis consequuntur nulla. Ipsam nihil aperiam est. At quas quibusdam perferendis autem deserunt totam. Et aspernatur autem corrupti ut earum velit. Itaque velit exercitationem dolor. Repellat sed iusto adipisci fugit. Quisquam cumque dolore omnis velit quos voluptatem nihil reprehenderit. Esse vitae quibusdam vitae asperiores voluptas ex. Omnis perferendis et est magni qui. Error totam ut autem. Fuga molestiae non assumenda nam sed sequi voluptatibus. Tempore nesciunt sit laborum pariatur consectetur id est. Exercitationem enim necessitatibus est. Repudiandae sit voluptates voluptas labore omnis inventore vero. Rerum fuga adipisci quibusdam possimus quis. Excepturi consequuntur assumenda saepe suscipit ut. Soluta qui amet voluptatibus aut ducimus illum. Facilis repellat omnis sint ipsa expedita dolorem corrupti omnis. Occaecati ipsum non eum consequatur commodi omnis dolorum. Consequuntur asperiores reiciendis ipsam enim ex fugiat nobis sequi.'";
    split(cmd14, argv, &argc);
    argv[6] = note_test;
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    reset(argv, &ip, 30);
}

void test_assign_values_units_metric()
{
    dbl_t ip_dbl = {
        .outval = 1,
        .val = 1,
    };
    
    char optstring1[] = "1";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric(&ip_dbl, optstring1, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e-1, 1, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1,ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("t", ip_dbl.units);

    char optstring2[] = "1T";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric(&ip_dbl, optstring2, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e11, 1e12, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("Tt", ip_dbl.units);

    char optstring3[] = "1G";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric(&ip_dbl, optstring3, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e8, 1e9, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("Gt", ip_dbl.units);

    char optstring4[] = "1M";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric(&ip_dbl, optstring4, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e5, 1e6, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("Mt", ip_dbl.units);

    char optstring5[] = "1K";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric(&ip_dbl, optstring5, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e2, 1e3, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("Kt", ip_dbl.units);

    char optstring6[] = "1c";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric(&ip_dbl, optstring6, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e-3, 1e-2, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("ct", ip_dbl.units);

    char optstring7[] = "1m";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric(&ip_dbl, optstring7, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e-4, 1e-3, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("mt", ip_dbl.units);
    
    char optstring8[] = "1u";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric(&ip_dbl, optstring8, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e-7, 1e-6, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("ut", ip_dbl.units);

    char optstring9[] = "1n";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric(&ip_dbl, optstring9, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e-10, 1e-9, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("nt", ip_dbl.units);

    char optstring10[] = "1p";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric(&ip_dbl, optstring10, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e-13, 1e-12, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("pt", ip_dbl.units);

    char optstring11[] = "1f";
    TEST_ASSERT_EQUAL_INT(1, assign_values_units_metric(&ip_dbl, optstring11, 't'));

    char optstring12[] = "!!!!";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric_area(&ip_dbl, optstring12, 't'));
    TEST_ASSERT_EQUAL_INT(0, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(0, ip_dbl.outval);
    
}

void test_assign_values_units_metric_area()
{
    dbl_t ip_dbl = {
        .outval = 1,
        .val = 1,
    };
    
    char optstring1[] = "1";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric_area(&ip_dbl, optstring1, 't'));
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("t^2", ip_dbl.units);

    char optstring2[] = "1T";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric_area(&ip_dbl, optstring2, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e23, 1e12 * 1e12, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("Tt^2", ip_dbl.units);

    char optstring3[] = "1G";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric_area(&ip_dbl, optstring3, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e17 ,1e9 * 1e9, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("Gt^2", ip_dbl.units);

    char optstring4[] = "1M";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric_area(&ip_dbl, optstring4, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e11 ,1e6 * 1e6, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("Mt^2", ip_dbl.units);

    char optstring5[] = "1K";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric_area(&ip_dbl, optstring5, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e5 ,1e3 * 1e3, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("Kt^2", ip_dbl.units);

    char optstring6[] = "1c";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric_area(&ip_dbl, optstring6, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e-5 ,1e-2 * 1e-2, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("ct^2", ip_dbl.units);

    char optstring7[] = "1m";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric_area(&ip_dbl, optstring7, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e-7 ,1e-3 * 1e-3, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("mt^2", ip_dbl.units);
    
    char optstring8[] = "1u";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric_area(&ip_dbl, optstring8, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e-13 ,1e-6 * 1e-6, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("ut^2", ip_dbl.units);

    char optstring9[] = "1n";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric_area(&ip_dbl, optstring9, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e-19 ,1e-9 * 1e-9, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("nt^2", ip_dbl.units);

    char optstring10[] = "1p";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric_area(&ip_dbl, optstring10, 't'));
    TEST_ASSERT_DOUBLE_WITHIN(1e-25 ,1e-12 * 1e-12, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("pt^2", ip_dbl.units);

    char optstring11[] = "1f";
    TEST_ASSERT_EQUAL_INT(1, assign_values_units_metric_area(&ip_dbl, optstring11, 't'));

    char optstring12[] = "!!!!";
    TEST_ASSERT_EQUAL_INT(0, assign_values_units_metric_area(&ip_dbl, optstring12, 't'));
    TEST_ASSERT_EQUAL_INT(0, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(0, ip_dbl.outval);
}

void test_assign_values_units_imperial()
{
    dbl_t ip_dbl;
    char optstring[2] = "1";

    TEST_ASSERT_EQUAL_INT(0, assign_values_units_imperial(&ip_dbl, optstring, "test"));
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.val);
    TEST_ASSERT_EQUAL_INT(1, ip_dbl.outval);
    TEST_ASSERT_EQUAL_STRING("test", ip_dbl.units);
}

void test_conversions()
{
    int argc = 0;
    char* argv[3];
    ip_t ip = {0};

    char cmd1[] = "first --convert-m-to-ozft2 1";
    split(cmd1, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-3, 28570.449, CONV_M_TO_OZFT2(1));
    reset(argv, &ip, 3);

    char cmd2[] = "first --convert-m-to-mil 1";
    split(cmd2, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-2, 39370.08, CONV_M_TO_MIL(1));
    reset(argv, &ip, 3);

    char cmd3[] = "first --convert-m2-to-in2 1";
    split(cmd3, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1, 1550, CONV_M2_TO_IN2(1));
    reset(argv, &ip, 3);

    char cmd4[] = "first --convert-m2-to-mil2 1";
    split(cmd4, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1, 1550003, CONV_M2_TO_MIL2(1));
    reset(argv, &ip, 3);

    char cmd5[] = "first --convert-mil-to-ozft2 1";
    split(cmd5, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-1, 0.7256894049, CONV_MIL_TO_OZFT2(1));
    reset(argv, &ip, 3);

    char cmd6[] = "first --convert-mil-to-mm 1";
    split(cmd6, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-4, 0.0254, CONV_MIL_TO_MM(1));
    reset(argv, &ip, 3);

    char cmd7[] = "first --convert-mil2-to-cm2 1";
    split(cmd7, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-7, 0.000006452, CONV_MIL2_TO_CM2(1));
    reset(argv, &ip, 3);

    char cmd8[] = "first --convert-mil2-to-mm2 1";
    split(cmd8, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-7, 0.0006452, CONV_MIL2_TO_MM2(1));
    reset(argv, &ip, 3);

    char cmd9[] = "first --convert-ozft2-to-mil 1";
    split(cmd9, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-2, 1.378, CONV_OZFT2_TO_MIL(1));
    reset(argv, &ip, 3);

    char cmd10[] = "first --convert-ozft2-to-mm 1";
    split(cmd10, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-3, 0.0350012, CONV_OZFT2_TO_MM(1));
    reset(argv, &ip, 3);

    char cmd11[] = "first --convert-ozft2-to-um 1";
    split(cmd11, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-3, 35.0012, CONV_OZFT2_TO_UM(1));
    reset(argv, &ip, 3);

    char cmd12[] = "first --convert-F-to-C 1";
    split(cmd12, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-1, -17.222, CONV_FAHR_TO_CELS(1));
    reset(argv, &ip, 3);

    char cmd13[] = "first --convert-C-to-F 1";
    split(cmd13, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-1, 33.8, CONV_CELS_TO_FAHR(1));
    reset(argv, &ip, 3);

    char cmd14[] = "first --convert-BTUhftF-to-WmK 1";
    split(cmd14, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-2, 1.730735, CONV_BTUhftF_TO_WmK(1));
    reset(argv, &ip, 3);

    char cmd15[] = "first --convert-WmK-to-BTUhftF 1";
    split(cmd15, argv, &argc);
    TEST_ASSERT_EQUAL_INT(1, get_options(argc, argv, &ip));
    TEST_ASSERT_DOUBLE_WITHIN(1e-2,  0.57778920516428, CONV_WmK_TO_BTUhftF(1));
    reset(argv, &ip, 3);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_output_help);
    RUN_TEST(test_output_results_IPC2221);
    RUN_TEST(test_output_results_IPC2152_A);
    RUN_TEST(test_output_results_IPC2152_B);
    RUN_TEST(test_output_results_IPC2152_C);
    RUN_TEST(test_vdrop);
    RUN_TEST(test_pow_loss);
    RUN_TEST(test_resistance);
    RUN_TEST(test_trace_width_mils);
    RUN_TEST(test_resistance_vdrop_ploss);
    RUN_TEST(test_calcs_IPC2221);
    RUN_TEST(test_calcs_IPC2152_A);
    RUN_TEST(test_calcs_IPC2152_B);
    RUN_TEST(test_calcs_IPC2152_C);
    RUN_TEST(test_get_time);
    RUN_TEST(test_autogen_file_name);
    RUN_TEST(test_set_output_file);
    RUN_TEST(test_sel_functions);
    RUN_TEST(test_set_defv);
    RUN_TEST(test_set_outu);
    RUN_TEST(test_check_method);
    RUN_TEST(test_check_standard);
    RUN_TEST(test_get_standard_method);
    RUN_TEST(test_get_options);
    RUN_TEST(test_assign_values_units_metric);
    RUN_TEST(test_assign_values_units_metric_area);
    RUN_TEST(test_assign_values_units_imperial);
    RUN_TEST(test_conversions);
    return UNITY_END();
}

