#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

/* 3-coordinate vector.
 *
 * (From the book) In many systems, vectors are 4D:
 * 3D + homogenous coordinate for geometry, and RGB +
 * alpha transparency channel).
 */
class vec3 {
public:
  vec3() : e{0, 0, 0} {}
  vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double x() const { return e[0]; };
  double y() const { return e[1]; };
  double z() const { return e[2]; };

  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; };

  vec3 &operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  vec3 &operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  vec3 &operator/=(const double t) { return *this *= 1 / t; }

  double length() const { return sqrt(length_squared()); }

  double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

public:
  double e[3];
};

// Type aliases for vec3
using point3 = vec3; // 3D point
using color = vec3;  // RGB color

inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
  return out << v.e[0] << v.e[1] << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) { return t * v; }

inline vec3 operator/(vec3 &v, double t) { return (1 / t) * v; }

std::istream &operator>>(std::istream &is, vec3 &t) {
  is >> t.e[0] >> t.e[1] >> t.e[2];
  return is;
}

/* Dot product
 * (u0, u1, u2) dot (v0, v1, v2) = u0v0 + u1v1 + u2v2
 */
inline double dot(const vec3 &u, const vec3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

/* Cross product
 * (u0, u1, u2) x (v0, v1, v2) = (u1v2 - u2v1, u2v0 - u0v2, u0v1 - u1v0)
 */
inline vec3 cross(const vec3 &u, const vec3 &v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) { return v / v.length(); }

#endif