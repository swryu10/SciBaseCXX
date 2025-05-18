#ifndef _MATRIX_H_
#define _MATRIX_H_

#include"CNumber.h"

class Matrix {
  private :

    int num_row_;
    int num_col_;

    CNumber **mtx_;

    bool flag_square_;

    bool initialized_;

  public :

    /* constructor
     * (default) */
    Matrix() {
        num_row_ = 0;
        num_col_ = 0;

        initialized_ = false;

        return;
    }

    /* constructor
     * (with number of rows and columns) */
    Matrix(int num_in_row, int num_in_col) {
        num_row_ = 0;
        num_col_ = 0;

        initialized_ = false;

        init(num_in_row, num_in_col, NULL);

        return;
    }

    /* constructor
     * (copy) */
    Matrix(const Matrix &mtx_src) {
        initialized_ = mtx_src.initialized_;
        if (!initialized_) {
            return;
        }

        num_row_ = mtx_src.num_row_;
        num_col_ = mtx_src.num_col_;

        mtx_ = new_array(num_row_, num_col_);
        for (int ir = 1; ir <= num_row_; ir++) {
            for (int ic = 1; ic <= num_col_; ic++) {
                mtx_[ir][ic] = mtx_src.mtx_[ir][ic];
            }
        }

        flag_square_ = num_row_ == num_col_;

        return;
    }

    // destructor
    ~Matrix() {
        reset();

        return;
    }

    Matrix &operator=(const Matrix &mtx_src) {
        reset();

        initialized_ = mtx_src.initialized_;
        if (!initialized_) {
            return *this;
        }

        num_row_ = mtx_src.num_row_;
        num_col_ = mtx_src.num_col_;

        mtx_ = new_array(num_row_, num_col_);
        for (int ir = 1; ir <= num_row_; ir++) {
            for (int ic = 1; ic <= num_col_; ic++) {
                mtx_[ir][ic] = mtx_src.mtx_[ir][ic];
            }
        }

        flag_square_ = num_row_ == num_col_;

        return *this;
    }

    CNumber *operator[](int ir) {return mtx_[ir];}

    void init(int num_in_row,
              int num_in_col,
              CNumber **mtx_in) {
        reset();

        if (num_in_row < 1 ||
            num_in_col < 1) {
            return;
        }

        num_row_ = num_in_row;
        num_col_ = num_in_col;
        mtx_ = new_array(num_row_, num_col_);

        for (int ir = 1; ir <= num_row_; ir++) {
            for (int ic = 1; ic <= num_col_; ic++) {
                if (mtx_in != NULL) {
                    mtx_[ir][ic] = mtx_in[ir][ic];
                } else {
                    mtx_[ir][ic][0] = 0.;
                    mtx_[ir][ic][1] = 0.;
                }
            }
        }

        flag_square_ = num_row_ == num_col_;

        initialized_ = true;

        return;
    }

    int get_num_row() {return num_row_;}
    int get_num_col() {return num_col_;}

    bool is_square() {
        return flag_square_;
    }

    void reset() {
        if (!initialized_) {
            return;
        }

        del_array(num_row_, num_col_, mtx_);

        num_row_ = 0;
        num_col_ = 0;

        initialized_ = false;

        return;
    }

    void make_symm() {
        if (!flag_square_) {
            return;
        }

        int num_in_rc = num_row_;
        for (int ir = 1; ir <= num_in_rc; ir++) {
            mtx_[ir][ir][1] = 0.;

            for (int ic = 1; ic < ir; ic++) {
                double entry_ir_ic_re = mtx_[ir][ic][0];
                double entry_ir_ic_im = mtx_[ir][ic][1];

                double entry_ic_ir_re = mtx_[ic][ir][0];
                double entry_ic_ir_im = mtx_[ic][ir][1];

                mtx_[ir][ic][0] =
                    0.5 * (entry_ir_ic_re + entry_ic_ir_re);
                mtx_[ir][ic][1] =
                    0.5 * (entry_ir_ic_im - entry_ic_ir_im);

                mtx_[ic][ir][0] =
                    mtx_[ir][ic][0];
                mtx_[ic][ir][1] =
                    -mtx_[ir][ic][1];
            }
        }

        return;
    }

