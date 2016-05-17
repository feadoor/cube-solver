#ifndef CUBEPRUNES_INCLUDED
#define CUBEPRUNES_INCLUDED

/******************************************************************************
* Header:  cubeprunes.h
*
* Purpose: Declarations of the pruning tables for the cube.
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <vector>

#include <cube.h>
#include <cubetranstables.h>

/******************************************************************************
* Constants
******************************************************************************/
std::vector<int> p1_moves = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L, MOVE_L2, 
                             MOVE_LP, MOVE_F, MOVE_F2, MOVE_FP, MOVE_R, 
                             MOVE_R2, MOVE_RP, MOVE_B, MOVE_B2, MOVE_BP, 
                             MOVE_D, MOVE_D2, MOVE_DP};
std::vector<int> p2_moves = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L2, MOVE_F2, 
                             MOVE_R2, MOVE_B2, MOVE_D, MOVE_D2, MOVE_DP};

/******************************************************************************
* Pruning tables
******************************************************************************/
typedef std::vector<std::vector<int>> prunetable;

extern prunetable cube_co_eo_prune;
extern prunetable cube_co_ud_prune;
extern prunetable cube_eo_ud_prune;

extern prunetable cube_ep_ud_prune;
extern prunetable cube_cp_ud_prune;

/******************************************************************************
* Functions to populate the pruning tables.
******************************************************************************/
void cube_phase1_prune(transtable trans1, transtable trans2, 
                       int start1, int start2, prunetable prune);
void cube_phase2_prune(transtable trans1, transtable trans2, 
                       int start1, int start2, prunetable prune);
void cube_all_prune();

#endif
