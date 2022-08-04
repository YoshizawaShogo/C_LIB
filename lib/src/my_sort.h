#ifndef _my_sort_h
#define _my_sort_h

int *generate_array(int length, int seed);
int check_if_success_sort(int *array, int length);
void get_time_sort(void (*pf)(int *, int), int *array, int length);
void swap(int *a, int *b);
void reverse_array(int *array, int length);
void display_array(int *array, int length);

void bubble_sort(int *array, int length);
void quick_sort(int *array, int length);
void merge_sort(int *array, int length);

#endif
