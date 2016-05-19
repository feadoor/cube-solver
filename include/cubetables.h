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

/******************************************************************************
* Functions to populate the transition tables.
******************************************************************************/
void cube_fill_all_trans_tables();

#endif
