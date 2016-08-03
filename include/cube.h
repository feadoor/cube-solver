#ifndef CUBE_INCLUDED
#define CUBE_INCLUDED

/******************************************************************************
* Header:  cube.h
*
* Purpose: Declarations for the Cube class
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <vector>

/******************************************************************************
* Constants
******************************************************************************/
enum {MOVE_U, MOVE_U2, MOVE_UP, MOVE_L, MOVE_L2, MOVE_LP,
      MOVE_F, MOVE_F2, MOVE_FP, MOVE_R, MOVE_R2, MOVE_RP,
      MOVE_B, MOVE_B2, MOVE_BP, MOVE_D, MOVE_D2, MOVE_DP, NUM_MOVES};
enum {EDGE_UF, EDGE_UL, EDGE_UB, EDGE_UR,
      EDGE_DF, EDGE_DL, EDGE_DB, EDGE_DR,
      EDGE_FR, EDGE_FL, EDGE_BL, EDGE_BR};
enum {CORNER_URF, CORNER_UFL, CORNER_ULB, CORNER_UBR,
      CORNER_DFR, CORNER_DLF, CORNER_DBL, CORNER_DRB};
enum {TWIST_NONE, TWIST_CW, TWIST_CCW};
enum {FLIP_NONE, FLIP_FLIP};

/******************************************************************************
* Helper functions
******************************************************************************/
int binom(int n, int k);

/******************************************************************************
* Cube class declarations
******************************************************************************/
class Cube
{
private:
    std::vector<int> corner_permutation;
    std::vector<int> corner_orientation;
    std::vector<int> edge_permutation;
    std::vector<int> edge_orientation;
    int coord_slice_sorted(std::vector<int> edges);
public:
    Cube();
    Cube(std::vector<int> corner_perm, std::vector<int> corner_orient,
         std::vector<int> edge_perm,   std::vector<int> edge_orient);
    Cube perform_move(int move);
    int coord_corner_orientation();
    int coord_edge_orientation();
    int coord_corner_permutation();
    int coord_ud_sorted();
    int coord_rl_sorted();
    int coord_fb_sorted();
    static int edge_permutation_calc(int rl_sorted, int fb_sorted);
    static int ud_unsorted_calc(int ud_sorted);
    static int ud_permutation_calc(int ud_sorted);
    int coord_edge_permutation();
    int coord_ud_unsorted();
    int coord_ud_permutation();
};

#endif
