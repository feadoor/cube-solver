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
#include <vector>

#include <cube.h>
#include <cubetranstables.h>
#include <cubeprunes.h>
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
    start_co = cube.coord_corner_orientation();
    start_eo = cube.coord_edge_orientation();
    start_ud = cube.coord_ud_pos();

    // Calculate the starting values of the auxiliary coordinates.
    start_ud_sorted = cube.coord_ud_sorted();
    start_rl_sorted = cube.coord_rl_sorted();
    start_fb_sorted = cube.coord_fb_sorted();
    start_cp  = cube.coord_corner_permutation();

    // Set up the available moves vectors
    create_available_moves();
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
    start_co = scrambled_cube.coord_corner_orientation();
    start_eo = scrambled_cube.coord_edge_orientation();
    start_ud = scrambled_cube.coord_ud_pos();

    // Calculate the starting values of the auxiliary coordinates.
    start_ud_sorted = scrambled_cube.coord_ud_sorted();
    start_rl_sorted = scrambled_cube.coord_rl_sorted();
    start_fb_sorted = scrambled_cube.coord_fb_sorted();
    start_cp  = scrambled_cube.coord_corner_permutation();

    // Set up the available moves vectors
    create_available_moves();
}

/******************************************************************************
* Function:  CubeSolver::create_available_moves
*
* Purpose:   Fill in the private member variables detailing which moves are
*            allowed to follow other moves in solutions.
*
* Params:    None.
*
* Returns:   Nothing.
*
* Operation: Mandate that no face can be turned twice in a row, and that the
*            L, U and F faces cannot follow the R, D and B faces respectively.
******************************************************************************/
void CubeSolver::create_available_moves()
{
    available_moves_p1 = std::vector<std::vector<int>>(NUM_MOVES, 
                                                       std::vector<int>(0));
    available_moves_p2 = std::vector<std::vector<int>>(NUM_MOVES, 
                                                       std::vector<int>(0));

    available_moves_p1[MOVE_U] = {MOVE_L, MOVE_L2, MOVE_LP, MOVE_F, MOVE_F2,
                                  MOVE_FP, MOVE_R, MOVE_R2, MOVE_RP, MOVE_B,
                                  MOVE_B2, MOVE_BP, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_U2] = {MOVE_L, MOVE_L2, MOVE_LP, MOVE_F, MOVE_F2,
                                   MOVE_FP, MOVE_R, MOVE_R2, MOVE_RP, MOVE_B,
                                   MOVE_B2, MOVE_BP, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_UP] = {MOVE_L, MOVE_L2, MOVE_LP, MOVE_F, MOVE_F2,
                                   MOVE_FP, MOVE_R, MOVE_R2, MOVE_RP, MOVE_B,
                                   MOVE_B2, MOVE_BP, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_L] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_F, MOVE_F2,
                                  MOVE_FP, MOVE_R, MOVE_R2, MOVE_RP, MOVE_B,
                                  MOVE_B2, MOVE_BP, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_L2] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_F, MOVE_F2,
                                   MOVE_FP, MOVE_R, MOVE_R2, MOVE_RP, MOVE_B,
                                   MOVE_B2, MOVE_BP, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_LP] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_F, MOVE_F2,
                                   MOVE_FP, MOVE_R, MOVE_R2, MOVE_RP, MOVE_B,
                                   MOVE_B2, MOVE_BP, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_F] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L, MOVE_L2,
                                  MOVE_LP, MOVE_R, MOVE_R2, MOVE_RP, MOVE_B,
                                  MOVE_B2, MOVE_BP, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_F2] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L, MOVE_L2,
                                   MOVE_LP, MOVE_R, MOVE_R2, MOVE_RP, MOVE_B,
                                   MOVE_B2, MOVE_BP, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_FP] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L, MOVE_L2,
                                   MOVE_LP, MOVE_R, MOVE_R2, MOVE_RP, MOVE_B,
                                   MOVE_B2, MOVE_BP, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_R] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_F, MOVE_F2,
                                  MOVE_FP, MOVE_B, MOVE_B2, MOVE_BP, MOVE_D,
                                  MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_R2] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_F, MOVE_F2,
                                   MOVE_FP, MOVE_B, MOVE_B2, MOVE_BP, MOVE_D,
                                   MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_RP] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_F, MOVE_F2,
                                   MOVE_FP, MOVE_B, MOVE_B2, MOVE_BP, MOVE_D,
                                   MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_B] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L, MOVE_L2,
                                  MOVE_LP, MOVE_R, MOVE_R2, MOVE_RP, MOVE_D,
                                  MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_B2] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L, MOVE_L2,
                                   MOVE_LP, MOVE_R, MOVE_R2, MOVE_RP, MOVE_D,
                                   MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_BP] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L, MOVE_L2,
                                   MOVE_LP, MOVE_R, MOVE_R2, MOVE_RP, MOVE_D,
                                   MOVE_D2, MOVE_DP};
    available_moves_p1[MOVE_D] = {MOVE_L, MOVE_L2, MOVE_LP, MOVE_F, MOVE_F2,
                                  MOVE_FP, MOVE_B, MOVE_B2, MOVE_BP, MOVE_R,
                                  MOVE_R2, MOVE_RP};
    available_moves_p1[MOVE_D2] = {MOVE_L, MOVE_L2, MOVE_LP, MOVE_F, MOVE_F2,
                                   MOVE_FP, MOVE_B, MOVE_B2, MOVE_BP, MOVE_R,
                                   MOVE_R2, MOVE_RP};
    available_moves_p1[MOVE_DP] = {MOVE_L, MOVE_L2, MOVE_LP, MOVE_F, MOVE_F2,
                                   MOVE_FP, MOVE_B, MOVE_B2, MOVE_BP, MOVE_R,
                                   MOVE_R2, MOVE_RP};
    available_moves_p1.push_back({MOVE_U, MOVE_U2, MOVE_UP, MOVE_L, MOVE_L2,
                                  MOVE_LP, MOVE_F, MOVE_F2, MOVE_FP, MOVE_R,
                                  MOVE_R2, MOVE_RP, MOVE_B, MOVE_B2, MOVE_BP,
                                  MOVE_D, MOVE_D2, MOVE_DP});

    available_moves_p2[MOVE_U] = {MOVE_L2, MOVE_F2, MOVE_R2, MOVE_B2, MOVE_D,
                                  MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_U2] = {MOVE_L2, MOVE_F2, MOVE_R2, MOVE_B2, MOVE_D,
                                   MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_UP] = {MOVE_L2, MOVE_F2, MOVE_R2, MOVE_B2, MOVE_D,
                                   MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_L] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_F2, MOVE_R2, 
                                  MOVE_B2, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_L2] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_F2, MOVE_R2, 
                                   MOVE_B2, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_LP] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_F2, MOVE_R2, 
                                   MOVE_B2, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_F] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L2, MOVE_R2, 
                                  MOVE_B2, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_F2] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L2, MOVE_R2, 
                                   MOVE_B2, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_FP] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L2, MOVE_R2, 
                                   MOVE_B2, MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_R] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_F2, MOVE_B2, 
                                  MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_R2] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_F2, MOVE_B2, 
                                   MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_RP] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_F2, MOVE_B2, 
                                   MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_B] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L2, MOVE_R2, 
                                  MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_B2] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L2, MOVE_R2, 
                                   MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_BP] = {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L2, MOVE_R2, 
                                   MOVE_D, MOVE_D2, MOVE_DP};
    available_moves_p2[MOVE_D] = {MOVE_L2, MOVE_F2, MOVE_R2, MOVE_B2};
    available_moves_p2[MOVE_D2] = {MOVE_L2, MOVE_F2, MOVE_R2, MOVE_B2};
    available_moves_p2[MOVE_DP] = {MOVE_L2, MOVE_F2, MOVE_R2, MOVE_B2};
    available_moves_p2.push_back({MOVE_U, MOVE_U2, MOVE_UP, MOVE_L2, MOVE_F2,
                                  MOVE_R2, MOVE_B2, MOVE_D, MOVE_D2, MOVE_DP});
}                                   

