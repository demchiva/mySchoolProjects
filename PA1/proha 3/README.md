Úkolem je realizovat funkci (ne celý program, pouze funkci), která bude navrhovat hyperloop tratě. Funkce bude na základě parametrů určovat, jak poskládat segmenty tratě, aby vznikla trať přesně požadované délky. Tato úloha je rozšířením jednodušší varianty, trať bude sestavována ze segmentů až tří různých délek.

Trať pro hyperloop je tvořena tubusem kruhového průřezu. Tubus je složen se segmentů určité délky. Předpokládáme, že segmenty dodávají tři výrobci, každý výrobce dodává segment s jednou fixní délkou. Dvojice sousedních segmentů je spojena právě jednou vzduchotěsnou přepážkou. Dále, vzduchotěsnou přepážkou musí celý tubus začínat i končit. Všechny přepážky mají stejnou délku. Segmenty ani přepážky nelze zkracovat ani prodlužovat. Úkolem funkce je určit, zda lze sestavit ze segmentů a přepážek tubus přesně zadané délky. Pokud tubus zadané délky sestavit lze, funkce navíc určí i počty potřebných segmentů jednotlivých délek a určí, kolika různými způsoby lze tubus sestavit.

Platné sestavení tubusu je tedy:

bulkhead
bulkhead segment bulkhead
bulkhead segment bulkhead segment bulkhead
bulkhead segment bulkhead segment bulkhead segment bulkhead
bulkhead segment bulkhead segment bulkhead segment bulkhead segment bulkhead
...
Požadovaná funkce má následující rozhraní:

unsigned long long int  hyperloop                          ( unsigned long long int len, 
                                                             unsigned int s1, 
                                                             unsigned int s2, 
                                                             unsigned int s3, 
                                                             unsigned int bulkhead, 
                                                             unsigned int * c1, 
                                                             unsigned int * c2, 
                                                             unsigned int * c3 );
len

je vstupní parametr udávající požadovanou délku tubusu,
s1, s2, s3

jsou vstupní parametry udávající délku segmentu od prvního/druhého/třetího výrobce. Parametry mohou být zadané i jako nulové, tato hodnota znamená, že segmenty od prvního/druhého/třetího výrobce (a případně i od více výrobců) nejsou k dispozici a při konstrukci nesmí být použity (musí stačit segmenty od jiných výrobců),dispozici (při konstrukci nesmí být použity).
bulkhead

je vstupní parametr udávající délku spojovací vzduchotěsné přepážky. Parametr může být zadaný jako 0, přepážky pak neprodlouží celkovou délku tubusu,
c1, c2, c3

jsou výstupní parametry, který udávají počet potřebných segmentů od prvního/druhého/třetího výrobce. Pokud se funkci nepodaří najít žádné řešení, ponechá parametry beze změny,
návratová hodnota

návratovou hodnotou funkce je počet nalezených řešení, případně informace o neúspěchu. Pokud výpočet neuspěje (požadované délky nelze dosáhnout žádnou platnou kombinací segmentů a přepážek) vrátí funkce hodnotu 0. Pokud požadované délky dosáhnout lze, funkce vrátí počet existujících různých kombinací segmentů, které vedou k požadované délce. Výstupní parametry c1, c2 a c3 nastaví na libovolné jedno z těchto řešení.
Dvě řešení považujeme za různá, pokud se v nich liší požadované počty segmentů nějaké délky. Naopak, pokud obě řešení vyžadují stejný počet segmentů v každé délce, považujeme je za ekvivalentní a do výsledku je započteme pouze jednou. Tedy:
- změna pořadí segmentů v tubusu nehraje roli. Například pro:
               len = 27
               s1 = 3
               s2 = 9
               s3 = 1
               bulkhead = 5
