#ifndef PERCOLATION_GRID_H
#define PERCOLATION_GRID_H

#include <memory>

class PercolationGrid {
public:
   PercolationGrid(size_t const x_dim, size_t const y_dim);
   ~PercolationGrid();

private:
   size_t x_dimension_;
   size_t y_dimension_;
   int ** values;
};

#endif