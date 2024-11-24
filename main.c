#include <stdio.h>
#include "map.h"
#include "loc.h"
#include "moves.h"
#include "arbre.h"
#include "utils.h"
#include "time_calcul.h"
//test
void to_occ(int move_occ[7], t_move result[9]){
    for (int i = 0; i < 9; i++){
        move_occ[result[i]] = move_occ[result[i]] + 1;
    }
}


void printTree(node_t* node, int level) {
    if (!node) return;

    // Print the current node with indentation
    for (int i = 0; i < level; i++) printf("  "); // Indentation for the current level
    printf("Cost: %d, Move: ", node->cost);
    printMove(node->move);
    printf(", TL: %d\n", node->TL);

    // Recursively print each child
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->children[i]) {
            printTree(node->children[i], level + 1);
        }
    }
}

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
    map = createMapFromFile("..\\maps\\example2.map");
#else
    map = createMapFromFile("../maps/example1.map");
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
    int miau[7] = {0,0,0,0,0,0,0};
    tirage_aleatoire(result);
    to_occ(miau, result);

    printf("Coordonnées du robot: x: %d, y: %d\n", MARC.pos.x, MARC.pos.y);
    printf("Orientation du robot: x: %d\n", MARC.ori);
    for(int i = 0; i < 9; i++){
        printMove(result[i]);
        printf("\n");
        move_marc(&MARC, result[i]);
        printf("Coordonnées du robot: x: %d, y: %d\n", MARC.pos.x, MARC.pos.y);
        printf("Orientation du robot: x: %d\n", MARC.ori);
    }
    for(int i = 0; i < 7; i++){
        printf("%d,", miau[i]);
    }
    printf("---FIN DU TESTE MOUVEMENT ALEATOIRE ROBOT----\n");

    printf("---TESTE ARBRE ----\n");
    MARC = loc_init(0, 0, EAST);
    arbre_t* test = create_arbre();
    int move_occ[7] = {2,2,0,0,1,2,2};
    node_t* racine = create_node(map.costs[MARC.pos.y][MARC.pos.x],999);
    test->root = racine;


    remplire_arbre(racine, 0, &move_occ, map, MARC, 0);


    printTree(racine,0);
    printf("---FIN TESTE ARBRE ----\n\n\n");


    printf("---TESTE TEMPS DE CALCUL ----\n");
    //double temps = calculer_temps_construction_arbre(racine, move_occ, map, MARC);
    double temps = 0;
    printf("Temps de construction de l'arbre: %f\n", temps);
    printf("---FIN TESTE TEMPS DE CALCUL ----\n\n\n");


    //test de la fonction find_smallest_Leaf
    printf("---TESTE FONCTION find_smallest_Leaf ----\n");
    int val = 9999;
    find_smallest_Leaf(racine, &val);
    printf("Valeur minimal de la feuille: %d\n", val);
    //tmep de recherche de la feuille minimal
    double temps_recherche = calculer_temps_recherche_feuille_min(racine);
    printf("Temps de recherche de la feuille minimal: %f\n", temps_recherche);

    printf("---FIN TESTE FONCTION find_smallest_Leaf ----\n\n\n");


    //test de la fonction findMinPath
    printf("---TESTE FONCTION findMinPath ----\n");
    int minCost = val;
    node_t* minNode = NULL;
    int path[HAUTEUR_ARBRE];
    int minPath[HAUTEUR_ARBRE];
    findMinPath(racine, &minCost, &minNode, path, minPath, 0);
    printf("Chemin minimal: ");
    for (int i = 0; i < HAUTEUR_ARBRE; i++) {
        if (minPath[i] == -1) break;
        printMove(minPath[i]);
        printf(" -> ");
    }
    printf("\n");
    printf("Temps de recherche du chemin minimal: %f\n", calculer_chemin_racine_vers_feuille(racine, minNode, path, minPath));
    printf("---FIN TESTE FONCTION findMinPath ----\n");



    return 0;
}


int menu() {
    int QUIT = 0;
    while(QUIT==0) {
        printf("---MENU DE MARC ----\n");
        printf("Quelle carte voulez-vous utiliser ?\n");
        int carte=-1;
        while (carte<=1 || carte>5) {
            printf("Entrez le nombre de 1 à 5 correspondant à la carte\n");
            scanf("%d", &carte);
        }
        printf("Parmis combien de mouvement voulez-vous faire choisir le rover ?\n");
        int nbchoix=-1;
        while (nbchoix<=1) {
            printf("Entrez un suppérieur à 1\n");
            scanf("%d", &nbchoix);
        }
        t_map map;
        //Creation de notre robot
        t_localisation MARC;
        MARC = loc_init(0, 0, EAST); //Position initial
        printf("Coordonnées du robot: x: %d, y: %d\n",MARC.pos.x, MARC.pos.y);
        switch (carte) {
            case 1:
                #if defined(_WIN32) || defined(_WIN64)
                    map = createMapFromFile("..\\maps\\example1.map");
                #else
                    map = createMapFromFile("../maps/example1.map");
                #endif
            break;
            case 2:
                #if defined(_WIN32) || defined(_WIN64)
                    map = createMapFromFile("..\\maps\\example2.map");
                #else
                    map = createMapFromFile("../maps/example2.map");
                #endif
            break;
            case 3:
                #if defined(_WIN32) || defined(_WIN64)
                    map = createMapFromFile("..\\maps\\example3.map");
                #else
                    map = createMapFromFile("../maps/example3.map");
                #endif
            break;
            case 4:
                #if defined(_WIN32) || defined(_WIN64)
                    map = createMapFromFile("..\\maps\\example4.map");
                #else
                    map = createMapFromFile("../maps/example4.map");
                #endif
            break;
            case 5:
                #if defined(_WIN32) || defined(_WIN64)
                    map = createMapFromFile("..\\maps\\example5.map");
                #else
                    map = createMapFromFile("../maps/example5.map");
                #endif
            break;
        }
        displayMap(map);
    }
}*/