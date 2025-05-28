#include <stdio.h>
#include <string.h>
#include "jadwal.h"

// Membuat jadwal untuk 30 hari, 3 shift per hari
void buat_jadwal(struct Dokter *dokter, int jumlah_dokter, struct EntriJadwal *jadwal, int *jumlah_jadwal) {
    *jumlah_jadwal = 0;
    // Mengatur ulang shift yang ditugaskan
    for (int i = 0; i < jumlah_dokter; i++) {
        for (int d = 0; d < 30; d++)
            for (int s = 0; s < 3; s++)
                dokter[i].shift_ditugaskan[d][s] = 0;
        dokter[i].total_shift = 0;
    }

    // Mengalokasikan satu dokter per shift, mempertimbangkan batasan
    for (int hari = 0; hari < 30; hari++) {
        int minggu = hari / 7;
        int shift_mingguan[DOKTER_MAKS] = {0}; // Melacak shift per minggu untuk setiap dokter
        for (int shift = 0; shift < 3; shift++) {
            for (int i = 0; i < jumlah_dokter; i++) {
                if (shift_mingguan[i] < dokter[i].maks_shift_per_minggu &&
                    dokter[i].total_shift < dokter[i].maks_shift_per_minggu * 4) {
                    jadwal[*jumlah_jadwal].shift = shift;
                    strcpy(jadwal[*jumlah_jadwal].nama_dokter, dokter[i].nama);
                    dokter[i].shift_ditugaskan[hari][shift] = 1;
                    dokter[i].total_shift++;
                    shift_mingguan[i]++;
                    (*jumlah_jadwal)++;
                    break; // Satu dokter per shift
                }
            }
        }
    }
}

// Menampilkan jadwal untuk hari tertentu
void tampilkan_jadwal_harian(struct EntriJadwal *jadwal, int jumlah_jadwal, int hari) {
    printf("\nJadwal Hari %d:\n", hari + 1);
    for (int i = 0; i < jumlah_jadwal; i++) {
        if (i / 3 == hari) {
            printf("Shift %d (%s): %s\n", jadwal[i].shift + 1,
                   jadwal[i].shift == 0 ? "Pagi" : jadwal[i].shift == 1 ? "Siang" : "Malam",
                   jadwal[i].nama_dokter);
        }
    }
}

// Menampilkan jadwal untuk minggu tertentu
void tampilkan_jadwal_mingguan(struct EntriJadwal *jadwal, int jumlah_jadwal, int minggu) {
    printf("\nJadwal Minggu %d:\n", minggu + 1);
    for (int hari = minggu * 7; hari < (minggu + 1) * 7 && hari < 30; hari++) {
        tampilkan_jadwal_harian(jadwal, jumlah_jadwal, hari);
    }
}

// Menampilkan jadwal bulanan penuh
void tampilkan_jadwal_bulanan(struct EntriJadwal *jadwal, int jumlah_jadwal) {
    printf("\nJadwal Bulanan:\n");
    for (int hari = 0; hari < 30; hari++) {
        tampilkan_jadwal_harian(jadwal, jumlah_jadwal, hari);
    }
}

// Menampilkan jumlah shift per dokter
void tampilkan_jumlah_shift_dokter(struct Dokter *dokter, int jumlah_dokter) {
    printf("\nJumlah Shift Dokter:\n");
    for (int i = 0; i < jumlah_dokter; i++) {
        printf("%s: %d shift\n", dokter[i].nama, dokter[i].total_shift);
    }
}

// Menghitung pelanggaran preferensi
int hitung_pelanggaran_preferensi(struct Dokter *dokter, int jumlah_dokter, struct EntriJadwal *jadwal, int jumlah_jadwal) {
    int pelanggaran = 0;
    for (int i = 0; i < jumlah_jadwal; i++) {
        for (int j = 0; j < jumlah_dokter; j++) {
            if (strcmp(jadwal[i].nama_dokter, dokter[j].nama) == 0) {
                if (dokter[j].preferensi[jadwal[i].shift] == 1) {
                    pelanggaran++;
                }
                break;
            }
        }
    }
    return pelanggaran;
}