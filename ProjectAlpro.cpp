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

        // konversi ke lowercase untuk perbandingan
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

//      QUICK SORT UNTUK HARGA (ARRAY POINTER)

void swapData(barang *a, barang *b) {
    int  tmpId   = a->id;    a->id   = b->id;    b->id   = tmpId;
    int  tmpStok = a->stok;  a->stok = b->stok;  b->stok = tmpStok;
    float tmpHrg = a->harga; a->harga = b->harga; b->harga = tmpHrg;

    char tmpNama[50];
    strcpy(tmpNama, a->nama);
    strcpy(a->nama, b->nama);
    strcpy(b->nama, tmpNama);
}

int partitionHarga(barang *arr[], int low, int high) {
    float pivot = arr[high]->harga;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j]->harga < pivot) {
            i++;
            barang *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    barang *temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSortHarga(barang *arr[], int low, int high) {
    if (low < high) {
        int pi = partitionHarga(arr, low, high);
        quickSortHarga(arr, low, pi - 1);
        quickSortHarga(arr, pi + 1, high);
    }
}

void sortingBarang() {
    if (head == NULL || head->next == NULL) {
        cout << "[!] Data tidak cukup untuk diurutkan.\n";
        return;
    }

    cout << "\n--- SORTING BARANG ---\n";
    cout << "Urutkan berdasarkan:\n";
    cout << "1. Nama (A-Z) -> Bubble Sort\n";
    cout << "2. Harga (Termurah - Termahal) -> Quick Sort\n";
    cout << "3. Stok (Terbanyak - Tersedikit) -> Bubble Sort\n";
    cout << "Pilih: ";
    int opsi; cin >> opsi;

    if (opsi == 1 || opsi == 3) {
    
        // BUBBLE SORT
    
        bool swapped;
        do {
            swapped = false;
            barang *current = head;

            while (current->next != NULL) {
                bool perluSwap = false;

                if (opsi == 1 && strcmp(current->nama, current->next->nama) > 0)
                    perluSwap = true;
                else if (opsi == 3 && current->stok < current->next->stok)
                    perluSwap = true;

                if (perluSwap) {
                    swapData(current, current->next);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);

        cout << "[+] Data berhasil diurutkan dengan Bubble Sort!\n";
    }

    else if (opsi == 2) {
    
        // QUICK SORT HARGA

        // hitung jumlah node
        int n = 0;
        barang *temp = head;
        while (temp != NULL) {
            n++;
            temp = temp->next;
        }

        // pindahkan pointer node ke array
        barang *arr[100];
        temp = head;
        int i = 0;
        while (temp != NULL) {
            arr[i++] = temp;
            temp = temp->next;
        }

        // quick sort array pointer
        quickSortHarga(arr, 0, n - 1);

        // susun ulang data linked list sesuai array
        for (int i = 0; i < n - 1; i++) {
            swapData(arr[i], arr[i]); 
        }


        for (int i = 0; i < n; i++) {
            for (barang *cek = head; cek != NULL; cek = cek->next) {
                if (cek == arr[i]) {
                    if (cek != arr[i]) swapData(cek, arr[i]);
                }
            }
        }

        
        barang tempData[100];
        for (int i = 0; i < n; i++) {
            tempData[i] = *arr[i];
        }

        temp = head;
        i = 0;
        while (temp != NULL) {
            temp->id = tempData[i].id;
            strcpy(temp->nama, tempData[i].nama);
            temp->stok = tempData[i].stok;
            temp->harga = tempData[i].harga;
            temp = temp->next;
            i++;
        }

        cout << "[+] Data berhasil diurutkan dengan Quick Sort!\n";
    }

    else {
        cout << "[!] Pilihan tidak valid.\n";
        return;
    }

    tampilBarang();
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
            case 4: sortingBarang(); break;
          
                break;
            default:
                cout << "Menu tidak tersedia.\n";
        }
        cout << endl;

}
