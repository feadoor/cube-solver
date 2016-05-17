/******************************************************************************
* File:    cubetranstables.cpp
*
* Purpose: Builds transition tables for the two phases of the Kociemba
*          algorithm for solving the cube.
******************************************************************************/

/******************************************************************************
* This file contains code which initialises the transition tables for the
* coordinates used in the two-phase algorithm. A description of each of the
* coordinates is provided here for reference.
*
* Corner orientation   - This coordinate is a number in the range 0..2186 which
*                        describes the orientation of the 8 corners of the cube.
*
* Edge orientation     - This coordinate is a number in the range 0..2047 which
*                        describes the orientation of the 12 edges of the cube.
*
* Corner permutation   - This coordinate is a number in the range 0..40319 
*                        which describes the permutation of the 8 corners of
*                        the cube.
*
* Sorted UD-slice      - This coordinate is a number in the range 0..11879 
*                        which describes the positions (order matters) of the 4
*                        edges belonging in the UD slice.
*
* Sorted RL-slice      - This coordinate is a number in the range 0..11879 
*                        which describes the positions (order matters) of the 4
*                        edges belonging in the RL slice.
*
* Sorted FB-slice      - This coordinate is a number in the range 0..11879 
*                        which describes the positions (order matters) of the 4
*                        edges belonging in the FB slice.
*
* Unsorted UD-slice    - This coordinate is a number in the range 0..494 
*                        which describes the positions (order doesn't matter) 
*                        of the 4 edges belonging in the UD slice. It is
*                        calculated as (UD-slice sorted) / 24.
*
* UD-slice permutation - This coordinate is a number in the range 0..23 which
*                        describes the permutation of the four UD-slice edges
*                        within the UD-slice. This coordinate is only used when
*                        the UD-slice edges are all actually in the UD-slice.
*                        It is calculated as (UD-slice sorted) % 24.
*
* Edge permutation     - This coordinate is a number in the range 0..40319
*                        which describes the permutation of the 8 edges from
*                        the U and D layers amongst themselves. This coordinate
*                        is only used when these 8 edges are all located in the
*                        U and D layers. It is calculated as 24 * x + y, where
*                        x is the sorted RL-slice and y is the sorted FB-slice.
******************************************************************************/

/******************************************************************************
* Includes
******************************************************************************/
#include <algorithm>
#include <iostream>
#include <vector>

#include <cube.h>
#include <cubetranstables.h>

/******************************************************************************
* Initial definitions of the transition tables
******************************************************************************/
transtable cube_co_trans(2187, std::vector<int>(NUM_MOVES, 0));
transtable cube_eo_trans(2048, std::vector<int>(NUM_MOVES, 0));
transtable cube_cp_trans(40320, std::vector<int>(NUM_MOVES, 0));
transtable cube_slice_sorted_trans(11880, std::vector<int>(NUM_MOVES, 0));

transtable cube_ud_pos_trans(495, std::vector<int>(NUM_MOVES, 0));
transtable cube_ud_perm_trans(24, std::vector<int>(NUM_MOVES, 0));
transtable cube_ep_trans(40320, std::vector<int>(NUM_MOVES, 0));

int cube_co_trans_solved = 0;
int cube_eo_trans_solved = 0;
int cube_cp_trans_solved = 0;
int cube_slice_sorted_trans_solved = 0;

int cube_ud_pos_trans_solved = 0;
int cube_ud_perm_trans_solved = 0;
int cube_ep_trans_solved = 0;

/******************************************************************************
* Implementation of functions which populate the transition tables for each
* coordinate used in the two-phase algorithm
******************************************************************************/

