#ifndef DOKTER_H
#define DOKTER_H

#define NAMA_MAKS 50
#define DOKTER_MAKS 100

struct Dokter {
    char nama[NAMA_MAKS];
    int maks_shift_per_minggu;
    int preferensi[3]; // 0: pagi, 1: siang, 2: malam (0 = diinginkan, 1 = tidak diinginkan)
    int shift_ditugaskan[30][3]; // Melacak shift untuk 30 hari, 3 shift per hari
    int total_shift; // Total shift yang ditugaskan
};

void tambah_dokter(struct Dokter *dokter, int *jumlah_dokter);
void hapus_dokter(struct Dokter *dokter, int *jumlah_dokter, char *nama);
void tampilkan_dokter(struct Dokter *dokter, int jumlah_dokter);
int baca_dokter_dari_file(struct Dokter *dokter, const char *nama_file);

#endif