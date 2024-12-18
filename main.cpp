#include "hotel.hpp"

int main() {
    ListKamar L;
    createListKamar(L);
    bool mainMenu = false;
    int pilihan,pilihan2;
    insertDummyData(L);
    while (!mainMenu) {
        clearTerminal();
        printAll(L);
        menu();
        cin >> pilihan;
        mainMenu = pilihan == 0;
        if (pilihan == 1) { // Tambah Kamar
            insertKamar(L);
        } else if (pilihan == 2) { // Tambah Pelanggan
            insertPelanggan(L);
        } else if (pilihan == 3) { // Edit Kamar
            editKamar(L);
        } else if (pilihan == 4) { // Edit Pelanggan
            editPelanggan(L);
        } else if (pilihan == 5) { // Total Transaksi
            totalTransaksi(L);
        }else if (pilihan == 6) { // Cari Pelanggan atau kamar
            searchAll(L);
        } else if (pilihan == 7) { // Hapus Kamar bersama childnya
            deleteKamar(L);
        } else if (pilihan == 8) { // Hapus Pelanggan
            deletePelanggan(L);
        } else if (pilihan == 9){
            printKamar(L);
        }
    };

    cout << "Terima kasih telah menggunakan program ini!" << endl;
    return 0;
}
