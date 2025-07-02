#include <iostream>
using namespace std;

#include "tipo.h"

int compare(tipo_inf a, tipo_inf b) {
    if (a.valore > b.valore) 
        return 1;
    else if (a.valore < b.valore)
        return -1;
    else
        return 0;
}
void copy(tipo_inf& a,tipo_inf b) {}
    

void print(tipo_inf e) {
    cout<<e.valore<< " " <<e.seme;
}
