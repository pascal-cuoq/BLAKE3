
int main(int argc, char **argv);

int main_wrapper(int argc, char **argv) {
  int main_retval = main(argc, argv);
  //@ assert UB: main_retval == 0;
  return main_retval;
}