    void make_conj() {
        if (flag_square_) {
            int num_in_rc = num_row_;
            for (int ir = 1; ir <= num_in_rc; ir++) {
                mtx_[ir][ir][1] =
                    -mtx_[ir][ir][1];

                for (int ic = 1; ic < ir; ic++) {
                    double entry_ir_ic_re = mtx_[ir][ic][0];
                    double entry_ir_ic_im = mtx_[ir][ic][1];

                    double entry_ic_ir_re = mtx_[ic][ir][0];
                    double entry_ic_ir_im = mtx_[ic][ir][1];

                    mtx_[ir][ic][0] =
                        entry_ic_ir_re;
                    mtx_[ir][ic][1] =
                        -entry_ic_ir_im;

                    mtx_[ic][ir][0] =
                        entry_ir_ic_re;
                    mtx_[ic][ir][1] =
                        -entry_ir_ic_im;
                }
            }
        } else {
            int nrow_prev = num_row_;
            int ncol_prev = num_col_;
            CNumber **mtx_src =
                new_array(ncol_prev, nrow_prev);

            for (int ir = 1; ir <= nrow_prev; ir++) {
                for (int ic = 1; ic <= ncol_prev; ic++) {
                    mtx_src[ic][ir][0] = mtx_[ir][ic][0];
                    mtx_src[ic][ir][1] = -mtx_[ir][ic][1];
                }
            }

            init(ncol_prev, nrow_prev, mtx_src);

            del_array(ncol_prev, nrow_prev, mtx_src);
        }

        return;
    }

    static CNumber **new_array(int n_in_row,
                               int n_in_col) {
        CNumber **ptr_out_mtx = NULL;
        if (n_in_row < 1 ||
            n_in_col < 1) {
            return ptr_out_mtx;
        }

        ptr_out_mtx = new CNumber *[n_in_row + 1];
        for (int ir = 1; ir <= n_in_row; ir++) {
            ptr_out_mtx[ir] = new CNumber[n_in_col + 1];

            for (int ic = 1; ic <= n_in_col; ic++) {
                ptr_out_mtx[ir][ic][0] = 0.;
                ptr_out_mtx[ir][ic][1] = 0.;
            }
        }

        return ptr_out_mtx;
    }

    static void del_array(int n_in_row,
                          int n_in_col,
                          CNumber **ptr_in_mtx) {
        if (n_in_row < 1 ||
            n_in_col < 1) {
            return;
        }

        for (int ir = 1; ir <= n_in_row; ir++) {
            delete [] ptr_in_mtx[ir];
        }
        delete [] ptr_in_mtx;

        return;
    }

    friend Matrix operator+(double num1, Matrix mtx2) {
        Matrix mtx_ret = mtx2;
        if (!mtx_ret.is_square()) {
            mtx_ret.reset();

            return mtx_ret;
        }

        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            mtx_ret[ir][ir][0] =
                num1 + mtx_ret[ir][ir][0];
        }

