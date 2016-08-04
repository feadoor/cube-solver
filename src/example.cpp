#include <iostream>
#include <vector>

#include <cube.h>
#include <cubephase.h>
#include <cubetables.h>
#include <cubesolver.h>

// Example of how to solve a cube using this code.
int main()
{
    // Common initialisation that must be done at startup.
    std::cout << "Initialising..." << std::endl;
    cube_create_allowed_moves();
    std::cout << "Generating transition tables..." << std::endl;
    cube_fill_all_trans_tables();
    std::cout << "Generating pruning tables..." << std::endl;
    cube_fill_all_pruning_tables();

    // The state of the cube that should be solved. The various vectors are
    // defined as follows:
    //
    // corner_perm - The permutation of the corners of the cube. If, for
    //               example, CORNER_URF is in the position that should be
    //               occupied by CORNER_DBL, then we would have it so that
    //               corner_perm[CORNER_DBL] = CORNER_URF, and so on.
    //
    // edge_perm - The permutation of the edges of the cube. If, for
    //             example, EDGE_FL is in the position that should be
    //             occupied by EDGE_UB, then we would have it so that
    //             edge_perm[EDGE_UB] = EDGE_FL, and so on.
    //
    // corner_orient - The orientation of the corners of the cube. If, for
    //                 example, the corner currently located in the position
    //                 where CORNER_ULB normally resides has been twisted
    //                 one twist clockwise, then we set it up so that
    //                 corner_orient[CORNER_ULB] = TWIST_CW.
    //
    // edge_orient - The orientation of the edges of the cube. If, for
    //               example, the edge currently located in the position
    //               where EDGE_UR normally resides has been flipped, then
    //               we set edge_orient[EDGE_UR] = FLIP_FLIP.
    std::vector<int> corner_perm = {CORNER_UBR, CORNER_DRB, CORNER_DBL,
                                    CORNER_DLF, CORNER_URF, CORNER_UFL,
                                    CORNER_DFR, CORNER_ULB};
    std::vector<int> corner_orient = {TWIST_CW, TWIST_CCW, TWIST_CW,
                                      TWIST_NONE, TWIST_NONE, TWIST_CCW,
                                      TWIST_CCW, TWIST_CW};
    std::vector<int> edge_perm = {EDGE_FR, EDGE_FL, EDGE_BR, EDGE_UL, EDGE_DB,
                                  EDGE_DL, EDGE_UR, EDGE_DF, EDGE_BL, EDGE_UB,
                                  EDGE_UF, EDGE_DR};
    std::vector<int> edge_orient = {FLIP_NONE, FLIP_NONE, FLIP_FLIP,
                                    FLIP_FLIP, FLIP_FLIP, FLIP_NONE,
                                    FLIP_FLIP, FLIP_NONE, FLIP_NONE,
                                    FLIP_NONE, FLIP_NONE, FLIP_NONE};

    Cube scrambled_cube(corner_perm, corner_orient, edge_perm, edge_orient);
    CubeSolver solver(scrambled_cube);

    std::cout << "Solving..." << std::endl << std::endl;
    solver.solve();

    return 0;
}
