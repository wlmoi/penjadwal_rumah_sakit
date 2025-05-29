#ifndef JADWAL_H
#define JADWAL_H

#include "dokter.h"

struct EntriJadwal {
    char pagi[NAMA_MAKS]; // Nama dokter untuk shift pagi
    char siang[NAMA_MAKS]; // Nama dokter untuk shift siang
    char malam[NAMA_MAKS]; // Nama dokter untuk shift malam
};

void buat_jadwal(struct Dokter *dokter, int jumlah_dokter, struct EntriJadwal *jadwal, int *jumlah_jadwal);
void tampilkan_jadwal_harian(struct EntriJadwal *jadwal, int jumlah_jadwal, int hari);
void tampilkan_jadwal_mingguan(struct EntriJadwal *jadwal, int jumlah_jadwal, int minggu);
void tampilkan_jadwal_bulanan(struct EntriJadwal *jadwal, int jumlah_jadwal);
void tampilkan_jumlah_shift_dokter(struct Dokter *dokter, int jumlah_dokter);
int hitung_pelanggaran_preferensi(struct Dokter *dokter, int jumlah_dokter, struct EntriJadwal *jadwal, int jumlah_jadwal);

#endif