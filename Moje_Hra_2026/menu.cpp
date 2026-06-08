#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int ZvolUtok(int& stamina, int maxStamina, int utok, string specialita, string jmeno, bool mensiStamina = false, int extraStamina = 0, bool maAmulet = false, int* hp = nullptr, int maxHp = 0) {
    string nazev1 = (jmeno == "Prokop") ? "Bodnuti propiskou" : "Rychly utok";
    string nazev2 = (jmeno == "Prokop") ? "Rana tezkym sesitem" : "Silny utok";

    int cenaUtoku1 = 1 + extraStamina;
    int cenaUtoku2 = (mensiStamina ? 2 : 3) + extraStamina;
    int cenaUtoku3 = (mensiStamina ? 3 : 5) + extraStamina;

    cout << "1. " << nazev1 << " (" << cenaUtoku1 << " staminy, DMG: " << utok / 2 + 1 << ")\n";
    cout << "2. " << nazev2 << " (" << cenaUtoku2 << " staminy, DMG: " << utok << ")\n";
    cout << "3. " << specialita << " (" << cenaUtoku3 << " staminy, DMG: " << utok + 4 << ")\n";

    if (stamina == 0) {
        cout << "4. Doplnit staminu (Nahodne 1-5)\n";
    }
    if (maAmulet && hp != nullptr) {
        cout << "5. Pouzit Amulet Zivota (3 staminy, Heal 3-20 HP)\n";
    }

    cout << "Volba: ";

    int volba;
    cin >> volba;

    if (volba == 1 && stamina >= cenaUtoku1) {
        stamina -= cenaUtoku1;
        cout << "Pouzil jsi " << nazev1 << " a zasahl za " << (utok / 2 + 1) << " poskozeni!" << endl;
        return utok / 2 + 1;
    }
    if (volba == 2 && stamina >= cenaUtoku2) {
        stamina -= cenaUtoku2;
        cout << "Pouzil jsi " << nazev2 << " a zasahl silou za " << utok << " poskozeni!" << endl;
        return utok;
    }
    if (volba == 3 && stamina >= cenaUtoku3) {
        stamina -= cenaUtoku3;
        cout << "Pouzil jsi specialni utok [" << specialita << "] a dal zasah za " << utok + 4 << " poskozeni!" << endl;
        return utok + 4;
    }
    if (volba == 4 && stamina == 0) {
        int obnova = rand() % 5 + 1;
        stamina += obnova;
        if (stamina > maxStamina) stamina = maxStamina;
        cout << "Zhluboka ses nadechl a doplnil jsi " << obnova << " staminy!" << endl;
        return 0;
    }
    if (volba == 5 && maAmulet && stamina >= 3 && hp != nullptr) {
        stamina -= 3;
        int heal = rand() % 18 + 3;
        *hp += heal;
        if (*hp > maxHp) *hp = maxHp;
        cout << "Amulet zivota zazaril! Vylecil ses o " << heal << " HP. (Aktualni HP: " << *hp << "/" << maxHp << ")" << endl;
        return 0;
    }

    cout << "Nemas dost staminy nebo jsi nezadal spravnou volbu! Promarnil jsi tah." << endl;
    return 0;
}

void PridejXP(int ziskaneXP, int& xp, int& level, int& xpDoDalsihoLevelu, int& hp, int& maxHp, int& utok) {
    xp += ziskaneXP;
    cout << "Ziskavas " << ziskaneXP << " XP! (Aktualne: " << xp << "/" << xpDoDalsihoLevelu << ")" << endl;
    if (xp >= xpDoDalsihoLevelu) {
        level++;
        maxHp += 5;
        hp = maxHp;
        utok += 1;
        xp = xp - xpDoDalsihoLevelu;
        xpDoDalsihoLevelu += 10;
        cout << "*** NOVY LEVEL! Jsi nyni level " << level << " ***" << endl;
        cout << "*** Tvoje maximalni HP se zvysilo na " << maxHp << " a jsi plne vylecen! ***" << endl;
    }
}

