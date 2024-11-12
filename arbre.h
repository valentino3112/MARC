//
// Created by vdela on 12/11/2024.
//

#ifndef ARBRE_H
#define ARBRE_H
#include "moves.h"
#define MAX_CHILDREN 9
#include <stdlib.h>

typedef struct node_s {
    int cost;
    t_move move;
    struct node_s* children[MAX_CHILDREN];
}node_t;

typedef struct arbre_s {
    node_t* root;
} arbre_t;


#endif //ARBRE_H
