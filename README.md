**🌲 RPG Dobrodružství: Cesta do Temného lesa**
Vítejte u zdrojového kódu textového RPG! Tento projekt je plně interaktivní konzolová hra napsaná v C++, která otestuje vaše strategické myšlení. Hra obsahuje komplexní tahový soubojový systém, správu inventáře, levelování a větvený příběh.

**📚 Použité knihovny a jejich význam**
Hra využívá několik standardních C++ knihoven pro zajištění plynulého chodu, matematických operací a náhody.

<iostream>
Základní stavební kámen pro komunikaci s hráčem. Stará se o vstup a výstup textu do konzole.

Příklad v kódu:

C++
cout << "Vitej v Temnem lese, hrdino!" << endl;
cin >> volba;
<cstdlib>
Tato knihovna nám dává přístup k funkcím pro generování pseudonáhodných čísel (rand()). Je to mozek veškeré nevyzpytatelnosti ve hře (např. šance na kritický zásah nebo síla nepřátelského útoku).

Příklad v kódu (Výpočet poškození):

C++
// Vygeneruje nahodne poskozeni mezi 5 a 10
int dmg = (rand() % 6) + 5; 
<ctime>
Slouží k získání aktuálního systémového času. Používáme ji ve spojení s <cstdlib>, aby hra při každém spuštění generovala jiná náhodná čísla (tzv. "seedování").

Příklad v kódu:

C++
srand(time(0)); // Inicializace generatoru nahody hned na zacatku main()
<algorithm>
Obsahuje pokročilé matematické funkce. V našem RPG se stará o to, aby statistiky hráče nepřekročily stanovené limity (např. aby se hráč neuzdravil na 120 HP, když je jeho maximum 100).

Příklad v kódu:

C++
// Hrac se vyleci o 20, ale nikdy nepresahne svuj maximalni limit
hp = max(0, min(maxHp, hp + 20)); 
**⚙️ Architektura a Klíčové Funkce**
Kód je navržen tak, aby byl modulární. Využívá předávání parametrů odkazem (pomocí operátoru &) a ukazateli (*), což umožňuje funkcím přímo upravovat hlavní proměnné hráče, jako jsou životy nebo výdrž. Rozhodovací logika často využívá switch příkazy a stavové proměnné typu bool (např. maAmulet), které přesně řídí, kam se hráč může vydat a jaké akce má odemčené.

**⚔️ Funkce ZvolUtok**
Toto je hlavní engine každého souboje.

Jak funguje: Funkce přijímá data hráče (odkazy na staminu, útok) a vrací hodnotu poškození, které hráč způsobil. Zároveň zjišťuje, zda se hráč nerozhodl raději bránit nebo léčit.

Ukázka logiky:

C++
int ZvolUtok(int& stamina, int maxStamina, int utok, int* hp, int maxHp) {
    // Hrac vybira akci (1. Rychly utok, 2. Silny utok...)
    // Funkce snizi staminu a vrati vygenerovane 'dmg'
}
**🌟 Funkce PridejXP**
Stará se o levelování hrdiny na konci každého vítězného boje.

Jak funguje: Přičte získané zkušenosti. Pokud přetečou hranici pro další úroveň, funkce automaticky zvýší level, upraví maximální HP a zvedne základní útok.

C++
void PridejXP(int ziskaneXP, int& xp, int& level, int& xpDoDalsihoLevelu, int& maxHp, int& utok) {
    xp += ziskaneXP;
    if (xp >= xpDoDalsihoLevelu) {
        level++;
        // Uprava statu pro novy level...
    }
}
**🎮 Detailní rozbor herních mechanik**


**🗡️ Jak funguje útočení a damage (poškození)**

Útočný systém kombinuje pevně dané statistiky s prvkem náhody a aktuálním stavem výdrže (staminy).

Volba útoku: Hráč zvolí typ útoku (např. lehký útok stojí 10 staminy, těžký 25).

Výpočet: Základní utok hráče se sečte s náhodným modifikátorem rand().

Penetrace obrany: Z výsledného poškození se odečte obrana nepřítele. Výsledek se následně odečte z hp (životů) nepřítele.

**🛡️ Jak fungují HP a Obrana**
HP (Health Points): Reprezentují životní sílu. Pokud klesnou na 0, hra končí. Program neustále hlídá cyklus while (hp > 0), který udržuje hráče ve hře.

Obrana: Funguje jako štít. Snižuje každé příchozí poškození o fixní částku. Pokud má nepřítel útok 15 a hráč obranu 5, hráč ztratí pouze 10 HP.

Léčení: Pomocí lektvarů nebo amuletů lze HP doplňovat, ale díky funkci std::min nikdy nepřesáhnou hodnotu maxHp.

**📈 Jak fungují XP (Zkušenosti)**
Zkušenostní systém odměňuje hráče za riskování.

Za každého poraženého nepřítele hráč obdrží specifický počet XP.

Hra si drží proměnnou xpDoDalsihoLevelu. Ta se s každým levelem zvyšuje (např. na level 2 je potřeba 100 XP, na level 3 už 250 XP).

Levelování je klíčové pro finální fáze hry, protože trvale zvyšuje maxHp a základní poškození, bez kterého nelze porazit Bosse.

**🗺️ Game Flow (Průběh hry)**
Hra běží v hlavní smyčce main(), která drží hráče v neustálé interakci.

Průzkumná fáze: Hráč si vybírá cesty (Lokace A, Lokace B, Obchod). Každá volba je řízena vstupy přes cin.

Soubojová fáze: Jakmile dojde ke střetu, spustí se vnořený cyklus while(hp > 0 && nepritelHp > 0). Tento cyklus se opakuje tak dlouho, dokud jedna strana nezemře.

Ekonomika: Obchodní systém porovnává nasbírané suroviny (drahokamy) s cenami předmětů a pomocí bool proměnných zamyká položky, které si hráč už jednou koupil.

**Hlavní vývojář a architekt: Prokop Lorenc**

**AI spolupracovník a technický mentor: Gemini (Google)**

**Verze: 1.0 (Konečná verze)**
