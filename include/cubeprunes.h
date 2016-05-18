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
extern std::vector<int> p1_moves;
extern std::vector<int> p2_moves;

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
void cube_phase1_prune(const transtable &trans1, const transtable &trans2, 
                       int start1, int start2, prunetable &prune);
void cube_phase2_prune(const transtable &trans1, const transtable &trans2, 
                       int start1, int start2, prunetable &prune);
void cube_all_prune();

#endif
