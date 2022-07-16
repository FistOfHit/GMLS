#include "../includes/src_includes/arithmetic.h"
#include "../includes/src_includes/multigrid_cycles.h"
#include "../includes/src_includes/reshapers.h"
#include "../includes/src_includes/smoothers.h"
#include <math.h>
#include <map>
#include <memory>
#include <vector>


using vector = std::vector<float>;


// Pre-determined depths for intermediate V-cycles to form the "W" in W-cycle
static std::vector<int> w_cycle_intermediate_depths = std::vector<int>{
    1, 2, 1,
    3, 1, 2, 1,
    4, 1, 2, 1, 3, 1, 2, 1,
    5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
};


void v_cycle(vector &a, vector &x, vector &b, vector &r, vector&e, 
    const int num_grids, const int num_iterations) {
    /* Perform one V-cycle iteration on a series of grids.

    Notes
    -----
    A V-cycle iteration is a single iteration of solving an Ax=b system by 
    using matrix/vector restriction (downsampling, downscaling, reduction 
    etc.), interpolation (upsampling, upscaling, refinement etc.) and smoothing
    (gradually nudging a solution approximation towards a more accuracte
    result). 

    The core-concepts of multi-grid methods are that smoothing iterations are
    also performed on coarser grids to:
    1) reduce the total computational cost by performing smoothing on grids
        with less elements in them
    2) accelerate the elimination of low-frequency errors on the fine-grid, as
        they become high-frequency errors on coarser grids (smoothers are good
        at reducing high-frequency errors)
    
    In particular, the "V" in V-cycle comes from the fact that the pattern in
    which restriction and interpolation happen form a V-shape:
    
    Fine-grid problem         Fine-grid soluation approximation
             \                     /
         Restriction          Interpolation
                \               /
                Lowest grid level
    
    For more information, please refer to:
    - https://en.wikipedia.org/wiki/Multigrid_method
    - https://math.mit.edu/classes/18.086/2006/am63.pdf
    Which are just a few of very useful sources out there on practical
    implementations of multi-grid methods

    Parameters
    ----------
    std::vector<float> &a:
        LHS n x m matrix A in Ax=b
    std::vector<float> &x:
        m-length Solution vector x in Ax=b
    std::vector<float> &b:
        n-length RHS vector b in Ax=b
    std::vector<float> &r:
        m-length residual vector for storing the values of b - Ax', where x' is
        some intermediate/approximation of x
    std::vector<float> &e:
        m-length error vector e for solving Ae=r, and storing the error values
        to correct x with
    const int num_grids:
        The number of grids to be used in this multigrid cycle
    const int num_iterations (default = 3):
        The number of iterations to apply smoothers whenever required during
        the cycle
    */

    // Get dimensions of A from x and b
    const auto num_rows = x.size();
    const auto num_cols = b.size();

    // Restrict down to coarsest mesh
    vector temp = vector(x);
    for (auto grid_depth = 0; grid_depth < num_grids - 1; grid_depth++) {
        // Presmooth x at finer level
        sor_smooth(a, x, b, grid_depth, num_iterations);

        // Find the current residual
        multiply(a, num_rows, num_cols, x, grid_depth, temp);
        subtract(b, temp, grid_depth, r);

        // Restrict residual (and LHS matrix)
        restrict_vector(r, grid_depth);
        restrict_matrix(a, grid_depth);

        // Solve on coarser meshes Ae=r
        sor_smooth(a, e, r, grid_depth + 1, num_iterations);
    }

    // Interpolate up to finest mesh
    for (auto grid_depth = num_grids; grid_depth >= 0; grid_depth--) {
        // Map the correction from the coarse grid we just found to a finer mesh
        interpolate_vector(e, grid_depth);
        add(x, e, grid_depth, x);

        // Apply a post-smoother to Ax=b
        interpolate_matrix(a, grid_depth);
        sor_smooth(a, x, b, grid_depth, num_iterations);
    }
}


void w_cycle(vector &a, vector &x, vector &b, vector &r, vector&e, 
    const int num_grids, const int num_iterations) {
    /* Perform one W-cycle iteration on a series of grids.

    Notes
    -----
    A W-cycle iteration is a single iteration of solving an Ax=b system by 
    using matrix/vector restriction (downsampling, downscaling, reduction 
    etc.), interpolation (upsampling, upscaling, refinement etc.) and smoothing
    (gradually nudging a solution approximation towards a more accuracte
    result). 

    The core-concepts of multi-grid methods are that smoothing iterations are
    also performed on coarser grids to:
    1) reduce the total computational cost by performing smoothing on grids
        with less elements in them
    2) accelerate the elimination of low-frequency errors on the fine-grid, as
        they become high-frequency errors on coarser grids (smoothers are good
        at reducing high-frequency errors)
    
    In particular, the "W" in W-cycle comes from the fact that the pattern in
    which restriction and interpolation happen form a W-shape:

    Fine-grid problem                          Fine-grid solution approximation
           \                                            /
         Restriction  Intermediate grid level      Interpolation
             \            /              \            /
             Lowest grid level          Lowest grid level
    
    In practice, there are many more grid levels used when applying
    multi-grid methods, and the exact shape of the intermediate cycles forming
    the W will change.

    For more information, please refer to:
    - https://en.wikipedia.org/wiki/Multigrid_method
    - https://math.mit.edu/classes/18.086/2006/am63.pdf
    Which are just a few of very useful sources out there on practical
    implementations of multi-grid methods

    Parameters
    ----------
    std::vector<float> &a:
        LHS n x m matrix A in Ax=b
    std::vector<float> &x:
        m-length Solution vector x in Ax=b
    std::vector<float> &b:
        n-length RHS vector b in Ax=b
    std::vector<float> &r:
        m-length residual vector for storing the values of b - Ax', where x' is
        some intermediate/approximation of x
    std::vector<float> &e:
        m-length error vector e for solving Ae=r, and storing the error values
        to correct x with
    const int num_grids:
        The number of grids to be used in this multigrid cycle
    const int num_iterations (default = 3):
        The number of iterations to apply smoothers whenever required during
        the cycle
    */

    // Get dimensions of A from x and b
    const auto num_rows = x.size();
    const auto num_cols = b.size();

    // Restrict down to coarsest mesh
    vector temp = vector(x);
    for (auto grid_depth = 0; grid_depth < num_grids - 1; grid_depth++) {
        // Presmooth x at finer level
        sor_smooth(a, x, b, grid_depth, num_iterations);

        // Find the current residual
        multiply(a, num_rows, num_cols, x, grid_depth, temp);
        subtract(b, temp, grid_depth, r);

        // Restrict residual (and LHS matrix)
        restrict_vector(r, grid_depth);
        restrict_matrix(a, grid_depth);

        // Solve on coarser meshes Ae=r
        sor_smooth(a, e, r, grid_depth + 1, num_iterations);
    }

    // V-cycle repeatedly at varying depths to form the W-cycle
    const auto num_intermediate_cycles = std::pow(2, num_grids) - 1;
    for (auto i = 0; i < num_intermediate_cycles; i++) {
        v_cycle(a, x, b, r, e,  w_cycle_intermediate_depths[i], num_iterations);
    }

    // Interpolate up to finest mesh
    for (auto grid_depth = num_grids; grid_depth >= 0; grid_depth--) {
        // Interpolate the error and use it to correct x
        interpolate_vector(e, grid_depth);
        add(x, e, grid_depth, x);

        // Apply a post-smoother to Ax=b
        interpolate_matrix(a, grid_depth);
        sor_smooth(a, x, b, grid_depth, num_iterations);
    }
}
