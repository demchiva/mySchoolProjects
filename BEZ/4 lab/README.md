Program se bude volat s následujícími přepínači/argumenty:
  -e šifrování
  -d dešifrování
  cesta k veřejnému/soukromému klíči
  soubor k šifrování/dešifrování
  výstupní soubor (šifrovaný/dešifrovaný soubor)
  
Výstup:
  V případě chyby žádný výstupní soubor
  Zašifrovaný/dešifrovaný soubor
  
Návratové hodnoty:
  0 vše OK
  !=0 chyba
  
Hlídejte správnost načtení veřejného/soukromého klíče
Kontrolujte návratové hodnoty fcí, které provádějí kryptografické operace
Při šifrování souboru je potřeba si vytvořit vhodnou vlastní hlavičku zašifrovaného souboru, pomocí které pak budete moct dešifrovat.
Tzn. všechny informace nutné pro dešifrování (klíč pro symetrickou šifru, IV, …​)
Vždy porovnávejte původní a dešifrovaný soubor, jestli je stejný! (např. diffem)
Inicializujte generátor náhodných čísel!

Napište dva programy:

První program zašifruje zprávu (soubor) pomocí kombinace symetrické a asymetrické šifry (EVP_Seal…​) pro příjemce (Vás nebo souseda).
Vstupem budou 2 soubory:
Soubor s daty (binární data obecné velikosti)
Soubor s veřejným klíčem adresáta
Výstupem bude 1 soubor obsahující vše, co je nutné pro dešifrování soukromým klíčem adresáta.
(šifrový text, typ symetrické šifry (včetně operačního módu a délky klíče), inicializační vektor a zašifrovaný symetrický klíč)
Jména souborů budou zadána formou parametrů na příkazové řádce.
Druhý program dešifruje zprávu (soubor) pomocí kombinace symetrické a asymetrické šifry (EVP_Open…​) z předchozího bodu a uloží do souboru.