int main() {
    srand(time(0));
    int volbaHlavni;
    bool hraceVybral = false;
    system("color B0");

    string jmeno;
    int hp = 0, utok = 0, obrana = 0, stamina = 0;
    int maxStamina = 0, maxHp = 0;
    string specialita = "Zadna";
    int drahokamy = 0, xp = 0, level = 1, xpDoDalsihoLevelu = 20;

    bool maAmuletZivota = false;
    bool maAmuletCistoty = false;

    cout << "=== VITEJ VE HRE ===" << endl;

    while (true) {
        cout << "\n--- HLAVNI MENU ---" << endl;
        cout << "1. Zvolit postavu\n2. Hrat\n3. Ukoncit\nTvoje volba: ";
        cin >> volbaHlavni;

        if (volbaHlavni == 1) {
            cout << "\nVyber si hrdinu:" << endl;
            cout << "1. Rytir\n2. Carodej\n3. Lucistnik\n4. Assassin\nVyber: ";
            int volbaPostavy;
            cin >> volbaPostavy;


            if (volbaPostavy == 1) { jmeno = "Rytir"; hp = 30; utok = 12; obrana = 11; stamina = 15; specialita = "Mec a stit"; }
            else if (volbaPostavy == 16) { jmeno = "Prokop"; hp = 100; utok = 100; obrana = 100; stamina = 100; specialita = "Jednicka z programovani"; }
            else if (volbaPostavy == 2) { jmeno = "Carodej"; hp = 20; utok = 10; obrana = 5; stamina = 10; specialita = "Magicka hul"; }
            else if (volbaPostavy == 3) { jmeno = "Lucistnik"; hp = 15; utok = 13; obrana = 5; stamina = 13; specialita = "Luk a sipy"; }
            else if (volbaPostavy == 4) { jmeno = "Assassin"; hp = 25; utok = 15; obrana = 5; stamina = 7; specialita = "Dvojita dyka"; }
            else { cout << "Spatna volba, davam ti Rytire." << endl; jmeno = "Rytir"; hp = 30; utok = 12; obrana = 11; stamina = 15; specialita = "Mec a stit"; }

            maxStamina = stamina; maxHp = hp;
            hraceVybral = true;

            cout << "\n--> Tvoje postava je nyni: " << jmeno << " <--" << endl;
            cout << "Staty: HP: " << hp << " | Utok: " << utok << " | Obrana: " << obrana << " | Stamina: " << stamina << "\nSpecialita: " << specialita << endl;
        }
        else if (volbaHlavni == 2) {
            if (!hraceVybral) cout << "\n!!! Pozor: Nejdriv si musis vybrat postavu (volba 1) !!!" << endl;
            else {
                cout << "\n==================================================================" << endl;
                cout << "Kral si te nechal urgentne povolat!\nZada te o pomoc. Jeho nejlepsi vojsko slo na lov mysi do Temneho lesa...\n...jenze se NEOZVALI a NEVRATILI. Nezbyly po nich ZADNE stopy." << endl;
                cout << "\nKral si zada prave tebe kvuli tvym zkusenostem a hrdinske povesti!\nKdyz najdes his druzinu, da ti pokladnici PLNOU ZLATA\na tvoje slava bude tak uchvatna, ze te budou znat VSOUDE!" << endl;
                cout << "==================================================================" << endl;
                cout << "\nPomozes krali v teto tezke chvili?\n1. Ano, prijmam tvuj ukol, krali!\n2. Ne, tohle me nezajima. Odchazim.\nTvoje volba: ";
                int volbaPomoci;
                cin >> volbaPomoci;

                if (volbaPomoci == 2) { cout << "\nGAME OVER: Kral te nechal POPRAVIT za nedostatek ucty k nemu!" << endl; return 0; }
                else if (volbaPomoci == 16) { cout << "\nWIN: Zabil jsi krale a ostatni strazni se ti poddali. Ted jsi kralem ty!" << endl; return 0; }
                else if (volbaPomoci == 1) {
                    cout << "\nDo sluzeb krale nastupuje hrdina... " << jmeno << "!" << endl;
                    drahokamy += 3;
                    cout << "Kral ti na zacatek tve vypravy dal 3 drahokamy, at si po ceste muzes neco poridit." << endl;
                    break;
                }
            }
        }
        else if (volbaHlavni == 3) { cout << "Koncim program..." << endl; return 0; }
        else cout << "Neznama volba v menu!" << endl;
    }

    cout << "\nOcitl ses na zacatku tve vypravy a pred sebou vidis dve cesty. Kterou si vyberes?" << endl;
    cout << "1 - Stary most, ktery vede pres reku\n2 - Cesta rovnou do husteho lesa\nTvoje volba: ";
    int cesta; cin >> cesta;

    if (cesta == 1) {
        drahokamy -= 1;
        cout << "\nSpatna volba! Jakmile jsi stoupl na stary most, prkna praskla a ty jsi spadl do reky!\nTezce jsi doplaval na breh. Ztratil jsi cas a ve vode jsi ztratil 1 drahokam! Musis pokracovat jedinou moznou cestou - do husteho lesa." << endl;
    }
    else {
        cout << "\nRozhodl ses pro jistotu a jdes rovnou po ceste do husteho lesa." << endl;
    }

    cout << "\nZ krovi na tebe vyskocila prisera: [LEHKE] Lesni sliz!" << endl;
    int hpPrisery = 10;
    while (hp > 0 && hpPrisery > 0) {
        cout << "\nTVOJE HP: " << hp << " | TVOJE STAMINA: " << stamina << "/" << maxStamina << "\nHP SLIZU: " << hpPrisery << endl;
        int udelenePoskozeni = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, false, 0, maAmuletZivota, &hp, maxHp);
        if (udelenePoskozeni > 0) {
            hpPrisery -= udelenePoskozeni;
            if (hpPrisery <= 0) {
                stamina = min(maxStamina, stamina + 5);
                drahokamy += 2;
                cout << "Zabil jsi Lesni sliz! Ziskavas 5 staminy a 2 drahokamy." << endl;
            }
        }
        if (hpPrisery > 0) {
            int utrpeno = 2 - (obrana / 12);
            if (utrpeno < 0) utrpeno = 0;
            hp -= utrpeno;
            cout << "[LEHKE] Lesni sliz po tobe plivnul kyselinu a ubral ti " << utrpeno << " HP!" << endl;
        }
    }
    if (hp <= 0) { cout << "\nZemrel jsi! Rozleptal te Lesni sliz. Hra konci." << endl; system("pause"); return 0; }

    PridejXP(10, xp, level, xpDoDalsihoLevelu, hp, maxHp, utok);
    hp = min(maxHp, hp + 10);
    cout << "*** Vycistil jsi cestu! Odpocinul sis a doplnilo se ti 10 HP. (Aktualni HP: " << hp << "/" << maxHp << ") ***" << endl;

    cout << "\n==================================================================" << endl;
    cout << "[INFO O HRE]" << endl;
    cout << "Po kazdem zabiti prisery obdrzis urcity pocet staminy a drahokamu podle obtiznosti:" << endl;
    cout << "- LEHKE: Dostanes 2 drahokamy a vrati se ti 5 staminy." << endl;
    cout << "- STREDNI: Dostanes 4 drahokamy a vrati se ti 2 staminy." << endl;
    cout << "- MINI-BOSS: Dostanes 8 drahokamu a vrati se ti 1 stamina." << endl;
    cout << "- BOSS: Nikdo nevi kdo ani co to je..." << endl;
    cout << "Budes si vybirat z nekolika rozcesti a az zabijes vsechna monstra na tom danem rozcesti, vzdy se ti doplni 10 zivotu!" << endl;
    cout << "Tezsi monstra maji specialni vlastnosti (RYCHLY, BRNENI, DALKA, JED)." << endl;
    cout << "==================================================================" << endl;

    cout << "\nPokracujes po ceste a narazis na vesnici." << endl;
    cout << "--- VESNICE 1 ---" << endl;
    cout << "Mas " << drahokamy << " drahokamu.\nMuzes si vybrat pouze JEDNU z techto sluzeb, pak te mistni z obchodu vyzenou:\n1. Vylecit se (Plne obnovi HP a Staminu) - Cena: 2 drahokamy\n2. Vylepsit utok (+2 k utoku) - Cena: 3 drahokamy\n3. Vylepsit ochranu (+5 k defense/obrane) - Cena: 3 drahokamy\n4. Odejit (Nic nepotrebujes)\nTvoje volba akce: ";
    int volbaObchod; cin >> volbaObchod;
    if (volbaObchod == 1) {
        if (drahokamy < 2) cout << "\n[!] Nemas dostatek drahokamu." << endl;
        else if (hp == maxHp && stamina == maxStamina) cout << "\n[!] Jsi plne vyleceny." << endl;
        else { hp = maxHp; stamina = maxStamina; drahokamy -= 2; cout << "\n-> Byl jsi uspesne vylecen!" << endl; }
    }
    else if (volbaObchod == 2) {
        if (drahokamy < 3) cout << "\n[!] Nemas dostatek drahokamu." << endl;
        else { utok += 2; drahokamy -= 3; cout << "\n-> Tvuj utok byl zvysen na: " << utok << endl; }
    }
    else if (volbaObchod == 3) {
        if (drahokamy < 3) cout << "\n[!] Nemas dostatek drahokamu." << endl;
        else { obrana += 5; drahokamy -= 3; cout << "\n-> Tvoje obrana byla zvysena na: " << obrana << endl; }
    }

    bool vespolekKecani = true;
    while (vespolekKecani) {
        cout << "\n--- ROZHOVORY S MISTNIMI ---\nKoho chces vyslechnout?\n1. Maly chlapec\n2. Svadlena\n3. Farmar\n4. Nikoho (Odejit z vesnice)\nVolba: ";
        int volbaPokec; cin >> volbaPokec;
        if (volbaPokec == 1) cout << "Jo ty si pamatuju rikaly ze jsou rytirove a ze bych taky mohl byt a pujcili mi helmu a mec byli na me hodni a slysel jsem neco ze tu vecer slavily ale to ja uz spal." << endl;
        else if (volbaPokec == 2) cout << "\nNo to vite ja celej den sedim doma a siju a siju sotva vystrcim paty z baraku na trh ale vim ze pri tu slavily ale nevim proc. Vite co farmar byl nastvanej on vam to rekne zeptejte se jeho." << endl;
        else if (volbaPokec == 3) cout << "Jo ty pacholky si pamatuju jo jako chovali se slusne a celou noc slavily a pily ze pri nejaky ritual pred misi ale neuvazali si ty svoje kone a pres noc mi ty jejich kobyly spradali pulku moji urody. No jo omlouvali se a ze drahokamy budou mit vic na ceste zpet tak snad se vrati a zaplati mi to." << endl;
        else if (volbaPokec == 4) break;
        else cout << "Takovy clovek tu neni." << endl;
    }

    cout << "\nVyrazils dal na cestu. Pred sebou mas rozcesti. Kudy pujdes?" << endl;
    cout << "1 - Pres listnaty les\n2 - Pres otevrenou louku (pole)\n3 - Do tajemneho lesa s fialovymi stromy\nTvoje volba: ";
    int finalniCesta; cin >> finalniCesta;

    if (finalniCesta == 1) {
        cout << "\n--- LISTNATY LES ---" << endl;
        int hpLehke = 10; string jmLehke = "[LEHKE] Zelena housenka";
        int hpStredni = 20; string jmStredni = "[STREDNI] Lesni troll";

        while (hp > 0 && (hpLehke > 0 || hpStredni > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpLehke > 0) cout << "[1] HP " << jmLehke << ": " << hpLehke << endl;
            if (hpStredni > 0) cout << "[2] HP " << jmStredni << ": " << hpStredni << " (BRNENI)" << endl;
            int cil = 1;
            if (hpLehke > 0 && hpStredni > 0) { cout << "Kdo bude tvuj cil? (1 nebo 2): "; cin >> cil; }
            else cil = (hpLehke > 0) ? 1 : 2;

            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, false, 0, maAmuletZivota, &hp, maxHp);
            if (dmg > 0) {
                if (cil == 1 && hpLehke > 0) {
                    hpLehke -= dmg;
                    if (hpLehke <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << jmLehke << " mrtva!" << endl; }
                }
                else if (cil == 2 && hpStredni > 0) {
                    cout << "Vysvetlivka: Toto monstrum ma brneni, davas mu o 1 poskozeni mene!" << endl;
                    dmg -= 1; if (dmg < 0) dmg = 0;
                    hpStredni -= dmg;
                    if (hpStredni <= 0) { stamina = min(maxStamina, stamina + 2); drahokamy += 4; cout << jmStredni << " mrtev!" << endl; }
                }
            }
            if (hpLehke > 0) {
                int utrpeno = 2 - (obrana / 12); if (utrpeno < 0) utrpeno = 0; hp -= utrpeno;
                cout << jmLehke << " te kousla za " << utrpeno << " HP!" << endl;
            }
            if (hpStredni > 0) {
                int utrpeno = 4 - (obrana / 12); if (utrpeno < 0) utrpeno = 0; hp -= utrpeno;
                cout << jmStredni << " te majznul za " << utrpeno << " HP!" << endl;
            }
        }
    }
    else if (finalniCesta == 2) {
        cout << "\n--- OTEVRENA LOUKA (POLE) ---" << endl;
        int hpLehke = 8; string jmLehke = "[LEHKE] Vztekle kliste";
        int hpStredni = 15; string jmStredni = "[STREDNI] Skreti pruzkumnik";

        cout << "Vysvetlivka: " << jmStredni << " je extremne rychly, utoci jako prvni nez vubec zacne tah!" << endl;
        int utrpenoPreb = 3 - (obrana / 12); if (utrpenoPreb < 0) utrpenoPreb = 0; hp -= utrpenoPreb;
        cout << jmStredni << " te bodl a ubral " << utrpenoPreb << " HP!" << endl;

        while (hp > 0 && (hpLehke > 0 || hpStredni > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpLehke > 0) cout << "[1] HP " << jmLehke << ": " << hpLehke << endl;
            if (hpStredni > 0) cout << "[2] HP " << jmStredni << ": " << hpStredni << " (RYCHLY)" << endl;
            int cil = 1;
            if (hpLehke > 0 && hpStredni > 0) { cout << "Kdo bude tvuj cil? (1 nebo 2): "; cin >> cil; }
            else cil = (hpLehke > 0) ? 1 : 2;

            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, false, 0, maAmuletZivota, &hp, maxHp);
            if (dmg > 0) {
                if (cil == 1 && hpLehke > 0) {
                    hpLehke -= dmg;
                    if (hpLehke <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << jmLehke << " mrtve!" << endl; }
                }
                else if (cil == 2 && hpStredni > 0) {
                    hpStredni -= dmg;
                    if (hpStredni <= 0) { stamina = min(maxStamina, stamina + 2); drahokamy += 4; cout << jmStredni << " mrtev!" << endl; }
                }
            }
            if (hpLehke > 0) {
                int utrpeno = 2 - (obrana / 12); if (utrpeno < 0) utrpeno = 0; hp -= utrpeno;
                cout << jmLehke << " te kouslo za " << utrpeno << " HP!" << endl;
            }
            if (hpStredni > 0) {
                int utrpeno = 3 - (obrana / 12); if (utrpeno < 0) utrpeno = 0; hp -= utrpeno;
                cout << jmStredni << " te sekl za " << utrpeno << " HP!" << endl;
            }
        }
    }
    else {
        cout << "\n--- FIALOVY LES ---" << endl;
        int hpBoss = 35; string jmBoss = "[MINI-BOSS] Stin lesu";

        cout << "Vysvetlivka: " << jmBoss << " je extremne rychly, utoci jako prvni!" << endl;
        int utrpenoPreb = 5 - (obrana / 12); if (utrpenoPreb < 0) utrpenoPreb = 0; hp -= utrpenoPreb;
        cout << "Stin ubral " << utrpenoPreb << " HP jeste nez jsi stihl zareagovat!" << endl;

        while (hp > 0 && hpBoss > 0) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << "\nHP " << jmBoss << ": " << hpBoss << " (RYCHLY, JED)" << endl;
            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, false, 0, maAmuletZivota, &hp, maxHp);
            if (dmg > 0) {
                hpBoss -= dmg;
                if (hpBoss <= 0) { stamina = min(maxStamina, stamina + 1); drahokamy += 8; cout << jmBoss << " mrtev!" << endl; }
            }
            if (hpBoss > 0) {
                int utrpeno = 4 - (obrana / 12); if (utrpeno < 0) utrpeno = 0; hp -= utrpeno;
                cout << jmBoss << " te zasahl za " << utrpeno << " HP!" << endl;
                int jed = rand() % 3 + 1;
                hp -= jed;
                cout << "Vysvetlivka: Dokud bojujes s timto monstrem, jsi otraveny! Jed ti ubral dalsich nahodnych " << jed << " HP." << endl;
            }
        }
    }

    if (hp <= 0) { cout << "\nZemrel jsi v boji! Hra konci." << endl; system("pause"); return 0; }
    PridejXP(15, xp, level, xpDoDalsihoLevelu, hp, maxHp, utok);
    hp = min(maxHp, hp + 10);
    cout << "*** Vycistil jsi rozcesti! Odpocinul sis a doplnilo se ti 10 HP. (Aktualni HP: " << hp << "/" << maxHp << ") ***" << endl;

    cout << "\nJdes dal a uvidis zvlastni kamen." << endl;
    cout << "Hrac: Achh, jsem unaveny. Sednu si a odpocinu." << endl;
    cout << "???: Au au au! Slez ze me ty grazle, pripadam ti jako lavicka? Vis ty vubec, kdo ja jsem?" << endl;
    cout << "Hrac: Co... co to bylo? Kdo mluvi?" << endl;
    cout << "???: Tady dole! Ja jsem moudry kamen." << endl;
    cout << "Kamen: Pomuzu ti, jen kdyz uhodnes tri hadanky! (odpovidej malymi pismeny a bez diakritiky)" << endl;

    int pocetUhodnutych = 0;
    bool mensiStaminaCena = false;
    bool radaDoVesnice = false;
    string odpovedHrace;

    cout << "\n1. Strazce vedeni\n\"Nemam usta, ale mluvim ke vsem, kdo me otevrou. Nemam nohy, ale zavedu te do dalekych risi. Moje kuze je z pergamenu ci kuze zvirat a krev mi nahrazuje cerny inkoust. Kdo jsem?\"" << endl;
    cout << "Tvoje odpoved: "; cin >> odpovedHrace;
    if (odpovedHrace == "kniha") {
        pocetUhodnutych++;
        cout << "Spravne!\n\n2. Poutnik noci\n\"Narodim se ve stinu, zemru v prvnim paprsku slunce. Pronasleduji te na kazdem kroku, ale nikdy se me nedotknes. Jsem vernym sluhou svetla, a presto bez tmy bych nebyl nicim. Kdo jsem?\"" << endl;
        cout << "Tvoje odpoved: "; cin >> odpovedHrace;
        if (odpovedHrace == "stin") {
            pocetUhodnutych++;
            cout << "Spravne!\n\n3. Dech zeme\n\"Jsem neviditelny, ale slysis me zpivat v korunach stromu. Nemam ruce, ale dokazu lamat skaly a plnit plachty lodi. Jsem prvnim nadechem novorozenete i poslednim vzdychnutim skomirajiciho ohen. Co jsem?\"" << endl;
            cout << "Tvoje odpoved: "; cin >> odpovedHrace;
            if (odpovedHrace == "vitr") pocetUhodnutych++;
        }
    }

    if (pocetUhodnutych == 0) cout << "Kamen: Tak to je dost bidna zachrana..." << endl;
    else if (pocetUhodnutych == 1) { cout << "Kamen: No nic moc.\n[Trvale snizeni potrebne staminy na utoky!]" << endl; mensiStaminaCena = true; }
    else if (pocetUhodnutych == 2) { cout << "Kamen: Ty mas potencial.\n[Snizeni staminy and +20 drahokamu!]" << endl; mensiStaminaCena = true; drahokamy += 20; }
    else if (pocetUhodnutych == 3) { cout << "Kamen: Ty jsi vyvoleny! V opustene vesnici najdes zbroj.\n[Snizeni staminy, +20 drahokamu a tajna rada!]" << endl; mensiStaminaCena = true; drahokamy += 20; radaDoVesnice = true; }

    cout << "\nPo rozhovoru jdes dal a stojis pred rozcestim:" << endl;
    cout << "1 - Pres Obycejny les\n2 - Pres Opustenou vesnici\n3 - Po Zapomenute stezce\nTvoje volba: ";
    int volbaDalsi; cin >> volbaDalsi;

    if (volbaDalsi == 1) {
        int hpLehke1 = 10, dmgLehke1 = 2; string jmLehke1 = "[LEHKE] Zmutovana zaba";
        int hpLehke2 = 12, dmgLehke2 = 2; string jmLehke2 = "[LEHKE] Zdivocely pes";
        int hpStredni = 20, dmgStredni = 4; string jmStredni = "[STREDNI] Temny dryad";

        while (hp > 0 && (hpLehke1 > 0 || hpLehke2 > 0 || hpStredni > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpLehke1 > 0) cout << "[1] HP " << jmLehke1 << ": " << hpLehke1 << endl;
            if (hpLehke2 > 0) cout << "[2] HP " << jmLehke2 << ": " << hpLehke2 << endl;
            if (hpStredni > 0) cout << "[3] HP " << jmStredni << ": " << hpStredni << " (DALKA)" << endl;

            int cil = 0; cout << "Kdo bude tvuj cil? (1, 2 nebo 3): "; cin >> cil;
            int extraStam = (cil == 3 && hpStredni > 0) ? 1 : 0;
            if (extraStam > 0) cout << "Vysvetlivka: Toto monstrum je daleko, takze na utok spotrebujes o 1 staminu vice!" << endl;

            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena, extraStam, maAmuletZivota, &hp, maxHp);
            if (dmg > 0) {
                if (cil == 1 && hpLehke1 > 0) { hpLehke1 -= dmg; if (hpLehke1 <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << jmLehke1 << " mrtev!" << endl; } }
                else if (cil == 2 && hpLehke2 > 0) { hpLehke2 -= dmg; if (hpLehke2 <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << jmLehke2 << " mrtev!" << endl; } }
                else if (cil == 3 && hpStredni > 0) { hpStredni -= dmg; if (hpStredni <= 0) { stamina = min(maxStamina, stamina + 2); drahokamy += 4; cout << jmStredni << " mrtev!" << endl; } }
            }
            if (hpLehke1 > 0) { int u = dmgLehke1 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpLehke2 > 0) { int u = dmgLehke2 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpStredni > 0) { int u = dmgStredni - (obrana / 12); if (u < 0) u = 0; hp -= u; }
        }
    }
    else if (volbaDalsi == 2) {
        if (radaDoVesnice) { cout << "\nDiky rade od kamene nachazis skrytou truhlu! Obrana +5." << endl; obrana += 5; }
        int hpLehke1 = 12, dmgLehke1 = 2; string jmLehke1 = "[LEHKE] Kostlivec";
        int hpLehke2 = 10, dmgLehke2 = 2; string jmLehke2 = "[LEHKE] Nakazena krysa";
        int hpStredni = 18, dmgStredni = 4; string jmStredni = "[STREDNI] Nemrtvy farmar";

        while (hp > 0 && (hpLehke1 > 0 || hpLehke2 > 0 || hpStredni > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpLehke1 > 0) cout << "[1] HP " << jmLehke1 << ": " << hpLehke1 << endl;
            if (hpLehke2 > 0) cout << "[2] HP " << jmLehke2 << ": " << hpLehke2 << endl;
            if (hpStredni > 0) cout << "[3] HP " << jmStredni << ": " << hpStredni << " (BRNENI)" << endl;
            int cil = 0; cout << "Kdo bude tvuj cil? (1, 2 nebo 3): "; cin >> cil;
            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena, 0, maAmuletZivota, &hp, maxHp);
            if (dmg > 0) {
                if (cil == 1 && hpLehke1 > 0) { hpLehke1 -= dmg; if (hpLehke1 <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << jmLehke1 << " mrtev!" << endl; } }
                else if (cil == 2 && hpLehke2 > 0) { hpLehke2 -= dmg; if (hpLehke2 <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << jmLehke2 << " mrtva!" << endl; } }
                else if (cil == 3 && hpStredni > 0) {
                    cout << "Vysvetlivka: Toto monstrum ma brneni, davas o 1 poskozeni mene!" << endl;
                    dmg -= 1; if (dmg < 0) dmg = 0;
                    hpStredni -= dmg;
                    if (hpStredni <= 0) { stamina = min(maxStamina, stamina + 2); drahokamy += 4; cout << jmStredni << " mrtev!" << endl; }
                }
            }
            if (hpLehke1 > 0) { int u = dmgLehke1 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpLehke2 > 0) { int u = dmgLehke2 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpStredni > 0) { int u = dmgStredni - (obrana / 12); if (u < 0) u = 0; hp -= u; }
        }
    }
    else {
        int hpLehke1 = 10, dmgLehke1 = 2; string jmLehke1 = "[LEHKE] Maly pavouk";
        int hpLehke2 = 10, dmgLehke2 = 2; string jmLehke2 = "[LEHKE] Krvavy komar";
        int hpStredni = 22, dmgStredni = 5; string jmStredni = "[STREDNI] Obri pavouci matka";

        while (hp > 0 && (hpLehke1 > 0 || hpLehke2 > 0 || hpStredni > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpLehke1 > 0) cout << "[1] HP " << jmLehke1 << ": " << hpLehke1 << endl;
            if (hpLehke2 > 0) cout << "[2] HP " << jmLehke2 << ": " << hpLehke2 << endl;
            if (hpStredni > 0) cout << "[3] HP " << jmStredni << ": " << hpStredni << " (JED)" << endl;

            int cil = 0; cout << "Kdo bude tvuj cil? (1, 2 nebo 3): "; cin >> cil;
            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena, 0, maAmuletZivota, &hp, maxHp);
            if (dmg > 0) {
                if (cil == 1 && hpLehke1 > 0) { hpLehke1 -= dmg; if (hpLehke1 <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << jmLehke1 << " mrtev!" << endl; } }
                else if (cil == 2 && hpLehke2 > 0) { hpLehke2 -= dmg; if (hpLehke2 <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << jmLehke2 << " mrtev!" << endl; } }
                else if (cil == 3 && hpStredni > 0) { hpStredni -= dmg; if (hpStredni <= 0) { stamina = min(maxStamina, stamina + 2); drahokamy += 4; cout << jmStredni << " mrtva!" << endl; } }
            }
            if (hpLehke1 > 0) { int u = dmgLehke1 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpLehke2 > 0) { int u = dmgLehke2 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpStredni > 0) {
                int u = dmgStredni - (obrana / 12); if (u < 0) u = 0; hp -= u;
                int jed = rand() % 3 + 1; hp -= jed;
                cout << "Vysvetlivka: Jsi otraveny! Jed ubral dalsich " << jed << " HP." << endl;
            }
        }
    }

    if (hp <= 0) { cout << "\nZemrel jsi v boji! Hra konci." << endl; system("pause"); return 0; }
    PridejXP(15, xp, level, xpDoDalsihoLevelu, hp, maxHp, utok);
    hp = min(maxHp, hp + 10);
    cout << "*** Vycistil jsi rozcesti! Odpocinul sis a doplnilo se ti 10 HP. (Aktualni HP: " << hp << "/" << maxHp << ") ***" << endl;

    cout << "\nJdes dal a pred tebou je dalsi rozcesti:" << endl;
    cout << "1 - Preplavat reku na lodicce uvazane u brehu\n2 - Jit pres jeskyni\nTvoje volba: ";
    int volbaReka; cin >> volbaReka;

    if (volbaReka == 1) {
        int hpLehke = 10, dmgLehke = 2; string jmLehke = "[LEHKE] Bahnak";
        int hpStredni = 25, dmgStredni = 4; string jmStredni = "[STREDNI] Vodni had";

        cout << "Vysvetlivka: " << jmStredni << " je extremne rychly a utoci jako prvni!" << endl;
        int utrpenoPreb = 3 - (obrana / 12); if (utrpenoPreb < 0) utrpenoPreb = 0; hp -= utrpenoPreb;
        cout << "Vodni had te stahl pod vodu a ubral " << utrpenoPreb << " HP!" << endl;

        while (hp > 0 && (hpLehke > 0 || hpStredni > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpLehke > 0) cout << "[1] HP " << jmLehke << ": " << hpLehke << endl;
            if (hpStredni > 0) cout << "[2] HP " << jmStredni << ": " << hpStredni << " (RYCHLY)" << endl;

            int cil = 1;
            if (hpLehke > 0 && hpStredni > 0) { cout << "Kdo bude tvuj cil? (1 nebo 2): "; cin >> cil; }
            else cil = (hpLehke > 0) ? 1 : 2;

            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena, 0, maAmuletZivota, &hp, maxHp);
            if (dmg > 0) {
                if (cil == 1 && hpLehke > 0) { hpLehke -= dmg; if (hpLehke <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << jmLehke << " mrtev!" << endl; } }
                else if (cil == 2 && hpStredni > 0) { hpStredni -= dmg; if (hpStredni <= 0) { stamina = min(maxStamina, stamina + 2); drahokamy += 4; cout << jmStredni << " mrtev!" << endl; } }
            }
            if (hpLehke > 0) { int u = dmgLehke - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpStredni > 0) { int u = dmgStredni - (obrana / 12); if (u < 0) u = 0; hp -= u; }
        }
    }
    else {
        int hpLehke = 10, dmgLehke = 2; string jmLehke = "[LEHKE] Netopyr";
        int hpBoss = 30, dmgBoss = 5; string jmBoss = "[MINI-BOSS] Kamenny golem";

        while (hp > 0 && (hpLehke > 0 || hpBoss > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpLehke > 0) cout << "[1] HP " << jmLehke << ": " << hpLehke << endl;
            if (hpBoss > 0) cout << "[2] HP " << jmBoss << ": " << hpBoss << " (BRNENI)" << endl;

            int cil = 1;
            if (hpLehke > 0 && hpBoss > 0) { cout << "Kdo bude tvuj cil? (1 nebo 2): "; cin >> cil; }
            else cil = (hpLehke > 0) ? 1 : 2;

            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena, 0, maAmuletZivota, &hp, maxHp);
            if (dmg > 0) {
                if (cil == 1 && hpLehke > 0) { hpLehke -= dmg; if (hpLehke <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << jmLehke << " mrtev!" << endl; } }
                else if (cil == 2 && hpBoss > 0) {
                    cout << "Vysvetlivka: Toto monstrum ma brneni, davas o 1 poskozeni mene!" << endl;
                    dmg -= 1; if (dmg < 0) dmg = 0;
                    hpBoss -= dmg;
                    if (hpBoss <= 0) { stamina = min(maxStamina, stamina + 1); drahokamy += 8; cout << jmBoss << " mrtev!" << endl; }
                }
            }
            if (hpLehke > 0) { int u = dmgLehke - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpBoss > 0) { int u = dmgBoss - (obrana / 12); if (u < 0) u = 0; hp -= u; }
        }
    }

    if (hp <= 0) { cout << "\nZemrel jsi v boji! Hra konci." << endl; system("pause"); return 0; }
    PridejXP(20, xp, level, xpDoDalsihoLevelu, hp, maxHp, utok);
    hp = min(maxHp, hp + 10);
    cout << "*** Vycistil jsi rozcesti! Odpocinul sis a doplnilo se ti 10 HP. (Aktualni HP: " << hp << "/" << maxHp << ") ***" << endl;

    cout << "\nJdes dal a narazis na mnohem vetsi vesnici." << endl;
    cout << "--- VESNICE 2 ---" << endl;
    cout << "Sluzby zde stoji vice, ale muzes si nyni vybrat DVE ruzne veci." << endl;

    int nakupy = 0;
    while (nakupy < 2) {
        cout << "\nMas " << drahokamy << " drahokamu. (Vyuzite nakupy: " << nakupy << " ze 2)" << endl;
        cout << "1. Vylecit se (Plne obnovi HP a Staminu) - Cena: 5 drahokamu\n2. Vylepsit utok (+2 k utoku) - Cena: 7 drahokamu\n3. Vylepsit ochranu (+5 k defense/obrane) - Cena: 7 drahokamu\n4. Odejit z obchodu\nTvoje volba: ";
        int volbaObchod2; cin >> volbaObchod2;

        if (volbaObchod2 == 1) {
            if (drahokamy < 5) cout << "\n[!] Nemas dostatek drahokamu." << endl;
            else if (hp == maxHp && stamina == maxStamina) cout << "\n[!] Jsi plne vyleceny." << endl;
            else { hp = maxHp; stamina = maxStamina; drahokamy -= 5; cout << "\n-> Byl jsi uspesne vylecen!" << endl; nakupy++; }
        }
        else if (volbaObchod2 == 2) {
            if (drahokamy < 7) cout << "\n[!] Nemas dostatek drahokamu." << endl;
            else { utok += 2; drahokamy -= 7; cout << "\n-> Tvuj utok byl zvysen na: " << utok << endl; nakupy++; }
        }
        else if (volbaObchod2 == 3) {
            if (drahokamy < 7) cout << "\n[!] Nemas dostatek drahokamu." << endl;
            else { obrana += 5; drahokamy -= 7; cout << "\n-> Tvoje obrana byla zvysena na: " << obrana << endl; nakupy++; }
        }
        else if (volbaObchod2 == 4) break;
        else cout << "Neznama volba." << endl;
    }

    bool vespolekKecani2 = true;
    while (vespolekKecani2) {
        cout << "\n--- ROZHOVORY S MISTNIMI ---\nKoho chces nyni vyslechnout?\n1. Starosta\n2. Stara blazniva zenska\n3. Prodavac\n4. Nikoho (Odejit z vesnice)\nVolba: ";
        int volbaPokec2; cin >> volbaPokec2;
        if (volbaPokec2 == 1) cout << "No to vite ze si je pamatuju ale byly nejaci divni nevim co se jim mohlo stat po ceste nejaky z tech kluku znam od mala ale nepoznali me a byly jako by zazily neco fakt hroznyho." << endl;
        else if (volbaPokec2 == 2) cout << "Hej hej ja vim ja to citila citila jsem z nich temnou energii ne jenom ze zazily neco hrozneho ale neco je posedlo neco musite mi verit. Nikdo mi neveri ale ja to vim muze za to ztraceny bratr naseho krale ale nikdo mi neveri." << endl;
        else if (volbaPokec2 == 3) cout << "Bylo mi jich lito moc nemluvily a nic nedelali jen tu prespali ani penize nemely tak jsem jim dal pulku chleba a nejakou zeleninu a dal jsem vodu jejich konim ikdyz prijeli bez jednoho a jednoho jsme tady museli utratit protoze byl zraneny. Radsi si nechci predstavovat co zazily protoze byli zbiti jak zito." << endl;
        else if (volbaPokec2 == 4) break;
        else cout << "Takovy clovek tu neni." << endl;
    }

    cout << "\nOdesel jsi z vesnice and blizis se k dalsimu rozcesti - Hrbitov and Bazina kud..." << endl;
    cout << "???: Kra kra, celou tvou cestu te sleduju a necekala jsem ze se dostanes tak daleko mladiku." << endl;
    cout << "Hrac: Halo halo, kdo to byl? Odkud?" << endl;
    cout << "???: Kra kra tady nahore." << endl;
    cout << "Hrac: Mluvici vrana... aha. Po mluvicim kameni ktery mi dava rady a hadanky me uz asi nic neprekvapi. Ty jsi taky pokus kralova alchymika? Teda pockat, jak jako ze me sledujes? Kdo teda jsi a proc me sledujes?" << endl;
    cout << "Stara vrana: Kra, mladiku uz od te doby co jsi odesel od krale te sleduju a cekala jsem, ze se nedostanes ani do prvni vesnice. Ale ty jsi az tady, dobra prace. A ne, nejsem pokusem alchymika, jsem jedno z monster Temneho krale... tak nejak mu rika ta starena... no to je jedno. Vymanila jsem se z jeho nadvlady a stala se ze me mluvici vrana." << endl;
    cout << "Stara vrana: A proc jsem se ti ted ozvala? Chci ti pomoct. Toto kralovstvi byvalo mirumilovne a hezke, ted potrebujeme hrdinu, a kdyz do tebe vlozil nadeje nas kral a moudry kamen, tak ti budu taky verit." << endl;
    cout << "Stara vrana: Nevsiml sis? Ze zacatku jsi sel pres lesy a pole, pak uz tam byla jeskyne nebo reka a ted bazina a nebo hrbitov. Cim dal jdes, tim vic je tady temne energie, ktera ovlivnuje prirodu, ale i lidi a zvirata. Davej si pozor, ale uz jsi blizko. Pak ode me pozdravuj korenarku, verim tomu ze ji potkas." << endl;
    cout << "Stara vrana: Jo a tady mas kouzelny Amulet zivota, pri souboji se budes moci vylecit. Nazdar! (Odleta pryc)" << endl;
    maAmuletZivota = true;
    cout << "Hrac: No vsechno jsem asi pochopil az na tu korenarku... tak snad ji potkam a zjistim co je zac." << endl;

    cout << "\n1 - Pres Hrbitov\n2 - Pres Bazinu\nTvoje volba: ";
    int volbaBazinaHrbitov; cin >> volbaBazinaHrbitov;

    string monstraRozcesti4 = (volbaBazinaHrbitov == 1) ? "Kostlivcu" : "Bahniaku";
    cout << "\nVstupujes na cestu plnou " << monstraRozcesti4 << ". Obklopi te hned 5 lehkych nepratel!" << endl;

    int hpLehke[5] = { 6, 6, 6, 6, 6 };
    while (hp > 0 && (hpLehke[0] > 0 || hpLehke[1] > 0 || hpLehke[2] > 0 || hpLehke[3] > 0 || hpLehke[4] > 0)) {
        cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
        for (int i = 0; i < 5; i++) {
            if (hpLehke[i] > 0) cout << "[" << i + 1 << "] HP [LEHKE] " << monstraRozcesti4 << ": " << hpLehke[i] << endl;
        }
        cout << "Na koho zautocis? (1-5): ";
        int cil; cin >> cil;
        if (cil < 1 || cil > 5 || hpLehke[cil - 1] <= 0) { cout << "Neplatny cil!" << endl; continue; }

        int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena, 0, maAmuletZivota, &hp, maxHp);
        if (dmg > 0) {
            hpLehke[cil - 1] -= dmg;
            if (hpLehke[cil - 1] <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << "Nepritel " << cil << " mrtev!" << endl; }
        }
        for (int i = 0; i < 5; i++) {
            if (hpLehke[i] > 0) {
                int u = 1 - (obrana / 12); if (u < 0) u = 0; hp -= u;
                cout << monstraRozcesti4 << " te sekl za " << u << " HP!" << endl;
            }
        }
    }
    if (hp <= 0) { cout << "\nZemrel jsi v boji! Hra konci." << endl; system("pause"); return 0; }
    PridejXP(25, xp, level, xpDoDalsihoLevelu, hp, maxHp, utok);
    hp = min(maxHp, hp + 10);
    cout << "*** Vycistil jsi rozcesti! Odpocinul sis a doplnilo se ti 10 HP. (Aktualni HP: " << hp << "/" << maxHp << ") ***" << endl;

    cout << "\nPokracujes do dalsi urovne temnoty..." << endl;
    cout << "1 - Prebrodit se pres Reku krve\n2 - Projit Pavoucim lesem\nTvoje volba: ";
    int volbaRekaKrve; cin >> volbaRekaKrve;

    if (volbaRekaKrve == 1) {
        int hpMiniBoss = 40, dmgMiniBoss = 5; string jmMiniBoss = "[MINI-BOSS] Obrovska Pirana";
        cout << "\nZ krvave reky vyskocila masivni Pirana a zablokovala ti cestu!" << endl;
        while (hp > 0 && hpMiniBoss > 0) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << "\n[1] HP " << jmMiniBoss << ": " << hpMiniBoss << endl;
            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena, 0, maAmuletZivota, &hp, maxHp);
            if (dmg > 0) {
                hpMiniBoss -= dmg;
                if (hpMiniBoss <= 0) { stamina = min(maxStamina, stamina + 1); drahokamy += 8; cout << jmMiniBoss << " mrtva!" << endl; }
            }
            if (hpMiniBoss > 0) {
                int u = dmgMiniBoss - (obrana / 12); if (u < 0) u = 0; hp -= u;
                cout << jmMiniBoss << " te kousla za " << u << " HP!" << endl;
            }
        }
    }
    else {
        int hpMiniBoss = 50, dmgMiniBoss = 4; string jmMiniBoss = "[MINI-BOSS] 4-Metrovy Pavouk co zere lidi";
        cout << "\nV lese te obklicil obrovsky pavouk a slintaji mu tesaky!" << endl;
        while (hp > 0 && hpMiniBoss > 0) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << "\n[1] HP " << jmMiniBoss << ": " << hpMiniBoss << endl;
            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena, 0, maAmuletZivota, &hp, maxHp);
            if (dmg > 0) {
                hpMiniBoss -= dmg;
                if (hpMiniBoss <= 0) { stamina = min(maxStamina, stamina + 1); drahokamy += 8; cout << jmMiniBoss << " mrtev!" << endl; }
            }
            if (hpMiniBoss > 0) {
                int u = dmgMiniBoss - (obrana / 12); if (u < 0) u = 0; hp -= u;
                cout << jmMiniBoss << " te sekl nohou za " << u << " HP!" << endl;
            }
        }
    }
    if (hp <= 0) { cout << "\nZemrel jsi v boji! Hra konci." << endl; system("pause"); return 0; }
    PridejXP(30, xp, level, xpDoDalsihoLevelu, hp, maxHp, utok);
    hp = min(maxHp, hp + 10);
    cout << "*** Vycistil jsi rozcesti! Odpocinul sis a doplnilo se ti 10 HP. (Aktualni HP: " << hp << "/" << maxHp << ") ***" << endl;

    cout << "\nPosledni kroky pred centrem temnoty:" << endl;
    cout << "1 - Les vrahu a blaznu\n2 - Puste horici pole\nTvoje volba: ";
    int volbaBlazni; cin >> volbaBlazni;

    if (volbaBlazni == 1) {
        int hpLehke1 = 12, hpLehke2 = 12, hpLehke3 = 12; string jmLehke = "[LEHKE] Blazen fetak";
        int hpMid = 25; string jmMid = "[STREDNI] Vrah z vezeni";
        int hpBoss = 35; string jmBoss = "[MINI-BOSS] Seriovy vrah";
        cout << "\nVkrocil jsi do Lesa vrahu..." << endl;
        while (hp > 0 && (hpLehke1 > 0 || hpLehke2 > 0 || hpLehke3 > 0 || hpMid > 0 || hpBoss > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpLehke1 > 0) cout << "[1] " << jmLehke << ": " << hpLehke1 << " HP\n";
            if (hpLehke2 > 0) cout << "[2] " << jmLehke << ": " << hpLehke2 << " HP\n";
            if (hpLehke3 > 0) cout << "[3] " << jmLehke << ": " << hpLehke3 << " HP\n";
            if (hpMid > 0) cout << "[4] " << jmMid << ": " << hpMid << " HP\n";
            if (hpBoss > 0) cout << "[5] " << jmBoss << ": " << hpBoss << " HP\n";
            cout << "Vyber cil (1-5): "; int cil; cin >> cil;
            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena, 0, maAmuletZivota, &hp, maxHp);
            if (dmg > 0) {
                if (cil == 1 && hpLehke1 > 0) { hpLehke1 -= dmg; if (hpLehke1 <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << "Mrtvy!\n"; } }
                else if (cil == 2 && hpLehke2 > 0) { hpLehke2 -= dmg; if (hpLehke2 <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << "Mrtvy!\n"; } }
                else if (cil == 3 && hpLehke3 > 0) { hpLehke3 -= dmg; if (hpLehke3 <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << "Mrtvy!\n"; } }
                else if (cil == 4 && hpMid > 0) { hpMid -= dmg; if (hpMid <= 0) { stamina = min(maxStamina, stamina + 2); drahokamy += 4; cout << "Mrtvy!\n"; } }
                else if (cil == 5 && hpBoss > 0) { hpBoss -= dmg; if (hpBoss <= 0) { stamina = min(maxStamina, stamina + 1); drahokamy += 8; cout << "Mrtvy!\n"; } }
            }
            if (hpLehke1 > 0) { int u = 2 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpLehke2 > 0) { int u = 2 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpLehke3 > 0) { int u = 2 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpMid > 0) { int u = 4 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpBoss > 0) { int u = 5 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
        }
    }
    else {
        int hpLehke1 = 15, hpLehke2 = 15, hpLehke3 = 15; string jmLehke = "[LEHKE] Ohnivy jezek";
        int hpMid = 30; string jmMid = "[STREDNI] Ohnivy sokol";
        int hpBoss = 40; string jmBoss = "[MINI-BOSS] Ohnivy golem";
        cout << "\nVkrocil jsi na Puste horici pole..." << endl;
        while (hp > 0 && (hpLehke1 > 0 || hpLehke2 > 0 || hpLehke3 > 0 || hpMid > 0 || hpBoss > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpLehke1 > 0) cout << "[1] " << jmLehke << ": " << hpLehke1 << " HP\n";
            if (hpLehke2 > 0) cout << "[2] " << jmLehke << ": " << hpLehke2 << " HP\n";
            if (hpLehke3 > 0) cout << "[3] " << jmLehke << ": " << hpLehke3 << " HP\n";
            if (hpMid > 0) cout << "[4] " << jmMid << ": " << hpMid << " HP\n";
            if (hpBoss > 0) cout << "[5] " << jmBoss << ": " << hpBoss << " HP\n";
            cout << "Vyber cil (1-5): "; int cil; cin >> cil;
            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena, 0, maAmuletZivota, &hp, maxHp);
            if (dmg > 0) {
                if (cil == 1 && hpLehke1 > 0) { hpLehke1 -= dmg; if (hpLehke1 <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << "Mrtvy!\n"; } }
                else if (cil == 2 && hpLehke2 > 0) { hpLehke2 -= dmg; if (hpLehke2 <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << "Mrtvy!\n"; } }
                else if (cil == 3 && hpLehke3 > 0) { hpLehke3 -= dmg; if (hpLehke3 <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << "Mrtvy!\n"; } }
                else if (cil == 4 && hpMid > 0) { hpMid -= dmg; if (hpMid <= 0) { stamina = min(maxStamina, stamina + 2); drahokamy += 4; cout << "Mrtvy!\n"; } }
                else if (cil == 5 && hpBoss > 0) { hpBoss -= dmg; if (hpBoss <= 0) { stamina = min(maxStamina, stamina + 1); drahokamy += 8; cout << "Mrtvy!\n"; } }
            }
            if (hpLehke1 > 0) { int u = 2 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpLehke2 > 0) { int u = 2 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpLehke3 > 0) { int u = 2 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpMid > 0) { int u = 4 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpBoss > 0) { int u = 5 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
        }
    }
    if (hp <= 0) { cout << "\nZemrel jsi v boji! Hra konci." << endl; system("pause"); return 0; }
    PridejXP(35, xp, level, xpDoDalsihoLevelu, hp, maxHp, utok);
    hp = min(maxHp, hp + 10);
    cout << "*** Vycistil jsi rozcesti! Odpocinul sis a doplnilo se ti 10 HP. (Aktualni HP: " << hp << "/" << maxHp << ") ***" << endl;


    cout << "\nUfff... co to je? Cedule: TEMNY LES. To uz tu jsem. Nekdo stoji pred lesem..." << endl;
    cout << "???: Ahoj mladiku, ja jsem korenarka." << endl;
    cout << "Hrac: Aha, vrana mi rekla ze vas mam pozdravovat." << endl;
    cout << "Korenarka: Hahaha, ta stara vrana. No jo a dala ti Amulet zivota." << endl;
    cout << "Hrac: Ano, ale co vy? Neni to nebezpecne tu takto stat se stankem pred Temnym lesem?" << endl;
    cout << "Korenarka: Pro obycejneho smrtelnika ano, ale ne pro me. Ja mam amulet bozskeho srdce a ten me chrani pred lehkyma monstrama a pred zlou energii, aby me neovlivnovala. A taky se tu nenudim, mam tu klid a obcas si sem zaleti ta stara vrana. Ale ja tu pro tebe taky neco mam... Nebude to zadarmo. Joo a tady mas amulet, muzes jeho silou ocistit posedla stvoreni." << endl;
    maAmuletCistoty = true;

    bool koupilHeal = false; bool koupilDef = false; bool koupilAtk = false; bool koupilStaty = false;
    while (true) {
        cout << "\nMas " << drahokamy << " drahokamu." << endl;
        cout << "1. Vylecit se a doplnit staminu (10 drahokamu)" << (koupilHeal ? " [VYPRODANO]" : "") << endl;
        cout << "2. Vylepsit obranu +5 (20 drahokamu)" << (koupilDef ? " [VYPRODANO]" : "") << endl;
        cout << "3. Vylepsit utok +5 (20 drahokamu)" << (koupilAtk ? " [VYPRODANO]" : "") << endl;
        cout << "4. Zvysit Max HP a Max Staminu o 5 (30 drahokamu)" << (koupilStaty ? " [VYPRODANO]" : "") << endl;
        cout << "5. Ukoncit nakup a vstoupit do Temneho lesa\nVolba: ";
        int shopVolba; cin >> shopVolba;
        if (shopVolba == 1 && !koupilHeal && drahokamy >= 10) { hp = maxHp; stamina = maxStamina; drahokamy -= 10; koupilHeal = true; cout << "Vylecen!\n"; }
        else if (shopVolba == 2 && !koupilDef && drahokamy >= 20) { obrana += 5; drahokamy -= 20; koupilDef = true; cout << "Obrana zvysena!\n"; }
        else if (shopVolba == 3 && !koupilAtk && drahokamy >= 20) { utok += 5; drahokamy -= 20; koupilAtk = true; cout << "Utok zvysen!\n"; }
        else if (shopVolba == 4 && !koupilStaty && drahokamy >= 30) { maxHp += 5; maxStamina += 5; hp += 5; stamina += 5; drahokamy -= 30; koupilStaty = true; cout << "Staty zvyseny!\n"; }
        else if (shopVolba == 5) { cout << "Preju hodne stesti, budes ho potrebovat...\n"; break; }
        else cout << "Neplatna volba nebo malo penez!\n";
    }


    cout << "\nTemny les... Je tu divna energie..." << endl;
    cout << "???: Ale, ale, kdo to prisel. Poslal te muj prohnilej bratr?" << endl;
    cout << "Hrac: Takze je to pravda. Jsi Ramus, bratr krale, ktery se uz davno ztratil na cestach." << endl;
    cout << "Ramus (Temny kral): Ted uz nejsem Ramus, ale Kral Temneho lesa! A moje kralovstvi smrti, strachu a utrpeni se postupne rozsiruje, nici a terorizuje kralovstvi meho bratra. A jednoho dne obsadim cele jeho kralovstvi, BAHAHAHA!" << endl;
    cout << "Hrac: Co? To se nikdy nestane, protoze te popravim!" << endl;
    cout << "Ramus (Temny kral): Hahaha, ty me? Tak to se nejdriv musis dostat pres ty mysi co sem jela chytat ta druzina... a vlastne se postav i samotne druzine, kterou jsi sem sel hledat! Hahaha!" << endl;

    int hpMysi[5] = { 5, 5, 5, 5, 5 };
    int hpRytiri[5] = { 15, 15, 15, 15, 15 };
    cout << "\nPred tebou stoji 5 zmutovanych mysi a 5 posedlych Kralovych rytiru!" << endl;

    while (hp > 0 && (hpMysi[0] > 0 || hpMysi[1] > 0 || hpMysi[2] > 0 || hpMysi[3] > 0 || hpMysi[4] > 0 || hpRytiri[0] > 0 || hpRytiri[1] > 0 || hpRytiri[2] > 0 || hpRytiri[3] > 0 || hpRytiri[4] > 0)) {
        cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
        for (int i = 0; i < 5; i++) if (hpMysi[i] > 0) cout << "[M" << i + 1 << "] Zmutovana mys: " << hpMysi[i] << " HP\n";
        for (int i = 0; i < 5; i++) if (hpRytiri[i] > 0) cout << "[R" << i + 1 << "] Posedly Rytir: " << hpRytiri[i] << " HP\n";

        cout << "Utocis na Mys (1) nebo na Rytire (2)? "; int druh; cin >> druh;
        cout << "Ktereho? (1-5): "; int index; cin >> index; index--;

        int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena, 0, maAmuletZivota, &hp, maxHp);
        if (dmg > 0) {
            if (druh == 1 && hpMysi[index] > 0) {
                hpMysi[index] -= dmg;
                if (hpMysi[index] <= 0) { stamina = min(maxStamina, stamina + 5); drahokamy += 2; cout << "Mys mrtva!\n"; }
            }
            else if (druh == 2 && hpRytiri[index] > 0) {
                hpRytiri[index] -= dmg;
                if (hpRytiri[index] <= 0) {
                    stamina = min(maxStamina, stamina + 5); drahokamy += 5;
                    if (maAmuletCistoty) cout << "Premohl jsi rytire a ocistil ho z temne magie!\n";
                    else cout << "Zabil jsi rytire!\n";
                }
            }
        }
        for (int i = 0; i < 5; i++) {
            if (hpMysi[i] > 0 && (rand() % 2 == 0)) { int u = 1 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
            if (hpRytiri[i] > 0) { int u = 1 - (obrana / 12); if (u < 0) u = 0; hp -= u; }
        }
    }
    if (hp <= 0) { cout << "\nZemrel jsi v boji! Hra konci." << endl; system("pause"); return 0; }
    hp = min(maxHp, hp + 10);
    cout << "*** Vycistil jsi cestu! Odpocinul sis a doplnilo se ti 10 HP. (Aktualni HP: " << hp << "/" << maxHp << ") ***" << endl;


    cout << "\nRamus (Temny kral): AAAAAA! Tak ted me uz neporazis!" << endl;
    cout << "Hrac: To se uvidi!" << endl;
    cout << "\n==========================================================" << endl;
    cout << "    FINALNI BOSS: TEMNY KRAL RAMUS (Geomancerova magie)    " << endl;
    cout << "==========================================================" << endl;

    int hpBossFinal = 100;
    int baseBossDmg = 4;

    while (hp > 0 && hpBossFinal > 0) {
        cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << "\nHP TEMNY KRAL: " << hpBossFinal << endl;
        int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena, 0, maAmuletZivota, &hp, maxHp);
        if (dmg > 0) {
            hpBossFinal -= dmg;
            if (hpBossFinal <= 0) { cout << "\nPORAZIL JSI TEMNEHO KRALE!" << endl; break; }
        }

        cout << "\n[!] Temny kral pouziva magii GEOMANCERA!" << endl;
        cout << "Geomancer te nuti nakreslit tvar na ochranu. Ktery vyberes?\n1. Ctverec\n2. Obdelnik\n3. Kruh\nTvoje volba: ";
        int tvar; cin >> tvar;
        int bossDmg = 0;

        cout << "Standardni utok bosse (zakladni poskozeni) je: " << baseBossDmg << endl;

        if (tvar == 1) {
            cout << "******\n"
                << "*    *\n"
                << "*    *\n"
                << "******\n";
            bossDmg = baseBossDmg * 4;
            cout << "Ctverec - Geomancer udeli sve zakladni poskozeni, ktere vynasobi 4" << endl;
        }
        else if (tvar == 2) {
            cout << "**********\n"
                << "*        *\n"
                << "*        *\n"
                << "**********\n";
            bossDmg = baseBossDmg * (2 + (level * 2));
            cout << "Obdelnik - Geomancer udeli sve zakladni poskozeni, ktere vynasobi 2 + (level hrace * 2)" << endl;
        }
        else if (tvar == 3) {
            cout << "   ****   \n"
                << " *      * \n"
                << " *      * \n"
                << "   ****   \n";
            int nahoda = rand() % 3;
            int mult = (nahoda == 0) ? 1 : ((nahoda == 1) ? 3 : 4);
            bossDmg = baseBossDmg * mult * 2;
            cout << "Kruh - Geomancer udeli ((sve zakladni poskozeni * (nahodna hodnota mezi 1-3-4) * 2)" << endl;
        }
        else {
            bossDmg = baseBossDmg * 5;
            cout << "Spatna volba! Boss dostava obrovsky utok!" << endl;
        }

        int konecnyBossDmg = bossDmg - (obrana / 12);
        if (konecnyBossDmg < 1) konecnyBossDmg = 1;

        hp -= konecnyBossDmg;
        cout << "Temny kral ti udelil " << konecnyBossDmg << " HP poskozeni magii Geomancera!" << endl;
    }

    if (hp <= 0) { cout << "\nZemrel jsi v boji s bosssem! Temny kral ovladl svet. Hra konci." << endl; system("pause"); return 0; }


    if (maAmuletCistoty) {
        cout << "\nTemna magie z Krale vyprchala dily Amuletu Cistoty!" << endl;
        cout << "Chces si vyslechnout jeho pribeh (1) nebo ho hned odsoudit (2)? ";
        int poslouchat; cin >> poslouchat;
        if (poslouchat == 1) {
            cout << "\nRamus: Byl jsem mladsi ze dvou kralovskych synu. Bylo jasny, ze muj bratr usedne jako prvni na trun a ja se na nej podivam az po jeho smrti. Teda pokud nebude mit potomky... Kdyby on mel syna, coz ma, tak na ten trun uz nikdy neusednu." << endl;
            cout << "Proto jsem cestoval daleko a daleko, tam kde me nikdo neznal. A kdyz me nikdo neznal a nic jsem neumel, tak se ke me lidi chovali hrozne. Kupil se ve me vztek. Alchymista na me zkousel uz tolik pokusu... Moje telo zporadalo tolik lektvaru a muj hnev a smutek se sloucili a zmenily me na takovou zrudu, co chtela obsadit kralovstvi sveho vlastniho bratra." << endl;
            cout << "Ale nikdy jsem ho nechtel zabit. Jen jsem ho chtel zajmout a nechat ho, at se diva na moji krutovladu nad timto ubohym kralovstvim. Ted, kdyz jsi me porazil a ocistil, tak se citim mnohem lepe a citim jak zla energie ustupuje z celeho kralovstvi. Ale za sve hrichy musim nest zodpovednost... Cin, jak uznas za vhodne." << endl;
        }
    }

    cout << "\nCo udelas s porazenym a ocistenym Ramusem?\n1. Zabit ho\n2. Zajmout ho do vezeni\nTvoje volba: ";
    int final; cin >> final;

    if (final == 1) {
        cout << "\nRozhodl ses ho ZABIT. Kdyz se to Kral dozvedel, zblaznil se z toho, ze proti nemu sel jeho vlastni bratr. Odsoupil a na trun usedl jeho syn." << endl;
    }
    else {
        cout << "\nRozhodl ses ho ZAJMOUT. Bude pod hradem zavren na veky veku. Kral mu odpustil a chodi ho tajne navstevovat, ale vi, ze jeho lid bratrovi neodpusti, tak ho uz nesmi z vezeni nikdy pustit." << endl;
    }

    cout << "\nZachranil jsi kralovstvi!" << endl;
    cout << "Dostal jsi obrovskou odmenu a budes do konce zivota bohaty!" << endl;
    if (maAmuletCistoty) cout << "Kralova ocistena druzina ti bude do konce zivota vdecne sloužit za zachranu zivotu!" << endl;

    cout << "\n*** GRATULUJI! DOHRAL JSI HRU! ***" << endl;
    system("pause");
    return 0;
}
