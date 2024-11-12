//
// Created by flasque on 19/10/2024.
//

#include "moves.h"

/* prototypes of local functions */
/* local functions are used only in this file, as helper functions */

/**
 * @brief Function to rotate the robot according to a move and its actual orientation
 * @param ori : the actual orientation of the robot
 * @param move : the move to do
 * @return the new orientation of the robot
 */
t_orientation rotate(t_orientation, t_move );

/**
 * @brief function to translate the robot according to a move and its actual position
 * @param loc : the actual localisation of the robot
 * @param move : the move to do
 * @return the new localisation of the robot
 */
t_localisation translate(t_localisation , t_move);

/* definition of local functions */

t_orientation rotate(t_orientation ori, t_move move)
{
    int rst;
    rst = 0;
    switch (move)
    {
        case T_LEFT:
            rst=3;
            break;
        case T_RIGHT:
            rst=1;
            break;
        case U_TURN:
            rst=2;
            break;
        default:
            break;
    }
    return (ori+rst)%4;
}

t_localisation translate(t_localisation loc, t_move move)
{
    /** rules for coordinates:
     *  - x grows to the right with step of +1
     *  - y grows to the bottom with step of +1
     *  - the origin (x=0, y=0) is at the top left corner
     */
    t_position res = loc.pos;
    switch (move) {
        case F_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 1;
                    break;
                case EAST:
                    res.x = loc.pos.x + 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 1;
                    break;
                case WEST:
                    res.x = loc.pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 2;
                    break;
                case EAST:
                    res.x = loc.pos.x + 2;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 2;
                    break;
                case WEST:
                    res.x = loc.pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        case F_30:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 3;
                    break;
                case EAST:
                    res.x = loc.pos.x + 3;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 3;
                    break;
                case WEST:
                    res.x = loc.pos.x - 3;
                    break;
                default:
                    break;
            }
            break;
        case B_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y + 1;
                    break;
                case EAST:
                    res.x = loc.pos.x - 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y - 1;
                    break;
                case WEST:
                    res.x = loc.pos.x + 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
        return loc_init(res.x, res.y, loc.ori);

}

/* definitions of exported functions */


/*----------------------------------------------------------------------------------------------------------------------
                            FONCTION : getMoveAsString
Cette fonction convertit un mouvement (`t_move`) en une chaîne de caractères lisible.
Elle prend en paramètre :
  - `move` : le mouvement à convertir.
Elle renvoie une chaîne de caractères représentant le mouvement.
----------------------------------------------------------------------------------------------------------------------*/
char *getMoveAsString(t_move move)
{
    return _moves[move];
}


/*----------------------------------------------------------------------------------------------------------------------
                            FONCTION : move
Cette fonction effectue un mouvement complet en ajustant l'orientation et la position du robot selon le mouvement
demandé. Elle prend en paramètres :
  - `loc` : la localisation actuelle du robot.
  - `move` : le mouvement à effectuer.
Elle renvoie la nouvelle localisation après la rotation et la translation.
----------------------------------------------------------------------------------------------------------------------*/
t_localisation move(t_localisation loc, t_move move)
{
    t_localisation new_loc;
    new_loc.ori = rotate(loc.ori, move);
    loc.ori = new_loc.ori; //flasque est nul en C
    new_loc = translate(loc, move);
    return new_loc;
}


/*----------------------------------------------------------------------------------------------------------------------
                            FONCTION : updateLocalisation
Cette fonction met à jour la localisation du robot en modifiant directement l'emplacement pointé par `p_loc` en fonction
du mouvement spécifié `m`. Elle prend en paramètres :
  - `p_loc` : un pointeur vers la localisation actuelle du robot.
  - `m` : le mouvement à effectuer.
Elle ne renvoie rien ; la mise à jour est effectuée directement dans la structure pointée.
----------------------------------------------------------------------------------------------------------------------*/
void updateLocalisation(t_localisation *p_loc, t_move m)
{
    //printf("problem");
    *p_loc = move(*p_loc, m);
    return;
}
