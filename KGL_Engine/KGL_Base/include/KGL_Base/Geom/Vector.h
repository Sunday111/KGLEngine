#ifndef KGL_BASE_VECTOR_H_INCLUDED
#define KGL_BASE_VECTOR_H_INCLUDED

#include <Eigen/Dense>

namespace KGL { namespace Geom {

template<class T, int rows, int cols>
using Matrix = Eigen::Matrix<T, rows, cols, Eigen::DontAlign>;

template<class T, int size>
using Vector = Matrix<T, size, 1>;

using Vector2d = Vector<double, 2>;
using Vector2f = Vector<float, 2>;
using Vector3f = Vector<float, 3>;
using Vector4f = Vector<float, 4>;

} }

#endif /* KGL_BASE_VECTOR_H_INCLUDED */