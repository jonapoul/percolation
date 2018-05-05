#include <iostream>
#include <vector>
#include <math.h>
#include "PercolationGrid.h"

int main() {
   size_t const run_count = 1e3;
   size_t const dimension = 25;
   float delta = 0.01;
   float density = 0.4;

   while (density < 1.01 && density >= 0) {
      /* Run the tests */
      size_t success_count = 0;
      for (size_t iRun = 0; iRun < run_count; ++iRun) {
         PercolationGrid grid(dimension);
         grid.Fill(density);
         grid.SetUniqueIntegers();
         bool result = grid.Test();
         if (result) ++success_count;
      }

      /* See how many successful percolations we got */
      float success_rate = 100.0*success_count/(float)run_count;
      printf("rho = %f, %.4f%%\n", density, success_rate);
      if      (success_rate > 50) density += delta;
      else if (success_rate < 50) density -= delta;
      delta /= 1.1;

      /* Back out if we're close enough to 50% */
      if (fabs(success_rate - 50.0) < 1e-2) {
         return 0;
      }
   }
}