/******************************************************************************
* Function:  cube_populate_co_trans
*
* Purpose:   Populate the corner orientation transition table.
*
* Params:    None
*
* Returns:   Nothing
*
* Operation: For each possible orientation of corners, construct a cube with
*            that corner orientation, and record the effect of each possible
*            move on the orientation of the corners.
******************************************************************************/
void cube_populate_co_trans()
{
    // Some vectors to hold permutation and orientation info from which we can
    // instantiate a Cube object.
    std::vector<int> corner_perm, corner_orient, edge_perm, edge_orient;
    corner_perm   = {0, 1, 2, 3, 4, 5, 6, 7};
    corner_orient = {0, 0, 0, 0, 0, 0, 0, 0};
    edge_perm     = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    edge_orient   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0};

    // Local variables
    int from, to;
    int move;

    // Step through each possible corner orientation. The orientations consist 
    // of a sequence of 8 numbers taking values between 0 and 2 inclusive, 
    // which can be considered as a single integer by reading in ternary. The 
    // final entry in the sequence is determined from the others by the fact
    // that their sum must be 0 (modulo 3).
    for (int orient = 0; orient < cube_co_trans.size(); ++orient)
    {
        int orient_copy = orient;
        int total_orientation = 0;
        for (int ii = 6; ii >= 0; --ii)
        {
            corner_orient[ii] = orient_copy % 3;
            total_orientation += corner_orient[ii];
            orient_copy /= 3;
        }
        corner_orient[7] = (3 - (total_orientation % 3)) % 3;

        // For every possible move that can be performed, construct a cube with
        // the given corner orientation and record the result of performing the
        // chosen move.
        for (move = 0; move < NUM_MOVES; ++move)
        {
            Cube cube(corner_perm, corner_orient, edge_perm, edge_orient);
            from = cube.coord_corner_orientation();
            cube.perform_move(move);
            to = cube.coord_corner_orientation();

            cube_co_trans[from][move] = to;
        }
    }

    // Store the coordinate cooresponding to the solved position
    Cube solved_cube;
    cube_co_trans_solved = solved_cube.coord_corner_orientation();
}

/******************************************************************************
* Function:  cube_populate_eo_trans
*
* Purpose:   Populate the edge orientation transition table.
*
* Params:    None
*
* Returns:   Nothing
*
* Operation: For each possible orientation of edges, construct a cube with
*            that edge orientation, and record the effect of each possible
*            move on the orientation of the edges.
******************************************************************************/
void cube_populate_eo_trans()
{
    // Some vectors to hold permutation and orientation info from which we can
    // instantiate a Cube object.
    std::vector<int> corner_perm, corner_orient, edge_perm, edge_orient;
    corner_perm   = {0, 1, 2, 3, 4, 5, 6, 7};
    corner_orient = {0, 0, 0, 0, 0, 0, 0, 0};
    edge_perm     = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    edge_orient   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0};

    // Local variables
    int from, to;
    int move;

    // Step through each possible edge orientation. The orientations consist 
    // of a sequence of 12 numbers taking values between 0 and 1 inclusive, 
    // which can be considered as a single integer by reading in binary. The 
    // final entry in the sequence is determined from the others by the fact
    // that their sum must be 0 (modulo 2).
    for (int orient = 0; orient < cube_eo_trans.size(); ++orient)
    {
        int orient_copy = orient;
        int total_orientation = 0;
        for (int ii = 10; ii >= 0; --ii)
        {
            edge_orient[ii] = orient_copy % 2;
            total_orientation += edge_orient[ii];
            orient_copy /= 2;
        }
        edge_orient[11] = (2 - (total_orientation % 2)) % 2;

        // For every possible move that can be performed, construct a cube with
        // the given edge orientation and record the result of performing the
        // chosen move.
        for (move = 0; move < NUM_MOVES; ++move)
        {
            Cube cube(corner_perm, corner_orient, edge_perm, edge_orient);
            from = cube.coord_edge_orientation();
            cube.perform_move(move);
            to = cube.coord_edge_orientation();

            cube_eo_trans[from][move] = to;
        }
    }

    // Store the coordinate cooresponding to the solved position
    Cube solved_cube;
    cube_eo_trans_solved = solved_cube.coord_edge_orientation();
}

