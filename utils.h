//
// Created by dnum on 21/11/24.
//

#ifndef UNTITLED1_UTILS_H
#define UNTITLED1_UTILS_H

#include "loc.h"
#include "moves.h"
#include "map.h"


void printMove(t_move move);
void initializeArray(t_move array[]);
void removeElement(t_move array[], int *size, int index);
void move_marc(t_localisation* MARC, t_move da_move, t_map map, int* secoue);
void tirage_aleatoire(t_move result[]);

#endif //UNTITLED1_UTILS_H
