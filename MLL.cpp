#include <iostream>
#include "MLL.h"

using namespace std;

// inisiasi data keluarga (parent - children)
void InisiasiDataKeluarga(list_orangTua &L1, list_anak &L2)
{
    L1.first = NULL;
    L2.first = NULL;

    // ayah
    adr_orangTua P1 = new elm_orangTua;
    P1->info = {"Rick", "Ayah", 53};
    P1->next = NULL;
    P1->anak.first = NULL;

    // ibu
    adr_orangTua P2 = new elm_orangTua;
    P2->info = {"Lori", "Ibu", 35};
    P2->next = NULL;
    P2->anak.first = NULL;

    // hubungkan parent-parent
    L1.first = P1;
    P1->next = P2;

    // anak
    adr_anak C1 = new elm_anak;
    C1->info = {"Carl", "Laki-laki", 19};
    C1->next = NULL;

    L2.first = C1;

    // relasi 1
    adr_relation R1 = new elm_relation;
    R1->next_anak = C1;
    R1->next = NULL;

    P1->anak.first = R1;

    // relasi 2
    adr_relation R2 = new elm_relation;
    R2->next_anak = C1;
    R2->next = NULL;

    P2->anak.first = R2;
}

// main menu
int showMainMenu()
{
    int pilihan;

// Bersihkan layar
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "===================================================" << endl;
    cout << "           APLIKASI DATA KELUARGA (MLL M:N)        " << endl;
    cout << "===================================================" << endl;
    cout << "           :: MANAJEMEN DATA ORANG TUA (L1) ::     " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << " 1. Tambah Data Orang Tua Baru (Insert First) " << endl;
    cout << " 2. Cari Data Orang Tua " << endl;
    cout << " 3. Hapus Data Orang Tua & Semua Relasinya " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "           :: MANAJEMEN DATA ANAK (L2) ::          " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << " 4. Tambah Data Anak Baru (Insert Last) " << endl;
    cout << " 5. Cari Data Anak " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "           :: MANAJEMEN RELASI ::                  " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << " 6. Hubungkan Orang Tua ke Anak (Buat Relasi) " << endl;
    cout << " 7. Hapus Relasi Tertentu (Putus Hubungan Ortu-Anak)" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "           :: PELAPORAN & ANALISIS ::              " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << " 8. Tampilkan Seluruh Data Keluarga (Ortu & Anak)" << endl;
    cout << " 9. Cari Anak dari Orang Tua Tertentu " << endl;
    cout << " 10. Hitung Jumlah Anak dari Orang Tua Tertentu " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << " 0. KELUAR DARI PROGRAM " << endl;
    cout << "===================================================" << endl;
    cout << "Masukkan Pilihan Anda (0-10): ";

    // Memastikan input adalah integer yang valid
    if (!(cin >> pilihan))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        pilihan = -1; // Set ke nilai invalid
    }

    return pilihan;
}

// handler function
void handleInsertParent(list_orangTua &L)
{
    infotype_orangTua infoBaru;
    cout << "\n--- TAMBAH ORANG TUA BARU ---\n";
    // ... (Semua kode cin, getline, validasi usia yang panjang) ...
    cout << "Nama: ";
    cin.ignore();
    getline(cin, infoBaru.nama);

    cout << "Jenis (Ayah/Ibu): ";
    cin.ignore();
    getline(cin, infoBaru.jenis);

    cout << "usia: ";
    while (!(cin >> infoBaru.usia))
    {
        cout << "Input usia tidak valid. Masukkan angka: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    // --- 2. PROSES STRUKTUR DATA (Panggilan ke fungsi MLL inti) ---
    adr_orangTua P_Baru = createNewParent(infoBaru);
    insertFirstParent(L, P_Baru);

    cout << "\n[SUCCESS] Orang Tua " << infoBaru.nama << " berhasil ditambahkan." << endl;
}

void handleInsertChild(list_anak &L)
{
    infotype_anak infoBaru;
    cout << "\n--- TAMBAH ANAK BARU ---\n";
    // ... (Semua kode cin, getline, validasi usia yang panjang) ...
    cout << "Nama: ";
    cin.ignore();
    getline(cin, infoBaru.nama);

    cout << "Jenis kelamin: ";
    cin.ignore();
    getline(cin, infoBaru.jenis_kelamin);

    cout << "usia: ";
    while (!(cin >> infoBaru.usia))
    {
        cout << "Input usia tidak valid. Masukkan angka: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    // --- 2. PROSES STRUKTUR DATA (Panggilan ke fungsi MLL inti) ---
    adr_anak C_Baru = createNewChild(infoBaru);
    insertLastChild(L, C_Baru);

    cout << "\n[SUCCESS] Anak " << infoBaru.nama << " berhasil ditambahkan." << endl;
}

void insertFirstParent(list_orangTua &L, adr_orangTua P)
{
    // Kasus 1: List kosong
    if (L.first == NULL)
    {
        L.first = P;
    }
    // Kasus 2: List tidak kosong
    else
    {
        P->next = L.first;

        L.first = P;
    }
}

adr_orangTua createNewParent(infotype_orangTua info)
{
    adr_orangTua P = new elm_orangTua;

    P->info = info;
    P->next = NULL;
    P->anak.first = NULL;

    return P;
}

void insertLastChild(list_anak &L, adr_anak C)
{
    // Kasus 1: List kosong
    if (L.first == NULL)
    {
        L.first = C;
    }
    // Kasus 2: List tidak kosong
    else
    {
        adr_anak last = L.first;
        while(last->next != NULL) {
            last = last->next;
        }
        last->next = C;
    }
}

adr_anak createNewChild(infotype_anak info)
{
    adr_anak C = new elm_anak;

    C->info = info;
    C->next = NULL;          // Next node di List L2

    return C;
}
