/******************************************************************************
* File:    cubeprune.cpp
*
* Purpose: Implementation of the CubePrune class, representing a single pruning
*          table for use in the Kociemba algorithm.
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

#include <cube.h>
#include <cubephase.h>
#include <cubeprune.h>
#include <cubetrans.h>

/******************************************************************************
* CubePrune class implementation.
******************************************************************************/

/******************************************************************************
* Function:  CubePrune::CubePrune
*
* Purpose:   Constructor for the CubePrune class.
*
* Params:    phase_desc    - Whether this pruning table is relevant in phase 1
*                            or phase 2 of the two-phase algorithm.
*            trans_table_1 - Pointers to the transition tables of the cube
*            trans_table_2 - coordinates that this table is for.
*
* Returns:   Nothing.
*
* Operation: Uses the phase to store the available moves, and stores the
*            transition tables. Allocates space for the data in the pruning
*            table.
******************************************************************************/
CubePrune::CubePrune(int phase_desc,
                     CubeTrans* trans_table_1, CubeTrans* trans_table_2)
{
    phase = phase_desc;
    transition_table_1 = trans_table_1;
    transition_table_2 = trans_table_2;

    table = std::vector<std::vector<int>>(
                                  trans_table_1->size(),
                                  std::vector<int>(trans_table_2->size(), -1));
}

/******************************************************************************
* Function:  CubePrune::operator()
*
* Purpose:   Returns an entry in the pruning table.
*
* Params:    coord_value_1 - The coordinate values of the position to look up.
*            coord_value_2
*
* Returns:   The value stored in the table for that combination of coordinates.
*
* Operation: Simply return the value from the private table.
******************************************************************************/
int CubePrune::operator()(int coord_value_1, int coord_value_2)
{
    return table[coord_value_1][coord_value_2];
}

/******************************************************************************
* Function:  CubePrune::fill
*
* Purpose:   Fill in the entries in this pruning table.
*
* Params:    None.
*
* Returns:   Nothing.
*
* Operation: Starting from the solved position, at depth 0, perform a
*            breadth-first search of the shared coordinate space and store the
*            depth from solved of each position.
******************************************************************************/
void CubePrune::fill()
{
    // Local variables
    std::pair<int, int> curr_position, next_position;
    int depth;

    // Set up a deque which we will use to perform the breadth-first search.
    std::deque<std::pair<int, int>> bfs;

    // Push the solved position onto the deque and record the depth of the
    // solved position.
    int solved_1 = transition_table_1->solved_pos();
    int solved_2 = transition_table_2->solved_pos();
    bfs.push_back(std::make_pair(solved_1, solved_2));
    table[solved_1][solved_2] = 0;

    // Work out the available moves
    if (phase == PHASE_1)
    {
        allowed_moves = cube_p1_allowed_moves[NUM_MOVES];
    }
    else if (phase == PHASE_2)
    {
        allowed_moves = cube_p2_allowed_moves[NUM_MOVES];
    }

    // Perform the breadth-first search
    while (!bfs.empty())
    {
        // Get the top position from the deque, and record the depths of all of
        // its children positions.
        curr_position = bfs.front();
        depth = table[curr_position.first][curr_position.second];
        bfs.pop_front();

        for (int move : allowed_moves)
        {
            next_position = std::make_pair(
                            (*transition_table_1)(curr_position.first,  move),
                            (*transition_table_2)(curr_position.second, move));

            if (table[next_position.first][next_position.second] == -1)
            {
                bfs.push_back(next_position);
                table[next_position.first][next_position.second] = depth + 1;
            }
        }
    }
}
