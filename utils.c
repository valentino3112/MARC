//
// Created by dnum on 21/11/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "map.h"
#include "arbre.h"

#define ARRAY_SIZE 100
#define NUM_REMOVALS 9

void printMove(t_move move) {
    switch (move) {
        case F_10: printf("F_10"); break;
        case F_20: printf("F_20"); break;
        case F_30: printf("F_30"); break;
        case B_10: printf("B_10"); break;
        case T_LEFT: printf("T_LEFT"); break;
        case T_RIGHT: printf("T_RIGHT"); break;
        case U_TURN: printf("U_TURN"); break;
        default: printf("POSITION_INITIALE");
    }
}

// Function to initialize the array with specified frequencies
void initializeArray(t_move array[]) {
    int i = 0;

    // Fill array with the specified frequencies
    for (int j = 0; j < 22; j++) array[i++] = F_10;
    for (int j = 0; j < 15; j++) array[i++] = F_20;
    for (int j = 0; j < 7; j++) array[i++] = F_30;
    for (int j = 0; j < 7; j++) array[i++] = B_10;
    for (int j = 0; j < 21; j++) array[i++] = T_LEFT;
    for (int j = 0; j < 21; j++) array[i++] = T_RIGHT;
    for (int j = 0; j < 7; j++) array[i++] = U_TURN;
}

// Function to remove an element from the array
void removeElement(t_move array[], int *size, int index) {
    for (int i = index; i < (*size) - 1; i++) {
        array[i] = array[i + 1];
    }
    (*size)--;
}

// Function to perform 9 random removals and return the result
void tirage_aleatoire(t_move result[]) {
    t_move array[ARRAY_SIZE];
    int size = ARRAY_SIZE;

    // Initialize the array with moves
    initializeArray(array);


    // Seed the random number generator
    srand(time(NULL));

    // Select 9 random moves
    for (int i = 0; i < NUM_REMOVALS; i++) {
        int index = rand() % size;  // Random index
        result[i] = array[index];  // Store the selected move
        removeElement(array, &size, index);  // Remove the move from the array
    }

}

void move_marc(t_localisation* MARC, t_move da_move, t_map map, int* secoue) {

    t_localisation Prochaine_Loc;
    Prochaine_Loc = move(*MARC, da_move);

    //check position valide
    if (isValidLocalisation(move(*MARC, da_move).pos, map.x_max, map.y_max) == 1) {
        Prochaine_Loc = move(*MARC, da_move);
    }else {
        return;
    }
    //check current soil for erg martien
    if (map.soils[MARC->pos.y][MARC->pos.x] == 2){
        if (da_move == F_10 || da_move == B_10){
            Prochaine_Loc = *MARC;
        }
        if (da_move == F_20){
            Prochaine_Loc = move(*MARC, F_10);
        }
        if (da_move == F_30){
            Prochaine_Loc = move(*MARC, F_20);
        }
        if (da_move == T_LEFT || da_move == T_RIGHT){
            Prochaine_Loc = *MARC;
        }
        if (da_move == U_TURN){
            Prochaine_Loc = move(*MARC, T_RIGHT);
        }
    }
    //check current soil reg martien
    if (map.soils[MARC->pos.y][MARC->pos.x] == 3 && secoue == 0){
        printf("robot secoué\n");
        secoue = 1;
    }
    if (map.soils[MARC->pos.y][MARC->pos.x] == 4){
        printf("FUCKAODAZOKDAZOKD");
        return;
    }

    *MARC = Prochaine_Loc;
}

t_localisation move_sans_teleporter(t_localisation loc, t_move da_move, t_map map)
{
    t_localisation current_loc;
    t_localisation current_loc_one;
    t_localisation current_loc_two;
    t_localisation current_loc_three;

    current_loc = loc;
    current_loc_one = move(current_loc, F_10);
    current_loc_two = move(current_loc_one, F_10);
    current_loc_three = move(current_loc_two, F_10);
    if (da_move == F_10){
        if (map.soils[current_loc.pos.y][current_loc.pos.x] == 4){
            return current_loc;
        }
        if (map.soils[current_loc_one.pos.y][current_loc_one.pos.x] == 4){
            return current_loc_one;
        }
    }
    if (da_move == F_20){
        if (map.soils[current_loc.pos.y][current_loc.pos.x] == 4){
            return current_loc;
        }
        if (map.soils[current_loc_one.pos.y][current_loc_one.pos.x] == 4){
            return current_loc_one;
        }
        if (map.soils[current_loc_two.pos.y][current_loc_two.pos.x] == 4){
            return current_loc_two;
        }
    }
    if (da_move == F_30){
        if (map.soils[current_loc.pos.y][current_loc.pos.x] == 4){
            return current_loc;
        }
        if (map.soils[current_loc_one.pos.y][current_loc_one.pos.x] == 4){
            return current_loc_one;
        }
        if (map.soils[current_loc_two.pos.y][current_loc_two.pos.x] == 4){
            return current_loc_two;
        }
        if (map.soils[current_loc_three.pos.y][current_loc_three.pos.x] == 4){
            return current_loc_three;
        }
    }
    return move(current_loc, da_move);
}
void to_occ(int move_occ[7], t_move result[9]){
    for (int i = 0; i < 9; i++){
        move_occ[result[i]] = move_occ[result[i]] + 1;
    }
}
int verif_base(t_map *map, const int *minPath, t_localisation* vrai_marc) {//verification si le robot trouve bien la base


    int secoue = 0;
    for (int i = 1; i < HAUTEUR_ARBRE+1; i++){
        move_marc(vrai_marc, minPath[i], (*map), &secoue);
        printf("coord x: %d, y: %d\n", vrai_marc->pos.x, vrai_marc->pos.y);
    }
    printf("Coordonnées du robot: x: %d, y: %d\n",vrai_marc->pos.x, vrai_marc->pos.y);
    if ((*map).costs[vrai_marc->pos.y][vrai_marc->pos.x] == 0){
        printf("le robot à trouvé la base\n");
    }else{
        printf("le robot ne trouve pas la base\n");
    }

    printf("cost: %d\n", (*map).costs[vrai_marc->pos.y][vrai_marc->pos.x]);
}