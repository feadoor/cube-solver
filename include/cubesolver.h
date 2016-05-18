#ifndef CUBESOLVER_INCLUDED
#define CUBESOLVER_INCLUDED

/******************************************************************************
* Header:  cubesolver.h
*
* Purpose: Declarations for the CubeSolver class
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <vector>

#include <cube.h>

/******************************************************************************
* CubeSolver class declaration
******************************************************************************/
class CubeSolver
{
private:
    int max_length;
    std::vector<int> solution;
    int last_move;

    int start_co, start_eo, start_ud;
    int start_ud_sorted, start_rl_sorted, start_fb_sorted, start_cp;

    std::vector<std::vector<int>> available_moves_p1;
    std::vector<std::vector<int>> available_moves_p2;
    void create_available_moves();

    void phase1_search(int coord_co, int coord_eo, int coord_ud,
                       int depth,
                       void (*process_sol)(std::vector<int> moves));
    void phase2_search(int coord_cp, int coord_ep, int coord_ud,
                       int depth,
                       void (*process_sol)(std::vector<int> moves));
public:
    CubeSolver();
    CubeSolver(Cube cube);
    void solve(void (*process_sol)(std::vector<int> moves));
};

#endif
