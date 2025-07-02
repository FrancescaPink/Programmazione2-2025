/**
 * @file hotel.cc
 * @brief Implementazione delle funzioni per la gestione degli hotel
 * @details Contiene la definizione della struttura `tipo_inf` e la funzione `copy` per copiare le informazioni tra due strutture `tipo_inf`.
 * @author Francesca
 */

#include "hotel.h"
#include <cstring>

/**
 * @brief Copia le informazioni da una struttura `tipo_inf` a un'altra.
 * @param dest La struttura di destinazione in cui copiare le informazioni.
 * @param src La struttura di origine da cui copiare le informazioni.
 * @details Copia il numero di stelle, il nome e il luogo dalla struttura `src` alla struttura `dest`.
 */
void copy(tipo_inf& dest, const tipo_inf& src) {
    dest.stelle = src.stelle;
    strcpy(dest.nome, src.nome);
    strcpy(dest.luogo, src.luogo);
}
