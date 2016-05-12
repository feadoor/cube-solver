/******************************************************************************
* File:    cube.cpp
*
* Purpose: Implements the Rubik's cube at the cubie level, and provides
*          translation to the coordinates required for the two-phase Kociemba
*          algorithm to run.
*******************************************************************************

/******************************************************************************
* Includes
******************************************************************************/
#include <algorithm>
#include <vector>
#include <cube.h>

/******************************************************************************
* Cube class implementation
******************************************************************************/

/******************************************************************************
* Function:  Cube::Cube
*
* Purpose:   Instantiates a representation of a Rubik's cube at the cubie level
*
* Params:    None
*
* Returns:   Nothing
*
* Operation: Initialises the cube in the solved state.
******************************************************************************/
Cube::Cube()
{
    corner_permutation = {0, 1, 2, 3, 4, 5, 6, 7};
    corner_orientation = {0, 0, 0, 0, 0, 0, 0, 0};
    edge_permutation   = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    edge_orientation   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0};
}

/******************************************************************************
* Function:  Cube::perform_move
*
* Purpose:   Performs a move on this CUbe object
*
* Params:    face     - which face is being rotated
*            turn_dir - is this turn cw, ccw or 180 degrees?
*
* Returns:   Nothing
*
* Operation: Update the permutation and orientation of all the pieces according
*            to the particular move being performed.
******************************************************************************/
void Cube::perform_move(cube_face_t face, cube_turn_t turn_dir)
{
    // Local variables
    std::vector<int> corners_moved;
    std::vector<int> edges_moved;
    std::vector<int> corner_twist;
    std::vector<int> edge_flip;

    // Set up new vectors in which to hold the result of the move having been
    // performed
    std::vector<int> new_corner_permutation = corner_permutation;
    std::vector<int> new_corner_orientation = corner_orientation;
    std::vector<int> new_edge_permutation = edge_permutation;
    std::vector<int> new_edge_orientation = edge_orientation;

    // Switch based on the face being turned to determine which corners and
    // edges are permuted by this move and how the orientations of the pieces
    // are affected.
    switch (face)
    {
        case FACE_U:
            corners_moved = {CORNER_URF, CORNER_UFL, CORNER_ULB, CORNER_UBR};
            edges_moved   = {EDGE_UF, EDGE_UL, EDGE_UB, EDGE_UR};
            corner_twist  = {TWIST_NONE, TWIST_NONE, TWIST_NONE, TWIST_NONE};
            edge_flip     = {FLIP_NONE, FLIP_NONE, FLIP_NONE, FLIP_NONE};
            break;

        case FACE_L:
            corners_moved = {CORNER_UFL, CORNER_DLF, CORNER_DBL, CORNER_ULB};
            edges_moved   = {EDGE_UL, EDGE_FL, EDGE_DL, EDGE_BL};
            corner_twist  = {TWIST_CCW, TWIST_CW, TWIST_CCW, TWIST_CW};
            edge_flip     = {FLIP_NONE, FLIP_NONE, FLIP_NONE, FLIP_NONE};
            break;

        case FACE_F:
            corners_moved = {CORNER_URF, CORNER_DFR, CORNER_DLF, CORNER_UFL};
            edges_moved   = {EDGE_UF, EDGE_FR, EDGE_DF, EDGE_FL};
            corner_twist  = {TWIST_CCW, TWIST_CW, TWIST_CCW, TWIST_CW};
            edge_flip     = {FLIP_FLIP, FLIP_FLIP, FLIP_FLIP, FLIP_FLIP};
            break;

        case FACE_R:
            corners_moved = {CORNER_URF, CORNER_UBR, CORNER_DRB, CORNER_DFR};
            edges_moved   = {EDGE_UR, EDGE_BR, EDGE_DR, EDGE_FR};
            corner_twist  = {TWIST_CW, TWIST_CCW, TWIST_CW, TWIST_CCW};
            edge_flip     = {FLIP_NONE, FLIP_NONE, FLIP_NONE, FLIP_NONE};
            break;

        case FACE_B:
            corners_moved = {CORNER_UBR, CORNER_ULB, CORNER_DBL, CORNER_DRB};
            edges_moved   = {EDGE_UB, EDGE_BL, EDGE_DB, EDGE_BR};
            corner_twist  = {TWIST_CW, TWIST_CCW, TWIST_CW, TWIST_CCW};
            edge_flip     = {FLIP_FLIP, FLIP_FLIP, FLIP_FLIP, FLIP_FLIP};
            break;

        case FACE_D:
            corners_moved = {CORNER_DFR, CORNER_DRB, CORNER_DBL, CORNER_DLF};
            edges_moved   = {EDGE_DF, EDGE_DR, EDGE_DB, EDGE_DL};
            corner_twist  = {TWIST_NONE, TWIST_NONE, TWIST_NONE, TWIST_NONE};
            edge_flip     = {FLIP_NONE, FLIP_NONE, FLIP_NONE, FLIP_NONE};
            break;
    }

    // Update the corner permutation and orientation
    for (int ii = 0; ii < corners_moved.size(); ++ii)
    {
        // Permute the corners according to how far we turned the face
        int from = corners_moved[ii];
        int to   = corners_moved[(ii + turn_dir) % corners_moved.size()];
        new_corner_permutation[to] = corner_permutation[from];

        // Calculate the total twist for this corner piece and update it
        int twist = 0;
        for (int jj = 0; jj < turn_dir; ++jj)
        {
            twist += corner_twist[(ii + jj) % corners_moved.size()];
        }
        new_corner_orientation[to] = (corner_orientation[from] + twist) % 3;
    }

    // Update the edge permutation and orientation
    for (int ii = 0; ii < edges_moved.size(); ++ii)
    {
        // Permute the edges according to how far we turned the face
        int from = edges_moved[ii];
        int to   = edges_moved[(ii + turn_dir) % edges_moved.size()];
        new_edge_permutation[to] = from;

        // Calculate the total flip for this edge piece and update it
        int flip = 0;
        for (int jj = 0; jj < turn_dir; ++jj)
        {
            flip += edge_flip[(ii + jj) % edges_moved.size()];
        }
        new_edge_orientation[to] = (edge_orientation[from] + flip) % 2;
    }

    // Replace the old permutations and orientations with the new ones
    corner_permutation = new_corner_permutation;
    corner_orientation = new_corner_orientation;
    edge_permutation   = new_edge_permutation;
    edge_orientation   = new_edge_orientation;
}

