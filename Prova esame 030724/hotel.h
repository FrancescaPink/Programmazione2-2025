/**
 * @file hotel.h
 * @brief Dichiarazione della struttura `tipo_inf` e della funzione `copy`.
 */

#ifndef HOTEL_H
#define HOTEL_H

struct tipo_inf {
    int stelle;
    char nome[20];
    char luogo[20];
} ;

void copy(tipo_inf& dest, const tipo_inf& src);

#endif
