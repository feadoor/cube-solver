/******************************************************************************
* File:    cubeprunes.cpp
*
* Purpose: Builds pruning tables for the two phases of the Kociemba
*          algorithm for solving the cube.
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <deque>
#include <utility>
#include <vector>

#include <cubetranstables.h>
#include <cubeprunes.h>

/******************************************************************************
* Definition of the moves belonging to each of the two phases.
******************************************************************************/
std::vector<int> p1_moves = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L, MOVE_L2, 
                             MOVE_LP, MOVE_F, MOVE_F2, MOVE_FP, MOVE_R, 
                             MOVE_R2, MOVE_RP, MOVE_B, MOVE_B2, MOVE_BP, 
                             MOVE_D, MOVE_D2, MOVE_DP};
std::vector<int> p2_moves = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L2, MOVE_F2, 
                             MOVE_R2, MOVE_B2, MOVE_D, MOVE_D2, MOVE_DP};
                             
/******************************************************************************
* Initial definition of the pruning tables.
******************************************************************************/
prunetable cube_co_eo_prune(2187, std::vector<int>(2048, -1));
prunetable cube_co_ud_prune(2187, std::vector<int>(495,  -1));
prunetable cube_eo_ud_prune(2048, std::vector<int>(495, -1));

prunetable cube_ep_ud_prune(40320, std::vector<int>(24, -1));
prunetable cube_cp_ud_prune(40320, std::vector<int>(24, -1));

/******************************************************************************
* Implementation of functions which create pruning tables for combinations of
* two coordinates.
******************************************************************************/

/******************************************************************************
* Function:  cube_phase1_prune
*
* Purpose:   Create a pruning table for a pair of coordinates in phase 1 of the
*            Kociemba algorithm.
*
* Params:    trans1, trans2 - The two transition tables that the pruning table
*                             should be created for.
*            start1, start2 - The coordinates in the two transition tables of
*                             the solved cube position.
*            prune          - The pruning table to store the results in.
*
* Returns:   Nothing.
*
* Operation: Performs a breadth-first search on the coordinate space, using the
*            transition tables for fast moves, and records the distance from
*            solved of each position in the pruning table.
******************************************************************************/
void cube_phase1_prune(const transtable &trans1, const transtable &trans2, 
                       int start1, int start2, prunetable &prune)
{
    // Local variables
    std::pair<int, int> position;
    std::pair<int, int> new_position;
    int prune_val;

    // Set up a deque to hold the states for the breadth-first search,
    // beginning at the solved position.
    std::deque<std::pair<int, int>> prune_bfs;
    prune_bfs.push_back(std::make_pair(start1, start2));
    prune[start1][start2] = 0;

    // Perform the breadth-first search through the reachable positions.
    while (!prune_bfs.empty())
    {
        position = prune_bfs.front();
        prune_val = prune[position.first][position.second];
        prune_bfs.pop_front();

        // Iterate over all possible moves from this position and store the
        // distance from solved of any new positions encountered.
        for (int move : p1_moves)
        {
            new_position = std::make_pair(trans1[position.first][move],
                                          trans2[position.second][move]);
            if (prune[new_position.first][new_position.second] == -1)
            {
                prune_bfs.push_back(new_position);
                prune[new_position.first][new_position.second] = prune_val + 1;
            }
        }
    }
}

/******************************************************************************
* Function:  cube_phase2_prune
*
* Purpose:   Create a pruning table for a pair of coordinates in phase 2 of the
*            Kociemba algorithm.
*
* Params:    trans1, trans2 - The two transition tables that the pruning table
*                             should be created for.
*            start1, start2 - The coordinates in the two transition tables of
*                             the solved cube position.
*            prune          - The pruning table to store the results in.
*
* Returns:   Nothing.
*
* Operation: Performs a breadth-first search on the coordinate space, using the
*            transition tables for fast moves, and records the distance from
*            solved of each position in the pruning table.
******************************************************************************/
void cube_phase2_prune(const transtable &trans1, const transtable &trans2, 
                       int start1, int start2, prunetable &prune)
{
    // Local variables
    std::pair<int, int> position;
    std::pair<int, int> new_position;
    int prune_val;

    // Set up a deque to hold the states for the breadth-first search,
    // beginning at the solved position.
    std::deque<std::pair<int, int>> prune_bfs;
    prune_bfs.push_back(std::make_pair(start1, start2));
    prune[start1][start2] = 0;

    // Perform the breadth-first search through the reachable positions.
    while (!prune_bfs.empty())
    {
        position = prune_bfs.front();
        prune_val = prune[position.first][position.second];
        prune_bfs.pop_front();

        // Iterate over all possible moves from this position and store the
        // distance from solved of any new positions encountered.
        for (int move : p2_moves)
        {
            new_position = std::make_pair(trans1[position.first][move],
                                          trans2[position.second][move]);
            if (prune[new_position.first][new_position.second] == -1)
            {
                prune_bfs.push_back(new_position);
                prune[new_position.first][new_position.second] = prune_val + 1;
            }
        }
    }
}

/******************************************************************************
* Function:  cube_all_prune
*
* Purpose:   Create all pruning tables used in the Kociemba algorithm.
*
* Params:    None.
*
* Returns:   Nothing.
*
* Operation: Calls into another function for each pruning table to make.
******************************************************************************/
void cube_all_prune()
{
    // CO and EO pruning table
    cube_phase1_prune(cube_co_trans, cube_eo_trans,
                      cube_co_trans_solved, cube_eo_trans_solved,
                      cube_co_eo_prune);
    // CO and UD-slice pruning table
    cube_phase1_prune(cube_co_trans, cube_ud_pos_trans,
                      cube_co_trans_solved, cube_ud_pos_trans_solved,
                      cube_co_ud_prune);
    // EO and UD-slice pruning table
    cube_phase1_prune(cube_eo_trans, cube_ud_pos_trans,
                      cube_eo_trans_solved, cube_ud_pos_trans_solved,
                      cube_eo_ud_prune); 

    // EP and UD-permutation pruning table
    cube_phase2_prune(cube_ep_trans, cube_ud_perm_trans,
                      cube_ep_trans_solved, cube_ud_perm_trans_solved,
                      cube_ep_ud_prune);
    // CP and UD-permutation pruning table
    cube_phase2_prune(cube_cp_trans, cube_ud_perm_trans,
                      cube_cp_trans_solved, cube_ud_perm_trans_solved,
                      cube_cp_ud_prune);
}
