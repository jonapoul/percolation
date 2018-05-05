#ifndef PERCOLATION_GRID_H
#define PERCOLATION_GRID_H

#include <vector>

class PercolationGrid {
public:
   PercolationGrid(size_t const dim);

   void Fill(float density);
   void Resize(size_t const new_dimension);
   void Reset();
   void SetUniqueIntegers();
   bool Test();
   void Print() const;

private:
   size_t dimension;
   std::vector< std::vector<unsigned> > grid; // values[r][c] = row, column

   float RandomNumber() const;
   std::vector<int> GetNeighbouringCells(size_t const row,
                                         size_t const col) const;
};

#endif