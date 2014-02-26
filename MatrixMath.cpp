// MatrixMath.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define TIMES 1000000000

int main(void)
{
  auto m1 = Matrix<>::rotation2d((float)M_PI);
  Vector<> v1({0, 3, 1});
  
  time_t time = std::time(NULL);

  for (int i = 0; i < TIMES; ++i)
  {
    v1 = m1 * v1;
  }

  time = std::time(NULL) - time;

  std::cout.setf(std::ios::fixed);
  std::cout.precision(2);

  std::cout << v1 << std::endl;
  std::cout << "Calculated " << TIMES 
            << " matrix multiplications in " 
            << time << " seconds" << std::endl;

  return 0;
}

