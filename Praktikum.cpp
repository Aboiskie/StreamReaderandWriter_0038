#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <stdexcept>

using namespace std;

// ==============================
// CLASS TOKO ELEKTRONIK
// ==============================
class TokoElektronik {
private:
    // Array private (enkapsulasi)
    array<string, 3> etalase;

public:
    // Constructor mengisi data awal
    TokoElektronik() {
        etalase[0] = "Laptop ASUS";
        etalase[1] = "Smartphone Samsung";
        etalase[2] = "Printer Epson";
    }

    // Method mengambil produk
    string ambilProduk(size_t nomorRak) {
        try {
            // Wajib menggunakan .at()
            return etalase.at(nomorRak);
        }
        catch (const out_of_range&) {
            // Throw custom error
            throw runtime_error(
                "Gagal Mengambil Barang : Rak nomor " +
                to_string(nomorRak) +
                " kosong atau tidak tersedia!"
            );
        }
    }
};

// ==============================
// CLASS GUDANG
// ==============================
class Gudang {
private:
    string namaFile;

public:
    Gudang(string file) {
        namaFile = file;
    }

    // READ FILE
    vector<string> bacaData() {
        vector<string> data;
        ifstream file(namaFile);

        string barang;

        while (getline(file, barang)) {
            data.push_back(barang);
        }

        file.close();
        return data;
    }

    // TAMPILKAN DATA
    void tampilkanData() {
        vector<string> data = bacaData();

        cout << "\n===== DAFTAR BARANG GUDANG =====\n";

        if (data.empty()) {
            cout << "Gudang masih kosong.\n";
        } else {
            for (size_t i = 0; i < data.size(); i++) {
                cout << i << ". " << data[i] << endl;
            }
        }

        cout << "================================\n";
    }

    // CREATE
    void tambahBarang() {
        ofstream file(namaFile, ios::app);

        string barang;
        cin.ignore();

        cout << "Masukkan nama barang: ";
        getline(cin, barang);

        file << barang << endl;

        file.close();

        cout << "Barang berhasil ditambahkan!\n";
    }

    // UPDATE
    void updateBarang() {
        vector<string> data = bacaData();

        if (data.empty()) {
            cout << "Tidak ada data untuk diupdate.\n";
            return;
        }

        tampilkanData();

        size_t index;
        cout << "Masukkan nomor barang yang ingin diupdate: ";
        cin >> index;

        if (index >= data.size()) {
            cout << "Index tidak valid!\n";
            return;
        }

        cin.ignore();

        string barangBaru;
        cout << "Masukkan nama barang baru: ";
        getline(cin, barangBaru);

        data[index] = barangBaru;

        ofstream file(namaFile);

        for (string barang : data) {
            file << barang << endl;
        }

        file.close();

        cout << "Data berhasil diupdate!\n";
    }

    // DELETE
    void hapusBarang() {
        vector<string> data = bacaData();

        if (data.empty()) {
            cout << "Tidak ada data untuk dihapus.\n";
            return;
        }

        tampilkanData();

        size_t index;
        cout << "Masukkan nomor barang yang ingin dihapus: ";
        cin >> index;

        if (index >= data.size()) {
            cout << "Index tidak valid!\n";
            return;
        }

        data.erase(data.begin() + index);

        ofstream file(namaFile);

        for (string barang : data) {
            file << barang << endl;
        }

        file.close();

        cout << "Data berhasil dihapus!\n";
    }
};

// ==============================
// MAIN PROGRAM
// ==============================
int main() {

    Gudang gudang("gudang.txt");
    TokoElektronik toko;

    int pilihan;

    do {
        cout << "\n=====================================\n";
        cout << " SISTEM MANAJEMEN TOKO GIBRAN JAYA\n";
        cout << "=====================================\n";

        // Read otomatis saat menu dibuka
        gudang.tampilkanData();

        cout << "\nMENU UTAMA\n";
        cout << "1. Tambah Barang (Create)\n";
        cout << "2. Lihat Barang (Read)\n";
        cout << "3. Update Barang (Update)\n";
        cout << "4. Hapus Barang (Delete)\n";
        cout << "5. Simulasi Etalase\n";
        cout << "0. Keluar\n";

        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {

        case 1:
            gudang.tambahBarang();
            break;

        case 2:
            gudang.tampilkanData();
            break;

        case 3:
            gudang.updateBarang();
            break;

        case 4:
            gudang.hapusBarang();
            break;

        case 5:
            cout << "\n===== SIMULASI ETALASE =====\n";

            // Skenario 1 (Sukses)
            try {
                cout << "\nSkenario 1:\n";
                cout << "Mengambil rak indeks ke-1...\n";

                string barang = toko.ambilProduk(1);

                cout << "Berhasil mengambil: "
                     << barang << endl;
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }

            // Skenario 2 (Gagal)
            try {
                cout << "\nSkenario 2:\n";
                cout << "Mengambil rak indeks ke-5...\n";

                string barang = toko.ambilProduk(5);

                cout << "Berhasil mengambil: "
                     << barang << endl;
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }

            break;

       