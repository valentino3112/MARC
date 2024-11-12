//
// Created by vdela on 12/11/2024.
//

#include "arbre.h"

#include <stdio.h>

node_t* create_node(int cost, t_move move) {
    node_t* new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        printf("Erreur\n");
        return NULL;
    }
    new_node->cost = cost;
    new_node->move = move;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        new_node->children[i] = NULL;
    }
    return new_node;
}


int add_node(node_t* node, node_t* child){
    if(node->children[8]==NULL)
        return 0;
    int cpt=0;
    while(node->children[cpt]!=NULL) {
    cpt++;
    }
    node->children[cpt]=child;
    return 1;

}