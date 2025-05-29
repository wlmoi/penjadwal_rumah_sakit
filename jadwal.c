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

    // Mengalokasikan dokter ke shift, memprioritaskan preferensi
    for (int hari = 0; hari < 30; hari++) {
        int minggu = hari / 7;
        int shift_mingguan[DOKTER_MAKS] = {0}; // Melacak shift per minggu untuk setiap dokter
        struct EntriJadwal *entry = &jadwal[hari];
        strcpy(entry->pagi, "0");
        strcpy(entry->siang, "0");
        strcpy(entry->malam, "0");

        // Mengalokasikan dokter untuk setiap shift (pagi, siang, malam)
        for (int shift = 0; shift < 3; shift++) {
            // Prioritaskan dokter dengan preferensi 0 untuk shift ini
            int dokter_dipilih = -1;
            for (int i = 0; i < jumlah_dokter; i++) {
                if (dokter[i].preferensi[shift] == 0 &&
                    shift_mingguan[i] < dokter[i].maks_shift_per_minggu &&
                    dokter[i].total_shift < dokter[i].maks_shift_per_minggu * 4) {
                    dokter_dipilih = i;
                    break;
                }
            }
            // Jika tidak ada dokter dengan preferensi 0, pilih dokter lain
            if (dokter_dipilih == -1) {
                for (int i = 0; i < jumlah_dokter; i++) {
                    if (shift_mingguan[i] < dokter[i].maks_shift_per_minggu &&
                        dokter[i].total_shift < dokter[i].maks_shift_per_minggu * 4) {
                        dokter_dipilih = i;
                        break;
                    }
                }
            }
            // Jika dokter ditemukan, tugaskan ke shift
            if (dokter_dipilih != -1) {
                if (shift == 0) strcpy(entry->pagi, dokter[dokter_dipilih].nama);
                else if (shift == 1) strcpy(entry->siang, dokter[dokter_dipilih].nama);
                else strcpy(entry->malam, dokter[dokter_dipilih].nama);
                dokter[dokter_dipilih].shift_ditugaskan[hari][shift] = 1;
                dokter[dokter_dipilih].total_shift++;
                shift_mingguan[dokter_dipilih]++;
            }
        }
        (*jumlah_jadwal)++;
    }
}

// Menampilkan jadwal untuk hari tertentu
void tampilkan_jadwal_harian(struct EntriJadwal *jadwal, int jumlah_jadwal, int hari) {
    if (hari >= jumlah_jadwal) {
        printf("Hari tidak valid.\n");
        return;
    }
    printf("\nJadwal Hari %d:\n", hari + 1);
    printf("Pagi: %s\n", jadwal[hari].pagi);
    printf("Siang: %s\n", jadwal[hari].siang);
    printf("Malam: %s\n", jadwal[hari].malam);
}

// Menampilkan jadwal untuk minggu tertentu
void tampilkan_jadwal_mingguan(struct EntriJadwal *jadwal, int jumlah_jadwal, int minggu) {
    printf("\nJadwal Minggu %d:\n", minggu + 1);
    for (int hari = minggu * 7; hari < (minggu + 1) * 7 && hari < jumlah_jadwal; hari++) {
        tampilkan_jadwal_harian(jadwal, jumlah_jadwal, hari);
    }
}

// Menampilkan jadwal bulanan penuh
void tampilkan_jadwal_bulanan(struct EntriJadwal *jadwal, int jumlah_jadwal) {
    printf("\nJadwal Bulanan:\n");
    for (int hari = 0; hari < jumlah_jadwal && hari < 30; hari++) {
        tampilkan_jadwal_harian(jadwal, jumlah_jadwal, hari);
    }
}

// Menampilkan jumlah shift per dokter
void tampilkan_jumlah_shift_dokter(struct Dokter *dokter, int jumlah_dokter) {
    printf("\nJumlah Shift Dokter:\n");
    for (int i = 0; i < jumlah_dokter; i++) {
        printf("%s (ID: %d): %d shift\n", dokter[i].nama, dokter[i].id, dokter[i].total_shift);
    }
}

// Menghitung pelanggaran preferensi
int hitung_pelanggaran_preferensi(struct Dokter *dokter, int jumlah_dokter, struct EntriJadwal *jadwal, int jumlah_jadwal) {
    int pelanggaran = 0;
    for (int hari = 0; hari < jumlah_jadwal && hari < 30; hari++) {
        for (int j = 0; j < jumlah_dokter; j++) {
            if (strcmp(jadwal[hari].pagi, dokter[j].nama) == 0 && dokter[j].preferensi[0] == 1) pelanggaran++;
            if (strcmp(jadwal[hari].siang, dokter[j].nama) == 0 && dokter[j].preferensi[1] == 1) pelanggaran++;
            if (strcmp(jadwal[hari].malam, dokter[j].nama) == 0 && dokter[j].preferensi[2] == 1) pelanggaran++;
        }
    }
    return pelanggaran;
}