- existují možnosti:
               [bulkhead] [segment 3] [bulkhead] [segment 3] [bulkhead] [segment 1] [bulkhead]
               [bulkhead] [segment 3] [bulkhead] [segment 1] [bulkhead] [segment 3] [bulkhead]
               [bulkhead] [segment 1] [bulkhead] [segment 3] [bulkhead] [segment 3] [bulkhead]
       
               [bulkhead] [segment 3] [bulkhead] [segment 9] [bulkhead]
               [bulkhead] [segment 9] [bulkhead] [segment 3] [bulkhead]
- Z těchto možností jsou ale první tři ekvivalentní (všechna vyžadují 2 segmenty délky 3, 0 segmentů délky 9 a jeden segment délky 1) a poslední dvě jsou také ekvivalentní (obě vyžadují 1 segment délky 3, 1 segment délky 9 a 0 segmentů délky 1).
               2 * s1 + 0 * s2 + 1 * s3 + 4 * bulkhead = 27
               1 * s1 + 1 * s2 + 0 * s3 + 3 * bulkhead = 27
     
               hyperloop ( 27, 3, 9, 1, 5, &c1, &c2, &c3 ) == 2
- pokud dva nebo všichni tři výrobci vyrábějí segmenty stejné délky, pak jsou tyto segmenty neodlišitelné. Například pro:
               len = 40
               s1 = 10
               s2 = 10
               s3 = 20
               bulkhead = 0
- existuje 9 možných poskládání segmentů do výsledku:
               4 * s1 + 0 * s2 + 0 * s3 + 5 * bulkhead = 40
               3 * s1 + 1 * s2 + 0 * s3 + 5 * bulkhead = 40
               2 * s1 + 2 * s2 + 0 * s3 + 5 * bulkhead = 40
               1 * s1 + 3 * s2 + 0 * s3 + 5 * bulkhead = 40
               0 * s1 + 4 * s2 + 0 * s3 + 5 * bulkhead = 40
       
               2 * s1 + 0 * s2 + 1 * s3 + 4 * bulkhead = 40
               1 * s1 + 1 * s2 + 1 * s3 + 4 * bulkhead = 40
               0 * s1 + 2 * s2 + 1 * s3 + 4 * bulkhead = 40
       
               0 * s1 + 0 * s2 + 2 * s3 + 3 * bulkhead = 40
- Těchto 9 možností ale dává pouze 3 různá řešení. První řešení potřebuje 4 segmenty délky 10 a 0 segmentů délky 20. Druhé řešení potřebuje 2 segmenty délky 10 a 1 segment délky 20. Poslední řešení potřebuje 0 segmentů délky 10 a 2 segmenty délky 20:
               hyperloop ( 40, 10, 10, 20, 0, &c1, &c2, &c3 ) == 3
Odevzdávejte zdrojový soubor, který obsahuje implementaci požadované funkce hyperloop. Do zdrojového souboru přidejte i další Vaše podpůrné funkce, které jsou z ní volané. Funkce hyperloop bude volaná z testovacího prostředí, je proto důležité přesně dodržet zadané rozhraní funkce. Za základ pro implementaci použijte kód z přiloženého souboru. V kódu chybí vyplnit tělo požadované funkce (a případné další podpůrné funkce). Ukázka obsahuje testovací funkci main, uvedené hodnoty jsou použité při základním testu. Všimněte si, že vkládání hlavičkových souborů a funkce main jsou zabalené v bloku podmíněného překladu (#ifdef/#endif). Prosím, ponechte bloky podmíněného překladu i v odevzdávaném zdrojovém souboru. Podmíněný překlad Vám zjednoduší práci. Při kompilaci na Vašem počítači můžete program normálně spouštět a testovat. Při kompilaci na Progtestu funkce main a vkládání hlavičkových souborů „zmizí“, tedy nebude kolidovat s hlavičkovými soubory a funkcí main testovacího prostředí.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. Rozumná implementace naivního algoritmu by měla projít všemi testy kromě testu rychlosti. Pro zvládnutí testu rychlosti je potřeba použít výkonnější algoritmus, který zbytečně netestuje všechny možné kombinace segmentů.