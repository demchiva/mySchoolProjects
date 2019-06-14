Úkolem je vytvořit program, který bude porovnávat dvojice trojúhelníků. Úloha je rozšířením jednodušší varianty, umožňuje zadávat vstupní trojúhelníky buď pomocí souřadnic vrcholů nebo pomocí délek stran. Doporučujeme nejprve řešit úlohu jednodušší.

V rovině jsou zadané 2 trojúhelníky. Každý trojúhelník je zadán buď pomocí trojice svých vrcholů, nebo pomocí délek svých stran:

trojúhelník určený pomocí svých vrcholů je zadán jako trojice souřadnic oddělená čárkami a uzavřená do složených závorek. Každá souřadnice je tvořena dvojicí desetinných čísel v hranatých závorkách, složky souřadnice jsou oddělené středníkem. Např.:
{ [ 1.5; 2 ], [3;4.2], [ 0.5 ; 0.6 ] }

trojúhelník určený pomocí délky svých stran je zadán jako trojice desetinných čísel, tato čísla jsou oddělená čárkami a celá trojice je umístěna do složených závorek. Např.:
{2.1, 3, 3.4}

Program přečte zadané trojúhelníky ze svého standardního vstupu a rozhodne se pro jednu z variant:

zda zadaný vstup tvoří trojúhelník (zadaná trojice bodů netvoří trojúhelník, pokud body leží na jedné přímce, strany musí splňovat trojúhelníkovou nerovnost),
zda jsou zadané trojúhelníky shodné,
zda jsou zadané trojúhelníky liší, ale mají stejný obvod, nebo
zda jsou zadané trojúhelníky zcela odlišné.
Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

nečíselné zadání souřadnic nebo délek stran (neplatné desetinné číslo),
chybějící souřadnice nebo délka strany,
chybějící nebo přebývající oddělovače (složené závorky, hranaté závorky, čárky, středníky).

Ukázka práce programu
Trojuhelnik #1:
{[0;0],[5;0],[2.5;3]}
Trojuhelnik #2:
 { [ 4 ; -1 ] , [ 7 ; 1.5 ] , [ 4 ; 4 ] } 
Trojuhelniky jsou shodne.
Trojuhelnik #1:
{
[
0
;
15
]
,	[	112	;	0	]	,[112;15]}
Trojuhelnik #2:
{96.0,40.0,104.0}
Trojuhelniky nejsou shodne, ale maji stejny obvod.
Trojuhelnik #1:
 { 10 , 15 , 10 } 
Trojuhelnik #2:
{12,8,17}
Trojuhelnik #2 ma vetsi obvod.
Trojuhelnik #1:
{[0;14.04],[11.2;0],[0;0]}
Trojuhelnik #2:
{[20.16;0],[0;2.7],[20.16;2.7]}
Trojuhelniky nejsou shodne, ale maji stejny obvod.
Trojuhelnik #1:
{[0.00;0.00],[0.24;0.70],[0.24;0.00]}
Trojuhelnik #2:
{0.65,0.78,0.25}
Trojuhelniky nejsou shodne, ale maji stejny obvod.
Trojuhelnik #1:
{51.09,49.49,4.94}
Trojuhelnik #2:
{37.92,50.11,17.49}
Trojuhelniky nejsou shodne, ale maji stejny obvod.
Trojuhelnik #1:
{[0;0],[10;0],[0;10]}
Trojuhelnik #2:
{[0;0],[10;10],[15;15]}
Neplatny trojuhelnik.
Trojuhelnik #1:
{[10;0],[20;1],[25;1.5]}
Neplatny trojuhelnik.
Trojuhelnik #1:
{1,2,3}
Neplatny trojuhelnik.
Trojuhelnik #1:
{[0;0],[999.990;204.330],[899.991;183.897]}
Neplatny trojuhelnik.
Trojuhelnik #1:
{1.923,59.240,61.163}
Neplatny trojuhelnik.
Trojuhelnik #1:
{[1;2],[3;abcd],[7,9]}
Nespravny vstup.