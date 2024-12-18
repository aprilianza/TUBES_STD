#include "hotel.hpp"
void createListKamar(ListKamar &L){
    // Inisial state: List kamar belum terdefinisi.
    // Final state: List kamar sudah terinisialisasi dengan elemen pertama dan terakhir NULL.
    FirstKamar(L) = NULL;
    LastKamar(L) = NULL;
};
void createElementKamar(AdrKamar &p, int noKamar, int harga, string jenisKamar) {
    // Inisial state: Pointer `p` belum teralokasi.
    // Final state: Pointer `p` teralokasi dengan nilai properti `noKamar`, `harga`, dan `jenisKamar`.
    p = new kamar;
    noKamar(p) = noKamar;
    harga(p) = harga;
    jenisKamar(p) = jenisKamar;
    next(p) = NULL;
    prev(p) = NULL;
};
void insertLastKamar(ListKamar &L, AdrKamar p){
    // Inisial state: List kamar mungkin kosong atau sudah memiliki elemen.
    // Final state: Elemen baru ditambahkan ke akhir list.
    if(FirstKamar(L) == NULL){
        FirstKamar(L) = p;
        LastKamar(L) = p;
    }else{
        next(LastKamar(L)) = p;
        prev(p) = LastKamar(L);
        LastKamar(L) = p;
    }
};

void printKamar(ListKamar L) {
    // Inisial state: List kamar mungkin kosong atau berisi elemen.
    // Final state: Semua elemen list kamar dicetak ke layar.
    bool menu = true;
    char pilihan;
    while (menu) {
        cout << "\n";
        cout << "==========================================================" << endl;
        cout << "                       DAFTAR KAMAR                      " << endl;
        cout << "==========================================================" << endl;

        AdrKamar p = FirstKamar(L);
        if (p != NULL) {
            while (p != NULL) {
                cout << "  No Kamar      : " << noKamar(p) << endl;
                cout << "----------------------------------------------------------" << endl;
                cout << "  Harga         : " << harga(p) << " IDR" << endl;
                cout << "  Jenis Kamar   : " << jenisKamar(p) << endl;
                cout << "==========================================================" << endl;
                p = next(p);
            }
        } else {
            cout << "List kamar kosong." << endl;
            cout << "==========================================================" << endl;
        }

        cout << "Tekan X untuk keluar: ";
        cin >> pilihan;
        if (pilihan == 'X' || pilihan == 'x') {
            menu = false;
        }
    }
}

void printAll(ListKamar L) {
    // Inisial state: List kamar mungkin kosong atau berisi elemen.
    // Final state: Semua elemen list kamar dan pelanggan yang terkait dicetak ke layar.
    cout << "\n";
    cout << "==========================================================" << endl;
    cout << "                    DAFTAR KAMAR DAN PELANGGAN            " << endl;
    cout << "==========================================================" << endl;

    AdrKamar p = FirstKamar(L);
    if (p != NULL) {
        while (p != NULL) {
            cout << "  No Kamar      : " << noKamar(p) << endl;
            cout << "----------------------------------------------------------" << endl;
            cout << "  Harga         : " << harga(p) << " IDR" << endl;
            cout << "  Jenis Kamar   : " << jenisKamar(p) << endl;

            AdrPelanggan q = FirstPelanggan(p);
            if (q == NULL) {
                cout << "  Pelanggan     : Tidak ada pelanggan." << endl;
            } else {
                cout << "  Pelanggan     :" << endl;
                while (q != NULL) {
                    char buffer[20];
                    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&tanggalCheckIn(q)));
                    cout << "    - ID Booking: " << idBooking(q) << endl;
                    cout << "      Nama      : " << nama(q) << endl;
                    cout << "      Check-In  : " << buffer << endl;

                    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&tanggalCheckOut(q)));
                    cout << "      Check-Out : " << buffer << endl;
                    q = next(q);
                }
            }
            cout << "==========================================================" << endl;
            p = next(p);
        }
    } else {
        cout << "Tidak ada kamar dalam daftar." << endl;
        cout << "==========================================================" << endl;
    }
}

