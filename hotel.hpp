#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;
#ifndef hotel_hpp
#define hotel_hpp
#define noKamar(k) k->noKamar
#define harga(k) k->harga
#define FirstKamar(k) k.FirstKamar
#define FirstPelanggan(k) k->FirstPelanggan
#define next(k) k->next
#define prev(k) k->prev
#define LastKamar(k) k.LastKamar
#define nama(p) p->nama
#define tanggalCheckIn(p) p->tanggalCheckIn
#define tanggalCheckOut(p) p->tanggalCheckOut
#define jenisKamar(k) k->jenisKamar
#define idBooking(p) p->idBooking
#include <stdio.h>

typedef struct kamar* AdrKamar;
typedef struct pelanggan* AdrPelanggan;

struct kamar{
    int noKamar;
    int harga;
    string jenisKamar;
    AdrPelanggan FirstPelanggan;
    AdrKamar next;
    AdrKamar prev;
};

struct pelanggan{
    string idBooking;
    string nama;
    time_t tanggalCheckIn, tanggalCheckOut;
    AdrPelanggan next;
};

struct ListKamar{
    AdrKamar FirstKamar;
    AdrKamar LastKamar;
};

void createListKamar(ListKamar &L);
void createElementKamar(AdrKamar &p, int noKamar, int harga, string jenisKamar);
void insertLastKamar(ListKamar &L, AdrKamar p);
void printAll(ListKamar L);
void printKamar(ListKamar L);
void createPelanggan(AdrPelanggan &p, string nama, time_t tanggalCheckIn, time_t tanggalCheckOut,string idBooking);
void insertLastPelanggan(AdrKamar &p, AdrPelanggan q);
void editPelanggan(ListKamar &L);
void editKamar(ListKamar &L);
void totalTransaksi(ListKamar L);
void deleteFirstKamar(ListKamar &L, AdrKamar &p);
void deleteAfterKamar(ListKamar &L, AdrKamar prec, AdrKamar &p);
void deleteLastKamar(ListKamar &L, AdrKamar &p);
void deleteFirstPelanggan(AdrKamar &p, AdrPelanggan &q);
void deleteAfterPelanggan(AdrKamar &p, AdrPelanggan prec, AdrPelanggan &q);
void deleteLastPelanggan(AdrKamar &p, AdrPelanggan &q);
AdrKamar searchKamar(ListKamar L, int noKamar);
void searchPelanggan(ListKamar L);
void menu();
void insertPelanggan(ListKamar &L);
void insertKamar(ListKamar &L);
bool insertPelangganValidation(AdrKamar p, time_t tanggalCheckIn, time_t tanggalCheckOut, string idBooking);
void deleteKamar(ListKamar &L);
AdrPelanggan searchPelangganonKamar(AdrKamar p, string idBooking);
bool insertKamarValidation(ListKamar L, int noKamar);
void deletePelanggan(ListKamar &L);
void insertDummyData(ListKamar &L);
bool checkidBooking(ListKamar L, string idBooking);
void clearTerminal();
void searchAll(ListKamar L);
#endif
