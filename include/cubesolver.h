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

    int curr_co, curr_eo, curr_ud_pos;
    int curr_cp, curr_ep, curr_ud_perm;
    int start_ud_sorted, start_rl_sorted, start_fb_sorted, start_cp;

    void phase1_search(int depth);
    void phase2_search(int depth);
    void print_sol();
public:
    CubeSolver();
    CubeSolver(Cube cube);
    void solve();
};

#endif
