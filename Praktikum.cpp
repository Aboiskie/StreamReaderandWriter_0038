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

    