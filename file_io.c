#include <stdio.h>
#include <string.h>
#include "file_io.h"

// Membaca data dokter dari file CSV
int baca_dokter_dari_file(struct Dokter *dokter, const char *nama_file) {
    FILE *file = fopen(nama_file, "r");
    if (!file) {
        printf("Tidak dapat membuka file %s\n", nama_file);
        return 0;
    }
    int jumlah_dokter = 0;
    char baris[256];
    fgets(baris, sizeof(baris), file); // Lewati header
    while (fgets(baris, sizeof(baris), file) && jumlah_dokter < DOKTER_MAKS) {
        sscanf(baris, "%[^,],%d,%d,%d,%d",
               dokter[jumlah_dokter].nama,
               &dokter[jumlah_dokter].maks_shift_per_minggu,
               &dokter[jumlah_dokter].preferensi[0],
               &dokter[jumlah_dokter].preferensi[1],
               &dokter[jumlah_dokter].preferensi[2]);
        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 3; j++)
                dokter[jumlah_dokter].shift_ditugaskan[i][j] = 0;
        dokter[jumlah_dokter].total_shift = 0;
        jumlah_dokter++;
    }
    fclose(file);
    return jumlah_dokter;
}

// Menyimpan jadwal ke file CSV
void simpan_jadwal_ke_file(struct EntriJadwal *jadwal, int jumlah_jadwal, const char *nama_file) {
    FILE *file = fopen(nama_file, "w");
    if (!file) {
        printf("Tidak dapat membuka file %s\n", nama_file);
        return;
    }
    fprintf(file, "Hari,Shift,Dokter\n");
    for (int i = 0; i < jumlah_jadwal; i++) {
        fprintf(file, "%d,%d,%s\n", (i / 3) + 1, jadwal[i].shift + 1, jadwal[i].nama_dokter);
    }
    fclose(file);
    printf("Jadwal disimpan ke %s\n", nama_file);
}