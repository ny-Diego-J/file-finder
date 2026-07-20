#include "file_item.h"
#include "input.h"
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int num;
  if (argc > 1) {
    num = atoi(argv[1]);
  } else {
    int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    num = num_cores * 2;
  }

  file_list list;
  create_List(&list);
  init_threads(&list, num);
  return 0;
}
