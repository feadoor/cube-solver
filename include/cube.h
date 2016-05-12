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
enum cube_face_t {FACE_U, FACE_L, FACE_F, FACE_R, FACE_B, FACE_D};
enum cube_turn_t {TURN_CW = 1, TURN_2, TURN_CCW};

enum             {EDGE_UF, EDGE_UL, EDGE_UB, EDGE_UR, 
                  EDGE_FR, EDGE_FL, EDGE_BL, EDGE_BR,
                  EDGE_DF, EDGE_DL, EDGE_DB, EDGE_DR};
enum             {CORNER_URF, CORNER_UFL, CORNER_ULB, CORNER_UBR, 
                  CORNER_DFR, CORNER_DLF, CORNER_DBL, CORNER_DRB};
enum             {TWIST_NONE, TWIST_CW, TWIST_CCW};
enum             {FLIP_NONE, FLIP_FLIP};

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
    void perform_move(cube_face_t face, cube_turn_t turn_dir);
    int coord_corner_orientation();
    int coord_edge_orientation();
    int coord_corner_permutation();
    int coord_ud_sorted();
    int coord_rl_sorted();
    int coord_fb_sorted();
};

#endif