        return mtx_ret;
    }

    friend Matrix operator+(Matrix mtx1, double num2) {
        Matrix mtx_ret = mtx1;
        if (!mtx_ret.is_square()) {
            mtx_ret.reset();

            return mtx_ret;
        }

        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            mtx_ret[ir][ir][0] =
                mtx_ret[ir][ir][0] + num2;
        }

        return mtx_ret;
    }

    friend Matrix operator+(CNumber num1, Matrix mtx2) {
        Matrix mtx_ret = mtx2;
        if (!mtx_ret.is_square()) {
            mtx_ret.reset();

            return mtx_ret;
        }

        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            mtx_ret[ir][ir] =
                num1 + mtx_ret[ir][ir];
        }

        return mtx_ret;
    }

    friend Matrix operator+(Matrix mtx1, CNumber num2) {
        Matrix mtx_ret = mtx1;
        if (!mtx_ret.is_square()) {
            mtx_ret.reset();

            return mtx_ret;
        }

        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            mtx_ret[ir][ir] =
                mtx_ret[ir][ir] + num2;
        }

        return mtx_ret;
    }

    friend Matrix operator-(double num1, Matrix mtx2) {
        Matrix mtx_ret = mtx2;
        if (!mtx_ret.is_square()) {
            mtx_ret.reset();

            return mtx_ret;
        }

        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            for (int ic = 1; ic <= ncol; ic++) {
                mtx_ret[ir][ir][0] =
                    -mtx_ret[ir][ir][0];
                mtx_ret[ir][ir][1] =
                    -mtx_ret[ir][ir][1];
                if (ir == ic) {
                    mtx_ret[ir][ir][0] += num1;
                }
            }
        }

        return mtx_ret;
    }

    friend Matrix operator-(Matrix mtx1, double num2) {
        Matrix mtx_ret = mtx1;
        if (!mtx_ret.is_square()) {
            mtx_ret.reset();

            return mtx_ret;
        }

        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            mtx_ret[ir][ir][0] =
                mtx_ret[ir][ir][0] - num2;
        }

        return mtx_ret;
    }

    friend Matrix operator-(CNumber num1, Matrix mtx2) {
        Matrix mtx_ret = mtx2;
        if (!mtx_ret.is_square()) {
            mtx_ret.reset();

            return mtx_ret;
        }

        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            for (int ic = 1; ic <= ncol; ic++) {
                mtx_ret[ir][ir][0] =
                    -mtx_ret[ir][ir][0];
                mtx_ret[ir][ir][1] =
                    -mtx_ret[ir][ir][1];
                if (ir == ic) {
                    mtx_ret[ir][ir] =
                        mtx_ret[ir][ir] + num1;
                }
            }
        }

        return mtx_ret;
    }

    friend Matrix operator-(Matrix mtx1, CNumber num2) {
        Matrix mtx_ret = mtx1;
        if (!mtx_ret.is_square()) {
            mtx_ret.reset();

            return mtx_ret;
        }

        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            mtx_ret[ir][ir] =
                mtx_ret[ir][ir] - num2;
        }

        return mtx_ret;
    }

    friend Matrix operator*(double fac, Matrix mtx) {
        Matrix mtx_ret = mtx;
        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            for (int ic = 1; ic <= ncol; ic++) {
                mtx_ret[ir][ic] = fac * mtx_ret[ir][ic];
            }
        }

        return mtx_ret;
    }

    friend Matrix operator*(Matrix mtx, double fac) {
        Matrix mtx_ret = mtx;
        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            for (int ic = 1; ic <= ncol; ic++) {
                mtx_ret[ir][ic] = mtx_ret[ir][ic] * fac;
            }
        }

        return mtx_ret;
    }

    friend Matrix operator*(CNumber fac, Matrix mtx) {
        Matrix mtx_ret = mtx;
        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            for (int ic = 1; ic <= ncol; ic++) {
                mtx_ret[ir][ic] = fac * mtx_ret[ir][ic];
            }
        }

        return mtx_ret;
    }

    friend Matrix operator*(Matrix mtx, CNumber fac) {
        Matrix mtx_ret = mtx;
        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            for (int ic = 1; ic <= ncol; ic++) {
                mtx_ret[ir][ic] = mtx_ret[ir][ic] * fac;
            }
        }

        return mtx_ret;
    }

    friend Matrix operator/(Matrix mtx, double fac) {
        Matrix mtx_ret = mtx;
        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            for (int ic = 1; ic <= ncol; ic++) {
                mtx_ret[ir][ic] = mtx_ret[ir][ic] / fac;
            }
        }

        return mtx_ret;
    }

    friend Matrix operator/(Matrix mtx, CNumber fac) {
        Matrix mtx_ret = mtx;
        int nrow = mtx_ret.get_num_row();
        int ncol = mtx_ret.get_num_col();

        for (int ir = 1; ir <= nrow; ir++) {
            for (int ic = 1; ic <= ncol; ic++) {
                mtx_ret[ir][ic] = mtx_ret[ir][ic] / fac;
            }
        }

        return mtx_ret;
    }

    friend Matrix operator*(Matrix mtx1, Matrix mtx2) {
        int nrow = mtx1.get_num_row();
        int ncol_mid = mtx1.get_num_col();

        int nrow_mid = mtx2.get_num_row();
        int ncol = mtx2.get_num_col();

        Matrix mtx_ret;
        if (ncol_mid != nrow_mid) {
            return mtx_ret;
        }

        mtx_ret.init(nrow, ncol, NULL);
        for (int ir = 1; ir <= nrow; ir++) {
            for (int ic = 1; ic <= ncol; ic++) {
                mtx_ret[ir][ic][0] = 0.;
                mtx_ret[ir][ic][1] = 0.;

                for (int jrc = 1; jrc <= ncol_mid; jrc++) {
                    mtx_ret[ir][ic] = mtx_ret[ir][ic] +
                        mtx1[ir][jrc] * mtx2[jrc][ic];
                }
            }
        }

        return mtx_ret;
    }
};

#endif
