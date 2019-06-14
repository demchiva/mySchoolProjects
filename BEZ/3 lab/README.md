Pomocí šablony kódu z minulé laboratoře si připravte program, který bude šifrovat zadaný řetězec pomocí šifry DES s operačním módem ECB.
Volbu šifry a operačního módu zjistěte z dokumentace EVP_EncryptInit (man EVP_EncryptInit).
Vlastnosti operačního módu demonstrujte pomocí zašifrování obrazových dat (datové části obrázku ve formátu BMP)
Stáhněte si např. tento obrázek ve formátu BMP (rozbalte zip): obrazek.zip. (homer-simpson.zip)
Napište program, který zkopíruje hlavičku a zašifruje část souboru s obrazovými daty pomocí DES v módu ECB. Výstupní soubor se bude jmenovat (původní_jméno)_ecb.bmp
Napište program, který dešifruje obrázek zašifrovaný prvním programem. Výstupní soubor se bude jmenovat (původní_jméno)_dec.bmp. Porovnejte dešifrovaný soubor s původním.
Porovnejte původní obrázek a jeho zašifrovanou podobu a vysvětlete svá zjištění
Změňte pro šifrování i dešifrování použitý operační mód na CBC a vytvořte (původní_jméno)_cbc.bmp a (původní_jméno)_cbc_dec.bmp(upřesní cvičící)
Porovnejte původní obrázek a jeho zašifrovanou podobu a vysvětlete svá zjištění

Program se bude volat s následujícími přepínači/argumenty:
  -e sifrovani
  -d desifrovani
  ecb mod ecb
  cbc mod cbc
  nazev vstupniho souboru

Výstup:
  V případě chyby žádný výstupní soubor
  Zašifrovaný soubor s příponou _ecb.bmp/_cbc.bmp
  Dešifrovaný soubor s příponou _dec.bmp

Návratové hodnoty:
  0 vše OK
  !=0 chyba