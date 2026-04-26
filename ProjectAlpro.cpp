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

//fungsi tambah barang
void tambahBarang() {
    barang *baru = new barang();

    cout << "\n--- TAMBAH BARANG BARU ---\n";
    cout << "ID Barang  : "; cin >> baru->id;

    // Cek duplikat ID
    barang *cek = head;
    while (cek != NULL) {
        if (cek->id == baru->id) {
            cout << "ID sudah digunakan!\n";
            delete baru;
            return;
        }
        cek = cek->next;
    }

    cin.ignore();
    cout << "Nama Barang: "; cin.getline(baru->nama, 50);
    cout << "Stok       : "; cin >> baru->stok;
    cout << "Harga      : "; cin >> baru->harga;

    baru->next = head;
    head = baru;
    cout << "Barang berhasil ditambahkan!\n";
}

//fungsi menampilkan barang
void tampilBarang() {
    if (head == NULL) {
        cout << "\nGudang kosong!\n";
        return;
    }

    cout << "\n";
    garis();
    cout << left
         << setw(6)  << "ID"
         << setw(22) << "NAMA BARANG"
         << setw(10) << "STOK"
         << setw(15) << "HARGA (Rp)"
         << endl;
    garis();

    barang *temp = head;
    while (temp != NULL) {
        cout << left
             << setw(6)  << temp->id
             << setw(22) << temp->nama
             << setw(10) << temp->stok
             << "Rp " << fixed << setprecision(2) << temp->harga
             << endl;
        temp = temp->next;
    }
    garis();
}

//fungsi cari barang
void cariBarang() {
    cout << "\n--- CARI BARANG ---\n";
    cout << "1. Cari berdasarkan ID\n";
    cout << "2. Cari berdasarkan Nama\n";
    cout << "Pilih: ";
    int opsi; cin >> opsi;

    if (opsi == 1) {
        // sequential search berdasarkan ID
        int idCari;
        cout << "Masukkan ID: "; cin >> idCari;

        barang *temp = head;
        bool ketemu = false;
        int posisi = 1;

        while (temp != NULL) {
            if (temp->id == idCari) {
                ketemu = true;
                cout << "\nBarang ditemukan di posisi node ke-" << posisi << ":\n";
                garis();
                cout << "ID    : " << temp->id << endl;
                cout << "Nama  : " << temp->nama << endl;
                cout << "Stok  : " << temp->stok << endl;
                cout << "Harga : Rp " << fixed << setprecision(2) << temp->harga << endl;
                garis();
                break;
            }
            temp = temp->next;
            posisi++;
        }
        if (!ketemu) cout << " Barang dengan ID " << idCari << " tidak ditemukan.\n";
        } else if (opsi == 2) {
        // linear search berdasarkan nama
        char namaCari[50];
        cin.ignore();
        cout << "Masukkan Nama: "; cin.getline(namaCari, 50);

        // Konversi ke lowercase untuk perbandingan
        char namaLower[50];
        strcpy(namaLower, namaCari);
        for (int i = 0; namaLower[i]; i++) namaLower[i] = tolower(namaLower[i]);

        barang *temp = head;
        bool ketemu = false;
        cout << "\nHasil pencarian \"" << namaCari << "\":\n";
        garis();

        while (temp != NULL) {
            char tempLower[50];
            strcpy(tempLower, temp->nama);
            for (int i = 0; tempLower[i]; i++) tempLower[i] = tolower(tempLower[i]);

            if (strstr(tempLower, namaLower) != NULL) {
                ketemu = true;
                cout << left
                     << setw(6)  << temp->id
                     << setw(22) << temp->nama
                     << setw(10) << temp->stok
                     << "Rp " << fixed << setprecision(2) << temp->harga
                     << endl;
            }
            temp = temp->next;
        }
        garis();
        if (!ketemu) cout << "Barang tidak ditemukan.\n";
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}


int main() {
    
    int pilih;
 
        menu();
        cout << "  Pilih menu: ";
        cin >> pilih;
        cout << endl;

        switch (pilih) {
            case 1: tambahBarang();  break;
            case 2: tampilBarang();  break;
            case 3: cariBarang();    break;
          
                break;
            default:
                cout << "Menu tidak tersedia.\n";
        }
        cout << endl;

}
