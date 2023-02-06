#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void exit_success() {
	exit(EXIT_SUCCESS);
}

void exit_failure() {
	exit(EXIT_FAILURE);
}

void print_stdout_help_text() {
	printf("Usage: b4 [options] [target] ...\n");
	printf("Options:\n");
	printf("    -%-20sPrint this message and exit\n",  "h");
	printf("\n");
	return;
}

void print_stderr_options_error() {
	fprintf(stderr, "Exiting with failure status. Invalid options strictly prohibited.\n");
	fprintf(stderr, "To see a list of valid options run b4 -h or b4 --help");
	return;
}

int main(int argc, char *argv[]) {
	int opt;

	// first get any options
	while ((opt = getopt(argc, argv, "h")) != -1) {
		switch (opt) {
			case 'h':
				print_stdout_help_text();
				exit_success();
				break;
			default:
				// getopt() is going to print an error message for us.
				// But lets add another specifying that we are going to exit with failure status. We will
				// also provide a pointer towards the help flag to get usage information.
				print_stderr_options_error();
				exit_failure();
		}
	}

	// then get any file arguments
	for (int i = optind; i < argc; i++) {
		int file_argument_index = i - optind;
		printf("file argument %d: %s\n", file_argument_index, argv[i]);
	}

	// read a char print a char
	char input_char;
	while ((input_char = fgetc(stdin)) > 0) {
		// how to check for a new line character and print something sensible
		switch (input_char) {
			case '\n':
				printf("read char: \\n\n");
				break;
			default:
				printf("read char: %c\n", input_char);
		}
	}

	
	return EXIT_SUCCESS;
}