void createPelanggan(AdrPelanggan &p, string nama, time_t tanggalCheckIn, time_t tanggalCheckOut, string idBooking) {
    // Inisial state: Pointer `p` belum teralokasi.
    // Final state: Pointer `p` teralokasi dengan data pelanggan.
    // Mengonversi string tanggal ke time_t
    p = new pelanggan;
    idBooking(p) = idBooking;
    nama(p) = nama;
    tanggalCheckIn(p) = tanggalCheckIn;
    tanggalCheckOut(p) = tanggalCheckOut;
    next(p) = NULL;
};

void insertLastPelanggan(AdrKamar &p, AdrPelanggan q){
    // Inisial state: Pelanggan pada kamar `p` mungkin kosong atau berisi elemen.
    // Final state: Elemen pelanggan baru ditambahkan ke akhir list pelanggan di kamar.
    if(FirstPelanggan(p) == NULL){
        FirstPelanggan(p) = q;
    }else{
        AdrPelanggan x = FirstPelanggan(p);
        while (next(x) != NULL) {
            x = next(x);
        }
        next(x) = q;
    }
};
void editPelanggan(ListKamar &L) {
    // Input data pelanggan baru
    time_t newCheckIn, newCheckOut;
    string idBooking, nama, tanggalCheckIn, tanggalCheckOut;
    bool pelangganDitemukan = false;
    bool menu = true;
    char pilihan;
    AdrKamar p = FirstKamar(L);

    while(menu){
        cout << "Masukkan Id Booking: ";
        cin >> idBooking;

        while (p != NULL && !pelangganDitemukan) {
            AdrPelanggan q = FirstPelanggan(p);
            while (q != NULL && !pelangganDitemukan) {
                if (idBooking(q) == idBooking) {
                    pelangganDitemukan = true;
                    cout << "Masukkan Nama Pelanggan Baru: ";
                    cin >> nama;
                    cout << "Masukkan Tanggal Check-In Baru (YYYY-MM-DD): ";
                    cin >> tanggalCheckIn;
                    cout << "Masukkan Tanggal Check-Out Baru (YYYY-MM-DD): ";
                    cin >> tanggalCheckOut;

                    // Konversi tanggal menjadi struct tm
                    struct tm tmCheckIn = {}, tmCheckOut = {};
                    strptime(tanggalCheckIn.c_str(), "%Y-%m-%d", &tmCheckIn);
                    strptime(tanggalCheckOut.c_str(), "%Y-%m-%d", &tmCheckOut);

                    // Konversi struct tm ke time_t
                    newCheckIn = mktime(&tmCheckIn);
                    newCheckOut = mktime(&tmCheckOut);

                    // Validasi dan ubah data jika valid
                    if (insertPelangganValidation(p, newCheckIn, newCheckOut,idBooking)) {
                        nama(q) = nama;
                        tanggalCheckIn(q) = newCheckIn;
                        tanggalCheckOut(q) = newCheckOut;
                        cout << "Data pelanggan berhasil diubah." << endl;
                    }
                }
                q = next(q);
            }
            p = next(p);
        }
        if (!pelangganDitemukan) {
            cout << "Error: Data pelanggan dengan Id Booking tersebut tidak ditemukan." << endl;
        }
        cout << "Tekan X untuk keluar: ";
        cin >> pilihan;
        if (pilihan == 'X' || pilihan == 'x') {
            menu = false;
        }
    }

}

