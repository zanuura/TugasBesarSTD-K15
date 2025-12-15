#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED
#include <iostream>
using namespace std;

// forward declaration
typedef struct elm_orangTua *adr_orangTua;
typedef struct elm_anak *adr_anak;
typedef struct elm_relation *adr_relation;

// struktur untuk list relasi
struct list_relation {
    adr_relation first;
};

// struktur orang tua
struct infotype_orangTua {
    string nama, jenis;
    int usia;
};

struct elm_orangTua {
    infotype_orangTua info;
    adr_orangTua next;
    list_relation anak;
};

struct list_orangTua {
    adr_orangTua first;
};

// struktur anak
struct infotype_anak {
    string nama, jenis_kelamin;
    int usia;
};

struct elm_anak {
    infotype_anak info;
    adr_anak next;
};

struct list_anak {
    adr_anak first;
};

// struktur relasi
struct elm_relation {
    adr_anak next_anak;
    adr_relation next;
};

// procedure inisiasi data keluarga
void InisiasiDataKeluarga(list_orangTua &L1, list_anak &L2);

#endif // MLL_H_INCLUDED