/******************************************************************************
* Function:  CubeSolver::phase1_search
*
* Purpose:   Finds solutions to phase 1 of the Kociemba algorithm.
*
* Params:    coord_co    - The current corner orientation coordinate.
*            coord_eo    - The current edge orientation coordinate.
*            coord_ud    - The current UD-slice coordinate.
*            depth       - How deep in the tree we should go from the current
*                          cube position.
*            process_sol - A callback which will be be called on each final
*                          solution as it is discovered.
*
* Returns:   Nothing.
*
* Operation: Uses a depth-first search to find phase-1 solutions, and when a
*            solution is found, starts a phase 2 search from that position.
******************************************************************************/
void CubeSolver::phase1_search(int coord_co, int coord_eo, int coord_ud,
                               int depth,
                               void (*process_sol)(std::vector<int> moves))
{
    // If the depth is zero, then check if we have a valid phase 1 solution.
    if (depth == 0 &&
        coord_co == cube_co_trans_solved &&
        coord_eo == cube_eo_trans_solved &&
        coord_ud == cube_ud_pos_trans_solved &&
        std::find(p2_moves.begin(), p2_moves.end(), last_move) == 
                                                                p2_moves.end())
    {
        // Initialise the phase 2 starting coordinates and call into the phase
        // 2 search from this position
        int ud_sorted = start_ud_sorted;
        int rl_sorted = start_rl_sorted;
        int fb_sorted = start_fb_sorted;
        int coord_cp  = start_cp;

        for (int move: solution)
        {
            ud_sorted = cube_slice_sorted_trans[ud_sorted][move];
            rl_sorted = cube_slice_sorted_trans[rl_sorted][move];
            fb_sorted = cube_slice_sorted_trans[fb_sorted][move];
            coord_cp  = cube_cp_trans[coord_cp][move];
        }

        int new_cp = coord_cp;
        int new_ep = 24 * rl_sorted + fb_sorted % 24;
        int new_ud = ud_sorted % 24;

        for (int depth2 = 0; depth2 <= max_length - solution.size(); ++depth2)
        {   
            phase2_search(new_cp, new_ep, new_ud, depth2, process_sol);
        }
    }

    // If the depth is not zero, then check the pruning tables to see if we
    // should prune this branch or not, and then check all available moves.
    else if (depth > 0)
    {
        if (cube_co_eo_prune[coord_co][coord_eo] <= depth &&
            cube_co_ud_prune[coord_co][coord_ud] <= depth &&
            cube_eo_ud_prune[coord_eo][coord_ud] <= depth)
        {
            for (int move: available_moves_p1[last_move])
            {
                int new_co = cube_co_trans[coord_co][move];
                int new_eo = cube_eo_trans[coord_eo][move];
                int new_ud = cube_ud_pos_trans[coord_ud][move];

                last_move = move;
                solution.push_back(move);

                phase1_search(new_co, new_eo, new_ud, depth - 1, process_sol);

                solution.pop_back();
                last_move = (solution.empty()) ? NUM_MOVES : solution.back();
            }
        }
    }
}

