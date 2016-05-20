/******************************************************************************
* File:    cubephase.cpp
*
* Purpose: Definitions of constants which determine the moves allowed in each
*          phase of the two-phase algorithm.
******************************************************************************/

/******************************************************************************
* Dependencies
******************************************************************************/
#include <vector>

#include <cube.h>

/******************************************************************************
* Allowed moves initial definitions
******************************************************************************/
std::vector<std::vector<int>> cube_p1_allowed_moves(NUM_MOVES + 1);
std::vector<std::vector<int>> cube_p2_allowed_moves(NUM_MOVES + 1);

/******************************************************************************
* Implementation of functions which fill the allowed moves vectors
******************************************************************************/

/******************************************************************************
* Function:  cube_create_p1_allowed_moves
*
* Purpose:   Fill in the allowed moves for phase 1.
*
* Params:    None.
*
* Returns:   Nothing.
*
* Operation: In phase 1, any move is allowed, but not every move is allowed to
*            follow every other move. In particular, no face can be turned
*            twice in a row, and, since RL = LR, FB = BF, UD = DU, we do not
*            allow a turn of the R face to follow a turn of the L face, or a
*            turn of the F face to follow a turn of the B face, or a turn of
*            the U face to follow a turn of the D face.
******************************************************************************/
void cube_create_p1_allowed_moves()
{
    cube_p1_allowed_moves[MOVE_U]    = {MOVE_L,  MOVE_L2, MOVE_LP, MOVE_F,
                                        MOVE_F2, MOVE_FP, MOVE_R,  MOVE_R2,
                                        MOVE_RP, MOVE_B,  MOVE_B2, MOVE_BP,
                                        MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_U2]   = {MOVE_L,  MOVE_L2, MOVE_LP, MOVE_F,
                                        MOVE_F2, MOVE_FP, MOVE_R,  MOVE_R2,
                                        MOVE_RP, MOVE_B,  MOVE_B2, MOVE_BP,
                                        MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_UP]   = {MOVE_L,  MOVE_L2, MOVE_LP, MOVE_F,
                                        MOVE_F2, MOVE_FP, MOVE_R,  MOVE_R2,
                                        MOVE_RP, MOVE_B,  MOVE_B2, MOVE_BP,
                                        MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_L]    = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_F,
                                        MOVE_F2, MOVE_FP, MOVE_B,  MOVE_B2,
                                        MOVE_BP, MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_L2]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_F,
                                        MOVE_F2, MOVE_FP, MOVE_B,  MOVE_B2,
                                        MOVE_BP, MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_LP]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_F,
                                        MOVE_F2, MOVE_FP, MOVE_B,  MOVE_B2,
                                        MOVE_BP, MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_F]    = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L,
                                        MOVE_L2, MOVE_LP, MOVE_R,  MOVE_R2,
                                        MOVE_RP, MOVE_B,  MOVE_B2, MOVE_BP,
                                        MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_F2]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L,
                                        MOVE_L2, MOVE_LP, MOVE_R,  MOVE_R2,
                                        MOVE_RP, MOVE_B,  MOVE_B2, MOVE_BP,
                                        MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_FP]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L,
                                        MOVE_L2, MOVE_LP, MOVE_R,  MOVE_R2,
                                        MOVE_RP, MOVE_B,  MOVE_B2, MOVE_BP,
                                        MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_R]    = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L,
                                        MOVE_L2, MOVE_LP, MOVE_F,  MOVE_F2,
                                        MOVE_FP, MOVE_B,  MOVE_B2, MOVE_BP,
                                        MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_R2]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L,
                                        MOVE_L2, MOVE_LP, MOVE_F,  MOVE_F2,
                                        MOVE_FP, MOVE_B,  MOVE_B2, MOVE_BP,
                                        MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_RP]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L,
                                        MOVE_L2, MOVE_LP, MOVE_F,  MOVE_F2,
                                        MOVE_FP, MOVE_B,  MOVE_B2, MOVE_BP,
                                        MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_B]    = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L,
                                        MOVE_L2, MOVE_LP, MOVE_R,  MOVE_R2,
                                        MOVE_RP, MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_B2]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L,
                                        MOVE_L2, MOVE_LP, MOVE_R,  MOVE_R2,
                                        MOVE_RP, MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_BP]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L,
                                        MOVE_L2, MOVE_LP, MOVE_R,  MOVE_R2,
                                        MOVE_RP, MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p1_allowed_moves[MOVE_D]    = {MOVE_L,  MOVE_L2, MOVE_LP, MOVE_F,
                                        MOVE_F2, MOVE_FP, MOVE_R,  MOVE_R2,
                                        MOVE_RP, MOVE_B,  MOVE_B2, MOVE_BP};

    cube_p1_allowed_moves[MOVE_D2]   = {MOVE_L,  MOVE_L2, MOVE_LP, MOVE_F,
                                        MOVE_F2, MOVE_FP, MOVE_R,  MOVE_R2,
                                        MOVE_RP, MOVE_B,  MOVE_B2, MOVE_BP};

    cube_p1_allowed_moves[MOVE_DP]   = {MOVE_L,  MOVE_L2, MOVE_LP, MOVE_F,
                                        MOVE_F2, MOVE_FP, MOVE_R,  MOVE_R2,
                                        MOVE_RP, MOVE_B,  MOVE_B2, MOVE_BP};

    cube_p1_allowed_moves[NUM_MOVES] = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L,
                                        MOVE_L2, MOVE_LP, MOVE_F,  MOVE_F2,
                                        MOVE_FP, MOVE_R,  MOVE_R2, MOVE_RP,
                                        MOVE_B,  MOVE_B2, MOVE_BP, MOVE_D,
                                        MOVE_D2, MOVE_DP};
}

