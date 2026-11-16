#include <stdio.h>
#include <string.h>

/*
====================================================================
               PROGRAM SISTEM MANAJEMEN RESTORAN
  Materi : Dasar Pemrograman / Algoritma (Maksimal Array)
  Aturan : Murni C, Array 1D & 2D char, TANPA Pointer
  Username & Password berbentuk string disimpan dalam array 2 dimensi
====================================================================
*/

/* Prosedur untuk mencetak nama makanan berdasarkan indeks (0 - 4) */
void cetak_nama_makanan(int indeks) {
    if (indeks == 0) {
        printf("Nasi Goreng Spesial");
    } else if (indeks == 1) {
        printf("Mie Goreng Seafood ");
    } else if (indeks == 2) {
        printf("Ayam Bakar Madu    ");
    } else if (indeks == 3) {
        printf("Sate Ayam Madura   ");
    } else if (indeks == 4) {
        printf("Rendang Daging Sapi");
    } else {
        printf("Menu Makanan       ");
    }
}

/* Prosedur untuk mencetak nama minuman berdasarkan indeks (0 - 4) */
void cetak_nama_minuman(int indeks) {
    if (indeks == 0) {
        printf("Es Teh Manis       ");
    } else if (indeks == 1) {
        printf("Es Jeruk Segar     ");
    } else if (indeks == 2) {
        printf("Kopi Hitam Tubruk  ");
    } else if (indeks == 3) {
        printf("Jus Alpukat        ");
    } else if (indeks == 4) {
        printf("Air Mineral Dingin ");
    } else {
        printf("Menu Minuman       ");
    }
}

/* Prosedur untuk mencetak garis pemisah tampilan */
void cetak_garis(void) {
    printf("====================================================================\n");
}

