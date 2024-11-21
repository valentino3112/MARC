#include <stdio.h>
#include "map.h"
#include "loc.h"
#include "moves.h"
#include "arbre.h"
#include "utils.h"


int main() {
    t_map map;
    //Creation de notre robot
    t_localisation MARC;
    MARC = loc_init(0, 0, EAST); //Position initial

    printf("Coordonnées du robot: x: %d, y: %d\n",MARC.pos.x, MARC.pos.y);
    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\training.map");
#else
    map = createMapFromFile("../maps/training.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    printf("\nDisplay cost:\n");
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    printf("\nDisplay map:\n");
    displayMap(map);

    printf("Coordonnées du robot: x: %d, y: %d\n", MARC.pos.x, MARC.pos.y);
    printf("Orientation du robot: x: %d\n", MARC.ori);
    /*
    int flipflop = 0;
    for (int i = 0; i < map.y_max - 1; i++)
    {
        for (int j = 0; j < map.x_max - 1; j++)
        {
            move_marc(&MARC, F_10);

        }
        if (flipflop == 0) {
            move_marc(&MARC, T_RIGHT);
            move_marc(&MARC, F_10);
            move_marc(&MARC, T_RIGHT);
            flipflop = 1;
        }
        else {
            move_marc(&MARC, T_LEFT);
            move_marc(&MARC, F_10);
            move_marc(&MARC, T_LEFT);
            flipflop = 0;
        }

    }
    move_marc(&MARC, U_TURN);
    move_marc(&MARC, U_TURN);
    printf("Coordonnées du robot: x: %d, y: %d\n", MARC.pos.x, MARC.pos.y);
    printf("Orientation du robot: x: %d\n", MARC.ori);
    printf("cost %d", map.costs[0][4] );
    */
    printf("----TESTE MOUVEMENT ALEATOIRE ROBOT----\n");
    MARC = loc_init(5, 5, EAST);
    t_move result[9];

    // Phase test
    tirage_aleatoire(result);
    printf("Coordonnées du robot: x: %d, y: %d\n", MARC.pos.x, MARC.pos.y);
    printf("Orientation du robot: x: %d\n", MARC.ori);
    for(int i = 0; i < 9; i++){
        printMove(result[i]);
        printf("\n");
        move_marc(&MARC, result[i]);
        printf("Coordonnées du robot: x: %d, y: %d\n", MARC.pos.x, MARC.pos.y);
        printf("Orientation du robot: x: %d\n", MARC.ori);
    }
    printf("---FIN DU TESTE MOUVEMENT ALEATOIRE ROBOT----\n");



    return 0;
}
