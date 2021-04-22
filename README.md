# Tema1PC-Tetris
[Tema1 Programarea Calculatoarelor (2018-2019, seria CB)]

Programul simuleaza un joc de Tetris care foloseste scrierea binara a numerelor pentru codificarea hartii si a pieselor. <br>
Enunt: https://ocw.cs.pub.ro/courses/programare/teme_2018/tema1_2018_cbd

#### IMPLEMENTARE
Functia ```is_set``` testeaza daca bitul i din scrierea numarului n este setat(are valoarea 1).
Functia ```print_map``` afiseaza harta sub codificarea ceruta de enuntul problemei cu "." pentru bitul 0 si "#" pentru bitul 1. Aceasta parcurge fiecare bit din numar si prin apelarea functiei ```is_set``` afla daca e 0 sau 1.

Functia ```build_right``` este creata pentru a returna un numar care are setati bitii,in reprezentarea sub forma de harta,pe coloana margine din dreapta. Functia ```build_left``` are aceeasi intrebuintare pentru coloana din stanga. Cele doua sunt utile in tratarea cazului in care transformarea pe care o face piesa depaseste limitele liniei pe care se afla.

Functia ```check_line``` verifica daca harta are vreo linie completata. Aceasta parcurge numarul si contorizeaza printr-o variabila k numarul de biti setati de pe o linie.Daca k ajunge la valoarea 8 inseamna ca linia curenta este completata si functia returneaza indicele liniei,respectiv in caz contrar returneaza -1.
Functia ```remove_line``` este apelata in cazul in care ```check_line``` are o valoare diferita de -1 si returneaza numarul dupa ce a fost stearsa linia care era completata. Aceasta functioneaza prin folosirea a 2 variabile copii ale numarului care urmeaza sa fie shiftate la stanga ,respectiv dreapta, astfel incat prin aplicarea operatorului " | " numarul rezultat are linia completata stearsa.

Pentru calcularea scorului la sfarsitul jocului este necesar numarul de zerouri din scrierea binara a hartii in forma finala.De aceea, functia ```zeros_number``` contorizeaza si returneaza numarul de zerouri.
Functia ```print_score``` afiseaza ```"GAME OVER!"``` si scorul.Este calculat scorul obtinut prin intermediul formulei date, tinand cont ca acesta trebuie sa aiba 2 zecimale exacte.

Urmeaza citirea hartii (H), a numarului de piese(M), a pieselor(P) si a transformarilor asociate(t). Metoda abordatata citeste pe rand fiecare piesa si transformarile ei,efectuand miscarile cerute dupa care se trece mai departe la urmatoarea piesa.
Se afiseaza harta initiala.
Verificarea daca harta si piesa se intersecteaza in scrierea binara se va face prin aplicarea operatorului " & " intre cele doua (un rezultat diferit de 0  inseamna ca se intersecteaza,prin urmare avem o coliziune).
Imbinarea hartii cu piesa se realizeaza prin operatorul " | " intre cele 2.

Avand in vedere ca piesa poate fi reprezentata in format grafic ca fiind maxim pe 2 nivele,vom trata separat cazurile corespunzatoare primelor 2 transformari citite. Pentru inceput vom salva valoarea piesei in 2 variabile (copy_P si copy2_P).Piesa se shifteaza la stanga cu 48 de pozitii,iar copy_P cu inca 8. 

Urmatoarele comenzi se efectueaza pentru j=1 corespunzatoare primei mutari. In cazul in care copy_P se intersecteaza cu harta,reprezentand ca nivelul de jos al piesei nu incape pe harta,se printeaza harta cu piesa integrata si scorul, iar jocul se incheie.

In continuare,se afla daca transformarea se presupune sa se efectueze la stanga sau la dreapta(t>0 sau t<0).
Pentru t>0, piesa se va muta in directia ceruta cu cate o pozitie daca harta este libera si permite toate mutarile,nu exista coliziuni,piesa nu trece pe randul urmator. Se verifica daca copy_P nu este pe margine prin evaluarea expresiei (copy_P | margin_right),variabila din urma reprezentand output-ul dat de functia ```border-right``` care reprezinta un numar care in scrierea binara are pe coloana din dreapta toate pozitiile ocupate de valoarea 1.Prin urmare,daca cele 2 se intersecteaza inseamna ca piesa este deja la margine si nu mai poate fi mutata peste limita peretelui din dreapta.Se mai testeaza daca exista coliziune intre harta si piesa,daca piesa nu mai poate avansa la un moment dat in directia dorita.In cazul in care cerintele nu sunt indeplinite piesa se blocheaza si este afisata harta cu piesa integrata.
Se procedeaza similar in cazul mutarii la stanga(t<0).

Daca piesa a trecut de primul nivel,se testeaza separat pentru al 2-lea (j==2).Procesul este similar si piesa trebuie sa treaca de aceleasi restictii de mai sus.Pentru a optimiza procesul,verificarea daca piesa incape pe harta se realizeaza doar pentru piese care au 2 nivele(adica mai mari de 255),folosindu-se de aceasta data variabila copy2_P.

Pentru j>2 se procedeaza in acelasi mod.

Daca piesa realizeaza o coliziune la deplasarea in jos si se blocheaza,trebuie sa tinem cont ca transformarile care urmeaza pentru piesa curenta vor fi citite chiar daca nu mai sunt valide.Prin urmare,se vor citi fara a efectua nimic cu ele.

Dupa fiecare mutate efectuata cu succes se va afisa harta si piesa.Se va actualiza valoarea hartii cu ultima intersectie de harta si piesa obtinuta.

Se verifica daca harta are linii completate prin apelarea functiei ```check_line``` si eventual se actualizeaza cu valoarea care nu contine linii,numarandu-se in acelasi timp in variabila completed_lines cate linii s-au eliminat.Daca s-a eliminat ceva se si afiseaza noua harta.

Daca programul ajunge sa execute toate transformarile,se sfarseste jocul si se afiseaza scorul obtinut.

