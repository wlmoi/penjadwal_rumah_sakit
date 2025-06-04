#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "file_io.h"

// Membaca data dokter dari file CSV dengan kolom id
int baca_dokter_dari_file(struct Dokter *dokter, const char *nama_file) {
    FILE *file = fopen(nama_file, "r");
    if (!file) {
        printf("Tidak dapat membuka file %s\n", nama_file);
        return 0;
    }
    int jumlah_dokter = 0;
    char baris[256];
    // Lewati header
    if (!fgets(baris, sizeof(baris), file)) {
        printf("Gagal membaca header file %s\n", nama_file);
        fclose(file);
        return 0;
    }
    // Membaca setiap baris data
    while (fgets(baris, sizeof(baris), file) && jumlah_dokter < DOKTER_MAKS) {
        // Menghapus karakter baris baru atau spasi di akhir
        baris[strcspn(baris, "\r\n")] = 0;
        // Parsing baris dengan sscanf
        int id, maks_shift, pagi, siang, malam;
        char nama[NAMA_MAKS];
        int parsed = sscanf(baris, "%d,%[^,],%d,%d,%d,%d",
                            &id, nama, &maks_shift, &pagi, &siang, &malam);
        if (parsed != 6) {
            printf("Gagal parsing baris: %s\n", baris);
            continue;
        }
        // Menyimpan data ke struktur
        dokter[jumlah_dokter].id = id;
        strncpy(dokter[jumlah_dokter].nama, nama, NAMA_MAKS - 1);
        dokter[jumlah_dokter].nama[NAMA_MAKS - 1] = '\0'; // Pastikan string null-terminated
        dokter[jumlah_dokter].maks_shift_per_minggu = maks_shift;
        dokter[jumlah_dokter].preferensi[0] = pagi;
        dokter[jumlah_dokter].preferensi[1] = siang;
        dokter[jumlah_dokter].preferensi[2] = malam;
        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 3; j++)
                dokter[jumlah_dokter].shift_ditugaskan[i][j] = 0;
        dokter[jumlah_dokter].total_shift = 0;
        // Debugging: Cetak data yang dibaca
        printf("Dokter dibaca: ID=%d, Nama=%s, MaksShift=%d, Pagi=%d, Siang=%d, Malam=%d\n",
               dokter[jumlah_dokter].id, dokter[jumlah_dokter].nama,
               dokter[jumlah_dokter].maks_shift_per_minggu,
               dokter[jumlah_dokter].preferensi[0],
               dokter[jumlah_dokter].preferensi[1],
               dokter[jumlah_dokter].preferensi[2]);
        jumlah_dokter++;
    }
    fclose(file);
    if (jumlah_dokter == 0) {
        printf("Tidak ada dokter yang berhasil dibaca dari file %s\n", nama_file);
    }
    return jumlah_dokter;
}

// Menyimpan jadwal ke file CSV dalam format hari,pagi,siang,malam
void simpan_jadwal_ke_file(struct EntriJadwal *jadwal, int jumlah_jadwal, const char *nama_file) {
    FILE *file = fopen(nama_file, "w");
    if (!file) {
        printf("Tidak dapat membuka file %s\n", nama_file);
        return;
    }
    fprintf(file, "hari,pagi,siang,malam\n");
    for (int i = 0; i < jumlah_jadwal && i < 30; i++) {
        fprintf(file, "%d,%s,%s,%s\n", i + 1, jadwal[i].pagi, jadwal[i].siang, jadwal[i].malam);
    }
    fclose(file);
    printf("Jadwal disimpan ke %s\n", nama_file);
}

// Menyimpan daftar dokter ke file CSV dalam format persis sesuai header contoh
void simpan_dokter_ke_file(struct Dokter *dokter, int jumlah_dokter, const char *nama_file) {
    FILE *file = fopen(nama_file, "w");
    if (!file) {
        printf("Tidak dapat membuka file %s\n", nama_file);
        return;
    }

    // Header CSV sesuai contoh yang kamu berikan
    fprintf(file, "id,Nama,MaksShiftPerMinggu,PagiPref,SiangPref,MalamPref\n");

    // Tulis data setiap dokter
    for (int i = 0; i < jumlah_dokter; i++) {
        fprintf(file, "%d,%s,%d,%d,%d,%d\n",
                dokter[i].id,
                dokter[i].nama,
                dokter[i].maks_shift_per_minggu,
                dokter[i].preferensi[0],
                dokter[i].preferensi[1],
                dokter[i].preferensi[2]);
    }

    fclose(file);
    printf("Daftar dokter disimpan ke %s\n", nama_file);
}
