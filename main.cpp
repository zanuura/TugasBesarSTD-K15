#include <iostream>
#include "MLL.h"

using namespace std;

int main()
{
    list_orangTua L_ORTU;
    list_anak L_ANAK;

    // menginisasi list dengan seorang ayah, ibu, dan satu anak
    InisiasiDataKeluarga(L_ORTU, L_ANAK);

    cout << "Hello world!" << endl;
    return 0;
}
