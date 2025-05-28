#ifndef FILE_IO_H
#define FILE_IO_H

#include "dokter.h"
#include "jadwal.h" 

int baca_dokter_dari_file(struct Dokter *dokter, const char *nama_file);
void simpan_jadwal_ke_file(struct EntriJadwal *jadwal, int jumlah_jadwal, const char *nama_file);

#endif