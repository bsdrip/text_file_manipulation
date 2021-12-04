# text_file_manipulation

## Running the program
`run.sh` uses C11 standard. Run `chmod u+x run.sh` to give permission for users
to execute the bash script.

Run `./run.sh` to compile and run the program.  
## Task
Itt van az ősz, itt a szüret ideje is. Az "Oprendszer Hegyvidék" bírója 
(hegybíró) elrendelte, hogy a pontosabb nyilvántartás és a nemkívánatos 
"csinált bor" háttérbe szorítása miatt minden borászat köteles jelenteni az 
egyes szüretelt fajták eredményeit. Azaz meg kell adni, hogy melyik borászat, 
mekkora területről (négyszögölben), milyen típusú szőlőt szüretelt, amiből hány 
liter, milyen cukorfokú must készült. Például: _Öt puttony borászat, 1580 
négyszögöl, kékfrankos szőlőből, 2960 liter, 21 cukorfokú mustot készített._

A "Hegybíró" (szülő folyamat) véletlenszerűen kiválaszt egy borászatot és 
kiküldi a "Számadót" (gyerek folyamat), hogy ellenőrizze a borászatot. _(Pl. a 
meglévő lehetőségek mellett megjeleneik az Ellenőrzés menüpont.)_ Adatcsövön 
elküldi a "Számadónak" a borászat nevét, majd a "Számadó" az ellenőrzés után 
visszaírja, szintén csövön, hogy megbukott a borászat vagy nem. (10% a megbukás 
esélye.) "Hegybíró" ezután bejegyzi az eredményt az adatsor végére. Pl. _Öt 
puttony borászat, 1580 négyszögöl, kékfrankos szőlőből, 2960 liter, 21 
cukorfokú mustot készített:Ellenőrizve, megfelelt (vagy nem felelt meg)_

Továbbra is legyen lehetőségünk új adat hozzáadásra, módosításra, és igény 
szerint "Számadó"  újra útnak indulhat.

Készítsen C nyelvű programot ami  segít a hegybírónak, és ezt a feladatot 
megoldja, a megoldásnak vagy az opsys.inf.elte.hu kiszolgálón, vagy egy hozzá 
hasonló(linux) rendszeren kell futnia. A megoldást a beadási határidőt követő 
héten be kell mutatni a gyakorlatvezetőnek.
