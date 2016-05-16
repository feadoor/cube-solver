#ifndef CUBETABLES_INCLUDED
#define CUBETABLES_INCLUDED

/******************************************************************************
* Header:  cubetables.h
*
* Purpose: Declarations of the transition and pruning tables for the cube.
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <array>

/******************************************************************************
* Functions to compute meta coordinates (a meta coordinate is a coordinate
* which is calculated from one or more normal coordinates, whereas a normal
* coordinate is one which is calculated directly from the cube state).
******************************************************************************/
int cube_coord_ud_unsorted     (int ud_sorted);
int cube_coord_ud_permutation  (int ud_sorted);
int cube_coord_edge_permutation(int rl_sorted, int fb_sorted);

/******************************************************************************
* Normal coordinate transition tables
******************************************************************************/
extern std::array<std::array<int, 18>, 2187> cube_corner_orientation_trans;
extern std::array<std::array<int, 18>, 2048> cube_edge_orientation_trans;
extern std::array<std::array<int, 18>, 40320> cube_corner_permutation_trans;
extern std::array<std::array<int, 18>, 11880> cube_ud_sorted_trans;
extern std::array<std::array<int, 18>, 11880> cube_rl_sorted_trans;
extern std::array<std::array<int, 18>, 11880> cube_fb_sorted_trans;

/******************************************************************************
* Meta coordinate transition tables
******************************************************************************/
extern std::array<std::array<int, 18>, 495> cube_ud_unsorted_trans;
extern std::array<std::array<int, 18>, 40320> cube_edge_permutation_trans;
extern std::array<std::array<int, 18>, 24> cube_ud_permutation_trans;

/******************************************************************************
* Pruning tables for combinations of the above coordinates
******************************************************************************/
extern std::array<int, 4478976> cube_corner_orientation_edge_orientation_prune;
extern std::array<int, 1082565> cube_corner_orientation_ud_unsorted_prune;
extern std::array<int, 1013760> cube_edge_orientation_ud_unsorted_prune;
extern std::array<int, 967680> cube_corner_permutation_ud_permutation_prune;
extern std::array<int, 967680> cube_edge_permutation_ud_permutation_prune;

/******************************************************************************
* Functions to populate the transition and pruning tables.
******************************************************************************/
void cube_populate_corner_orientation_trans();
void cube_populate_edge_orientation_trans();
void cube_populate_corner_permutation_trans();
void cube_populate_ud_sorted_trans();
void cube_populate_rl_sorted_trans();
void cube_populate_fb_sorted_trans();

void cube_populate_ud_unsorted_trans();
void cube_populate_edge_permutation_trans();
void cube_populate_ud_permutation_trans();

void cube_populate_corner_orientation_edge_orientation_prune();
void cube_populate_corner_orientation_ud_unsorted_prune();
void cube_populate_edge_orientation_ud_unsorted_prune();
void cube_populate_corner_permutation_ud_permutation_prune();
void cube_populate_edge_permutation_ud_permutation_prune();

void cube_populate_all_tables();

#endif
