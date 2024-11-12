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

node_t* create_node(int cost, t_move move);

int add_node(node_t* node, node_t* child);

void free_node(node_t* node);

int is_leaf(node_t* node);

void find_smallest_Leaf(node_t *node, int *val);

void findMinPath(node_t* node, int* minCost, node_t** minNode, int path[], int* minPath, int level);

arbre_t* create_arbre();

void free_arbre(arbre_t* arbre);





#endif //ARBRE_H
