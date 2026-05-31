#include <iostream>
#include <string>
#include <cstdlib>


using namespace std;



// hlavni logika hry
int main() {
    int volbaHlavni;
    bool hraceVybral = false;

    system("color B0");

    // promenne pro staty postav
    string jmeno;
    int hp = 0, utok = 0, obrana = 0, rychlost = 0, stamina = 0;
    int maxStamina = 0; // pro reset a kontrolu maxima
    int maxHp = 0;      // pro kontrolu maximalniho vyleceni
    string specialita = "Zadna";

    // inventar hrace
    int drahokamy = 0;

    cout << "=== VITEJ VE HRE ===" << endl;
       
    // hlavni menu
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
                jmeno = "Rytir"; hp = 20; utok = 8; obrana = 10; rychlost = 2; stamina = 10; specialita = "Mec a stit";
            }
            else if (volbaPostavy == 67) {
                jmeno = "Light"; hp = 100; utok = 50; obrana = 25; rychlost = 20; stamina = 80; specialita = "Death note";
            }
            else if (volbaPostavy == 2) {
                jmeno = "Goblin"; hp = 10; utok = 3; obrana = 2; rychlost = 15; stamina = 8; specialita = "Rezava kudlicka";
            }
            else if (volbaPostavy == 3) {
                jmeno = "Carodej"; hp = 15; utok = 5; obrana = 5; rychlost = 5; stamina = 15; specialita = "Magicka hul";
            }
            else if (volbaPostavy == 4) {
                jmeno = "Jezibaba"; hp = 18; utok = 4; obrana = 6; rychlost = 3; stamina = 20; specialita = "Jed (Poison)";
            }
            else if (volbaPostavy == 5) {
                jmeno = "Lucistnik"; hp = 12; utok = 7; obrana = 3; rychlost = 8; stamina = 12; specialita = "Luk a sipy";
            }
            else {
                cout << "Spatna volba, davam ti Rytire." << endl;
                jmeno = "Rytir"; hp = 20; utok = 8; obrana = 10; rychlost = 2; stamina = 10; specialita = "Mec a stit";
            }

            maxStamina = stamina; // ulozeni zakladni staminy do pameti
            maxHp = hp;           // ulozeni zakladnich zivotu do pameti
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
                // Intro od krale
                cout << "\n==================================================================" << endl;
                cout << "Kral si te nechal urgentne povolat!" << endl;
                cout << "Zada te o pomoc. Jeho nejlepsi vojsko slo na lov mysi do Temneho lesa..." << endl;
                cout << "...jenze se NEOZVALI a NEVRATILI. Nezbyly po nich ZADNE stopy." << endl;
                cout << "\nKral si zada prave tebe kvuli tvym zkusenostem a hrdinske povesti!" << endl;
                cout << "Kdyz najdes jeho druzinu, da ti pokladnici PLNOU ZLATA" << endl;
                cout << "a tvoje slava bude tak uchvatna, ze te budou znat VSOUDE!" << endl;
                cout << "==================================================================" << endl;

                cout << "\nPomozes krali v teto tezke chvili?" << endl;
                cout << "1. Ano, prijmam tvuj ukol, krali!" << endl;
                cout << "2. Ne, tohle me nezajima. Odchazim." << endl;
                cout << "Tvoje volba: ";
                int volbaPomoci;
                cin >> volbaPomoci;

                if (volbaPomoci == 2) {
                    cout << "\nGAME OVER: Kral te nechal POPRAVIT za nedostatek ucty k nemu!" << endl;
                    return 0;
                }
                else if (volbaPomoci == 36945710628) {
                    cout << "\nWIN: Zabil jsi krale a ostatni strazni se ti poddali. Ted jsi kralem ty!" << endl;
                    return 0;
                }
                else if (volbaPomoci == 1) {
                    cout << "\nDo sluzeb krale nastupuje hrdina... " << jmeno << "!" << endl;
                    break; // Vyskok z menu, jdeme hrat
                }
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

    // cesty-most
    cout << "\nOcitl ses na zacatku tve vypravy a pred sebou vidis dve cesty. Kterou si vyberes?" << endl;
    cout << "1 - Stary most, ktery vede pres reku" << endl;
    cout << "2 - Cesta rovnou do husteho lesa" << endl;
    cout << "Tvoje volba: ";

    int cesta;
    cin >> cesta;

    if (cesta == 1) {
        cout << "\nSpatna volba! Jakmile jsi stoupl na stary most, prkna praskla a ty jsi spadl do reky!" << endl;
        cout << "Tezce jsi doplaval na breh. Ztratil jsi cas, ale musis pokracovat jedinou moznou cestou - do husteho lesa." << endl;
    }
    else {
        cout << "\nRozhodl ses pro jistotu a jdes rovnou po ceste do husteho lesa." << endl;
    }

    // info o hre
    cout << "\n[INFO O HRE]" << endl;
    cout << "V Temnem lese zijou ruzne urovne priser:" << endl;
    cout << "- Lehke: Lesni sliz¨, krtci" << endl;
    cout << "- Stredni: Skret, Lesni troll" << endl;
    cout << "- Tezke: Stin lesu, Farmar smrti" << endl;
    cout << "Z KAZDE prisery padaji DRAHOKAMY. Ty pak muzes ve vesnici utratit!" << endl;
    cout << "Po kazdem boji se ti take vrati cast staminy podle toho, jak tezka prisera to byla." << endl;
    cout << "\n==================================================================" << endl;

    // boj s lehkou priserou
    cout << "\n!!! Z krovi na tebe vyskocila ta nejlehci prisera: LESNI SLIZ !!!" << endl;

    int hpPrisery = 10;

    while (hp > 0 && hpPrisery > 0) {
        cout << "\nTVOJE HP: " << hp << " | TVOJE STAMINA: " << stamina << "/" << maxStamina << endl;
        cout << "HP SLIZU: " << hpPrisery << endl;

        cout << "Vyber jeden ze 3 utoku:" << endl;
        cout << "1. Rychly utok     (Bere 1 staminu, utok za: " << utok / 2 + 1 << ")" << endl;
        cout << "2. Silny utok      (Bere 3 staminy, utok za: " << utok << ")" << endl;
        cout << "3. " << specialita << " (Bere 5 staminy, utok za: " << utok + 4 << ")" << endl;
        cout << "Volba utoku: ";

        int utokVolba;
        cin >> utokVolba;

        if (utokVolba == 1) {
            if (stamina >= 1) {
                hpPrisery -= (utok / 2 + 1);
                stamina -= 1;
                cout << "Bleskove jsi priseru zasahnul za " << (utok / 2 + 1) << " poskozeni!" << endl;
            }
            else {
                cout << "Nemas dost staminy ani na rychly utok! Promarnil jsi tah unavou." << endl;
            }
        }
        else if (utokVolba == 2) {
            if (stamina >= 3) {
                hpPrisery -= utok;
                stamina -= 3;
                cout << "Rozprahnul ses a zasahnul silou za " << utok << " poskozeni!" << endl;
            }
            else {
                cout << "Nemas staminu na silny utok! Prisera se ti vysmiva." << endl;
            }
        }
        else if (utokVolba == 3) {
            if (stamina >= 5) {
                hpPrisery -= (utok + 4);
                stamina -= 5;
                cout << "Pouzil jsi specialni utok [" << specialita << "] a dal zasah za " << utok + 4 << " poskozeni!" << endl;
            }
            else {
                cout << "Na tuhle specialitu jsi az moc vycerpany, utok sel vedle." << endl;
            }
        }
        else {
            cout << "Zmatene koukas a nic nedelas." << endl;
        }

        // tah prisery pokud zije
        if (hpPrisery > 0) {
            hp -= 2; // Sliz je lehky, dava maly damage
            cout << "Lesni sliz po tobe plivnul kyselinu a ubral ti 2 HP!" << endl;
        }
    }

    // Konec hry pokud hrac umre
    if (hp <= 0) {
        cout << "\nZemrel jsi! Rozleptal te Lesni sliz. Hra konci." << endl;
        system("pause");
        return 0;
    }

    // Vyhra nad priserou
    cout << "\n=========================================" << endl;
    cout << "Porazil jsi Lesni sliz!" << endl;
    cout << "Z jeho zbytku jsi ziskal 3 DRAHOKAMY!" << endl;
    drahokamy += 3;

    cout << "Byla to lehka prisera, vraci se ti 5 bodu staminy." << endl;
    stamina += 5;
    if (stamina > maxStamina) {
        stamina = maxStamina;
    }
    cout << "Tvoje aktualni stamina: " << stamina << "/" << maxStamina << endl;
    cout << "=========================================" << endl;

    // --- VESNICE: OBCHOD A SLUŽBY (POUZE JEDNA VOLBA) ---
    cout << "\nPokracujes dal po ceste a po chvili narazis na malou vesnici." << endl;
    cout << "\n--- MISTNI TRH A LAZNETE ---" << endl;
    cout << "Mas " << drahokamy << " drahokamu." << endl;
    cout << "Muzes si vybrat pouze JEDNU z techto sluzeb, pak te mistni vyzenou:" << endl;
    cout << "1. Vylecit se (Plne obnovi HP a Staminu) - Cena: 2 drahokamy" << endl;
    cout << "2. Vylepsit utok (+2 k utoku) - Cena: 3 drahokamy" << endl;
    cout << "3. Vylepsit ochranu (+2 k defense/obrane) - Cena: 3 drahokamy" << endl;
    cout << "4. Odejit (Nic nepotrebujes)" << endl;
    cout << "Tvoje volba akce: ";

    int volbaObchod;
    cin >> volbaObchod;

    if (volbaObchod == 1) {
        if (drahokamy < 2) {
            cout << "\n[!] Tohle udelat nemuzes! Nemas dostatek drahokamu." << endl;
        }
        else if (hp == maxHp && stamina == maxStamina) {
            cout << "\n[!] Tohle udelat nemuzes! Jsi plne vyhealovanej a odpocinutej na max." << endl;
        }
        else {
            hp = maxHp;
            stamina = maxStamina;
            drahokamy -= 2;
            cout << "\n-> Byl jsi uspesne vylecen! Tvoje HP a Stamina jsou na maximu. Ubyly ti 2 drahokamy." << endl;
        }
    }
    else if (volbaObchod == 2) {
        if (drahokamy < 3) {
            cout << "\n[!] Tohle udelat nemuzes! Nemas dostatek drahokamu." << endl;
        }
        else {
            utok += 2;
            drahokamy -= 3;
            cout << "\n-> Tvuj utok byl permanentne zvysen o +2! Aktualni utok: " << utok << ". Ubyly ti 3 drahokamy." << endl;
        }
    }
    else if (volbaObchod == 3) {
        if (drahokamy < 3) {
            cout << "\n[!] Tohle udelat nemuzes! Nemas dostatek drahokamu." << endl;
        }
        else {
            obrana += 2;
            drahokamy -= 3;
            cout << "\n-> Tvoje obrana byla permanentne zvysena o +2! Aktualni obrana: " << obrana << ". Ubyly ti 3 drahokamy." << endl;
        }
    }
    else {
        cout << "\nRozhodl ses, ze nic nepotrebujes a odchazis od stanku." << endl;
    }


    // rozhovory ve smicce
    bool vespolekKecani = true;

    while (vespolekKecani) {
        cout << "\n--- ROZHOVORY S VESNICANY ---" << endl;
        cout << "Koho chces nyni vyslechnout?" << endl;
        cout << "1. Farmar" << endl;
        cout << "2. Maly chlapec" << endl;
        cout << "3. Svadlena" << endl;
        cout << "4. Nikoho (Odejst z vesnice)" << endl;
        cout << "Volba: ";

        int volbaPokec;
        cin >> volbaPokec;

        if (volbaPokec == 1) {
            cout << "\n Jooo, vy se shanite po tech rytirich? Ty me teda vytocili! Oni si sli jen tak vklidu slavit prii nejaky jejich rytual na zacatku kazde mise pro stesti. No, rytual nerytual, kone si neuvazali a ty jejich kone mi spasli pres noc polovinu urody. No jasne, ze se omlouvali, ale pri maji na spech a drahokamu uz jim taky moc nezbylo, ze pri mi to zaplati na ceste zpet. Rikali neco otom, ze jedou lovit mysi do temneho lesa, tak snad se vrati, jinak nebudu mit co zrat, prodavat, ani nebudu mit zadny drahokami. Pokud je potkas tak jim pripomen aby se tu zastavili. " << endl;
           
        }
        else if (volbaPokec == 2) {
            cout << "\nJo, ti ritiri! Pamatuju si tu druzinu. Rikali mi, ze bych jednou mohl byt veliky valecnik, tak mi pujcili mec a helmu, abych si to zkusil, jaky to je. Byli na me hodni, dokonce i kolac mi koupili a pri tu vecer i slavily, ale to uz jsem spal. " << endl;
           
        }
        else if (volbaPokec == 3) {
            cout << "\nJa jsem svadlena, cely den jen siju a siju a z baraku sotva paty na trh vytahnu, ale to vite, ze si je pamatuju. Slavili tady pri nejaky rytual, tak snad se jim vydariil a nic se jim nestalo. Ale presto, ze se tady striskaly, tak nic neznicily a za vsechny sluzby zaplatily. Jediny co, tak jsem slysela, ze farmarovy ty jejich kone spasli urodu, ale to nevim, zeptejte se jeho. " << endl;
           
        }
        else if (volbaPokec == 4) {
            break; // vyskoci z otazek
        }
        else {
            cout << "Takovy clovek tu nestoji." << endl;
            continue;
        }

        // nabydka pro rozhovor
        cout << "\nCo chces udelat nyni?" << endl;
        cout << "1. Pokracovat v ceste" << endl;
        cout << "2. Vyslechnout vesnicany " << endl;
        cout << "Tvoje volba: ";

        int poRozhovoruVolba;
        cin >> poRozhovoruVolba;

        if (poRozhovoruVolba == 1) {
            vespolekKecani = false; // ukonci smycku
        }
    }

   
    cout << "\nOpustil jsi vesnici a stojis pred dalsim rozhodnutim. Kam se vydas ted?" << endl;
    cout << "1 - Pujdes pres listnaty les" << endl;
    cout << "2 - Vydas se pres otevrenou louku" << endl;
    cout << "3 - Vstoupis do tajomneho lesa s fialovymi stromy" << endl;
    cout << "Tvoje volba: ";

    int finalniCesta;
    cin >> finalniCesta;

    if (finalniCesta == 1) {
        
    }
    else if (finalniCesta == 2) {
        
    }
    else if (finalniCesta == 3) {
    }

    cout << "\nStiskni Enter pro ukonceni..." << endl;
    system("pause");
    return 0;
}