/******************************************************************************
* Function:  cube_create_p2_allowed_moves
*
* Purpose:   Fill in the allowed moves for phase 2.
*
* Params:    None.
*
* Returns:   Nothing.
*
* Operation: In phase 2, one half turns of R, L, F, B are allowed, but not 
*            every move is allowed to follow every other move. In particular, 
*            no face can be turned twice in a row, and, since RL = LR, FB = BF,
*            UD = DU, we do not allow a turn of the R face to follow a turn of
*            the L face, or a turn of the F face to follow a turn of the B 
*            face, or a turn of the U face to follow a turn of the D face.
******************************************************************************/
void cube_create_p2_allowed_moves()
{
    cube_p2_allowed_moves[MOVE_U]    = {MOVE_L2, MOVE_F2, MOVE_R2, MOVE_B2,
                                        MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p2_allowed_moves[MOVE_U2]   = {MOVE_L2, MOVE_F2, MOVE_R2, MOVE_B2,
                                        MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p2_allowed_moves[MOVE_UP]   = {MOVE_L2, MOVE_F2, MOVE_R2, MOVE_B2,
                                        MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p2_allowed_moves[MOVE_L]    = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_F2,
                                        MOVE_B2, MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p2_allowed_moves[MOVE_L2]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_F2,
                                        MOVE_B2, MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p2_allowed_moves[MOVE_LP]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_F2,
                                        MOVE_B2, MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p2_allowed_moves[MOVE_F]    = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L2,
                                        MOVE_R2, MOVE_B2, MOVE_D,  MOVE_D2, 
                                        MOVE_DP};

    cube_p2_allowed_moves[MOVE_F2]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L2,
                                        MOVE_R2, MOVE_B2, MOVE_D,  MOVE_D2, 
                                        MOVE_DP};

    cube_p2_allowed_moves[MOVE_FP]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L2,
                                        MOVE_R2, MOVE_B2, MOVE_D,  MOVE_D2, 
                                        MOVE_DP};

    cube_p2_allowed_moves[MOVE_R]    = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L2,
                                        MOVE_F2, MOVE_B2, MOVE_D,  MOVE_D2, 
                                        MOVE_DP};

    cube_p2_allowed_moves[MOVE_R2]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L2,
                                        MOVE_F2, MOVE_B2, MOVE_D,  MOVE_D2, 
                                        MOVE_DP};

    cube_p2_allowed_moves[MOVE_RP]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L2,
                                        MOVE_F2, MOVE_B2, MOVE_D,  MOVE_D2, 
                                        MOVE_DP};

    cube_p2_allowed_moves[MOVE_B]    = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L2,
                                        MOVE_R2, MOVE_D,  MOVE_D2, MOVE_DP};
 
    cube_p2_allowed_moves[MOVE_B2]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L2,
                                        MOVE_R2, MOVE_D,  MOVE_D2, MOVE_DP};
 
    cube_p2_allowed_moves[MOVE_BP]   = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L2,
                                        MOVE_R2, MOVE_D,  MOVE_D2, MOVE_DP};

    cube_p2_allowed_moves[MOVE_D]    = {MOVE_L2, MOVE_F2, MOVE_R2, MOVE_B2};

    cube_p2_allowed_moves[MOVE_D2]   = {MOVE_L2, MOVE_F2, MOVE_R2, MOVE_B2};

    cube_p2_allowed_moves[MOVE_DP]   = {MOVE_L2, MOVE_F2, MOVE_R2, MOVE_B2};

    cube_p2_allowed_moves[NUM_MOVES] = {MOVE_U,  MOVE_U2, MOVE_UP, MOVE_L2,
                                        MOVE_F2, MOVE_R2, MOVE_B2, MOVE_D,
                                        MOVE_D2, MOVE_DP};
}

/******************************************************************************
* Function:  cube_create_allowed_moves
*
* Purpose:   Fill in the allowed moves vectors for both phases.
*
* Params:    None
*
* Returns:   Nothing.
*
* Operation: Calls into functions responsible for filling in the vector for
*            each phase separately.
******************************************************************************/
void cube_create_allowed_moves()
{
    cube_create_p1_allowed_moves();
    cube_create_p2_allowed_moves();
}
