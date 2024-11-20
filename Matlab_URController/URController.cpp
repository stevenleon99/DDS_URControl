//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: URController.cpp
//
// Code generated for Simulink model 'URController'.
//
// Model version                  : 1.277
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Wed Nov 20 00:49:24 2024
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
//    '<S7>/velConvert'
//    '<S8>/velConvert'
//    '<S9>/velConvert'
//    '<S10>/velConvert'
//    '<S11>/velConvert'
//    '<S12>/velConvert'
//
void URController::velConvert(real_T rtu_vol, real_T rtu_maxVel, real_T
  rtu_maxVol, real_T *rty_vel)
{
  *rty_vel = rtu_vol / rtu_maxVol * rtu_maxVel;
}

//
// Output and update for atomic system:
//    '<S7>/voltageConvert'
//    '<S8>/voltageConvert'
//    '<S9>/voltageConvert'
//    '<S10>/voltageConvert'
//    '<S11>/voltageConvert'
//    '<S12>/voltageConvert'
//
void URController::voltageConvert(real_T rtu_vel, real_T rtu_maxVel, real_T
  rtu_maxVol, real_T *rty_voltage)
{
  *rty_voltage = rtu_vel / rtu_maxVel * rtu_maxVol;
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
  real_T a_1;
  real_T a_2;
  real_T a_3;
  real_T b_tmp;
  real_T c_a_3;
  real_T c_a_4;
  real_T cy;
  real_T cy_data;
  real_T phi;
  real_T psi;
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
  int8_T b_tmp_0[3];
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
  cy = std::sin(rtU.desire_pos_orient_arr[4]);
  b_tmp = std::cos(rtU.desire_pos_orient_arr[4]);
  c_a_3 = std::sin(rtU.desire_pos_orient_arr[5]);
  c_a_4 = std::cos(rtU.desire_pos_orient_arr[5]);
  R[1] = 0.0;
  R[4] = psi;
  R[7] = -phi;
  R[2] = 0.0;
  R[5] = phi;
  R[8] = psi;
  b_R[0] = b_tmp;
  b_R[3] = 0.0;
  b_R[6] = cy;
  rtb_gd[12] = rtU.desire_pos_orient_arr[0];
  R[0] = 1.0;
  b_R[1] = 0.0;
  rtb_gd[13] = rtU.desire_pos_orient_arr[1];
  R[3] = 0.0;
  b_R[4] = 1.0;
  rtb_gd[14] = rtU.desire_pos_orient_arr[2];
  R[6] = 0.0;
  b_R[7] = 0.0;
  b_R[2] = -cy;
  b_R[5] = 0.0;
  b_R[8] = b_tmp;
  c_R[0] = c_a_4;
  c_R[3] = -c_a_3;
  c_R[6] = 0.0;
  c_R[1] = c_a_3;
  c_R[4] = c_a_4;
  c_R[7] = 0.0;
  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    psi = R[p05_tmp_0 + 3];
    cy = R[p05_tmp_0];
    phi = R[p05_tmp_0 + 6];
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      b_0[p05_tmp_0 + 3 * xpageoffset] = (b_R[3 * xpageoffset + 1] * psi + b_R[3
        * xpageoffset] * cy) + b_R[3 * xpageoffset + 2] * phi;
    }

    c_R[3 * p05_tmp_0 + 2] = d[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    phi = c_R[3 * p05_tmp_0 + 1];
    psi = c_R[3 * p05_tmp_0];
    cy = c_R[3 * p05_tmp_0 + 2];
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      rtb_gd[xpageoffset + (p05_tmp_0 << 2)] = (b_0[xpageoffset + 3] * phi + psi
        * b_0[xpageoffset]) + b_0[xpageoffset + 6] * cy;
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
  cy = (psi + 1.5707963267948966) + phi;
  rtb_theta[0] = cy;
  psi = (psi + 1.5707963267948966) - phi;
  rtb_theta[24] = psi;
  rtb_theta[6] = cy;
  rtb_theta[30] = psi;
  rtb_theta[12] = cy;
  rtb_theta[36] = psi;
  rtb_theta[18] = cy;
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
    b_tmp = std::sin(psi);
    cy = std::cos(psi);
    b[0] = cy;
    b[4] = -b_tmp;
    b[8] = 0.0;
    b[1] = b_tmp;
    b[5] = cy;
    b[9] = 0.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      xpageoffset = p05_tmp_0 << 2;
      b[xpageoffset + 2] = d[p05_tmp_0];
      c_b[xpageoffset] = f[3 * p05_tmp_0];
      c_b[xpageoffset + 1] = f[3 * p05_tmp_0 + 1];
      c_b[xpageoffset + 2] = f[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      cy = c_a[p05_tmp_0 + 4];
      b_tmp = c_a[p05_tmp_0];
      c_a_3 = c_a[p05_tmp_0 + 8];
      c_a_4 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * cy + b[c_a_tmp_1] *
          b_tmp) + b[c_a_tmp_1 + 2] * c_a_3) + b[c_a_tmp_1 + 3] * c_a_4;
      }

      cy = c_a_0[p05_tmp_0 + 4];
      b_tmp = c_a_0[p05_tmp_0];
      c_a_3 = c_a_0[p05_tmp_0 + 8];
      c_a_4 = c_a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * cy + b_b[c_a_tmp_1]
          * b_tmp) + b_b[c_a_tmp_1 + 2] * c_a_3) + b_b[c_a_tmp_1 + 3] * c_a_4;
      }

      cy = c_a_1[p05_tmp_0 + 4];
      b_tmp = c_a_1[p05_tmp_0];
      c_a_3 = c_a_1[p05_tmp_0 + 8];
      c_a_4 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * cy + c_b[c_a_tmp_1]
          * b_tmp) + c_b[c_a_tmp_1 + 2] * c_a_3) + c_b[c_a_tmp_1 + 3] * c_a_4;
      }
    }

    inv(c_a_2, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      psi = a[p05_tmp_0];
      cy = a[p05_tmp_0 + 8];
      b_tmp = a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_b[p05_tmp_0 + c_a_tmp_1] = ((rtb_gd[c_a_tmp_1 + 1] * phi +
          rtb_gd[c_a_tmp_1] * psi) + rtb_gd[c_a_tmp_1 + 2] * cy) +
          rtb_gd[c_a_tmp_1 + 3] * b_tmp;
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
    b_tmp = std::sin(psi);
    cy = std::cos(psi);
    b[0] = cy;
    b[4] = -b_tmp;
    b[8] = 0.0;
    b[1] = b_tmp;
    b[5] = cy;
    b[9] = 0.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      xpageoffset = p05_tmp_0 << 2;
      b[xpageoffset + 2] = d[p05_tmp_0];
      c_b[xpageoffset] = f[3 * p05_tmp_0];
      c_b[xpageoffset + 1] = f[3 * p05_tmp_0 + 1];
      c_b[xpageoffset + 2] = f[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      cy = c_a[p05_tmp_0 + 4];
      b_tmp = c_a[p05_tmp_0];
      c_a_3 = c_a[p05_tmp_0 + 8];
      c_a_4 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * cy + b[c_a_tmp_1] *
          b_tmp) + b[c_a_tmp_1 + 2] * c_a_3) + b[c_a_tmp_1 + 3] * c_a_4;
      }

      cy = c_a_0[p05_tmp_0 + 4];
      b_tmp = c_a_0[p05_tmp_0];
      c_a_3 = c_a_0[p05_tmp_0 + 8];
      c_a_4 = c_a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * cy + b_b[c_a_tmp_1]
          * b_tmp) + b_b[c_a_tmp_1 + 2] * c_a_3) + b_b[c_a_tmp_1 + 3] * c_a_4;
      }

      cy = c_a_1[p05_tmp_0 + 4];
      b_tmp = c_a_1[p05_tmp_0];
      c_a_3 = c_a_1[p05_tmp_0 + 8];
      c_a_4 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * cy + c_b[c_a_tmp_1]
          * b_tmp) + c_b[c_a_tmp_1 + 2] * c_a_3) + c_b[c_a_tmp_1 + 3] * c_a_4;
      }
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      psi = a[p05_tmp_0];
      cy = a[p05_tmp_0 + 8];
      b_tmp = a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_tmp[p05_tmp_0 + c_a_tmp_1] = ((c_a_2[c_a_tmp_1 + 1] * phi +
          c_a_2[c_a_tmp_1] * psi) + c_a_2[c_a_tmp_1 + 2] * cy) + c_a_2[c_a_tmp_1
          + 3] * b_tmp;
      }
    }

    psi = std::sin(rtb_theta[rtb_theta_tmp + 4]);
    psi = std::atan2(-c_a_tmp[9] / psi, c_a_tmp[8] / psi);
    rtb_theta[6 * i + 5] = psi;
    rtb_theta[6 * (i + 1) + 5] = psi;
  }

  b_tmp_0[0] = 0;
  b_tmp_0[1] = 0;
  b_tmp_0[2] = 1;
  for (b_i = 0; b_i < 4; b_i++) {
    i = b_i << 1;
    rtb_theta_tmp = i * 6;
    psi = rtb_theta[rtb_theta_tmp];
    b_tmp = std::sin(psi);
    cy = std::cos(psi);
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
    b[0] = cy;
    b[4] = -b_tmp;
    b[8] = 0.0;
    b[1] = b_tmp;
    b[5] = cy;
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
      cy = c_a[p05_tmp_0 + 4];
      b_tmp = c_a[p05_tmp_0];
      c_a_3 = c_a[p05_tmp_0 + 8];
      c_a_4 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * cy + b[c_a_tmp_1] *
          b_tmp) + b[c_a_tmp_1 + 2] * c_a_3) + b[c_a_tmp_1 + 3] * c_a_4;
      }

      cy = c_a_1[p05_tmp_0 + 4];
      b_tmp = c_a_1[p05_tmp_0];
      c_a_3 = c_a_1[p05_tmp_0 + 8];
      c_a_4 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * cy + b_b[c_a_tmp_1]
          * b_tmp) + b_b[c_a_tmp_1 + 2] * c_a_3) + b_b[c_a_tmp_1 + 3] * c_a_4;
      }

      cy = c_a_0[p05_tmp_0 + 4];
      b_tmp = c_a_0[p05_tmp_0];
      c_a_3 = c_a_0[p05_tmp_0 + 8];
      c_a_4 = c_a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * cy + c_b[c_a_tmp_1]
          * b_tmp) + c_b[c_a_tmp_1 + 2] * c_a_3) + c_b[c_a_tmp_1 + 3] * c_a_4;
      }
    }

    inv(c_a_2, c_a);
    psi = rtb_theta[rtb_theta_tmp + 5];
    b_tmp = std::sin(psi);
    cy = std::cos(psi);
    std::memcpy(&a[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&b_b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&c_b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    a[14] = 0.0825;
    b_b[12] = 0.0;
    b[0] = cy;
    b[4] = -b_tmp;
    b[8] = 0.0;
    b[1] = b_tmp;
    b[5] = cy;
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
      phi = a[p05_tmp_0 + 4];
      a_1 = a[p05_tmp_0];
      a_2 = a[p05_tmp_0 + 8];
      a_3 = a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * phi + b[c_a_tmp_1] *
          a_1) + b[c_a_tmp_1 + 2] * a_2) + b[c_a_tmp_1 + 3] * a_3;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      a_1 = c_a_2[p05_tmp_0];
      a_2 = c_a_2[p05_tmp_0 + 8];
      a_3 = c_a_2[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_0[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * phi + b_b[c_a_tmp_1]
          * a_1) + b_b[c_a_tmp_1 + 2] * a_2) + b_b[c_a_tmp_1 + 3] * a_3;
      }

      phi = a_0[p05_tmp_0 + 4];
      a_1 = a_0[p05_tmp_0];
      a_2 = a_0[p05_tmp_0 + 8];
      a_3 = a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * phi +
          c_b[c_a_tmp_1] * a_1) + c_b[c_a_tmp_1 + 2] * a_2) + c_b[c_a_tmp_1 + 3]
          * a_3;
      }
    }

    inv(c_a_0, b_b);
    std::memcpy(&a[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    std::memcpy(&c_b[0], &c_a_tmp[0], sizeof(real_T) << 4U);
    a[14] = 0.09475;
    b[12] = 0.0;
    psi = rtb_theta[rtb_theta_tmp + 4];
    cy = std::sin(psi);
    phi = std::cos(psi);
    c_b[0] = phi;
    c_b[4] = -cy;
    c_b[8] = 0.0;
    c_b[1] = cy;
    c_b[5] = phi;
    c_b[9] = 0.0;
    for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
      xpageoffset = p05_tmp_0 << 2;
      c_b[xpageoffset + 2] = b_tmp_0[p05_tmp_0];
      c_a_tmp[xpageoffset] = h[3 * p05_tmp_0];
      c_a_tmp[xpageoffset + 1] = h[3 * p05_tmp_0 + 1];
      c_a_tmp[xpageoffset + 2] = h[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      a_1 = a[p05_tmp_0];
      a_2 = a[p05_tmp_0 + 8];
      a_3 = a[p05_tmp_0 + 12];
      cy = c_a[p05_tmp_0 + 4];
      b_tmp = c_a[p05_tmp_0];
      c_a_3 = c_a[p05_tmp_0 + 8];
      c_a_4 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_tmp = p05_tmp_0 + c_a_tmp_1;
        c_a_2[a_tmp] = ((c_b[c_a_tmp_1 + 1] * phi + c_b[c_a_tmp_1] * a_1) +
                        c_b[c_a_tmp_1 + 2] * a_2) + c_b[c_a_tmp_1 + 3] * a_3;
        c_a_1[a_tmp] = ((rtb_gd[c_a_tmp_1 + 1] * cy + rtb_gd[c_a_tmp_1] * b_tmp)
                        + rtb_gd[c_a_tmp_1 + 2] * c_a_3) + rtb_gd[c_a_tmp_1 + 3]
          * c_a_4;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      a_1 = c_a_2[p05_tmp_0];
      a_2 = c_a_2[p05_tmp_0 + 8];
      a_3 = c_a_2[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_0[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * phi + b[c_a_tmp_1] *
          a_1) + b[c_a_tmp_1 + 2] * a_2) + b[c_a_tmp_1 + 3] * a_3;
      }

      phi = a_0[p05_tmp_0 + 4];
      a_1 = a_0[p05_tmp_0];
      a_2 = a_0[p05_tmp_0 + 8];
      a_3 = a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((c_a_tmp[c_a_tmp_1 + 1] * phi +
          c_a_tmp[c_a_tmp_1] * a_1) + c_a_tmp[c_a_tmp_1 + 2] * a_2) +
          c_a_tmp[c_a_tmp_1 + 3] * a_3;
      }
    }

    inv(c_a_0, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      cy = c_a_1[p05_tmp_0 + 4];
      b_tmp = c_a_1[p05_tmp_0];
      c_a_3 = c_a_1[p05_tmp_0 + 8];
      c_a_4 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * cy + b_b[c_a_tmp_1] *
          b_tmp) + b_b[c_a_tmp_1 + 2] * c_a_3) + b_b[c_a_tmp_1 + 3] * c_a_4;
      }

      phi = 0.0;
      cy = c_a[p05_tmp_0 + 4];
      b_tmp = c_a[p05_tmp_0];
      c_a_3 = c_a[p05_tmp_0 + 8];
      c_a_4 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        phi += (((a[c_a_tmp_1 + 1] * cy + a[c_a_tmp_1] * b_tmp) + a[c_a_tmp_1 +
                 2] * c_a_3) + a[c_a_tmp_1 + 3] * c_a_4) * k[xpageoffset];
      }

      p05[p05_tmp_0] = phi - static_cast<real_T>(p05_tmp[p05_tmp_0]);
    }

    psi = norm(p05);
    psi = std::acos(((psi * psi - 0.18062499999999998) - 0.15366400000000002) /
                    0.3332);
    rtb_theta[rtb_theta_tmp + 2] = psi;
    rtb_theta[6 * (i + 1) + 2] = -psi;
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    R[p05_tmp_0] = g[p05_tmp_0];
  }

  for (rtb_theta_tmp = 0; rtb_theta_tmp < 8; rtb_theta_tmp++) {
    psi = rtb_theta[6 * rtb_theta_tmp];
    b_tmp = std::sin(psi);
    cy = std::cos(psi);
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
    b[0] = cy;
    b[4] = -b_tmp;
    b[8] = 0.0;
    b[1] = b_tmp;
    b[5] = cy;
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
      cy = c_a[p05_tmp_0 + 4];
      b_tmp = c_a[p05_tmp_0];
      c_a_3 = c_a[p05_tmp_0 + 8];
      c_a_4 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * cy + b[c_a_tmp_1] *
          b_tmp) + b[c_a_tmp_1 + 2] * c_a_3) + b[c_a_tmp_1 + 3] * c_a_4;
      }

      cy = c_a_1[p05_tmp_0 + 4];
      b_tmp = c_a_1[p05_tmp_0];
      c_a_3 = c_a_1[p05_tmp_0 + 8];
      c_a_4 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * cy + b_b[c_a_tmp_1]
          * b_tmp) + b_b[c_a_tmp_1 + 2] * c_a_3) + b_b[c_a_tmp_1 + 3] * c_a_4;
      }

      cy = c_a_0[p05_tmp_0 + 4];
      b_tmp = c_a_0[p05_tmp_0];
      c_a_3 = c_a_0[p05_tmp_0 + 8];
      c_a_4 = c_a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * cy + c_b[c_a_tmp_1]
          * b_tmp) + c_b[c_a_tmp_1 + 2] * c_a_3) + c_b[c_a_tmp_1 + 3] * c_a_4;
      }
    }

    inv(c_a_2, c_a);
    c_a_3 = rtb_theta[6 * rtb_theta_tmp + 5];
    b_tmp = std::sin(c_a_3);
    cy = std::cos(c_a_3);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      csz_idx_2 = c_a_tmp_0[p05_tmp_0];
      a[p05_tmp_0] = csz_idx_2;
      b_b[p05_tmp_0] = csz_idx_2;
      b[p05_tmp_0] = csz_idx_2;
      c_b[p05_tmp_0] = csz_idx_2;
    }

    a[14] = 0.0825;
    b_b[12] = 0.0;
    b[0] = cy;
    b[4] = -b_tmp;
    b[8] = 0.0;
    b[1] = b_tmp;
    b[5] = cy;
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
      phi = a[p05_tmp_0 + 4];
      a_1 = a[p05_tmp_0];
      a_2 = a[p05_tmp_0 + 8];
      a_3 = a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * phi + b[c_a_tmp_1] *
          a_1) + b[c_a_tmp_1 + 2] * a_2) + b[c_a_tmp_1 + 3] * a_3;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      a_1 = c_a_2[p05_tmp_0];
      a_2 = c_a_2[p05_tmp_0 + 8];
      a_3 = c_a_2[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_0[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * phi + b_b[c_a_tmp_1]
          * a_1) + b_b[c_a_tmp_1 + 2] * a_2) + b_b[c_a_tmp_1 + 3] * a_3;
      }

      phi = a_0[p05_tmp_0 + 4];
      a_1 = a_0[p05_tmp_0];
      a_2 = a_0[p05_tmp_0 + 8];
      a_3 = a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * phi +
          c_b[c_a_tmp_1] * a_1) + c_b[c_a_tmp_1 + 2] * a_2) + c_b[c_a_tmp_1 + 3]
          * a_3;
      }
    }

    inv(c_a_0, b_b);
    c_a_3 = rtb_theta[6 * rtb_theta_tmp + 4];
    cy = std::sin(c_a_3);
    phi = std::cos(c_a_3);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      csz_idx_2 = c_a_tmp_0[p05_tmp_0];
      a[p05_tmp_0] = csz_idx_2;
      b[p05_tmp_0] = csz_idx_2;
      c_b[p05_tmp_0] = csz_idx_2;
      c_a_tmp[p05_tmp_0] = csz_idx_2;
    }

    a[14] = 0.09475;
    b[12] = 0.0;
    c_b[0] = phi;
    c_b[4] = -cy;
    c_b[8] = 0.0;
    c_b[1] = cy;
    c_b[5] = phi;
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
      phi = a[p05_tmp_0 + 4];
      a_1 = a[p05_tmp_0];
      a_2 = a[p05_tmp_0 + 8];
      a_3 = a[p05_tmp_0 + 12];
      cy = c_a[p05_tmp_0 + 4];
      b_tmp = c_a[p05_tmp_0];
      c_a_3 = c_a[p05_tmp_0 + 8];
      c_a_4 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_tmp = p05_tmp_0 + c_a_tmp_1;
        c_a_2[a_tmp] = ((c_b[c_a_tmp_1 + 1] * phi + c_b[c_a_tmp_1] * a_1) +
                        c_b[c_a_tmp_1 + 2] * a_2) + c_b[c_a_tmp_1 + 3] * a_3;
        c_a_1[a_tmp] = ((rtb_gd[c_a_tmp_1 + 1] * cy + rtb_gd[c_a_tmp_1] * b_tmp)
                        + rtb_gd[c_a_tmp_1 + 2] * c_a_3) + rtb_gd[c_a_tmp_1 + 3]
          * c_a_4;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      a_1 = c_a_2[p05_tmp_0];
      a_2 = c_a_2[p05_tmp_0 + 8];
      a_3 = c_a_2[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_0[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * phi + b[c_a_tmp_1] *
          a_1) + b[c_a_tmp_1 + 2] * a_2) + b[c_a_tmp_1 + 3] * a_3;
      }

      phi = a_0[p05_tmp_0 + 4];
      a_1 = a_0[p05_tmp_0];
      a_2 = a_0[p05_tmp_0 + 8];
      a_3 = a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((c_a_tmp[c_a_tmp_1 + 1] * phi +
          c_a_tmp[c_a_tmp_1] * a_1) + c_a_tmp[c_a_tmp_1 + 2] * a_2) +
          c_a_tmp[c_a_tmp_1 + 3] * a_3;
      }
    }

    inv(c_a_0, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      cy = c_a_1[p05_tmp_0 + 4];
      b_tmp = c_a_1[p05_tmp_0];
      c_a_3 = c_a_1[p05_tmp_0 + 8];
      c_a_4 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * cy + b_b[c_a_tmp_1] *
          b_tmp) + b_b[c_a_tmp_1 + 2] * c_a_3) + b_b[c_a_tmp_1 + 3] * c_a_4;
      }

      phi = 0.0;
      cy = c_a[p05_tmp_0 + 4];
      b_tmp = c_a[p05_tmp_0];
      c_a_3 = c_a[p05_tmp_0 + 8];
      c_a_4 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        i = xpageoffset << 2;
        a_1 = ((a[i + 1] * cy + a[i] * b_tmp) + a[i + 2] * c_a_3) + a[i + 3] *
          c_a_4;
        T14[p05_tmp_0 + i] = a_1;
        phi += a_1 * k[xpageoffset];
      }

      p05[p05_tmp_0] = phi - static_cast<real_T>(p05_tmp[p05_tmp_0]);
    }

    c_a_3 = rtb_theta[6 * rtb_theta_tmp + 2];
    cy = std::sin(c_a_3);
    phi = std::asin(-0.392 * cy / norm(p05)) - std::atan2(p05[1], -p05[0]);
    rtb_theta[6 * rtb_theta_tmp + 1] = phi;
    b_tmp = std::cos(c_a_3);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      csz_idx_2 = c_a_tmp_0[p05_tmp_0];
      c_a[p05_tmp_0] = csz_idx_2;
      b_b[p05_tmp_0] = csz_idx_2;
      b[p05_tmp_0] = csz_idx_2;
      c_b[p05_tmp_0] = csz_idx_2;
    }

    c_a[14] = 0.0;
    b_b[12] = -0.392;
    b[0] = b_tmp;
    b[4] = -cy;
    b[8] = 0.0;
    b[1] = cy;
    b[5] = b_tmp;
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
      cy = c_a[p05_tmp_0 + 4];
      b_tmp = c_a[p05_tmp_0];
      c_a_3 = c_a[p05_tmp_0 + 8];
      c_a_4 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * cy + b[c_a_tmp_1] *
          b_tmp) + b[c_a_tmp_1 + 2] * c_a_3) + b[c_a_tmp_1 + 3] * c_a_4;
      }

      cy = c_a_1[p05_tmp_0 + 4];
      b_tmp = c_a_1[p05_tmp_0];
      c_a_3 = c_a_1[p05_tmp_0 + 8];
      c_a_4 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * cy + b_b[c_a_tmp_1]
          * b_tmp) + b_b[c_a_tmp_1 + 2] * c_a_3) + b_b[c_a_tmp_1 + 3] * c_a_4;
      }

      cy = c_a_0[p05_tmp_0 + 4];
      b_tmp = c_a_0[p05_tmp_0];
      c_a_3 = c_a_0[p05_tmp_0 + 8];
      c_a_4 = c_a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * cy + c_b[c_a_tmp_1]
          * b_tmp) + c_b[c_a_tmp_1 + 2] * c_a_3) + c_b[c_a_tmp_1 + 3] * c_a_4;
      }
    }

    inv(c_a_2, c_a);
    b_tmp = std::sin(phi);
    cy = std::cos(phi);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      csz_idx_2 = c_a_tmp_0[p05_tmp_0];
      a[p05_tmp_0] = csz_idx_2;
      b_b[p05_tmp_0] = csz_idx_2;
      b[p05_tmp_0] = csz_idx_2;
      c_b[p05_tmp_0] = csz_idx_2;
    }

    a[14] = 0.0;
    b_b[12] = -0.425;
    b[0] = cy;
    b[4] = -b_tmp;
    b[8] = 0.0;
    b[1] = b_tmp;
    b[5] = cy;
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
      phi = a[p05_tmp_0 + 4];
      a_1 = a[p05_tmp_0];
      a_2 = a[p05_tmp_0 + 8];
      a_3 = a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_1] = ((b[c_a_tmp_1 + 1] * phi + b[c_a_tmp_1] *
          a_1) + b[c_a_tmp_1 + 2] * a_2) + b[c_a_tmp_1 + 3] * a_3;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      a_1 = c_a_2[p05_tmp_0];
      a_2 = c_a_2[p05_tmp_0 + 8];
      a_3 = c_a_2[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        a_0[p05_tmp_0 + c_a_tmp_1] = ((b_b[c_a_tmp_1 + 1] * phi + b_b[c_a_tmp_1]
          * a_1) + b_b[c_a_tmp_1 + 2] * a_2) + b_b[c_a_tmp_1 + 3] * a_3;
      }

      phi = a_0[p05_tmp_0 + 4];
      a_1 = a_0[p05_tmp_0];
      a_2 = a_0[p05_tmp_0 + 8];
      a_3 = a_0[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_1] = ((c_b[c_a_tmp_1 + 1] * phi +
          c_b[c_a_tmp_1] * a_1) + c_b[c_a_tmp_1 + 2] * a_2) + c_b[c_a_tmp_1 + 3]
          * a_3;
      }
    }

    inv(c_a_0, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      cy = c_a[p05_tmp_0 + 4];
      b_tmp = c_a[p05_tmp_0];
      c_a_3 = c_a[p05_tmp_0 + 8];
      c_a_4 = c_a[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_1] = ((a[c_a_tmp_1 + 1] * cy + a[c_a_tmp_1] *
          b_tmp) + a[c_a_tmp_1 + 2] * c_a_3) + a[c_a_tmp_1 + 3] * c_a_4;
      }

      cy = c_a_1[p05_tmp_0 + 4];
      b_tmp = c_a_1[p05_tmp_0];
      c_a_3 = c_a_1[p05_tmp_0 + 8];
      c_a_4 = c_a_1[p05_tmp_0 + 12];
      for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
        c_a_tmp_1 = xpageoffset << 2;
        c_a_tmp[p05_tmp_0 + c_a_tmp_1] = ((T14[c_a_tmp_1 + 1] * cy +
          T14[c_a_tmp_1] * b_tmp) + T14[c_a_tmp_1 + 2] * c_a_3) + T14[c_a_tmp_1
          + 3] * c_a_4;
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

  // SignalConversion generated from: '<S340>/ SFunction ' incorporates:
  //   Integrator: '<S10>/Integrator'
  //   Integrator: '<S11>/Integrator'
  //   Integrator: '<S12>/Integrator'
  //   Integrator: '<S7>/Integrator'
  //   Integrator: '<S8>/Integrator'
  //   Integrator: '<S9>/Integrator'
  //   MATLAB Function: '<S2>/isInitialized'
  //   MATLAB Function: '<S3>/MATLAB Function'
  //   SignalConversion generated from: '<S6>/ SFunction '

  rtb_Switch[0] = rtX.Integrator_CSTATE;
  rtb_Switch[1] = rtX.Integrator_CSTATE_g;
  rtb_Switch[2] = rtX.Integrator_CSTATE_o;
  rtb_Switch[3] = rtX.Integrator_CSTATE_c;
  rtb_Switch[4] = rtX.Integrator_CSTATE_k;
  rtb_Switch[5] = rtX.Integrator_CSTATE_gj;

  // MATLAB Function: '<S3>/MATLAB Function' incorporates:
  //   Integrator: '<S10>/Integrator'
  //   Integrator: '<S11>/Integrator'
  //   Integrator: '<S12>/Integrator'
  //   Integrator: '<S7>/Integrator'
  //   Integrator: '<S8>/Integrator'
  //   Integrator: '<S9>/Integrator'

  phi = std::sin(rtX.Integrator_CSTATE);
  psi = std::cos(rtX.Integrator_CSTATE);
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
      R[rtb_theta_tmp] = (((1.0 - psi) * static_cast<real_T>(R_tmp[p05_tmp_0 + 3])
                           * static_cast<real_T>(R_tmp[3 * xpageoffset + 1]) +
                           (1.0 - psi) * static_cast<real_T>(R_tmp[p05_tmp_0]) *
                           static_cast<real_T>(R_tmp[3 * xpageoffset])) +
                          static_cast<real_T>(R_tmp[p05_tmp_0 + 6]) * (1.0 - psi)
                          * static_cast<real_T>(R_tmp[3 * xpageoffset + 2])) + (
        static_cast<real_T>(R_tmp[rtb_theta_tmp]) * phi + static_cast<real_T>
        (b_I[rtb_theta_tmp]));
    }
  }

  psi = std::sin(rtX.Integrator_CSTATE_g);
  cy = std::cos(rtX.Integrator_CSTATE_g);
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
        static_cast<real_T>(R_tmp[rtb_theta_tmp]) * psi + static_cast<real_T>
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

  cy = std::sin(rtX.Integrator_CSTATE_o);
  psi = std::cos(rtX.Integrator_CSTATE_o);
  for (p05_tmp_0 = 0; p05_tmp_0 < 9; p05_tmp_0++) {
    b_I[p05_tmp_0] = 0;
  }

  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      rtb_theta_tmp = 3 * xpageoffset + p05_tmp_0;
      c_R[rtb_theta_tmp] = (((1.0 - psi) * static_cast<real_T>(R_tmp[p05_tmp_0 +
        3]) * static_cast<real_T>(R_tmp[3 * xpageoffset + 1]) + (1.0 - psi) *
        static_cast<real_T>(R_tmp[p05_tmp_0]) * static_cast<real_T>(R_tmp[3 *
        xpageoffset])) + static_cast<real_T>(R_tmp[p05_tmp_0 + 6]) * (1.0 - psi)
                            * static_cast<real_T>(R_tmp[3 * xpageoffset + 2])) +
        (static_cast<real_T>(R_tmp[rtb_theta_tmp]) * cy + static_cast<real_T>
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

  psi = std::sin(rtX.Integrator_CSTATE_c);
  cy = std::cos(rtX.Integrator_CSTATE_c);
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
        static_cast<real_T>(R_tmp[rtb_theta_tmp]) * psi + static_cast<real_T>
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

  psi = std::sin(rtX.Integrator_CSTATE_k);
  cy = std::cos(rtX.Integrator_CSTATE_k);
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
                            xpageoffset + 2]) + (f_R[rtb_theta_tmp] * psi +
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

  psi = std::sin(rtX.Integrator_CSTATE_gj);
  cy = std::cos(rtX.Integrator_CSTATE_gj);
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
        static_cast<real_T>(R_tmp[rtb_theta_tmp]) * psi + static_cast<real_T>
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
    psi = c_b[p05_tmp_0 + 4];
    cy = c_b[p05_tmp_0];
    phi = c_b[p05_tmp_0 + 8];
    b_tmp = c_b[p05_tmp_0 + 12];
    for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
      rtb_theta_tmp = xpageoffset << 2;
      c_a[p05_tmp_0 + rtb_theta_tmp] = ((b_b[rtb_theta_tmp + 1] * psi +
        b_b[rtb_theta_tmp] * cy) + b_b[rtb_theta_tmp + 2] * phi) +
        b_b[rtb_theta_tmp + 3] * b_tmp;
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
    psi = c_a[p05_tmp_0 + 4];
    cy = c_a[p05_tmp_0];
    phi = c_a[p05_tmp_0 + 8];
    b_tmp = c_a[p05_tmp_0 + 12];
    for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
      rtb_theta_tmp = xpageoffset << 2;
      c_b[p05_tmp_0 + rtb_theta_tmp] = ((rtb_gd[rtb_theta_tmp + 1] * psi +
        rtb_gd[rtb_theta_tmp] * cy) + rtb_gd[rtb_theta_tmp + 2] * phi) +
        rtb_gd[rtb_theta_tmp + 3] * b_tmp;
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
    psi = c_b[p05_tmp_0 + 4];
    cy = c_b[p05_tmp_0];
    phi = c_b[p05_tmp_0 + 8];
    b_tmp = c_b[p05_tmp_0 + 12];
    for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
      rtb_theta_tmp = xpageoffset << 2;
      c_a[p05_tmp_0 + rtb_theta_tmp] = ((b_b[rtb_theta_tmp + 1] * psi +
        b_b[rtb_theta_tmp] * cy) + b_b[rtb_theta_tmp + 2] * phi) +
        b_b[rtb_theta_tmp + 3] * b_tmp;
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
    psi = c_a[p05_tmp_0 + 4];
    cy = c_a[p05_tmp_0];
    phi = c_a[p05_tmp_0 + 8];
    b_tmp = c_a[p05_tmp_0 + 12];
    for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
      rtb_theta_tmp = xpageoffset << 2;
      c_b[p05_tmp_0 + rtb_theta_tmp] = ((rtb_gd[rtb_theta_tmp + 1] * psi +
        rtb_gd[rtb_theta_tmp] * cy) + rtb_gd[rtb_theta_tmp + 2] * phi) +
        rtb_gd[rtb_theta_tmp + 3] * b_tmp;
    }

    b_b[(p05_tmp_0 << 2) + 3] = p05_tmp[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
    psi = c_b[p05_tmp_0 + 4];
    cy = c_b[p05_tmp_0];
    phi = c_b[p05_tmp_0 + 8];
    b_tmp = c_b[p05_tmp_0 + 12];
    for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
      rtb_theta_tmp = xpageoffset << 2;
      c_a[p05_tmp_0 + rtb_theta_tmp] = ((b_b[rtb_theta_tmp + 1] * psi +
        b_b[rtb_theta_tmp] * cy) + b_b[rtb_theta_tmp + 2] * phi) +
        b_b[rtb_theta_tmp + 3] * b_tmp;
    }

    psi = c_a[p05_tmp_0 + 4];
    cy = c_a[p05_tmp_0];
    phi = c_a[p05_tmp_0 + 8];
    b_tmp = c_a[p05_tmp_0 + 12];
    for (xpageoffset = 0; xpageoffset < 4; xpageoffset++) {
      rtb_theta_tmp = xpageoffset << 2;
      rtb_gd[p05_tmp_0 + rtb_theta_tmp] = ((g_b[rtb_theta_tmp + 1] * psi +
        g_b[rtb_theta_tmp] * cy) + g_b[rtb_theta_tmp + 2] * phi) +
        g_b[rtb_theta_tmp + 3] * b_tmp;
    }
  }

  // MATLAB Function: '<S2>/isInitialized' incorporates:
  //   Integrator: '<S7>/Integrator'
  //   SignalConversion generated from: '<S6>/ SFunction '

  psi = rtX.Integrator_CSTATE;
  for (p05_tmp_0 = 0; p05_tmp_0 < 5; p05_tmp_0++) {
    psi += rtb_Switch[p05_tmp_0 + 1];
  }

  if (psi == 0.0) {
    // Switch: '<S2>/Switch' incorporates:
    //   Inport: '<Root>/ori_theta_arr'

    rtb_Switch[0] = rtU.ori_theta_arr[0];
    rtb_Switch[1] = rtU.ori_theta_arr[1];
    rtb_Switch[2] = rtU.ori_theta_arr[2];
    rtb_Switch[3] = rtU.ori_theta_arr[3];
    rtb_Switch[4] = rtU.ori_theta_arr[4];
    rtb_Switch[5] = rtU.ori_theta_arr[5];
  } else {
    // Switch: '<S2>/Switch' incorporates:
    //   Integrator: '<S10>/Integrator'
    //   Integrator: '<S11>/Integrator'
    //   Integrator: '<S12>/Integrator'
    //   Integrator: '<S8>/Integrator'
    //   Integrator: '<S9>/Integrator'

    rtb_Switch[0] = rtX.Integrator_CSTATE;
    rtb_Switch[1] = rtX.Integrator_CSTATE_g;
    rtb_Switch[2] = rtX.Integrator_CSTATE_o;
    rtb_Switch[3] = rtX.Integrator_CSTATE_c;
    rtb_Switch[4] = rtX.Integrator_CSTATE_k;
    rtb_Switch[5] = rtX.Integrator_CSTATE_gj;
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
    psi = y[xpageoffset];
    for (rtb_theta_tmp = 0; rtb_theta_tmp < 5; rtb_theta_tmp++) {
      psi += y[(xpageoffset + rtb_theta_tmp) + 1];
    }

    varargin_1[p05_tmp_0] = psi;
  }

  cy = varargin_1[0];
  p05_tmp_0 = 0;
  for (xpageoffset = 0; xpageoffset < 7; xpageoffset++) {
    psi = varargin_1[xpageoffset + 1];
    if (cy > psi) {
      cy = psi;
      p05_tmp_0 = xpageoffset + 1;
    }
  }

  // MATLAB Function: '<Root>/MATLAB Function'
  psi = rtb_gd[10] * rtb_gd[10] + rtb_gd[9] * rtb_gd[9];
  cy = std::sqrt(psi);
  rtY.ori_arr[0] = std::atan2(rtb_gd[4], rtb_gd[0]);
  rtY.ori_arr[1] = std::atan2(-rtb_gd[8], cy);
  rtY.ori_arr[2] = std::atan2(rtb_gd[9], rtb_gd[10]);
  if (psi < 2.2204460492503131E-15) {
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
      rtY.ori_arr[0] = varargin_1_data;
    }

    if (reshapes[1].f1.size[2] - 1 >= 0) {
      rtY.ori_arr[1] = reshapes[1].f1.data;
    }

    rtY.ori_arr[2] = 0.0;
  }

  rtY.ori_arr[0] = -rtY.ori_arr[0];
  rtY.ori_arr[1] = -rtY.ori_arr[1];
  rtY.ori_arr[2] = -rtY.ori_arr[2];
  psi = rtY.ori_arr[0];
  rtY.ori_arr[0] = rtY.ori_arr[2];
  rtY.ori_arr[2] = psi;

  // Outport: '<Root>/pos_arr' incorporates:
  //   MATLAB Function: '<Root>/MATLAB Function'

  rtY.pos_arr[0] = rtb_gd[12];
  rtY.pos_arr[1] = rtb_gd[13];
  rtY.pos_arr[2] = rtb_gd[14];
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S13>/MATLAB Function' incorporates:
    //   Constant: '<S13>/Constant'
    //   Constant: '<S13>/Constant1'
    //   Constant: '<S13>/Constant2'
    //   Delay: '<S13>/Delay One Step2'
    //   Delay: '<S13>/Delay One Step3'
    //   MATLAB Function: '<S5>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0], rtDW.DelayOneStep2_DSTATE,
                   rtDW.DelayOneStep3_DSTATE, 300.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_j, &rtDW.sf_MATLABFunction_j);
  }

  // MATLAB Function: '<S13>/MATLAB Function1' incorporates:
  //   Constant: '<S13>/Constant1'
  //   Constant: '<S13>/Constant2'
  //   MATLAB Function: '<S5>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_j.tB, rtB.sf_MATLABFunction_j.dB,
                  rtB.sf_MATLABFunction_j.tA, rtB.sf_MATLABFunction_j.dA,
                  rtB.sf_MATLABFunction_j.dCV, rtB.sf_MATLABFunction_j.tCV,
                  rtB.sf_MATLABFunction_j.s, rtB.sf_MATLABFunction_j.vT,
                  rtB.sf_MATLABFunction_j.tD, rtB.sf_MATLABFunction_j.sM,
                  rtB.sf_MATLABFunction_j.t, rtb_theta[6 * p05_tmp_0],
                  rtB.sf_MATLABFunction_j.oP, rtB.sf_MATLABFunction_j.oV, 300.0,
                  180.0, &rtB.pos_d, &rtB.vel_c3, &psi);

  // MATLAB Function: '<S7>/voltageConvert' incorporates:
  //   Constant: '<S7>/Constant'
  //   Constant: '<S7>/Constant1'

  voltageConvert(rtB.vel_c3, 180.0, 12.0, &psi);

  // TransferFcn: '<S7>/trans func2'
  cy = 361.0 * rtX.transfunc2_CSTATE[1];

  // Sum: '<S7>/Sum14' incorporates:
  //   Integrator: '<S7>/Integrator'
  //   Sum: '<S7>/Sum15'

  phi = ((rtB.pos_d - rtX.Integrator_CSTATE) + psi) - cy;

  // Gain: '<S56>/Filter Coefficient' incorporates:
  //   Gain: '<S47>/Derivative Gain'
  //   Integrator: '<S48>/Filter'
  //   Sum: '<S48>/SumD'

  rtB.FilterCoefficient = (0.327956120616846 * phi - rtX.Filter_CSTATE) *
    454.516416693375;

  // Sum: '<S12>/Sum14' incorporates:
  //   Integrator: '<S53>/Integrator'

  psi = rtX.Integrator_CSTATE_m;

  // Sum: '<S62>/Sum' incorporates:
  //   Gain: '<S58>/Proportional Gain'
  //   Integrator: '<S53>/Integrator'

  rtB.Sum = (10.5857290910674 * phi + rtX.Integrator_CSTATE_m) +
    rtB.FilterCoefficient;

  // Gain: '<S50>/Integral Gain'
  rtB.IntegralGain = 78.2339953359067 * phi;

  // MATLAB Function: '<S7>/velConvert' incorporates:
  //   Constant: '<S7>/Constant2'
  //   Constant: '<S7>/Constant3'

  velConvert(cy, 180.0, 12.0, &rtB.vel_cp);
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S14>/MATLAB Function' incorporates:
    //   Constant: '<S14>/Constant'
    //   Constant: '<S14>/Constant1'
    //   Constant: '<S14>/Constant2'
    //   Delay: '<S14>/Delay One Step2'
    //   Delay: '<S14>/Delay One Step3'
    //   MATLAB Function: '<S5>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 1], rtDW.DelayOneStep2_DSTATE_i,
                   rtDW.DelayOneStep3_DSTATE_m, 300.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_o, &rtDW.sf_MATLABFunction_o);
  }

  // MATLAB Function: '<S14>/MATLAB Function1' incorporates:
  //   Constant: '<S14>/Constant1'
  //   Constant: '<S14>/Constant2'
  //   MATLAB Function: '<S5>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_o.tB, rtB.sf_MATLABFunction_o.dB,
                  rtB.sf_MATLABFunction_o.tA, rtB.sf_MATLABFunction_o.dA,
                  rtB.sf_MATLABFunction_o.dCV, rtB.sf_MATLABFunction_o.tCV,
                  rtB.sf_MATLABFunction_o.s, rtB.sf_MATLABFunction_o.vT,
                  rtB.sf_MATLABFunction_o.tD, rtB.sf_MATLABFunction_o.sM,
                  rtB.sf_MATLABFunction_o.t, rtb_theta[6 * p05_tmp_0 + 1],
                  rtB.sf_MATLABFunction_o.oP, rtB.sf_MATLABFunction_o.oV, 300.0,
                  180.0, &rtB.pos_ms, &rtB.vel_c, &psi);

  // MATLAB Function: '<S8>/voltageConvert' incorporates:
  //   Constant: '<S8>/Constant'
  //   Constant: '<S8>/Constant1'

  voltageConvert(rtB.vel_c, 180.0, 12.0, &psi);

  // TransferFcn: '<S8>/trans func2'
  cy = 361.0 * rtX.transfunc2_CSTATE_o[1];

  // Sum: '<S12>/Sum14' incorporates:
  //   Integrator: '<S8>/Integrator'
  //   Sum: '<S8>/Sum14'
  //   Sum: '<S8>/Sum15'

  psi = ((rtB.pos_ms - rtX.Integrator_CSTATE_g) + psi) - cy;

  // Gain: '<S107>/Filter Coefficient' incorporates:
  //   Gain: '<S98>/Derivative Gain'
  //   Integrator: '<S99>/Filter'
  //   Sum: '<S99>/SumD'

  rtB.FilterCoefficient_c = (0.327956120616846 * psi - rtX.Filter_CSTATE_a) *
    454.516416693375;

  // Sum: '<S113>/Sum' incorporates:
  //   Gain: '<S109>/Proportional Gain'
  //   Integrator: '<S104>/Integrator'

  rtB.Sum_b = (10.5857290910674 * psi + rtX.Integrator_CSTATE_j) +
    rtB.FilterCoefficient_c;

  // Gain: '<S101>/Integral Gain'
  rtB.IntegralGain_f = 78.2339953359067 * psi;

  // MATLAB Function: '<S8>/velConvert' incorporates:
  //   Constant: '<S8>/Constant2'
  //   Constant: '<S8>/Constant3'

  velConvert(cy, 180.0, 12.0, &rtB.vel_k);
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S15>/MATLAB Function' incorporates:
    //   Constant: '<S15>/Constant'
    //   Constant: '<S15>/Constant1'
    //   Constant: '<S15>/Constant2'
    //   Delay: '<S15>/Delay One Step2'
    //   Delay: '<S15>/Delay One Step3'
    //   MATLAB Function: '<S5>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 2], rtDW.DelayOneStep2_DSTATE_p,
                   rtDW.DelayOneStep3_DSTATE_e, 300.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_c, &rtDW.sf_MATLABFunction_c);
  }

  // MATLAB Function: '<S15>/MATLAB Function1' incorporates:
  //   Constant: '<S15>/Constant1'
  //   Constant: '<S15>/Constant2'
  //   MATLAB Function: '<S5>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_c.tB, rtB.sf_MATLABFunction_c.dB,
                  rtB.sf_MATLABFunction_c.tA, rtB.sf_MATLABFunction_c.dA,
                  rtB.sf_MATLABFunction_c.dCV, rtB.sf_MATLABFunction_c.tCV,
                  rtB.sf_MATLABFunction_c.s, rtB.sf_MATLABFunction_c.vT,
                  rtB.sf_MATLABFunction_c.tD, rtB.sf_MATLABFunction_c.sM,
                  rtB.sf_MATLABFunction_c.t, rtb_theta[6 * p05_tmp_0 + 2],
                  rtB.sf_MATLABFunction_c.oP, rtB.sf_MATLABFunction_c.oV, 300.0,
                  180.0, &rtB.pos_n, &rtB.vel_i, &psi);

  // MATLAB Function: '<S9>/voltageConvert' incorporates:
  //   Constant: '<S9>/Constant'
  //   Constant: '<S9>/Constant1'

  voltageConvert(rtB.vel_i, 180.0, 12.0, &psi);

  // TransferFcn: '<S9>/trans func2'
  cy = 361.0 * rtX.transfunc2_CSTATE_ow[1];

  // Sum: '<S12>/Sum14' incorporates:
  //   Integrator: '<S9>/Integrator'
  //   Sum: '<S9>/Sum14'
  //   Sum: '<S9>/Sum15'

  psi = ((rtB.pos_n - rtX.Integrator_CSTATE_o) + psi) - cy;

  // Gain: '<S158>/Filter Coefficient' incorporates:
  //   Gain: '<S149>/Derivative Gain'
  //   Integrator: '<S150>/Filter'
  //   Sum: '<S150>/SumD'

  rtB.FilterCoefficient_cd = (0.327956120616846 * psi - rtX.Filter_CSTATE_c) *
    454.516416693375;

  // Sum: '<S164>/Sum' incorporates:
  //   Gain: '<S160>/Proportional Gain'
  //   Integrator: '<S155>/Integrator'

  rtB.Sum_k = (10.5857290910674 * psi + rtX.Integrator_CSTATE_a) +
    rtB.FilterCoefficient_cd;

  // Gain: '<S152>/Integral Gain'
  rtB.IntegralGain_c = 78.2339953359067 * psi;

  // MATLAB Function: '<S9>/velConvert' incorporates:
  //   Constant: '<S9>/Constant2'
  //   Constant: '<S9>/Constant3'

  velConvert(cy, 180.0, 12.0, &rtB.vel_ha);
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S16>/MATLAB Function' incorporates:
    //   Constant: '<S16>/Constant'
    //   Constant: '<S16>/Constant1'
    //   Constant: '<S16>/Constant2'
    //   Delay: '<S16>/Delay One Step2'
    //   Delay: '<S16>/Delay One Step3'
    //   MATLAB Function: '<S5>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 3], rtDW.DelayOneStep2_DSTATE_m,
                   rtDW.DelayOneStep3_DSTATE_p, 300.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_ow, &rtDW.sf_MATLABFunction_ow);
  }

  // MATLAB Function: '<S16>/MATLAB Function1' incorporates:
  //   Constant: '<S16>/Constant1'
  //   Constant: '<S16>/Constant2'
  //   MATLAB Function: '<S5>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_ow.tB, rtB.sf_MATLABFunction_ow.dB,
                  rtB.sf_MATLABFunction_ow.tA, rtB.sf_MATLABFunction_ow.dA,
                  rtB.sf_MATLABFunction_ow.dCV, rtB.sf_MATLABFunction_ow.tCV,
                  rtB.sf_MATLABFunction_ow.s, rtB.sf_MATLABFunction_ow.vT,
                  rtB.sf_MATLABFunction_ow.tD, rtB.sf_MATLABFunction_ow.sM,
                  rtB.sf_MATLABFunction_ow.t, rtb_theta[6 * p05_tmp_0 + 3],
                  rtB.sf_MATLABFunction_ow.oP, rtB.sf_MATLABFunction_ow.oV,
                  300.0, 180.0, &rtB.pos_m, &rtB.vel_j, &psi);

  // MATLAB Function: '<S10>/voltageConvert' incorporates:
  //   Constant: '<S10>/Constant'
  //   Constant: '<S10>/Constant1'

  voltageConvert(rtB.vel_j, 180.0, 12.0, &psi);

  // TransferFcn: '<S10>/trans func2'
  cy = 361.0 * rtX.transfunc2_CSTATE_c[1];

  // Sum: '<S12>/Sum14' incorporates:
  //   Integrator: '<S10>/Integrator'
  //   Sum: '<S10>/Sum14'
  //   Sum: '<S10>/Sum15'

  psi = ((rtB.pos_m - rtX.Integrator_CSTATE_c) + psi) - cy;

  // Gain: '<S209>/Filter Coefficient' incorporates:
  //   Gain: '<S200>/Derivative Gain'
  //   Integrator: '<S201>/Filter'
  //   Sum: '<S201>/SumD'

  rtB.FilterCoefficient_m = (0.327956120616846 * psi - rtX.Filter_CSTATE_f) *
    454.516416693375;

  // Sum: '<S215>/Sum' incorporates:
  //   Gain: '<S211>/Proportional Gain'
  //   Integrator: '<S206>/Integrator'

  rtB.Sum_j = (10.5857290910674 * psi + rtX.Integrator_CSTATE_an) +
    rtB.FilterCoefficient_m;

  // Gain: '<S203>/Integral Gain'
  rtB.IntegralGain_l = 78.2339953359067 * psi;

  // MATLAB Function: '<S10>/velConvert' incorporates:
  //   Constant: '<S10>/Constant2'
  //   Constant: '<S10>/Constant3'

  velConvert(cy, 180.0, 12.0, &rtB.vel_cx);
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S17>/MATLAB Function' incorporates:
    //   Constant: '<S17>/Constant'
    //   Constant: '<S17>/Constant1'
    //   Constant: '<S17>/Constant2'
    //   Delay: '<S17>/Delay One Step2'
    //   Delay: '<S17>/Delay One Step3'
    //   MATLAB Function: '<S5>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 4], rtDW.DelayOneStep2_DSTATE_f,
                   rtDW.DelayOneStep3_DSTATE_mr, 300.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_cn, &rtDW.sf_MATLABFunction_cn);
  }

  // MATLAB Function: '<S17>/MATLAB Function1' incorporates:
  //   Constant: '<S17>/Constant1'
  //   Constant: '<S17>/Constant2'
  //   MATLAB Function: '<S5>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_cn.tB, rtB.sf_MATLABFunction_cn.dB,
                  rtB.sf_MATLABFunction_cn.tA, rtB.sf_MATLABFunction_cn.dA,
                  rtB.sf_MATLABFunction_cn.dCV, rtB.sf_MATLABFunction_cn.tCV,
                  rtB.sf_MATLABFunction_cn.s, rtB.sf_MATLABFunction_cn.vT,
                  rtB.sf_MATLABFunction_cn.tD, rtB.sf_MATLABFunction_cn.sM,
                  rtB.sf_MATLABFunction_cn.t, rtb_theta[6 * p05_tmp_0 + 4],
                  rtB.sf_MATLABFunction_cn.oP, rtB.sf_MATLABFunction_cn.oV,
                  300.0, 180.0, &rtB.pos_l, &rtB.vel_h, &psi);

  // MATLAB Function: '<S11>/voltageConvert' incorporates:
  //   Constant: '<S11>/Constant'
  //   Constant: '<S11>/Constant1'

  voltageConvert(rtB.vel_h, 180.0, 12.0, &psi);

  // TransferFcn: '<S11>/trans func2'
  cy = 361.0 * rtX.transfunc2_CSTATE_j[1];

  // Sum: '<S12>/Sum14' incorporates:
  //   Integrator: '<S11>/Integrator'
  //   Sum: '<S11>/Sum14'
  //   Sum: '<S11>/Sum15'

  psi = ((rtB.pos_l - rtX.Integrator_CSTATE_k) + psi) - cy;

  // Gain: '<S260>/Filter Coefficient' incorporates:
  //   Gain: '<S251>/Derivative Gain'
  //   Integrator: '<S252>/Filter'
  //   Sum: '<S252>/SumD'

  rtB.FilterCoefficient_d = (0.327956120616846 * psi - rtX.Filter_CSTATE_m) *
    454.516416693375;

  // Sum: '<S266>/Sum' incorporates:
  //   Gain: '<S262>/Proportional Gain'
  //   Integrator: '<S257>/Integrator'

  rtB.Sum_m = (10.5857290910674 * psi + rtX.Integrator_CSTATE_ji) +
    rtB.FilterCoefficient_d;

  // Gain: '<S254>/Integral Gain'
  rtB.IntegralGain_g = 78.2339953359067 * psi;

  // MATLAB Function: '<S11>/velConvert' incorporates:
  //   Constant: '<S11>/Constant2'
  //   Constant: '<S11>/Constant3'

  velConvert(cy, 180.0, 12.0, &rtB.vel_hy);
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S18>/MATLAB Function' incorporates:
    //   Constant: '<S18>/Constant'
    //   Constant: '<S18>/Constant1'
    //   Constant: '<S18>/Constant2'
    //   Delay: '<S18>/Delay One Step2'
    //   Delay: '<S18>/Delay One Step3'
    //   MATLAB Function: '<S5>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 5], rtDW.DelayOneStep2_DSTATE_b,
                   rtDW.DelayOneStep3_DSTATE_k, 300.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_e, &rtDW.sf_MATLABFunction_e);
  }

  // MATLAB Function: '<S18>/MATLAB Function1' incorporates:
  //   Constant: '<S18>/Constant1'
  //   Constant: '<S18>/Constant2'
  //   MATLAB Function: '<S5>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_e.tB, rtB.sf_MATLABFunction_e.dB,
                  rtB.sf_MATLABFunction_e.tA, rtB.sf_MATLABFunction_e.dA,
                  rtB.sf_MATLABFunction_e.dCV, rtB.sf_MATLABFunction_e.tCV,
                  rtB.sf_MATLABFunction_e.s, rtB.sf_MATLABFunction_e.vT,
                  rtB.sf_MATLABFunction_e.tD, rtB.sf_MATLABFunction_e.sM,
                  rtB.sf_MATLABFunction_e.t, rtb_theta[6 * p05_tmp_0 + 5],
                  rtB.sf_MATLABFunction_e.oP, rtB.sf_MATLABFunction_e.oV, 300.0,
                  180.0, &rtB.pos, &rtB.vel, &psi);

  // MATLAB Function: '<S12>/voltageConvert' incorporates:
  //   Constant: '<S12>/Constant'
  //   Constant: '<S12>/Constant1'

  voltageConvert(rtB.vel, 180.0, 12.0, &psi);

  // TransferFcn: '<S12>/trans func2'
  cy = 361.0 * rtX.transfunc2_CSTATE_k[1];

  // Sum: '<S12>/Sum14' incorporates:
  //   Integrator: '<S12>/Integrator'
  //   Sum: '<S12>/Sum15'

  psi = ((rtB.pos - rtX.Integrator_CSTATE_gj) + psi) - cy;

  // Gain: '<S311>/Filter Coefficient' incorporates:
  //   Gain: '<S302>/Derivative Gain'
  //   Integrator: '<S303>/Filter'
  //   Sum: '<S303>/SumD'

  rtB.FilterCoefficient_b = (0.327956120616846 * psi - rtX.Filter_CSTATE_n) *
    454.516416693375;

  // Sum: '<S317>/Sum' incorporates:
  //   Gain: '<S313>/Proportional Gain'
  //   Integrator: '<S308>/Integrator'

  rtB.Sum_h = (10.5857290910674 * psi + rtX.Integrator_CSTATE_f) +
    rtB.FilterCoefficient_b;

  // Gain: '<S305>/Integral Gain'
  rtB.IntegralGain_m = 78.2339953359067 * psi;

  // MATLAB Function: '<S12>/velConvert' incorporates:
  //   Constant: '<S12>/Constant2'
  //   Constant: '<S12>/Constant3'

  velConvert(cy, 180.0, 12.0, &rtB.vel_p);

  // Outport: '<Root>/actual_theta_arr' incorporates:
  //   Integrator: '<S10>/Integrator'
  //   Integrator: '<S11>/Integrator'
  //   Integrator: '<S12>/Integrator'
  //   Integrator: '<S7>/Integrator'
  //   Integrator: '<S8>/Integrator'
  //   Integrator: '<S9>/Integrator'

  rtY.actual_theta_arr[0] = rtX.Integrator_CSTATE;
  rtY.actual_theta_arr[1] = rtX.Integrator_CSTATE_g;
  rtY.actual_theta_arr[2] = rtX.Integrator_CSTATE_o;
  rtY.actual_theta_arr[3] = rtX.Integrator_CSTATE_c;
  rtY.actual_theta_arr[4] = rtX.Integrator_CSTATE_k;
  rtY.actual_theta_arr[5] = rtX.Integrator_CSTATE_gj;
  if (rtmIsMajorTimeStep((&rtM))) {
    if (rtmIsMajorTimeStep((&rtM))) {
      // Update for Delay: '<S13>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE = rtB.pos_d;

      // Update for Delay: '<S13>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE = rtB.vel_c3;

      // Update for Delay: '<S14>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_i = rtB.pos_ms;

      // Update for Delay: '<S14>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_m = rtB.vel_c;

      // Update for Delay: '<S15>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_p = rtB.pos_n;

      // Update for Delay: '<S15>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_e = rtB.vel_i;

      // Update for Delay: '<S16>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_m = rtB.pos_m;

      // Update for Delay: '<S16>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_p = rtB.vel_j;

      // Update for Delay: '<S17>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_f = rtB.pos_l;

      // Update for Delay: '<S17>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_mr = rtB.vel_h;

      // Update for Delay: '<S18>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_b = rtB.pos;

      // Update for Delay: '<S18>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_k = rtB.vel;
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

  // Derivatives for Integrator: '<S7>/Integrator'
  _rtXdot->Integrator_CSTATE = rtB.vel_cp;

  // Derivatives for Integrator: '<S8>/Integrator'
  _rtXdot->Integrator_CSTATE_g = rtB.vel_k;

  // Derivatives for Integrator: '<S9>/Integrator'
  _rtXdot->Integrator_CSTATE_o = rtB.vel_ha;

  // Derivatives for Integrator: '<S10>/Integrator'
  _rtXdot->Integrator_CSTATE_c = rtB.vel_cx;

  // Derivatives for Integrator: '<S11>/Integrator'
  _rtXdot->Integrator_CSTATE_k = rtB.vel_hy;

  // Derivatives for Integrator: '<S12>/Integrator'
  _rtXdot->Integrator_CSTATE_gj = rtB.vel_p;

  // Derivatives for Integrator: '<S48>/Filter'
  _rtXdot->Filter_CSTATE = rtB.FilterCoefficient;

  // Derivatives for Integrator: '<S53>/Integrator'
  _rtXdot->Integrator_CSTATE_m = rtB.IntegralGain;

  // Derivatives for Integrator: '<S99>/Filter'
  _rtXdot->Filter_CSTATE_a = rtB.FilterCoefficient_c;

  // Derivatives for Integrator: '<S104>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtB.IntegralGain_f;

  // Derivatives for Integrator: '<S150>/Filter'
  _rtXdot->Filter_CSTATE_c = rtB.FilterCoefficient_cd;

  // Derivatives for Integrator: '<S155>/Integrator'
  _rtXdot->Integrator_CSTATE_a = rtB.IntegralGain_c;

  // Derivatives for Integrator: '<S201>/Filter'
  _rtXdot->Filter_CSTATE_f = rtB.FilterCoefficient_m;

  // Derivatives for Integrator: '<S206>/Integrator'
  _rtXdot->Integrator_CSTATE_an = rtB.IntegralGain_l;

  // Derivatives for Integrator: '<S252>/Filter'
  _rtXdot->Filter_CSTATE_m = rtB.FilterCoefficient_d;

  // Derivatives for Integrator: '<S257>/Integrator'
  _rtXdot->Integrator_CSTATE_ji = rtB.IntegralGain_g;

  // Derivatives for TransferFcn: '<S7>/trans func2'
  _rtXdot->transfunc2_CSTATE[0] = -3.098 * rtX.transfunc2_CSTATE[0];

  // Derivatives for TransferFcn: '<S8>/trans func2'
  _rtXdot->transfunc2_CSTATE_o[0] = -3.098 * rtX.transfunc2_CSTATE_o[0];

  // Derivatives for TransferFcn: '<S9>/trans func2'
  _rtXdot->transfunc2_CSTATE_ow[0] = -3.098 * rtX.transfunc2_CSTATE_ow[0];

  // Derivatives for TransferFcn: '<S10>/trans func2'
  _rtXdot->transfunc2_CSTATE_c[0] = -3.098 * rtX.transfunc2_CSTATE_c[0];

  // Derivatives for TransferFcn: '<S11>/trans func2'
  _rtXdot->transfunc2_CSTATE_j[0] = -3.098 * rtX.transfunc2_CSTATE_j[0];

  // Derivatives for TransferFcn: '<S12>/trans func2'
  _rtXdot->transfunc2_CSTATE_k[0] = -3.098 * rtX.transfunc2_CSTATE_k[0];

  // Derivatives for TransferFcn: '<S7>/trans func2'
  _rtXdot->transfunc2_CSTATE[0] += -56.11 * rtX.transfunc2_CSTATE[1];

  // Derivatives for TransferFcn: '<S8>/trans func2'
  _rtXdot->transfunc2_CSTATE_o[0] += -56.11 * rtX.transfunc2_CSTATE_o[1];

  // Derivatives for TransferFcn: '<S9>/trans func2'
  _rtXdot->transfunc2_CSTATE_ow[0] += -56.11 * rtX.transfunc2_CSTATE_ow[1];

  // Derivatives for TransferFcn: '<S10>/trans func2'
  _rtXdot->transfunc2_CSTATE_c[0] += -56.11 * rtX.transfunc2_CSTATE_c[1];

  // Derivatives for TransferFcn: '<S11>/trans func2'
  _rtXdot->transfunc2_CSTATE_j[0] += -56.11 * rtX.transfunc2_CSTATE_j[1];

  // Derivatives for TransferFcn: '<S12>/trans func2'
  _rtXdot->transfunc2_CSTATE_k[0] += -56.11 * rtX.transfunc2_CSTATE_k[1];

  // Derivatives for TransferFcn: '<S7>/trans func2'
  _rtXdot->transfunc2_CSTATE[1] = rtX.transfunc2_CSTATE[0];
  _rtXdot->transfunc2_CSTATE[0] += rtB.Sum;

  // Derivatives for TransferFcn: '<S8>/trans func2'
  _rtXdot->transfunc2_CSTATE_o[1] = rtX.transfunc2_CSTATE_o[0];
  _rtXdot->transfunc2_CSTATE_o[0] += rtB.Sum_b;

  // Derivatives for TransferFcn: '<S9>/trans func2'
  _rtXdot->transfunc2_CSTATE_ow[1] = rtX.transfunc2_CSTATE_ow[0];
  _rtXdot->transfunc2_CSTATE_ow[0] += rtB.Sum_k;

  // Derivatives for TransferFcn: '<S10>/trans func2'
  _rtXdot->transfunc2_CSTATE_c[1] = rtX.transfunc2_CSTATE_c[0];
  _rtXdot->transfunc2_CSTATE_c[0] += rtB.Sum_j;

  // Derivatives for TransferFcn: '<S11>/trans func2'
  _rtXdot->transfunc2_CSTATE_j[1] = rtX.transfunc2_CSTATE_j[0];
  _rtXdot->transfunc2_CSTATE_j[0] += rtB.Sum_m;

  // Derivatives for TransferFcn: '<S12>/trans func2'
  _rtXdot->transfunc2_CSTATE_k[1] = rtX.transfunc2_CSTATE_k[0];
  _rtXdot->transfunc2_CSTATE_k[0] += rtB.Sum_h;

  // Derivatives for Integrator: '<S303>/Filter'
  _rtXdot->Filter_CSTATE_n = rtB.FilterCoefficient_b;

  // Derivatives for Integrator: '<S308>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtB.IntegralGain_m;
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

  // InitializeConditions for Integrator: '<S7>/Integrator'
  rtX.Integrator_CSTATE = 0.0;

  // InitializeConditions for Integrator: '<S8>/Integrator'
  rtX.Integrator_CSTATE_g = 0.0;

  // InitializeConditions for Integrator: '<S9>/Integrator'
  rtX.Integrator_CSTATE_o = 0.0;

  // InitializeConditions for Integrator: '<S10>/Integrator'
  rtX.Integrator_CSTATE_c = 0.0;

  // InitializeConditions for Integrator: '<S11>/Integrator'
  rtX.Integrator_CSTATE_k = 0.0;

  // InitializeConditions for Integrator: '<S12>/Integrator'
  rtX.Integrator_CSTATE_gj = 0.0;

  // InitializeConditions for Integrator: '<S48>/Filter'
  rtX.Filter_CSTATE = 0.0;

  // InitializeConditions for Integrator: '<S53>/Integrator'
  rtX.Integrator_CSTATE_m = 0.0;

  // InitializeConditions for Integrator: '<S99>/Filter'
  rtX.Filter_CSTATE_a = 0.0;

  // InitializeConditions for Integrator: '<S104>/Integrator'
  rtX.Integrator_CSTATE_j = 0.0;

  // InitializeConditions for Integrator: '<S150>/Filter'
  rtX.Filter_CSTATE_c = 0.0;

  // InitializeConditions for Integrator: '<S155>/Integrator'
  rtX.Integrator_CSTATE_a = 0.0;

  // InitializeConditions for Integrator: '<S201>/Filter'
  rtX.Filter_CSTATE_f = 0.0;

  // InitializeConditions for Integrator: '<S206>/Integrator'
  rtX.Integrator_CSTATE_an = 0.0;

  // InitializeConditions for Integrator: '<S252>/Filter'
  rtX.Filter_CSTATE_m = 0.0;

  // InitializeConditions for Integrator: '<S257>/Integrator'
  rtX.Integrator_CSTATE_ji = 0.0;

  // InitializeConditions for TransferFcn: '<S7>/trans func2'
  rtX.transfunc2_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S8>/trans func2'
  rtX.transfunc2_CSTATE_o[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S9>/trans func2'
  rtX.transfunc2_CSTATE_ow[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S10>/trans func2'
  rtX.transfunc2_CSTATE_c[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S11>/trans func2'
  rtX.transfunc2_CSTATE_j[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S12>/trans func2'
  rtX.transfunc2_CSTATE_k[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S7>/trans func2'
  rtX.transfunc2_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S8>/trans func2'
  rtX.transfunc2_CSTATE_o[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S9>/trans func2'
  rtX.transfunc2_CSTATE_ow[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S10>/trans func2'
  rtX.transfunc2_CSTATE_c[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S11>/trans func2'
  rtX.transfunc2_CSTATE_j[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S12>/trans func2'
  rtX.transfunc2_CSTATE_k[1] = 0.0;

  // InitializeConditions for Integrator: '<S303>/Filter'
  rtX.Filter_CSTATE_n = 0.0;

  // InitializeConditions for Integrator: '<S308>/Integrator'
  rtX.Integrator_CSTATE_f = 0.0;
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