/******************************************************************************
* Function:  CubeSolver::phase2_search
*
* Purpose:   Finds solutions to phase 2 of the Kociemba algorithm.
*
* Params:    coord_cp    - The current corner permutation coordinate.
*            coord_ep    - The current edge permutation coordinate.
*            coord_ud    - The current UD-slice permutation coordinate.
*            depth       - How deep in the tree we should go from the current
*                          cube position.
*            process_sol - A callback which will be be called on each final
*                          solution as it is discovered.
*
* Returns:   Nothing.
*
* Operation: Uses a depth-first search to find phase-2 solutions, and when a
*            solution is found, executes the callback.
******************************************************************************/
void CubeSolver::phase2_search(int coord_cp, int coord_ep, int coord_ud,
                               int depth,
                               void (*process_sol)(std::vector<int> moves))
{
    // Break out early if we're looking for a solution of the same length as
    // one we've already found, or longer.
    if (depth + solution.size() >= max_length)
    {
        return;
    }

    // If the depth is zero, then check if we have a valid phase 2 solution.
    if (depth == 0 &&
        coord_cp == cube_cp_trans_solved &&
        coord_ep == cube_ep_trans_solved &&
        coord_ud == cube_ud_perm_trans_solved)
    {
        // We've found a solution, so update the max_length, and execute the
        // callback on the solution
        max_length = solution.size() - 1;
        process_sol(solution);
    }

    // If the depth is not zero, then check the pruning tables to see if we
    // should prune this branch or not, and then check all available moves.
    else if (depth > 0)
    {
        if (cube_cp_ud_prune[coord_cp][coord_ud] <= depth &&
            cube_ep_ud_prune[coord_ep][coord_ud] <= depth)
        {
            for (int move: available_moves_p2[last_move])
            {
                int new_cp = cube_cp_trans[coord_cp][move];
                int new_ep = cube_ep_trans[coord_ep][move];
                int new_ud = cube_ud_perm_trans[coord_ud][move];

                last_move = move;
                solution.push_back(move);

                phase2_search(new_cp, new_ep, new_ud, depth - 1, process_sol);

                solution.pop_back();
                last_move = (solution.empty()) ? NUM_MOVES : solution.back();
            }
        }
    }
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
void CubeSolver::solve(void (*process_sol)(std::vector<int> moves))
{
    // Reset private member variables to their starting values
    max_length = INT_MAX;
    solution = {};
    last_move = NUM_MOVES;

    // Begin searching for solutions.
    for (int depth = 0; depth <= max_length; ++depth)
    {
        phase1_search(start_co, start_eo, start_ud, depth, process_sol);
    }
}