void editKamar(ListKamar &L){
    // Inisial state: List kamar mungkin kosong atau berisi elemen.
    // Final state: Elemen kamar tertentu di list diubah sesuai input dari pengguna.
    int noKamar, harga;
    string jenisKamar;
    AdrKamar p;
    char pilihan;
    bool menu = true;
    while(menu){
        cout << "Masukkan No Kamar: ";
        cin >> noKamar;
        p = searchKamar(L, noKamar);
        if (p != NULL) {
            cout << "Masukkan Harga: ";
            cin >> harga;
            cout << "Masukkan Jenis Kamar: ";
            cin >> jenisKamar;
            harga(p) = harga;
            jenisKamar(p) = jenisKamar;
            cout << "Data kamar berhasil diubah." << endl;
        }else{
            cout << "Data kamar tidak ditemukan." << endl;
        }
        cout << "Tekan X untuk keluar: ";
        cin >> pilihan;
        if (pilihan == 'X' || pilihan == 'x') {
            menu = false;
        }
    }
};
void totalTransaksi(ListKamar L){
    // Inisial state: Data transaksi di dalam list kamar belum dihitung.
    // Final state: Total transaksi seluruh kamar dicetak ke layar.
    bool menu = false;
    string pilihan;
    AdrKamar p = FirstKamar(L);
    int total = 0;
    while (p != NULL) {
        AdrPelanggan q = FirstPelanggan(p);
        while (q != NULL) {
            int days = difftime(tanggalCheckOut(q), tanggalCheckIn(q)) / (60 * 60 * 24);
            total += harga(p) * days;
            q = next(q);
        }
        p = next(p);
    }
    cout << "Total Transaksi: " << total << endl;
    while (!menu) {
        cout << "Masukkan X untuk keluar : ";
        cin >> pilihan;
        if (pilihan == "X" || pilihan == "x") {
            menu = true;
        }
    }
};
void deleteFirstKamar(ListKamar &L, AdrKamar &p){
    // Inisial state: Elemen pertama mungkin ada atau kosong.
    // Final state: Elemen pertama dihapus dari list kamar.
    if(FirstKamar(L) == NULL){
        cout << "List Kamar Kosong" << endl;
    }else{
        if (FirstKamar(L) == LastKamar(L)) {
            p = FirstKamar(L);
            FirstKamar(L) = NULL;
            LastKamar(L) = NULL;
        }else{
            p = FirstKamar(L);
            FirstKamar(L) = next(p);
            next(p) = NULL;
            prev(next(p)) = NULL;
        }
        delete p;
    }
};
void deleteAfterKamar(ListKamar &L, AdrKamar prec, AdrKamar &p){
    // Inisial state: List kamar berisi elemen yang memiliki `prec` sebagai elemen sebelumnya.
    // Final state: Elemen setelah `prec` dihapus.
    if(FirstKamar(L) == NULL){
        cout << "List Kamar Kosong" << endl;
    }else{
        p = next(prec);
        next(prec) = next(p);
        prev(next(p)) = prec;
        next(p) = NULL;
        prev(p) = NULL;
    }
    delete p;
};
void deleteLastKamar(ListKamar &L, AdrKamar &p){
    // Inisial state: List kamar berisi elemen.
    // Final state: Elemen terakhir dihapus.
    if(FirstKamar(L) == NULL){
        cout << "List Kamar Kosong" << endl;
    }else{
        if (FirstKamar(L) == LastKamar(L)) {
            p = FirstKamar(L);
            FirstKamar(L) = NULL;
            LastKamar(L) = NULL;
        }else{
            p = LastKamar(L);
            LastKamar(L) = prev(p);
            next(prev(p)) = NULL;
            prev(p) = NULL;
        }
        delete p;
    }
};
AdrKamar searchKamar(ListKamar L, int noKamar){
    // Inisial state: Elemen kamar dengan nomor tertentu mungkin ada atau tidak.
    // Final state: Status ditemukan atau tidak dicetak ke layar, dan informasi kamar dicetak jika ditemukan.
    AdrKamar p = FirstKamar(L);
    while(p != NULL){
        if(noKamar(p) == noKamar){
            return p;
        }
        p = next(p);
    }
    return p;
};

