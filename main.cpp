#include <iostream>
#include "MLL.h"

using namespace std;

int main()
{
    list_orangTua L_ORTU;
    list_anak L_ANAK;

    // menginisasi list dengan seorang ayah, ibu, dan satu anak
    InisiasiDataKeluarga(L_ORTU, L_ANAK);

    int pilihanMenu;
    do
    {
        pilihanMenu = showMainMenu();

        switch (pilihanMenu)
        {
        case 1:
            // Panggil InsertFirstParent
            handleInsertParent(L_ORTU);
            break;
        case 2:
            // Panggil findParent
            break;
        case 3:
            // Panggil DeleteParent
            break;
        case 4:
            // Panggil insertLastChild
            handleInsertChild(L_ANAK);
            break;
        case 5:
            // Panggil findChild
            break;
        case 6:
            // Panggil HubungkanParentToChild
            break;
        case 7:
            // Panggil deleteRelation
            break;
        case 8:
            // Panggil ShowAllParentAndChild
            break;
        case 9:
            // Panggil findChildOnParent
            break;
        case 10:
            // Panggil countChildOfParent
            break;
        case 0:
            cout << "Terima kasih telah menggunakan program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
        }

        if (pilihanMenu != 0)
        {
            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }

    } while (pilihanMenu != 0);
    return 0;
}
