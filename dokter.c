#include <stdio.h>
#include <string.h>
#include "dokter.h"
#include "random_id.h"

// Menambahkan dokter baru ke daftar
void tambah_dokter(struct Dokter *dokter, int *jumlah_dokter) {
    if (*jumlah_dokter >= DOKTER_MAKS) {
        printf("Tidak dapat menambah dokter, batas tercapai.\n");
        return;
    }
    struct Dokter *d = &dokter[*jumlah_dokter];
    //d->id = *jumlah_dokter + 1; // ID otomatis berdasarkan jumlah dokter
    generate_random_numeric_id(&d->id, 1000, 9999);
    printf("Masukkan nama dokter: ");
    scanf(" %[^\n]", d->nama);
    printf("Masukkan maksimum shift per minggu: ");
    scanf("%d", &d->maks_shift_per_minggu);
    printf("Masukkan preferensi (0=diinginkan, 1=tidak diinginkan) untuk pagi, siang, malam: ");
    scanf("%d %d %d", &d->preferensi[0], &d->preferensi[1], &d->preferensi[2]);
    for (int i = 0; i < 30; i++)
        for (int j = 0; j < 3; j++)
            d->shift_ditugaskan[i][j] = 0;
    d->total_shift = 0;
    (*jumlah_dokter)++;
    printf("Dokter berhasil ditambahkan.\n");
}

// Menghapus dokter berdasarkan nama
void hapus_dokter(struct Dokter *dokter, int *jumlah_dokter, char *nama) {
    int indeks = -1;
    for (int i = 0; i < *jumlah_dokter; i++) {
        if (strcmp(dokter[i].nama, nama) == 0) {
            indeks = i;
            break;
        }
    }
    if (indeks == -1) {
        printf("Dokter tidak ditemukan.\n");
        return;
    }
    for (int i = indeks; i < *jumlah_dokter - 1; i++)
        dokter[i] = dokter[i + 1];
    (*jumlah_dokter)--;
    printf("Dokter berhasil dihapus.\n");
}

// Menampilkan semua dokter
void tampilkan_dokter(struct Dokter *dokter, int jumlah_dokter) {
    printf("\nDaftar Dokter:\n");
    for (int i = 0; i < jumlah_dokter; i++) {
        printf("ID: %d, Nama: %s, Maks Shift/Minggu: %d, Preferensi (Pagi, Siang, Malam): %d, %d, %d\n",
               dokter[i].id, dokter[i].nama, dokter[i].maks_shift_per_minggu,
               dokter[i].preferensi[0], dokter[i].preferensi[1], dokter[i].preferensi[2]);
    }
}