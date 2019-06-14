Úkolem je realizovat sadu funkcí pro práci se spojovými seznamy. Úřad je definován dvojicí spojových seznamů. První reprezentuje seznam pracovníků a druhý seznam automobilů. Pracovník je reprezentován jménem a může obsahovat odkaz na přidělený automobil. Automobil je reprezentován názvem modelu. S takovou strukturou chceme provádět tyto operace: inicializace úřadu, přidání pracovníka, přidání automobilu, kopírování úřadu a mazání úřadu.

TEMPLOYEE

tato datová struktura je deklarovaná v testovacím prostředí. Vaše implementace bude s touto strukturou pracovat, ale nesmí jí nijak měnit. Struktura reprezentuje jednoho zaměstnance. Zaměstnanci jsou uloženi v podobě jednosměrně zřetězeného spojového seznamu. Struktura má následující složky:

m_Next - odkaz na dalšího zaměstnance ve spojovém seznamu. Poslední zaměstnanec v seznamu má odkaz m_Next nastaven na hodnotu NULL.
m_Car - odkaz na přidělený automobil. Odkaz má buď hodnotu NULL (pak automobil není přidělený), nebo odkazuje na nějaký prvek spojového seznamu automobilů.
m_Name - ASCIIZ (nulou ukončený) řetězec udávající jméno zaměstnance.
TCAR

tato datová struktura je deklarovaná v testovacím prostředí. Vaše implementace bude s touto strukturou pracovat, ale nesmí jí nijak měnit. Struktura reprezentuje jeden automobil. Automobily jsou uložené v podobě jednosměrně zřetězeného spojového seznamu. Struktura má následující složky:

m_Next - odkaz na další automobil ve spojovém seznamu. Poslední automobil v seznamu má odkaz m_Next nastaven na hodnotu NULL.
m_Model - ASCIIZ (nulou ukončený) řetězec udávající typ automobilu.
TOFFICE

tato datová struktura je deklarovaná v testovacím prostředí. Vaše implementace bude s touto strukturou pracovat, ale nesmí jí nijak měnit. Struktura reprezentuje jeden úřad a má následující složky:

m_Emp - počátek spojového seznamu zaměstnanců,
m_Car - počátek spojového seznamu automobilů,
initOffice ()

funkce vytvoří nový prázdný úřad. Struktura úřadu bude dynamicky alokována, oba seznamy (zaměstnanci i automobily) budou prázdné.

addEmployee ( office, name )

funkce vytvoří nový prvek ve spojovém seznamu zaměstnanců a umístí jej na první pozici v seznamu. Parametrem je name - jméno nového pracovníka a office - úřad, kam bude zaměstnanec přidán. Nově přidávaný zaměstnanec nemá přidělený automobil, tedy složka m_Car bude mít hodnotu NULL.

addCar ( office, model )

funkce vytvoří nový prvek ve spojovém seznamu automobilů a umístí jej na první pozici v seznamu. Parametrem je model - model nového automobilu a office - úřad, kam bude automobil přidán.

freeOffice ( office )

funkce k uvolnění prostředků alokovaných ve spojových seznamech zadaného úřadu. Funkci je předán odkaz na úřad k uvolnění, funkce uvolní paměť používanou zaměstnanci i automobily zadaného úřadu a následně uvolní i strukturu vlastního úřadu.

cloneOffice ( office )

funkce vytvoří kopii zadaného úřadu. Nově vytvořený úřad musí zachovat jména zaměstnanců i automobilů včetně jejich pořadí v seznamech a musí správně upravit odkazy na přidělené automobily. Pozor, nově vytvořený seznam musí být zcela nezávislý na originále, tedy i odkazy na automobily musí směřovat na prvky nově vytvořeného seznamu. Návratovou hodnotou funkce je odkaz na dynamicky alokovanou strukturu nového úřadu.

Odevzdávejte zdrojový soubor, který obsahuje implementaci požadovaných funkcí. Do zdrojového souboru přidejte i další Vaše podpůrné funkce, které jsou z nich volané. Implementované funkce budou volané z testovacího prostředí, je proto důležité přesně dodržet zadané rozhraní funkcí. Za základ pro implementaci použijte kód z přiloženého souboru. V kódu chybí vyplnit těla požadovaných funkcí (a případné další podpůrné funkce). Ukázka obsahuje testovací funkci main, uvedené hodnoty jsou použité při základním testu. Všimněte si, že vkládání hlavičkových souborů a funkce main jsou zabalené v bloku podmíněného překladu (#ifdef/#endif). Prosím, ponechte bloky podmíněného překladu i v odevzdávaném zdrojovém souboru. Podmíněný překlad Vám zjednoduší práci. Při kompilaci na Vašem počítači můžete program normálně spouštět a testovat. Při kompilaci na Progtestu funkce main a vkládání hlavičkových souborů „zmizí“, tedy nebude kolidovat s hlavičkovými soubory a funkcí main testovacího prostředí.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. Rozumná implementace naivního algoritmu by měla projít všemi testy kromě testu rychlosti. Pro zvládnutí testu rychlosti je potřeba použít výkonnější algoritmus, který efektivně kopíruje seznamy.