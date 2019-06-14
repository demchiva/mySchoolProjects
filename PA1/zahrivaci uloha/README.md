Úkolem je vytvořit program, který bude zobrazovat vybrané citáty.

Vstupem programu je jedno celé číslo. Toto číslo je z rozsahu 1 až 5 a určuje citát, který má být zobrazen.

Výstupem programu je citát odpovídající zadanému číslu na vstupu. Citáty odpovídající jednotlivým číslům jsou uvedené v ukázkových bězích programu níže. Pozor, za textem citátu je odřádkování (\n).

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

vstup není celé číslo,
na vstupu je celé číslo mimo interval 1 až 5.
Při programování si dejte pozor na přesnou podobu výpisů. Výstup Vašeho programu kontroluje stroj, který požaduje přesnou shodu výstupů Vašeho programu s výstupy referenčními. Za chybu je považováno, pokud se výpis liší. I chybějící nebo přebývající mezera/odřádkování je považováno za chybu. Abyste tyto problémy rychle vyloučili, použijte přiložený archiv se sadou vstupních a očekávaných výstupních dat. Podívejte se na videotutoriál (edux → výuková videa), jak testovací data použít a jak testování zautomatizovat.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti (ale tato úloha by ani s jedním omezením neměla mít problém). Testovací prostředí dále zakazuje používat některé „nebezpečné funkce“ – funkce pro spouštění programu, pro práci se sítí, … Pokud jsou tyto funkce použité, program se nespustí. Možná ve svém programu používáte volání:

int main ( int argc, char * argv [] )
{
 
  ...
 
  system ( "pause" ); /* aby se nezavrelo okno programu */
  return 0;
}
Toto nebude v testovacím prostředí fungovat - je zakázáno spouštění jiného programu. (I pokud by se program spustil, byl by odmítnut. Nebyl by totiž nikdo, kdo by pauzu „odmáčkl“, program by čekal věčně a překročil by tak maximální dobu běhu.) Pokud tedy chcete zachovat pauzu pro testování na Vašem počítači a zároveň chcete mít jistotu, že program poběží správně, použijte následující trik:

int main ( int argc, char * argv [] )
{
 
  ...
 
#ifndef __PROGTEST__
  system ( "pause" ); /* toto progtest "nevidi" */
#endif /* __PROGTEST__ */
  return 0;
} 