#include <iostream>
#include <random>
#include <string>
#include <algorithm>

#include "PercolationGrid.h"

PercolationGrid::PercolationGrid(size_t const dim) : dimension(dim) {
   // plus two to allow for the cells around the edge
   const size_t rows = dim+2, cols = dim+2;
   grid.resize(rows);
   for (auto& row : grid) {
      row.resize(cols, 0);
   }
}

/* Expecting a value from 0 to 1. 1 = full, 0 = empty */
void PercolationGrid::Fill(float density) {
   for (size_t row = 1; row < dimension+1; ++row) {
      for (size_t col = 1; col < dimension+1; ++col) {
         float const generated = RandomNumber();
         grid[row][col] = (generated > density) ? 1 : 0;
      }
   }
}

void PercolationGrid::Resize(size_t const new_dimension) {
   this->dimension = new_dimension;
   this->grid.resize(dimension+2);
   for (auto& row : this->grid) {
      row.resize(dimension+2, 0);
   }
}

void PercolationGrid::Reset() {
   for (auto& row : this->grid) {
      std::fill(row.begin(), row.end(), 0);
   }
}

void PercolationGrid::SetUniqueIntegers() {
   int running_counter = 1;
   for (auto& row : this->grid) {
      for (auto& cell : row) {
         if (cell != 0) {
            cell = running_counter++;
         }
      }
   }
}

bool PercolationGrid::Test() {
   bool finished_updating = false;
   while (!finished_updating) {
      bool cell_has_changed = false;
      for (size_t row = 1; row < dimension+1; ++row) {
         for (size_t col = 1; col < dimension+1; ++col) {
            int const current_value = grid[row][col];
            if (current_value == 0)
               continue;
            std::vector<int> const neighbours = GetNeighbouringCells(row, col);
            int const max_neighbour = *std::max_element(neighbours.begin(),
                                                        neighbours.end());
            if (max_neighbour > current_value) {
               grid[row][col] = max_neighbour;
               cell_has_changed = true;
            }
         }
      }
      if (!cell_has_changed) {
         finished_updating = true;
      }
   }
   /* All nonzero cells should now be clustered. CHeck the top and bottom rows
      to see if any nonzero values match */
   auto top = grid[1];
   auto bottom = grid[dimension-2];
   for (auto& t : top) {
      for (auto& b : bottom) {
         if (t != 0 && t == b) {
            return true;
         }
      }
   }
   return false;
}

template<typename T>
std::string PaddedString(T const input, size_t const width) {
   std::string output = std::to_string(input);
   if (output.length() > width) {
      printf("'%s' is too long to fit in a PaddedString of size %zu.\n",
             output.c_str(), width);
      exit(1);
   }
   while (output.length() < width) {
      output.insert(output.begin(), ' ');
      if (output.length() >= width) {
         break;
      }
      output.insert(output.end(), ' ');
   }
   return output;
}

void PercolationGrid::Print() const {
   std::string GREEN = "\033[32m";
   std::string WHITE = "\033[37m";

   for (size_t row = 0; row < dimension+2; ++row) {
      std::cout << std::string(10, ' ');
      for (size_t col = 0; col < dimension+2; ++col) {
         if (grid[row][col] == 0) std::cout << GREEN;
         std::string output = PaddedString<int>(grid[row][col], 4);
         std::cout << output << WHITE;
      }
      std::cout << '\n';
   }

   int filled_cells = 0;
   for (auto& row : this->grid) {
      for (auto& cell : row) {
         if (cell > 0) filled_cells++;
      }
   }
   printf("Actual Density = %.2f%%\n",
          100.0*filled_cells/float(dimension*dimension));
}

float PercolationGrid::RandomNumber() const {
   static std::random_device device;
   static std::mt19937 generator(device());
   static std::uniform_real_distribution<> distribution(0.0, 1.0);

   return distribution(generator);
}

std::vector<int> PercolationGrid::GetNeighbouringCells(size_t const row,
                                                       size_t const col) const {
   std::vector<int> output(4);
   output[0] = grid[row-1][col  ];
   output[1] = grid[row+1][col  ];
   output[2] = grid[row  ][col-1];
   output[3] = grid[row  ][col+1];
   return output;
}