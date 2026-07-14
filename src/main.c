#include "FileItem.h"
#include "input.h"
int main() {
  FileList list;
  create_List(&list);
  multithread(&list);
  return 0;
}
