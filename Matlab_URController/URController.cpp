//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: URController.cpp
//
// Code generated for Simulink model 'URController'.
//
// Model version                  : 1.53
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Thu Sep 26 20:51:00 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Custom
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "URController.h"
#include "rtwtypes.h"
#include <cstring>
#include <cmath>
#include "URController_private.h"

//
// This function updates continuous states using the ODE4 fixed-step
// solver algorithm
//
void URController::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t { rtsiGetT(si) };

  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE4_IntgData *id { static_cast<ODE4_IntgData *>(rtsiGetSolverData(si)) };

  real_T *y { id->y };

  real_T *f0 { id->f[0] };

  real_T *f1 { id->f[1] };

  real_T *f2 { id->f[2] };

  real_T *f3 { id->f[3] };

  real_T temp;
  int_T i;
  int_T nXc { 30 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  // Save the state values at time t in y, we'll use x as ynew.
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  URController_derivatives();

  // f1 = f(t + (h/2), y + (h/2)*f0)
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  this->step();
  URController_derivatives();

  // f2 = f(t + (h/2), y + (h/2)*f1)
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  this->step();
  URController_derivatives();

  // f3 = f(t + h, y + h*f2)
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  this->step();
  URController_derivatives();

  // tnew = t + h
  // ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3)
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Function for MATLAB Function: '<S2>/MATLAB Function'
void URController::inv(const real_T x[16], real_T y[16])
{
  real_T A[16];
  real_T smax;
  int32_T jA;
  int32_T jj;
  int32_T kAcol;
  int32_T n;
  int32_T pipk;
  int8_T ipiv[4];
  int8_T p[4];
  for (pipk = 0; pipk < 16; pipk++) {
    A[pipk] = x[pipk];
    y[pipk] = 0.0;
  }

  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  for (pipk = 0; pipk < 3; pipk++) {
    jj = pipk * 5;
    n = 4 - pipk;
    jA = 0;
    smax = std::abs(A[jj]);
    for (int32_T d_k{2}; d_k <= n; d_k++) {
      real_T s;
      s = std::abs(A[(jj + d_k) - 1]);
      if (s > smax) {
        jA = d_k - 1;
        smax = s;
      }
    }

    if (A[jj + jA] != 0.0) {
      if (jA != 0) {
        n = pipk + jA;
        ipiv[pipk] = static_cast<int8_T>(n + 1);
        smax = A[pipk];
        A[pipk] = A[n];
        A[n] = smax;
        smax = A[pipk + 4];
        A[pipk + 4] = A[n + 4];
        A[n + 4] = smax;
        smax = A[pipk + 8];
        A[pipk + 8] = A[n + 8];
        A[n + 8] = smax;
        smax = A[pipk + 12];
        A[pipk + 12] = A[n + 12];
        A[n + 12] = smax;
      }

      n = (jj - pipk) + 4;
      for (jA = jj + 2; jA <= n; jA++) {
        A[jA - 1] /= A[jj];
      }
    }

    n = 2 - pipk;
    jA = jj + 6;
    for (int32_T d_k{0}; d_k <= n; d_k++) {
      smax = A[((d_k << 2) + jj) + 4];
      if (smax != 0.0) {
        kAcol = (jA - pipk) + 2;
        for (int32_T ijA{jA}; ijA <= kAcol; ijA++) {
          A[ijA - 1] += A[((jj + ijA) - jA) + 1] * -smax;
        }
      }

      jA += 4;
    }
  }

  p[0] = 1;
  p[1] = 2;
  p[2] = 3;
  p[3] = 4;
  if (ipiv[0] > 1) {
    pipk = p[ipiv[0] - 1];
    p[ipiv[0] - 1] = 1;
    p[0] = static_cast<int8_T>(pipk);
  }

  if (ipiv[1] > 2) {
    pipk = p[ipiv[1] - 1];
    p[ipiv[1] - 1] = p[1];
    p[1] = static_cast<int8_T>(pipk);
  }

  if (ipiv[2] > 3) {
    pipk = p[ipiv[2] - 1];
    p[ipiv[2] - 1] = p[2];
    p[2] = static_cast<int8_T>(pipk);
  }

  for (n = 0; n < 4; n++) {
    jj = (p[n] - 1) << 2;
    y[n + jj] = 1.0;
    for (jA = n + 1; jA < 5; jA++) {
      pipk = (jj + jA) - 1;
      if (y[pipk] != 0.0) {
        for (int32_T d_k{jA + 1}; d_k < 5; d_k++) {
          kAcol = (jj + d_k) - 1;
          y[kAcol] -= A[(((jA - 1) << 2) + d_k) - 1] * y[pipk];
        }
      }
    }
  }

  for (n = 0; n < 4; n++) {
    jA = n << 2;
    for (int32_T d_k{3}; d_k >= 0; d_k--) {
      kAcol = d_k << 2;
      pipk = d_k + jA;
      smax = y[pipk];
      if (smax != 0.0) {
        y[pipk] = smax / A[d_k + kAcol];
        for (int32_T ijA{0}; ijA < d_k; ijA++) {
          jj = ijA + jA;
          y[jj] -= A[ijA + kAcol] * y[pipk];
        }
      }
    }
  }
}

// Function for MATLAB Function: '<S2>/MATLAB Function'
real_T URController::norm(const real_T x[4])
{
  real_T absxk;
  real_T scale;
  real_T t;
  real_T y;
  scale = 3.3121686421112381E-170;
  absxk = std::abs(x[0]);
  if (absxk > 3.3121686421112381E-170) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    y = t * t;
  }

  absxk = std::abs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = std::abs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = std::abs(x[3]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * std::sqrt(y);
}

// Model step function
void URController::step()
{
  static const real_T f[9]{ 1.0, 0.0, 0.0, 0.0, 6.123233995736766E-17, 1.0, 0.0,
    -1.0, 6.123233995736766E-17 };

  static const real_T h[9]{ 1.0, 0.0, 0.0, 0.0, 6.123233995736766E-17, -1.0, 0.0,
    1.0, 6.123233995736766E-17 };

  static const real_T k[4]{ 0.0, -0.1093, 0.0, 1.0 };

  static const int8_T d_0[16]{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

  static const int8_T g[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const int8_T p05_tmp_1[4]{ 0, 0, 0, 1 };

  static const int8_T d[3]{ 0, 0, 1 };

  real_T rtb_theta[48];
  real_T x[48];
  real_T y[48];
  real_T T14[16];
  real_T a[16];
  real_T a_0[16];
  real_T b[16];
  real_T b_b[16];
  real_T c_a[16];
  real_T c_a_0[16];
  real_T c_a_1[16];
  real_T c_a_2[16];
  real_T c_a_tmp[16];
  real_T c_b[16];
  real_T rtb_gd[16];
  real_T b_0[9];
  real_T b_1[9];
  real_T tmp[9];
  real_T tmp_0[9];
  real_T varargin_1[8];
  real_T p05[4];
  real_T a_1;
  real_T a_2;
  real_T a_3;
  real_T phi;
  real_T psi;
  real_T rtb_Integrator;
  real_T rtb_Integrator_h;
  real_T rtb_Sum;
  real_T rtb_Sum4;
  int32_T a_tmp;
  int32_T b_i;
  int32_T b_tmp_0;
  int32_T c_a_tmp_2;
  int32_T i;
  int32_T p05_tmp_0;
  int32_T xpageoffset;
  int8_T c_a_tmp_0[16];
  int8_T c_b_tmp[9];
  int8_T p05_tmp[4];
  int8_T b_tmp[3];
  int8_T c_a_tmp_1;
  if (rtmIsMajorTimeStep((&rtM))) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&rtM)->solverInfo,(((&rtM)->Timing.clockTick0+1)*
      (&rtM)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep((&rtM))) {
    (&rtM)->Timing.t[0] = rtsiGetT(&(&rtM)->solverInfo);
  }

  // MATLAB Function: '<S2>/MATLAB Function1' incorporates:
  //   Inport: '<Root>/desire_pos_orient_arr'

  std::memset(&rtb_gd[0], 0, sizeof(real_T) << 4U);
  rtb_gd[0] = 1.0;
  rtb_gd[5] = 1.0;
  rtb_gd[10] = 1.0;
  rtb_gd[15] = 1.0;
  phi = std::sin(rtU.desire_pos_orient_arr[3]);
  psi = std::cos(rtU.desire_pos_orient_arr[3]);
  rtb_Sum4 = std::sin(rtU.desire_pos_orient_arr[4]);
  rtb_Sum = std::cos(rtU.desire_pos_orient_arr[4]);
  rtb_Integrator_h = std::sin(rtU.desire_pos_orient_arr[5]);
  rtb_Integrator = std::cos(rtU.desire_pos_orient_arr[5]);
  b_0[1] = 0.0;
  b_0[4] = psi;
  b_0[7] = -phi;
  b_0[2] = 0.0;
  b_0[5] = phi;
  b_0[8] = psi;
  tmp[0] = rtb_Sum;
  tmp[3] = 0.0;
  tmp[6] = rtb_Sum4;
  rtb_gd[12] = rtU.desire_pos_orient_arr[0];
  b_0[0] = 1.0;
  tmp[1] = 0.0;
  rtb_gd[13] = rtU.desire_pos_orient_arr[1];
  b_0[3] = 0.0;
  tmp[4] = 1.0;
  rtb_gd[14] = rtU.desire_pos_orient_arr[2];
  b_0[6] = 0.0;
  tmp[7] = 0.0;
  tmp[2] = -rtb_Sum4;
  tmp[5] = 0.0;
  tmp[8] = rtb_Sum;
  tmp_0[0] = rtb_Integrator;
  tmp_0[3] = -rtb_Integrator_h;
  tmp_0[6] = 0.0;
  tmp_0[1] = rtb_Integrator_h;
  tmp_0[4] = rtb_Integrator;
  tmp_0[7] = 0.0;
  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    psi = b_0[p05_tmp_0 + 3];
    phi = b_0[p05_tmp_0];
    rtb_Sum4 = b_0[p05_tmp_0 + 6];
    for (b_tmp_0 = 0; b_tmp_0 < 3; b_tmp_0++) {
      b_1[p05_tmp_0 + 3 * b_tmp_0] = (tmp[3 * b_tmp_0 + 1] * psi + tmp[3 *
        b_tmp_0] * phi) + tmp[3 * b_tmp_0 + 2] * rtb_Sum4;
    }

    tmp_0[3 * p05_tmp_0 + 2] = d[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    phi = tmp_0[3 * p05_tmp_0 + 1];
    psi = tmp_0[3 * p05_tmp_0];
    rtb_Sum4 = tmp_0[3 * p05_tmp_0 + 2];
    for (b_tmp_0 = 0; b_tmp_0 < 3; b_tmp_0++) {
      rtb_gd[b_tmp_0 + (p05_tmp_0 << 2)] = (b_1[b_tmp_0 + 3] * phi + psi *
        b_1[b_tmp_0]) + b_1[b_tmp_0 + 6] * rtb_Sum4;
    }
  }

  // End of MATLAB Function: '<S2>/MATLAB Function1'

  // MATLAB Function: '<S2>/MATLAB Function'
  std::memset(&rtb_theta[0], 0, 48U * sizeof(real_T));
  for (i = 0; i < 4; i++) {
    p05_tmp_0 = p05_tmp_1[i];
    p05_tmp[i] = static_cast<int8_T>(p05_tmp_0);
    p05[i] = (rtb_gd[i + 8] * -0.0825 + rtb_gd[i + 12]) - static_cast<real_T>
      (p05_tmp_0);
  }

  psi = std::atan2(p05[1], p05[0]);
  phi = std::acos(0.1093 / std::sqrt(p05[1] * p05[1] + p05[0] * p05[0]));
  rtb_Sum4 = (psi + 1.5707963267948966) + phi;
  rtb_theta[0] = rtb_Sum4;
  psi = (psi + 1.5707963267948966) - phi;
  rtb_theta[24] = psi;
  rtb_theta[6] = rtb_Sum4;
  rtb_theta[30] = psi;
  rtb_theta[12] = rtb_Sum4;
  rtb_theta[36] = psi;
  rtb_theta[18] = rtb_Sum4;
  rtb_theta[42] = psi;
  for (i = 0; i < 2; i++) {
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      xpageoffset = d_0[p05_tmp_0];
      c_b[p05_tmp_0] = xpageoffset;
      c_a[p05_tmp_0] = xpageoffset;
      b_b[p05_tmp_0] = xpageoffset;
      b[p05_tmp_0] = xpageoffset;
    }

    c_a[14] = 0.0892;
    b_b[12] = 0.0;
    xpageoffset = i << 2;
    psi = rtb_theta[xpageoffset * 6];
    rtb_Sum = std::sin(psi);
    phi = std::cos(psi);
    b[0] = phi;
    b[4] = -rtb_Sum;
    b[8] = 0.0;
    b[1] = rtb_Sum;
    b[5] = phi;
    b[9] = 0.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      b_tmp_0 = p05_tmp_0 << 2;
      b[b_tmp_0 + 2] = d[p05_tmp_0];
      c_b[b_tmp_0] = f[3 * p05_tmp_0];
      c_b[b_tmp_0 + 1] = f[3 * p05_tmp_0 + 1];
      c_b[b_tmp_0 + 2] = f[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      rtb_Sum4 = c_a[p05_tmp_0 + 4];
      rtb_Sum = c_a[p05_tmp_0];
      rtb_Integrator_h = c_a[p05_tmp_0 + 8];
      rtb_Integrator = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * rtb_Sum4 +
          b[c_a_tmp_2] * rtb_Sum) + b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          b[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      rtb_Sum4 = c_a_0[p05_tmp_0 + 4];
      rtb_Sum = c_a_0[p05_tmp_0];
      rtb_Integrator_h = c_a_0[p05_tmp_0 + 8];
      rtb_Integrator = c_a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_Sum4 +
          b_b[c_a_tmp_2] * rtb_Sum) + b_b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          b_b[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      rtb_Sum4 = c_a_1[p05_tmp_0 + 4];
      rtb_Sum = c_a_1[p05_tmp_0];
      rtb_Integrator_h = c_a_1[p05_tmp_0 + 8];
      rtb_Integrator = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * rtb_Sum4 +
          c_b[c_a_tmp_2] * rtb_Sum) + c_b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          c_b[c_a_tmp_2 + 3] * rtb_Integrator;
      }
    }

    inv(c_a_2, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      psi = a[p05_tmp_0];
      rtb_Sum4 = a[p05_tmp_0 + 8];
      rtb_Sum = a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_b[p05_tmp_0 + c_a_tmp_2] = ((rtb_gd[c_a_tmp_2 + 1] * phi +
          rtb_gd[c_a_tmp_2] * psi) + rtb_gd[c_a_tmp_2 + 2] * rtb_Sum4) +
          rtb_gd[c_a_tmp_2 + 3] * rtb_Sum;
      }
    }

    psi = std::acos((c_b[14] - 0.1093) / 0.0825);
    rtb_theta[6 * xpageoffset + 4] = psi;
    rtb_theta[6 * (xpageoffset + 2) + 4] = -psi;
    rtb_theta[6 * (xpageoffset + 1) + 4] = psi;
    rtb_theta[6 * (xpageoffset + 3) + 4] = -psi;
  }

  inv(rtb_gd, a);
  for (b_i = 0; b_i < 4; b_i++) {
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      xpageoffset = d_0[p05_tmp_0];
      c_b[p05_tmp_0] = xpageoffset;
      c_a[p05_tmp_0] = xpageoffset;
      b_b[p05_tmp_0] = xpageoffset;
      b[p05_tmp_0] = xpageoffset;
    }

    c_a[14] = 0.0892;
    b_b[12] = 0.0;
    i = b_i << 1;
    xpageoffset = i * 6;
    psi = rtb_theta[xpageoffset];
    rtb_Sum = std::sin(psi);
    phi = std::cos(psi);
    b[0] = phi;
    b[4] = -rtb_Sum;
    b[8] = 0.0;
    b[1] = rtb_Sum;
    b[5] = phi;
    b[9] = 0.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      b_tmp_0 = p05_tmp_0 << 2;
      b[b_tmp_0 + 2] = d[p05_tmp_0];
      c_b[b_tmp_0] = f[3 * p05_tmp_0];
      c_b[b_tmp_0 + 1] = f[3 * p05_tmp_0 + 1];
      c_b[b_tmp_0 + 2] = f[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      rtb_Sum4 = c_a[p05_tmp_0 + 4];
      rtb_Sum = c_a[p05_tmp_0];
      rtb_Integrator_h = c_a[p05_tmp_0 + 8];
      rtb_Integrator = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * rtb_Sum4 +
          b[c_a_tmp_2] * rtb_Sum) + b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          b[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      rtb_Sum4 = c_a_0[p05_tmp_0 + 4];
      rtb_Sum = c_a_0[p05_tmp_0];
      rtb_Integrator_h = c_a_0[p05_tmp_0 + 8];
      rtb_Integrator = c_a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_Sum4 +
          b_b[c_a_tmp_2] * rtb_Sum) + b_b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          b_b[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      rtb_Sum4 = c_a_1[p05_tmp_0 + 4];
      rtb_Sum = c_a_1[p05_tmp_0];
      rtb_Integrator_h = c_a_1[p05_tmp_0 + 8];
      rtb_Integrator = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * rtb_Sum4 +
          c_b[c_a_tmp_2] * rtb_Sum) + c_b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          c_b[c_a_tmp_2 + 3] * rtb_Integrator;
      }
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      psi = a[p05_tmp_0];
      rtb_Sum4 = a[p05_tmp_0 + 8];
      rtb_Sum = a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_tmp[p05_tmp_0 + c_a_tmp_2] = ((c_a_2[c_a_tmp_2 + 1] * phi +
          c_a_2[c_a_tmp_2] * psi) + c_a_2[c_a_tmp_2 + 2] * rtb_Sum4) +
          c_a_2[c_a_tmp_2 + 3] * rtb_Sum;
      }
    }

    psi = std::sin(rtb_theta[xpageoffset + 4]);
    psi = std::atan2(-c_a_tmp[9] / psi, c_a_tmp[8] / psi);
    rtb_theta[6 * i + 5] = psi;
    rtb_theta[6 * (i + 1) + 5] = psi;
  }

  b_tmp[0] = 0;
  b_tmp[1] = 0;
  b_tmp[2] = 1;
  for (b_i = 0; b_i < 4; b_i++) {
    i = b_i << 1;
    xpageoffset = i * 6;
    psi = rtb_theta[xpageoffset];
    rtb_Sum = std::sin(psi);
    phi = std::cos(psi);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      c_a_tmp_2 = d_0[p05_tmp_0];
      c_a_tmp[p05_tmp_0] = c_a_tmp_2;
      c_a[p05_tmp_0] = c_a_tmp_2;
      b_b[p05_tmp_0] = c_a_tmp_2;
      b[p05_tmp_0] = c_a_tmp_2;
      c_b[p05_tmp_0] = c_a_tmp_2;
    }

    c_a[14] = 0.0892;
    b_b[12] = 0.0;
    b[0] = phi;
    b[4] = -rtb_Sum;
    b[8] = 0.0;
    b[1] = rtb_Sum;
    b[5] = phi;
    b[9] = 0.0;
    b[2] = 0.0;
    b[6] = 0.0;
    b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      b_tmp_0 = p05_tmp_0 << 2;
      c_b[b_tmp_0] = f[3 * p05_tmp_0];
      c_b[b_tmp_0 + 1] = f[3 * p05_tmp_0 + 1];
      c_b[b_tmp_0 + 2] = f[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      rtb_Sum4 = c_a[p05_tmp_0 + 4];
      rtb_Sum = c_a[p05_tmp_0];
      rtb_Integrator_h = c_a[p05_tmp_0 + 8];
      rtb_Integrator = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * rtb_Sum4 +
          b[c_a_tmp_2] * rtb_Sum) + b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          b[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      rtb_Sum4 = c_a_1[p05_tmp_0 + 4];
      rtb_Sum = c_a_1[p05_tmp_0];
      rtb_Integrator_h = c_a_1[p05_tmp_0 + 8];
      rtb_Integrator = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_Sum4 +
          b_b[c_a_tmp_2] * rtb_Sum) + b_b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          b_b[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      rtb_Sum4 = c_a_0[p05_tmp_0 + 4];
      rtb_Sum = c_a_0[p05_tmp_0];
      rtb_Integrator_h = c_a_0[p05_tmp_0 + 8];
      rtb_Integrator = c_a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * rtb_Sum4 +
          c_b[c_a_tmp_2] * rtb_Sum) + c_b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          c_b[c_a_tmp_2 + 3] * rtb_Integrator;
      }
    }

    inv(c_a_2, c_a);
    psi = rtb_theta[xpageoffset + 5];
    rtb_Sum = std::sin(psi);
    phi = std::cos(psi);
    std::memcpy(&a[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&b_b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&c_b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    a[14] = 0.0825;
    b_b[12] = 0.0;
    b[0] = phi;
    b[4] = -rtb_Sum;
    b[8] = 0.0;
    b[1] = rtb_Sum;
    b[5] = phi;
    b[9] = 0.0;
    b[2] = 0.0;
    b[6] = 0.0;
    b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      b_tmp_0 = p05_tmp_0 << 2;
      c_b[b_tmp_0] = g[3 * p05_tmp_0];
      c_b[b_tmp_0 + 1] = g[3 * p05_tmp_0 + 1];
      c_b[b_tmp_0 + 2] = g[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      a_1 = a[p05_tmp_0];
      a_2 = a[p05_tmp_0 + 8];
      a_3 = a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * phi + b[c_a_tmp_2] *
          a_1) + b[c_a_tmp_2 + 2] * a_2) + b[c_a_tmp_2 + 3] * a_3;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      a_1 = c_a_2[p05_tmp_0];
      a_2 = c_a_2[p05_tmp_0 + 8];
      a_3 = c_a_2[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_0[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * phi + b_b[c_a_tmp_2]
          * a_1) + b_b[c_a_tmp_2 + 2] * a_2) + b_b[c_a_tmp_2 + 3] * a_3;
      }

      phi = a_0[p05_tmp_0 + 4];
      a_1 = a_0[p05_tmp_0];
      a_2 = a_0[p05_tmp_0 + 8];
      a_3 = a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * phi +
          c_b[c_a_tmp_2] * a_1) + c_b[c_a_tmp_2 + 2] * a_2) + c_b[c_a_tmp_2 + 3]
          * a_3;
      }
    }

    inv(c_a_0, b_b);
    std::memcpy(&a[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&c_b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    a[14] = 0.09475;
    b[12] = 0.0;
    psi = rtb_theta[xpageoffset + 4];
    phi = std::sin(psi);
    rtb_Sum4 = std::cos(psi);
    c_b[0] = rtb_Sum4;
    c_b[4] = -phi;
    c_b[8] = 0.0;
    c_b[1] = phi;
    c_b[5] = rtb_Sum4;
    c_b[9] = 0.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      b_tmp_0 = p05_tmp_0 << 2;
      c_b[b_tmp_0 + 2] = b_tmp[p05_tmp_0];
      c_a_tmp[b_tmp_0] = h[3 * p05_tmp_0];
      c_a_tmp[b_tmp_0 + 1] = h[3 * p05_tmp_0 + 1];
      c_a_tmp[b_tmp_0 + 2] = h[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      a_1 = a[p05_tmp_0];
      a_2 = a[p05_tmp_0 + 8];
      a_3 = a[p05_tmp_0 + 12];
      rtb_Sum4 = c_a[p05_tmp_0 + 4];
      rtb_Sum = c_a[p05_tmp_0];
      rtb_Integrator_h = c_a[p05_tmp_0 + 8];
      rtb_Integrator = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_tmp = p05_tmp_0 + c_a_tmp_2;
        c_a_2[a_tmp] = ((c_b[c_a_tmp_2 + 1] * phi + c_b[c_a_tmp_2] * a_1) +
                        c_b[c_a_tmp_2 + 2] * a_2) + c_b[c_a_tmp_2 + 3] * a_3;
        c_a_1[a_tmp] = ((rtb_gd[c_a_tmp_2 + 1] * rtb_Sum4 + rtb_gd[c_a_tmp_2] *
                         rtb_Sum) + rtb_gd[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          rtb_gd[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      a_1 = c_a_2[p05_tmp_0];
      a_2 = c_a_2[p05_tmp_0 + 8];
      a_3 = c_a_2[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_0[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * phi + b[c_a_tmp_2] *
          a_1) + b[c_a_tmp_2 + 2] * a_2) + b[c_a_tmp_2 + 3] * a_3;
      }

      phi = a_0[p05_tmp_0 + 4];
      a_1 = a_0[p05_tmp_0];
      a_2 = a_0[p05_tmp_0 + 8];
      a_3 = a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((c_a_tmp[c_a_tmp_2 + 1] * phi +
          c_a_tmp[c_a_tmp_2] * a_1) + c_a_tmp[c_a_tmp_2 + 2] * a_2) +
          c_a_tmp[c_a_tmp_2 + 3] * a_3;
      }
    }

    inv(c_a_0, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      rtb_Sum4 = c_a_1[p05_tmp_0 + 4];
      rtb_Sum = c_a_1[p05_tmp_0];
      rtb_Integrator_h = c_a_1[p05_tmp_0 + 8];
      rtb_Integrator = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_Sum4 +
          b_b[c_a_tmp_2] * rtb_Sum) + b_b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          b_b[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      phi = 0.0;
      rtb_Sum4 = c_a[p05_tmp_0 + 4];
      rtb_Sum = c_a[p05_tmp_0];
      rtb_Integrator_h = c_a[p05_tmp_0 + 8];
      rtb_Integrator = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        phi += (((a[c_a_tmp_2 + 1] * rtb_Sum4 + a[c_a_tmp_2] * rtb_Sum) +
                 a[c_a_tmp_2 + 2] * rtb_Integrator_h) + a[c_a_tmp_2 + 3] *
                rtb_Integrator) * k[b_tmp_0];
      }

      p05[p05_tmp_0] = phi - static_cast<real_T>(p05_tmp[p05_tmp_0]);
    }

    psi = norm(p05);
    psi = std::acos(((psi * psi - 0.18062499999999998) - 0.15366400000000002) /
                    0.3332);
    rtb_theta[xpageoffset + 2] = psi;
    rtb_theta[6 * (i + 1) + 2] = -psi;
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    c_b_tmp[p05_tmp_0] = g[p05_tmp_0];
  }

  for (xpageoffset = 0; xpageoffset < 8; xpageoffset++) {
    psi = rtb_theta[6 * xpageoffset];
    rtb_Sum = std::sin(psi);
    phi = std::cos(psi);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      c_a_tmp_2 = d_0[p05_tmp_0];
      c_a_tmp_0[p05_tmp_0] = static_cast<int8_T>(c_a_tmp_2);
      c_a[p05_tmp_0] = c_a_tmp_2;
      b_b[p05_tmp_0] = c_a_tmp_2;
      b[p05_tmp_0] = c_a_tmp_2;
      c_b[p05_tmp_0] = static_cast<int8_T>(c_a_tmp_2);
    }

    c_a[14] = 0.0892;
    b_b[12] = 0.0;
    b[0] = phi;
    b[4] = -rtb_Sum;
    b[8] = 0.0;
    b[1] = rtb_Sum;
    b[5] = phi;
    b[9] = 0.0;
    b[2] = 0.0;
    b[6] = 0.0;
    b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      b_tmp_0 = p05_tmp_0 << 2;
      c_b[b_tmp_0] = f[3 * p05_tmp_0];
      c_b[b_tmp_0 + 1] = f[3 * p05_tmp_0 + 1];
      c_b[b_tmp_0 + 2] = f[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      rtb_Sum4 = c_a[p05_tmp_0 + 4];
      rtb_Sum = c_a[p05_tmp_0];
      rtb_Integrator_h = c_a[p05_tmp_0 + 8];
      rtb_Integrator = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * rtb_Sum4 +
          b[c_a_tmp_2] * rtb_Sum) + b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          b[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      rtb_Sum4 = c_a_1[p05_tmp_0 + 4];
      rtb_Sum = c_a_1[p05_tmp_0];
      rtb_Integrator_h = c_a_1[p05_tmp_0 + 8];
      rtb_Integrator = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_Sum4 +
          b_b[c_a_tmp_2] * rtb_Sum) + b_b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          b_b[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      rtb_Sum4 = c_a_0[p05_tmp_0 + 4];
      rtb_Sum = c_a_0[p05_tmp_0];
      rtb_Integrator_h = c_a_0[p05_tmp_0 + 8];
      rtb_Integrator = c_a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * rtb_Sum4 +
          c_b[c_a_tmp_2] * rtb_Sum) + c_b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          c_b[c_a_tmp_2 + 3] * rtb_Integrator;
      }
    }

    inv(c_a_2, c_a);
    rtb_Integrator_h = rtb_theta[6 * xpageoffset + 5];
    rtb_Sum = std::sin(rtb_Integrator_h);
    phi = std::cos(rtb_Integrator_h);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      c_a_tmp_1 = c_a_tmp_0[p05_tmp_0];
      a[p05_tmp_0] = c_a_tmp_1;
      b_b[p05_tmp_0] = c_a_tmp_1;
      b[p05_tmp_0] = c_a_tmp_1;
      c_b[p05_tmp_0] = c_a_tmp_1;
    }

    a[14] = 0.0825;
    b_b[12] = 0.0;
    b[0] = phi;
    b[4] = -rtb_Sum;
    b[8] = 0.0;
    b[1] = rtb_Sum;
    b[5] = phi;
    b[9] = 0.0;
    b[2] = 0.0;
    b[6] = 0.0;
    b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      b_tmp_0 = p05_tmp_0 << 2;
      c_b[b_tmp_0] = c_b_tmp[3 * p05_tmp_0];
      c_b[b_tmp_0 + 1] = c_b_tmp[3 * p05_tmp_0 + 1];
      c_b[b_tmp_0 + 2] = c_b_tmp[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      a_1 = a[p05_tmp_0];
      a_2 = a[p05_tmp_0 + 8];
      a_3 = a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * phi + b[c_a_tmp_2] *
          a_1) + b[c_a_tmp_2 + 2] * a_2) + b[c_a_tmp_2 + 3] * a_3;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      a_1 = c_a_2[p05_tmp_0];
      a_2 = c_a_2[p05_tmp_0 + 8];
      a_3 = c_a_2[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_0[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * phi + b_b[c_a_tmp_2]
          * a_1) + b_b[c_a_tmp_2 + 2] * a_2) + b_b[c_a_tmp_2 + 3] * a_3;
      }

      phi = a_0[p05_tmp_0 + 4];
      a_1 = a_0[p05_tmp_0];
      a_2 = a_0[p05_tmp_0 + 8];
      a_3 = a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * phi +
          c_b[c_a_tmp_2] * a_1) + c_b[c_a_tmp_2 + 2] * a_2) + c_b[c_a_tmp_2 + 3]
          * a_3;
      }
    }

    inv(c_a_0, b_b);
    rtb_Integrator_h = rtb_theta[6 * xpageoffset + 4];
    phi = std::sin(rtb_Integrator_h);
    rtb_Sum4 = std::cos(rtb_Integrator_h);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      c_a_tmp_1 = c_a_tmp_0[p05_tmp_0];
      a[p05_tmp_0] = c_a_tmp_1;
      b[p05_tmp_0] = c_a_tmp_1;
      c_b[p05_tmp_0] = c_a_tmp_1;
      c_a_tmp[p05_tmp_0] = c_a_tmp_1;
    }

    a[14] = 0.09475;
    b[12] = 0.0;
    c_b[0] = rtb_Sum4;
    c_b[4] = -phi;
    c_b[8] = 0.0;
    c_b[1] = phi;
    c_b[5] = rtb_Sum4;
    c_b[9] = 0.0;
    c_b[2] = 0.0;
    c_b[6] = 0.0;
    c_b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      c_a_tmp_2 = p05_tmp_0 << 2;
      c_a_tmp[c_a_tmp_2] = h[3 * p05_tmp_0];
      c_a_tmp[c_a_tmp_2 + 1] = h[3 * p05_tmp_0 + 1];
      c_a_tmp[c_a_tmp_2 + 2] = h[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      a_1 = a[p05_tmp_0];
      a_2 = a[p05_tmp_0 + 8];
      a_3 = a[p05_tmp_0 + 12];
      rtb_Sum4 = c_a[p05_tmp_0 + 4];
      rtb_Sum = c_a[p05_tmp_0];
      rtb_Integrator_h = c_a[p05_tmp_0 + 8];
      rtb_Integrator = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_tmp = p05_tmp_0 + c_a_tmp_2;
        c_a_2[a_tmp] = ((c_b[c_a_tmp_2 + 1] * phi + c_b[c_a_tmp_2] * a_1) +
                        c_b[c_a_tmp_2 + 2] * a_2) + c_b[c_a_tmp_2 + 3] * a_3;
        c_a_1[a_tmp] = ((rtb_gd[c_a_tmp_2 + 1] * rtb_Sum4 + rtb_gd[c_a_tmp_2] *
                         rtb_Sum) + rtb_gd[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          rtb_gd[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      a_1 = c_a_2[p05_tmp_0];
      a_2 = c_a_2[p05_tmp_0 + 8];
      a_3 = c_a_2[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_0[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * phi + b[c_a_tmp_2] *
          a_1) + b[c_a_tmp_2 + 2] * a_2) + b[c_a_tmp_2 + 3] * a_3;
      }

      phi = a_0[p05_tmp_0 + 4];
      a_1 = a_0[p05_tmp_0];
      a_2 = a_0[p05_tmp_0 + 8];
      a_3 = a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((c_a_tmp[c_a_tmp_2 + 1] * phi +
          c_a_tmp[c_a_tmp_2] * a_1) + c_a_tmp[c_a_tmp_2 + 2] * a_2) +
          c_a_tmp[c_a_tmp_2 + 3] * a_3;
      }
    }

    inv(c_a_0, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      rtb_Sum4 = c_a_1[p05_tmp_0 + 4];
      rtb_Sum = c_a_1[p05_tmp_0];
      rtb_Integrator_h = c_a_1[p05_tmp_0 + 8];
      rtb_Integrator = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_Sum4 +
          b_b[c_a_tmp_2] * rtb_Sum) + b_b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          b_b[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      phi = 0.0;
      rtb_Sum4 = c_a[p05_tmp_0 + 4];
      rtb_Sum = c_a[p05_tmp_0];
      rtb_Integrator_h = c_a[p05_tmp_0 + 8];
      rtb_Integrator = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        i = b_tmp_0 << 2;
        a_1 = ((a[i + 1] * rtb_Sum4 + a[i] * rtb_Sum) + a[i + 2] *
               rtb_Integrator_h) + a[i + 3] * rtb_Integrator;
        T14[p05_tmp_0 + i] = a_1;
        phi += a_1 * k[b_tmp_0];
      }

      p05[p05_tmp_0] = phi - static_cast<real_T>(p05_tmp[p05_tmp_0]);
    }

    rtb_Integrator_h = rtb_theta[6 * xpageoffset + 2];
    rtb_Sum4 = std::sin(rtb_Integrator_h);
    phi = std::asin(-0.392 * rtb_Sum4 / norm(p05)) - std::atan2(p05[1], -p05[0]);
    rtb_theta[6 * xpageoffset + 1] = phi;
    rtb_Sum = std::cos(rtb_Integrator_h);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      c_a_tmp_1 = c_a_tmp_0[p05_tmp_0];
      c_a[p05_tmp_0] = c_a_tmp_1;
      b_b[p05_tmp_0] = c_a_tmp_1;
      b[p05_tmp_0] = c_a_tmp_1;
      c_b[p05_tmp_0] = c_a_tmp_1;
    }

    c_a[14] = 0.0;
    b_b[12] = -0.392;
    b[0] = rtb_Sum;
    b[4] = -rtb_Sum4;
    b[8] = 0.0;
    b[1] = rtb_Sum4;
    b[5] = rtb_Sum;
    b[9] = 0.0;
    b[2] = 0.0;
    b[6] = 0.0;
    b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      b_tmp_0 = p05_tmp_0 << 2;
      c_b[b_tmp_0] = c_b_tmp[3 * p05_tmp_0];
      c_b[b_tmp_0 + 1] = c_b_tmp[3 * p05_tmp_0 + 1];
      c_b[b_tmp_0 + 2] = c_b_tmp[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      rtb_Sum4 = c_a[p05_tmp_0 + 4];
      rtb_Sum = c_a[p05_tmp_0];
      rtb_Integrator_h = c_a[p05_tmp_0 + 8];
      rtb_Integrator = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * rtb_Sum4 +
          b[c_a_tmp_2] * rtb_Sum) + b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          b[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      rtb_Sum4 = c_a_1[p05_tmp_0 + 4];
      rtb_Sum = c_a_1[p05_tmp_0];
      rtb_Integrator_h = c_a_1[p05_tmp_0 + 8];
      rtb_Integrator = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_Sum4 +
          b_b[c_a_tmp_2] * rtb_Sum) + b_b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          b_b[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      rtb_Sum4 = c_a_0[p05_tmp_0 + 4];
      rtb_Sum = c_a_0[p05_tmp_0];
      rtb_Integrator_h = c_a_0[p05_tmp_0 + 8];
      rtb_Integrator = c_a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * rtb_Sum4 +
          c_b[c_a_tmp_2] * rtb_Sum) + c_b[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          c_b[c_a_tmp_2 + 3] * rtb_Integrator;
      }
    }

    inv(c_a_2, c_a);
    rtb_Sum = std::sin(phi);
    phi = std::cos(phi);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      c_a_tmp_1 = c_a_tmp_0[p05_tmp_0];
      a[p05_tmp_0] = c_a_tmp_1;
      b_b[p05_tmp_0] = c_a_tmp_1;
      b[p05_tmp_0] = c_a_tmp_1;
      c_b[p05_tmp_0] = c_a_tmp_1;
    }

    a[14] = 0.0;
    b_b[12] = -0.425;
    b[0] = phi;
    b[4] = -rtb_Sum;
    b[8] = 0.0;
    b[1] = rtb_Sum;
    b[5] = phi;
    b[9] = 0.0;
    b[2] = 0.0;
    b[6] = 0.0;
    b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      b_tmp_0 = p05_tmp_0 << 2;
      c_b[b_tmp_0] = c_b_tmp[3 * p05_tmp_0];
      c_b[b_tmp_0 + 1] = c_b_tmp[3 * p05_tmp_0 + 1];
      c_b[b_tmp_0 + 2] = c_b_tmp[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      a_1 = a[p05_tmp_0];
      a_2 = a[p05_tmp_0 + 8];
      a_3 = a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * phi + b[c_a_tmp_2] *
          a_1) + b[c_a_tmp_2 + 2] * a_2) + b[c_a_tmp_2 + 3] * a_3;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      a_1 = c_a_2[p05_tmp_0];
      a_2 = c_a_2[p05_tmp_0 + 8];
      a_3 = c_a_2[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_0[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * phi + b_b[c_a_tmp_2]
          * a_1) + b_b[c_a_tmp_2 + 2] * a_2) + b_b[c_a_tmp_2 + 3] * a_3;
      }

      phi = a_0[p05_tmp_0 + 4];
      a_1 = a_0[p05_tmp_0];
      a_2 = a_0[p05_tmp_0 + 8];
      a_3 = a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * phi +
          c_b[c_a_tmp_2] * a_1) + c_b[c_a_tmp_2 + 2] * a_2) + c_b[c_a_tmp_2 + 3]
          * a_3;
      }
    }

    inv(c_a_0, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      rtb_Sum4 = c_a[p05_tmp_0 + 4];
      rtb_Sum = c_a[p05_tmp_0];
      rtb_Integrator_h = c_a[p05_tmp_0 + 8];
      rtb_Integrator = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_2] = ((a[c_a_tmp_2 + 1] * rtb_Sum4 +
          a[c_a_tmp_2] * rtb_Sum) + a[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          a[c_a_tmp_2 + 3] * rtb_Integrator;
      }

      rtb_Sum4 = c_a_1[p05_tmp_0 + 4];
      rtb_Sum = c_a_1[p05_tmp_0];
      rtb_Integrator_h = c_a_1[p05_tmp_0 + 8];
      rtb_Integrator = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_tmp[p05_tmp_0 + c_a_tmp_2] = ((T14[c_a_tmp_2 + 1] * rtb_Sum4 +
          T14[c_a_tmp_2] * rtb_Sum) + T14[c_a_tmp_2 + 2] * rtb_Integrator_h) +
          T14[c_a_tmp_2 + 3] * rtb_Integrator;
      }
    }

    rtb_theta[6 * xpageoffset + 3] = std::atan2(c_a_tmp[1], c_a_tmp[0]);
    rtb_theta[6 * xpageoffset] = psi - 3.1415926535897931;
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 8; p05_tmp_0++) {
    // MATLAB Function: '<S2>/MATLAB Function2' incorporates:
    //   Inport: '<Root>/ori_theta_arr'

    for (b_tmp_0 = 0; b_tmp_0 < 6; b_tmp_0++) {
      xpageoffset = 6 * p05_tmp_0 + b_tmp_0;
      psi = rtb_theta[xpageoffset];
      if (psi <= -3.1415926535897931) {
        psi += 6.2831853071795862;
        rtb_theta[xpageoffset] = psi;
      } else if (psi > 3.1415926535897931) {
        psi -= 6.2831853071795862;
        rtb_theta[xpageoffset] = psi;
      }

      x[xpageoffset] = psi - rtU.ori_theta_arr[b_tmp_0];
    }
  }

  // End of MATLAB Function: '<S2>/MATLAB Function'

  // MATLAB Function: '<S2>/MATLAB Function2'
  for (p05_tmp_0 = 0; p05_tmp_0 < 48; p05_tmp_0++) {
    y[p05_tmp_0] = std::abs(x[p05_tmp_0]);
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 8; p05_tmp_0++) {
    xpageoffset = p05_tmp_0 * 6;
    psi = y[xpageoffset];
    for (b_tmp_0 = 0; b_tmp_0 < 5; b_tmp_0++) {
      psi += y[(xpageoffset + b_tmp_0) + 1];
    }

    varargin_1[p05_tmp_0] = psi;
  }

  phi = varargin_1[0];
  p05_tmp_0 = 0;
  for (xpageoffset = 0; xpageoffset < 7; xpageoffset++) {
    psi = varargin_1[xpageoffset + 1];
    if (phi > psi) {
      phi = psi;
      p05_tmp_0 = xpageoffset + 1;
    }
  }

  // TransferFcn: '<S1>/Transfer Fcn1'
  rtb_Integrator = (6.0 * rtX.TransferFcn1_CSTATE[1] + rtX.TransferFcn1_CSTATE[0])
    + 10.0 * rtX.TransferFcn1_CSTATE[2];

  // TransferFcn: '<S1>/Transfer Fcn2'
  psi = (6.0 * rtX.TransferFcn2_CSTATE[1] + rtX.TransferFcn2_CSTATE[0]) + 10.0 *
    rtX.TransferFcn2_CSTATE[2];

  // Sum: '<S1>/Sum1' incorporates:
  //   MATLAB Function: '<S2>/MATLAB Function2'

  phi = rtb_theta[6 * p05_tmp_0] - rtb_Integrator;

  // Gain: '<S43>/Filter Coefficient' incorporates:
  //   Gain: '<S34>/Derivative Gain'
  //   Integrator: '<S35>/Filter'
  //   Sum: '<S35>/SumD'

  rtB.FilterCoefficient = (0.0 - rtX.Filter_CSTATE) * 100.0;

  // Sum: '<S49>/Sum' incorporates:
  //   Gain: '<S45>/Proportional Gain'
  //   Integrator: '<S40>/Integrator'

  rtB.Sum = (116.803030033433 * phi + rtX.Integrator_CSTATE) +
    rtB.FilterCoefficient;

  // Gain: '<S37>/Integral Gain'
  rtB.IntegralGain = 1910.35619712381 * phi;

  // TransferFcn: '<S1>/Transfer Fcn3'
  phi = (6.0 * rtX.TransferFcn3_CSTATE[1] + rtX.TransferFcn3_CSTATE[0]) + 10.0 *
    rtX.TransferFcn3_CSTATE[2];

  // TransferFcn: '<S1>/Transfer Fcn5'
  rtb_Sum4 = (6.0 * rtX.TransferFcn5_CSTATE[1] + rtX.TransferFcn5_CSTATE[0]) +
    10.0 * rtX.TransferFcn5_CSTATE[2];

  // TransferFcn: '<S1>/Transfer Fcn4'
  rtb_Sum = (6.0 * rtX.TransferFcn4_CSTATE[1] + rtX.TransferFcn4_CSTATE[0]) +
    10.0 * rtX.TransferFcn4_CSTATE[2];

  // TransferFcn: '<S1>/Transfer Fcn6'
  rtb_Integrator_h = (6.0 * rtX.TransferFcn6_CSTATE[1] +
                      rtX.TransferFcn6_CSTATE[0]) + 10.0 *
    rtX.TransferFcn6_CSTATE[2];

  // Outport: '<Root>/actual_theta_arr'
  rtY.actual_theta_arr[0] = rtb_Integrator;
  rtY.actual_theta_arr[1] = psi;
  rtY.actual_theta_arr[2] = phi;
  rtY.actual_theta_arr[3] = rtb_Sum4;
  rtY.actual_theta_arr[4] = rtb_Sum;
  rtY.actual_theta_arr[5] = rtb_Integrator_h;

  // Sum: '<S1>/Sum5' incorporates:
  //   MATLAB Function: '<S2>/MATLAB Function2'

  rtb_Integrator_h = rtb_theta[6 * p05_tmp_0 + 5] - rtb_Integrator_h;

  // Gain: '<S235>/Filter Coefficient' incorporates:
  //   Gain: '<S226>/Derivative Gain'
  //   Integrator: '<S227>/Filter'
  //   Sum: '<S227>/SumD'

  rtB.FilterCoefficient_c = (0.0 - rtX.Filter_CSTATE_g) * 100.0;

  // Sum: '<S241>/Sum' incorporates:
  //   Gain: '<S237>/Proportional Gain'
  //   Integrator: '<S232>/Integrator'

  rtB.Sum_l = (116.803030033433 * rtb_Integrator_h + rtX.Integrator_CSTATE_l) +
    rtB.FilterCoefficient_c;

  // Gain: '<S229>/Integral Gain'
  rtB.IntegralGain_h = 1910.35619712381 * rtb_Integrator_h;

  // Sum: '<S1>/Sum' incorporates:
  //   MATLAB Function: '<S2>/MATLAB Function2'

  rtb_Sum = rtb_theta[6 * p05_tmp_0 + 4] - rtb_Sum;

  // Gain: '<S283>/Filter Coefficient' incorporates:
  //   Gain: '<S274>/Derivative Gain'
  //   Integrator: '<S275>/Filter'
  //   Sum: '<S275>/SumD'

  rtB.FilterCoefficient_n = (0.0 - rtX.Filter_CSTATE_b) * 100.0;

  // Sum: '<S289>/Sum' incorporates:
  //   Gain: '<S285>/Proportional Gain'
  //   Integrator: '<S280>/Integrator'

  rtB.Sum_e = (116.803030033433 * rtb_Sum + rtX.Integrator_CSTATE_o) +
    rtB.FilterCoefficient_n;

  // Gain: '<S277>/Integral Gain'
  rtB.IntegralGain_k = 1910.35619712381 * rtb_Sum;

  // Sum: '<S1>/Sum4' incorporates:
  //   MATLAB Function: '<S2>/MATLAB Function2'

  rtb_Sum4 = rtb_theta[6 * p05_tmp_0 + 3] - rtb_Sum4;

  // Gain: '<S187>/Filter Coefficient' incorporates:
  //   Gain: '<S178>/Derivative Gain'
  //   Integrator: '<S179>/Filter'
  //   Sum: '<S179>/SumD'

  rtB.FilterCoefficient_f = (-0.189486999754633 * rtb_Sum4 - rtX.Filter_CSTATE_o)
    * 63.8304243098863;

  // Sum: '<S193>/Sum' incorporates:
  //   Gain: '<S189>/Proportional Gain'
  //   Integrator: '<S184>/Integrator'

  rtB.Sum_a = (47.3438798562812 * rtb_Sum4 + rtX.Integrator_CSTATE_f) +
    rtB.FilterCoefficient_f;

  // Gain: '<S181>/Integral Gain'
  rtB.IntegralGain_j = 206.276392279903 * rtb_Sum4;

  // Sum: '<S1>/Sum3' incorporates:
  //   MATLAB Function: '<S2>/MATLAB Function2'

  phi = rtb_theta[6 * p05_tmp_0 + 2] - phi;

  // Gain: '<S139>/Filter Coefficient' incorporates:
  //   Gain: '<S130>/Derivative Gain'
  //   Integrator: '<S131>/Filter'
  //   Sum: '<S131>/SumD'

  rtB.FilterCoefficient_n4 = (0.0 - rtX.Filter_CSTATE_b0) * 100.0;

  // Sum: '<S145>/Sum' incorporates:
  //   Gain: '<S141>/Proportional Gain'
  //   Integrator: '<S136>/Integrator'

  rtB.Sum_j = (116.803030033433 * phi + rtX.Integrator_CSTATE_ot) +
    rtB.FilterCoefficient_n4;

  // Gain: '<S133>/Integral Gain'
  rtB.IntegralGain_g = 1910.35619712381 * phi;

  // Sum: '<S1>/Sum2' incorporates:
  //   MATLAB Function: '<S2>/MATLAB Function2'

  psi = rtb_theta[6 * p05_tmp_0 + 1] - psi;

  // Gain: '<S91>/Filter Coefficient' incorporates:
  //   Gain: '<S82>/Derivative Gain'
  //   Integrator: '<S83>/Filter'
  //   Sum: '<S83>/SumD'

  rtB.FilterCoefficient_l = (0.0 - rtX.Filter_CSTATE_p) * 100.0;

  // Sum: '<S97>/Sum' incorporates:
  //   Gain: '<S93>/Proportional Gain'
  //   Integrator: '<S88>/Integrator'

  rtB.Sum_m = (116.803030033433 * psi + rtX.Integrator_CSTATE_j) +
    rtB.FilterCoefficient_l;

  // Gain: '<S85>/Integral Gain'
  rtB.IntegralGain_p = 1910.35619712381 * psi;
  if (rtmIsMajorTimeStep((&rtM))) {
    rt_ertODEUpdateContinuousStates(&(&rtM)->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.

    ++(&rtM)->Timing.clockTick0;
    (&rtM)->Timing.t[0] = rtsiGetSolverStopTime(&(&rtM)->solverInfo);

    {
      // Update absolute timer for sample time: [0.01s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.01, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.

      (&rtM)->Timing.clockTick1++;
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void URController::URController_derivatives()
{
  URController::XDot *_rtXdot;
  _rtXdot = ((XDot *) (&rtM)->derivs);

  // Derivatives for TransferFcn: '<S1>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE[0] = -7.0 * rtX.TransferFcn1_CSTATE[1];
  _rtXdot->TransferFcn1_CSTATE[0] -= rtX.TransferFcn1_CSTATE[2];
  _rtXdot->TransferFcn1_CSTATE[1] = rtX.TransferFcn1_CSTATE[0];
  _rtXdot->TransferFcn1_CSTATE[2] = rtX.TransferFcn1_CSTATE[1];
  _rtXdot->TransferFcn1_CSTATE[0] += rtB.Sum;

  // Derivatives for Integrator: '<S35>/Filter'
  _rtXdot->Filter_CSTATE = rtB.FilterCoefficient;

  // Derivatives for Integrator: '<S40>/Integrator'
  _rtXdot->Integrator_CSTATE = rtB.IntegralGain;

  // Derivatives for TransferFcn: '<S1>/Transfer Fcn2'
  _rtXdot->TransferFcn2_CSTATE[0] = -7.0 * rtX.TransferFcn2_CSTATE[1];
  _rtXdot->TransferFcn2_CSTATE[0] -= rtX.TransferFcn2_CSTATE[2];
  _rtXdot->TransferFcn2_CSTATE[1] = rtX.TransferFcn2_CSTATE[0];
  _rtXdot->TransferFcn2_CSTATE[2] = rtX.TransferFcn2_CSTATE[1];
  _rtXdot->TransferFcn2_CSTATE[0] += rtB.Sum_m;

  // Derivatives for TransferFcn: '<S1>/Transfer Fcn3'
  _rtXdot->TransferFcn3_CSTATE[0] = -7.0 * rtX.TransferFcn3_CSTATE[1];
  _rtXdot->TransferFcn3_CSTATE[0] -= rtX.TransferFcn3_CSTATE[2];
  _rtXdot->TransferFcn3_CSTATE[1] = rtX.TransferFcn3_CSTATE[0];
  _rtXdot->TransferFcn3_CSTATE[2] = rtX.TransferFcn3_CSTATE[1];
  _rtXdot->TransferFcn3_CSTATE[0] += rtB.Sum_j;

  // Derivatives for TransferFcn: '<S1>/Transfer Fcn5'
  _rtXdot->TransferFcn5_CSTATE[0] = -7.0 * rtX.TransferFcn5_CSTATE[1];
  _rtXdot->TransferFcn5_CSTATE[0] -= rtX.TransferFcn5_CSTATE[2];
  _rtXdot->TransferFcn5_CSTATE[1] = rtX.TransferFcn5_CSTATE[0];
  _rtXdot->TransferFcn5_CSTATE[2] = rtX.TransferFcn5_CSTATE[1];
  _rtXdot->TransferFcn5_CSTATE[0] += rtB.Sum_a;

  // Derivatives for TransferFcn: '<S1>/Transfer Fcn4'
  _rtXdot->TransferFcn4_CSTATE[0] = -7.0 * rtX.TransferFcn4_CSTATE[1];
  _rtXdot->TransferFcn4_CSTATE[0] -= rtX.TransferFcn4_CSTATE[2];
  _rtXdot->TransferFcn4_CSTATE[1] = rtX.TransferFcn4_CSTATE[0];
  _rtXdot->TransferFcn4_CSTATE[2] = rtX.TransferFcn4_CSTATE[1];
  _rtXdot->TransferFcn4_CSTATE[0] += rtB.Sum_e;

  // Derivatives for TransferFcn: '<S1>/Transfer Fcn6'
  _rtXdot->TransferFcn6_CSTATE[0] = -7.0 * rtX.TransferFcn6_CSTATE[1];
  _rtXdot->TransferFcn6_CSTATE[0] -= rtX.TransferFcn6_CSTATE[2];
  _rtXdot->TransferFcn6_CSTATE[1] = rtX.TransferFcn6_CSTATE[0];
  _rtXdot->TransferFcn6_CSTATE[2] = rtX.TransferFcn6_CSTATE[1];
  _rtXdot->TransferFcn6_CSTATE[0] += rtB.Sum_l;

  // Derivatives for Integrator: '<S227>/Filter'
  _rtXdot->Filter_CSTATE_g = rtB.FilterCoefficient_c;

  // Derivatives for Integrator: '<S232>/Integrator'
  _rtXdot->Integrator_CSTATE_l = rtB.IntegralGain_h;

  // Derivatives for Integrator: '<S275>/Filter'
  _rtXdot->Filter_CSTATE_b = rtB.FilterCoefficient_n;

  // Derivatives for Integrator: '<S280>/Integrator'
  _rtXdot->Integrator_CSTATE_o = rtB.IntegralGain_k;

  // Derivatives for Integrator: '<S179>/Filter'
  _rtXdot->Filter_CSTATE_o = rtB.FilterCoefficient_f;

  // Derivatives for Integrator: '<S184>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtB.IntegralGain_j;

  // Derivatives for Integrator: '<S131>/Filter'
  _rtXdot->Filter_CSTATE_b0 = rtB.FilterCoefficient_n4;

  // Derivatives for Integrator: '<S136>/Integrator'
  _rtXdot->Integrator_CSTATE_ot = rtB.IntegralGain_g;

  // Derivatives for Integrator: '<S83>/Filter'
  _rtXdot->Filter_CSTATE_p = rtB.FilterCoefficient_l;

  // Derivatives for Integrator: '<S88>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtB.IntegralGain_p;
}

// Model initialize function
void URController::initialize()
{
  // Registration code
  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&(&rtM)->solverInfo, &(&rtM)->Timing.simTimeStep);
    rtsiSetTPtr(&(&rtM)->solverInfo, &rtmGetTPtr((&rtM)));
    rtsiSetStepSizePtr(&(&rtM)->solverInfo, &(&rtM)->Timing.stepSize0);
    rtsiSetdXPtr(&(&rtM)->solverInfo, &(&rtM)->derivs);
    rtsiSetContStatesPtr(&(&rtM)->solverInfo, (real_T **) &(&rtM)->contStates);
    rtsiSetNumContStatesPtr(&(&rtM)->solverInfo, &(&rtM)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&rtM)->solverInfo, &(&rtM)
      ->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&rtM)->solverInfo, &(&rtM)
      ->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&rtM)->solverInfo, &(&rtM)
      ->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&rtM)->solverInfo, (&rtmGetErrorStatus((&rtM))));
    rtsiSetRTModelPtr(&(&rtM)->solverInfo, (&rtM));
  }

  rtsiSetSimTimeStep(&(&rtM)->solverInfo, MAJOR_TIME_STEP);
  (&rtM)->intgData.y = (&rtM)->odeY;
  (&rtM)->intgData.f[0] = (&rtM)->odeF[0];
  (&rtM)->intgData.f[1] = (&rtM)->odeF[1];
  (&rtM)->intgData.f[2] = (&rtM)->odeF[2];
  (&rtM)->intgData.f[3] = (&rtM)->odeF[3];
  (&rtM)->contStates = ((X *) &rtX);
  rtsiSetSolverData(&(&rtM)->solverInfo, static_cast<void *>(&(&rtM)->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&(&rtM)->solverInfo, false);
  rtsiSetSolverName(&(&rtM)->solverInfo,"ode4");
  rtmSetTPtr((&rtM), &(&rtM)->Timing.tArray[0]);
  (&rtM)->Timing.stepSize0 = 0.01;

  // InitializeConditions for Integrator: '<S35>/Filter'
  rtX.Filter_CSTATE = 0.0;

  // InitializeConditions for Integrator: '<S40>/Integrator'
  rtX.Integrator_CSTATE = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn1'
  rtX.TransferFcn1_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn2'
  rtX.TransferFcn2_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn3'
  rtX.TransferFcn3_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn5'
  rtX.TransferFcn5_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn4'
  rtX.TransferFcn4_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn6'
  rtX.TransferFcn6_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn1'
  rtX.TransferFcn1_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn2'
  rtX.TransferFcn2_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn3'
  rtX.TransferFcn3_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn5'
  rtX.TransferFcn5_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn4'
  rtX.TransferFcn4_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn6'
  rtX.TransferFcn6_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn1'
  rtX.TransferFcn1_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn2'
  rtX.TransferFcn2_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn3'
  rtX.TransferFcn3_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn5'
  rtX.TransferFcn5_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn4'
  rtX.TransferFcn4_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S1>/Transfer Fcn6'
  rtX.TransferFcn6_CSTATE[2] = 0.0;

  // InitializeConditions for Integrator: '<S227>/Filter'
  rtX.Filter_CSTATE_g = 0.0;

  // InitializeConditions for Integrator: '<S232>/Integrator'
  rtX.Integrator_CSTATE_l = 0.0;

  // InitializeConditions for Integrator: '<S275>/Filter'
  rtX.Filter_CSTATE_b = 0.0;

  // InitializeConditions for Integrator: '<S280>/Integrator'
  rtX.Integrator_CSTATE_o = 0.0;

  // InitializeConditions for Integrator: '<S179>/Filter'
  rtX.Filter_CSTATE_o = 0.0;

  // InitializeConditions for Integrator: '<S184>/Integrator'
  rtX.Integrator_CSTATE_f = 0.0;

  // InitializeConditions for Integrator: '<S131>/Filter'
  rtX.Filter_CSTATE_b0 = 0.0;

  // InitializeConditions for Integrator: '<S136>/Integrator'
  rtX.Integrator_CSTATE_ot = 0.0;

  // InitializeConditions for Integrator: '<S83>/Filter'
  rtX.Filter_CSTATE_p = 0.0;

  // InitializeConditions for Integrator: '<S88>/Integrator'
  rtX.Integrator_CSTATE_j = 0.0;
}

// Model terminate function
void URController::terminate()
{
  // (no terminate code required)
}

// Constructor
URController::URController() :
  rtU(),
  rtY(),
  rtB(),
  rtX(),
  rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
URController::~URController() = default;

// Real-Time Model get method
URController::RT_MODEL * URController::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
