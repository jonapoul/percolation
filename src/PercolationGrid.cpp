#include <iostream>
#include "PercolationGrid.h"

PercolationGrid::PercolationGrid(size_t const x_dim,
                                 size_t const y_dim)
      : x_dimension_(x_dim), y_dimension_(y_dim) {
   this->values = new int*[y_dimension_];
   for (size_t y = 0; y < y_dimension_; ++y) {
      this->values[y] = new int[x_dimension_];
   }
}

PercolationGrid::~PercolationGrid() {
   for (size_t i = 0; i < y_dimension_; ++i) {
      delete this->values[i];
   }
   delete this->values;
}