#ifndef CUBEPRUNE_INCLUDED
#define CUBEPRUNE_INCLUDED

/******************************************************************************
* Header:  cubeprune.h
*
* Purpose: Declaration of the CubePrune class.
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <vector>

#include <cubetrans.h>

/******************************************************************************
* CubePrune class declaration.
******************************************************************************/
class CubePrune
{
private:
    int phase;
    std::vector<int> allowed_moves;
    CubeTrans* transition_table_1;
    CubeTrans* transition_table_2;
    std::vector<std::vector<int>> table;
public:
    CubePrune(int phase_desc,
              CubeTrans* trans_table_1, CubeTrans* trans_table_2);
    int operator()(int coord_value_1, int coord_value_2);
    void fill();
};

#endif
