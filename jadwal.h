#ifndef JADWAL_H
#define JADWAL_H

#include "dokter.h"

struct EntriJadwal {
    char pagi[NAMA_MAKS]; // Nama dokter untuk shift pagi
    char siang[NAMA_MAKS]; // Nama dokter untuk shift siang
    char malam[NAMA_MAKS]; // Nama dokter untuk shift malam
};

struct PelanggaranDokter {
    int preferensi;
    int maksimal_shift;
    int total_pelanggaran;
};

void hitung_pelanggaran(struct Dokter *dokter, int jumlah_dokter, struct PelanggaranDokter *pelanggaran);
int hitung_shift_minggu_ini(struct Dokter *dokter, int idx_dokter, int hari);
int cari_dokter_terbaik(struct Dokter *dokter, int jumlah_dokter, int hari, int shift, struct PelanggaranDokter *pelanggaran);
void buat_jadwal(struct Dokter *dokter, int jumlah_dokter, struct PelanggaranDokter *pelanggaran, struct EntriJadwal *jadwal, int *jumlah_jadwal);
void tampilkan_jadwal_harian(struct EntriJadwal *jadwal, int jumlah_jadwal, int hari);
void tampilkan_jadwal_mingguan(struct EntriJadwal *jadwal, int jumlah_jadwal, int minggu);
void tampilkan_jadwal_bulanan(struct EntriJadwal *jadwal, int jumlah_jadwal);
void tampilkan_jumlah_shift_dokter(struct Dokter *dokter, int jumlah_dokter);
void tampilkan_pelanggaran(struct Dokter *dokter, struct PelanggaranDokter *pelanggaran, int jumlah_dokter);

#endif
