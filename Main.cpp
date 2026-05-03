#include <iostream>
#include <string>

using namespace std;

int main() {
    int volbaHlavni;
    bool hraceVybral = false;

    // Promenne pro staty postavy
    string jmeno;
    int hp = 0;
    int utok = 0;
    int obrana = 0;
    int rychlost = 0;
    int stamina = 0;
    string specialita = "Zadna";

    cout << "=== VITEJ VE HRE ===" << endl;

    // Nekonecny cyklus pro hlavni menu, dokud hrac neda "Hrat"
    while (true) {
        cout << "\n--- HLAVNI MENU ---" << endl;
        cout << "1. Zvolit postavu" << endl;
        cout << "2. Hrat" << endl;
        cout << "3. Ukoncit" << endl;
        cout << "Tvoje volba: ";
        cin >> volbaHlavni;

        if (volbaHlavni == 1) {
            cout << "\nVyber si hrdinu:" << endl;
            cout << "1. Rytir (Dobry utok i obrana, ale pomaly, ma mec a stit)" << endl;
            cout << "2. Goblin (Maly a extremne rychly, ale ma jen kudlicku)" << endl;
            cout << "3. Carodej (Normalni staty, muze si vylepsit hul ve stanu)" << endl;
            cout << "4. Jezibaba (Pomalejsi, ale ma ostrazitost, staminu a jed)" << endl;
            cout << "5. Lucistnik (Rychly, utoci na dalku)" << endl;
            cout << "Vyber: ";

            int volbaPostavy;
            cin >> volbaPostavy;

            if (volbaPostavy == 1) {
                jmeno = "Rytir";
                hp = 20; utok = 8; obrana = 10; rychlost = 2; stamina = 10;
                specialita = "Mec a stit";
            }
            else if (volbaPostavy == 2) {
                jmeno = "Goblin";
                hp = 10; utok = 3; obrana = 2; rychlost = 15; stamina = 8;
                specialita = "Rezava kudlicka";
            }
            else if (volbaPostavy == 3) {
                jmeno = "Carodej";
                hp = 15; utok = 5; obrana = 5; rychlost = 5; stamina = 15;
                cout << "\nJsi ve svem stanu. Jakou chces hul?" << endl;
                cout << "1. Ohniva, 2. Mraziva, 3. Toxicka" << endl;
                cout << "Vyber: ";
                int hul;
                cin >> hul;
                if (hul == 1) specialita = "Ohniva hul";
                else if (hul == 2) specialita = "Mraziva hul";
                else specialita = "Toxicka hul";
            }
            else if (volbaPostavy == 4) {
                jmeno = "Jezibaba";
                hp = 18; utok = 4; obrana = 6; rychlost = 3; stamina = 20;
                specialita = "Jed (Poison)";
            }
            else if (volbaPostavy == 5) {
                jmeno = "Lucistnik";
                hp = 12; utok = 7; obrana = 3; rychlost = 8; stamina = 12;
                specialita = "Luk a sipy";
            }
            else {
                cout << "Spatna volba, davam ti Rytire." << endl;
                jmeno = "Rytir"; hp = 20; utok = 8; obrana = 10; rychlost = 2; stamina = 10;
                specialita = "Mec a stit";
            }

            hraceVybral = true;
            cout << "\n--> Tvoje postava je nyni: " << jmeno << " <--" << endl;
            cout << "Staty: HP: " << hp << " | Utok: " << utok << " | Obrana: " << obrana
                << " | Rychlost: " << rychlost << " | Stamina: " << stamina << endl;
            cout << "Specialita: " << specialita << endl;

        }
        else if (volbaHlavni == 2) {
            if (hraceVybral == false) {
                cout << "\n!!! Pozor: Nejdriv si musis vybrat postavu (volba 1) !!!" << endl;
            }
            else {
                cout << "\nVyborne, hra zacina za postavu: " << jmeno << "..." << endl;
                break; 
            }
        }
        else if (volbaHlavni == 3) {
            cout << "Koncim program..." << endl;
            return 0; 
        }
        else {
            cout << "Neznama volba v menu!" << endl;
        }
    }

  
    cout << "\nOcitl ses v temnem lese a v dalce vidis vesnici..." << endl;

    cout << "\nStiskni Enter pro ukonceni..." << endl;
    system("pause");
    return 0;
}
