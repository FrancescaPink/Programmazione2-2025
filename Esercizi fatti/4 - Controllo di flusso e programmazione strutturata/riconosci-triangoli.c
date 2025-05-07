//Dati tre valori a ≦ b ≦ c che rappresentano le lunghezze di tre segmenti, valutare se possono essere i tre lati di un triangolo, 
//e se sì deciderne il tipo (scaleno, isoscele, equilatero). Per avere un triangolo deve valere: c < (a+b)
//Rappresentazione delle informazioni:
// • la variabile booleana "triangolo" indica se i tre segmenti possono costituire un triangolo
// • le variabili booleane scaleno, isoscele e equil indicano il tipo di triangolo

#include <stdio.h>
#include <stdbool.h>

int main () {
    int a, b, c;
    bool triangolo, scaleno, isoscele, equil;
    printf("Inserisci i tre lati del triangolo: ");
    scanf("%d %d %d", &a, &b, &c);
    triangolo = (c < (a + b));
    switch (triangolo) {
        case true:
            if (a == b && b == c) {
                equil = true;
                isoscele = false;
                scaleno = false;
            } else if (a == b || b == c || a == c) {
                equil = false;
                isoscele = true;
                scaleno = false;
            } else {
                equil = false;
                isoscele = false;
                scaleno = true;
            }
            break;
        case false:
            printf("I tre lati non possono formare un triangolo.\n");
            return 0;
    }
    if (equil) {
        printf("Il triangolo è equilatero.\n");
    } else if (isoscele) {
        printf("Il triangolo è isoscele.\n");
    } else if (scaleno) {
        printf("Il triangolo è scaleno.\n");
    }
}