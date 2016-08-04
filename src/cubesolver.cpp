/******************************************************************************
* File:    cubesolver.cpp
*
* Purpose: Implementation of the CubeSolver class which uses the Kociemba
*          algorithm to quickly find near-optimal solutions to the cube.
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

#include <cube.h>
#include <cubephase.h>
#include <cubetables.h>
#include <cubesolver.h>

/******************************************************************************
* CubeSolver class implementation
******************************************************************************/

/******************************************************************************
* Function:  CubeSolver::CubeSolver
*
* Purpose:   Default constructor for the CubeSolver class.
*
* Params:    None.
*
* Returns:   Nothing.
*
* Operation: Sets up a CubeSolver instance which will try to find a solution
*            to a cube given by the default Constructor of the Cube class.
******************************************************************************/
CubeSolver::CubeSolver()
{
    Cube cube;

    // Calculate the starting values of the phase 1 coordinates.
    curr_co = cube.coord_corner_orientation();
    curr_eo = cube.coord_edge_orientation();
    curr_ud_pos = cube.coord_ud_unsorted();

    // Calculate the starting values of the auxiliary coordinates.
    start_ud_sorted = cube.coord_ud_sorted();
    start_rl_sorted = cube.coord_rl_sorted();
    start_fb_sorted = cube.coord_fb_sorted();
    start_cp  = cube.coord_corner_permutation();
}

/******************************************************************************
* Function:  CubeSolver::CubeSolver
*
* Purpose:   Constructor for the CubeSolver class.
*
* Params:    scrambled_cube - a Cube object which is in the state we are
*                             trying to find a solution to.
*
* Returns:   Nothing.
*
* Operation: Sets the private member variable cube to be equal to the cube
*            object which was passed in.
******************************************************************************/
CubeSolver::CubeSolver(Cube scrambled_cube)
{
    // Calculate the starting values of the phase 1 coordinates.
    curr_co = scrambled_cube.coord_corner_orientation();
    curr_eo = scrambled_cube.coord_edge_orientation();
    curr_ud_pos = scrambled_cube.coord_ud_unsorted();

    // Calculate the starting values of the auxiliary coordinates.
    start_ud_sorted = scrambled_cube.coord_ud_sorted();
    start_rl_sorted = scrambled_cube.coord_rl_sorted();
    start_fb_sorted = scrambled_cube.coord_fb_sorted();
    start_cp  = scrambled_cube.coord_corner_permutation();
}

/******************************************************************************
* Function:  CubeSolver::phase1_search
*
* Purpose:   Finds solutions to phase 1 of the Kociemba algorithm.
*
* Params:    depth - How deep in the tree we should go from the current cube
*                    position.
*
* Returns:   Nothing.
*
* Operation: Uses a depth-first search to find phase-1 solutions, and when a
*            solution is found, starts a phase 2 search from that position.
******************************************************************************/
void CubeSolver::phase1_search(int depth)
{
    // If the depth is zero, then check if we have a valid phase 1 solution.
    if (depth == 0 &&
        curr_co == cube_co_trans.solved_pos() &&
        curr_eo == cube_eo_trans.solved_pos() &&
        curr_ud_pos == cube_ud_unsorted_trans.solved_pos() &&
        std::find(cube_p2_allowed_moves[NUM_MOVES].begin(),
                  cube_p2_allowed_moves[NUM_MOVES].end(), last_move)
                                     == cube_p2_allowed_moves[NUM_MOVES].end())
    {
        // Initialise the phase 2 starting coordinates and call into the phase
        // 2 search from this position
        int ud_sorted = start_ud_sorted;
        int rl_sorted = start_rl_sorted;
        int fb_sorted = start_fb_sorted;
        int coord_cp  = start_cp;

        for (int move : solution)
        {
            ud_sorted = cube_ud_sorted_trans(ud_sorted, move);
            rl_sorted = cube_rl_sorted_trans(rl_sorted, move);
            fb_sorted = cube_fb_sorted_trans(fb_sorted, move);
            coord_cp  = cube_cp_trans(coord_cp, move);
        }

        curr_cp = coord_cp;
        curr_ep = Cube::edge_permutation_calc(rl_sorted, fb_sorted);
        curr_ud_perm = Cube::ud_permutation_calc(ud_sorted);

        for (int depth2 = 0;
             (int)(depth2 + solution.size()) <= max_length;
             ++depth2)
        {
            phase2_search(depth2);
        }
    }

    // If the depth is not zero, then check the pruning tables to see if we
    // should prune this branch or not, and then check all available moves.
    else if (depth > 0)
    {
        if (cube_co_eo_prune(curr_co, curr_eo) <= depth &&
            cube_co_ud_prune(curr_co, curr_ud_pos) <= depth &&
            cube_eo_ud_prune(curr_eo, curr_ud_pos) <= depth)
        {
            int old_co = curr_co;
            int old_eo = curr_eo;
            int old_ud_pos = curr_ud_pos;

            for (int move : cube_p1_allowed_moves[last_move])
            {
                curr_co = cube_co_trans(old_co, move);
                curr_eo = cube_eo_trans(old_eo, move);
                curr_ud_pos = cube_ud_unsorted_trans(old_ud_pos, move);

                last_move = move;
                solution.push_back(move);

                phase1_search(depth - 1);

                solution.pop_back();
                last_move = (solution.empty()) ? NUM_MOVES : solution.back();
            }

            curr_co = old_co;
            curr_eo = old_eo;
            curr_ud_pos = old_ud_pos;
        }
    }
}

