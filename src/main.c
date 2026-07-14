#include "FileItem.h"
#include "input.h"
int main(int argc, char *argv[]) {
  FileList list;
  create_List(&list);
  multithread(&list);
  return 0;
}
