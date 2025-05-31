#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jadwal.h"

//Hitung pelanggaran dokter
void hitung_pelanggaran(struct Dokter *dokter, int jumlah_dokter, struct PelanggaranDokter *pelanggaran) {
    for (int d = 0; d < jumlah_dokter; d++) {
        pelanggaran[d].preferensi = 0;
        pelanggaran[d].maksimal_shift = 0;
        pelanggaran[d].total_pelanggaran = 0;

        // Hitung pelanggaran preferensi
        for (int h = 0; h < 30; h++) {
            for (int s = 0; s < 3; s++) {
                if (dokter[d].shift_ditugaskan[h][s] && dokter[d].preferensi[s] == 0) {
                    pelanggaran[d].preferensi++;
                    pelanggaran[d].total_pelanggaran++;
                }
            }
        }

        // Hitung pelanggaran shift per minggu
        for (int m = 0; m < 5; m++) {
            int shift_minggu = 0;
            for (int h = m * 7; h < (m + 1) * 7 && h < 30; h++) {
                for (int s = 0; s < 3; s++) {
                    if (dokter[d].shift_ditugaskan[h][s]) {
                        shift_minggu++;
                    }
                }
            }
            if (shift_minggu > dokter[d].maks_shift_per_minggu) {
                pelanggaran[d].maksimal_shift += (shift_minggu - dokter[d].maks_shift_per_minggu);
                pelanggaran[d].total_pelanggaran += (shift_minggu - dokter[d].maks_shift_per_minggu);
            }
        }
    }
}

//Hitung shift dookter perminggunya
int hitung_shift_minggu_ini(struct Dokter *dokter, int idx_dokter, int hari) {
    int minggu = hari / 7;
    int shift_minggu_ini = 0;
    for (int h = minggu * 7; h < (minggu + 1) * 7 && h < 30; h++) {
        for (int s = 0; s < 3; s++) {
            if (dokter[idx_dokter].shift_ditugaskan[h][s]) {
                shift_minggu_ini++;
            }
        }
    }
    return shift_minggu_ini;
}

//Mencari dokter yang paling cocok sesuai dengan shift yang diminta
int cari_dokter_terbaik(struct Dokter *dokter, int jumlah_dokter, int hari, int shift, struct PelanggaranDokter *pelanggaran) {
    int terpilih = -1;
    int skor_sebelumnya = 0;

    for (int d = 0; d < jumlah_dokter; d++) {
        hitung_pelanggaran(dokter, jumlah_dokter, pelanggaran);
        int skor = 0;
        int shift_minggu_ini = hitung_shift_minggu_ini(dokter, d, hari);

        if (shift_minggu_ini >= dokter[d].maks_shift_per_minggu) {
            skor++;
        }

        if (dokter[d].preferensi[shift] == 0) {
            skor++;
        }
        skor += pelanggaran[d].total_pelanggaran;

        if (terpilih == -1 || skor < skor_sebelumnya) {
            terpilih = d;
            skor_sebelumnya = skor;
        }
    }

    return terpilih;
}

//Algoritma utama pembuatan jadwal
void buat_jadwal(struct Dokter *dokter, int jumlah_dokter, struct PelanggaranDokter *pelanggaran, struct EntriJadwal *jadwal, int *jumlah_jadwal) {
    (*jumlah_jadwal) = 0;
    //Inisialisasi jadwal
    for (int hari = 0; hari < 30; hari++) {
        for (int shift = 0; shift < 3; shift++) {
            for (int d = 0; d < jumlah_dokter; d++) {
                dokter[d].shift_ditugaskan[hari][shift] = 0;
            }
        }
        strcpy(jadwal[hari].pagi, "0");
        strcpy(jadwal[hari].siang, "0");
        strcpy(jadwal[hari].malam, "0");
    }

    //Penjadwalan Dokter Utama
    for (int hari = 0; hari < 30; hari++) {
        for (int shift = 0; shift < 3; shift++) {
            int terpilih = cari_dokter_terbaik(dokter, jumlah_dokter, hari, shift, pelanggaran);
            if (terpilih != -1) {
                dokter[terpilih].shift_ditugaskan[hari][shift] = 1;
                if (shift == 0) {
                    strcpy(jadwal[hari].pagi, dokter[terpilih].nama);
                } else if (shift == 1) {
                    strcpy(jadwal[hari].siang, dokter[terpilih].nama);
                } else if (shift == 2) {
                    strcpy(jadwal[hari].malam, dokter[terpilih].nama);
                }
            }
        }
        (*jumlah_jadwal)++;
    }

    //Penjadwalan Dokter Tambahan
    for (int hari = 0; hari < 30; hari++) {
        for (int shift = 0; shift < 3; shift++) {

            for (int d = 0; d < jumlah_dokter; d++) {
                // Hitung shift minggu ini untuk dokter ini
                int shift_minggu_ini = hitung_shift_minggu_ini(dokter, d, hari);
                
                if (shift_minggu_ini < dokter[d].maks_shift_per_minggu &&
                    dokter[d].preferensi[shift] == 1 &&
                    !dokter[d].shift_ditugaskan[hari][shift]) {
                    
                    dokter[d].shift_ditugaskan[hari][shift] = 1;
                    
                    //Update jadwal
                    if (shift == 0) {
                        if (strcmp(jadwal[hari].pagi, "0") != 0) {
                            strcat(jadwal[hari].pagi, ", ");
                        }
                        strcat(jadwal[hari].pagi, dokter[d].nama);
                    } else if (shift == 1) {
                        if (strcmp(jadwal[hari].siang, "0") != 0) {
                            strcat(jadwal[hari].siang, ", ");
                        }
                        strcat(jadwal[hari].siang, dokter[d].nama);
                    } else if (shift == 2) {
                        if (strcmp(jadwal[hari].malam, "0") != 0) {
                            strcat(jadwal[hari].malam, ", ");
                        }
                        strcat(jadwal[hari].malam, dokter[d].nama);
                    }
                }
            }
        }
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

// Menampilkan pelanggaran semua dokter
void tampilkan_pelanggaran(struct Dokter *dokter, struct PelanggaranDokter *pelanggaran, int jumlah_dokter) {
    hitung_pelanggaran(dokter, jumlah_dokter, pelanggaran);
    printf("\nJumlah Shift Dokter:\n");
    for (int i = 0; i < jumlah_dokter; i++) {
        printf("\n%s (ID: %d)\nPelanggaran Preferensi: %d\nPelanggaran Shift: %d\n", dokter[i].nama, dokter[i].id, pelanggaran[i].preferensi, pelanggaran[i].maksimal_shift);
    }
}