int main(void) {
    /* -------------------------------------------------------------
       DATABASE PENGGUNA (PARALLEL ARRAY 1D & 2D CHAR)
       - user_name     : Username berbentuk string
       - user_pass     : Password berbentuk string
       - user_role     : 1 = Admin, 0 = User Biasa
       - user_banned   : 1 = Banned (Terblokir), 0 = Aktif
       - user_salah    : Penghitung percobaan salah password (maks 5x)
       ------------------------------------------------------------- */
    char user_name[50][30];
    char user_pass[50][30];
    int user_role[50];
    int user_banned[50];
    int user_salah[50];
    int jumlah_user = 1; /* Hanya admin yang ada di awal, user biasa wajib registrasi */

    /* Akun Bawaan: Admin */
    strcpy(user_name[0], "admin");
    strcpy(user_pass[0], "admin");
    user_role[0] = 1;
    user_banned[0] = 0;
    user_salah[0] = 0;

    /* -------------------------------------------------------------
       DATA MENU & HARGA (ARRAY 1 DIMENSI)
       ------------------------------------------------------------- */
    int jumlah_menu_makanan = 5;
    int harga_makanan[5];
    int terjual_makanan[5];

    harga_makanan[0] = 25000;
    harga_makanan[1] = 28000;
    harga_makanan[2] = 30000;
    harga_makanan[3] = 26000;
    harga_makanan[4] = 35000;

    terjual_makanan[0] = 0;
    terjual_makanan[1] = 0;
    terjual_makanan[2] = 0;
    terjual_makanan[3] = 0;
    terjual_makanan[4] = 0;

    int jumlah_menu_minuman = 5;
    int harga_minuman[5];
    int terjual_minuman[5];

    harga_minuman[0] = 5000;
    harga_minuman[1] = 8000;
    harga_minuman[2] = 10000;
    harga_minuman[3] = 15000;
    harga_minuman[4] = 4000;

    terjual_minuman[0] = 0;
    terjual_minuman[1] = 0;
    terjual_minuman[2] = 0;
    terjual_minuman[3] = 0;
    terjual_minuman[4] = 0;

    /* -------------------------------------------------------------
       KERANJANG PESANAN USER AKTIF
       ------------------------------------------------------------- */
    int pesanan_makanan[5];
    int pesanan_minuman[5];
    int i;
    for (i = 0; i < 5; i++) {
        pesanan_makanan[i] = 0;
        pesanan_minuman[i] = 0;
    }

    int tipe_layanan = 1; /* 1 = Take In (Makan di tempat), 2 = Take Away (Bungkus) */

    /* -------------------------------------------------------------
       DATA KODE DISKON
       ------------------------------------------------------------- */
    int kode_diskon_admin = 8888;
    int persen_diskon_admin = 20;   /* 20% */
    int kode_diskon_spesial = 7777; /* Diskon acak / promo spesial */
    int persen_diskon_spesial = 30; /* 30% */

    int diskon_terpakai = 0; /* Persentase diskon aktif untuk pesanan saat ini */

    /* -------------------------------------------------------------
       DATA RATING RESTORAN (ARRAY 1 DIMENSI)
       ------------------------------------------------------------- */
    int rating_riwayat[100];
    int jumlah_rating = 2;
    rating_riwayat[0] = 5;
    rating_riwayat[1] = 4;

    /* -------------------------------------------------------------
       VARIABEL NAVIGASI HALAMAN & SESI
       ------------------------------------------------------------- */
    int halaman = 1; /* Dimulai dari Halaman 1: Dashboard */
    int user_aktif = -1; /* Indeks array user yang sedang login */
    int program_berjalan = 1;

    /* Variabel bantuan operasional */
    int pilihan;
    char input_user[30];
    char input_pass[30];
    int user_ditemukan;
    int jumlah_pesan;
    int subtotal_makanan, subtotal_minuman, total_kotor;
    int nominal_diskon, total_bayar;
    int uang_bayar, kembalian;
    int rating_baru;
    int ada_item;

    while (program_berjalan == 1) {
        /* =========================================================
           PAGE 1: DASHBOARD (LOGIN, REGISTER)
           ========================================================= */
        if (halaman == 1) {
            cetak_garis();
            printf("            SELAMAT DATANG DI RESTORAN NUSANTARA\n");
            cetak_garis();

            /* Tampilkan Rating Rata-rata Restoran */
            if (jumlah_rating > 0) {
                int total_skor = 0;
                for (i = 0; i < jumlah_rating; i++) {
                    total_skor += rating_riwayat[i];
                }
                float rata_rating = (float)total_skor / (float)jumlah_rating;
                printf("[Rating Restoran : %.1f / 5.0 Bintang (dari %d ulasan pelanggan)]\n", rata_rating, jumlah_rating);
            } else {
                printf("[Rating Restoran : Belum ada ulasan]\n");
            }
            printf("\n");
            printf("Pilihan Menu Utama:\n");
            printf("1. Login (Pengguna / Admin)\n");
            printf("2. Register Akun Baru\n");
            printf("3. Keluar dari Program\n");
            printf("Pilih opsi (1-3): ");
            if (scanf("%d", &pilihan) != 1) {
                break;
            }

            if (pilihan == 1) {
                halaman = 2; /* Menuju Page 2: Login */
            } else if (pilihan == 2) {
                halaman = 3; /* Menuju Page 3: Register */
            } else if (pilihan == 3) {
                printf("\nTerima kasih telah mengunjungi Restoran Nusantara. Sampai jumpa!\n");
                program_berjalan = 0;
            } else {
                printf("\n[ERROR] Pilihan tidak valid! Silakan masukkan angka 1 - 3.\n\n");
            }
        }

        /* =========================================================
           PAGE 2: LOGIN
           - Cek admin / user biasa
           - Cek apakah akun di-ban
           - Jika password salah 5x -> otomatis di-ban
           ========================================================= */
        else if (halaman == 2) {
            cetak_garis();
            printf("                      HALAMAN LOGIN\n");
            cetak_garis();
            printf("(Petunjuk Akun Default Admin -> Username: admin, Password: admin)\n");
            printf("(Untuk Pengguna Baru: Silakan registrasi terlebih dahulu di Menu Register)\n\n");
            printf("Masukkan Username: ");
            if (scanf("%29s", input_user) != 1) break;
            printf("Masukkan Password: ");
            if (scanf("%29s", input_pass) != 1) break;

            user_ditemukan = -1;
            for (i = 0; i < jumlah_user; i++) {
                if (strcmp(user_name[i], input_user) == 0) {
                    user_ditemukan = i;
                    break;
                }
            }

            if (user_ditemukan == -1) {
                printf("\n[GAGAL] Username '%s' tidak ditemukan dalam database!\n", input_user);
                printf("(Catatan: Pengguna harus melakukan registrasi terlebih dahulu sebelum login)\n\n");
                printf("1. Coba Login Lagi\n");
                printf("2. Kembali ke Dashboard\n");
                printf("Pilihan (1-2): ");
                if (scanf("%d", &pilihan) != 1) break;
                if (pilihan != 1) {
                    halaman = 1;
                }
            } else {
                /* Cek status blokir akun */
                if (user_banned[user_ditemukan] == 1) {
                    printf("\n[DITOLAK] Akun '%s' saat ini sedang DI-BAN!\n", input_user);
                    printf("Penyebab : Melakukan kesalahan password >= 5 kali atau sanksi admin.\n");
                    printf("Silakan hubungi admin restoran untuk membuka blokir (unban).\n\n");
                    halaman = 1; /* Dialihkan kembali ke dashboard */
                } else {
                    /* Verifikasi password */
                    if (strcmp(user_pass[user_ditemukan], input_pass) == 0) {
                        /* Login Berhasil */
                        user_salah[user_ditemukan] = 0; /* Reset counter salah */
                        user_aktif = user_ditemukan;

                        if (user_role[user_ditemukan] == 1) {
                            /* Role == Admin */
                            printf("\n>>> Login BERHASIL sebagai ADMIN (%s) <<<\n\n", input_user);
                            halaman = 5; /* Menuju Page 5: Admin */
                        } else {
                            /* Role == User Biasa */
                            printf("\n>>> Login BERHASIL sebagai PELANGGAN (%s) <<<\n\n", input_user);
                            /* Reset keranjang belanja */
                            for (i = 0; i < 5; i++) {
                                pesanan_makanan[i] = 0;
                                pesanan_minuman[i] = 0;
                            }
                            diskon_terpakai = 0;
                            tipe_layanan = 1;
                            halaman = 6; /* Menuju Page 6: Menu Makanan */
                        }
                    } else {
                        /* Password Salah */
                        user_salah[user_ditemukan]++;
                        printf("\n[PASSWORD SALAH] Percobaan gagal ke-%d dari 5.\n", user_salah[user_ditemukan]);

                        if (user_salah[user_ditemukan] >= 5) {
                            user_banned[user_ditemukan] = 1;
                            user_salah[user_ditemukan] = 0;
                            printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                            printf("PERINGATAN SISTEM: Anda salah password 5 kali berturut-turut!\n");
                            printf("Akun '%s' sekarang telah DI-BAN demi keamanan.\n", input_user);
                            printf("Hubungi admin restoran untuk melakukan unban akun Anda.\n");
                            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
                            halaman = 1; /* Dialihkan ke dashboard */
                        } else {
                            printf("Sisa kesempatan sebelum akun di-ban: %d kali.\n\n", 5 - user_salah[user_ditemukan]);
                            printf("1. Coba Login Lagi\n");
                            printf("2. Kembali ke Dashboard\n");
                            printf("Pilihan (1-2): ");
                            if (scanf("%d", &pilihan) != 1) break;
                            if (pilihan != 1) {
                                halaman = 1;
                            }
                        }
                    }
                }
            }
        }

        /* =========================================================
           PAGE 3: REGISTER
           - Input username & password baru (string)
           - Cek apakah username sudah digunakan
           - Setelah registrasi, user diarahkan login lagi
           ========================================================= */
        else if (halaman == 3) {
            cetak_garis();
            printf("                    REGISTRASI AKUN BARU\n");
            cetak_garis();
            printf("Masukkan Username baru: ");
            if (scanf("%29s", input_user) != 1) break;

            /* Cek apakah username sudah ada */
            user_ditemukan = 0;
            for (i = 0; i < jumlah_user; i++) {
                if (strcmp(user_name[i], input_user) == 0) {
                    user_ditemukan = 1;
                    break;
                }
            }

            if (user_ditemukan == 1) {
                printf("\n[GAGAL] Username '%s' sudah digunakan pengguna lain!\n\n", input_user);
                printf("1. Coba Daftar Lagi dengan Username Lain\n");
                printf("2. Kembali ke Dashboard\n");
                printf("Pilihan (1-2): ");
                if (scanf("%d", &pilihan) != 1) break;
                if (pilihan != 1) {
                    halaman = 1;
                }
            } else {
                printf("Masukkan Password baru: ");
                if (scanf("%29s", input_pass) != 1) break;

                /* Simpan ke array database */
                strcpy(user_name[jumlah_user], input_user);
                strcpy(user_pass[jumlah_user], input_pass);
                user_role[jumlah_user] = 0;   /* Role default = User Biasa */
                user_banned[jumlah_user] = 0; /* Status aktif */
                user_salah[jumlah_user] = 0;  /* Reset kesalahan */
                jumlah_user++;

                printf("\n[SUKSES] Akun '%s' berhasil didaftarkan!\n", input_user);
                printf("Silakan login menggunakan akun baru yang telah Anda buat...\n\n");
                halaman = 2; /* Dialihkan langsung ke halaman Login! */
            }
        }

        /* =========================================================
           PAGE 4: LOG OUT
           - Menampilkan pesan user sudah log out
           - Interface otomatis diarahkan ke dashboard
           ========================================================= */
        else if (halaman == 4) {
            cetak_garis();
            printf("                      HALAMAN LOGOUT\n");
            cetak_garis();
            if (user_aktif >= 0) {
                printf("Pengguna '%s' telah berhasil LOGOUT dari sistem.\n", user_name[user_aktif]);
            } else {
                printf("Anda telah berhasil LOGOUT dari sistem.\n");
            }
            printf("Sesi aktif telah diakhiri. Interface diarahkan ke Dashboard...\n\n");
            user_aktif = -1; /* Bersihkan sesi login */
            halaman = 1;     /* Otomatis kembali ke dashboard */
        }

        /* =========================================================
           PAGE 5: ADMIN
           - Update menu dan harga
           - Unban user
           - Lihat data menu yang terjual
           - Atur kode diskon admin
           ========================================================= */
        else if (halaman == 5) {
            cetak_garis();
            printf("                    HALAMAN PANEL ADMIN\n");
            cetak_garis();
            printf("1. Update Menu dan Harga\n");
            printf("2. Unban User\n");
            printf("3. Lihat Data Menu yang Terjual\n");
            printf("4. Atur Kode Diskon Admin\n");
            printf("5. Logout\n");
            printf("Pilih opsi admin (1-5): ");
            if (scanf("%d", &pilihan) != 1) break;

            /* Sub-fitur 1: Update Menu dan Harga */
            if (pilihan == 1) {
                cetak_garis();
                printf("               ADMIN: UPDATE MENU DAN HARGA\n");
                cetak_garis();
                printf("Pilih Kategori Menu:\n");
                printf("1. Makanan\n");
                printf("2. Minuman\n");
                printf("Pilihan (1-2): ");
                int kat;
                if (scanf("%d", &kat) != 1) break;

                if (kat == 1) {
                    printf("\nDaftar Harga Menu Makanan Saat Ini:\n");
                    for (i = 0; i < jumlah_menu_makanan; i++) {
                        printf("%d. ", i + 1);
                        cetak_nama_makanan(i);
                        printf(" - Rp %d\n", harga_makanan[i]);
                    }
                    printf("Pilih nomor makanan yang ingin diubah harganya (1-5): ");
                    int no_menu, harga_baru;
                    if (scanf("%d", &no_menu) != 1) break;
                    if (no_menu >= 1 && no_menu <= 5) {
                        printf("Masukkan harga baru untuk ");
                        cetak_nama_makanan(no_menu - 1);
                        printf(": Rp ");
                        if (scanf("%d", &harga_baru) != 1) break;
                        if (harga_baru > 0) {
                            harga_makanan[no_menu - 1] = harga_baru;
                            printf("[SUKSES] Harga berhasil diubah menjadi Rp %d!\n\n", harga_baru);
                        } else {
                            printf("[GAGAL] Harga harus lebih besar dari 0!\n\n");
                        }
                    } else {
                        printf("[GAGAL] Nomor menu makanan tidak valid!\n\n");
                    }
                } else if (kat == 2) {
                    printf("\nDaftar Harga Menu Minuman Saat Ini:\n");
                    for (i = 0; i < jumlah_menu_minuman; i++) {
                        printf("%d. ", i + 1);
                        cetak_nama_minuman(i);
                        printf(" - Rp %d\n", harga_minuman[i]);
                    }
                    printf("Pilih nomor minuman yang ingin diubah harganya (1-5): ");
                    int no_menu, harga_baru;
                    if (scanf("%d", &no_menu) != 1) break;
                    if (no_menu >= 1 && no_menu <= 5) {
                        printf("Masukkan harga baru untuk ");
                        cetak_nama_minuman(no_menu - 1);
                        printf(": Rp ");
                        if (scanf("%d", &harga_baru) != 1) break;
                        if (harga_baru > 0) {
                            harga_minuman[no_menu - 1] = harga_baru;
                            printf("[SUKSES] Harga berhasil diubah menjadi Rp %d!\n\n", harga_baru);
                        } else {
                            printf("[GAGAL] Harga harus lebih besar dari 0!\n\n");
                        }
                    } else {
                        printf("[GAGAL] Nomor menu minuman tidak valid!\n\n");
                    }
                } else {
                    printf("[GAGAL] Kategori tidak valid!\n\n");
                }
            }

            /* Sub-fitur 2: Unban User */
            else if (pilihan == 2) {
                cetak_garis();
                printf("                     ADMIN: UNBAN USER\n");
                cetak_garis();
                int ada_banned = 0;
                printf("Daftar Pengguna yang Sedang Di-ban:\n");
                for (i = 0; i < jumlah_user; i++) {
                    if (user_banned[i] == 1) {
                        printf("- Username: %s (Role: %s)\n", user_name[i], user_role[i] == 1 ? "Admin" : "User Biasa");
                        ada_banned = 1;
                    }
                }

                if (ada_banned == 0) {
                    printf("(Tidak ada user yang sedang di-ban saat ini)\n\n");
                } else {
                    printf("\nMasukkan Username yang ingin di-unban (atau ketik 'batal'): ");
                    char target_unban[30];
                    if (scanf("%29s", target_unban) != 1) break;
                    if (strcmp(target_unban, "batal") != 0) {
                        int status_unban = 0;
                        for (i = 0; i < jumlah_user; i++) {
                            if (strcmp(user_name[i], target_unban) == 0 && user_banned[i] == 1) {
                                user_banned[i] = 0;
                                user_salah[i] = 0;
                                status_unban = 1;
                                break;
                            }
                        }
                        if (status_unban == 1) {
                            printf("[SUKSES] Akun '%s' berhasil di-unban!\n\n", target_unban);
                        } else {
                            printf("[GAGAL] Username '%s' tidak ditemukan atau tidak sedang di-ban!\n\n", target_unban);
                        }
                    }
                }
            }

            /* Sub-fitur 3: Lihat Data Menu yang Terjual */
            else if (pilihan == 3) {
                cetak_garis();
                printf("             LAPORAN DATA MENU YANG TERJUAL\n");
                cetak_garis();
                int total_omset = 0;

                printf("--- REKAP PENJUALAN MAKANAN ---\n");
                for (i = 0; i < jumlah_menu_makanan; i++) {
                    int subtotal = terjual_makanan[i] * harga_makanan[i];
                    total_omset += subtotal;
                    printf("%d. ", i + 1);
                    cetak_nama_makanan(i);
                    printf(" | Terjual: %3d porsi | Total Omset: Rp %d\n", terjual_makanan[i], subtotal);
                }

                printf("\n--- REKAP PENJUALAN MINUMAN ---\n");
                for (i = 0; i < jumlah_menu_minuman; i++) {
                    int subtotal = terjual_minuman[i] * harga_minuman[i];
                    total_omset += subtotal;
                    printf("%d. ", i + 1);
                    cetak_nama_minuman(i);
                    printf(" | Terjual: %3d porsi | Total Omset: Rp %d\n", terjual_minuman[i], subtotal);
                }

                cetak_garis();
                printf("TOTAL KESELURUHAN PENDAPATAN RESTORAN: Rp %d\n", total_omset);
                cetak_garis();
                printf("\n");
            }

            /* Sub-fitur 4: Atur Kode Diskon Admin */
            else if (pilihan == 4) {
                cetak_garis();
                printf("               ADMIN: ATUR KODE DISKON\n");
                cetak_garis();
                printf("Kode Diskon Aktif Saat Ini : %d\n", kode_diskon_admin);
                printf("Besaran Potongan           : %d%%\n\n", persen_diskon_admin);
                printf("Masukkan Kode Diskon Baru (Angka) : ");
                if (scanf("%d", &kode_diskon_admin) != 1) break;
                printf("Masukkan Persentase Diskon Baru (%%) : ");
                if (scanf("%d", &persen_diskon_admin) != 1) break;
                printf("[SUKSES] Kode Diskon Admin diperbarui menjadi %d sebesar %d%%!\n\n", kode_diskon_admin, persen_diskon_admin);
            }

            /* Sub-fitur 5: Logout */
            else if (pilihan == 5) {
                halaman = 4; /* Menuju Page 4: Logout */
            } else {
                printf("[GAGAL] Pilihan menu tidak valid!\n\n");
            }
        }

        /* =========================================================
           PAGE 6: MENU (LIST MENU DAN HARGA MAKANAN)
           ========================================================= */
        else if (halaman == 6) {
            cetak_garis();
            printf("                    DAFTAR MENU MAKANAN\n");
            cetak_garis();
            for (i = 0; i < jumlah_menu_makanan; i++) {
                printf("%d. ", i + 1);
                cetak_nama_makanan(i);
                printf(" - Rp %d", harga_makanan[i]);
                if (pesanan_makanan[i] > 0) {
                    printf(" [Dipesan: %d porsi]", pesanan_makanan[i]);
                }
                printf("\n");
            }
            cetak_garis();
            printf("Pilihan Aksi:\n");
            printf("1. Pesan Makanan\n");
            printf("2. Lanjut ke Menu Minuman\n");
            printf("3. Batal Pesan & Logout\n");
            printf("Pilih opsi (1-3): ");
            if (scanf("%d", &pilihan) != 1) break;

            if (pilihan == 1) {
                printf("Pilih nomor menu makanan (1-5): ");
                int no_mkn;
                if (scanf("%d", &no_mkn) != 1) break;
                if (no_mkn >= 1 && no_mkn <= 5) {
                    printf("Masukkan jumlah porsi: ");
                    if (scanf("%d", &jumlah_pesan) != 1) break;
                    if (jumlah_pesan > 0) {
                        pesanan_makanan[no_mkn - 1] += jumlah_pesan;
                        printf("[OK] ");
                        cetak_nama_makanan(no_mkn - 1);
                        printf(" sebanyak %d porsi ditambahkan ke keranjang!\n\n", jumlah_pesan);
                    } else {
                        printf("[GAGAL] Jumlah porsi harus lebih dari 0!\n\n");
                    }
                } else {
                    printf("[GAGAL] Nomor menu makanan tidak valid!\n\n");
                }
            } else if (pilihan == 2) {
                halaman = 7; /* Menuju Page 7: Minuman */
            } else if (pilihan == 3) {
                halaman = 4; /* Logout */
            } else {
                printf("[GAGAL] Pilihan tidak valid!\n\n");
            }
        }

        /* =========================================================
           PAGE 7: MENU MINUMAN
           ========================================================= */
        else if (halaman == 7) {
            cetak_garis();
            printf("                    DAFTAR MENU MINUMAN\n");
            cetak_garis();
            for (i = 0; i < jumlah_menu_minuman; i++) {
                printf("%d. ", i + 1);
                cetak_nama_minuman(i);
                printf(" - Rp %d", harga_minuman[i]);
                if (pesanan_minuman[i] > 0) {
                    printf(" [Dipesan: %d porsi]", pesanan_minuman[i]);
                }
                printf("\n");
            }
            cetak_garis();
            printf("Pilihan Aksi:\n");
            printf("1. Pesan Minuman\n");
            printf("2. Kembali ke Menu Makanan\n");
            printf("3. Lanjut ke Pilihan Take In / Take Away\n");
            printf("Pilih opsi (1-3): ");
            if (scanf("%d", &pilihan) != 1) break;

            if (pilihan == 1) {
                printf("Pilih nomor menu minuman (1-5): ");
                int no_mnm;
                if (scanf("%d", &no_mnm) != 1) break;
                if (no_mnm >= 1 && no_mnm <= 5) {
                    printf("Masukkan jumlah porsi: ");
                    if (scanf("%d", &jumlah_pesan) != 1) break;
                    if (jumlah_pesan > 0) {
                        pesanan_minuman[no_mnm - 1] += jumlah_pesan;
                        printf("[OK] ");
                        cetak_nama_minuman(no_mnm - 1);
                        printf(" sebanyak %d porsi ditambahkan ke keranjang!\n\n", jumlah_pesan);
                    } else {
                        printf("[GAGAL] Jumlah porsi harus lebih dari 0!\n\n");
                    }
                } else {
                    printf("[GAGAL] Nomor menu minuman tidak valid!\n\n");
                }
            } else if (pilihan == 2) {
                halaman = 6; /* Kembali ke Page 6: Makanan */
            } else if (pilihan == 3) {
                /* Validasi ketersediaan pesanan di keranjang */
                ada_item = 0;
                for (i = 0; i < 5; i++) {
                    if (pesanan_makanan[i] > 0 || pesanan_minuman[i] > 0) {
                        ada_item = 1;
                        break;
                    }
                }
                if (ada_item == 0) {
                    printf("\n[PERINGATAN] Keranjang pesanan masih kosong!\n");
                    printf("Silakan pesan minimal 1 makanan atau minuman terlebih dahulu.\n\n");
                } else {
                    halaman = 8; /* Menuju Page 8: Take In / Take Away */
                }
            } else {
                printf("[GAGAL] Pilihan tidak valid!\n\n");
            }
        }

        /* =========================================================
           PAGE 8: TAKE IN / TAKE AWAY
           ========================================================= */
        else if (halaman == 8) {
            cetak_garis();
            printf("               PILIHAN TAKE IN / TAKE AWAY\n");
            cetak_garis();
            printf("Silakan tentukan metode penyajian pesanan Anda:\n");
            printf("1. Take In (Makan di Tempat / Restoran)\n");
            printf("2. Take Away (Bungkus / Dibawa Pulang)\n");
            printf("Pilih opsi (1-2): ");
            if (scanf("%d", &pilihan) != 1) break;

            if (pilihan == 1) {
                tipe_layanan = 1;
                printf("\n[PILIHAN ANDA] Take In (Makan di Tempat).\n\n");
                halaman = 9; /* Menuju Page 9: Kode Diskon */
            } else if (pilihan == 2) {
                tipe_layanan = 2;
                printf("\n[PILIHAN ANDA] Take Away (Bungkus / Bawa Pulang).\n\n");
                halaman = 9; /* Menuju Page 9: Kode Diskon */
            } else {
                printf("[GAGAL] Pilihan tidak valid! Silakan masukkan 1 atau 2.\n\n");
            }
        }

        /* =========================================================
           PAGE 9: KODE DISKON
           - Kode dari admin atau kode promo spesial
           ========================================================= */
        else if (halaman == 9) {
            cetak_garis();
            printf("                      KODE DISKON\n");
            cetak_garis();
            printf("Apakah Anda memiliki kode diskon promo?\n");
            printf("1. Ya, masukkan kode diskon\n");
            printf("2. Tidak / Lewati tanpa kode diskon\n");
            printf("Pilih opsi (1-2): ");
            if (scanf("%d", &pilihan) != 1) break;

            if (pilihan == 1) {
                printf("Masukkan Kode Diskon (Angka): ");
                int input_diskon;
                if (scanf("%d", &input_diskon) != 1) break;

                if (input_diskon == kode_diskon_admin) {
                    diskon_terpakai = persen_diskon_admin;
                    printf("\n[SELAMAT] Kode Diskon Admin valid! Diskon %d%% berhasil diterapkan.\n\n", diskon_terpakai);
                } else if (input_diskon == kode_diskon_spesial) {
                    diskon_terpakai = persen_diskon_spesial;
                    printf("\n[SELAMAT] Kode Promo Spesial (7777) valid! Diskon %d%% berhasil diterapkan.\n\n", diskon_terpakai);
                } else {
                    diskon_terpakai = 0;
                    printf("\n[INFO] Kode diskon tidak cocok atau kedaluwarsa. Diskon yang diterapkan: 0%%.\n\n");
                }
                halaman = 10; /* Menuju Page 10: Konfirmasi */
            } else if (pilihan == 2) {
                diskon_terpakai = 0;
                printf("\n[INFO] Pesanan dilanjutkan tanpa diskon.\n\n");
                halaman = 10; /* Menuju Page 10: Konfirmasi */
            } else {
                printf("[GAGAL] Pilihan tidak valid!\n\n");
            }
        }

        /* =========================================================
           PAGE 10: KONFIRMASI PESANAN
           - Menampilkan pilihan menu, harga, jumlah pesanan, total harga
           - Ada opsi ke menu pembatalan
           ========================================================= */
        else if (halaman == 10) {
            cetak_garis();
            printf("                 HALAMAN KONFIRMASI PESANAN\n");
            cetak_garis();
            printf("Jenis Layanan : %s\n", tipe_layanan == 1 ? "Take In (Makan di Tempat)" : "Take Away (Bungkus)");
            printf("--------------------------------------------------------------------\n");
            printf("%-4s %-22s %-12s %-8s %-12s\n", "No", "Nama Menu", "Harga", "Jumlah", "Subtotal");
            printf("--------------------------------------------------------------------\n");

            int nomor_tampil = 1;
            total_kotor = 0;
            int total_item = 0;

            /* Tampilkan dan hitung subtotal makanan */
            for (i = 0; i < 5; i++) {
                if (pesanan_makanan[i] > 0) {
                    subtotal_makanan = pesanan_makanan[i] * harga_makanan[i];
                    total_kotor += subtotal_makanan;
                    total_item += pesanan_makanan[i];
                    printf("%-4d ", nomor_tampil++);
                    cetak_nama_makanan(i);
                    printf(" Rp %-9d %-8d Rp %-12d\n", harga_makanan[i], pesanan_makanan[i], subtotal_makanan);
                }
            }

            /* Tampilkan dan hitung subtotal minuman */
            for (i = 0; i < 5; i++) {
                if (pesanan_minuman[i] > 0) {
                    subtotal_minuman = pesanan_minuman[i] * harga_minuman[i];
                    total_kotor += subtotal_minuman;
                    total_item += pesanan_minuman[i];
                    printf("%-4d ", nomor_tampil++);
                    cetak_nama_minuman(i);
                    printf(" Rp %-9d %-8d Rp %-12d\n", harga_minuman[i], pesanan_minuman[i], subtotal_minuman);
                }
            }

            nominal_diskon = (total_kotor * diskon_terpakai) / 100;
            total_bayar = total_kotor - nominal_diskon;

            printf("--------------------------------------------------------------------\n");
            printf("Total Jumlah Pesanan (Item) : %d item\n", total_item);
            printf("Subtotal Kotor              : Rp %d\n", total_kotor);
            printf("Potongan Diskon (%d%%)        : - Rp %d\n", diskon_terpakai, nominal_diskon);
            printf("TOTAL AKHIR TAGIHAN         : Rp %d\n", total_bayar);
            cetak_garis();

            printf("Pilihan Aksi:\n");
            printf("1. Lanjut ke Pembayaran\n");
            printf("2. Masuk ke Menu Pembatalan (Ubah / Batalkan Item)\n");
            printf("3. Batalkan Seluruh Pesanan dan Kembali ke Menu\n");
            printf("Pilih opsi (1-3): ");
            if (scanf("%d", &pilihan) != 1) break;

            if (pilihan == 1) {
                if (total_item <= 0) {
                    printf("\n[PERINGATAN] Keranjang pesanan Anda kosong! Kembali ke menu makanan.\n\n");
                    halaman = 6;
                } else {
                    halaman = 12; /* Menuju Page 12: Pembayaran */
                }
            } else if (pilihan == 2) {
                halaman = 11; /* Menuju Page 11: Menu Pembatalan */
            } else if (pilihan == 3) {
                for (i = 0; i < 5; i++) {
                    pesanan_makanan[i] = 0;
                    pesanan_minuman[i] = 0;
                }
                diskon_terpakai = 0;
                printf("\n[BATAL] Seluruh pesanan telah dibatalkan. Kembali ke menu makanan.\n\n");
                halaman = 6;
            } else {
                printf("[GAGAL] Pilihan tidak valid!\n\n");
            }
        }

        /* =========================================================
           PAGE 11: MENU PEMBATALAN
           - Memilih menu yang batal dipesan
           - Setelah selesai akan dikembalikan ke page konfirmasi
           ========================================================= */
        else if (halaman == 11) {
            cetak_garis();
            printf("                    MENU PEMBATALAN PESANAN\n");
            cetak_garis();
            printf("Pilih kategori pesanan yang ingin diubah/dibatalkan:\n");
            printf("1. Batalkan / Kurangi Pesanan Makanan\n");
            printf("2. Batalkan / Kurangi Pesanan Minuman\n");
            printf("3. Selesai dan Kembali ke Halaman Konfirmasi\n");
            printf("Pilih opsi (1-3): ");
            if (scanf("%d", &pilihan) != 1) break;

            if (pilihan == 1) {
                printf("\nDaftar Pesanan Makanan Saat Ini:\n");
                int ada_mkn = 0;
                for (i = 0; i < 5; i++) {
                    if (pesanan_makanan[i] > 0) {
                        printf("%d. ", i + 1);
                        cetak_nama_makanan(i);
                        printf(" (Sedang dipesan: %d porsi)\n", pesanan_makanan[i]);
                        ada_mkn = 1;
                    }
                }
                if (ada_mkn == 0) {
                    printf("(Tidak ada makanan dalam keranjang pesanan)\n\n");
                } else {
                    printf("Pilih nomor makanan yang ingin dikurangi (1-5): ");
                    int target;
                    if (scanf("%d", &target) != 1) break;
                    if (target >= 1 && target <= 5 && pesanan_makanan[target - 1] > 0) {
                        printf("Masukkan jumlah porsi yang ingin dibatalkan: ");
                        int batal_qty;
                        if (scanf("%d", &batal_qty) != 1) break;
                        if (batal_qty >= pesanan_makanan[target - 1]) {
                            pesanan_makanan[target - 1] = 0;
                            printf("[SUKSES] Seluruh porsi makanan tersebut berhasil dibatalkan!\n\n");
                        } else if (batal_qty > 0) {
                            pesanan_makanan[target - 1] -= batal_qty;
                            printf("[SUKSES] Berhasil mengurangi %d porsi. Sisa pesanan: %d porsi.\n\n", batal_qty, pesanan_makanan[target - 1]);
                        } else {
                            printf("[GAGAL] Jumlah pembatalan tidak valid!\n\n");
                        }
                    } else {
                        printf("[GAGAL] Nomor makanan tidak valid atau belum dipesan!\n\n");
                    }
                }
            } else if (pilihan == 2) {
                printf("\nDaftar Pesanan Minuman Saat Ini:\n");
                int ada_mnm = 0;
                for (i = 0; i < 5; i++) {
                    if (pesanan_minuman[i] > 0) {
                        printf("%d. ", i + 1);
                        cetak_nama_minuman(i);
                        printf(" (Sedang dipesan: %d porsi)\n", pesanan_minuman[i]);
                        ada_mnm = 1;
                    }
                }
                if (ada_mnm == 0) {
                    printf("(Tidak ada minuman dalam keranjang pesanan)\n\n");
                } else {
                    printf("Pilih nomor minuman yang ingin dikurangi (1-5): ");
                    int target;
                    if (scanf("%d", &target) != 1) break;
                    if (target >= 1 && target <= 5 && pesanan_minuman[target - 1] > 0) {
                        printf("Masukkan jumlah porsi yang ingin dibatalkan: ");
                        int batal_qty;
                        if (scanf("%d", &batal_qty) != 1) break;
                        if (batal_qty >= pesanan_minuman[target - 1]) {
                            pesanan_minuman[target - 1] = 0;
                            printf("[SUKSES] Seluruh porsi minuman tersebut berhasil dibatalkan!\n\n");
                        } else if (batal_qty > 0) {
                            pesanan_minuman[target - 1] -= batal_qty;
                            printf("[SUKSES] Berhasil mengurangi %d porsi. Sisa pesanan: %d porsi.\n\n", batal_qty, pesanan_minuman[target - 1]);
                        } else {
                            printf("[GAGAL] Jumlah pembatalan tidak valid!\n\n");
                        }
                    } else {
                        printf("[GAGAL] Nomor minuman tidak valid atau belum dipesan!\n\n");
                    }
                }
            } else if (pilihan == 3) {
                halaman = 10; /* Dikembalikan ke Page 10: Konfirmasi */
            } else {
                printf("[GAGAL] Pilihan tidak valid!\n\n");
            }
        }

        /* =========================================================
           PAGE 12: PEMBAYARAN (STRUK BELANJA)
           - Menampilkan pilihan menu serta harga / struk belanja
           - Input uang dan cek kembalian
           - Catat pesanan ke rekap menu yang terjual
           ========================================================= */
        else if (halaman == 12) {
            cetak_garis();
            printf("                  STRUK PEMBAYARAN KASIR\n");
            cetak_garis();
            printf("Layanan      : %s\n", tipe_layanan == 1 ? "Take In (Makan di Tempat)" : "Take Away (Bungkus)");
            printf("Pelanggan    : %s\n", user_name[user_aktif]);
            printf("--------------------------------------------------------------------\n");

            total_kotor = 0;
            for (i = 0; i < 5; i++) {
                if (pesanan_makanan[i] > 0) {
                    int sub = pesanan_makanan[i] * harga_makanan[i];
                    total_kotor += sub;
                    printf("- ");
                    cetak_nama_makanan(i);
                    printf("  x%d  = Rp %d\n", pesanan_makanan[i], sub);
                }
            }
            for (i = 0; i < 5; i++) {
                if (pesanan_minuman[i] > 0) {
                    int sub = pesanan_minuman[i] * harga_minuman[i];
                    total_kotor += sub;
                    printf("- ");
                    cetak_nama_minuman(i);
                    printf("  x%d  = Rp %d\n", pesanan_minuman[i], sub);
                }
            }

            nominal_diskon = (total_kotor * diskon_terpakai) / 100;
            total_bayar = total_kotor - nominal_diskon;

            printf("--------------------------------------------------------------------\n");
            printf("Subtotal Kotor      : Rp %d\n", total_kotor);
            printf("Potongan Diskon     : Rp %d (%d%%)\n", nominal_diskon, diskon_terpakai);
            printf("TOTAL TAGIHAN       : Rp %d\n", total_bayar);
            cetak_garis();

            int bayar_sukses = 0;
            while (bayar_sukses == 0) {
                printf("Masukkan Nominal Uang Pembayaran: Rp ");
                if (scanf("%d", &uang_bayar) != 1) break;

                if (uang_bayar >= total_bayar) {
                    kembalian = uang_bayar - total_bayar;
                    printf("\n====================================================================\n");
                    printf("UANG DITERIMA       : Rp %d\n", uang_bayar);
                    printf("UANG KEMBALIAN      : Rp %d\n", kembalian);
                    printf("STATUS PEMBAYARAN   : LUNAS [TERIMA KASIH]\n");
                    printf("====================================================================\n\n");

                    /* Rekap pesanan ke data menu yang terjual */
                    for (i = 0; i < 5; i++) {
                        terjual_makanan[i] += pesanan_makanan[i];
                        terjual_minuman[i] += pesanan_minuman[i];
                    }

                    bayar_sukses = 1;
                } else {
                    printf("[UANG KURANG] Pembayaran kurang sebesar Rp %d!\n", total_bayar - uang_bayar);
                    printf("Silakan masukkan nominal uang yang cukup.\n\n");
                }
            }

            halaman = 13; /* Menuju Page 13: Rating */
        }

        /* =========================================================
           PAGE 13: RATING
           - User menginputkan rating 1 - 5 ke restoran
           - Rating akan ditampilkan di dashboard
           ========================================================= */
        else if (halaman == 13) {
            cetak_garis();
            printf("                      RATING RESTORAN\n");
            cetak_garis();
            printf("Bagaimana kepuasan Anda menikmati sajian Restoran Nusantara?\n");
            printf("Berikan penilaian Anda (Skala 1 - 5 Bintang):\n");
            printf("1 : Sangat Kecewa\n");
            printf("2 : Kurang Puas\n");
            printf("3 : Cukup Puas\n");
            printf("4 : Puas / Enak\n");
            printf("5 : Sangat Puas / Istimewa\n\n");

            int rating_valid = 0;
            while (rating_valid == 0) {
                printf("Masukkan Skor Rating Anda (1-5): ");
                if (scanf("%d", &rating_baru) != 1) break;

                if (rating_baru >= 1 && rating_baru <= 5) {
                    rating_valid = 1;
                } else {
                    printf("[PERINGATAN] Rating hanya boleh angka antara 1 sampai 5!\n");
                }
            }

            /* Simpan rating baru ke array riwayat */
            rating_riwayat[jumlah_rating] = rating_baru;
            jumlah_rating++;

            printf("\n[TERIMA KASIH] Penilaian bintang %d Anda telah berhasil disimpan!\n", rating_baru);
            printf("Rating restoran pada Dashboard otomatis diperbarui.\n\n");

            halaman = 14; /* Menuju Page 14: Penutup */
        }

        /* =========================================================
           PAGE 14: PENUTUP
           - Menampilkan terima kasih kepada pelanggan
           - Pilihan untuk pesan lagi atau dipaksa ke dashboard
           ========================================================= */
        else if (halaman == 14) {
            cetak_garis();
            printf("                 TERIMA KASIH ATAS KUNJUNGAN ANDA\n");
            cetak_garis();
            printf("Restoran Nusantara mengucapkan terima kasih atas kunjungan Anda.\n");
            printf("Kami selalu siap menyajikan hidangan nusantara terbaik untuk Anda!\n\n");
            printf("Pilihan Selanjutnya:\n");
            printf("1. Pesan Lagi (Buka Keranjang Belanja Baru)\n");
            printf("2. Selesai (Logout dan Kembali ke Dashboard Utama)\n");
            printf("Pilih opsi (1-2): ");
            if (scanf("%d", &pilihan) != 1) break;

            /* Reset keranjang pesanan */
            for (i = 0; i < 5; i++) {
                pesanan_makanan[i] = 0;
                pesanan_minuman[i] = 0;
            }
            diskon_terpakai = 0;
            tipe_layanan = 1;

            if (pilihan == 1) {
                printf("\nMenyiapkan keranjang baru...\n\n");
                halaman = 6; /* Kembali ke Page 6: Menu Makanan */
            } else {
                printf("\nSesi selesai. Anda dialihkan kembali ke Dashboard...\n\n");
                user_aktif = -1; /* Logout otomatis */
                halaman = 1;    /* Kembali ke Page 1: Dashboard */
            }
        }
    }

    return 0;
}
