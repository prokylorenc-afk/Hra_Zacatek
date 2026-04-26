#include <iostream>
#include <string>

using namespace std;

int main() {
    int volba;
    string jmenoClassy;
    int hp, utok, mana;

    cout << "--- VITej V MOJI RPG HRE ---" << endl;
    cout << "1. Vybrat postavu" << endl;
    cout << "2. Ukoncit hru" << endl;
    cin >> volba;

    if (volba == 1) {
        bool potvrzeno = false;
        while (potvrzeno == false) {
            cout << "\nVyber si classu:\n1. Paladin\n2. Mag" << endl;
            int vyber;
            cin >> vyber;

            if (vyber == 1) {
                jmenoClassy = "Paladin";
                hp = 10; utok = 3; mana = 5;
            }
            else {
                jmenoClassy = "Mag";
                hp = 6; utok = 5; mana = 10;
            }

            cout << "\nZvolil jsi: " << jmenoClassy << endl;
            cout << "Staty: HP: " << hp << ", Utok: " << utok << ", Mana: " << mana << endl;
            cout << "Chces tuhle postavu? (1 = Ano / 0 = Ne): ";
            cin >> potvrzeno;
        }
        cout << "\nHra zacina za postavu " << jmenoClassy << "..." << endl;
    }
    else {
        cout << "Koncim program..." << endl;
    }

    // Tohle zajisti, ze se okno nezavre hned
    cout << "\nStiskni Enter pro ukonceni..." << endl;
    system("pause");

    return 0;
}