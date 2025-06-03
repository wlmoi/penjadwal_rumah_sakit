#include <stdio.h>
#include "random_id.h"

int main() {
    int numeric_id;
    char string_id[9]; // 8 char + null terminator

    generate_random_numeric_id(&numeric_id, 1000, 9999);
    generate_random_string_id(string_id, 8);

    printf("ID numerik: %d\n", numeric_id);
    printf("ID string : %s\n", string_id);

    return 0;
}

//gcc tes.c random_id.c -o tes
