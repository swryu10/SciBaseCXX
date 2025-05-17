#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include<vector>

class Vector3 {
  private :

    double *vec_;

  public :

    /* constructor
     * (default) */
    Vector3() {
        vec_ = new double[3];
        vec_[0] = 0.;
        vec_[1] = 0.;
        vec_[2] = 0.;

        return;
    }

    /* constructor
     * (copy) */
    Vector3(const Vector3 &vec_src) {
        vec_ = new double[3];

        vec_[0] = vec_src.vec_[0];
        vec_[1] = vec_src.vec_[1];
        vec_[2] = vec_src.vec_[2];

        return;
    }

    // destructor
    ~Vector3() {
        delete [] vec_;

        return;
    }

    Vector3 &operator=(const Vector3 &vec_src) {
        vec_[0] = vec_src.vec_[0];
        vec_[1] = vec_src.vec_[1];
        vec_[2] = vec_src.vec_[2];

        return *this;
    }

    double &operator[](int ix) {return vec_[ix];}

    void set(int ix, double vx_in) {
        vec_[ix] = vx_in;

        return;
    }

    void set(double *vec_in) {
        vec_[0] = vec_in[0];
        vec_[1] = vec_in[1];
        vec_[2] = vec_in[2];

        return;
    }

    void set(std::vector<double> &vec_in) {
        vec_[0] = vec_in[0];
        vec_[1] = vec_in[1];
        vec_[2] = vec_in[2];

        return;
    }

    double get(int ix) {return vec_[ix];}

    friend Vector3 operator+(Vector3 vec1, Vector3 vec2) {
        Vector3 vec_ret;
        vec_ret.set(0, vec1.vec_[0] + vec2.vec_[0]);
        vec_ret.set(1, vec1.vec_[1] + vec2.vec_[1]);
        vec_ret.set(2, vec1.vec_[2] + vec2.vec_[2]);

        return vec_ret;
    }

    friend Vector3 operator-(Vector3 vec1, Vector3 vec2) {
        Vector3 vec_ret;
        vec_ret.set(0, vec1.vec_[0] - vec2.vec_[0]);
        vec_ret.set(1, vec1.vec_[1] - vec2.vec_[1]);
        vec_ret.set(2, vec1.vec_[2] - vec2.vec_[2]);

        return vec_ret;
    }

    friend Vector3 operator*(double fac, Vector3 vec) {
        Vector3 vec_ret;
        vec_ret.set(0, fac * vec.vec_[0]);
        vec_ret.set(1, fac * vec.vec_[1]);
        vec_ret.set(2, fac * vec.vec_[2]);

        return vec_ret;
    }

    friend Vector3 operator*(Vector3 vec, double fac) {
        Vector3 vec_ret;
        vec_ret.set(0, vec.vec_[0] * fac);
        vec_ret.set(1, vec.vec_[1] * fac);
        vec_ret.set(2, vec.vec_[2] * fac);

        return vec_ret;
    }

    friend Vector3 operator/(Vector3 vec, double fac) {
        Vector3 vec_ret;
        vec_ret.set(0, vec.vec_[0] / fac);
        vec_ret.set(1, vec.vec_[1] / fac);
        vec_ret.set(2, vec.vec_[2] / fac);

        return vec_ret;
    }

    // inner product
    friend double operator*(Vector3 vec1, Vector3 vec2) {
        double prod =
        vec1.vec_[0] * vec2.vec_[0] +
        vec1.vec_[1] * vec2.vec_[1] +
        vec1.vec_[2] * vec2.vec_[2];

        return prod;
    }

    // exterior product
    friend Vector3 operator^(Vector3 vec1, Vector3 vec2) {
        Vector3 vec_ret;
        vec_ret[0] =
            vec1.vec_[1] * vec2.vec_[2] -
            vec1.vec_[2] * vec2.vec_[1];
        vec_ret[1] =
            vec1.vec_[2] * vec2.vec_[0] -
            vec1.vec_[0] * vec2.vec_[2];
        vec_ret[2] =
            vec1.vec_[0] * vec2.vec_[1] -
            vec1.vec_[1] * vec2.vec_[0];

        return vec_ret;
    }
};

#endif