/******************************************************************************
* Function:  cube_populate_cp_trans
*
* Purpose:   Populate the corner permutation transition table.
*
* Params:    None
*
* Returns:   Nothing
*
* Operation: For each possible permutation of corners, construct a cube with
*            that corner permutation, and record the effect of each possible
*            move on the permutation of the corners.
******************************************************************************/
void cube_populate_cp_trans()
{
    // Some vectors to hold permutation and orientation info from which we can
    // instantiate a Cube object.
    std::vector<int> corner_perm, corner_orient, edge_perm, edge_orient;
    corner_perm   = {0, 1, 2, 3, 4, 5, 6, 7};
    corner_orient = {0, 0, 0, 0, 0, 0, 0, 0};
    edge_perm     = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    edge_orient   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0};

    // Local variables
    int from, to;
    int move;

    // Step through every possible corner permutation, for each one recording
    // the result of performing each possible move on it.
    do
    {
        for (move = 0; move < NUM_MOVES; ++move)
        {
            Cube cube(corner_perm, corner_orient, edge_perm, edge_orient);
            from = cube.coord_corner_permutation();
            cube.perform_move(move);
            to = cube.coord_corner_permutation();

            cube_cp_trans[from][move] = to;
        }
    } while (std::next_permutation(corner_perm.begin(), corner_perm.end()));

    // Store the coordinate cooresponding to the solved position
    Cube solved_cube;
    cube_cp_trans_solved = solved_cube.coord_corner_permutation();
}

/******************************************************************************
* Function:  cube_populate_slice_sorted_trans
*
* Purpose:   Populate the sorted-slice transition table.
*
* Params:    None
*
* Returns:   Nothing
*
* Operation: For each possible sequence of positions for the slice edges,
*            construct a cube with those positions, and record the effect of
*            each possible move on the positions of the slice edges.
*
*            Note that the structure of this transition table is independent
*            of which slice is being considered, so we can perform the moves
*            on the UD-slice edges, and the transition table will be equally
*            valid for the FB-slice or RL-slice sorted coordinates.
******************************************************************************/
void cube_populate_slice_sorted_trans()
{
    // Some vectors to hold permutation and orientation info from which we can
    // instantiate a Cube object.
    std::vector<int> corner_perm, corner_orient, edge_perm, edge_orient;
    corner_perm   = {0, 1, 2, 3, 4, 5, 6, 7};
    corner_orient = {0, 0, 0, 0, 0, 0, 0, 0};
    edge_perm     = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    edge_orient   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0};

    // Local variables
    int from, to;
    int move;

    // Step through all the possible positionings of the UD-slice edges.
    edge_perm = {-1, -1, -1, -1, -1, -1, -1, -1, 
                 EDGE_FR, EDGE_FL, EDGE_BL, EDGE_BR};
    std::sort(edge_perm.begin(), edge_perm.end());

    do
    {
        for (move = 0; move < NUM_MOVES; ++move)
        {
            Cube cube(corner_perm, corner_orient, edge_perm, edge_orient);
            from = cube.coord_ud_sorted();
            cube.perform_move(move);
            to = cube.coord_ud_sorted();

            cube_slice_sorted_trans[from][move] = to;
        }
    } while (std::next_permutation(edge_perm.begin(), edge_perm.end()));

    // Store the coordinate cooresponding to the solved position
    Cube solved_cube;
    cube_slice_sorted_trans_solved = solved_cube.coord_ud_sorted();
}

/******************************************************************************
* Function:  cube_populate_ud_pos_trans
*
* Purpose:   Populate the unsorted UD-slice coordinate transition table.
*
* Params:    None
*
* Returns:   Nothing
*
* Operation: Uses the already-existing transition table for the sorted UD-slice
*            coordinate to determine the effect of each possible move on the
*            unsorted UD-slice coordinate.
******************************************************************************/
void cube_populate_ud_pos_trans()
{
    // Local variables
    int from, to;
    int move;

    // Step through the possible values of the unsorted UD-slice coordinate.
    // For each one, use a corresponding entry in the sorted slice transition
    // table to determine the effect of each possible move.
    for (move = 0; move < NUM_MOVES; ++move)
    {
        for (from = 0; from < cube_ud_pos_trans.size(); ++from)
        {
            to = cube_slice_sorted_trans[24 * from][move] / 24;
            cube_ud_pos_trans[from][move] = to;
        }
    }

    // Store the coordinate cooresponding to the solved position
    Cube solved_cube;
    int ud_solved = solved_cube.coord_ud_sorted();
    cube_ud_pos_trans_solved = ud_solved / 24;
}

