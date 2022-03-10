# Image-Processing
Third assignment for Computer Science class - 2021

Task 0:
    Citirea comenzilor s-a implementat pe parcurs printr-un while care merge pana cand se citeste comanda quit.
    
Task 1:
    Pentru comanda de editare, se incarca fisierul binar intr-un buffer din care se construieste imaginea.
    Pentru comanda de salvare, se reconstruieste in mod invers fisierul binar folosind imaginea stocata.
Task 2:

    Pentru comanda insert, se incarca pentru editare separat imaginea data, se suprapune peste imaginea deja deschisa cu coltul din stanga jos in pozitia data.
    La final, se elibereaza memoria pentru imaginea care se suprapune.

Task 3:
    Pentru comenzile set, se stocheaza valorile date in variabile corespunzatoare.
    Pentru comanda draw line, se folosesc indicatiile date in enunt pentru a construi teoretic linia propriu-zisa, apoi se umple in jurul ei in functie de grosime si culoare.
    Pentru comenzile de desenare a formelor, se deseneaza liniile pentru pozitiile date sau se calculeaza pozitiile necesare daca lipsesc analog draw line.

Task 4:
    Pentru comanda de fill, se porneste din pozitia data si fiecare vecin corespunzator pozitiei curente se adauga la o coada, iar coada se parcurge pana la final.
    Astfel, se viziteaza toti pixelii de aceeasi culoare cu cel de la pozitia data si se coloreaza cu culoarea stocata.
    Daca culoarea stocata este aceeasi cu cea de la pozitia data, nu se intampla nimic.