/******************************************************************************
* Function:  Cube::coord_corner_orientation
*
* Purpose:   Extract the corner orientation coordinate from the current cube
*            position.
*
* Params:    None
*
* Returns:   The value of the corner orientation coordinate.
*
* Operation: Calculates the value of the corner orientation coordinate by
*            combining the twist of each individual corner piece into a single
*            integer result using a ternary encoding.
******************************************************************************/
int Cube::coord_corner_orientation()
{
    // Interpret the corner orientation vector as a base-3 number to get the
    // value of this coordinate
    int ret = 0;
    for (int ii = 0; ii < corner_orientation.size(); ++ii)
    {
        ret = (3 * ret + corner_orientation[ii]);
    }
    return ret;
}

/******************************************************************************
* Function:  Cube::coord_edge_orientation
*
* Purpose:   Extract the edge orientation coordinate from the current cube
*            position.
*
* Params:    None
*
* Returns:   The value of the edge orientation coordinate.
*
* Operation: Calculates the value of the edge orientation coordinate by
*            combining the flip of each individual corner piece into a single
*            integer result using a binary encoding.
******************************************************************************/
int Cube::coord_edge_orientation()
{
    // Interpret the edge orientation vector as a base-2 number to get the
    // value of this coordinate
    int ret = 0;
    for (int ii = 0; ii < edge_orientation.size(); ++ii)
    {
        ret = (2 * ret + edge_orientation[ii]);
    }
    return ret;
}

/******************************************************************************
* Function:  Cube::coord_corner_permutation
*
* Purpose:   Extract the corner permutation coordinate from the current cube
*            position.
*
* Params:    None.
*
* Returns:   The value of the corner permutation coordinate.
*
* Operation: Calculates the value of the corner permutation coordinate by
*            working out the lexicographic position of the vector which
*            represents the corner permutation.
******************************************************************************/
int Cube::coord_corner_permutation()
{
    // Local variable to keep track of value of factorials
    int factorial = 1;

    // Calculate the lexicographic position of the permutation represented by
    // the vector corner_permutation - for each element of the permutation,
    // work out how many elements following it have a lower value, and use
    // these numbers as the coefficients of some factorials.
    int ret = 0;
    for (int ii = corner_permutation.size() - 1; ii >= 0; --ii)
    {
        int low_count = 0;
        for (int jj = ii + 1; jj < corner_permutation.size(); ++jj)
        {
            if (corner_permutation[jj] < corner_permutation[ii])
            {
                ++low_count;
            }
        }
        ret += low_count * factorial;
        factorial *= corner_permutation.size() - ii;
    }
    return ret;
}

