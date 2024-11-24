//
// Created by dnum on 21/11/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"


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
    /*
    for (int i = 0; i < size; i++) {
        printMove(array[i]);
        printf("  %d\n",i);
    }
    */
}

void move_marc(t_localisation* MARC, t_move da_move) {
    //TODO: remove magic number 11,11 to map.x_max, map.y_max
    t_localisation Prochaine_Loc;
    Prochaine_Loc = move(*MARC, da_move);
    //printf("Prochaine coordonn�es du robot: x: %d, y: %d\n", Prochaine_Loc.pos.x, Prochaine_Loc.pos.y);
    //printf("Prochaine Orientation du robot: x: %d\n", Prochaine_Loc.ori);
    if (isValidLocalisation(Prochaine_Loc.pos, 11, 11) == 1) {
        //printf("Prochaine coordonn�es valide\n");
        updateLocalisation(MARC, da_move);
    }
    else {
        printf("move non valide %d %d\n", Prochaine_Loc.pos.x, Prochaine_Loc.pos.y);
    }
}
