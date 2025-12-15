#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED
#include <iostream>
using namespace std;

// forward declaration
typedef struct elm_orangTua *adr_orangTua;
typedef struct elm_anak *adr_anak;
typedef struct elm_relation *adr_relation;

// struktur untuk list relasi
struct list_relation
{
    adr_relation first;
};

// struktur orang tua
struct infotype_orangTua
{
    string nama, jenis;
    int usia;
};

struct elm_orangTua
{
    infotype_orangTua info;
    adr_orangTua next;
    list_relation anak;
};

struct list_orangTua
{
    adr_orangTua first;
};

// struktur anak
struct infotype_anak
{
    string nama, jenis_kelamin;
    int usia;
};

struct elm_anak
{
    infotype_anak info;
    adr_anak next;
};

struct list_anak
{
    adr_anak first;
};

// struktur relasi
struct elm_relation
{
    adr_anak next_anak;
    adr_relation next;
};

// procedure inisiasi data keluarga
void InisiasiDataKeluarga(list_orangTua &L1, list_anak &L2);

// main menu
int showMainMenu();

// handler function
void handleInsertParent(list_orangTua &L);

// --- FUNGSI/PROSEDUR UTAMA (PROTOTYPE) ---
// 1. Insert data parent dari depan
void insertFirstParent(list_orangTua &L, adr_orangTua P);
adr_orangTua createNewParent(infotype_orangTua info); // Fungsi pembantu untuk membuat node baru

// 2. Show all data parent
void showAllParent(list_orangTua L);

// 3. Menghapus data parent beserta relasinya
// menggunakan deleteLast untuk list parent
bool deleteParent(list_orangTua &L_Ortu, list_anak &L_Anak, string namaParent, adr_orangTua &P_Hapus);
void deleteLastParent(list_orangTua &L, adr_orangTua &P_Hapus);
// mengunakan deleteFirst untuk list anak
void deleteFirstChild(list_anak &L, adr_anak &C_Hapus);

// 4. Mencari data parent
adr_orangTua findParent(list_orangTua L, string namaParent);

// 5. Mencari data child
adr_anak findChild(list_anak L, string namaChild);

// 6. Menambahkan data child dari belakang
void insertLastChild(list_anak &L, adr_anak C);
adr_anak createNewChild(infotype_anak info); // Fungsi pembantu untuk membuat node baru

// 7. Menghubungkan data parent ke data child
bool hubungkanParentToChild(list_orangTua &L_Ortu, adr_anak C, string namaAyah, string namaIbu);
adr_relation createNewRelation(adr_anak C); // C adalah pointer ke anak

// 8. Menampilkan seluruh data parent beserta childnya
void showAllParentAndChild(list_orangTua L_Ortu);

// 9. Mencari data child pada parent tertentu
adr_anak findChildOnParent(list_orangTua L_Ortu, string namaParent, string namaChild);

// 10. Menghapus data child pada parent tertentu beserta relasinya
bool deleteRelation(list_orangTua &L_Ortu, string namaParent, string namaChild);
// Tambahan: Prosedur untuk menghapus Node Anak di L2 jika semua relasinya sudah dihapus
// adr_anak deleteChildNode(list_anak &L_Anak, string namaChild);

// 11. Menghitung jumlah data child dari parent tertentu
int countChildOfParent(list_orangTua L, string namaParent);

#endif // MLL_H_INCLUDED
