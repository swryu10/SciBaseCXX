#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include<vector>
#include"Vector3.h"

/* 4-dimensional vector
 * in Minkowski space-time */
class Vector4 {
  private :

    // time component
    double vec_t_;

    // spatial components
    Vector3 vec_x_;

  public :

    /* constructor
     * (default) */
    Vector4() {
        vec_t_ = 0.;
        vec_x_[0] = 0.;
        vec_x_[1] = 0.;
        vec_x_[2] = 0.;

        return;
    }

    /* constructor
     * (copy) */
    Vector4(const Vector4 &vec_src) {
        vec_t_ = vec_src.vec_t_;
        vec_x_[0] = vec_src.vec_x_[0];
        vec_x_[1] = vec_src.vec_x_[1];
        vec_x_[2] = vec_src.vec_x_[2];

        return;
    }

    // destructor
    ~Vector4() {}

    Vector4 &operator=(const Vector4 &vec_src) {
        vec_t_ = vec_src.vec_t_;
        vec_x_[0] = vec_src.vec_x_[0];
        vec_x_[1] = vec_src.vec_x_[1];
        vec_x_[2] = vec_src.vec_x_[2];

        return *this;
    }

    double &operator[](int i) {
        if (i == 0) {
            return vec_t_;
        } else if (i == 3) {
            return vec_x_[0];
        } else {
            return vec_x_[i];
        }
    }

    void set(int i, double vx_in) {
        if (i == 0) {
            vec_t_ = vx_in;
        } else if (i == 3) {
            vec_x_[0] = vx_in;
        } else {
            vec_x_[i] = vx_in;
        }

        return;
    }

    void set(double *vec_in) {
        vec_t_ = vec_in[0];
        vec_x_[0] = vec_in[3];
        vec_x_[1] = vec_in[1];
        vec_x_[2] = vec_in[2];

        return;
    }

    void set(std::vector<double> &vec_in) {
        vec_t_ = vec_in[0];
        vec_x_[0] = vec_in[3];
        vec_x_[1] = vec_in[1];
        vec_x_[2] = vec_in[2];

        return;
    }

    double get(int i) {
        if (i == 0) {
            return vec_t_;
        } else if (i == 3) {
            return vec_x_[0];
        } else {
            return vec_x_[i];
        }
    }

    friend Vector4 operator+(Vector4 vec1, Vector4 vec2) {
        Vector4 vec_ret;
        vec_ret.vec_t_ = vec1.vec_t_ + vec2.vec_t_;
        vec_ret.vec_x_ = vec1.vec_x_ + vec2.vec_x_;

        return vec_ret;
    }

    friend Vector4 operator-(Vector4 vec1, Vector4 vec2) {
        Vector4 vec_ret;
        vec_ret.vec_t_ = vec1.vec_t_ - vec2.vec_t_;
        vec_ret.vec_x_ = vec1.vec_x_ - vec2.vec_x_;

        return vec_ret;
    }

    friend Vector4 operator*(double fac, Vector4 vec) {
        Vector4 vec_ret;
        vec_ret.vec_t_ = fac * vec.vec_t_;
        vec_ret.vec_x_ = fac * vec.vec_x_;

        return vec_ret;
    }

    friend Vector4 operator*(Vector4 vec, double fac) {
        Vector4 vec_ret;
        vec_ret.vec_t_ = vec.vec_t_ * fac;
        vec_ret.vec_x_ = vec.vec_x_ * fac;

        return vec_ret;
    }

    friend Vector4 operator/(Vector4 vec, double fac) {
        Vector4 vec_ret;
        vec_ret.vec_t_ = vec.vec_t_ / fac;
        vec_ret.vec_x_ = vec.vec_x_ / fac;

        return vec_ret;
    }

    /* inner product
     * assuming the mostly-negative Minkowski metric */
    friend double operator*(Vector4 vec1, Vector4 vec2) {
        double prod =
            vec1.vec_t_ * vec2.vec_t -
            vec1.vec_x_ * vec2_vec_x;

        return prod;
    }
};

#endif
