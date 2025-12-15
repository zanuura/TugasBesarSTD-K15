#include <iostream>
#include "MLL.h"

using namespace std;

// ----------------------------------------------------

// Fungsi pembantu untuk membuat node anak baru
adr_anak createNewChild(infotype_anak info)
{
    adr_anak C = new elm_anak;

    C->info = info;
    C->next = NULL;

    return C;
}

// 4. Insert data anak dari belakang (Insert Last Child)
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
        adr_anak current = L.first;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = C;
    }
}

// 2. Cari data parent
adr_orangTua findParent(list_orangTua L, string namaParent)
{
    adr_orangTua P = L.first;
    while (P != NULL)
    {
        if (P->info.nama == namaParent)
        {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

// 5. Cari data anak
adr_anak findChild(list_anak L, string namaAnak)
{
    adr_anak C = L.first;
    while (C != NULL)
    {
        if (C->info.nama == namaAnak)
        {
            return C;
        }
        C = C->next;
    }
    return NULL;
}

// 6. Fungsi pembantu untuk membuat node relasi baru
adr_relation createNewRelation(adr_anak C)
{
    adr_relation R = new elm_relation;
    R->next_anak = C;
    R->next = NULL;
    return R;
}

// 6. Fungsi pembantu untuk insert relasi di depan (Insert First Relation)
void insertFirstRelation(list_relation &L, adr_relation R)
{
    R->next = L.first;
    L.first = R;
}

// 3. Hapus data parent & relasinya
void deleteParent(list_orangTua &L, string namaParent)
{
    adr_orangTua P_del = findParent(L, namaParent);

    if (P_del == NULL)
    {
        cout << "[NOT FOUND] Orang Tua dengan nama " << namaParent << " tidak ditemukan." << endl;
        return;
    }

    adr_orangTua prev = NULL;
    adr_orangTua curr = L.first;

    // Cari P_del dan prev-nya
    while (curr != NULL && curr != P_del)
    {
        prev = curr;
        curr = curr->next;
    }

    // Jika ditemukan
    if (curr != NULL)
    {
        // Penghapusan node Parent
        if (prev == NULL)
        {
            // Case: Hapus First
            L.first = curr->next;
        }
        else
        {
            // Case: Hapus di tengah/belakang
            prev->next = curr->next;
        }

        // Hapus node dan bebaskan memori. (Node relasi yang terhubung ke P_del akan dihapus secara otomatis)
        delete curr;
        cout << "[SUCCESS] Orang Tua " << namaParent << " beserta semua relasinya berhasil dihapus." << endl;
    }
}

// 7. Fungsi pembantu untuk mencari relasi tertentu (digunakan oleh handleDeleteRelation)
adr_relation findRelation(adr_orangTua P, string namaAnak)
{
    adr_relation R = P->anak.first;
    while (R != NULL)
    {
        if (R->next_anak != NULL && R->next_anak->info.nama == namaAnak)
        {
            return R;
        }
        R = R->next;
    }
    return NULL;
}

// 7. Hapus relasi tertentu
void deleteRelation(list_orangTua &L_ORTU, adr_orangTua P, string namaAnak)
{
    adr_relation prev_R = NULL;
    adr_relation curr_R = P->anak.first;

    while (curr_R != NULL)
    {
        if (curr_R->next_anak != NULL && curr_R->next_anak->info.nama == namaAnak)
        {
            // Found the relation to delete (curr_R)
            if (prev_R == NULL)
            {
                // Case: Delete First
                P->anak.first = curr_R->next;
            }
            else
            {
                // Case: Delete in middle/last
                prev_R->next = curr_R->next;
            }
            // Delete the relation node
            delete curr_R;
            cout << "[SUCCESS] Relasi Orang Tua " << P->info.nama << " dengan Anak " << namaAnak << " berhasil dihapus." << endl;
            return;
        }
        prev_R = curr_R;
        curr_R = curr_R->next;
    }
    cout << "[NOT FOUND] Relasi Orang Tua " << P->info.nama << " dengan Anak " << namaAnak << " tidak ditemukan." << endl;
}

// 8. Tampilkan Seluruh Data
void printAllParentAndChild(list_orangTua L_ORTU, list_anak L_ANAK)
{
    cout << "\n===================================================" << endl;
    cout << "           LAPORAN SELURUH DATA KELUARGA           " << endl;
    cout << "===================================================" << endl;

    // Tampilkan Data Anak (L2)
    cout << ":: DATA ANAK (L2) ::" << endl;
    if (L_ANAK.first == NULL)
    {
        cout << "Tidak ada data anak." << endl;
    }
    else
    {
        adr_anak C = L_ANAK.first;
        int i = 1;
        while (C != NULL)
        {
            cout << " " << i++ << ". Nama: " << C->info.nama << ", Jenis Kelamin: " << C->info.jenis_kelamin << ", Usia: " << C->info.usia << endl;
            C = C->next;
        }
    }
    cout << "---------------------------------------------------" << endl;

    // Tampilkan Data Orang Tua (L1) dan Relasi (anak)
    cout << ":: DATA ORANG TUA (L1) & RELASI ANAK ::" << endl;
    if (L_ORTU.first == NULL)
    {
        cout << "Tidak ada data orang tua." << endl;
    }
    else
    {
        adr_orangTua P = L_ORTU.first;
        int j = 1;
        while (P != NULL)
        {
            cout << j++ << ". Orang Tua: " << P->info.nama << " (" << P->info.jenis << ", " << P->info.usia << " tahun)" << endl;
            cout << "   - Anak:";

            adr_relation R = P->anak.first;
            if (R == NULL)
            {
                cout << " (Tidak ada relasi anak)";
            }
            else
            {
                int k = 1;
                while (R != NULL)
                {
                    if (R->next_anak != NULL)
                    {
                        cout << " " << k++ << ". " << R->next_anak->info.nama;
                    }
                    R = R->next;
                }
            }
            cout << endl;
            P = P->next;
        }
    }
    cout << "===================================================" << endl;
}

// 9. Cari Anak dari Orang Tua Tertentu
void printChildrenOfParent(list_orangTua L_ORTU, string namaParent)
{
    adr_orangTua P = findParent(L_ORTU, namaParent);

    if (P == NULL)
    {
        cout << "[NOT FOUND] Orang Tua dengan nama " << namaParent << " tidak ditemukan." << endl;
        return;
    }

    cout << "\n--- DAFTAR ANAK DARI ORANG TUA: " << P->info.nama << " ---" << endl;
    adr_relation R = P->anak.first;

    if (R == NULL)
    {
        cout << "Orang Tua " << P->info.nama << " tidak memiliki relasi anak." << endl;
        return;
    }

    int count = 0;
    while (R != NULL)
    {
        if (R->next_anak != NULL)
        {
            cout << " - Nama: " << R->next_anak->info.nama
                 << ", Jenis Kelamin: " << R->next_anak->info.jenis_kelamin
                 << ", Usia: " << R->next_anak->info.usia << endl;
            count++;
        }
        R = R->next;
    }

    cout << "Total anak yang ditemukan: " << count << endl;
}

// 10. Hitung Jumlah Anak dari Orang Tua Tertentu
int countChildrenOfParent(list_orangTua L_ORTU, string namaParent)
{
    adr_orangTua P = findParent(L_ORTU, namaParent);

    if (P == NULL)
    {
        return -1; // -1 indicates not found
    }

    int count = 0;
    adr_relation R = P->anak.first;

    while (R != NULL)
    {
        // Only count if next_anak is not NULL (to ensure valid pointer)
        if (R->next_anak != NULL)
        {
            count++;
        }
        R = R->next;
    }

    return count;
}


// ----------------------------------------------------

// 2. Handler untuk Cari Data Orang Tua
void handleFindParent(list_orangTua L)
{
    string namaCari;
    cout << "\n--- CARI DATA ORANG TUA ---" << endl;
    cout << "Masukkan Nama Orang Tua yang dicari: ";
    cin.ignore();
    getline(cin, namaCari);

    adr_orangTua P = findParent(L, namaCari);

    if (P != NULL)
    {
        cout << "\n[SUCCESS] Orang Tua ditemukan!" << endl;
        cout << "Nama: " << P->info.nama << endl;
        cout << "Jenis: " << P->info.jenis << endl;
        cout << "Usia: " << P->info.usia << " tahun" << endl;
        // Opsional: Tampilkan relasi anaknya juga
        cout << "Anak:";
        adr_relation R = P->anak.first;
        if (R == NULL)
        {
            cout << " (Tidak ada relasi anak)";
        }
        else
        {
            int k = 1;
            while (R != NULL)
            {
                if (R->next_anak != NULL)
                {
                    cout << " " << k++ << ". " << R->next_anak->info.nama;
                }
                R = R->next;
            }
        }
        cout << endl;
    }
    else
    {
        cout << "[NOT FOUND] Orang Tua dengan nama " << namaCari << " tidak ditemukan." << endl;
    }
}

// 3. Handler untuk Hapus Data Orang Tua & Semua Relasinya
void handleDeleteParent(list_orangTua &L)
{
    string namaHapus;
    cout << "\n--- HAPUS DATA ORANG TUA ---" << endl;
    cout << "Masukkan Nama Orang Tua yang akan dihapus: ";
    cin.ignore();
    getline(cin, namaHapus);

    deleteParent(L, namaHapus);
}

// 4. Handler untuk Tambah Data Anak Baru (Insert Last)
void handleInsertChild(list_anak &L)
{
    infotype_anak infoBaru;
    cout << "\n--- TAMBAH DATA ANAK BARU ---\n";
    cin.ignore(10000, '\n'); 

    cout << "Nama: ";
    getline(cin, infoBaru.nama);
    
    // Check if child already exists
    if (findChild(L, infoBaru.nama) != NULL)
    {
        cout << "[ERROR] Anak dengan nama " << infoBaru.nama << " sudah ada." << endl;
        return;
    }

    cout << "Jenis Kelamin (Laki-laki/Perempuan): ";
    getline(cin, infoBaru.jenis_kelamin);

    cout << "Usia: ";
    while (!(cin >> infoBaru.usia))
    {
        cout << "Input usia tidak valid. Masukkan angka: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    adr_anak C_Baru = createNewChild(infoBaru);
    insertLastChild(L, C_Baru);

    cout << "\n[SUCCESS] Anak " << infoBaru.nama << " berhasil ditambahkan." << endl;
}

// 5. Handler untuk Cari Data Anak
void handleFindChild(list_anak L)
{
    string namaCari;
    cout << "\n--- CARI DATA ANAK ---" << endl;
    cout << "Masukkan Nama Anak yang dicari: ";
    cin.ignore();
    getline(cin, namaCari);

    adr_anak C = findChild(L, namaCari);

    if (C != NULL)
    {
        cout << "\n[SUCCESS] Anak ditemukan!" << endl;
        cout << "Nama: " << C->info.nama << endl;
        cout << "Jenis Kelamin: " << C->info.jenis_kelamin << endl;
        cout << "Usia: " << C->info.usia << " tahun" << endl;
    }
    else
    {
        cout << "[NOT FOUND] Anak dengan nama " << namaCari << " tidak ditemukan." << endl;
    }
}

// 6. Handler untuk Hubungkan Orang Tua ke Anak (Buat Relasi)
void handleCreateRelation(list_orangTua &L_ORTU, list_anak L_ANAK)
{
    string namaParent, namaChild;
    cout << "\n--- BUAT RELASI ORANG TUA - ANAK ---" << endl;
    cout << "Masukkan Nama Orang Tua: ";
    cin.ignore();
    getline(cin, namaParent);

    cout << "Masukkan Nama Anak: ";
    getline(cin, namaChild);

    // 1. Cari Parent
    adr_orangTua P = findParent(L_ORTU, namaParent);
    if (P == NULL)
    {
        cout << "[ERROR] Orang Tua dengan nama " << namaParent << " tidak ditemukan." << endl;
        return;
    }

    // 2. Cari Anak
    adr_anak C = findChild(L_ANAK, namaChild);
    if (C == NULL)
    {
        cout << "[ERROR] Anak dengan nama " << namaChild << " tidak ditemukan." << endl;
        return;
    }

    // 3. Cek apakah relasi sudah ada
    if (findRelation(P, namaChild) != NULL)
    {
        cout << "[WARNING] Relasi antara " << namaParent << " dan " << namaChild << " sudah ada." << endl;
        return;
    }

    // 4. Buat dan hubungkan relasi (Insert First Relation)
    adr_relation R_Baru = createNewRelation(C);
    insertFirstRelation(P->anak, R_Baru);

    cout << "[SUCCESS] Relasi antara " << namaParent << " dan " << namaChild << " berhasil dibuat." << endl;
}

// 7. Handler untuk Hapus Relasi Tertentu (Putus Hubungan Ortu-Anak)
void handleDeleteRelation(list_orangTua &L_ORTU)
{
    string namaParent, namaChild;
    cout << "\n--- HAPUS RELASI ORANG TUA - ANAK ---" << endl;
    cout << "Masukkan Nama Orang Tua: ";
    cin.ignore();
    getline(cin, namaParent);

    cout << "Masukkan Nama Anak yang relasinya akan dihapus: ";
    getline(cin, namaChild);

    // 1. Cari Parent
    adr_orangTua P = findParent(L_ORTU, namaParent);
    if (P == NULL)
    {
        cout << "[ERROR] Orang Tua dengan nama " << namaParent << " tidak ditemukan." << endl;
        return;
    }

    // 2. Hapus relasi
    deleteRelation(L_ORTU, P, namaChild);
}

// 8. Handler untuk Tampilkan Seluruh Data
void handleShowAllParentAndChild(list_orangTua L_ORTU, list_anak L_ANAK)
{
    printAllParentAndChild(L_ORTU, L_ANAK);
}

// 9. Handler untuk Cari Anak dari Orang Tua Tertentu
void handleFindChildOnParent(list_orangTua L_ORTU)
{
    string namaParent;
    cout << "\n--- CARI ANAK DARI ORANG TUA TERTENTU ---" << endl;
    cout << "Masukkan Nama Orang Tua: ";
    cin.ignore();
    getline(cin, namaParent);

    printChildrenOfParent(L_ORTU, namaParent);
}

// 10. Handler untuk Hitung Jumlah Anak dari Orang Tua Tertentu
void handleCountChildOfParent(list_orangTua L_ORTU)
{
    string namaParent;
    cout << "\n--- HITUNG JUMLAH ANAK DARI ORANG TUA TERTENTU ---" << endl;
    cout << "Masukkan Nama Orang Tua: ";
    cin.ignore();
    getline(cin, namaParent);

    int count = countChildrenOfParent(L_ORTU, namaParent);

    if (count == -1)
    {
        cout << "[NOT FOUND] Orang Tua dengan nama " << namaParent << " tidak ditemukan." << endl;
    }
    else
    {
        cout << "\n[RESULT] Orang Tua " << namaParent << " memiliki total " << count << " anak." << endl;
    }
}

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

int showMainMenu()
{
    int pilihan;

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

    if (!(cin >> pilihan))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        pilihan = -1;
    }

    return pilihan;
}

// handler function
void handleInsertParent(list_orangTua &L)
{
    infotype_orangTua infoBaru;
    cout << "\n--- TAMBAH ORANG TUA BARU ---\n";
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

// NOTE: Perlu buat dulu fungsi findParent, dan findChild
void handleHubungkanParentToChild(list_orangTua &L1, list_anak &L2)
{
    // ...
}

void insertFirstParent(list_orangTua &L, adr_orangTua P)
{
    if (L.first == NULL)
    {
        L.first = P;
    }
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
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = C;
    }
}

adr_anak createNewChild(infotype_anak info)
{
    adr_anak C = new elm_anak;

    C->info = info;
    C->next = NULL; // Next node di List L2

    return C;
}

// NOTE : Perlu buat dulu fungsi createNewRelation
bool hubungkanParentToChild(adr_orangTua P, adr_anak C)
{
    if (P == NULL || C == NULL)
    {
        return false; // Pointer tidak valid
    }
    // 1. Buat Node Relasi baru
    adr_relation R_Baru = createNewRelation(C);

    // 2. Sisipkan Node Relasi ke list relasi Parent (P->anak)
    R_Baru->next = P->anak.first;
    P->anak.first = R_Baru;

    return true;
}