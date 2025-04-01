/*
    twc : Trace Width Calculator.
    Copyright (C) 2024 Yiannis Michael (ymich9963)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

//TODO: Describe in docs the workflow for development
// Mention in docs that the default behaviour is metrimc
//TODO: Add more methods
//TODO: Put a sample of the help option in the docs
//TODO: Add a --comment/description option to add some custom text to the output
//TODO: Add a conversion function as a parameter like CONV_M_MIL(1) and multiply that variable by the value

#include "twc.h"

int main(int argc, char** argv)
{
	/* Inputs */
	ip_t ip;

	/* Outputs */
	op_t op;

	/* Output stream */
	FILE* file = stdout;

	/* Universal Defaults */
	ip.standard.num = IPC2152;
	ip.method = 'A';
	ip.uflag = 'm';
	ip.resistivity.val = 1.724e-6;
	ip.a.val = 3.93e-3;
	ip.ofile.oflag = 0;

	/* Get the standard and the method for the calculations */
	CHECK_ERR(get_standard_method(argc, argv, &ip));

	/* Set functions based on the inputs */
	CHECK_ERR(sel_functions(&ip));

	/* Set defaults */
	ip.defv(&ip);

	/* Get the inputs and options */
	CHECK_ERR(get_options(argc, argv, &ip));

	/* Calculate the values */
	ip.proc(&ip, &op);

	/* Set output units */
	ip.outu(&ip, &op);

	/* Open file to save outputs */
	if (ip.ofile.oflag) {
		file = fopen(ip.ofile.path, "w");

		if (!(file)) {
			fprintf(stderr, "\nFile not able to be saved, check input. Directory '%s' may not exist.\n\n", ip.ofile.path);
			exit(EXIT_FAILURE);
		}
	}

	/* Output the results to the buffer */
	ip.outp(&ip, &op, file);

	/* Close file and free memory */
	if (file != stdout) {
		fclose(file);
		printf("\nContents exported to %s\n\n", ip.ofile.path);
	}

	/* Program done. exit succesfully */
	exit(EXIT_SUCCESS);
}