void searchPelanggan(ListKamar k){
    // Inisial state: Elemen pelanggan dengan data tertentu mungkin ada atau tidak.
    // Final state: Status ditemukan atau tidak dicetak ke layar, dan informasi pelanggan dicetak jika ditemukan.
    int noKamar;
    char pilihan;
    bool menu = true;
    string idBooking;
    cout << "Masukkan Nomor Kamar: ";
    cin >> noKamar;

    AdrKamar p = searchKamar(k, noKamar);
    if (p == NULL) {
        cout << "Data Kamar Tidak Ditemukan" << endl;
    } else {
        cout << "Masukkan Id Booking: ";
        cin >> idBooking;
        AdrPelanggan pelanggan = FirstPelanggan(p);
        bool found = false;
        while (pelanggan != NULL) {
                if (idBooking(pelanggan) == idBooking) {
                    found = true;
                    char buffer[20];
                    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&tanggalCheckIn(pelanggan)));
                    cout << "=================================================" << endl;
                    cout << "Id booking: " << idBooking(pelanggan) << endl;
                    cout << "Nama: " << nama(pelanggan) << endl;
                    cout << "Check-In: " << buffer << endl;

                    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&tanggalCheckOut(pelanggan)));
                    cout << "Check-Out: " << buffer << endl;
                    cout << "=================================================" << endl;
                }
                pelanggan = next(pelanggan);
        }

        if (!found) {
                cout << "Data Pelanggan Tidak Ditemukan" << endl;
        }
    }


};
void menu() {
    // Inisial state: Menu belum ditampilkan.
    // Final state: Menu ditampilkan untuk memberi tahu pengguna daftar pilihan.
    cout << "\n";
    cout << "==========================================================" << endl;
    cout << "                       HOTEL CALIFORNIA                   " << endl;
    cout << "==========================================================" << endl;
    cout << "| 1. Tambah Kamar         | 6. Cari Pelanggan / Kamar    |" << endl;
    cout << "| 2. Tambah Pelanggan     | 7. Hapus Kamar               |" << endl;
    cout << "| 3. Edit Kamar           | 8. Hapus Pelanggan           |" << endl;
    cout << "| 4. Edit Pelanggan       | 9. Lihat List Kamar          |" << endl;
    cout << "| 5. Total Transaksi      | 0. Keluar                    |" << endl;
    cout << "==========================================================" << endl;
    cout << "Pilihan Anda: ";
}

void insertPelanggan(ListKamar &L){
    // Inisial state: List kamar dan data pelanggan mungkin ada atau tidak.
    // Final state: Data pelanggan baru ditambahkan ke kamar tertentu jika kamar ditemukan.
    AdrPelanggan pelanggan;
    char pilihan;
    bool menu = true;
    int noKamar;
    string nama, checkIn, checkOut, idBooking;
    AdrKamar kamar;
    while (menu) {
        cout << "Masukkan No Kamar: ";
        cin >> noKamar;
        kamar = searchKamar(L, noKamar);
        if (kamar != NULL) {
            cout << "Masukkan Id Booking: ";
            cin >> idBooking;
            if (checkidBooking(L, idBooking) == false) {
                cout << "Id Booking sudah ada." << endl;
            }else{
                cout << "Masukkan Nama Pelanggan: ";
                cin >> nama;
                cout << "Masukkan Tanggal Check-In (YYYY-MM-DD): ";
                cin >> checkIn;
                cout << "Masukkan Tanggal Check-Out (YYYY-MM-DD): ";
                cin >> checkOut;
                struct tm tmCheckIn = {}, tmCheckOut = {};
                strptime(checkIn.c_str(), "%Y-%m-%d", &tmCheckIn);
                strptime(checkOut.c_str(), "%Y-%m-%d", &tmCheckOut);
                if (insertPelangganValidation(kamar, mktime(&tmCheckIn), mktime(&tmCheckOut), idBooking) == true) {
                    createPelanggan(pelanggan, nama, mktime(&tmCheckIn), mktime(&tmCheckOut),idBooking);
                    insertLastPelanggan(kamar, pelanggan);
                    cout << "Data pelanggan berhasil ditambahkan." << endl;
                }
            }
        } else {
            cout << "Kamar tidak ditemukan." << endl;
        }
        cout << "Ingin menambahkan data pelanggan lagi? (y/n): ";
        cin >> pilihan;
        if (pilihan == 'n' || pilihan == 'N') {
            menu = false;
        }
    }

};
bool insertPelangganValidation(AdrKamar p, time_t tanggalCheckIn, time_t tanggalCheckOut, string idBooking) {
    // Mendapatkan waktu sekarang
    time_t now = time(0);
    struct tm* localTime = localtime(&now);
    now = mktime(localTime); // Normalisasi waktu sekarang ke format tanpa detik
    if (tanggalCheckIn >= tanggalCheckOut){
        cout << "Tanggal check-out harus lebih besar dari tanggal check-in." << endl;
        return false;
    }
    // Pastikan tanggal check-in baru tidak di masa lalu
    if (difftime(tanggalCheckIn, now) < 0) {
        cout << "Tanggal check-in tidak valid (tidak bisa di masa lalu)." << endl;
        return false;
    }
    // Validasi idBooking unik
    AdrPelanggan q = FirstPelanggan(p);
    while (q != NULL) {
        if (idBooking(q) == idBooking) {
            cout<< "";
        }else{
            if ((tanggalCheckIn >= tanggalCheckIn(q) && tanggalCheckIn < tanggalCheckOut(q))) {
                cout << "Tanggal check-in berbenturan dengan pelanggan lain (id booking: "
                     << idBooking(q) << ")." << endl;
                return false;
            }
            if ((tanggalCheckOut > tanggalCheckIn(q) && tanggalCheckOut <= tanggalCheckOut(q))) {
                cout << "Tanggal check-out berbenturan dengan pelanggan lain (id booking: "
                     << idBooking(q) << ")." << endl;
                return false;
            }
        }
        q = next(q);
    }

    return true;
}