/******************************************************************************
* Function:  CubeSolver::phase2_search
*
* Purpose:   Finds solutions to phase 2 of the Kociemba algorithm.
*
* Params:    depth - How deep in the tree we should go from the current cube
*                    cube position.
*
* Returns:   Nothing.
*
* Operation: Uses a depth-first search to find phase-2 solutions, and when a
*            solution is found, calls print_sol on it.
******************************************************************************/
void CubeSolver::phase2_search(int depth)
{
    // Break out early if we're looking for a solution of the same length as
    // one we've already found, or longer.
    if ((int)(depth + solution.size()) >= max_length)
    {
        return;
    }

    // If the depth is zero, then check if we have a valid phase 2 solution.
    if (depth == 0 &&
        curr_cp == cube_cp_trans.solved_pos() &&
        curr_ep == cube_ep_trans.solved_pos() &&
        curr_ud_perm == cube_ud_perm_trans.solved_pos())
    {
        // We've found a solution, so update the max_length, and execute the
        // callback on the solution
        max_length = solution.size() - 1;
        print_sol();
    }

    // If the depth is not zero, then check the pruning tables to see if we
    // should prune this branch or not, and then check all available moves.
    else if (depth > 0)
    {
        if (cube_cp_ud_prune(curr_cp, curr_ud_perm) <= depth &&
            cube_ep_ud_prune(curr_ep, curr_ud_perm) <= depth)
        {
            int old_cp = curr_cp;
            int old_ep = curr_ep;
            int old_ud_perm = curr_ud_perm;

            for (int move : cube_p2_allowed_moves[last_move])
            {
                curr_cp = cube_cp_trans(old_cp, move);
                curr_ep = cube_ep_trans(old_ep, move);
                curr_ud_perm = cube_ud_perm_trans(old_ud_perm, move);

                last_move = move;
                solution.push_back(move);

                phase2_search(depth - 1);

                solution.pop_back();
                last_move = (solution.empty()) ? NUM_MOVES : solution.back();
            }

            curr_cp = old_cp;
            curr_ep = old_ep;
            curr_ud_perm = old_ud_perm;
        }
    }
}

/******************************************************************************
* Function:  CubeSolver::print_sol
*
* Purpose:   Display a solution that has been found.
*
* Params:    None.
*
* Returns:   Nothing.
*
* Operation: Prints out the length and the moves of the currently stored
*            solution.
******************************************************************************/
void CubeSolver::print_sol()
{
    std::cout << "Length: " << solution.size() << std::endl;
    for (int ii = 0; ii < solution.size(); ++ii)
    {
        switch (solution[ii])
        {
            case MOVE_U:
            case MOVE_U2:
            case MOVE_UP:
                std::cout << "U";
                break;
            case MOVE_L:
            case MOVE_L2:
            case MOVE_LP:
                std::cout << "L";
                break;
            case MOVE_F:
            case MOVE_F2:
            case MOVE_FP:
                std::cout << "F";
                break;
            case MOVE_R:
            case MOVE_R2:
            case MOVE_RP:
                std::cout << "R";
                break;
            case MOVE_B:
            case MOVE_B2:
            case MOVE_BP:
                std::cout << "B";
                break;
            case MOVE_D:
            case MOVE_D2:
            case MOVE_DP:
                std::cout << "D";
                break;
        }

        switch (solution[ii])
        {
            case MOVE_U:
            case MOVE_L:
            case MOVE_F:
            case MOVE_R:
            case MOVE_B:
            case MOVE_D:
                std::cout << " ";
                break;
            case MOVE_U2:
            case MOVE_L2:
            case MOVE_F2:
            case MOVE_R2:
            case MOVE_B2:
            case MOVE_D2:
                std::cout << "2 ";
                break;
            case MOVE_UP:
            case MOVE_LP:
            case MOVE_FP:
            case MOVE_RP:
            case MOVE_BP:
            case MOVE_DP:
                std::cout << "' ";
                break;
        }
    }
    std::cout << std::endl << std::endl;
}

/******************************************************************************
* Function:  CubeSolver::solve
*
* Purpose:   Finds solutions to the current cube state.
*
* Params:    process_sol - A callback which will be called on each solution as
*                          it is discovered.
*
* Returns:   Nothing.
*
* Operation: Uses the two-phase Kociemba algorithm with transition tables and
*            pruning to find solutions.
******************************************************************************/
void CubeSolver::solve()
{
    // Reset private member variables to their starting values
    max_length = INT_MAX;
    solution = {};
    last_move = NUM_MOVES;

    // Begin searching for solutions.
    for (int depth = 0; depth <= max_length; ++depth)
    {
        phase1_search(depth);
    }
}