#include "random_id.h"
#include <stdlib.h>
#include <time.h>

void generate_random_numeric_id(int *id, int min, int max) {
    if (min >= max) {
        *id = min; // fallback jika salah input
        return;
    }

    // seed hanya dilakukan sekali, cek apakah sudah diset
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    *id = rand() % (max - min + 1) + min;
}

void generate_random_string_id(char *buffer, int length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charset_size = sizeof(charset) - 1;

    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    for (int i = 0; i < length; i++) {
        int key = rand() % charset_size;
        buffer[i] = charset[key];
    }
    buffer[length] = '\0';
}
