/******************************************************************************
* File:    cubetables.cpp
*
* Purpose: Builds transition and pruning tables for the two phases of the
*          Kociemba algorithm for solving the cube.
******************************************************************************/

/******************************************************************************
* Includes
******************************************************************************/
#include <cube.h>
#include <cubephase.h>
#include <cubeprune.h>
#include <cubetrans.h>
#include <cubetables.h>

/******************************************************************************
* Initial definitions of the transition tables
******************************************************************************/
CubeTrans cube_co_trans(PHASE_1, &Cube::coord_corner_orientation, 2187);
CubeTrans cube_eo_trans(PHASE_1, &Cube::coord_edge_orientation, 2048);
CubeTrans cube_cp_trans(PHASE_2, &Cube::coord_corner_permutation, 40320);
CubeTrans cube_ud_sorted_trans(PHASE_1, &Cube::coord_ud_sorted, 11880);
CubeTrans cube_rl_sorted_trans(PHASE_1, &Cube::coord_rl_sorted, 11880);
CubeTrans cube_fb_sorted_trans(PHASE_1, &Cube::coord_fb_sorted, 11880);
CubeTrans cube_ep_trans(PHASE_2, &Cube::coord_edge_permutation, 40320);
CubeTrans cube_ud_unsorted_trans(PHASE_1, &Cube::coord_ud_unsorted, 495);
CubeTrans cube_ud_perm_trans(PHASE_2, &Cube::coord_ud_permutation, 24);

/******************************************************************************
* Initial definitions of the pruning tables
******************************************************************************/
CubePrune cube_co_eo_prune(PHASE_1, &cube_co_trans, &cube_eo_trans);
CubePrune cube_co_ud_prune(PHASE_1, &cube_co_trans, &cube_ud_unsorted_trans);
CubePrune cube_eo_ud_prune(PHASE_1, &cube_eo_trans, &cube_ud_unsorted_trans);
CubePrune cube_ep_ud_prune(PHASE_2, &cube_ep_trans, &cube_ud_perm_trans);
CubePrune cube_cp_ud_prune(PHASE_2, &cube_cp_trans, &cube_ud_perm_trans);

/******************************************************************************
* Implementation of functions which populate the tables with data.
******************************************************************************/

/******************************************************************************
* Function:  cube_fill_all_trans_tables
*
* Purpose:   Populate all transition tables for the cube.
*
* Params:    None.
*
* Returns:   Nothing.
*
* Operation: Calls into each of the functions responsible for populating a
*            particular transition table.
******************************************************************************/
void cube_fill_all_trans_tables()
{
    cube_co_trans.fill();
    cube_eo_trans.fill();
    cube_cp_trans.fill();
    cube_ud_sorted_trans.fill();
    cube_rl_sorted_trans.fill();
    cube_fb_sorted_trans.fill();
    cube_ep_trans.fill();
    cube_ud_unsorted_trans.fill();
    cube_ud_perm_trans.fill();
}

/******************************************************************************
* Function:  cube_fill_all_pruning_tables
*
* Purpose:   Populate all pruning tables for the cube.
*
* Params:    None.
*
* Returns:   Nothing.
*
* Operation: Calls into each of the functions responsible for populating a
*            particular pruning table.
******************************************************************************/
void cube_fill_all_pruning_tables()
{
    cube_co_eo_prune.fill();
    cube_co_ud_prune.fill();
    cube_eo_ud_prune.fill();
    cube_ep_ud_prune.fill();
    cube_cp_ud_prune.fill();
}

int main()
{
    cube_create_allowed_moves();
    cube_fill_all_trans_tables();
    cube_fill_all_pruning_tables();
    cube_co_eo_prune.print();
    cube_co_ud_prune.print();
    cube_eo_ud_prune.print();
    cube_ep_ud_prune.print();
    cube_cp_ud_prune.print();
}