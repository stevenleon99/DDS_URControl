//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: URController.cpp
//
// Code generated for Simulink model 'URController'.
//
// Model version                  : 1.235
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Wed Nov  6 19:45:33 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Custom
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "URController.h"
#include "rtwtypes.h"
#include <cmath>
#include <cstring>
#include "URController_types.h"
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

//
// Output and update for atomic system:
//    '<S13>/MATLAB Function'
//    '<S14>/MATLAB Function'
//    '<S15>/MATLAB Function'
//    '<S16>/MATLAB Function'
//    '<S17>/MATLAB Function'
//    '<S18>/MATLAB Function'
//
void URController::MATLABFunction(real_T rtu_posRef, real_T rtu_pos, real_T
  rtu_vel, real_T rtu_maxAcc, real_T rtu_maxVel, real_T rtu_CYCLE_FREQ,
  B_MATLABFunction *localB, DW_MATLABFunction *localDW)
{
  real_T distanceTotal;
  real_T sM_tmp;
  real_T tB_tmp;
  real_T u;
  if ((!localDW->timeBrake_not_empty) || (!localDW->distanceBrake_not_empty) ||
      (!localDW->timeAccelerate_not_empty) ||
      (!localDW->distanceAccelerate_not_empty) ||
      (!localDW->distanceConstVelocity_not_empty) ||
      (!localDW->timeConstVelocity_not_empty) ||
      (!localDW->timeDecelerate_not_empty) || (!localDW->shape_not_empty) ||
      (!localDW->velTop_not_empty) || (!localDW->signM_not_empty) ||
      (!localDW->oldPoseRef_not_empty) || (!localDW->oldPos_not_empty) ||
      (!localDW->oldVel_not_empty) || (!localDW->time_not_empty)) {
    localDW->timeBrake = 0.0;
    localDW->timeBrake_not_empty = true;
    localDW->distanceBrake = 0.0;
    localDW->distanceBrake_not_empty = true;
    localDW->timeAccelerate = 0.0;
    localDW->timeAccelerate_not_empty = true;
    localDW->distanceAccelerate = 0.0;
    localDW->distanceAccelerate_not_empty = true;
    localDW->distanceConstVelocity = 0.0;
    localDW->distanceConstVelocity_not_empty = true;
    localDW->timeConstVelocity = 0.0;
    localDW->timeConstVelocity_not_empty = true;
    localDW->timeDecelerate = 0.0;
    localDW->timeDecelerate_not_empty = true;
    localDW->shape = 0.0;
    localDW->shape_not_empty = true;
    localDW->velTop = 0.0;
    localDW->velTop_not_empty = true;
    localDW->signM = 0.0;
    localDW->signM_not_empty = true;
    localDW->oldPoseRef = 0.0;
    localDW->oldPoseRef_not_empty = true;
    localDW->oldPos = 0.0;
    localDW->oldPos_not_empty = true;
    localDW->oldVel = 0.0;
    localDW->oldVel_not_empty = true;
    localDW->time = 0.0;
    localDW->time_not_empty = true;
    localB->tB = 0.0;
    localB->dB = 0.0;
    localB->tA = 0.0;
    localB->dA = 0.0;
    localB->dCV = 0.0;
    localB->tCV = 0.0;
    localB->tD = 0.0;
    localB->s = 0.0;
    localB->vT = 0.0;
    localB->sM = 0.0;
    localB->t = 0.0;
    localB->oV = 0.0;
    localB->oP = 0.0;
  } else {
    if (localDW->oldPoseRef != rtu_posRef) {
      localDW->oldPos = rtu_pos;
      localDW->oldVel = rtu_vel;
      localDW->oldPoseRef = rtu_posRef;
      localDW->time = 0.0;
      tB_tmp = std::abs(localDW->oldVel);
      localDW->timeBrake = tB_tmp / rtu_maxAcc;
      localDW->distanceBrake = localDW->timeBrake * tB_tmp / 2.0;
      if (localDW->oldVel < 0.0) {
        sM_tmp = -1.0;
      } else {
        sM_tmp = (localDW->oldVel > 0.0);
      }

      u = rtu_posRef - (sM_tmp * localDW->distanceBrake + localDW->oldPos);
      if (u < 0.0) {
        localDW->signM = -1.0;
      } else {
        localDW->signM = (u > 0.0);
      }

      if (localDW->signM != sM_tmp) {
        localDW->timeAccelerate = rtu_maxVel / rtu_maxAcc;
        localDW->distanceAccelerate = rtu_maxVel / 2.0 * localDW->timeAccelerate;
      } else {
        localDW->timeBrake = 0.0;
        localDW->distanceBrake = 0.0;
        localDW->timeAccelerate = (rtu_maxVel - tB_tmp) / rtu_maxAcc;
        localDW->distanceAccelerate = (rtu_maxVel + tB_tmp) *
          localDW->timeAccelerate / 2.0;
      }

      u = rtu_posRef - localDW->oldPos;
      distanceTotal = std::abs(localDW->signM * localDW->distanceBrake + u);
      localDW->timeDecelerate = rtu_maxVel / rtu_maxAcc;
      localDW->distanceConstVelocity = distanceTotal - (localDW->timeDecelerate *
        rtu_maxVel / 2.0 + localDW->distanceAccelerate);
      localDW->timeConstVelocity = localDW->distanceConstVelocity / rtu_maxVel;
      if (localDW->timeConstVelocity > 0.0) {
        localDW->shape = 1.0;
        localDW->velTop = 0.0;
      } else {
        localDW->shape = 0.0;
        if (localDW->signM != sM_tmp) {
          localDW->velTop = std::sqrt(rtu_maxAcc * distanceTotal);
          localDW->timeAccelerate = localDW->velTop / rtu_maxAcc;
          localDW->distanceAccelerate = localDW->velTop / 2.0 *
            localDW->timeAccelerate;
        } else {
          localDW->timeBrake = 0.0;
          localDW->distanceBrake = 0.0;
          localDW->velTop = std::sqrt(localDW->oldVel * localDW->oldVel * 0.5 +
            std::abs(u) * rtu_maxAcc);
          localDW->timeAccelerate = (localDW->velTop - tB_tmp) / rtu_maxAcc;
          localDW->distanceAccelerate = (localDW->velTop + tB_tmp) *
            localDW->timeAccelerate / 2.0;
        }

        localDW->timeDecelerate = localDW->velTop / rtu_maxAcc;
      }
    }

    localB->tB = localDW->timeBrake;
    localB->dB = localDW->distanceBrake;
    localB->tA = localDW->timeAccelerate;
    localB->dA = localDW->distanceAccelerate;
    localB->dCV = localDW->distanceConstVelocity;
    localB->tCV = localDW->timeConstVelocity;
    localB->tD = localDW->timeDecelerate;
    localB->s = localDW->shape;
    localB->vT = localDW->velTop;
    localB->sM = localDW->signM;
    localDW->time += rtu_CYCLE_FREQ;
    localB->t = localDW->time;
    localB->oV = localDW->oldVel;
    localB->oP = localDW->oldPos;
  }
}

//
// Output and update for atomic system:
//    '<S13>/MATLAB Function1'
//    '<S14>/MATLAB Function1'
//    '<S15>/MATLAB Function1'
//    '<S16>/MATLAB Function1'
//    '<S17>/MATLAB Function1'
//    '<S18>/MATLAB Function1'
//
void URController::MATLABFunction1(real_T rtu_timeBrake, real_T
  rtu_distanceBrake, real_T rtu_timeAccelerate, real_T rtu_distanceAccelerate,
  real_T rtu_distanceConstVelocity, real_T rtu_timeConstVelocity, real_T
  rtu_shape, real_T rtu_velTop, real_T rtu_timeDecelerate, real_T rtu_signM,
  real_T rtu_deltaTime, real_T rtu_posRef, real_T rtu_oldPos, real_T rtu_oldVel,
  real_T rtu_maxAcc, real_T rtu_maxVel, real_T *rty_pos, real_T *rty_vel, real_T
  *rty_acc)
{
  *rty_acc = 0.0;
  if (rtu_shape != 0.0) {
    real_T a_tmp;
    a_tmp = rtu_timeBrake + rtu_timeAccelerate;
    if (rtu_deltaTime <= a_tmp) {
      *rty_pos = rtu_signM * 0.5 * rtu_maxAcc * (rtu_deltaTime * rtu_deltaTime)
        + (rtu_oldVel * rtu_deltaTime + rtu_oldPos);
      a_tmp = rtu_signM * rtu_maxAcc;
      *rty_vel = a_tmp * rtu_deltaTime + rtu_oldVel;
      *rty_acc = a_tmp;
    } else {
      real_T tmp;
      tmp = a_tmp + rtu_timeConstVelocity;
      if ((rtu_deltaTime > a_tmp) && (rtu_deltaTime < tmp)) {
        *rty_pos = (((rtu_deltaTime - rtu_timeBrake) - rtu_timeAccelerate) *
                    rtu_maxVel + (-rtu_distanceBrake + rtu_distanceAccelerate)) *
          rtu_signM + rtu_oldPos;
        *rty_vel = rtu_signM * rtu_maxVel;
      } else if ((rtu_deltaTime >= tmp) && (rtu_deltaTime < tmp +
                  rtu_timeDecelerate)) {
        a_tmp = ((rtu_deltaTime - rtu_timeBrake) - rtu_timeAccelerate) -
          rtu_timeConstVelocity;
        *rty_pos = ((((-rtu_distanceBrake + rtu_distanceAccelerate) +
                      rtu_distanceConstVelocity) + a_tmp * rtu_maxVel) - 0.5 *
                    rtu_maxAcc * (a_tmp * a_tmp)) * rtu_signM + rtu_oldPos;
        *rty_vel = (rtu_maxVel - a_tmp * rtu_maxAcc) * rtu_signM;
        *rty_acc = -rtu_signM * rtu_maxAcc;
      } else {
        *rty_pos = rtu_posRef;
        *rty_vel = 0.0;
      }
    }
  } else {
    real_T a_tmp;
    a_tmp = rtu_timeBrake + rtu_timeAccelerate;
    if (rtu_deltaTime <= a_tmp) {
      *rty_pos = rtu_signM * 0.5 * rtu_maxAcc * (rtu_deltaTime * rtu_deltaTime)
        + (rtu_oldVel * rtu_deltaTime + rtu_oldPos);
      a_tmp = rtu_signM * rtu_maxAcc;
      *rty_vel = a_tmp * rtu_deltaTime + rtu_oldVel;
      *rty_acc = a_tmp;
    } else if ((rtu_deltaTime > a_tmp) && (rtu_deltaTime < a_tmp +
                rtu_timeDecelerate)) {
      a_tmp = (rtu_deltaTime - rtu_timeBrake) - rtu_timeAccelerate;
      *rty_pos = ((a_tmp * rtu_velTop + (-rtu_distanceBrake +
        rtu_distanceAccelerate)) - 0.5 * rtu_maxAcc * (a_tmp * a_tmp)) *
        rtu_signM + rtu_oldPos;
      *rty_vel = (rtu_velTop - a_tmp * rtu_maxAcc) * rtu_signM;
      *rty_acc = -rtu_signM * rtu_maxAcc;
    } else {
      *rty_pos = rtu_posRef;
      *rty_vel = 0.0;
      *rty_acc = 0.0;
    }
  }
}

