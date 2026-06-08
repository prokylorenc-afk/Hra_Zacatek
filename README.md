
⚔️ Temný Les: Záchrana Království 🏰
Vítej u mého textového RPG dobrodružství! Tato hra tě zavede do fantasy světa, kde králův nejlepší oddíl zmizel v Temném lese a je jen na tobě, abys zjistil, co se stalo, a zachránil království před temnou hrozbou. Připrav se na taktické tahové souboje, řešení hádanek, správu surovin a těžká rozhodnutí, která ovlivní osud celého království!

🛠️ Použité knihovny a technologie
Hra je naprogramována v čistém jazyce C++. Aby celý svět fungoval – od soubojů až po náhodná zranění jedem – využívá hra několik standardních knihoven. Zde je jejich podrobný rozbor s ukázkami přímo ze hry:

🖥️ 1. Knihovna 
Toto je absolutní základ každé konzolové aplikace v C++. Zkratka znamená "Input/Output Stream". Stará se o to, aby hra mohla s hráčem komunikovat: vypisovat mu příběh, ukazovat stav životů (pomocí cout) a naopak číst to, co hráč zadá na klávesnici (pomocí cin).

Jak to funguje v mém kódu:
Kdykoliv potřebuji vypsat menu nebo přijmout volbu hráče v souboji, používám tuto knihovnu.

cout << "\nTVOJE HP: " << hp << " | STAMINA: " << stamina << "/" << maxStamina << endl;
cout << "Kdo bude tvuj cil? (1, 2 nebo 3): ";
cin >> cil;

📜 2. Knihovna 
V základním C/C++ se texty dají ukládat jako složitá pole znaků, což je velmi nepraktické. Knihovna <string> přidává datový typ pro snadnou práci s textovými řetězci. V mé hře ji používám pro dynamické pojmenovávání nepřátel, útoků nebo pro čtení odpovědí na hádanky.

Jak to funguje v mém kódu:
Ukládám do něj jména monster, aby se výpisy v konzoli hezky formátovaly, nebo kontroluji textovou odpověď hráče.

string jmStredni = "[STREDNI] Obri pavouci matka";
string odpovedHrace;
cin >> odpovedHrace;
if (odpovedHrace == "kniha") { pocetUhodnutych++; }

🎲 3. Knihovny  a 
Hra na hrdiny by nebyla zábavná bez prvku náhody. <cstdlib> poskytuje funkci rand(), která generuje náhodná čísla. Kdybychom ale použili jen tu, hra by pokaždé házela stejná čísla ve stejném pořadí. Proto se s ní páruje <ctime>, která umí přečíst aktuální čas počítače. Pomocí příkazu srand(time(0)) na začátku hry se generátor "nastartuje" aktuálním časem, takže je každá hra stoprocentně unikátní.

Jak to funguje v mém kódu:
Používám náhodu pro útoky jedem, kde nepřítel uštědří náhodné poškození od 1 do 3, nebo pro různé chování finálního bosse.

int jed = rand() % 3 + 1;
hp -= jed;
cout << "Vysvetlivka: Jsi otraveny! Jed ubral dalsich " << jed << " HP." << endl;

🧮 4. Knihovna 
Tato knihovna obsahuje spoustu matematických a řadících funkcí. Já z ní využívám extrémně užitečnou funkci min(). Ta porovná dvě čísla a vybere to menší. Je to dokonalá pojistka ("guardrail"), která brání tomu, aby si hráč obnovil více staminy nebo životů, než je jeho povolené maximum.

Jak to funguje v mém kódu:
Když hráč zabije monstrum nebo odpočívá po boji, obnoví se mu stamina/HP, ale nikdy nepřesáhne svůj limit (např. maxStamina).

stamina = min(maxStamina, stamina + 5);
hp = min(maxHp, hp + 10);

⚙️ Detailní rozbor logiky a architektury kódu
Aby byl kód čistý a funkční, je postaven na několika provázaných systémech.

⚔️ Dynamický soubojový systém (while cykly)
Boje nejsou jen jeden statický útok. Jsou tvořeny pomocí cyklů while. Cyklus běží tak dlouho, dokud je hráč naživu (hp > 0) a zároveň žije alespoň jedno monstrum ze skupiny (např. hpLehke > 0 || hpBoss > 0).

Tento systém umožňuje taktické boje proti skupinám nepřátel. Hráč si pomocí čísel vybírá, na koho zaútočí, a funkce ZvolUtok() následně propočítá výdej staminy a poškození. Pokud hráč nemá dostatek staminy, neudělí poškození a musí jedno kolo odpočívat, přičemž do něj nepřátelé stále buší.

👹 Modifikátory nepřátel
Při návrhu nepřátel jsem nechtěl, aby to byly jen "boxovací pytle". Přidal jsem jim specifické vlastnosti ovlivňující boj:

[RYCHLÝ] Vodní had: Hráči je ubráno HP ještě před prvním tahem, simulující překvapivý útok.

[BRNĚNÍ] Kamenný golem: Samostatná podmínka při útoku snižuje hráčovo poškození. Kód doslova říká: dmg -= 1; if (dmg < 0) dmg = 0; (aby hráč monstrum nezačal omylem léčit záporným útokem).

[DÁLKA] Temný dryád: Do funkce útoku se odesílá speciální proměnná extraStam = 1, která hráče nutí zaplatit více staminy za to, že musí k nepříteli doběhnout.

🛍️ Obchodní systém a ochrana před chybami
Ve vesnicích má hráč možnost nakupovat upgrady. Kód je zde chráněn pomocí podmínek if a else if, aby hráč nemohl podvádět.

Kód nejdříve zkontroluje, zda má hráč dostatek drahokamů: if (drahokamy < 5).

Dále kontroluje, zda má nákup vůbec smysl: else if (hp == maxHp && stamina == maxStamina) zabraňuje tomu, aby hráč zbytečně utratil peníze za léčení, když je plně zdravý.

Aby se hráč nemohl ve druhé vesnici "naboostovat" do nekonečna, je zde implementováno počítadlo int nakupy = 0; while (nakupy < 2), které obchod automaticky uzavře po dvou transakcích.

🛡️ Finální Boss a "Geomancerova magie"
Závěrečný souboj s Temným králem Ramusem obsahuje unikátní mechaniku. Hráč vybírá geometrické tvary (Čtverec, Obdélník, Kruh) pro magický štít. Kód následně provádí výpočty zranění na základě hráčovy volby. U obdélníku se dokonce dynamicky počítá poškození na základě hráčova aktuálního levelu: bossDmg = baseBossDmg * (2 + (level * 2));. To zajišťuje, že boss zůstává hrozbou i pro velmi "nakažené" (vyexpované) postavy.

🏆 Konec hry a Morální Volba
Na samotném konci hry, pokud hráč disponuje Amuletem čistoty, může z krále Ramuse vyhnat temnotu a vyslechnout si jeho příběh (Lore). Hra nabízí dvě různé příběhové cesty – popravu, nebo uvěznění – čímž přidává na znovuhratelnosti.
