/******************************************************************************
* File:    cubetrans.cpp
*
* Purpose: Implementation of the CubeTrans class, which represents a single
*          transition table for a Rubik's cube coordinate.
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <functional>
#include <stack>

#include <cube.h>
#include <cubetrans.h>

/******************************************************************************
* Cubetrans class implementation
******************************************************************************/

/******************************************************************************
* Function:  CubeTrans::CubeTrans
*
* Purpose:   Constructor for the CubeTrans class.
*
* Params:    func  - Pointer to Cube member function which calculates the value
*                    of some coordinate.
*            range - The number of values taken by the above coordinate.
*
* Returns:   Nothing.
*
* Operation: Stores the function pointer as a member variable and allocates
*            space for the transition table entries.
******************************************************************************/
CubeTrans::CubeTrans(std::function<int(Cube&)> func, int range)
{
    coord_func = func;
    table = std::vector<std::vector<int>>(range, 
                                          std::vector<int>(NUM_MOVES, -1));
}

/******************************************************************************
* Function:  CubeTrans::solved_pos
*
* Purpose:   Getter for the private _solved_pos member variable
*
* Params:    None.
*
* Returns:   The value of the _solved_pos member.
*
* Operation: Simply return the value.
******************************************************************************/
int CubeTrans::solved_pos()
{
    return _solved_pos;
}

/******************************************************************************
* Function:  CubeTrans::operator()
*
* Purpose:   Returns an entry in the transition table.
*
* Params:    position - The coordinate value of the 'from' position 
*            move     - The move to be performed.
*
* Returns:   The coordinate value of the resulting position.
*
* Operation: Simply return the value from the private table.
******************************************************************************/
int CubeTrans::operator()(int position, int move)
{
    return table[position][move];
}

/******************************************************************************
* Function:  CubeTrans::fill
*
* Purpose:   Fills in the entries of this transition table.
*
* Params:    None.
*
* Returns:   Nothing.
*
* Operation: Starting from the solved position, uses a depth-first search of
*            cube positions, visiting each value of the coordinate exactly once
*            and determining the result of each move on it.
******************************************************************************/
void CubeTrans::fill()
{
    // Local variables
    Cube curr_cube, next_cube;
    int curr_coord, next_coord;
    int move;

    // Set up a stack which we will use to perform the depth-first search and
    // an auxiliary array which will keep track of which coordinate values we
    // have already pushed onto the stack, to avoid duplication.
    std::stack<Cube> dfs;
    std::vector<bool> seen(table.size(), false);

    // Push the solved position onto the stack and record the coordinate value
    // of the solved cube.
    Cube solved_cube;
    _solved_pos = coord_func(solved_cube);
    seen[_solved_pos] = true;
    dfs.push(solved_cube);

    // Perform the depth-first search
    while (!dfs.empty())
    {
        // Get the top cube from the stack, and record the result of each move
        // on the coordinate value.
        curr_cube = dfs.top();
        curr_coord = coord_func(curr_cube);
        dfs.pop();

        for (move = 0; move < NUM_MOVES; ++move)
        {
            next_cube = curr_cube.perform_move(move);
            next_coord = coord_func(next_cube);
            table[curr_coord][move] = next_coord;

            // Push the resulting cube onto the stack if necessary.
            if (!seen[next_coord])
            {
                seen[next_coord] = true;
                dfs.push(next_cube);
            }
        }
    }
}
