#include <stdio.h>

FILE *fp_output;

int main(int argc, char **argv);

int main_wrapper(int argc, char **argv) {
  fp_output = fopen("output", "w+");

  int main_retval = main(argc, argv);

  rewind(fp_output);

  FILE *fp_expected = fopen("expected", "r");
  int c_output, c_expected;

  printf("Checking the output.");
  while (1) {
    c_output = fgetc(fp_output);
    if (c_output == EOF)
      break;
    if (c_output == '\n') {
      rewind(fp_expected);
      printf("Next.");
      continue;
    }
    c_expected = fgetc(fp_expected);
    //@ assert UB: c_expected == c_output;
    printf("output = %c, expected = %c", c_output, c_expected);
  };
  printf("Done.");

  fclose(fp_expected);
  fclose(fp_output);

  //@ assert UB: main_retval == 0;
  return main_retval;
}
