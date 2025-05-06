#include <math.h>

int main() {
    // L'operatore di assegnamento serve a scrivere un valore in una variabile
    int a = 10;
    a = a + 2;
    // Incremento e decremento hanno due notazioni abbreviate
    int b = a++; // Notazione prefissa (denota il valore pre-incremnto)
    int c = ++a; // Notazione postfissa (denota il valore post-incremento)
    // Alcuni operatori ammettono una notazione compatta quando sono combinati con l'operatore di assegnemto
    a += 2;
    a -= 2;
    // L'operatore di assegnemto è esso stesso una espressione
    int d = (a = 2*a);
    int e = a /= 2; 
    return 0;
}