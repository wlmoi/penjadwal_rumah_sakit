#include <stdio.h>
#include <stdlib.h>
#include "dokter.h"
#include "jadwal.h"
#include "file_io.h"

// JALANKAN 
// gcc -o penjadwal_rumah_sakit main.c dokter.c jadwal.c file_io.c
// ./penjadwal_rumah_sakit

int main() {
    struct Dokter dokter[DOKTER_MAKS];
    struct EntriJadwal jadwal[30];// 30 hari, masing-masing dengan pagi, siang, malam
    struct PelanggaranDokter pelanggaran[DOKTER_MAKS];
    int jumlah_dokter = 0, jumlah_jadwal = 0;
    char nama_file[] = "daftar_dokter.csv";
    char nama_file_jadwal[] = "jadwal.csv";
    int pilihan;

    while (1) {
        printf("\nSistem Penjadwalan Rumah Sakit\n");
        printf("1. Baca dokter dari file\n");
        printf("2. Tambah dokter\n");
        printf("3. Hapus dokter\n");
        printf("4. Tampilkan dokter\n");
        printf("5. Buat jadwal\n");
        printf("6. Tampilkan jadwal harian\n");
        printf("7. Tampilkan jadwal mingguan\n");
        printf("8. Tampilkan jadwal bulanan\n");
        printf("9. Tampilkan jumlah shift dokter\n");
        printf("10. Tampilkan pelanggaran preferensi\n");
        printf("11. Simpan jadwal ke file\n");
        printf("12. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);

        if (pilihan == 12) break;

        switch (pilihan) {
            case 1:
                jumlah_dokter = baca_dokter_dari_file(dokter, nama_file);
                printf("Berhasil membaca %d dokter dari file.\n", jumlah_dokter);
                break;
            case 2:
                tambah_dokter(dokter, &jumlah_dokter);
                break;
            case 3: {
                char nama[NAMA_MAKS];
                printf("Masukkan nama dokter yang akan dihapus: ");
                scanf(" %[^\n]", nama);
                hapus_dokter(dokter, &jumlah_dokter, nama);
                break;
            }
            case 4:
                tampilkan_dokter(dokter, jumlah_dokter);
                break;
            case 5:
                buat_jadwal(dokter, jumlah_dokter, pelanggaran, jadwal, &jumlah_jadwal);
                printf("Jadwal dibuat untuk %d hari.\n", jumlah_jadwal);
                break;
            case 6: {
                int hari;
                printf("Masukkan hari (1-30): ");
                scanf("%d", &hari);
                if (hari >= 1 && hari <= 30)
                    tampilkan_jadwal_harian(jadwal, jumlah_jadwal, hari - 1);
                else
                    printf("Hari tidak valid.\n");
                break;
            }
            case 7: {
                int minggu;
                printf("Masukkan minggu (1-5): ");
                scanf("%d", &minggu);
                if (minggu >= 1 && minggu <= 5)
                    tampilkan_jadwal_mingguan(jadwal, jumlah_jadwal, minggu - 1);
                else
                    printf("Minggu tidak valid.\n");
                break;
            }
            case 8:
                tampilkan_jadwal_bulanan(jadwal, jumlah_jadwal);
                break;
            case 9:
                tampilkan_jumlah_shift_dokter(dokter, jumlah_dokter);
                break;
            case 10:
                tampilkan_pelanggaran(dokter, pelanggaran, jumlah_dokter);
                break;
            case 11:
                simpan_jadwal_ke_file(jadwal, jumlah_jadwal, nama_file_jadwal);
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }
    return 0;
}
