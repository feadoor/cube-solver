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
#include <cube.h>
#include <cubetrans.h>

/******************************************************************************
* Transition tables
******************************************************************************/
extern CubeTrans cube_co_trans;
extern CubeTrans cube_eo_trans;
extern CubeTrans cube_cp_trans;
extern CubeTrans cube_ud_sorted_trans;
extern CubeTrans cube_rl_sorted_trans;
extern CubeTrans cube_fb_sorted_trans;
extern CubeTrans cube_ep_trans;
extern CubeTrans cube_ud_unsorted_trans;
extern CubeTrans cube_ud_perm_trans;

/******************************************************************************
* Pruning tables
******************************************************************************/
extern CubePrune cube_co_eo_prune;
extern CubePrune cube_co_ud_prune;
extern CubePrune cube_eo_ud_prune;
extern CubePrune cube_ep_ud_prune;
extern CubePrune cube_cp_ud_prune;

/******************************************************************************
* Functions to populate the tables.
******************************************************************************/
void cube_fill_all_trans_tables();
void cube_fill_all_pruning_tables();

#endif
