#ifndef CUBETRANSTABLES_INCLUDED
#define CUBETRANSTABLES_INCLUDED

/******************************************************************************
* Header:  cubetranstables.h
*
* Purpose: Declarations of the transition tables for the cube.
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <array>

#include <cube.h>

/******************************************************************************
* Transition tables
******************************************************************************/
extern std::array<std::array<int, NUM_MOVES>, 2187>  cube_co_trans;
extern std::array<std::array<int, NUM_MOVES>, 2048>  cube_eo_trans;
extern std::array<std::array<int, NUM_MOVES>, 40320> cube_cp_trans;
extern std::array<std::array<int, NUM_MOVES>, 11880> cube_slice_sorted_trans;

extern std::array<std::array<int, NUM_MOVES>, 495>   cube_ud_pos_trans;
extern std::array<std::array<int, NUM_MOVES>, 24>    cube_ud_perm_trans;
extern std::array<std::array<int, NUM_MOVES>, 40320> cube_ep_trans;

/******************************************************************************
* Functions to populate the transition tables.
******************************************************************************/
void cube_populate_co_trans();
void cube_populate_eo_trans();
void cube_populate_cp_trans();
void cube_populate_slice_sorted_trans();

void cube_populate_ud_pos_trans();
void cube_populate_ud_perm_trans();
void cube_populate_ep_trans();

void cube_populate_all_trans_tables();

#endif
