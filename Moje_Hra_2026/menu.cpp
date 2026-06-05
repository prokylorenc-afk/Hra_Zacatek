#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;




int ZvolUtok(int& stamina, int maxStamina, int utok, string specialita, string jmeno, bool mensiStamina = false) {
    string nazev1 = (jmeno == "Prokop") ? "Bodnuti propiskou" : "Rychly utok";
    string nazev2 = (jmeno == "Prokop") ? "Rana tezkym sesitem" : "Silny utok";


    int cenaUtoku2 = mensiStamina ? 2 : 3;
    int cenaUtoku3 = mensiStamina ? 3 : 5;

    cout << "1. " << nazev1 << " (1 staminy, DMG: " << utok / 2 + 1 << ")\n";
    cout << "2. " << nazev2 << " (" << cenaUtoku2 << " staminy, DMG: " << utok << ")\n";
    cout << "3. " << specialita << " (" << cenaUtoku3 << " staminy, DMG: " << utok + 4 << ")\n";

    if (stamina == 0) {
        cout << "4. Doplnit staminu (Nahodne 1-5)\n";
    }
    cout << "Volba: ";

    int volba;
    cin >> volba;

    if (volba == 1 && stamina >= 1) {
        stamina -= 1;
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
        if (stamina > maxStamina) {
            stamina = maxStamina;
        }
        cout << "Zhluboka ses nadechl, chvili jsi odpocival a doplnil jsi " << obnova << " staminy!" << endl;
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
    int hp = 0, utok = 0, obrana = 0, rychlost = 0, stamina = 0;
    int maxStamina = 0, maxHp = 0;
    string specialita = "Zadna";
    int drahokamy = 0, xp = 0, level = 1, xpDoDalsihoLevelu = 20;

    cout << "=== VITEJ VE HRE ===" << endl;

    while (true) {
        cout << "\n--- HLAVNI MENU ---" << endl;
        cout << "1. Zvolit postavu\n2. Hrat\n3. Ukoncit\nTvoje volba: ";
        cin >> volbaHlavni;

        if (volbaHlavni == 1) {
            cout << "\nVyber si hrdinu:" << endl;
            cout << "1. Rytir (Dobry utok i obrana, ale pomaly, ma mec a stit)\n2. Goblin (Maly a extremne rychly, ale ma jen kudlicku)\n3. Carodej (Normalni staty, muze si vylepsit hul ve stanu)\n4. Jezibaba (Pomalejsi, ale ma ostrazitost, staminu a jed)\n5. Lucistnik (Rychly, utoci na dalku)\nVyber: ";
            int volbaPostavy;
            cin >> volbaPostavy;

            if (volbaPostavy == 1) { jmeno = "Rytir"; hp = 20; utok = 8; obrana = 10; rychlost = 2; stamina = 10; specialita = "Mec a stit"; }
            else if (volbaPostavy == 67) { jmeno = "Prokop"; hp = 25; utok = 6; obrana = 8; rychlost = 5; stamina = 15; specialita = "Jednicka z programovani"; }
            else if (volbaPostavy == 2) { jmeno = "Goblin"; hp = 10; utok = 3; obrana = 2; rychlost = 15; stamina = 8; specialita = "Rezava kudlicka"; }
            else if (volbaPostavy == 3) { jmeno = "Carodej"; hp = 15; utok = 5; obrana = 5; rychlost = 5; stamina = 15; specialita = "Magicka hul"; }
            else if (volbaPostavy == 4) { jmeno = "Jezibaba"; hp = 18; utok = 4; obrana = 6; rychlost = 3; stamina = 20; specialita = "Jed (Poison)"; }
            else if (volbaPostavy == 5) { jmeno = "Lucistnik"; hp = 12; utok = 7; obrana = 3; rychlost = 8; stamina = 12; specialita = "Luk a sipy"; }
            else { cout << "Spatna volba, davam ti Rytire." << endl; jmeno = "Rytir"; hp = 20; utok = 8; obrana = 10; rychlost = 2; stamina = 10; specialita = "Mec a stit"; }

            maxStamina = stamina; maxHp = hp;
            hraceVybral = true;

            cout << "\n--> Tvoje postava je nyni: " << jmeno << " <--" << endl;
            cout << "Staty: HP: " << hp << " | Utok: " << utok << " | Obrana: " << obrana << " | Rychlost: " << rychlost << " | Stamina: " << stamina << "\nSpecialita: " << specialita << endl;
        }
        else if (volbaHlavni == 2) {
            if (!hraceVybral) cout << "\n!!! Pozor: Nejdriv si musis vybrat postavu (volba 1) !!!" << endl;
            else {
                cout << "\n==================================================================" << endl;
                cout << "Kral si te nechal urgentne povolat!\nZada te o pomoc. Jeho nejlepsi vojsko slo na lov mysi do Temneho lesa...\n...jenze se NEOZVALI a NEVRATILI. Nezbyly po nich ZADNE stopy." << endl;
                cout << "\nKral si zada prave tebe kvuli tvym zkusenostem a hrdinske povesti!\nKdyz najdes jeho druzinu, da ti pokladnici PLNOU ZLATA\na tvoje slava bude tak uchvatna, ze te budou znat VSOUDE!" << endl;
                cout << "==================================================================" << endl;
                cout << "\nPomozes krali v teto tezke chvili?\n1. Ano, prijmam tvuj ukol, krali!\n2. Ne, tohle me nezajima. Odchazim.\nTvoje volba: ";
                int volbaPomoci;
                cin >> volbaPomoci;

                if (volbaPomoci == 2) { cout << "\nGAME OVER: Kral te nechal POPRAVIT za nedostatek ucty k nemu!" << endl; return 0; }
                else if (volbaPomoci == 3) { cout << "\nWIN: Zabil jsi krale a ostatni strazni se ti poddali. Ted jsi kralem ty!" << endl; return 0; }
                else if (volbaPomoci == 1) { cout << "\nDo sluzeb krale nastupuje hrdina... " << jmeno << "!" << endl; break; }
            }
        }
        else if (volbaHlavni == 3) { cout << "Koncim program..." << endl; return 0; }
        else cout << "Neznama volba v menu!" << endl;
    }

    cout << "\nOcitl ses na zacatku tve vypravy a pred sebou vidis dve cesty. Kterou si vyberes?" << endl;
    cout << "1 - Stary most, ktery vede pres reku\n2 - Cesta rovnou do husteho lesa\nTvoje volba: ";
    int cesta; cin >> cesta;

    if (cesta == 1) cout << "\nSpatna volba! Jakmile jsi stoupl na stary most, prkna praskla a ty jsi spadl do reky!\nTezce jsi doplaval na breh. Ztratil jsi cas, ale musis pokracovat jedinou moznou cestou - do husteho lesa." << endl;
    else cout << "\nRozhodl ses pro jistotu a jdes rovnou po ceste do husteho lesa." << endl;

    cout << "\n[INFO O HRE]\nVe hre jsou urovne priser:\n- Lehke: Lesni sliz, krtci\n- Stredni: Skret, Lesni troll\n- Mini boss: Stin lesu, Farmar smrti\n- Kral temneho lesa\nZ KAZDE prisery padaji DRAHOKAMY. Ty pak muzes ve vesnici utratit!\nPo kazdem boji se ti take vrati cast staminy podle toho, jak tezka prisera to byla.\n==================================================================" << endl;


    cout << "\n!!! Z krovi na tebe vyskocila ta nejlehci prisera: LESNI SLIZ !!!" << endl;
    int hpPrisery = 10;
    while (hp > 0 && hpPrisery > 0) {
        cout << "\nTVOJE HP: " << hp << " | TVOJE STAMINA: " << stamina << "/" << maxStamina << "\nHP SLIZU: " << hpPrisery << endl;
        int udelenePoskozeni = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno);
        if (udelenePoskozeni > 0) {
            hpPrisery -= udelenePoskozeni;
            if (hpPrisery <= 0) {
                int obnova = rand() % 4; // Vygeneruje 0 az 3
                stamina = (stamina + obnova > maxStamina) ? maxStamina : stamina + obnova;
                cout << "Zabil jsi Lesni sliz a obnovilo se ti " << obnova << " staminy!" << endl;
            }
        }
        if (hpPrisery > 0) { hp -= 2; cout << "Lesni sliz po tobe plivnul kyselinu a ubral ti 2 HP!" << endl; }
    }
    if (hp <= 0) { cout << "\nZemrel jsi! Rozleptal te Lesni sliz. Hra konci." << endl; system("pause"); return 0; }

    cout << "\n=========================================\nPorazil jsi Lesni sliz!\nZ jeho zbytku jsi ziskal 3 DRAHOKAMY!" << endl;
    drahokamy += 3;
    PridejXP(10, xp, level, xpDoDalsihoLevelu, hp, maxHp, utok);
    cout << "Byla to lehka prisera, vraci se ti 5 bodu staminy." << endl;
    stamina = (stamina + 5 > maxStamina) ? maxStamina : stamina + 5;
    cout << "=========================================" << endl;


    cout << "\nPokracujes dal po ceste a po chvili narazis na malou vesnici." << endl;
    cout << "\n--- MISTNI TRH ---\nMas " << drahokamy << " drahokamu.\nMuzes si vybrat pouze JEDNU z techto sluzeb, pak te mistni vyzenou:\n1. Vylecit se (Plne obnovi HP a Staminu) - Cena: 2 drahokamy\n2. Vylepsit utok (+2 k utoku) - Cena: 3 drahokamy\n3. Vylepsit ochranu (+2 k defense/obrane) - Cena: 3 drahokamy\n4. Odejit (Nic nepotrebujes)\nTvoje volba akce: ";
    int volbaObchod; cin >> volbaObchod;
    if (volbaObchod == 1) {
        if (drahokamy < 2) cout << "\n[!] Tohle udelat nemuzes! Nemas dostatek drahokamu." << endl;
        else if (hp == maxHp && stamina == maxStamina) cout << "\n[!] Tohle udelat nemuzes! Jsi plne vyhealovanej a odpocinutej na max." << endl;
        else { hp = maxHp; stamina = maxStamina; drahokamy -= 2; cout << "\n-> Byl jsi uspesne vylecen! Ubyly ti 2 drahokamy." << endl; }
    }
    else if (volbaObchod == 2) {
        if (drahokamy < 3) cout << "\n[!] Tohle udelat nemuzes! Nemas dostatek drahokamu." << endl;
        else { utok += 2; drahokamy -= 3; cout << "\n-> Tvuj utok byl permanentne zvysen! Aktualni utok: " << utok << endl; }
    }
    else if (volbaObchod == 3) {
        if (drahokamy < 3) cout << "\n[!] Tohle udelat nemuzes! Nemas dostatek drahokamu." << endl;
        else { obrana += 2; drahokamy -= 3; cout << "\n-> Tvoje obrana byla permanentne zvysena! Aktualni obrana: " << obrana << endl; }
    }

    bool vespolekKecani = true;
    while (vespolekKecani) {
        cout << "\n--- ROZHOVORY S VESNICANY ---\nKoho chces nyni vyslechnout?\n1. Farmar\n2. Maly chlapec\n3. Svadlena\n4. Nikoho (Odejst z vesnice)\nVolba: ";
        int volbaPokec; cin >> volbaPokec;
        if (volbaPokec == 1) cout << "\n Jooo, vy se shanite po tech rytirich? Ty me teda vytocili! Oni si sli jen tak vklidu slavit prii nejaky jejich rytual na zacatku kazde mise pro stesti. No, rytual nerytual, kone si neuvazali a ty jejich kone mi spasli pres noc polovinu urody. No jasne, ze se omlouvali, ale pri maji na spech a drahokamu uz jim taky moc nezbylo, ze pri mi to zaplati na ceste zpet. Rikali neco otom, ze jedou lovit mysi do temneho lesa, tak snad se vrati, jinak nebudu mit co zrat, prodavat, ani nebudu mit zadny drahokami. Pokud je potkas tak jim pripomen aby se tu zastavili. " << endl;
        else if (volbaPokec == 2) cout << "\nJo, ti ritiri! Pamatuju si tu druzinu. Rikali mi, ze bych jednou mohl byt veliky valecnik, tak mi pujcili mec a helmu, abych si to zkusil, jaky to je. Byli na me hodni, dokonce i kolac mi koupili a pri tu vecer i slavily, ale to uz jsem spal. " << endl;
        else if (volbaPokec == 3) cout << "\nJa jsem svadlena, cely den jen siju a siju a z baraku sotva paty na trh vytahnu, ale to vite, ze si je pamatuju. Slavili tady pri nejaky rytual, tak snad se jim vydariil a nic se jim nestalo. Ale presto, ze se tady striskaly, tak nic neznicily a za vsechny sluzby zaplatily. Jediny co, tak jsem slysela, ze farmarovy ty jejich kone spasli urodu, ale to nevim, zeptejte se jeho. " << endl;
        else if (volbaPokec == 4) break;
        else { cout << "Takovy clovek tu nestoji." << endl; continue; }
        cout << "\nCo chces udelat nyni?\n1. Pokracovat v ceste\n2. Vyslechnout vesnicany\nTvoje volba: ";
        int poRozhovoruVolba; cin >> poRozhovoruVolba;
        if (poRozhovoruVolba == 1) vespolekKecani = false;
    }


    cout << "\nOpustil jsi vesnici a stojis pred dalsim rozhodnutim. Kam se vydas ted?" << endl;
    cout << "1 - Pujdes pres listnaty les\n2 - Vydas se pres otevrenou louku (pole)\n3 - Vstoupis do tajemneho lesa s fialovymi stromy\nTvoje volba: ";
    int finalniCesta; cin >> finalniCesta;

    if (finalniCesta == 1) {
        cout << "\n--- LISTNATY LES ---\nProdiras se listnatym lesem, kdyz v tom na tebe zautoci DVE monstra najednou!" << endl;
        int hpSliz = 10, hpTrol = 20;
        while (hp > 0 && (hpSliz > 0 || hpTrol > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpSliz > 0) cout << "[1] HP SLIZU: " << hpSliz << endl;
            if (hpTrol > 0) cout << "[2] HP TROLA: " << hpTrol << endl;
            int cil = 1;
            if (hpSliz > 0 && hpTrol > 0) { cout << "Kdo bude tvuj cil? (1 = Sliz, 2 = Trol): "; cin >> cil; }
            else cil = (hpSliz > 0) ? 1 : 2;

            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno);
            if (dmg > 0) {
                if (cil == 1) {
                    hpSliz -= dmg; cout << "Zasahl jsi Sliz!" << endl;
                    if (hpSliz <= 0) { int obnova = rand() % 4; stamina = (stamina + obnova > maxStamina) ? maxStamina : stamina + obnova; cout << "Sliz padl! Obnovilo se ti " << obnova << " staminy." << endl; }
                }
                else {
                    hpTrol -= dmg; cout << "Zasahl jsi Trola!" << endl;
                    if (hpTrol <= 0) { int obnova = rand() % 4; stamina = (stamina + obnova > maxStamina) ? maxStamina : stamina + obnova; cout << "Trol padl! Obnovilo se ti " << obnova << " staminy." << endl; }
                }
            }
            if (hpSliz > 0) { hp -= 2; cout << "Sliz po tobe plivl a ubral 2 HP!" << endl; }
            if (hpTrol > 0) { hp -= 4; cout << "Trol te majznul klackem a ubral 4 HP!" << endl; }
        }
    }
    else if (finalniCesta == 2) {
        cout << "\n--- OTEVRENA LOUKA (POLE) ---\nJdes pres pole, kdyz se zeme zatrese. Z nory vyrazi Krtek a z krovi vybehne Skret!" << endl;
        int hpKrtek = 8, hpSkret = 15;
        while (hp > 0 && (hpKrtek > 0 || hpSkret > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpKrtek > 0) cout << "[1] HP KRTKA: " << hpKrtek << endl;
            if (hpSkret > 0) cout << "[2] HP SKRETA: " << hpSkret << endl;
            int cil = 1;
            if (hpKrtek > 0 && hpSkret > 0) { cout << "Kdo bude tvuj cil? (1 = Krtek, 2 = Skret): "; cin >> cil; }
            else cil = (hpKrtek > 0) ? 1 : 2;

            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno);
            if (dmg > 0) {
                if (cil == 1) {
                    hpKrtek -= dmg; cout << "Zasahl jsi Krtka!" << endl;
                    if (hpKrtek <= 0) { int obnova = rand() % 4; stamina = (stamina + obnova > maxStamina) ? maxStamina : stamina + obnova; cout << "Krtek byl porazen! Obnovilo se ti " << obnova << " staminy." << endl; }
                }
                else {
                    hpSkret -= dmg; cout << "Zasahl jsi Skreta!" << endl;
                    if (hpSkret <= 0) { int obnova = rand() % 4; stamina = (stamina + obnova > maxStamina) ? maxStamina : stamina + obnova; cout << "Skret byl porazen! Obnovilo se ti " << obnova << " staminy." << endl; }
                }
            }
            if (hpKrtek > 0) { hp -= 2; cout << "Krtek te podkopl a ubral 2 HP!" << endl; }
            if (hpSkret > 0) { hp -= 3; cout << "Skret te bodl kudlou a ubral 3 HP!" << endl; }
        }
    }
    else if (finalniCesta == 3) {
        cout << "\n--- FIALOVY LES ---\nVstoupil jsi do tajemneho lesa. Je tu tma. Najednou se pred tebou zhmotni MINI-BOSS: Stin lesu!\nStin lesu je rychlejsi nez ty a utoci jako PRVNI!" << endl;
        int hpBoss = 35;
        hp -= 5;
        cout << "Stin te zahalil temnotou a ubral ti 5 HP jeste nez jsi stihl zareagovat!" << endl;
        while (hp > 0 && hpBoss > 0) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << "\nHP MINI-BOSSE: " << hpBoss << endl;
            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno);
            if (dmg > 0) {
                hpBoss -= dmg;
                if (hpBoss <= 0) { int obnova = rand() % 4; stamina = (stamina + obnova > maxStamina) ? maxStamina : stamina + obnova; cout << "Mini-boss padl! Obnovilo se ti " << obnova << " staminy." << endl; }
            }
            if (hpBoss > 0) { hp -= 5; cout << "Stin lesu te zasahl magii a ubral ti 5 HP!" << endl; }
        }
    }

    if (hp <= 0) { cout << "\nZemrel jsi v boji! Hra konci." << endl; system("pause"); return 0; }

    PridejXP(15, xp, level, xpDoDalsihoLevelu, hp, maxHp, utok);
    drahokamy += 5;
    cout << "Prezil jsi tezky boj! Ziskavas navic 5 drahokamu.\n\n==================================================================\nAt sis vybral jakoukoliv cestu na rozcesti, po boji si vsimas, ze se \nvsechny cesty stejne staci do jednoho bodu. Dostavas se na stejne misto.\n==================================================================" << endl;

    cout << "\nHrac: Achh, jsem unaveny. Sednu si a odpocinu na tomto kameni." << endl;
    cout << "???: Au au au! Slez ze me ty grazle, pripadam ti jako lavicka? Vis ty vubec, kdo ja jsem?" << endl;
    cout << "Hrac: Co... co... co to bylo? Kdo mluvi?" << endl;
    cout << "???: Tady dole! Ja jsem moudry kamen." << endl;
    cout << "Hrac: K... k... kamen, co mluvi?" << endl;
    cout << "Kamen: Ano, jsem jeden z prvnich experimentu kralova alchymisty a mam zde cekat a pomahat lidem. Ale potom, co jsi si na me sednul, ti pomuzu, jen kdyz uhodnes tri hadanky!" << endl;
    cout << "(Odpovedi zapisuj bez diakritiky a malymi pismeny)" << endl;

    int pocetUhodnutych = 0;
    bool mensiStaminaCena = false;
    bool radaDoVesnice = false;
    string odpovedHrace;


    cout << "\n1. Strazce vedeni" << endl;
    cout << "\"Nemam usta, ale mluvim ke vsem, kdo me otevrou. Nemam nohy, ale zavedu te do dalekych risi. Moje kuze je z pergamenu ci kuze zvirat a krev mi nahrazuje cerny inkoust. Kdo jsem?\"" << endl;
    cout << "Tvoje odpoved: ";
    cin >> odpovedHrace;

    if (odpovedHrace == "kniha") {
        pocetUhodnutych++;

        cout << "\nSpravne! Tady je druha:" << endl;
        cout << "2. Poutnik noci" << endl;
        cout << "\"Narodim se ve stinu, zemru v prvnim paprsku slunce. Pronasleduji te na kazdem kroku, ale nikdy se me nedotknes. Jsem vernym sluhou svetla, a presto bez tmy bych nebyl nicim. Kdo jsem?\"" << endl;
        cout << "Tvoje odpoved: ";
        cin >> odpovedHrace;

        if (odpovedHrace == "stin") {
            pocetUhodnutych++;

            cout << "\nSpravne! A posledni:" << endl;
            cout << "3. Dech zeme" << endl;
            cout << "\"Jsem neviditelny, ale slysis me zpivat v korunach stromu. Nemam ruce, ale dokazu lamat skaly a plnit plachty lodi. Jsem prvnim nadechem novorozenete i poslednim vzdychnutim skomirajiciho ohne. Co jsem?\"" << endl;
            cout << "Tvoje odpoved: ";
            cin >> odpovedHrace;

            if (odpovedHrace == "vitr") {
                pocetUhodnutych++;
            }
        }
    }


    cout << "\n--- VYSLEDEK HADANEK ---" << endl;
    if (pocetUhodnutych == 0) {
        cout << "Kamen: Tak to je dost bidna zachrana, kral musi byt asi dost zoufaly..." << endl;
    }
    else if (pocetUhodnutych == 1) {
        cout << "Kamen: No nic moc, ale aspon nejsi takova luza." << endl;
        cout << "[Ziskavas trvale snizeni potrebne staminy na utoky 2 a 3!]" << endl;
        mensiStaminaCena = true;
    }
    else if (pocetUhodnutych == 2) {
        cout << "Kamen: Ty mas potencial." << endl;
        cout << "[Ziskavas snizeni staminy na utoky a 20 drahokamu!]" << endl;
        mensiStaminaCena = true;
        drahokamy += 20;
    }
    else if (pocetUhodnutych == 3) {
        cout << "Kamen: Ty jsi vyvoleny! Jdi pres vesnici a tam v truhle dostanes muj treti dar, a to vylepseni brneni." << endl;
        cout << "[Ziskavas snizeni staminy na utoky, 20 drahokamu a tajnou radu!]" << endl;
        mensiStaminaCena = true;
        drahokamy += 20;
        radaDoVesnice = true;
    }
    cout << "------------------------------------------------------------------" << endl;


    cout << "\nPred tebou je nyni dalsi rozhodnuti:" << endl;
    cout << "1 - Jit pres Obycejny les" << endl;
    cout << "2 - Jit pres Opustenou vesnici" << endl;
    cout << "Tvoje volba: ";

    int volbaDalsi;
    cin >> volbaDalsi;

    if (volbaDalsi == 1) {
        cout << "\n--- OBYCEJNY LES ---" << endl;
        cout << "Slysis praskani vetvicek... ceka te boj s priserami z lesa!" << endl;

        int hpLehke = 10, dmgLehke = 2; string jmenoLehke = "Lesni sliz";
        int hpStredni = 15, dmgStredni = 3; string jmenoStredni = "Lesni skret";
        int hpMiniBoss = 30, dmgMiniBoss = 6; string jmenoMiniBoss = "Temny lesni duch";

        cout << "Z krovi na tebe vyskocil " << jmenoLehke << ", " << jmenoStredni << " a MINI-BOSS " << jmenoMiniBoss << "!" << endl;

        while (hp > 0 && (hpLehke > 0 || hpStredni > 0 || hpMiniBoss > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpLehke > 0) cout << "[1] HP " << jmenoLehke << ": " << hpLehke << endl;
            if (hpStredni > 0) cout << "[2] HP " << jmenoStredni << ": " << hpStredni << endl;
            if (hpMiniBoss > 0) cout << "[3] HP " << jmenoMiniBoss << ": " << hpMiniBoss << endl;

            int cil = 0;
            cout << "Kdo bude tvuj cil? (1, 2 nebo 3): ";
            cin >> cil;

            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena);
            if (dmg > 0) {
                if (cil == 1 && hpLehke > 0) {
                    hpLehke -= dmg;
                    if (hpLehke <= 0) { int obnova = rand() % 4; stamina = (stamina + obnova > maxStamina) ? maxStamina : stamina + obnova; cout << jmenoLehke << " padl! Obnovilo se ti " << obnova << " staminy." << endl; }
                }
                else if (cil == 2 && hpStredni > 0) {
                    hpStredni -= dmg;
                    if (hpStredni <= 0) { int obnova = rand() % 4; stamina = (stamina + obnova > maxStamina) ? maxStamina : stamina + obnova; cout << jmenoStredni << " padl! Obnovilo se ti " << obnova << " staminy." << endl; }
                }
                else if (cil == 3 && hpMiniBoss > 0) {
                    hpMiniBoss -= dmg;
                    if (hpMiniBoss <= 0) { int obnova = rand() % 4; stamina = (stamina + obnova > maxStamina) ? maxStamina : stamina + obnova; cout << jmenoMiniBoss << " padl! Obnovilo se ti " << obnova << " staminy." << endl; }
                }
            }

            if (hpLehke > 0) { hp -= dmgLehke; cout << jmenoLehke << " ti ubral " << dmgLehke << " HP!" << endl; }
            if (hpStredni > 0) { hp -= dmgStredni; cout << jmenoStredni << " ti ubral " << dmgStredni << " HP!" << endl; }
            if (hpMiniBoss > 0) { hp -= dmgMiniBoss; cout << jmenoMiniBoss << " ti ubral " << dmgMiniBoss << " HP!" << endl; }
        }

        if (hp <= 0) { cout << "\nZemrel jsi v boji! Hra konci." << endl; system("pause"); return 0; }
        cout << "\nUspesne jsi porazil vsechny nepratele v lese!" << endl;
    }
    else {
        cout << "\n--- OPUSTENA VESNICE ---" << endl;
        cout << "Vstupujes do opustene vesnice. Vsude je ticho a polorozpadle domy." << endl;

        if (radaDoVesnice) {
            cout << "\nDiky rade od Moudreho kamene nachazis skrytou starou truhlu!" << endl;
            cout << "Nachazis v ni vylepseni brneni! Tvoje obrana se zvysila o 5." << endl;
            obrana += 5;
        }

        cout << "Z rozpadle stodoly se na tebe vrhnou monstra z poli a luk!" << endl;
        int hpLehke = 10, dmgLehke = 2; string jmenoLehke = "Zdivocely pes";
        int hpStredni = 15, dmgStredni = 4; string jmenoStredni = "Polni skret";

        while (hp > 0 && (hpLehke > 0 || hpStredni > 0)) {
            cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
            if (hpLehke > 0) cout << "[1] HP " << jmenoLehke << ": " << hpLehke << endl;
            if (hpStredni > 0) cout << "[2] HP " << jmenoStredni << ": " << hpStredni << endl;

            int cil = 0;
            cout << "Kdo bude tvuj cil? (1 nebo 2): ";
            cin >> cil;

            int dmg = ZvolUtok(stamina, maxStamina, utok, specialita, jmeno, mensiStaminaCena);
            if (dmg > 0) {
                if (cil == 1 && hpLehke > 0) {
                    hpLehke -= dmg;
                    if (hpLehke <= 0) { int obnova = rand() % 4; stamina = (stamina + obnova > maxStamina) ? maxStamina : stamina + obnova; cout << jmenoLehke << " byl porazen! Obnovilo se ti " << obnova << " staminy." << endl; }
                }
                else if (cil == 2 && hpStredni > 0) {
                    hpStredni -= dmg;
                    if (hpStredni <= 0) { int obnova = rand() % 4; stamina = (stamina + obnova > maxStamina) ? maxStamina : stamina + obnova; cout << jmenoStredni << " byl porazen! Obnovilo se ti " << obnova << " staminy." << endl; }
                }
            }

            if (hpLehke > 0) { hp -= dmgLehke; cout << jmenoLehke << " ti ubral " << dmgLehke << " HP!" << endl; }
            if (hpStredni > 0) { hp -= dmgStredni; cout << jmenoStredni << " ti ubral " << dmgStredni << " HP!" << endl; }
        }

        if (hp <= 0) { cout << "\nZemrel jsi v boji! Hra konci." << endl; system("pause"); return 0; }
        cout << "\nUspesne jsi porazil nepratele v opustene vesnici!" << endl;
    }

    cout << "\nPrezil jsi to nejhorsi! Pokracovani priste..." << endl;
    cout << "\nStiskni Enter pro ukonceni..." << endl;
    system("pause");
    return 0;
}
