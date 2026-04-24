#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct barang {
    int id;
    char nama[50];
    int stok;
    float harga;
    
    barang *next;
};

//pointer
barang *head = NULL;

//fungsi garis tabel agar dapat dipanggil berulang kali
void garis() {
    cout << setfill('-') << setw(65) << "" << endl;
    cout << setfill(' ');
}

//fungsi menu 
void menu() {
    garis();
    cout << "SISTEM MANAJEMEN LOGISTIK & GUDANG" << endl;
    garis();
    cout << "  1. Tambah Barang" << endl;
    cout << "  2. Tampilkan Semua Barang" << endl;
    cout << "  3. Cari Barang" << endl;
    cout << "  4. Sorting Barang" << endl;
    cout << "  5. Transaksi (Keluar/Masuk Stok)" << endl;
    cout << "  6. Hapus Barang" << endl;
    cout << "  7. Simpan ke File" << endl;
    cout << "  8. Keluar" << endl;
    garis();
}

int main() {

}