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
    std::function<int(Cube&)> coord_func;
    std::vector<std::vector<int>> table;
    int _solved_pos;
public:
    CubeTrans(std::function<int(Cube&)> func, int range);
    int solved_pos();
    int operator()(int position, int move);
    void fill();
};

#endif
