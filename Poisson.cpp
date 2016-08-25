/*
 * Poisson.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: Jean23
 */

#include "Poisson.h"

int poisson(int n,
                 std::vector<int> &ptr,
                 std::vector<int> &col,
                 std::vector<double> &val,
                 std::vector<double> &rhs,double h)
{
    //double h = 1.0 / (n - 1);
    int n2 = n * n; // Number of points in the grid.
    // Grid spacing.
    ptr.clear(); ptr.reserve(n2 + 1); ptr.push_back(0);
    col.clear(); col.reserve(n2 * 5); // We use 5-point stencil, so the matrix
    val.clear(); val.reserve(n2 * 5); // will have at most n2 * 5 nonzero elements.
    rhs.resize(n2);




    int max = n2; //UNUSED VARIABLE



    for(int j = 0, k = 0; j < n; ++j) {
        for(int i = 0; i < n; ++i) {
            // Interior point. Use 5-point finite difference stencil.
            if ((k-n)>=(j-1)*n && (k-n)>=0){
                col.push_back(k - n);
                val.push_back(-1.0 / (h * h));
            }
            if ((k-1)>=j*n){
                col.push_back(k - 1);
                val.push_back(-1.0 / (h * h));
            }
            col.push_back(k);
            val.push_back(4.0 / (h * h));
            if ((k+1)<((j+1)*n)){
                col.push_back(k + 1);
                val.push_back(-1.0 / (h * h));
            }
            if ((k+n)<((j+2)*n) && (k+n)<n2){
                col.push_back(k + n);
                val.push_back(-1.0 / (h * h));
            }
            rhs[k] = 1.0;
            ++k;

            ptr.push_back(col.size());
        }
    }
    return n2;
}



// Assembles matrix for Poisson's equation with homogeneous
// boundary conditions on a n x n grid.
// Returns number of rows in the assembled matrix.
// The matrix is returned in the CRS components ptr, col, and val.
// The right-hand side is returned in rhs.
//int poisson(
//    int n,
//    std::vector<int>    &ptr,
//    std::vector<int>    &col,
//    std::vector<double> &val,
//    std::vector<double> &rhs
//    )
//{
//    int    n2 = n * n;        // Number of points in the grid.
//    double h = 1.0 / (n - 1); // Grid spacing.
//
//    ptr.clear(); ptr.reserve(n2 + 1); ptr.push_back(0);
//    col.clear(); col.reserve(n2 * 5); // We use 5-point stencil, so the matrix
//    val.clear(); val.reserve(n2 * 5); // will have at most n2 * 5 nonzero elements.
//
//    rhs.resize(n2);
//
//    for(int j = 0, k = 0; j < n; ++j) {
//        for(int i = 0; i < n; ++i, ++k) {
//            if (i == 0 || i == n - 1 || j == 0 || j == n - 1) {
//                // Boundary point. Use Dirichlet condition.
//                col.push_back(k);
//                val.push_back(1.0);
//
//                rhs[k] = 0.0;
//            } else {
//                // Interior point. Use 5-point finite difference stencil.
//                col.push_back(k - n);
//                val.push_back(-1.0 / (h * h));
//
//                col.push_back(k - 1);
//                val.push_back(-1.0 / (h * h));
//
//                col.push_back(k);
//                val.push_back(4.0 / (h * h));
//
//                col.push_back(k + 1);
//                val.push_back(-1.0 / (h * h));
//
//                col.push_back(k + n);
//                val.push_back(-1.0 / (h * h));
//
//                rhs[k] = 1.0;
//            }
//
//            ptr.push_back(col.size());
//        }
//    }
//
//    return n2;
//}
