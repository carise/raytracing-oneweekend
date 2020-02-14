#include <iostream>
#include <math.h>
#include <stdlib.h>

/* 3-coordinate vector.
 *
 * (From the book) In many systems, vectors are 4D:
 * 3D + homogenous coordinate for geometry, and RGB +
 * alpha transparency channel).
 */
class vec3 {
public:
  vec3() {}
  vec3(float e0, float e1, float e2) {
    e[0] = e0;
    e[1] = e1;
    e[2] = e2;
  }

  float e[3];

  inline float x() const { return e[0]; };
  inline float y() const { return e[1]; };
  inline float z() const { return e[2]; };
  inline float r() const { return e[0]; };
  inline float g() const { return e[1]; };
  inline float b() const { return e[2]; };

  inline const vec3 &operator+() const { return *this; };
  inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); };
  inline float operator[](int i) const { return e[i]; };
  inline float &operator[](int i) { return e[i]; };

  inline vec3 &operator+=(const vec3 &v2);
  inline vec3 &operator-=(const vec3 &v2);
  inline vec3 &operator*=(const vec3 &v2);
  inline vec3 &operator/=(const vec3 &v2);
  inline vec3 &operator*=(float t);
  inline vec3 &operator/=(float t);

  inline float length() const {
    return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
  }
  inline float squared_length() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }
  inline void make_unit_vector();
};

inline std::istream &operator>>(std::istream &is, vec3 &t) {
  is >> t.e[0] >> t.e[1] >> t.e[2];
  return is;
}

inline std::ostream &operator<<(std::ostream &os, const vec3 &t) {
  os << t.e[0] << t.e[1] << t.e[2];
  return os;
}

inline void vec3::make_unit_vector() {
  float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
  e[0] *= k;
  e[1] *= k;
  e[2] *= k;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

// For some reason, there were 2 definitions of this function,
// with the same body but different signature (vec3&, float) vs
// (float, vec3&). I left one out.
inline vec3 operator*(const vec3 &v, float t) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(const vec3 &v, float t) {
  return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

/* Dot product
 * (a0, a1, a2) dot (b0, b1, b2) = a0b0 + a1b1 + a2b2
 */
inline float dot(const vec3 &v1, const vec3 &v2) {
  return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

/* Cross product
 * (a0, a1, a2) x (b0, b1, b2) = (a1b2 - a2b1) + (-a0b2 + a2b0) + (a0b1 + a1b0)
 */
inline vec3 cross(const vec3 &v1, const vec3 &v2) {
  return vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
              (-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
              (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

inline vec3 &vec3::operator+=(const vec3 &v) {
  e[0] += v.e[0];
  e[1] += v.e[1];
  e[2] += v.e[2];
  return *this;
}

inline vec3 &vec3::operator-=(const vec3 &v) {
  e[0] -= v.e[0];
  e[1] -= v.e[1];
  e[2] -= v.e[2];
  return *this;
}

inline vec3 &vec3::operator*=(const vec3 &v) {
  e[0] *= v.e[0];
  e[1] *= v.e[1];
  e[2] *= v.e[2];
  return *this;
}

inline vec3 &vec3::operator/=(const vec3 &v) {
  e[0] /= v.e[0];
  e[1] /= v.e[1];
  e[2] /= v.e[2];
  return *this;
}

inline vec3 &vec3::operator*=(const float t) {
  e[0] *= t;
  e[1] *= t;
  e[2] *= t;
  return *this;
}

inline vec3 &vec3::operator/=(const float t) {
  // Why not just e /= t?
  float k = 1.0 / t;
  e[0] *= k;
  e[1] *= t;
  e[2] *= t;
  return *this;
}

inline vec3 unit_vector(vec3 v) { return v / v.length(); }