//
// Created by vdela on 12/11/2024.
//

#include "arbre.h"
#include "utils.h"

#include <stdio.h>




node_t* create_node(int cost, t_move move) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        printf("Erreur\n");
        return NULL;
    }
    new_node->cost = cost;
    new_node->move = move;
    new_node->TL = 0;
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


void free_node(node_t* node) {
    if(node==NULL)
        return;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if(node->children[i]!=NULL)
            free_node(node->children[i]);
    }
    free(node);
}

/*
node_t* find_min(node_t* node) {
    node_t* min = node;
    int min_cost = min->cost;
    for (int i = 0; i < MAX_CHILDREN; i++)
        {
        if(node->children[i]!=NULL)
        {
            if(node->children[i]->cost<min_cost) {
                min = node->children[i];
                min_cost = node->cost;
            }
        }
    }
    return min;
}*/

int is_leaf(node_t* node){
    int val = 1;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->children[i] != NULL) {
            val = 0;
            break;
        }
    }
    return val;
}

//val : OUT
void find_smallest_Leaf(node_t *node, int *val) {
    if (node == NULL) {
        return;
    }

    if (is_leaf(node)) {
        if (node->cost < *val) {
            *val = node->cost;
        }
    } else {
        for (int i = 0; i < MAX_CHILDREN; i++) {
            find_smallest_Leaf(node->children[i], val);
        }
    }
}

void findMinPath(node_t* node, int* minCost, node_t** minNode, int path[], int* minPath, int level) {
    if (node == NULL) return;

    // Ajouter le mouvement courant au chemin
    path[level] = node->move;

    // Si le nœud est une feuille (n’a pas d’enfants)
    if (is_leaf(node)) {
        // Vérifier si cette feuille a un coût inférieur au coût minimal
        if (node->cost <= *minCost) {
            *minCost = node->cost;
            *minNode = node;
            // Copier le chemin courant vers le chemin minimal
            for (int i = 0; i <= level; i++) {
                minPath[i] = path[i];
            }
            minPath[level + 1] = -1; // Marquer la fin du chemin
        }
    }

    // Parcourir les enfants
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->children[i] != NULL) {
            findMinPath(node->children[i], minCost, minNode, path, minPath, level + 1);
        }
    }
}



arbre_t* create_arbre() {
    arbre_t* new_arbre = malloc(sizeof(arbre_t));
    if (new_arbre == NULL) {
        printf("Erreur\n");
        return NULL;
    }
    new_arbre->root=NULL;
    return new_arbre;
}

// example: t_move moves = [F_10, F_10, F_10, T_LEFT, T_RIGHT, B_10]
// int move_occ = [3,0,0,1,1,1,0]
void remplire_arbre(node_t* parent, int niveau, int move_occ[7], t_map map, t_localisation sim_MARC, int secoue){
    int **costs = map.costs;
    if (secoue == 0){
        if (niveau >= HAUTEUR_ARBRE) return;
    }else{
        if (niveau >= HAUTEUR_ARBRE - 1) return; //si robot secoue 4 mouvement seulement
    }

    int sum = 0;
    for (int i = 0; i < 7; i++){
        sum = sum + move_occ[i];
    }
    if (sum == 0) return;
    t_localisation Prochaine_Loc;

    int modified_occ[7];
    for (int i = 0; i < 7; i++){
        modified_occ[i] = move_occ[i];
    }

    /*
    int occ = 0;
    for (t_move move = 0; move < 7; move++){
        if (move_occ[move] != 0) {
            occ = move_occ[move];
            break;
        }
    }
    */
    //racine->children[racine->TL] = create_node(costs[y][x],mouvements[i]);
    for (int move_i = 0; move_i < 7; move_i++){ //loop over move_occ
        if (move_occ[move_i] <= 0){
            continue; //if its 0 just skip
        }
        for (int num_of_move = 0; num_of_move < move_occ[move_i]; num_of_move++) { //loop over occurence
            //check position valide
            if (isValidLocalisation(move(sim_MARC, move_i).pos, map.x_max, map.y_max) == 1) {
                Prochaine_Loc = move_sans_teleporter(sim_MARC, move_i, map);
            }else {
                continue;
            }
            //check current soil for erg martien
            if (map.soils[sim_MARC.pos.y][sim_MARC.pos.x] == 2){
                if (move_i == F_10 || move_i == B_10){
                    Prochaine_Loc = sim_MARC;
                }
                if (move_i == F_20){
                    //Prochaine_Loc = move(sim_MARC, F_10);
                    Prochaine_Loc = move_sans_teleporter(sim_MARC, F_10, map);
                }
                if (move_i == F_30){
                    //Prochaine_Loc = move(sim_MARC, F_20);
                    Prochaine_Loc = move_sans_teleporter(sim_MARC, F_20, map);
                }
                if (move_i == T_LEFT || move_i == T_RIGHT){
                    Prochaine_Loc = sim_MARC;
                }
                if (move_i == U_TURN){
                    //Prochaine_Loc = move(sim_MARC, T_RIGHT);
                    Prochaine_Loc = move_sans_teleporter(sim_MARC, T_RIGHT, map);
                }
            }
            //check current soil reg martien
            if (map.soils[sim_MARC.pos.y][sim_MARC.pos.x] == 3 && secoue == 0){
                printf("robot secoué\n");
                //niveau++; //erreur là
                secoue = 1;
            }
            //check current soil crevasse
            if (map.soils[sim_MARC.pos.y][sim_MARC.pos.x] == 4 ){
                continue;
            }
            //printf("%d", costs[Prochaine_Loc.pos.y][Prochaine_Loc.pos.x]);
            node_t* child = create_node(costs[Prochaine_Loc.pos.y][Prochaine_Loc.pos.x], move_i);

            //printf("%d\n", parent->TL);
            if(parent == 0x55555555ca10){
                printf("\t%d\n");
            }
            parent->children[parent->TL++] = child;
            modified_occ[move_i] = modified_occ[move_i] - 1;
            remplire_arbre(child, niveau + 1, modified_occ, map,  Prochaine_Loc, secoue);
            modified_occ[move_i] = modified_occ[move_i] + 1;
        }
    }
}


void free_arbre(arbre_t* arbre) {

    if (arbre == NULL)
        return;
    free_node(arbre->root);
    free(arbre);
}