void insertKamar(ListKamar &L){
    // Inisial state: List kamar mungkin kosong atau sudah memiliki elemen.
    // Final state: Elemen kamar baru ditambahkan ke list berdasarkan input dari pengguna.
    AdrKamar p;
    char pilihan;
    int noKamar, harga;
    string jenisKamar;
    bool menu = true;
    while (menu) {
        cout << "Masukkan No Kamar: ";
        cin >> noKamar;
        if (searchKamar(L, noKamar) != NULL) {
            cout << "No kamar sudah ada. Gunakan no kamar yang berbeda." << endl;
        }else{
            cout << "Masukkan Harga: ";
            cin >> harga;
            cout << "Masukkan Jenis Kamar: ";
            cin >> jenisKamar;
            createElementKamar(p, noKamar, harga, jenisKamar);
            insertLastKamar(L, p);
            cout << "Data kamar berhasil ditambahkan." << endl;
        }
        cout << "Ingin menambahkan data kamar lagi? (y/n): ";
        cin >> pilihan;
        if (pilihan == 'n' || pilihan == 'N') {
            menu = false;
        }
    }

};


void deleteKamar(ListKamar &L){
    // Inisial state: List kamar berisi elemen.
    // Final state: Elemen kamar terakhir dihapus.
    AdrKamar p;
    AdrPelanggan q;
    bool menu = true;
    char pilihan;
    int noKamar;

    while (menu) {
        cout << "Masukkan No Kamar: ";
        cin >> noKamar;
        p = searchKamar(L, noKamar);
        if (p != NULL) {
            q = FirstPelanggan(p);
            while (q != NULL) {
                deleteFirstPelanggan(p, q);
                q = FirstPelanggan(p);
            }
            if (next(p) == NULL) {
                deleteLastKamar(L, p);
            } else if (prev(p) == NULL) {
                deleteFirstKamar(L, p);
            }else{
                deleteAfterKamar(L, prev(p), p);
            }
            cout << "Data kamar berhasil dihapus." << endl;
        } else {
            cout << "Kamar tidak ditemukan." << endl;
        }
        cout << "Ingin menghapus data kamar lagi? (y/n): ";
        cin >> pilihan;
        if (pilihan == 'n' || pilihan == 'N') {
            menu = false;
        }
    }

};

void deleteFirstPelanggan(AdrKamar &p, AdrPelanggan &q) {
    q = FirstPelanggan(p);
    if (q != NULL) {
        FirstPelanggan(p) = next(q);
        next(q) = NULL;
        delete q;
    } else {
        cout << "Data Pelanggan Kosong." << endl;
    }
}

