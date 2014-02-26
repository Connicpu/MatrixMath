// MatrixMath.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define TIMES 100000000
#define CROSS_SECTIONS 16

int main(void)
{
  auto m1 = Matrix<3, 3, double>::rotation2d(2.0 / CROSS_SECTIONS * M_PI / TIMES);
  Vector<3, double> v1 { 
    12,
    34,
    1
  };
  
  time_t total_time = std::time(NULL);

  std::cout.setf(std::ios::fixed);
  std::cout.precision(2);

  std::cout << v1 << std::endl;

  for (int j = 0; j < CROSS_SECTIONS; ++j)
  {
    time_t time = std::time(NULL);

    std::cout << "Rotating by " << 360 / CROSS_SECTIONS 
              << " degrees with " << TIMES 
              << " operations" << std::endl;

    for (int i = 0; i < TIMES; ++i)
    {
      v1 = m1 * v1;
    }

    time = std::time(NULL) - time;

    std::cout << v1 << std::endl
              << "Calculated " << TIMES 
              << " matrix multiplications in " 
              << time << " seconds" << std::endl
              << std::endl;
  }
  
  total_time = std::time(NULL) - total_time;

  std::cout << "Total " << TIMES*CROSS_SECTIONS
            << " operations in " << total_time
            << " seconds" << std::endl;

  return 0;
}