// Function for MATLAB Function: '<S5>/MATLAB Function'
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

// Function for MATLAB Function: '<S5>/MATLAB Function'
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

// Function for MATLAB Function: '<Root>/MATLAB Function'
void URController::expand_atan2(const real_T a_data[], const int32_T a_size[3],
  const real_T b_data[], const int32_T b_size[3], real_T c_data[], int32_T
  c_size[3])
{
  int8_T tmp;
  c_size[0] = 1;
  c_size[1] = 1;
  if (b_size[2] == 1) {
    c_size[2] = static_cast<int8_T>(a_size[2]);
    tmp = static_cast<int8_T>(a_size[2]);
  } else {
    c_size[2] = 0;
    tmp = 0;
  }

  if (tmp != 0) {
    c_data[0] = std::atan2(a_data[0], b_data[0]);
  }
}

// Model step function
void URController::step()
{
  static const real_T g_b[16]{ -1.0, -1.2246467991473532E-16,
    7.498798913309288E-33, 0.0, 0.0, 6.123233995736766E-17, 1.0, 0.0,
    -1.2246467991473532E-16, 1.0, -6.123233995736766E-17, 0.0, 0.817, 0.1918,
    -0.0055499999999999994, 1.0 };

  static const real_T f[9]{ 1.0, 0.0, 0.0, 0.0, 6.123233995736766E-17, 1.0, 0.0,
    -1.0, 6.123233995736766E-17 };

  static const real_T h[9]{ 1.0, 0.0, 0.0, 0.0, 6.123233995736766E-17, -1.0, 0.0,
    1.0, 6.123233995736766E-17 };

  static const real_T k[4]{ 0.0, -0.1093, 0.0, 1.0 };

  static const int8_T d_0[16]{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

  static const int8_T g[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const int8_T g_R[9]{ 0, 1, 0, -1, 0, 0, 0, 0, 0 };

  static const int8_T h_R[9]{ 0, 0, -1, 0, 0, 0, 1, 0, 0 };

  static const int8_T i_R[9]{ 0, -1, 0, 1, 0, 0, 0, 0, 0 };

  static const int8_T p05_tmp_1[4]{ 0, 0, 0, 1 };

  static const int8_T d[3]{ 0, 0, 1 };

  cell_wrap_7 reshapes[3];
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
  real_T R[9];
  real_T b_0[9];
  real_T b_R[9];
  real_T c_R[9];
  real_T d_R[9];
  real_T e_R[9];
  real_T f_R[9];
  real_T varargin_1[8];
  real_T rtb_Switch[6];
  real_T p05[4];
  real_T b_p_data[3];
  real_T c_p_data[3];
  real_T d_p_data[3];
  real_T e_p_data[3];
  real_T f_p_data[3];
  real_T R_0;
  real_T a_1;
  real_T cy;
  real_T cy_data;
  real_T phi;
  real_T psi;
  real_T rtb_TransferFcn10;
  real_T rtb_TransferFcn11;
  real_T rtb_TransferFcn12;
  real_T rtb_TransferFcn9;
  real_T s;
  real_T varargin_1_data;
  real_T x_data;
  int32_T cy_size[3];
  int32_T x_size[3];
  int32_T a_tmp;
  int32_T b_i;
  int32_T c_a_tmp_1;
  int32_T i;
  int32_T p05_tmp_0;
  int32_T rtb_theta_tmp;
  int32_T xpageoffset;
  int8_T c_a_tmp_0[16];
  int8_T R_tmp[9];
  int8_T b_I[9];
  int8_T p05_tmp[4];
  int8_T b_tmp[3];
  int8_T csz_idx_2;
  if (rtmIsMajorTimeStep((&rtM))) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&rtM)->solverInfo,(((&rtM)->Timing.clockTick0+1)*
      (&rtM)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep((&rtM))) {
    (&rtM)->Timing.t[0] = rtsiGetT(&(&rtM)->solverInfo);
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Inport: '<Root>/desire_pos_orient_arr'

  std::memset(&rtb_gd[0], 0, sizeof(real_T) << 4U);
  rtb_gd[0] = 1.0;
  rtb_gd[5] = 1.0;
  rtb_gd[10] = 1.0;
  rtb_gd[15] = 1.0;
  phi = std::sin(rtU.desire_pos_orient_arr[3]);
  psi = std::cos(rtU.desire_pos_orient_arr[3]);
  rtb_TransferFcn9 = std::sin(rtU.desire_pos_orient_arr[4]);
  rtb_TransferFcn10 = std::cos(rtU.desire_pos_orient_arr[4]);
  rtb_TransferFcn11 = std::sin(rtU.desire_pos_orient_arr[5]);
  rtb_TransferFcn12 = std::cos(rtU.desire_pos_orient_arr[5]);
  R[1] = 0.0;
  R[4] = psi;
  R[7] = -phi;
  R[2] = 0.0;
  R[5] = phi;
  R[8] = psi;
  b_R[0] = rtb_TransferFcn10;
  b_R[3] = 0.0;
  b_R[6] = rtb_TransferFcn9;
  rtb_gd[12] = rtU.desire_pos_orient_arr[0];
  R[0] = 1.0;
  b_R[1] = 0.0;
  rtb_gd[13] = rtU.desire_pos_orient_arr[1];
  R[3] = 0.0;
  b_R[4] = 1.0;
  rtb_gd[14] = rtU.desire_pos_orient_arr[2];
  R[6] = 0.0;
  b_R[7] = 0.0;
  b_R[2] = -rtb_TransferFcn9;
  b_R[5] = 0.0;
  b_R[8] = rtb_TransferFcn10;
  c_R[0] = rtb_TransferFcn12;
  c_R[3] = -rtb_TransferFcn11;
  c_R[6] = 0.0;
  c_R[1] = rtb_TransferFcn11;
  c_R[4] = rtb_TransferFcn12;
  c_R[7] = 0.0;
  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    psi = R[p05_tmp_0 + 3];
    phi = R[p05_tmp_0];
    rtb_TransferFcn9 = R[p05_tmp_0 + 6];
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      b_0[p05_tmp_0 + 3 * xpageoffset] = (b_R[3 * xpageoffset + 1] * psi + b_R[3
        * xpageoffset] * phi) + b_R[3 * xpageoffset + 2] * rtb_TransferFcn9;
    }

    c_R[3 * p05_tmp_0 + 2] = d[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    phi = c_R[3 * p05_tmp_0 + 1];
    psi = c_R[3 * p05_tmp_0];
    rtb_TransferFcn9 = c_R[3 * p05_tmp_0 + 2];
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      rtb_gd[xpageoffset + (p05_tmp_0 << 2)] = (b_0[xpageoffset + 3] * phi + psi
        * b_0[xpageoffset]) + b_0[xpageoffset + 6] * rtb_TransferFcn9;
    }
  }

  // End of MATLAB Function: '<S5>/MATLAB Function1'

  // MATLAB Function: '<S5>/MATLAB Function'
  std::memset(&rtb_theta[0], 0, 48U * sizeof(real_T));
  for (i = 0; i < 4; i++) {
    p05_tmp_0 = p05_tmp_1[i];
    p05_tmp[i] = static_cast<int8_T>(p05_tmp_0);
    p05[i] = (rtb_gd[i + 8] * -0.0825 + rtb_gd[i + 12]) - static_cast<real_T>
      (p05_tmp_0);
  }

  psi = std::atan2(p05[1], p05[0]);
  phi = std::acos(0.1093 / std::sqrt(p05[1] * p05[1] + p05[0] * p05[0]));
  rtb_TransferFcn9 = (psi + 1.5707963267948966) + phi;
  rtb_theta[0] = rtb_TransferFcn9;
  psi = (psi + 1.5707963267948966) - phi;
  rtb_theta[24] = psi;
  rtb_theta[6] = rtb_TransferFcn9;
  rtb_theta[30] = psi;
  rtb_theta[12] = rtb_TransferFcn9;
  rtb_theta[36] = psi;
  rtb_theta[18] = rtb_TransferFcn9;
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
    rtb_theta_tmp = i << 2;
    psi = rtb_theta[rtb_theta_tmp * 6];
    rtb_TransferFcn10 = std::sin(psi);
    phi = std::cos(psi);
    b[0] = phi;
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
    b[5] = phi;
    b[9] = 0.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      xpageoffset = p05_tmp_0 << 2;
      b[xpageoffset + 2] = d[p05_tmp_0];
      c_b[xpageoffset] = f[3 * p05_tmp_0];
      c_b[xpageoffset + 1] = f[3 * p05_tmp_0 + 1];
      c_b[xpageoffset + 2] = f[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      s = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a[p05_tmp_0];
      rtb_TransferFcn10 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * s + b[c_a_tmp_1] *
          rtb_TransferFcn9) + b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      s = c_a_0[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_0[p05_tmp_0];
      rtb_TransferFcn10 = c_a_0[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * s + b_b[c_a_tmp_1]
          * rtb_TransferFcn9) + b_b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          b_b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      s = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_1[p05_tmp_0];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * s + c_b[c_a_tmp_1]
          * rtb_TransferFcn9) + c_b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          c_b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }
    }

    inv(c_a_2, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      psi = a[p05_tmp_0];
      rtb_TransferFcn9 = a[p05_tmp_0 + 8];
      rtb_TransferFcn10 = a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_b[p05_tmp_0 + c_a_tmp_1] = ((rtb_gd[c_a_tmp_1 + 1] * phi +
          rtb_gd[c_a_tmp_1] * psi) + rtb_gd[c_a_tmp_1 + 2] * rtb_TransferFcn9) +
          rtb_gd[c_a_tmp_1 + 3] * rtb_TransferFcn10;
      }
    }

    psi = std::acos((c_b[14] - 0.1093) / 0.0825);
    rtb_theta[6 * rtb_theta_tmp + 4] = psi;
    rtb_theta[6 * (rtb_theta_tmp + 2) + 4] = -psi;
    rtb_theta[6 * (rtb_theta_tmp + 1) + 4] = psi;
    rtb_theta[6 * (rtb_theta_tmp + 3) + 4] = -psi;
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
    rtb_theta_tmp = i * 6;
    psi = rtb_theta[rtb_theta_tmp];
    rtb_TransferFcn10 = std::sin(psi);
    phi = std::cos(psi);
    b[0] = phi;
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
    b[5] = phi;
    b[9] = 0.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      xpageoffset = p05_tmp_0 << 2;
      b[xpageoffset + 2] = d[p05_tmp_0];
      c_b[xpageoffset] = f[3 * p05_tmp_0];
      c_b[xpageoffset + 1] = f[3 * p05_tmp_0 + 1];
      c_b[xpageoffset + 2] = f[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      s = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a[p05_tmp_0];
      rtb_TransferFcn10 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * s + b[c_a_tmp_1] *
          rtb_TransferFcn9) + b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      s = c_a_0[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_0[p05_tmp_0];
      rtb_TransferFcn10 = c_a_0[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * s + b_b[c_a_tmp_1]
          * rtb_TransferFcn9) + b_b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          b_b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      s = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_1[p05_tmp_0];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * s + c_b[c_a_tmp_1]
          * rtb_TransferFcn9) + c_b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          c_b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      psi = a[p05_tmp_0];
      rtb_TransferFcn9 = a[p05_tmp_0 + 8];
      rtb_TransferFcn10 = a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_tmp[p05_tmp_0 + c_a_tmp_1] = ((c_a_2[c_a_tmp_1 + 1] * phi +
          c_a_2[c_a_tmp_1] * psi) + c_a_2[c_a_tmp_1 + 2] * rtb_TransferFcn9) +
          c_a_2[c_a_tmp_1 + 3] * rtb_TransferFcn10;
      }
    }

    psi = std::sin(rtb_theta[rtb_theta_tmp + 4]);
    psi = std::atan2(-c_a_tmp[9] / psi, c_a_tmp[8] / psi);
    rtb_theta[6 * i + 5] = psi;
    rtb_theta[6 * (i + 1) + 5] = psi;
  }

  b_tmp[0] = 0;
  b_tmp[1] = 0;
  b_tmp[2] = 1;
  for (b_i = 0; b_i < 4; b_i++) {
    i = b_i << 1;
    rtb_theta_tmp = i * 6;
    psi = rtb_theta[rtb_theta_tmp];
    rtb_TransferFcn10 = std::sin(psi);
    phi = std::cos(psi);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      c_a_tmp_1 = d_0[p05_tmp_0];
      c_a_tmp[p05_tmp_0] = c_a_tmp_1;
      c_a[p05_tmp_0] = c_a_tmp_1;
      b_b[p05_tmp_0] = c_a_tmp_1;
      b[p05_tmp_0] = c_a_tmp_1;
      c_b[p05_tmp_0] = c_a_tmp_1;
    }

    c_a[14] = 0.0892;
    b_b[12] = 0.0;
    b[0] = phi;
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
    b[5] = phi;
    b[9] = 0.0;
    b[2] = 0.0;
    b[6] = 0.0;
    b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      xpageoffset = p05_tmp_0 << 2;
      c_b[xpageoffset] = f[3 * p05_tmp_0];
      c_b[xpageoffset + 1] = f[3 * p05_tmp_0 + 1];
      c_b[xpageoffset + 2] = f[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      s = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a[p05_tmp_0];
      rtb_TransferFcn10 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * s + b[c_a_tmp_1] *
          rtb_TransferFcn9) + b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      s = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_1[p05_tmp_0];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * s + b_b[c_a_tmp_1]
          * rtb_TransferFcn9) + b_b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          b_b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      s = c_a_0[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_0[p05_tmp_0];
      rtb_TransferFcn10 = c_a_0[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * s + c_b[c_a_tmp_1]
          * rtb_TransferFcn9) + c_b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          c_b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }
    }

    inv(c_a_2, c_a);
    psi = rtb_theta[rtb_theta_tmp + 5];
    rtb_TransferFcn10 = std::sin(psi);
    phi = std::cos(psi);
    std::memcpy(&a[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&b_b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&c_b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    a[14] = 0.0825;
    b_b[12] = 0.0;
    b[0] = phi;
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
    b[5] = phi;
    b[9] = 0.0;
    b[2] = 0.0;
    b[6] = 0.0;
    b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      xpageoffset = p05_tmp_0 << 2;
      c_b[xpageoffset] = g[3 * p05_tmp_0];
      c_b[xpageoffset + 1] = g[3 * p05_tmp_0 + 1];
      c_b[xpageoffset + 2] = g[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      cy = a[p05_tmp_0 + 4];
      phi = a[p05_tmp_0];
      rtb_TransferFcn12 = a[p05_tmp_0 + 8];
      a_1 = a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * cy + b[c_a_tmp_1] *
          phi) + b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + b[c_a_tmp_1 + 3] * a_1;
      }

      cy = c_a_2[p05_tmp_0 + 4];
      phi = c_a_2[p05_tmp_0];
      rtb_TransferFcn12 = c_a_2[p05_tmp_0 + 8];
      a_1 = c_a_2[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_0[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * cy + b_b[c_a_tmp_1] *
          phi) + b_b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + b_b[c_a_tmp_1 + 3] *
          a_1;
      }

      cy = a_0[p05_tmp_0 + 4];
      phi = a_0[p05_tmp_0];
      rtb_TransferFcn12 = a_0[p05_tmp_0 + 8];
      a_1 = a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * cy + c_b[c_a_tmp_1]
          * phi) + c_b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + c_b[c_a_tmp_1 + 3] *
          a_1;
      }
    }

    inv(c_a_0, b_b);
    std::memcpy(&a[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&c_b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    a[14] = 0.09475;
    b[12] = 0.0;
    psi = rtb_theta[rtb_theta_tmp + 4];
    phi = std::sin(psi);
    rtb_TransferFcn9 = std::cos(psi);
    c_b[0] = rtb_TransferFcn9;
    c_b[4] = -phi;
    c_b[8] = 0.0;
    c_b[1] = phi;
    c_b[5] = rtb_TransferFcn9;
    c_b[9] = 0.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      xpageoffset = p05_tmp_0 << 2;
      c_b[xpageoffset + 2] = b_tmp[p05_tmp_0];
      c_a_tmp[xpageoffset] = h[3 * p05_tmp_0];
      c_a_tmp[xpageoffset + 1] = h[3 * p05_tmp_0 + 1];
      c_a_tmp[xpageoffset + 2] = h[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      cy = a[p05_tmp_0 + 4];
      phi = a[p05_tmp_0];
      rtb_TransferFcn12 = a[p05_tmp_0 + 8];
      a_1 = a[p05_tmp_0 + 12];
      s = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a[p05_tmp_0];
      rtb_TransferFcn10 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_tmp = p05_tmp_0 + c_a_tmp_1;
        c_a_2[a_tmp] = ((c_b[c_a_tmp_1 + 1] * cy + c_b[c_a_tmp_1] * phi) +
                        c_b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + c_b[c_a_tmp_1
          + 3] * a_1;
        c_a_1[a_tmp] = ((rtb_gd[c_a_tmp_1 + 1] * s + rtb_gd[c_a_tmp_1] *
                         rtb_TransferFcn9) + rtb_gd[c_a_tmp_1 + 2] *
                        rtb_TransferFcn10) + rtb_gd[c_a_tmp_1 + 3] *
          rtb_TransferFcn11;
      }

      cy = c_a_2[p05_tmp_0 + 4];
      phi = c_a_2[p05_tmp_0];
      rtb_TransferFcn12 = c_a_2[p05_tmp_0 + 8];
      a_1 = c_a_2[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_0[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * cy + b[c_a_tmp_1] *
          phi) + b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + b[c_a_tmp_1 + 3] * a_1;
      }

      cy = a_0[p05_tmp_0 + 4];
      phi = a_0[p05_tmp_0];
      rtb_TransferFcn12 = a_0[p05_tmp_0 + 8];
      a_1 = a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((c_a_tmp[c_a_tmp_1 + 1] * cy +
          c_a_tmp[c_a_tmp_1] * phi) + c_a_tmp[c_a_tmp_1 + 2] * rtb_TransferFcn12)
          + c_a_tmp[c_a_tmp_1 + 3] * a_1;
      }
    }

    inv(c_a_0, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      s = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_1[p05_tmp_0];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * s + b_b[c_a_tmp_1] *
          rtb_TransferFcn9) + b_b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          b_b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      phi = 0.0;
      s = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a[p05_tmp_0];
      rtb_TransferFcn10 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        phi += (((a[c_a_tmp_1 + 1] * s + a[c_a_tmp_1] * rtb_TransferFcn9) +
                 a[c_a_tmp_1 + 2] * rtb_TransferFcn10) + a[c_a_tmp_1 + 3] *
                rtb_TransferFcn11) * k[xpageoffset];
      }

      p05[p05_tmp_0] = phi - static_cast<real_T>(p05_tmp[p05_tmp_0]);
    }

    s = norm(p05);
    psi = std::acos(((s * s - 0.18062499999999998) - 0.15366400000000002) /
                    0.3332);
    rtb_theta[rtb_theta_tmp + 2] = psi;
    rtb_theta[6 * (i + 1) + 2] = -psi;
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    R[p05_tmp_0] = g[p05_tmp_0];
  }

  for (rtb_theta_tmp = 0; rtb_theta_tmp < 8; rtb_theta_tmp++) {
    psi = rtb_theta[6 * rtb_theta_tmp];
    rtb_TransferFcn10 = std::sin(psi);
    phi = std::cos(psi);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      c_a_tmp_1 = d_0[p05_tmp_0];
      c_a_tmp_0[p05_tmp_0] = static_cast<int8_T>(c_a_tmp_1);
      c_a[p05_tmp_0] = c_a_tmp_1;
      b_b[p05_tmp_0] = c_a_tmp_1;
      b[p05_tmp_0] = c_a_tmp_1;
      c_b[p05_tmp_0] = static_cast<int8_T>(c_a_tmp_1);
    }

    c_a[14] = 0.0892;
    b_b[12] = 0.0;
    b[0] = phi;
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
    b[5] = phi;
    b[9] = 0.0;
    b[2] = 0.0;
    b[6] = 0.0;
    b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      xpageoffset = p05_tmp_0 << 2;
      c_b[xpageoffset] = f[3 * p05_tmp_0];
      c_b[xpageoffset + 1] = f[3 * p05_tmp_0 + 1];
      c_b[xpageoffset + 2] = f[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      s = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a[p05_tmp_0];
      rtb_TransferFcn10 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * s + b[c_a_tmp_1] *
          rtb_TransferFcn9) + b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      s = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_1[p05_tmp_0];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * s + b_b[c_a_tmp_1]
          * rtb_TransferFcn9) + b_b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          b_b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      s = c_a_0[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_0[p05_tmp_0];
      rtb_TransferFcn10 = c_a_0[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * s + c_b[c_a_tmp_1]
          * rtb_TransferFcn9) + c_b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          c_b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }
    }

    inv(c_a_2, c_a);
    rtb_TransferFcn11 = rtb_theta[6 * rtb_theta_tmp + 5];
    rtb_TransferFcn10 = std::sin(rtb_TransferFcn11);
    phi = std::cos(rtb_TransferFcn11);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      csz_idx_2 = c_a_tmp_0[p05_tmp_0];
      a[p05_tmp_0] = csz_idx_2;
      b_b[p05_tmp_0] = csz_idx_2;
      b[p05_tmp_0] = csz_idx_2;
      c_b[p05_tmp_0] = csz_idx_2;
    }

    a[14] = 0.0825;
    b_b[12] = 0.0;
    b[0] = phi;
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
    b[5] = phi;
    b[9] = 0.0;
    b[2] = 0.0;
    b[6] = 0.0;
    b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      xpageoffset = p05_tmp_0 << 2;
      c_b[xpageoffset] = R[3 * p05_tmp_0];
      c_b[xpageoffset + 1] = R[3 * p05_tmp_0 + 1];
      c_b[xpageoffset + 2] = R[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      cy = a[p05_tmp_0 + 4];
      phi = a[p05_tmp_0];
      rtb_TransferFcn12 = a[p05_tmp_0 + 8];
      a_1 = a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * cy + b[c_a_tmp_1] *
          phi) + b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + b[c_a_tmp_1 + 3] * a_1;
      }

      cy = c_a_2[p05_tmp_0 + 4];
      phi = c_a_2[p05_tmp_0];
      rtb_TransferFcn12 = c_a_2[p05_tmp_0 + 8];
      a_1 = c_a_2[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_0[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * cy + b_b[c_a_tmp_1] *
          phi) + b_b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + b_b[c_a_tmp_1 + 3] *
          a_1;
      }

      cy = a_0[p05_tmp_0 + 4];
      phi = a_0[p05_tmp_0];
      rtb_TransferFcn12 = a_0[p05_tmp_0 + 8];
      a_1 = a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * cy + c_b[c_a_tmp_1]
          * phi) + c_b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + c_b[c_a_tmp_1 + 3] *
          a_1;
      }
    }

    inv(c_a_0, b_b);
    rtb_TransferFcn11 = rtb_theta[6 * rtb_theta_tmp + 4];
    phi = std::sin(rtb_TransferFcn11);
    rtb_TransferFcn9 = std::cos(rtb_TransferFcn11);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      csz_idx_2 = c_a_tmp_0[p05_tmp_0];
      a[p05_tmp_0] = csz_idx_2;
      b[p05_tmp_0] = csz_idx_2;
      c_b[p05_tmp_0] = csz_idx_2;
      c_a_tmp[p05_tmp_0] = csz_idx_2;
    }

    a[14] = 0.09475;
    b[12] = 0.0;
    c_b[0] = rtb_TransferFcn9;
    c_b[4] = -phi;
    c_b[8] = 0.0;
    c_b[1] = phi;
    c_b[5] = rtb_TransferFcn9;
    c_b[9] = 0.0;
    c_b[2] = 0.0;
    c_b[6] = 0.0;
    c_b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      c_a_tmp_1 = p05_tmp_0 << 2;
      c_a_tmp[c_a_tmp_1] = h[3 * p05_tmp_0];
      c_a_tmp[c_a_tmp_1 + 1] = h[3 * p05_tmp_0 + 1];
      c_a_tmp[c_a_tmp_1 + 2] = h[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      cy = a[p05_tmp_0 + 4];
      phi = a[p05_tmp_0];
      rtb_TransferFcn12 = a[p05_tmp_0 + 8];
      a_1 = a[p05_tmp_0 + 12];
      s = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a[p05_tmp_0];
      rtb_TransferFcn10 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_tmp = p05_tmp_0 + c_a_tmp_1;
        c_a_2[a_tmp] = ((c_b[c_a_tmp_1 + 1] * cy + c_b[c_a_tmp_1] * phi) +
                        c_b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + c_b[c_a_tmp_1
          + 3] * a_1;
        c_a_1[a_tmp] = ((rtb_gd[c_a_tmp_1 + 1] * s + rtb_gd[c_a_tmp_1] *
                         rtb_TransferFcn9) + rtb_gd[c_a_tmp_1 + 2] *
                        rtb_TransferFcn10) + rtb_gd[c_a_tmp_1 + 3] *
          rtb_TransferFcn11;
      }

      cy = c_a_2[p05_tmp_0 + 4];
      phi = c_a_2[p05_tmp_0];
      rtb_TransferFcn12 = c_a_2[p05_tmp_0 + 8];
      a_1 = c_a_2[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_0[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * cy + b[c_a_tmp_1] *
          phi) + b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + b[c_a_tmp_1 + 3] * a_1;
      }

      cy = a_0[p05_tmp_0 + 4];
      phi = a_0[p05_tmp_0];
      rtb_TransferFcn12 = a_0[p05_tmp_0 + 8];
      a_1 = a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((c_a_tmp[c_a_tmp_1 + 1] * cy +
          c_a_tmp[c_a_tmp_1] * phi) + c_a_tmp[c_a_tmp_1 + 2] * rtb_TransferFcn12)
          + c_a_tmp[c_a_tmp_1 + 3] * a_1;
      }
    }

    inv(c_a_0, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      s = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_1[p05_tmp_0];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * s + b_b[c_a_tmp_1] *
          rtb_TransferFcn9) + b_b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          b_b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      phi = 0.0;
      s = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a[p05_tmp_0];
      rtb_TransferFcn10 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        i = xpageoffset << 2;
        rtb_TransferFcn12 = ((a[i + 1] * s + a[i] * rtb_TransferFcn9) + a[i + 2]
                             * rtb_TransferFcn10) + a[i + 3] * rtb_TransferFcn11;
        T14[p05_tmp_0 + i] = rtb_TransferFcn12;
        phi += rtb_TransferFcn12 * k[xpageoffset];
      }

      p05[p05_tmp_0] = phi - static_cast<real_T>(p05_tmp[p05_tmp_0]);
    }

    rtb_TransferFcn11 = rtb_theta[6 * rtb_theta_tmp + 2];
    rtb_TransferFcn9 = std::sin(rtb_TransferFcn11);
    phi = std::asin(-0.392 * rtb_TransferFcn9 / norm(p05)) - std::atan2(p05[1],
      -p05[0]);
    rtb_theta[6 * rtb_theta_tmp + 1] = phi;
    rtb_TransferFcn10 = std::cos(rtb_TransferFcn11);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      csz_idx_2 = c_a_tmp_0[p05_tmp_0];
      c_a[p05_tmp_0] = csz_idx_2;
      b_b[p05_tmp_0] = csz_idx_2;
      b[p05_tmp_0] = csz_idx_2;
      c_b[p05_tmp_0] = csz_idx_2;
    }

    c_a[14] = 0.0;
    b_b[12] = -0.392;
    b[0] = rtb_TransferFcn10;
    b[4] = -rtb_TransferFcn9;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn9;
    b[5] = rtb_TransferFcn10;
    b[9] = 0.0;
    b[2] = 0.0;
    b[6] = 0.0;
    b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      xpageoffset = p05_tmp_0 << 2;
      c_b[xpageoffset] = R[3 * p05_tmp_0];
      c_b[xpageoffset + 1] = R[3 * p05_tmp_0 + 1];
      c_b[xpageoffset + 2] = R[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      s = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a[p05_tmp_0];
      rtb_TransferFcn10 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * s + b[c_a_tmp_1] *
          rtb_TransferFcn9) + b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      s = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_1[p05_tmp_0];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * s + b_b[c_a_tmp_1]
          * rtb_TransferFcn9) + b_b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          b_b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      s = c_a_0[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_0[p05_tmp_0];
      rtb_TransferFcn10 = c_a_0[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * s + c_b[c_a_tmp_1]
          * rtb_TransferFcn9) + c_b[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          c_b[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }
    }

    inv(c_a_2, c_a);
    rtb_TransferFcn10 = std::sin(phi);
    phi = std::cos(phi);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      csz_idx_2 = c_a_tmp_0[p05_tmp_0];
      a[p05_tmp_0] = csz_idx_2;
      b_b[p05_tmp_0] = csz_idx_2;
      b[p05_tmp_0] = csz_idx_2;
      c_b[p05_tmp_0] = csz_idx_2;
    }

    a[14] = 0.0;
    b_b[12] = -0.425;
    b[0] = phi;
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
    b[5] = phi;
    b[9] = 0.0;
    b[2] = 0.0;
    b[6] = 0.0;
    b[10] = 1.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      xpageoffset = p05_tmp_0 << 2;
      c_b[xpageoffset] = R[3 * p05_tmp_0];
      c_b[xpageoffset + 1] = R[3 * p05_tmp_0 + 1];
      c_b[xpageoffset + 2] = R[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      cy = a[p05_tmp_0 + 4];
      phi = a[p05_tmp_0];
      rtb_TransferFcn12 = a[p05_tmp_0 + 8];
      a_1 = a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * cy + b[c_a_tmp_1] *
          phi) + b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + b[c_a_tmp_1 + 3] * a_1;
      }

      cy = c_a_2[p05_tmp_0 + 4];
      phi = c_a_2[p05_tmp_0];
      rtb_TransferFcn12 = c_a_2[p05_tmp_0 + 8];
      a_1 = c_a_2[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_0[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * cy + b_b[c_a_tmp_1] *
          phi) + b_b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + b_b[c_a_tmp_1 + 3] *
          a_1;
      }

      cy = a_0[p05_tmp_0 + 4];
      phi = a_0[p05_tmp_0];
      rtb_TransferFcn12 = a_0[p05_tmp_0 + 8];
      a_1 = a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * cy + c_b[c_a_tmp_1]
          * phi) + c_b[c_a_tmp_1 + 2] * rtb_TransferFcn12) + c_b[c_a_tmp_1 + 3] *
          a_1;
      }
    }

    inv(c_a_0, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      s = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a[p05_tmp_0];
      rtb_TransferFcn10 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_1] = ((a[c_a_tmp_1 + 1] * s + a[c_a_tmp_1] *
          rtb_TransferFcn9) + a[c_a_tmp_1 + 2] * rtb_TransferFcn10) +
          a[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }

      s = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn9 = c_a_1[p05_tmp_0];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_tmp[p05_tmp_0 + c_a_tmp_1] = ((T14[c_a_tmp_1 + 1] * s +
          T14[c_a_tmp_1] * rtb_TransferFcn9) + T14[c_a_tmp_1 + 2] *
          rtb_TransferFcn10) + T14[c_a_tmp_1 + 3] * rtb_TransferFcn11;
      }
    }

    rtb_theta[6 * rtb_theta_tmp + 3] = std::atan2(c_a_tmp[1], c_a_tmp[0]);
    rtb_theta[6 * rtb_theta_tmp] = psi - 3.1415926535897931;
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 8; p05_tmp_0++) {
    for (xpageoffset = 0; xpageoffset < 6; xpageoffset++) {
      rtb_theta_tmp = 6 * p05_tmp_0 + xpageoffset;
      psi = rtb_theta[rtb_theta_tmp];
      if (psi <= -3.1415926535897931) {
        rtb_theta[rtb_theta_tmp] = psi + 6.2831853071795862;
      } else if (psi > 3.1415926535897931) {
        rtb_theta[rtb_theta_tmp] = psi - 6.2831853071795862;
      }
    }
  }

  // End of MATLAB Function: '<S5>/MATLAB Function'

  // TransferFcn: '<S4>/Transfer Fcn7'
  psi = (6.0 * rtX.TransferFcn7_CSTATE[1] + rtX.TransferFcn7_CSTATE[0]) + 10.0 *
    rtX.TransferFcn7_CSTATE[2];

  // TransferFcn: '<S4>/Transfer Fcn8'
  phi = (6.0 * rtX.TransferFcn8_CSTATE[1] + rtX.TransferFcn8_CSTATE[0]) + 10.0 *
    rtX.TransferFcn8_CSTATE[2];

  // TransferFcn: '<S4>/Transfer Fcn9'
  rtb_TransferFcn9 = (6.0 * rtX.TransferFcn9_CSTATE[1] +
                      rtX.TransferFcn9_CSTATE[0]) + 10.0 *
    rtX.TransferFcn9_CSTATE[2];

  // TransferFcn: '<S4>/Transfer Fcn10'
  rtb_TransferFcn10 = (6.0 * rtX.TransferFcn10_CSTATE[1] +
                       rtX.TransferFcn10_CSTATE[0]) + 10.0 *
    rtX.TransferFcn10_CSTATE[2];

  // TransferFcn: '<S4>/Transfer Fcn11'
  rtb_TransferFcn11 = (6.0 * rtX.TransferFcn11_CSTATE[1] +
                       rtX.TransferFcn11_CSTATE[0]) + 10.0 *
    rtX.TransferFcn11_CSTATE[2];

  // TransferFcn: '<S4>/Transfer Fcn12'
  rtb_TransferFcn12 = (6.0 * rtX.TransferFcn12_CSTATE[1] +
                       rtX.TransferFcn12_CSTATE[0]) + 10.0 *
    rtX.TransferFcn12_CSTATE[2];

  // SignalConversion generated from: '<S322>/ SFunction ' incorporates:
  //   MATLAB Function: '<S2>/isInitialized'
  //   MATLAB Function: '<S3>/MATLAB Function'
  //   SignalConversion generated from: '<S6>/ SFunction '

  rtb_Switch[0] = psi;
  rtb_Switch[1] = phi;
  rtb_Switch[2] = rtb_TransferFcn9;
  rtb_Switch[3] = rtb_TransferFcn10;
  rtb_Switch[4] = rtb_TransferFcn11;
  rtb_Switch[5] = rtb_TransferFcn12;

  // MATLAB Function: '<S3>/MATLAB Function' incorporates:
  //   SignalConversion generated from: '<S322>/ SFunction '

  cy = std::sin(psi);
  s = std::cos(psi);
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_I[p05_tmp_0] = 0;
  }

  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    R_tmp[p05_tmp_0] = g_R[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      rtb_theta_tmp = 3 * xpageoffset + p05_tmp_0;
      R[rtb_theta_tmp] = (((1.0 - s) * static_cast<real_T>(R_tmp[p05_tmp_0 + 3])
                           * static_cast<real_T>(R_tmp[3 * xpageoffset + 1]) +
                           (1.0 - s) * static_cast<real_T>(R_tmp[p05_tmp_0]) *
                           static_cast<real_T>(R_tmp[3 * xpageoffset])) +
                          static_cast<real_T>(R_tmp[p05_tmp_0 + 6]) * (1.0 - s) *
                          static_cast<real_T>(R_tmp[3 * xpageoffset + 2])) + (
        static_cast<real_T>(R_tmp[rtb_theta_tmp]) * cy + static_cast<real_T>
        (b_I[rtb_theta_tmp]));
    }
  }

  s = std::sin(phi);
  cy = std::cos(phi);
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_I[p05_tmp_0] = 0;
  }

  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    R_tmp[p05_tmp_0] = h_R[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      rtb_theta_tmp = 3 * xpageoffset + p05_tmp_0;
      b_R[rtb_theta_tmp] = (((1.0 - cy) * static_cast<real_T>(R_tmp[p05_tmp_0 +
        3]) * static_cast<real_T>(R_tmp[3 * xpageoffset + 1]) + (1.0 - cy) *
        static_cast<real_T>(R_tmp[p05_tmp_0]) * static_cast<real_T>(R_tmp[3 *
        xpageoffset])) + static_cast<real_T>(R_tmp[p05_tmp_0 + 6]) * (1.0 - cy) *
                            static_cast<real_T>(R_tmp[3 * xpageoffset + 2])) + (
        static_cast<real_T>(R_tmp[rtb_theta_tmp]) * s + static_cast<real_T>
        (b_I[rtb_theta_tmp]));
    }
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_I[p05_tmp_0] = 0;
  }

  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_0[p05_tmp_0] = static_cast<real_T>(b_I[p05_tmp_0]) - b_R[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    b_p_data[p05_tmp_0] = b_0[p05_tmp_0 + 6] * 0.0892;
  }

  s = std::sin(rtb_TransferFcn9);
  cy = std::cos(rtb_TransferFcn9);
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_I[p05_tmp_0] = 0;
  }

  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      rtb_theta_tmp = 3 * xpageoffset + p05_tmp_0;
      c_R[rtb_theta_tmp] = (((1.0 - cy) * static_cast<real_T>(R_tmp[p05_tmp_0 +
        3]) * static_cast<real_T>(R_tmp[3 * xpageoffset + 1]) + (1.0 - cy) *
        static_cast<real_T>(R_tmp[p05_tmp_0]) * static_cast<real_T>(R_tmp[3 *
        xpageoffset])) + static_cast<real_T>(R_tmp[p05_tmp_0 + 6]) * (1.0 - cy) *
                            static_cast<real_T>(R_tmp[3 * xpageoffset + 2])) + (
        static_cast<real_T>(R_tmp[rtb_theta_tmp]) * s + static_cast<real_T>
        (b_I[rtb_theta_tmp]));
    }
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_I[p05_tmp_0] = 0;
  }

  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_0[p05_tmp_0] = static_cast<real_T>(b_I[p05_tmp_0]) - c_R[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    c_p_data[p05_tmp_0] = b_0[p05_tmp_0 + 6] * 0.0892 + b_0[p05_tmp_0] * 0.425;
  }

  s = std::sin(rtb_TransferFcn10);
  cy = std::cos(rtb_TransferFcn10);
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_I[p05_tmp_0] = 0;
  }

  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      rtb_theta_tmp = 3 * xpageoffset + p05_tmp_0;
      d_R[rtb_theta_tmp] = (((1.0 - cy) * static_cast<real_T>(R_tmp[p05_tmp_0 +
        3]) * static_cast<real_T>(R_tmp[3 * xpageoffset + 1]) + (1.0 - cy) *
        static_cast<real_T>(R_tmp[p05_tmp_0]) * static_cast<real_T>(R_tmp[3 *
        xpageoffset])) + static_cast<real_T>(R_tmp[p05_tmp_0 + 6]) * (1.0 - cy) *
                            static_cast<real_T>(R_tmp[3 * xpageoffset + 2])) + (
        static_cast<real_T>(R_tmp[rtb_theta_tmp]) * s + static_cast<real_T>
        (b_I[rtb_theta_tmp]));
    }
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_I[p05_tmp_0] = 0;
  }

  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_0[p05_tmp_0] = static_cast<real_T>(b_I[p05_tmp_0]) - d_R[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    d_p_data[p05_tmp_0] = b_0[p05_tmp_0 + 6] * 0.0892 + b_0[p05_tmp_0] * 0.817;
  }

  s = std::sin(rtb_TransferFcn11);
  cy = std::cos(rtb_TransferFcn11);
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_I[p05_tmp_0] = 0;
  }

  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    f_R[p05_tmp_0] = i_R[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      rtb_theta_tmp = 3 * xpageoffset + p05_tmp_0;
      e_R[rtb_theta_tmp] = (((1.0 - cy) * f_R[p05_tmp_0 + 3] * f_R[3 *
        xpageoffset + 1] + (1.0 - cy) * f_R[p05_tmp_0] * f_R[3 * xpageoffset]) +
                            f_R[p05_tmp_0 + 6] * (1.0 - cy) * f_R[3 *
                            xpageoffset + 2]) + (f_R[rtb_theta_tmp] * s +
        static_cast<real_T>(b_I[rtb_theta_tmp]));
    }
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_I[p05_tmp_0] = 0;
  }

  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_0[p05_tmp_0] = static_cast<real_T>(b_I[p05_tmp_0]) - e_R[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    e_p_data[p05_tmp_0] = b_0[p05_tmp_0 + 3] * 0.1093 + b_0[p05_tmp_0] * 0.817;
  }

  s = std::sin(rtb_TransferFcn12);
  cy = std::cos(rtb_TransferFcn12);
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_I[p05_tmp_0] = 0;
  }

  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      rtb_theta_tmp = 3 * xpageoffset + p05_tmp_0;
      f_R[rtb_theta_tmp] = (((1.0 - cy) * static_cast<real_T>(R_tmp[p05_tmp_0 +
        3]) * static_cast<real_T>(R_tmp[3 * xpageoffset + 1]) + (1.0 - cy) *
        static_cast<real_T>(R_tmp[p05_tmp_0]) * static_cast<real_T>(R_tmp[3 *
        xpageoffset])) + static_cast<real_T>(R_tmp[p05_tmp_0 + 6]) * (1.0 - cy) *
                            static_cast<real_T>(R_tmp[3 * xpageoffset + 2])) + (
        static_cast<real_T>(R_tmp[rtb_theta_tmp]) * s + static_cast<real_T>
        (b_I[rtb_theta_tmp]));
    }
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_I[p05_tmp_0] = 0;
  }

  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_0[p05_tmp_0] = static_cast<real_T>(b_I[p05_tmp_0]) - f_R[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    f_p_data[p05_tmp_0] = b_0[p05_tmp_0 + 6] * -0.0055499999999999994 +
      b_0[p05_tmp_0] * 0.817;
  }

  c_b[0] = R[0];
  c_b[4] = R[3];
  c_b[8] = R[6];
  c_b[12] = 0.0;
  c_b[1] = R[1];
  c_b[5] = R[4];
  c_b[9] = R[7];
  c_b[13] = 0.0;
  c_b[2] = R[2];
  c_b[6] = R[5];
  c_b[10] = R[8];
  c_b[14] = 0.0;
  b_b[0] = b_R[0];
  b_b[4] = b_R[3];
  b_b[8] = b_R[6];
  b_b[12] = b_p_data[0];
  b_b[1] = b_R[1];
  b_b[5] = b_R[4];
  b_b[9] = b_R[7];
  b_b[13] = b_p_data[1];
  b_b[2] = b_R[2];
  b_b[6] = b_R[5];
  b_b[10] = b_R[8];
  b_b[14] = b_p_data[2];
  p05_tmp[0] = 0;
  c_b[3] = 0.0;
  b_b[3] = 0.0;
  p05_tmp[1] = 0;
  c_b[7] = 0.0;
  b_b[7] = 0.0;
  p05_tmp[2] = 0;
  c_b[11] = 0.0;
  b_b[11] = 0.0;
  p05_tmp[3] = 1;
  c_b[15] = 1.0;
  b_b[15] = 1.0;
  rtb_gd[0] = c_R[0];
  rtb_gd[4] = c_R[3];
  rtb_gd[8] = c_R[6];
  rtb_gd[12] = c_p_data[0];
  rtb_gd[1] = c_R[1];
  rtb_gd[5] = c_R[4];
  rtb_gd[9] = c_R[7];
  rtb_gd[13] = c_p_data[1];
  rtb_gd[2] = c_R[2];
  rtb_gd[6] = c_R[5];
  rtb_gd[10] = c_R[8];
  rtb_gd[14] = c_p_data[2];
  for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
    s = c_b[p05_tmp_0 + 4];
    cy = c_b[p05_tmp_0];
    a_1 = c_b[p05_tmp_0 + 8];
    R_0 = c_b[p05_tmp_0 + 12];
    for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
      rtb_theta_tmp = xpageoffset << 2;
      c_a[p05_tmp_0 + rtb_theta_tmp] = ((b_b[rtb_theta_tmp + 1] * s +
        b_b[rtb_theta_tmp] * cy) + b_b[rtb_theta_tmp + 2] * a_1) +
        b_b[rtb_theta_tmp + 3] * R_0;
    }

    rtb_gd[(p05_tmp_0 << 2) + 3] = p05_tmp[p05_tmp_0];
  }

  b_b[0] = d_R[0];
  b_b[4] = d_R[3];
  b_b[8] = d_R[6];
  b_b[12] = d_p_data[0];
  b_b[1] = d_R[1];
  b_b[5] = d_R[4];
  b_b[9] = d_R[7];
  b_b[13] = d_p_data[1];
  b_b[2] = d_R[2];
  b_b[6] = d_R[5];
  b_b[10] = d_R[8];
  b_b[14] = d_p_data[2];
  for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
    s = c_a[p05_tmp_0 + 4];
    cy = c_a[p05_tmp_0];
    a_1 = c_a[p05_tmp_0 + 8];
    R_0 = c_a[p05_tmp_0 + 12];
    for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
      rtb_theta_tmp = xpageoffset << 2;
      c_b[p05_tmp_0 + rtb_theta_tmp] = ((rtb_gd[rtb_theta_tmp + 1] * s +
        rtb_gd[rtb_theta_tmp] * cy) + rtb_gd[rtb_theta_tmp + 2] * a_1) +
        rtb_gd[rtb_theta_tmp + 3] * R_0;
    }

    b_b[(p05_tmp_0 << 2) + 3] = p05_tmp[p05_tmp_0];
  }

  rtb_gd[0] = e_R[0];
  rtb_gd[4] = e_R[3];
  rtb_gd[8] = e_R[6];
  rtb_gd[12] = e_p_data[0];
  rtb_gd[1] = e_R[1];
  rtb_gd[5] = e_R[4];
  rtb_gd[9] = e_R[7];
  rtb_gd[13] = e_p_data[1];
  rtb_gd[2] = e_R[2];
  rtb_gd[6] = e_R[5];
  rtb_gd[10] = e_R[8];
  rtb_gd[14] = e_p_data[2];
  for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
    s = c_b[p05_tmp_0 + 4];
    cy = c_b[p05_tmp_0];
    a_1 = c_b[p05_tmp_0 + 8];
    R_0 = c_b[p05_tmp_0 + 12];
    for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
      rtb_theta_tmp = xpageoffset << 2;
      c_a[p05_tmp_0 + rtb_theta_tmp] = ((b_b[rtb_theta_tmp + 1] * s +
        b_b[rtb_theta_tmp] * cy) + b_b[rtb_theta_tmp + 2] * a_1) +
        b_b[rtb_theta_tmp + 3] * R_0;
    }

    rtb_gd[(p05_tmp_0 << 2) + 3] = p05_tmp[p05_tmp_0];
  }

  b_b[0] = f_R[0];
  b_b[4] = f_R[3];
  b_b[8] = f_R[6];
  b_b[12] = f_p_data[0];
  b_b[1] = f_R[1];
  b_b[5] = f_R[4];
  b_b[9] = f_R[7];
  b_b[13] = f_p_data[1];
  b_b[2] = f_R[2];
  b_b[6] = f_R[5];
  b_b[10] = f_R[8];
  b_b[14] = f_p_data[2];
  for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
    s = c_a[p05_tmp_0 + 4];
    cy = c_a[p05_tmp_0];
    a_1 = c_a[p05_tmp_0 + 8];
    R_0 = c_a[p05_tmp_0 + 12];
    for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
      rtb_theta_tmp = xpageoffset << 2;
      c_b[p05_tmp_0 + rtb_theta_tmp] = ((rtb_gd[rtb_theta_tmp + 1] * s +
        rtb_gd[rtb_theta_tmp] * cy) + rtb_gd[rtb_theta_tmp + 2] * a_1) +
        rtb_gd[rtb_theta_tmp + 3] * R_0;
    }

    b_b[(p05_tmp_0 << 2) + 3] = p05_tmp[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
    s = c_b[p05_tmp_0 + 4];
    cy = c_b[p05_tmp_0];
    a_1 = c_b[p05_tmp_0 + 8];
    R_0 = c_b[p05_tmp_0 + 12];
    for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
      rtb_theta_tmp = xpageoffset << 2;
      c_a[p05_tmp_0 + rtb_theta_tmp] = ((b_b[rtb_theta_tmp + 1] * s +
        b_b[rtb_theta_tmp] * cy) + b_b[rtb_theta_tmp + 2] * a_1) +
        b_b[rtb_theta_tmp + 3] * R_0;
    }

    s = c_a[p05_tmp_0 + 4];
    cy = c_a[p05_tmp_0];
    a_1 = c_a[p05_tmp_0 + 8];
    R_0 = c_a[p05_tmp_0 + 12];
    for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
      rtb_theta_tmp = xpageoffset << 2;
      rtb_gd[p05_tmp_0 + rtb_theta_tmp] = ((g_b[rtb_theta_tmp + 1] * s +
        g_b[rtb_theta_tmp] * cy) + g_b[rtb_theta_tmp + 2] * a_1) +
        g_b[rtb_theta_tmp + 3] * R_0;
    }
  }

  // MATLAB Function: '<S2>/isInitialized' incorporates:
  //   MATLAB Function: '<S3>/MATLAB Function'
  //   SignalConversion generated from: '<S322>/ SFunction '
  //   SignalConversion generated from: '<S6>/ SFunction '

  s = psi;
  for (p05_tmp_0 = 0; p05_tmp_0 < 5; p05_tmp_0++) {
    s += rtb_Switch[p05_tmp_0 + 1];
  }

  if (s == 0.0) {
    // Switch: '<S2>/Switch' incorporates:
    //   Inport: '<Root>/ori_theta_arr'

    rtb_Switch[0] = rtU.ori_theta_arr[0];
    rtb_Switch[1] = rtU.ori_theta_arr[1];
    rtb_Switch[2] = rtU.ori_theta_arr[2];
    rtb_Switch[3] = rtU.ori_theta_arr[3];
    rtb_Switch[4] = rtU.ori_theta_arr[4];
    rtb_Switch[5] = rtU.ori_theta_arr[5];
  } else {
    // Switch: '<S2>/Switch'
    rtb_Switch[0] = psi;
    rtb_Switch[1] = phi;
    rtb_Switch[2] = rtb_TransferFcn9;
    rtb_Switch[3] = rtb_TransferFcn10;
    rtb_Switch[4] = rtb_TransferFcn11;
    rtb_Switch[5] = rtb_TransferFcn12;
  }

  // MATLAB Function: '<S5>/MATLAB Function2'
  for (p05_tmp_0 = 0; p05_tmp_0 < 8; p05_tmp_0++) {
    for (xpageoffset = 0; xpageoffset < 6; xpageoffset++) {
      rtb_theta_tmp = 6 * p05_tmp_0 + xpageoffset;
      x[rtb_theta_tmp] = rtb_theta[rtb_theta_tmp] - rtb_Switch[xpageoffset];
    }
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 48; p05_tmp_0++) {
    y[p05_tmp_0] = std::abs(x[p05_tmp_0]);
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 8; p05_tmp_0++) {
    xpageoffset = p05_tmp_0 * 6;
    s = y[xpageoffset];
    for (rtb_theta_tmp = 0; rtb_theta_tmp < 5; rtb_theta_tmp++) {
      s += y[(xpageoffset + rtb_theta_tmp) + 1];
    }

    varargin_1[p05_tmp_0] = s;
  }

  cy = varargin_1[0];
  p05_tmp_0 = 0;
  for (xpageoffset = 0; xpageoffset < 7; xpageoffset++) {
    s = varargin_1[xpageoffset + 1];
    if (cy > s) {
      cy = s;
      p05_tmp_0 = xpageoffset + 1;
    }
  }

  // MATLAB Function: '<Root>/MATLAB Function'
  s = rtb_gd[10] * rtb_gd[10] + rtb_gd[9] * rtb_gd[9];
  cy = std::sqrt(s);
  rtY.Output1[0] = std::atan2(rtb_gd[4], rtb_gd[0]);
  rtY.Output1[1] = std::atan2(-rtb_gd[8], cy);
  rtY.Output1[2] = std::atan2(rtb_gd[9], rtb_gd[10]);
  if (s < 2.2204460492503131E-15) {
    xpageoffset = 0;
    for (i = 0; i < 1; i++) {
      xpageoffset++;
    }

    c_a_tmp_1 = xpageoffset;
    xpageoffset = 0;
    rtb_theta_tmp = 0;
    for (i = 0; i < 1; i++) {
      rtb_theta_tmp = xpageoffset + 1;
      xpageoffset++;
    }

    if (rtb_theta_tmp - 1 >= 0) {
      x_data = -rtb_gd[1];
    }

    xpageoffset = 0;
    for (i = 0; i < 1; i++) {
      xpageoffset++;
    }

    if (rtb_theta_tmp <= xpageoffset) {
      csz_idx_2 = static_cast<int8_T>(rtb_theta_tmp);
    } else {
      csz_idx_2 = 0;
    }

    if (csz_idx_2 - 1 >= 0) {
      varargin_1_data = std::atan2(x_data, rtb_gd[5]);
    }

    xpageoffset = 0;
    for (i = 0; i < 1; i++) {
      xpageoffset++;
    }

    x_size[0] = 1;
    x_size[1] = 1;
    x_size[2] = xpageoffset;
    if (xpageoffset - 1 >= 0) {
      x_data = -rtb_gd[8];
    }

    if (c_a_tmp_1 == xpageoffset) {
      reshapes[1].f1.size[2] = xpageoffset;
      if (xpageoffset - 1 >= 0) {
        reshapes[1].f1.data = std::atan2(x_data, cy);
      }
    } else {
      cy_size[0] = 1;
      cy_size[1] = 1;
      cy_size[2] = c_a_tmp_1;
      if (c_a_tmp_1 - 1 >= 0) {
        cy_data = cy;
      }

      expand_atan2(&x_data, x_size, &cy_data, cy_size, &reshapes[1].f1.data,
                   reshapes[1].f1.size);
    }

    if (csz_idx_2 - 1 >= 0) {
      rtY.Output1[0] = varargin_1_data;
    }

    if (reshapes[1].f1.size[2] - 1 >= 0) {
      rtY.Output1[1] = reshapes[1].f1.data;
    }

    rtY.Output1[2] = 0.0;
  }

  rtY.Output1[0] = -rtY.Output1[0];
  rtY.Output1[1] = -rtY.Output1[1];
  rtY.Output1[2] = -rtY.Output1[2];
  s = rtY.Output1[0];
  rtY.Output1[0] = rtY.Output1[2];
  rtY.Output1[2] = s;

  // Outport: '<Root>/Output' incorporates:
  //   MATLAB Function: '<Root>/MATLAB Function'

  rtY.Output[0] = rtb_gd[12];
  rtY.Output[1] = rtb_gd[13];
  rtY.Output[2] = rtb_gd[14];
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S13>/MATLAB Function' incorporates:
    //   Constant: '<S13>/Constant'
    //   Constant: '<S13>/Constant1'
    //   Constant: '<S13>/Constant2'
    //   Delay: '<S13>/Delay One Step2'
    //   Delay: '<S13>/Delay One Step3'
    //   MATLAB Function: '<S5>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0], rtDW.DelayOneStep2_DSTATE,
                   rtDW.DelayOneStep3_DSTATE, 100.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_f, &rtDW.sf_MATLABFunction_f);
  }

  // MATLAB Function: '<S13>/MATLAB Function1' incorporates:
  //   Constant: '<S13>/Constant1'
  //   Constant: '<S13>/Constant2'
  //   MATLAB Function: '<S5>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_f.tB, rtB.sf_MATLABFunction_f.dB,
                  rtB.sf_MATLABFunction_f.tA, rtB.sf_MATLABFunction_f.dA,
                  rtB.sf_MATLABFunction_f.dCV, rtB.sf_MATLABFunction_f.tCV,
                  rtB.sf_MATLABFunction_f.s, rtB.sf_MATLABFunction_f.vT,
                  rtB.sf_MATLABFunction_f.tD, rtB.sf_MATLABFunction_f.sM,
                  rtB.sf_MATLABFunction_f.t, rtb_theta[6 * p05_tmp_0],
                  rtB.sf_MATLABFunction_f.oP, rtB.sf_MATLABFunction_f.oV, 100.0,
                  180.0, &rtB.pos_i, &rtB.vel_j2, &s);

  // Sum: '<S4>/Sum13'
  s = rtB.pos_i - psi;

  // Gain: '<S149>/Filter Coefficient' incorporates:
  //   Gain: '<S140>/Derivative Gain'
  //   Integrator: '<S141>/Filter'
  //   Sum: '<S141>/SumD'

  rtB.FilterCoefficient = (-0.0900818829328251 * s - rtX.Filter_CSTATE) *
    186.823463181414;

  // Sum: '<S155>/Sum' incorporates:
  //   Gain: '<S151>/Proportional Gain'
  //   Integrator: '<S146>/Integrator'

  rtB.Sum = (16.8294093394131 * s + rtX.Integrator_CSTATE) +
    rtB.FilterCoefficient;

  // Gain: '<S143>/Integral Gain'
  rtB.IntegralGain = 84.3967388731047 * s;
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S14>/MATLAB Function' incorporates:
    //   Constant: '<S14>/Constant'
    //   Constant: '<S14>/Constant1'
    //   Constant: '<S14>/Constant2'
    //   Delay: '<S14>/Delay One Step2'
    //   Delay: '<S14>/Delay One Step3'
    //   MATLAB Function: '<S5>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 1], rtDW.DelayOneStep2_DSTATE_e,
                   rtDW.DelayOneStep3_DSTATE_h, 100.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_m, &rtDW.sf_MATLABFunction_m);
  }

  // MATLAB Function: '<S14>/MATLAB Function1' incorporates:
  //   Constant: '<S14>/Constant1'
  //   Constant: '<S14>/Constant2'
  //   MATLAB Function: '<S5>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_m.tB, rtB.sf_MATLABFunction_m.dB,
                  rtB.sf_MATLABFunction_m.tA, rtB.sf_MATLABFunction_m.dA,
                  rtB.sf_MATLABFunction_m.dCV, rtB.sf_MATLABFunction_m.tCV,
                  rtB.sf_MATLABFunction_m.s, rtB.sf_MATLABFunction_m.vT,
                  rtB.sf_MATLABFunction_m.tD, rtB.sf_MATLABFunction_m.sM,
                  rtB.sf_MATLABFunction_m.t, rtb_theta[6 * p05_tmp_0 + 1],
                  rtB.sf_MATLABFunction_m.oP, rtB.sf_MATLABFunction_m.oV, 100.0,
                  180.0, &rtB.pos_g, &rtB.vel_j, &s);

  // Sum: '<S4>/Sum7'
  s = rtB.pos_g - phi;

  // Gain: '<S197>/Filter Coefficient' incorporates:
  //   Gain: '<S188>/Derivative Gain'
  //   Integrator: '<S189>/Filter'
  //   Sum: '<S189>/SumD'

  rtB.FilterCoefficient_l = (-0.0900818829328251 * s - rtX.Filter_CSTATE_k) *
    186.823463181414;

  // Sum: '<S203>/Sum' incorporates:
  //   Gain: '<S199>/Proportional Gain'
  //   Integrator: '<S194>/Integrator'

  rtB.Sum_d = (16.8294093394131 * s + rtX.Integrator_CSTATE_d) +
    rtB.FilterCoefficient_l;

  // Gain: '<S191>/Integral Gain'
  rtB.IntegralGain_o = 84.3967388731047 * s;
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S15>/MATLAB Function' incorporates:
    //   Constant: '<S15>/Constant'
    //   Constant: '<S15>/Constant1'
    //   Constant: '<S15>/Constant2'
    //   Delay: '<S15>/Delay One Step2'
    //   Delay: '<S15>/Delay One Step3'
    //   MATLAB Function: '<S5>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 2], rtDW.DelayOneStep2_DSTATE_p,
                   rtDW.DelayOneStep3_DSTATE_i, 100.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_n, &rtDW.sf_MATLABFunction_n);
  }

  // MATLAB Function: '<S15>/MATLAB Function1' incorporates:
  //   Constant: '<S15>/Constant1'
  //   Constant: '<S15>/Constant2'
  //   MATLAB Function: '<S5>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_n.tB, rtB.sf_MATLABFunction_n.dB,
                  rtB.sf_MATLABFunction_n.tA, rtB.sf_MATLABFunction_n.dA,
                  rtB.sf_MATLABFunction_n.dCV, rtB.sf_MATLABFunction_n.tCV,
                  rtB.sf_MATLABFunction_n.s, rtB.sf_MATLABFunction_n.vT,
                  rtB.sf_MATLABFunction_n.tD, rtB.sf_MATLABFunction_n.sM,
                  rtB.sf_MATLABFunction_n.t, rtb_theta[6 * p05_tmp_0 + 2],
                  rtB.sf_MATLABFunction_n.oP, rtB.sf_MATLABFunction_n.oV, 100.0,
                  180.0, &rtB.pos_a5, &rtB.vel_i, &s);

  // Sum: '<S4>/Sum8'
  s = rtB.pos_a5 - rtb_TransferFcn9;

  // Gain: '<S245>/Filter Coefficient' incorporates:
  //   Gain: '<S236>/Derivative Gain'
  //   Integrator: '<S237>/Filter'
  //   Sum: '<S237>/SumD'

  rtB.FilterCoefficient_f = (-0.0900818829328251 * s - rtX.Filter_CSTATE_j) *
    186.823463181414;

  // Sum: '<S251>/Sum' incorporates:
  //   Gain: '<S247>/Proportional Gain'
  //   Integrator: '<S242>/Integrator'

  rtB.Sum_f = (16.8294093394131 * s + rtX.Integrator_CSTATE_f) +
    rtB.FilterCoefficient_f;

  // Gain: '<S239>/Integral Gain'
  rtB.IntegralGain_n = 84.3967388731047 * s;
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S16>/MATLAB Function' incorporates:
    //   Constant: '<S16>/Constant'
    //   Constant: '<S16>/Constant1'
    //   Constant: '<S16>/Constant2'
    //   Delay: '<S16>/Delay One Step2'
    //   Delay: '<S16>/Delay One Step3'
    //   MATLAB Function: '<S5>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 3], rtDW.DelayOneStep2_DSTATE_f,
                   rtDW.DelayOneStep3_DSTATE_l, 100.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_fe, &rtDW.sf_MATLABFunction_fe);
  }

  // MATLAB Function: '<S16>/MATLAB Function1' incorporates:
  //   Constant: '<S16>/Constant1'
  //   Constant: '<S16>/Constant2'
  //   MATLAB Function: '<S5>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_fe.tB, rtB.sf_MATLABFunction_fe.dB,
                  rtB.sf_MATLABFunction_fe.tA, rtB.sf_MATLABFunction_fe.dA,
                  rtB.sf_MATLABFunction_fe.dCV, rtB.sf_MATLABFunction_fe.tCV,
                  rtB.sf_MATLABFunction_fe.s, rtB.sf_MATLABFunction_fe.vT,
                  rtB.sf_MATLABFunction_fe.tD, rtB.sf_MATLABFunction_fe.sM,
                  rtB.sf_MATLABFunction_fe.t, rtb_theta[6 * p05_tmp_0 + 3],
                  rtB.sf_MATLABFunction_fe.oP, rtB.sf_MATLABFunction_fe.oV,
                  100.0, 180.0, &rtB.pos_h, &rtB.vel_es, &s);

  // Sum: '<S4>/Sum9'
  s = rtB.pos_h - rtb_TransferFcn10;

  // Gain: '<S293>/Filter Coefficient' incorporates:
  //   Gain: '<S284>/Derivative Gain'
  //   Integrator: '<S285>/Filter'
  //   Sum: '<S285>/SumD'

  rtB.FilterCoefficient_fr = (-0.0900818829328251 * s - rtX.Filter_CSTATE_c) *
    186.823463181414;

  // Sum: '<S299>/Sum' incorporates:
  //   Gain: '<S295>/Proportional Gain'
  //   Integrator: '<S290>/Integrator'

  rtB.Sum_h = (16.8294093394131 * s + rtX.Integrator_CSTATE_g) +
    rtB.FilterCoefficient_fr;

  // Gain: '<S287>/Integral Gain'
  rtB.IntegralGain_a = 84.3967388731047 * s;
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S17>/MATLAB Function' incorporates:
    //   Constant: '<S17>/Constant'
    //   Constant: '<S17>/Constant1'
    //   Constant: '<S17>/Constant2'
    //   Delay: '<S17>/Delay One Step2'
    //   Delay: '<S17>/Delay One Step3'
    //   MATLAB Function: '<S5>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 4], rtDW.DelayOneStep2_DSTATE_i,
                   rtDW.DelayOneStep3_DSTATE_f, 100.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_e, &rtDW.sf_MATLABFunction_e);
  }

  // MATLAB Function: '<S17>/MATLAB Function1' incorporates:
  //   Constant: '<S17>/Constant1'
  //   Constant: '<S17>/Constant2'
  //   MATLAB Function: '<S5>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_e.tB, rtB.sf_MATLABFunction_e.dB,
                  rtB.sf_MATLABFunction_e.tA, rtB.sf_MATLABFunction_e.dA,
                  rtB.sf_MATLABFunction_e.dCV, rtB.sf_MATLABFunction_e.tCV,
                  rtB.sf_MATLABFunction_e.s, rtB.sf_MATLABFunction_e.vT,
                  rtB.sf_MATLABFunction_e.tD, rtB.sf_MATLABFunction_e.sM,
                  rtB.sf_MATLABFunction_e.t, rtb_theta[6 * p05_tmp_0 + 4],
                  rtB.sf_MATLABFunction_e.oP, rtB.sf_MATLABFunction_e.oV, 100.0,
                  180.0, &rtB.pos_a, &rtB.vel_e, &s);

  // Sum: '<S4>/Sum10'
  s = rtB.pos_a - rtb_TransferFcn11;

  // Gain: '<S53>/Filter Coefficient' incorporates:
  //   Gain: '<S44>/Derivative Gain'
  //   Integrator: '<S45>/Filter'
  //   Sum: '<S45>/SumD'

  rtB.FilterCoefficient_b = (-0.0900818829328251 * s - rtX.Filter_CSTATE_d) *
    186.823463181414;

  // Sum: '<S59>/Sum' incorporates:
  //   Gain: '<S55>/Proportional Gain'
  //   Integrator: '<S50>/Integrator'

  rtB.Sum_n = (16.8294093394131 * s + rtX.Integrator_CSTATE_di) +
    rtB.FilterCoefficient_b;

  // Gain: '<S47>/Integral Gain'
  rtB.IntegralGain_os = 84.3967388731047 * s;
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S18>/MATLAB Function' incorporates:
    //   Constant: '<S18>/Constant'
    //   Constant: '<S18>/Constant1'
    //   Constant: '<S18>/Constant2'
    //   Delay: '<S18>/Delay One Step2'
    //   Delay: '<S18>/Delay One Step3'
    //   MATLAB Function: '<S5>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 5], rtDW.DelayOneStep2_DSTATE_em,
                   rtDW.DelayOneStep3_DSTATE_fz, 100.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_i, &rtDW.sf_MATLABFunction_i);
  }

  // MATLAB Function: '<S18>/MATLAB Function1' incorporates:
  //   Constant: '<S18>/Constant1'
  //   Constant: '<S18>/Constant2'
  //   MATLAB Function: '<S5>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_i.tB, rtB.sf_MATLABFunction_i.dB,
                  rtB.sf_MATLABFunction_i.tA, rtB.sf_MATLABFunction_i.dA,
                  rtB.sf_MATLABFunction_i.dCV, rtB.sf_MATLABFunction_i.tCV,
                  rtB.sf_MATLABFunction_i.s, rtB.sf_MATLABFunction_i.vT,
                  rtB.sf_MATLABFunction_i.tD, rtB.sf_MATLABFunction_i.sM,
                  rtB.sf_MATLABFunction_i.t, rtb_theta[6 * p05_tmp_0 + 5],
                  rtB.sf_MATLABFunction_i.oP, rtB.sf_MATLABFunction_i.oV, 100.0,
                  180.0, &rtB.pos, &rtB.vel, &s);

  // Sum: '<S4>/Sum11'
  s = rtB.pos - rtb_TransferFcn12;

  // Gain: '<S101>/Filter Coefficient' incorporates:
  //   Gain: '<S92>/Derivative Gain'
  //   Integrator: '<S93>/Filter'
  //   Sum: '<S93>/SumD'

  rtB.FilterCoefficient_g = (-0.0900818829328251 * s - rtX.Filter_CSTATE_i) *
    186.823463181414;

  // Sum: '<S107>/Sum' incorporates:
  //   Gain: '<S103>/Proportional Gain'
  //   Integrator: '<S98>/Integrator'

  rtB.Sum_o = (16.8294093394131 * s + rtX.Integrator_CSTATE_o) +
    rtB.FilterCoefficient_g;

  // Gain: '<S95>/Integral Gain'
  rtB.IntegralGain_i = 84.3967388731047 * s;

  // Outport: '<Root>/actual_theta_arr'
  rtY.actual_theta_arr[0] = psi;
  rtY.actual_theta_arr[1] = phi;
  rtY.actual_theta_arr[2] = rtb_TransferFcn9;
  rtY.actual_theta_arr[3] = rtb_TransferFcn10;
  rtY.actual_theta_arr[4] = rtb_TransferFcn11;
  rtY.actual_theta_arr[5] = rtb_TransferFcn12;
  if (rtmIsMajorTimeStep((&rtM))) {
    if (rtmIsMajorTimeStep((&rtM))) {
      // Update for Delay: '<S13>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE = rtB.pos_i;

      // Update for Delay: '<S13>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE = rtB.vel_j2;

      // Update for Delay: '<S14>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_e = rtB.pos_g;

      // Update for Delay: '<S14>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_h = rtB.vel_j;

      // Update for Delay: '<S15>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_p = rtB.pos_a5;

      // Update for Delay: '<S15>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_i = rtB.vel_i;

      // Update for Delay: '<S16>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_f = rtB.pos_h;

      // Update for Delay: '<S16>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_l = rtB.vel_es;

      // Update for Delay: '<S17>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_i = rtB.pos_a;

      // Update for Delay: '<S17>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_f = rtB.vel_e;

      // Update for Delay: '<S18>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_em = rtB.pos;

      // Update for Delay: '<S18>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_fz = rtB.vel;
    }
  }                                    // end MajorTimeStep

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
      // Update absolute timer for sample time: [0.001s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.001, which is the step size
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

  // Derivatives for TransferFcn: '<S4>/Transfer Fcn7'
  _rtXdot->TransferFcn7_CSTATE[0] = -7.0 * rtX.TransferFcn7_CSTATE[1];
  _rtXdot->TransferFcn7_CSTATE[0] -= rtX.TransferFcn7_CSTATE[2];
  _rtXdot->TransferFcn7_CSTATE[1] = rtX.TransferFcn7_CSTATE[0];
  _rtXdot->TransferFcn7_CSTATE[2] = rtX.TransferFcn7_CSTATE[1];
  _rtXdot->TransferFcn7_CSTATE[0] += rtB.Sum;

  // Derivatives for TransferFcn: '<S4>/Transfer Fcn8'
  _rtXdot->TransferFcn8_CSTATE[0] = -7.0 * rtX.TransferFcn8_CSTATE[1];
  _rtXdot->TransferFcn8_CSTATE[0] -= rtX.TransferFcn8_CSTATE[2];
  _rtXdot->TransferFcn8_CSTATE[1] = rtX.TransferFcn8_CSTATE[0];
  _rtXdot->TransferFcn8_CSTATE[2] = rtX.TransferFcn8_CSTATE[1];
  _rtXdot->TransferFcn8_CSTATE[0] += rtB.Sum_d;

  // Derivatives for TransferFcn: '<S4>/Transfer Fcn9'
  _rtXdot->TransferFcn9_CSTATE[0] = -7.0 * rtX.TransferFcn9_CSTATE[1];
  _rtXdot->TransferFcn9_CSTATE[0] -= rtX.TransferFcn9_CSTATE[2];
  _rtXdot->TransferFcn9_CSTATE[1] = rtX.TransferFcn9_CSTATE[0];
  _rtXdot->TransferFcn9_CSTATE[2] = rtX.TransferFcn9_CSTATE[1];
  _rtXdot->TransferFcn9_CSTATE[0] += rtB.Sum_f;

  // Derivatives for TransferFcn: '<S4>/Transfer Fcn10'
  _rtXdot->TransferFcn10_CSTATE[0] = -7.0 * rtX.TransferFcn10_CSTATE[1];
  _rtXdot->TransferFcn10_CSTATE[0] -= rtX.TransferFcn10_CSTATE[2];
  _rtXdot->TransferFcn10_CSTATE[1] = rtX.TransferFcn10_CSTATE[0];
  _rtXdot->TransferFcn10_CSTATE[2] = rtX.TransferFcn10_CSTATE[1];
  _rtXdot->TransferFcn10_CSTATE[0] += rtB.Sum_h;

  // Derivatives for TransferFcn: '<S4>/Transfer Fcn11'
  _rtXdot->TransferFcn11_CSTATE[0] = -7.0 * rtX.TransferFcn11_CSTATE[1];
  _rtXdot->TransferFcn11_CSTATE[0] -= rtX.TransferFcn11_CSTATE[2];
  _rtXdot->TransferFcn11_CSTATE[1] = rtX.TransferFcn11_CSTATE[0];
  _rtXdot->TransferFcn11_CSTATE[2] = rtX.TransferFcn11_CSTATE[1];
  _rtXdot->TransferFcn11_CSTATE[0] += rtB.Sum_n;

  // Derivatives for TransferFcn: '<S4>/Transfer Fcn12'
  _rtXdot->TransferFcn12_CSTATE[0] = -7.0 * rtX.TransferFcn12_CSTATE[1];
  _rtXdot->TransferFcn12_CSTATE[0] -= rtX.TransferFcn12_CSTATE[2];
  _rtXdot->TransferFcn12_CSTATE[1] = rtX.TransferFcn12_CSTATE[0];
  _rtXdot->TransferFcn12_CSTATE[2] = rtX.TransferFcn12_CSTATE[1];
  _rtXdot->TransferFcn12_CSTATE[0] += rtB.Sum_o;

  // Derivatives for Integrator: '<S141>/Filter'
  _rtXdot->Filter_CSTATE = rtB.FilterCoefficient;

  // Derivatives for Integrator: '<S146>/Integrator'
  _rtXdot->Integrator_CSTATE = rtB.IntegralGain;

  // Derivatives for Integrator: '<S189>/Filter'
  _rtXdot->Filter_CSTATE_k = rtB.FilterCoefficient_l;

  // Derivatives for Integrator: '<S194>/Integrator'
  _rtXdot->Integrator_CSTATE_d = rtB.IntegralGain_o;

  // Derivatives for Integrator: '<S237>/Filter'
  _rtXdot->Filter_CSTATE_j = rtB.FilterCoefficient_f;

  // Derivatives for Integrator: '<S242>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtB.IntegralGain_n;

  // Derivatives for Integrator: '<S285>/Filter'
  _rtXdot->Filter_CSTATE_c = rtB.FilterCoefficient_fr;

  // Derivatives for Integrator: '<S290>/Integrator'
  _rtXdot->Integrator_CSTATE_g = rtB.IntegralGain_a;

  // Derivatives for Integrator: '<S45>/Filter'
  _rtXdot->Filter_CSTATE_d = rtB.FilterCoefficient_b;

  // Derivatives for Integrator: '<S50>/Integrator'
  _rtXdot->Integrator_CSTATE_di = rtB.IntegralGain_os;

  // Derivatives for Integrator: '<S93>/Filter'
  _rtXdot->Filter_CSTATE_i = rtB.FilterCoefficient_g;

  // Derivatives for Integrator: '<S98>/Integrator'
  _rtXdot->Integrator_CSTATE_o = rtB.IntegralGain_i;
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
  (&rtM)->Timing.stepSize0 = 0.001;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn7'
  rtX.TransferFcn7_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn8'
  rtX.TransferFcn8_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn9'
  rtX.TransferFcn9_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn10'
  rtX.TransferFcn10_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn11'
  rtX.TransferFcn11_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn12'
  rtX.TransferFcn12_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn7'
  rtX.TransferFcn7_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn8'
  rtX.TransferFcn8_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn9'
  rtX.TransferFcn9_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn10'
  rtX.TransferFcn10_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn11'
  rtX.TransferFcn11_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn12'
  rtX.TransferFcn12_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn7'
  rtX.TransferFcn7_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn8'
  rtX.TransferFcn8_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn9'
  rtX.TransferFcn9_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn10'
  rtX.TransferFcn10_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn11'
  rtX.TransferFcn11_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn12'
  rtX.TransferFcn12_CSTATE[2] = 0.0;

  // InitializeConditions for Integrator: '<S141>/Filter'
  rtX.Filter_CSTATE = 0.0;

  // InitializeConditions for Integrator: '<S146>/Integrator'
  rtX.Integrator_CSTATE = 0.0;

  // InitializeConditions for Integrator: '<S189>/Filter'
  rtX.Filter_CSTATE_k = 0.0;

  // InitializeConditions for Integrator: '<S194>/Integrator'
  rtX.Integrator_CSTATE_d = 0.0;

  // InitializeConditions for Integrator: '<S237>/Filter'
  rtX.Filter_CSTATE_j = 0.0;

  // InitializeConditions for Integrator: '<S242>/Integrator'
  rtX.Integrator_CSTATE_f = 0.0;

  // InitializeConditions for Integrator: '<S285>/Filter'
  rtX.Filter_CSTATE_c = 0.0;

  // InitializeConditions for Integrator: '<S290>/Integrator'
  rtX.Integrator_CSTATE_g = 0.0;

  // InitializeConditions for Integrator: '<S45>/Filter'
  rtX.Filter_CSTATE_d = 0.0;

  // InitializeConditions for Integrator: '<S50>/Integrator'
  rtX.Integrator_CSTATE_di = 0.0;

  // InitializeConditions for Integrator: '<S93>/Filter'
  rtX.Filter_CSTATE_i = 0.0;

  // InitializeConditions for Integrator: '<S98>/Integrator'
  rtX.Integrator_CSTATE_o = 0.0;
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
  rtDW(),
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
