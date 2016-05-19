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
#include <cubetrans.h>
#include <cubetables.h>

/******************************************************************************
* Initial definitions of the transition tables
******************************************************************************/
CubeTrans cube_co_trans(&Cube::coord_corner_orientation, 2187);
CubeTrans cube_eo_trans(&Cube::coord_edge_orientation, 2187);
CubeTrans cube_cp_trans(&Cube::coord_corner_permutation, 40320);
CubeTrans cube_ud_sorted_trans(&Cube::coord_ud_sorted, 11880);
CubeTrans cube_rl_sorted_trans(&Cube::coord_rl_sorted, 11880);
CubeTrans cube_fb_sorted_trans(&Cube::coord_fb_sorted, 11880);

/******************************************************************************
* Implementation of functions which populate the transition tables for each
* coordinate.
******************************************************************************/

/******************************************************************************
* Function:  cube_populate_all_trans_tables
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
}

int main()
{
    cube_fill_all_trans_tables();
    return 0;
}