void deleteAfterPelanggan(AdrKamar &p, AdrPelanggan prec, AdrPelanggan &q) {
    q = next(prec);
    if (q != NULL) {
        next(prec) = next(q);
        next(q) = NULL;
        delete q;
    } else {
        cout << "Data Pelanggan Kosong." << endl;
    }
}

void deleteLastPelanggan(AdrKamar &p, AdrPelanggan &q) {
    q = FirstPelanggan(p);
    if (q != NULL) {
        if (next(q) == NULL) {
            deleteFirstPelanggan(p, q); 
        } else {
            AdrPelanggan prev = q;
            q = next(q);
            while (next(q) != NULL) {
                prev = q;
                q = next(q);
            }
            next(prev) = NULL;
            delete q;
        }
    } else {
        cout << "Data Pelanggan Kosong." << endl;
    }
}

void deletePelanggan(ListKamar &L) {
    AdrKamar p;
    AdrPelanggan q;
    int noKamar;
    string idBooking;
    bool menu = true;
    char pilihan;

    while (menu) {
        cout << "Masukkan No Kamar: ";
        cin >> noKamar;
        p = searchKamar(L, noKamar);
        if (p != NULL) {
            cout << "Masukkan Id Booking: ";
            cin >> idBooking;
            q = searchPelangganonKamar(p, idBooking);
            if (q != NULL) {
                if (q == FirstPelanggan(p)) {
                    deleteFirstPelanggan(p, q);
                }
                else if (next(q) == NULL) {
                    deleteLastPelanggan(p, q);
                }
                else {
                    AdrPelanggan prev = FirstPelanggan(p);
                    while (next(prev) != q) {
                        prev = next(prev);
                    }
                    deleteAfterPelanggan(p, prev, q);
                }
                cout << "Data pelanggan berhasil dihapus." << endl;
            } else {
                cout << "Data Pelanggan Tidak Ditemukan." << endl;
            }
        } else {
            cout << "Kamar tidak ditemukan." << endl;
        }
        cout << "Ingin menghapus data pelanggan lagi? (y/n): ";
        cin >> pilihan;
        if (pilihan == 'n' || pilihan == 'N') {
            menu = false;
        }
    }
}

AdrPelanggan searchPelangganonKamar(AdrKamar p, string idBooking){
    AdrPelanggan q = FirstPelanggan(p);
    while (q != NULL) {
        if (idBooking(q) == idBooking) {
            return q;
        }
        q = next(q);
    }
    return NULL;
};

bool checkidBooking(ListKamar L, string idBooking) {
    AdrKamar p = FirstKamar(L);
    while (p != NULL) {
        AdrPelanggan q = FirstPelanggan(p);
        while (q != NULL) {
            if (idBooking(q) == idBooking) {
                return false;
            }
            q = next(q);
        }
        p = next(p);
    }
    return true;
};


