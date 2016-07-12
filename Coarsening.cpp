/*
 * Coarsening.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: Jean23
 */



#include "Coarsening.h"


int createCoarse( int size,
                             std::vector<int>    &ptr,
                             std::vector<int>    &col,
                             std::vector<double> &val)
{
    int max= (size-2)*(size-2);
    int grootte = size-2;   // Number of points in the grid.
    int size2= size*size;
    ptr.clear(); ptr.reserve(size2 + 1); ptr.push_back(0);
    col.clear(); col.reserve(size2 * 5); // We use 5-point stencil, so the matrix
    val.clear(); val.reserve(size2 * 5); // will have at most n2 * 5 nonzero elements.


    for(int j = 0,k=grootte+1; j< (grootte-1)/2; ++j) {
        for(int i = 0; i < (grootte-1)/2;++i) {
            // Interior point. Use 5-point finite difference stencil.
            if(k-grootte-1>=0){
                col.push_back(k - grootte -1);
                val.push_back(1.0 / 16.0);
            }
            if(k-grootte>=0 ){
                col.push_back(k - grootte);
                val.push_back(2.0 / 16.0);
            }
            if(k-grootte+1>=0 ){
                col.push_back(k - grootte +1);
                val.push_back(1.0 / 16.0);
            }
            if(k-1>=j*grootte ){
                col.push_back(k - 1);
                val.push_back(2.0/ 16.0);
            }
            col.push_back(k);
            val.push_back(4.0/ 16.0);

            if (k+1<(j+1)*grootte){
                col.push_back(k + 1);
                val.push_back(2.0/ 16.0);
            }

            if (k+grootte-1<max ){
                col.push_back(k + grootte -1);
                val.push_back(1.0 / 16.0);
            }
            if (k+grootte<max ){
                col.push_back(k + grootte);
                val.push_back(2.0 / 16.0);
            }
            if (k+grootte+1<max ){
                col.push_back(k + grootte +1);
                val.push_back(1.0 / 16.0);
            }
            k+=2;

            ptr.push_back(col.size());
        }

        k+=grootte+3;
    }

    return 0;
}
