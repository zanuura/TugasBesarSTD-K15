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

// 1. Insert data parent dari depan
void insertFirstParent(list_orangTua &L, adr_orangTua P);
adr_orangTua createNewParent(infotype_orangTua info);

// 2. Cari data parent
adr_orangTua findParent(list_orangTua L, string namaParent);

// 3. Hapus data parent & relasinya
void deleteParent(list_orangTua &L, string namaParent);

// 4. Insert data anak dari belakang
void insertLastChild(list_anak &L, adr_anak C);
adr_anak createNewChild(infotype_anak info); // Fungsi pembantu untuk membuat node anak baru

// 5. Cari data anak
adr_anak findChild(list_anak L, string namaAnak);

// 6. Buat Relasi (Hubungkan Parent ke Child)
adr_relation createNewRelation(adr_anak C);
void insertFirstRelation(list_relation &L, adr_relation R);

// 7. Hapus relasi tertentu
adr_relation findRelation(adr_orangTua P, string namaAnak); 

void deleteRelation(list_orangTua &L_ORTU, adr_orangTua P, string namaAnak);

// 8. Tampilkan Seluruh Data
void printAllParentAndChild(list_orangTua L_ORTU, list_anak L_ANAK);

// 9. Cari Anak dari Orang Tua Tertentu
void printChildrenOfParent(list_orangTua L_ORTU, string namaParent);

// 10. Hitung Jumlah Anak dari Orang Tua Tertentu
int countChildrenOfParent(list_orangTua L_ORTU, string namaParent);

// --- HANDLER FUNCTION (UNTUK MENU) ---
void handleInsertParent(list_orangTua &L); // Already exists in original file
void handleFindParent(list_orangTua L);
void handleDeleteParent(list_orangTua &L);
void handleInsertChild(list_anak &L);
void handleFindChild(list_anak L);
void handleCreateRelation(list_orangTua &L_ORTU, list_anak L_ANAK);
void handleDeleteRelation(list_orangTua &L_ORTU);
void handleShowAllParentAndChild(list_orangTua L_ORTU, list_anak L_ANAK);
void handleFindChildOnParent(list_orangTua L_ORTU);
void handleCountChildOfParent(list_orangTua L_ORTU);
#endif // MLL_H_INCLUDED
