#ifndef _my_sort_h
#define _my_sort_h

int *generate_array(int, int);
int check_if_success_sort(int *, int);
void get_time_sort(void (*pf)(int *, int), int *, int);
void swap(int *, int *);
void reverse_array(int *, int);
void display_array(int *, int);

void bubble_sort(int *, int);
void quick_sort(int *, int);
void merge_sort(int *, int);

#endif
