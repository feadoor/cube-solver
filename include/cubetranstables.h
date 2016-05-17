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
#include <vector>

#include <cube.h>

/******************************************************************************
* Transition tables
******************************************************************************/
typedef std::vector<std::vector<int>> transtable;

extern transtable cube_co_trans;
extern transtable cube_eo_trans;
extern transtable cube_cp_trans;
extern transtable cube_slice_sorted_trans;

extern transtable cube_ud_pos_trans;
extern transtable cube_ud_perm_trans;
extern transtable cube_ep_trans;

/******************************************************************************
* Coordinates representing the solved position for each transition table
******************************************************************************/
extern int cube_co_trans_solved;
extern int cube_eo_trans_solved;
extern int cube_cp_trans_solved;
extern int cube_slice_sorted_trans_solved;

extern int cube_ud_pos_trans_solved;
extern int cube_ud_perm_trans_solved;
extern int cube_ep_trans_solved;

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
