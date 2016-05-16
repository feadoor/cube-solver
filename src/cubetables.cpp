/******************************************************************************
* File:    cube.cpp
*
* Purpose: Builds transition and pruning tables for the two phases of the
*          Kociemba algorithm for solving the cube.
*******************************************************************************

/******************************************************************************
* Includes
******************************************************************************/
#include <array>
#include <deque>
#include <cube.h>
#include <cubetables.h>

/******************************************************************************
* Initial definitions of the transition and pruning tables
******************************************************************************/
std::array<std::array<int, 18>, 2187> cube_corner_orientation_trans;
std::array<std::array<int, 18>, 2048> cube_edge_orientation_trans;
std::array<std::array<int, 18>, 40320> cube_corner_permutation_trans;
std::array<std::array<int, 18>, 11880> cube_ud_sorted_trans;
std::array<std::array<int, 18>, 11880> cube_rl_sorted_trans;
std::array<std::array<int, 18>, 11880> cube_fb_sorted_trans;

std::array<std::array<int, 18>, 495> cube_ud_unsorted_trans;
std::array<std::array<int, 18>, 40320> cube_edge_permutation_trans;
std::array<std::array<int, 18>, 24> cube_ud_permutation_trans;

std::array<int, 4478976> cube_corner_orientation_edge_orientation_prune;
std::array<int, 1082565> cube_corner_orientation_ud_unsorted_prune;
std::array<int, 1013760> cube_edge_orientation_ud_unsorted_prune;
std::array<int, 967680> cube_corner_permutation_ud_permutation_prune;
std::array<int, 967680> cube_edge_permutation_ud_permutation_prune;

/******************************************************************************
* Implementation of functions which compute meta coordinates (a meta
* coordinate is a coordinate which is calculated from one or more normal 
* coordinates, whereas a normal coordinate is one which is calculated directly
* from the cube state).
******************************************************************************/

/******************************************************************************
* Function:  cube_coord_ud_unsorted
*
* Purpose:   Calculates the unsorted UD-slice coordinate from its sorted
*            counterpart.
*
* Params:    ud_sorted - the sorted UD-slice coordinate.
*
* Returns:   The value of the unsorted UD-slice coordinate.
*
* Operation: Calculates the result as ud_sorted / 24.
******************************************************************************/
int cube_coord_ud_unsorted(int cube_coord_ud_sorted);
{
    return ud_sorted / 24;
}

/******************************************************************************
* Function:  cube_coord_ud_permutation
*
* Purpose:   Calculates the phase 2 UD-slice edge permutation coordinate from
*            the sorted UD-slice coordinate.
*
* Params:    ud_sorted - the sorted UD-slice coordinate.
*
* Returns:   The value of the UD-slice permutation coordinate.
*
* Operation: Calculates the result as ud_sorted % 24.
******************************************************************************/
int cube_coord_ud_permutation(int cube_coord_ud_sorted);
{
    return ud_sorted % 24;
}

/******************************************************************************
* Function:  cube_coord_edge_permutation
*
* Purpose:   Calculates the phase 2 edge permutation coordinate from the sorted
*            RL-slice and FB-slice coordinates.
*
* Params:    rl_sorted - the sorted RL-slice coordinate.
*            fb_sorted - the sorted FB-slice coordinate.
*
* Returns:   The value of the edge permutation coordinate.
*
* Operation: This coordinate is defined as 24x + y, where x is equal to the
*            sorted RL-slice coordinate, and y is equal to the sorted FB-slice
*            coordinate taken modulo 24.
******************************************************************************/
int cube_coord_edge_permutation(int rl_sorted, int fb_sorted);
{
    return 24 * rl_sorted + (fb_sorted % 24);
}