void insertDummyData(ListKamar &L) {
    // Inisial state: List kamar kosong atau berisi elemen.
    // Final state: List kamar diisi dengan data dummy untuk keperluan pengujian.

    AdrKamar kamar;
    AdrPelanggan pelanggan;

    // Data dummy kamar
    createElementKamar(kamar, 101, 500000, "Deluxe");
    insertLastKamar(L, kamar);

    createElementKamar(kamar, 102, 750000, "Suite");
    insertLastKamar(L, kamar);

    createElementKamar(kamar, 103, 300000, "Standard");
    insertLastKamar(L, kamar);

    createElementKamar(kamar, 104, 400000, "Superior");
    insertLastKamar(L, kamar);

    createElementKamar(kamar, 105, 600000, "Executive");
    insertLastKamar(L, kamar);

    // Data dummy pelanggan
    time_t checkIn, checkOut;
    struct tm tmDate = {};

    // Pelanggan untuk kamar 101
    strptime("2025-01-10", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-01-15", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Joko Santoso", checkIn, checkOut, "A001");
    AdrKamar p = searchKamar(L, 101);
    insertLastPelanggan(p, pelanggan);

    strptime("2025-01-20", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-01-25", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Agus Wirawan", checkIn, checkOut, "A002");
    p = searchKamar(L, 101);
    insertLastPelanggan(p, pelanggan);



    // Pelanggan untuk kamar 102
    strptime("2025-03-10", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-03-15", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Bima Putra", checkIn, checkOut, "B001");
    p = searchKamar(L, 102);
    insertLastPelanggan(p, pelanggan);

    strptime("2025-03-20", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-03-25", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Siti Aminah", checkIn, checkOut, "B002");
    p = searchKamar(L, 102);
    insertLastPelanggan(p, pelanggan);


    // Pelanggan untuk kamar 103
    strptime("2025-04-05", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-04-10", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Hari Prasetyo", checkIn, checkOut, "C001");
    p = searchKamar(L, 103);
    insertLastPelanggan(p, pelanggan);

    strptime("2025-04-15", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-04-20", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Rudi Hartono", checkIn, checkOut, "C002");
    p = searchKamar(L, 103);
    insertLastPelanggan(p, pelanggan);

    strptime("2025-04-25", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-04-30", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Nina Sari", checkIn, checkOut, "C003");
    p = searchKamar(L, 103);
    insertLastPelanggan(p, pelanggan);

    // Pelanggan untuk kamar 104
    strptime("2025-05-15", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-05-20", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Dewi Kartini", checkIn, checkOut, "D001");
    p = searchKamar(L, 104);
    insertLastPelanggan(p, pelanggan);

    strptime("2025-05-25", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-05-30", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Eko Saputra", checkIn, checkOut, "D002");
    p = searchKamar(L, 104);
    insertLastPelanggan(p, pelanggan);

    strptime("2025-06-05", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-06-10", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Sari Melati", checkIn, checkOut, "D003");
    p = searchKamar(L, 104);
    insertLastPelanggan(p, pelanggan);

    // Pelanggan untuk kamar 105
    strptime("2025-06-01", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-06-06", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Lina Aprilia", checkIn, checkOut, "E001");
    p = searchKamar(L, 105);
    insertLastPelanggan(p, pelanggan);

    strptime("2025-06-10", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-06-15", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Fahmi Rizky", checkIn, checkOut, "E002");
    p = searchKamar(L, 105);
    insertLastPelanggan(p, pelanggan);

    strptime("2025-06-20", "%Y-%m-%d", &tmDate);
    checkIn = mktime(&tmDate);
    strptime("2025-06-25", "%Y-%m-%d", &tmDate);
    checkOut = mktime(&tmDate);
    pelanggan = nullptr; 
    createPelanggan(pelanggan, "Rizky Aditya", checkIn, checkOut, "E003");
    p = searchKamar(L, 105);
    insertLastPelanggan(p, pelanggan);

}

void clearTerminal() {
    #ifdef _WIN32
        system("cls"); // Untuk Windows
    #else
        system("clear"); // Untuk macOS dan Linux
    #endif
}

void searchAll(ListKamar L){
    AdrKamar p;
    int noKamar;
    char pilihan2;
    bool menu = true;
    while (menu) {
        cout << "ketik K untuk cari kamar" << endl;
        cout << "ketik P untuk cari pelanggan" << endl;
        cout << "pilihan: ";
        cin >> pilihan2;
        if (pilihan2 == 'K' || pilihan2 == 'k') {
            cout << "Masukkan Nomor Kamar: ";
            cin >> noKamar;
            p = searchKamar(L, noKamar);
            if (p == NULL) {
                cout << "Data Kamar Tidak Ditemukan" << endl;
            } else {
                cout << "=========================================" << endl;
                cout << "No Kamar: " << noKamar << endl;
                cout << "Harga: " << harga(p) << endl;
                cout << "Jenis Kamar: " << jenisKamar(p) << endl;
                cout << "=========================================" << endl;
            }
        } else if (pilihan2 == 'P' || pilihan2 == 'p') {
            searchPelanggan(L);
        }
        cout << "Tekan X untuk keluar: ";
        cin >> pilihan2;
        if (pilihan2 == 'X' || pilihan2 == 'x') {
            menu = false;
        }
    }
};
