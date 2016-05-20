#ifndef CUBEPHASE_INCLUDED
#define CUBEPHASE_INCLUDED

/******************************************************************************
* Header:  cubephase.h
*
* Purpose: Declarations of constants which determine the moves allowed in each
*          phase of the two-phase algorithm.
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <vector>

/******************************************************************************
* Allowed moves constant declarations
******************************************************************************/
extern std::vector<std::vector<int>> cube_p1_allowed_moves;
extern std::vector<std::vector<int>> cube_p2_allowed_moves;

/******************************************************************************
* Functions which populate the above vectors with the actual allowed moves
******************************************************************************/
void cube_create_p1_allowed_moves();
void cube_create_p2_allowed_moves();
void cube_create_allowed_moves();

#endif