/******************************************************************************
* Function:  cube_populate_ud_perm_trans
*
* Purpose:   Populate the UD-slice permutation coordinate transition table.
*
* Params:    None
*
* Returns:   Nothing
*
* Operation: Uses the already-existing transition table for the sorted UD-slice
*            coordinate to determine the effect of each possible move on the
*            UD-slice permutation coordinate.
******************************************************************************/
void cube_populate_ud_perm_trans()
{
    // Local variables
    int from, to;
    int move;

    // Work out the base value of the sorted UD-slice coordinate so that we
    // know which entry in the sorted transition table is relevant.
    Cube cube;
    int base = (cube.coord_ud_sorted() / 24) * 24;

    // Step through the possible values of the UD-slice permutation coordinate.
    // For each one, use a corresponding entry in the sorted slice transition
    // table to determine the effect of each possible move.
    for (move = 0; move < NUM_MOVES; ++move)
    {
        for (from = 0; from < cube_ud_perm_trans.size(); ++from)
        {
            to = cube_slice_sorted_trans[base + from][move] % 24;
            cube_ud_perm_trans[from][move] = to;
        }
    }

    // Store the coordinate cooresponding to the solved position
    Cube solved_cube;
    int ud_solved = solved_cube.coord_ud_sorted();
    cube_ud_perm_trans_solved = ud_solved % 24;
}

/******************************************************************************
* Function:  cube_populate_ep_trans
*
* Purpose:   Populate the edge permutation transition table.
*
* Params:    None
*
* Returns:   Nothing
*
* Operation: For each set of positions for the 8 edges in the U and D layers,
*            construct a cube with that permutation of edges, extract the
*            sorted RL-slice and FB-slice coordinates from that cube, and
*            use the already-existing sorted slice transition table to work out
*            the result of performing each possible move on the cube.
******************************************************************************/
void cube_populate_ep_trans()
{
    // Some vectors to hold permutation and orientation info from which we can
    // instantiate a Cube object.
    std::vector<int> corner_perm, corner_orient, edge_perm, edge_orient;
    corner_perm   = {0, 1, 2, 3, 4, 5, 6, 7};
    corner_orient = {0, 0, 0, 0, 0, 0, 0, 0};
    edge_perm     = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    edge_orient   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0};

    // Local variables
    int from, to;
    int move;

    // Step through the possible permutations of the 8 edges within the U and
    // D layers.
    std::vector<int> ud_edges = {EDGE_UF, EDGE_UL, EDGE_UB, EDGE_UR,
                                 EDGE_DF, EDGE_DL, EDGE_DB, EDGE_DR};
    std::sort(ud_edges.begin(), ud_edges.end());
    std::vector<int> sorted_ud_edges = ud_edges;

    do
    {
        // Construct a cube with the given edge permutation
        for (int ii = 0; ii < ud_edges.size(); ++ii)
        {
            edge_perm[sorted_ud_edges[ii]] = ud_edges[ii];
        }   
        Cube cube(corner_perm, corner_orient, edge_perm, edge_orient);

        // Extract the sorted RL-slice and FB-slice coordinates and compute the
        // result of each move
        int from_rl = cube.coord_rl_sorted();
        int from_fb = cube.coord_fb_sorted();
        from = 24 * from_rl + from_fb;

        int to_rl = cube_slice_sorted_trans[from_rl][move];
        int to_fb = cube_slice_sorted_trans[from_fb][move];
        int to = 24 * to_rl + to_fb;

        cube_ep_trans[from][move] = to;

    } while (std::next_permutation(ud_edges.begin(), ud_edges.end()));

    // Store the coordinate cooresponding to the solved position
    Cube solved_cube;
    int rl_solved = solved_cube.coord_rl_sorted();
    int fb_solved = solved_cube.coord_fb_sorted();
    cube_ep_trans_solved = 24 * rl_solved + fb_solved;
}

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
void cube_populate_all_trans_tables()
{
    cube_populate_co_trans();
    cube_populate_eo_trans();
    cube_populate_cp_trans();
    cube_populate_slice_sorted_trans();

    cube_populate_ud_pos_trans();
    cube_populate_ud_perm_trans();
    cube_populate_ep_trans();
}
