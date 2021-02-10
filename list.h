#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

typedef enum {
    _INIT_,
    _DECIMAL_,
    _REAL_,
    _STRING_,
} type_elem;

typedef union {
    int64_t decimal;
    double real;
    uint8_t *string;
} value_list;

typedef struct List{
    struct List *next;
    value_list value;
    type_elem type;
} List;

List *list_push(List *list, uint8_t *format, ...);
List *list_new(uint8_t *format, ...);
void list_free(List *list);
List *list_pop(List *list);
void list_print(List *list);
