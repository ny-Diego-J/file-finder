#include "file_item.h"
#include <stddef.h>
#ifndef INPUT
#define INPUT
void init_threads(file_list *list, int amount);
void append_char(char *dest, char *src, size_t dest_capacity);
#else
#endif // !INPUT
