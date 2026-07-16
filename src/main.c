#include "file_item.h"
#include "input.h"
#include <stdlib.h>
int main(int argc, char *argv[]) {
  int num;
  if (argc > 1) {
    num = atoi(argv[1]);
  } else {
    num = 1024;
  }

  file_list list;
  create_List(&list);
  init_threads(&list, num);
  return 0;
}
