#ifndef CUBETRANS_INCLUDED
#define CUBETRANS_INCLUDED

/******************************************************************************
* Header:  cubetrans.h
*
* Purpose: Declarations for the CubeTrans class.
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <functional>
#include <vector>

#include <cube.h>

/******************************************************************************
* CubeTrans class declaration.
******************************************************************************/
class CubeTrans
{
private:
    int phase;
    std::function<int(Cube&)> coord_func;
    std::vector<std::vector<int>> table;
    int _solved_pos;
    std::vector<int> allowed_moves;
public:
    CubeTrans(int phase_desc, std::function<int(Cube&)> func, int range);
    int solved_pos();
    int size();
    int operator()(int position, int move);
    void fill();
};

#endif
