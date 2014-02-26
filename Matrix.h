#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cstdlib>

#define MTX_DEFAULT_ROWS 3
#define MTX_DEFAULT_COLS 3

#if defined(MTX_DEFAULT_ROWS) && defined(MTX_DEFAULT_COLS)
template<unsigned ROWS = MTX_DEFAULT_ROWS, unsigned COLS = MTX_DEFAULT_COLS, typename AType = float>
#else
template<unsigned ROWS, unsigned COLS, typename AType = float>
#endif
class Matrix
{
public:
  Matrix() 
  {
    memset(values, 0, sizeof(values));
  }
#if __cplusplus >= 199711L
  Matrix(std::initializer_list<AType> args)
  {
    if (args.size() != ROWS * COLS)
      throw std::invalid_argument("The args size must match the number of elements in the matrix");
    auto iter = args.begin();
    memcpy_s(values, sizeof(values), iter, sizeof(values));
  }
#endif
  Matrix(const Matrix& other)
  {
    memcpy_s(values, sizeof(values), other.values, sizeof(values));
  }

  AType& get(unsigned r, unsigned c)
  {
    if (r < 1 || r > ROWS || c < 1 || c > COLS)
      throw std::invalid_argument("The row or column was out of bounds");
    return values[r - 1][c - 1];
  }

  template<unsigned N>
  Matrix<ROWS, N, AType> operator*(const Matrix<COLS, N, AType>& b) const
  {
    Matrix<ROWS, N, AType> result;
    for (unsigned ar = 0; ar < ROWS; ++ar) // Matrix A row
    {
      for (unsigned bc = 0; bc < N; ++bc) // Matrix B column
      {
        result.values[ar][bc] = 0.0f;
        for (unsigned c = 0; c < COLS; ++c) // Common coordinate
          result.values[ar][bc] += values[ar][c] * b.values[c][bc];
      }
    }
    return result;
  }

  Matrix operator+(const Matrix& b) const
  {
    Matrix result = *this;
    result += b;
    return result;
  }

  Matrix& operator*=(const Matrix& b)
  {
    operator=(*this * b);
    return *this;
  }

  Matrix& operator+=(const Matrix& b)
  {
    for (unsigned r = 0; r < ROWS; ++r)
      for (unsigned c = 0; c < COLS; ++c)
        values[r][c] += b.values[r][c];
    return *this;
  }

  Matrix& operator-=(const Matrix& b)
  {
    for (unsigned r = 0; r < ROWS; ++r)
      for (unsigned c = 0; c < COLS; ++c)
        values[r][c] -= b.values[r][c];
    return *this;
  }

  static Matrix identity()
  {
    Matrix ident;
    for (unsigned i = 0; i < ROWS; ++i)
      for (unsigned j = 0; j < COLS; ++j)
        ident.values[i][j] = i == j ? 1.0f : 0.0f;
    return ident;
  }

  static Matrix<3, 3, AType> rotation2d(AType rads)
  {
    return {
      cos(rads), -sin(rads), 0,
      sin(rads),  cos(rads), 0,
              0,          0, 1,
    };
  }

  template<unsigned R, unsigned C>
  friend std::ostream& operator<<(std::ostream& os, const Matrix<R, C>& mtx);

  AType values[ROWS][COLS];
};

template<unsigned ROWS, unsigned COLS, typename AType>
std::ostream& operator<<(std::ostream& os, const Matrix<ROWS, COLS, AType>& mtx)
{
  size_t text_len = 0;
  {
    // calculate longest number
    for (unsigned r = 0; r < ROWS; ++r)
      for (unsigned c = 0; c < COLS; ++c)
      {
        std::stringstream buf;
        buf.copyfmt(os);
        buf << mtx.values[r][c];
        text_len = std::max<size_t>(buf.str().length(), text_len);
      }
  }

  os << "\xD6 " << std::setw(text_len * COLS + COLS) << "" << "\xB7" << std::endl;
  for (unsigned r = 0; r < ROWS; ++r)
  {
    os << "\xBA ";
    for (unsigned c = 0; c < COLS; ++c)
    {
      os << std::setw(text_len) << mtx.values[r][c] << " ";
    }
    os << "\xBA" << std::endl;
  }
  os << "\xD3 " << std::setw(text_len * COLS + COLS) << "" << "\xBD";

  return os;
}

#ifdef MTX_DEFAULT_ROWS
template <unsigned N = MTX_DEFAULT_ROWS, typename AType = float>
#else
template <unsigned N, typename AType = float>
#endif
using Vector = Matrix<N, 1, AType>;

