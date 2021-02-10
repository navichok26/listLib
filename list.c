#ifndef _LIST_H
#define _LIST_H
#include "list.h"

List *list_new(uint8_t *format, ...) {
    List *list = (List*) malloc(sizeof(List));
    List *list_ptr = list;
    list->type = _INIT_;
    list->next = NULL;

    value_list value;

    va_list factor;
    va_start(factor, format);
    while(*format) {
        switch (*format) {
            case 'd': case 'i':
                value.decimal = va_arg(factor, int64_t);
                list_ptr = list_push(list_ptr, "d", value.decimal);
            break;

            case 'r': case 'f':
                value.real = va_arg(factor, double);
                list_ptr = list_push(list_ptr, "r", value.real);
            break;

            case 's':
                value.string = va_arg(factor, uint8_t*);
                list_ptr = list_push(list_ptr, "s", value.string);
            break;
        }
        ++format;
    }
    va_end(factor);
    return list;
}

void list_free(List *list) {
    List *list_ptr;
    while (list != NULL) {
        list_ptr = list->next;
        free(list);
        list = list_ptr;
    }
}

List *list_push(List *list, uint8_t *format, ...) {
    if (list == NULL) {
        fprintf(stderr, "%s\n", "list is null");
        return NULL;
    }

    while (list->next != NULL) {
        list = list->next;
    }
    value_list value;
    va_list factor;
    va_start(factor, format);
    while(*format) {
        switch (*format) {
            case 'd': case 'i':
                value.decimal = va_arg(factor, int64_t);
                list->next = (List*)malloc(sizeof(List));
                list = list->next;
                list->type = _DECIMAL_;
                list->value.decimal = value.decimal;
            break;

            case 'r': case 'f':
                value.real = va_arg(factor, double);
                list->next = (List*)malloc(sizeof(List));
                list = list->next;
                list->type = _REAL_;
                list->value.real = value.real;
            break;

            case 's':
                value.string = va_arg(factor, uint8_t*);
                list->next = (List*)malloc(sizeof(List));
                list = list->next;
                list->type = _STRING_;
                list->value.string = value.string;
            break;
        }
        ++format;
    }
    va_end(factor);
    return list;
}

List *list_pop(List *list) {
    if (list == NULL) {
        fprintf(stderr, "%s\n", "List is null");
        return NULL;
    }

    if (list->next == NULL) {
        return list;
    }
    List *prev = list;
    List *past = list->next;
    while (past->next != NULL) {
        prev = past;
        past = past->next;
    }
    prev->next = NULL;
    return past;
}

void list_print(List *list) {
    printf("[ ");
    while (list != NULL) {
        switch(list->type) {
            case _DECIMAL_:
                printf("%ld ", list->value.decimal);
            break;

            case _REAL_:
                printf("%lf ", list->value.real);
            break;

            case _STRING_:
                printf("%s ", list->value.string);
            break;
        }
        list = list->next;
    }
    printf("]");
}

#endif
