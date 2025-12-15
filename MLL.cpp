#include <iostream>
#include "MLL.h"

using namespace std;

// inisiasi data keluarga (parent - children)
void InisiasiDataKeluarga(list_orangTua &L1, list_anak &L2) {
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
