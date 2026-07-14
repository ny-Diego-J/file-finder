#include "file_item.h"
#include "input.h"
int main() {
  file_list list;
  create_List(&list);
  multithread(&list);
  return 0;
}
