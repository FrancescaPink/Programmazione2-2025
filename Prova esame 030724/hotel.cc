#include "hotel.h"
#include <cstring>

void copy(tipo_inf& dest, const tipo_inf& src) {
    dest.stelle = src.stelle;
    strcpy(dest.nome, src.nome);
    strcpy(dest.luogo, src.luogo);
}
