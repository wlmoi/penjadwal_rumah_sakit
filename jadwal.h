#ifndef JADWAL_H
#define JADWAL_H

#include "dokter.h"

struct EntriJadwal {
    char nama_dokter[NAMA_MAKS];
    int shift; // 0: pagi, 1: siang, 2: malam
};

void buat_jadwal(struct Dokter *dokter, int jumlah_dokter, struct EntriJadwal *jadwal, int *jumlah_jadwal);
void tampilkan_jadwal_harian(struct EntriJadwal *jadwal, int jumlah_jadwal, int hari);
void tampilkan_jadwal_mingguan(struct EntriJadwal *jadwal, int jumlah_jadwal, int minggu);
void tampilkan_jadwal_bulanan(struct EntriJadwal *jadwal, int jumlah_jadwal);
void tampilkan_jumlah_shift_dokter(struct Dokter *dokter, int jumlah_dokter);
int hitung_pelanggaran_preferensi(struct Dokter *dokter, int jumlah_dokter, struct EntriJadwal *jadwal, int jumlah_jadwal);

#endif