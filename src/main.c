#include "my_sort.h"

#define LENGTH 1000000

int main(void){
    int *array = generate_array(LENGTH, 0);
    get_time_sort(quick_sort, array, LENGTH);
    check_if_success_sort(array, LENGTH);
    return 0;
}