/******************************************************************************
* Function:  Cube::coord_slice_sorted
*
* Purpose:   Given a particular slice of edges, extract the associated sorted
*            slice coordinate from the current cube position.
*
* Params:    None.
*
* Returns:   The value of the sorted slice coordinate.
*
* Operation: Calculates the lexicographic position x of the set of 4 positions
*            occupied by the four slice edges, and also the lexicographic
*            position y of the permutation of these 4 edges among themselves,
*            and calculates the coordinate as 24x + y.
******************************************************************************/
int Cube::coord_slice_sorted(std::vector<int> edges)
{
    // Local variables n, k.
    int n = edge_permutation.size() - 1;
    int k = edges.size();

    // Local variable binom which represents the value of (n choose k), and
    // which will be updated alongside n and k as we progress.
    int binom = 1;
    for (int ii = 1; ii <= k; ++ii)
    {
        binom *= (n - ii + 1);
        binom /= ii;
    }

    // The order in which the edges making up this slice appear in the current
    // cube position.
    std::vector<int> order = {};

    // Calculate the lexicographic position of the four positions occupied by
    // the slice edges.
    int pos = 0;
    while (k >= 0)
    {
        int curr_edge = edge_permutation[n];
        if (std::find(edges.begin(), edges.end(), curr_edge) != edges.end())
        {
            // We've found one of the edges, so update the values of k and of
            // the binomial coefficient
            binom *= k--;
            binom /= (n - k);

            // Store the edge so we know the order in which they appear in the
            // cube.
            order.push_back(curr_edge);
        }
        else
        {
            // Add on the current binomial coeffcient to the value
            pos += binom;
        }

        // Update the values of n and the binomial coeffcient
        binom *= (n - k);
        binom /= n--;
    }

    // Now calculate the lexicographic position of the permutation of the four
    // edges among themselves
    int perm = 0; int factorial = 1;
    for (int ii = order.size() - 1; ii >= 0; --ii)
    {
        int high_count = 0;
        for (int jj = ii + 1; jj < order.size(); ++jj)
        {
            if (order[jj] > order[ii])
            {
                ++high_count;
            }
        }
        perm += high_count * factorial;
        factorial *= (order.size() - ii);
    }

    // Return the combination of these two data which makes the coordinate
    return 24 * pos + perm;
}

/******************************************************************************
* Function:  Cube::coord_ud_sorted
*
* Purpose:   Extracts the value of the sorted UD-slice coordinate fromt the
*            current cube position.
*
* Params:    None.
*
* Returns:   The value of the sorted UD-slice coordinate.
*
* Operation: Calls into coord_slice_sorted with a specific set of edges for
*            the UD-slice.
******************************************************************************/
int Cube::coord_ud_sorted()
{
    std::vector<int> edges = {EDGE_FR, EDGE_FL, EDGE_BL, EDGE_BR};
    return coord_slice_sorted(edges);
}

/******************************************************************************
* Function:  Cube::coord_rl_sorted
*
* Purpose:   Extracts the value of the sorted RL-slice coordinate fromt the
*            current cube position.
*
* Params:    None.
*
* Returns:   The value of the sorted RL-slice coordinate.
*
* Operation: Calls into coord_slice_sorted with a specific set of edges for
*            the RL-slice.
******************************************************************************/
int Cube::coord_rl_sorted()
{
    std::vector<int> edges = {EDGE_UF, EDGE_UB, EDGE_DB, EDGE_DF};
    return coord_slice_sorted(edges);
}

/******************************************************************************
* Function:  Cube::coord_fb_sorted
*
* Purpose:   Extracts the value of the sorted FB-slice coordinate fromt the
*            current cube position.
*
* Params:    None.
*
* Returns:   The value of the sorted FB-slice coordinate.
*
* Operation: Calls into coord_slice_sorted with a specific set of edges for
*            the -slice.
******************************************************************************/
int Cube::coord_fb_sorted()
{
    std::vector<int> edges = {EDGE_UR, EDGE_UL, EDGE_DL, EDGE_DR};
    return coord_slice_sorted(edges);
}

int main()
{
    return 0;
}