//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: URController.cpp
//
// Code generated for Simulink model 'URController'.
//
// Model version                  : 1.222
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Fri Oct 25 19:41:48 2024
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
//    '<S11>/MATLAB Function'
//    '<S12>/MATLAB Function'
//    '<S13>/MATLAB Function'
//    '<S14>/MATLAB Function'
//    '<S15>/MATLAB Function'
//    '<S16>/MATLAB Function'
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
//    '<S11>/MATLAB Function1'
//    '<S12>/MATLAB Function1'
//    '<S13>/MATLAB Function1'
//    '<S14>/MATLAB Function1'
//    '<S15>/MATLAB Function1'
//    '<S16>/MATLAB Function1'
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

// Function for MATLAB Function: '<S3>/MATLAB Function'
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

// Function for MATLAB Function: '<S3>/MATLAB Function'
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
  real_T rtb_TmpSignalConversionAtSFunct[6];
  real_T p05[4];
  real_T a_1;
  real_T a_2;
  real_T phi;
  real_T psi;
  real_T rtb_TransferFcn10;
  real_T rtb_TransferFcn11;
  real_T rtb_TransferFcn12;
  real_T rtb_TransferFcn9;
  real_T s;
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

  // MATLAB Function: '<S3>/MATLAB Function1' incorporates:
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
  b_0[1] = 0.0;
  b_0[4] = psi;
  b_0[7] = -phi;
  b_0[2] = 0.0;
  b_0[5] = phi;
  b_0[8] = psi;
  tmp[0] = rtb_TransferFcn10;
  tmp[3] = 0.0;
  tmp[6] = rtb_TransferFcn9;
  rtb_gd[12] = rtU.desire_pos_orient_arr[0];
  b_0[0] = 1.0;
  tmp[1] = 0.0;
  rtb_gd[13] = rtU.desire_pos_orient_arr[1];
  b_0[3] = 0.0;
  tmp[4] = 1.0;
  rtb_gd[14] = rtU.desire_pos_orient_arr[2];
  b_0[6] = 0.0;
  tmp[7] = 0.0;
  tmp[2] = -rtb_TransferFcn9;
  tmp[5] = 0.0;
  tmp[8] = rtb_TransferFcn10;
  tmp_0[0] = rtb_TransferFcn12;
  tmp_0[3] = -rtb_TransferFcn11;
  tmp_0[6] = 0.0;
  tmp_0[1] = rtb_TransferFcn11;
  tmp_0[4] = rtb_TransferFcn12;
  tmp_0[7] = 0.0;
  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    psi = b_0[p05_tmp_0 + 3];
    phi = b_0[p05_tmp_0];
    rtb_TransferFcn9 = b_0[p05_tmp_0 + 6];
    for (b_tmp_0 = 0; b_tmp_0 < 3; b_tmp_0++) {
      b_1[p05_tmp_0 + 3 * b_tmp_0] = (tmp[3 * b_tmp_0 + 1] * psi + tmp[3 *
        b_tmp_0] * phi) + tmp[3 * b_tmp_0 + 2] * rtb_TransferFcn9;
    }

    tmp_0[3 * p05_tmp_0 + 2] = d[p05_tmp_0];
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 3; p05_tmp_0++) {
    phi = tmp_0[3 * p05_tmp_0 + 1];
    psi = tmp_0[3 * p05_tmp_0];
    rtb_TransferFcn9 = tmp_0[3 * p05_tmp_0 + 2];
    for (b_tmp_0 = 0; b_tmp_0 < 3; b_tmp_0++) {
      rtb_gd[b_tmp_0 + (p05_tmp_0 << 2)] = (b_1[b_tmp_0 + 3] * phi + psi *
        b_1[b_tmp_0]) + b_1[b_tmp_0 + 6] * rtb_TransferFcn9;
    }
  }

  // End of MATLAB Function: '<S3>/MATLAB Function1'

  // MATLAB Function: '<S3>/MATLAB Function'
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
    xpageoffset = i << 2;
    psi = rtb_theta[xpageoffset * 6];
    rtb_TransferFcn10 = std::sin(psi);
    phi = std::cos(psi);
    b[0] = phi;
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
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
      rtb_TransferFcn9 = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a[p05_tmp_0];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          b[c_a_tmp_2] * rtb_TransferFcn10) + b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      rtb_TransferFcn9 = c_a_0[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_0[p05_tmp_0];
      rtb_TransferFcn11 = c_a_0[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          b_b[c_a_tmp_2] * rtb_TransferFcn10) + b_b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + b_b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      rtb_TransferFcn9 = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          c_b[c_a_tmp_2] * rtb_TransferFcn10) + c_b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + c_b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }
    }

    inv(c_a_2, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      psi = a[p05_tmp_0];
      rtb_TransferFcn9 = a[p05_tmp_0 + 8];
      rtb_TransferFcn10 = a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_b[p05_tmp_0 + c_a_tmp_2] = ((rtb_gd[c_a_tmp_2 + 1] * phi +
          rtb_gd[c_a_tmp_2] * psi) + rtb_gd[c_a_tmp_2 + 2] * rtb_TransferFcn9) +
          rtb_gd[c_a_tmp_2 + 3] * rtb_TransferFcn10;
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
    rtb_TransferFcn10 = std::sin(psi);
    phi = std::cos(psi);
    b[0] = phi;
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
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
      rtb_TransferFcn9 = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a[p05_tmp_0];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          b[c_a_tmp_2] * rtb_TransferFcn10) + b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      rtb_TransferFcn9 = c_a_0[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_0[p05_tmp_0];
      rtb_TransferFcn11 = c_a_0[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          b_b[c_a_tmp_2] * rtb_TransferFcn10) + b_b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + b_b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      rtb_TransferFcn9 = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          c_b[c_a_tmp_2] * rtb_TransferFcn10) + c_b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + c_b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      psi = a[p05_tmp_0];
      rtb_TransferFcn9 = a[p05_tmp_0 + 8];
      rtb_TransferFcn10 = a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_tmp[p05_tmp_0 + c_a_tmp_2] = ((c_a_2[c_a_tmp_2 + 1] * phi +
          c_a_2[c_a_tmp_2] * psi) + c_a_2[c_a_tmp_2 + 2] * rtb_TransferFcn9) +
          c_a_2[c_a_tmp_2 + 3] * rtb_TransferFcn10;
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
    rtb_TransferFcn10 = std::sin(psi);
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
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
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
      rtb_TransferFcn9 = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a[p05_tmp_0];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          b[c_a_tmp_2] * rtb_TransferFcn10) + b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      rtb_TransferFcn9 = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          b_b[c_a_tmp_2] * rtb_TransferFcn10) + b_b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + b_b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      rtb_TransferFcn9 = c_a_0[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_0[p05_tmp_0];
      rtb_TransferFcn11 = c_a_0[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          c_b[c_a_tmp_2] * rtb_TransferFcn10) + c_b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + c_b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }
    }

    inv(c_a_2, c_a);
    psi = rtb_theta[xpageoffset + 5];
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
      b_tmp_0 = p05_tmp_0 << 2;
      c_b[b_tmp_0] = g[3 * p05_tmp_0];
      c_b[b_tmp_0 + 1] = g[3 * p05_tmp_0 + 1];
      c_b[b_tmp_0 + 2] = g[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      s = a[p05_tmp_0];
      a_1 = a[p05_tmp_0 + 8];
      a_2 = a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * phi + b[c_a_tmp_2] *
          s) + b[c_a_tmp_2 + 2] * a_1) + b[c_a_tmp_2 + 3] * a_2;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      s = c_a_2[p05_tmp_0];
      a_1 = c_a_2[p05_tmp_0 + 8];
      a_2 = c_a_2[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_0[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * phi + b_b[c_a_tmp_2]
          * s) + b_b[c_a_tmp_2 + 2] * a_1) + b_b[c_a_tmp_2 + 3] * a_2;
      }

      phi = a_0[p05_tmp_0 + 4];
      s = a_0[p05_tmp_0];
      a_1 = a_0[p05_tmp_0 + 8];
      a_2 = a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * phi +
          c_b[c_a_tmp_2] * s) + c_b[c_a_tmp_2 + 2] * a_1) + c_b[c_a_tmp_2 + 3] *
          a_2;
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
    rtb_TransferFcn9 = std::cos(psi);
    c_b[0] = rtb_TransferFcn9;
    c_b[4] = -phi;
    c_b[8] = 0.0;
    c_b[1] = phi;
    c_b[5] = rtb_TransferFcn9;
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
      s = a[p05_tmp_0];
      a_1 = a[p05_tmp_0 + 8];
      a_2 = a[p05_tmp_0 + 12];
      rtb_TransferFcn9 = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a[p05_tmp_0];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_tmp = p05_tmp_0 + c_a_tmp_2;
        c_a_2[a_tmp] = ((c_b[c_a_tmp_2 + 1] * phi + c_b[c_a_tmp_2] * s) +
                        c_b[c_a_tmp_2 + 2] * a_1) + c_b[c_a_tmp_2 + 3] * a_2;
        c_a_1[a_tmp] = ((rtb_gd[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
                         rtb_gd[c_a_tmp_2] * rtb_TransferFcn10) +
                        rtb_gd[c_a_tmp_2 + 2] * rtb_TransferFcn11) +
          rtb_gd[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      s = c_a_2[p05_tmp_0];
      a_1 = c_a_2[p05_tmp_0 + 8];
      a_2 = c_a_2[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_0[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * phi + b[c_a_tmp_2] * s)
          + b[c_a_tmp_2 + 2] * a_1) + b[c_a_tmp_2 + 3] * a_2;
      }

      phi = a_0[p05_tmp_0 + 4];
      s = a_0[p05_tmp_0];
      a_1 = a_0[p05_tmp_0 + 8];
      a_2 = a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((c_a_tmp[c_a_tmp_2 + 1] * phi +
          c_a_tmp[c_a_tmp_2] * s) + c_a_tmp[c_a_tmp_2 + 2] * a_1) +
          c_a_tmp[c_a_tmp_2 + 3] * a_2;
      }
    }

    inv(c_a_0, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      rtb_TransferFcn9 = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          b_b[c_a_tmp_2] * rtb_TransferFcn10) + b_b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + b_b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      phi = 0.0;
      rtb_TransferFcn9 = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a[p05_tmp_0];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        phi += (((a[c_a_tmp_2 + 1] * rtb_TransferFcn9 + a[c_a_tmp_2] *
                  rtb_TransferFcn10) + a[c_a_tmp_2 + 2] * rtb_TransferFcn11) +
                a[c_a_tmp_2 + 3] * rtb_TransferFcn12) * k[b_tmp_0];
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
    rtb_TransferFcn10 = std::sin(psi);
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
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
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
      rtb_TransferFcn9 = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a[p05_tmp_0];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          b[c_a_tmp_2] * rtb_TransferFcn10) + b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      rtb_TransferFcn9 = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          b_b[c_a_tmp_2] * rtb_TransferFcn10) + b_b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + b_b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      rtb_TransferFcn9 = c_a_0[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_0[p05_tmp_0];
      rtb_TransferFcn11 = c_a_0[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          c_b[c_a_tmp_2] * rtb_TransferFcn10) + c_b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + c_b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }
    }

    inv(c_a_2, c_a);
    rtb_TransferFcn11 = rtb_theta[6 * xpageoffset + 5];
    rtb_TransferFcn10 = std::sin(rtb_TransferFcn11);
    phi = std::cos(rtb_TransferFcn11);
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
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
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
      s = a[p05_tmp_0];
      a_1 = a[p05_tmp_0 + 8];
      a_2 = a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * phi + b[c_a_tmp_2] *
          s) + b[c_a_tmp_2 + 2] * a_1) + b[c_a_tmp_2 + 3] * a_2;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      s = c_a_2[p05_tmp_0];
      a_1 = c_a_2[p05_tmp_0 + 8];
      a_2 = c_a_2[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_0[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * phi + b_b[c_a_tmp_2]
          * s) + b_b[c_a_tmp_2 + 2] * a_1) + b_b[c_a_tmp_2 + 3] * a_2;
      }

      phi = a_0[p05_tmp_0 + 4];
      s = a_0[p05_tmp_0];
      a_1 = a_0[p05_tmp_0 + 8];
      a_2 = a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * phi +
          c_b[c_a_tmp_2] * s) + c_b[c_a_tmp_2 + 2] * a_1) + c_b[c_a_tmp_2 + 3] *
          a_2;
      }
    }

    inv(c_a_0, b_b);
    rtb_TransferFcn11 = rtb_theta[6 * xpageoffset + 4];
    phi = std::sin(rtb_TransferFcn11);
    rtb_TransferFcn9 = std::cos(rtb_TransferFcn11);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      c_a_tmp_1 = c_a_tmp_0[p05_tmp_0];
      a[p05_tmp_0] = c_a_tmp_1;
      b[p05_tmp_0] = c_a_tmp_1;
      c_b[p05_tmp_0] = c_a_tmp_1;
      c_a_tmp[p05_tmp_0] = c_a_tmp_1;
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
      c_a_tmp_2 = p05_tmp_0 << 2;
      c_a_tmp[c_a_tmp_2] = h[3 * p05_tmp_0];
      c_a_tmp[c_a_tmp_2 + 1] = h[3 * p05_tmp_0 + 1];
      c_a_tmp[c_a_tmp_2 + 2] = h[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      phi = a[p05_tmp_0 + 4];
      s = a[p05_tmp_0];
      a_1 = a[p05_tmp_0 + 8];
      a_2 = a[p05_tmp_0 + 12];
      rtb_TransferFcn9 = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a[p05_tmp_0];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_tmp = p05_tmp_0 + c_a_tmp_2;
        c_a_2[a_tmp] = ((c_b[c_a_tmp_2 + 1] * phi + c_b[c_a_tmp_2] * s) +
                        c_b[c_a_tmp_2 + 2] * a_1) + c_b[c_a_tmp_2 + 3] * a_2;
        c_a_1[a_tmp] = ((rtb_gd[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
                         rtb_gd[c_a_tmp_2] * rtb_TransferFcn10) +
                        rtb_gd[c_a_tmp_2 + 2] * rtb_TransferFcn11) +
          rtb_gd[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      s = c_a_2[p05_tmp_0];
      a_1 = c_a_2[p05_tmp_0 + 8];
      a_2 = c_a_2[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_0[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * phi + b[c_a_tmp_2] * s)
          + b[c_a_tmp_2 + 2] * a_1) + b[c_a_tmp_2 + 3] * a_2;
      }

      phi = a_0[p05_tmp_0 + 4];
      s = a_0[p05_tmp_0];
      a_1 = a_0[p05_tmp_0 + 8];
      a_2 = a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((c_a_tmp[c_a_tmp_2 + 1] * phi +
          c_a_tmp[c_a_tmp_2] * s) + c_a_tmp[c_a_tmp_2 + 2] * a_1) +
          c_a_tmp[c_a_tmp_2 + 3] * a_2;
      }
    }

    inv(c_a_0, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      rtb_TransferFcn9 = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          b_b[c_a_tmp_2] * rtb_TransferFcn10) + b_b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + b_b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      phi = 0.0;
      rtb_TransferFcn9 = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a[p05_tmp_0];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        i = b_tmp_0 << 2;
        s = ((a[i + 1] * rtb_TransferFcn9 + a[i] * rtb_TransferFcn10) + a[i + 2]
             * rtb_TransferFcn11) + a[i + 3] * rtb_TransferFcn12;
        T14[p05_tmp_0 + i] = s;
        phi += s * k[b_tmp_0];
      }

      p05[p05_tmp_0] = phi - static_cast<real_T>(p05_tmp[p05_tmp_0]);
    }

    rtb_TransferFcn11 = rtb_theta[6 * xpageoffset + 2];
    rtb_TransferFcn9 = std::sin(rtb_TransferFcn11);
    phi = std::asin(-0.392 * rtb_TransferFcn9 / norm(p05)) - std::atan2(p05[1],
      -p05[0]);
    rtb_theta[6 * xpageoffset + 1] = phi;
    rtb_TransferFcn10 = std::cos(rtb_TransferFcn11);
    for (p05_tmp_0 = 0; p05_tmp_0 < 16; p05_tmp_0++) {
      c_a_tmp_1 = c_a_tmp_0[p05_tmp_0];
      c_a[p05_tmp_0] = c_a_tmp_1;
      b_b[p05_tmp_0] = c_a_tmp_1;
      b[p05_tmp_0] = c_a_tmp_1;
      c_b[p05_tmp_0] = c_a_tmp_1;
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
      b_tmp_0 = p05_tmp_0 << 2;
      c_b[b_tmp_0] = c_b_tmp[3 * p05_tmp_0];
      c_b[b_tmp_0 + 1] = c_b_tmp[3 * p05_tmp_0 + 1];
      c_b[b_tmp_0 + 2] = c_b_tmp[3 * p05_tmp_0 + 2];
    }

    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      rtb_TransferFcn9 = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a[p05_tmp_0];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          b[c_a_tmp_2] * rtb_TransferFcn10) + b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      rtb_TransferFcn9 = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          b_b[c_a_tmp_2] * rtb_TransferFcn10) + b_b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + b_b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      rtb_TransferFcn9 = c_a_0[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_0[p05_tmp_0];
      rtb_TransferFcn11 = c_a_0[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          c_b[c_a_tmp_2] * rtb_TransferFcn10) + c_b[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + c_b[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }
    }

    inv(c_a_2, c_a);
    rtb_TransferFcn10 = std::sin(phi);
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
    b[4] = -rtb_TransferFcn10;
    b[8] = 0.0;
    b[1] = rtb_TransferFcn10;
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
      s = a[p05_tmp_0];
      a_1 = a[p05_tmp_0 + 8];
      a_2 = a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_2[p05_tmp_0 + c_a_tmp_2] = ((b[c_a_tmp_2 + 1] * phi + b[c_a_tmp_2] *
          s) + b[c_a_tmp_2 + 2] * a_1) + b[c_a_tmp_2 + 3] * a_2;
      }

      phi = c_a_2[p05_tmp_0 + 4];
      s = c_a_2[p05_tmp_0];
      a_1 = c_a_2[p05_tmp_0 + 8];
      a_2 = c_a_2[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        a_0[p05_tmp_0 + c_a_tmp_2] = ((b_b[c_a_tmp_2 + 1] * phi + b_b[c_a_tmp_2]
          * s) + b_b[c_a_tmp_2 + 2] * a_1) + b_b[c_a_tmp_2 + 3] * a_2;
      }

      phi = a_0[p05_tmp_0 + 4];
      s = a_0[p05_tmp_0];
      a_1 = a_0[p05_tmp_0 + 8];
      a_2 = a_0[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_0[p05_tmp_0 + c_a_tmp_2] = ((c_b[c_a_tmp_2 + 1] * phi +
          c_b[c_a_tmp_2] * s) + c_b[c_a_tmp_2 + 2] * a_1) + c_b[c_a_tmp_2 + 3] *
          a_2;
      }
    }

    inv(c_a_0, a);
    for (p05_tmp_0 = 0; p05_tmp_0 < 4; p05_tmp_0++) {
      rtb_TransferFcn9 = c_a[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a[p05_tmp_0];
      rtb_TransferFcn11 = c_a[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_1[p05_tmp_0 + c_a_tmp_2] = ((a[c_a_tmp_2 + 1] * rtb_TransferFcn9 +
          a[c_a_tmp_2] * rtb_TransferFcn10) + a[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + a[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }

      rtb_TransferFcn9 = c_a_1[p05_tmp_0 + 4];
      rtb_TransferFcn10 = c_a_1[p05_tmp_0];
      rtb_TransferFcn11 = c_a_1[p05_tmp_0 + 8];
      rtb_TransferFcn12 = c_a_1[p05_tmp_0 + 12];
      for (b_tmp_0 = 0; b_tmp_0 < 4; b_tmp_0++) {
        c_a_tmp_2 = b_tmp_0 << 2;
        c_a_tmp[p05_tmp_0 + c_a_tmp_2] = ((T14[c_a_tmp_2 + 1] * rtb_TransferFcn9
          + T14[c_a_tmp_2] * rtb_TransferFcn10) + T14[c_a_tmp_2 + 2] *
          rtb_TransferFcn11) + T14[c_a_tmp_2 + 3] * rtb_TransferFcn12;
      }
    }

    rtb_theta[6 * xpageoffset + 3] = std::atan2(c_a_tmp[1], c_a_tmp[0]);
    rtb_theta[6 * xpageoffset] = psi - 3.1415926535897931;
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 8; p05_tmp_0++) {
    for (b_tmp_0 = 0; b_tmp_0 < 6; b_tmp_0++) {
      xpageoffset = 6 * p05_tmp_0 + b_tmp_0;
      psi = rtb_theta[xpageoffset];
      if (psi <= -3.1415926535897931) {
        rtb_theta[xpageoffset] = psi + 6.2831853071795862;
      } else if (psi > 3.1415926535897931) {
        rtb_theta[xpageoffset] = psi - 6.2831853071795862;
      }
    }
  }

  // End of MATLAB Function: '<S3>/MATLAB Function'

  // TransferFcn: '<S2>/Transfer Fcn7'
  psi = (6.0 * rtX.TransferFcn7_CSTATE[1] + rtX.TransferFcn7_CSTATE[0]) + 10.0 *
    rtX.TransferFcn7_CSTATE[2];

  // TransferFcn: '<S2>/Transfer Fcn8'
  phi = (6.0 * rtX.TransferFcn8_CSTATE[1] + rtX.TransferFcn8_CSTATE[0]) + 10.0 *
    rtX.TransferFcn8_CSTATE[2];

  // TransferFcn: '<S2>/Transfer Fcn9'
  rtb_TransferFcn9 = (6.0 * rtX.TransferFcn9_CSTATE[1] +
                      rtX.TransferFcn9_CSTATE[0]) + 10.0 *
    rtX.TransferFcn9_CSTATE[2];

  // TransferFcn: '<S2>/Transfer Fcn10'
  rtb_TransferFcn10 = (6.0 * rtX.TransferFcn10_CSTATE[1] +
                       rtX.TransferFcn10_CSTATE[0]) + 10.0 *
    rtX.TransferFcn10_CSTATE[2];

  // TransferFcn: '<S2>/Transfer Fcn11'
  rtb_TransferFcn11 = (6.0 * rtX.TransferFcn11_CSTATE[1] +
                       rtX.TransferFcn11_CSTATE[0]) + 10.0 *
    rtX.TransferFcn11_CSTATE[2];

  // TransferFcn: '<S2>/Transfer Fcn12'
  rtb_TransferFcn12 = (6.0 * rtX.TransferFcn12_CSTATE[1] +
                       rtX.TransferFcn12_CSTATE[0]) + 10.0 *
    rtX.TransferFcn12_CSTATE[2];

  // SignalConversion generated from: '<S4>/ SFunction ' incorporates:
  //   MATLAB Function: '<S1>/isInitialized'

  rtb_TmpSignalConversionAtSFunct[0] = psi;
  rtb_TmpSignalConversionAtSFunct[1] = phi;
  rtb_TmpSignalConversionAtSFunct[2] = rtb_TransferFcn9;
  rtb_TmpSignalConversionAtSFunct[3] = rtb_TransferFcn10;
  rtb_TmpSignalConversionAtSFunct[4] = rtb_TransferFcn11;
  rtb_TmpSignalConversionAtSFunct[5] = rtb_TransferFcn12;

  // MATLAB Function: '<S1>/isInitialized' incorporates:
  //   SignalConversion generated from: '<S4>/ SFunction '

  s = psi;
  for (p05_tmp_0 = 0; p05_tmp_0 < 5; p05_tmp_0++) {
    s += rtb_TmpSignalConversionAtSFunct[p05_tmp_0 + 1];
  }

  if (s == 0.0) {
    // Switch: '<S1>/Switch' incorporates:
    //   Inport: '<Root>/ori_theta_arr'

    rtb_TmpSignalConversionAtSFunct[0] = rtU.ori_theta_arr[0];
    rtb_TmpSignalConversionAtSFunct[1] = rtU.ori_theta_arr[1];
    rtb_TmpSignalConversionAtSFunct[2] = rtU.ori_theta_arr[2];
    rtb_TmpSignalConversionAtSFunct[3] = rtU.ori_theta_arr[3];
    rtb_TmpSignalConversionAtSFunct[4] = rtU.ori_theta_arr[4];
    rtb_TmpSignalConversionAtSFunct[5] = rtU.ori_theta_arr[5];
  } else {
    // Switch: '<S1>/Switch'
    rtb_TmpSignalConversionAtSFunct[0] = psi;
    rtb_TmpSignalConversionAtSFunct[1] = phi;
    rtb_TmpSignalConversionAtSFunct[2] = rtb_TransferFcn9;
    rtb_TmpSignalConversionAtSFunct[3] = rtb_TransferFcn10;
    rtb_TmpSignalConversionAtSFunct[4] = rtb_TransferFcn11;
    rtb_TmpSignalConversionAtSFunct[5] = rtb_TransferFcn12;
  }

  // MATLAB Function: '<S3>/MATLAB Function2'
  for (p05_tmp_0 = 0; p05_tmp_0 < 8; p05_tmp_0++) {
    for (b_tmp_0 = 0; b_tmp_0 < 6; b_tmp_0++) {
      xpageoffset = 6 * p05_tmp_0 + b_tmp_0;
      x[xpageoffset] = rtb_theta[xpageoffset] -
        rtb_TmpSignalConversionAtSFunct[b_tmp_0];
    }
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 48; p05_tmp_0++) {
    y[p05_tmp_0] = std::abs(x[p05_tmp_0]);
  }

  for (p05_tmp_0 = 0; p05_tmp_0 < 8; p05_tmp_0++) {
    xpageoffset = p05_tmp_0 * 6;
    s = y[xpageoffset];
    for (b_tmp_0 = 0; b_tmp_0 < 5; b_tmp_0++) {
      s += y[(xpageoffset + b_tmp_0) + 1];
    }

    varargin_1[p05_tmp_0] = s;
  }

  a_1 = varargin_1[0];
  p05_tmp_0 = 0;
  for (xpageoffset = 0; xpageoffset < 7; xpageoffset++) {
    s = varargin_1[xpageoffset + 1];
    if (a_1 > s) {
      a_1 = s;
      p05_tmp_0 = xpageoffset + 1;
    }
  }

  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S11>/MATLAB Function' incorporates:
    //   Constant: '<S11>/Constant'
    //   Constant: '<S11>/Constant1'
    //   Constant: '<S11>/Constant2'
    //   Delay: '<S11>/Delay One Step2'
    //   Delay: '<S11>/Delay One Step3'
    //   MATLAB Function: '<S3>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0], rtDW.DelayOneStep2_DSTATE,
                   rtDW.DelayOneStep3_DSTATE, 100.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction, &rtDW.sf_MATLABFunction);
  }

  // MATLAB Function: '<S11>/MATLAB Function1' incorporates:
  //   Constant: '<S11>/Constant1'
  //   Constant: '<S11>/Constant2'
  //   MATLAB Function: '<S3>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction.tB, rtB.sf_MATLABFunction.dB,
                  rtB.sf_MATLABFunction.tA, rtB.sf_MATLABFunction.dA,
                  rtB.sf_MATLABFunction.dCV, rtB.sf_MATLABFunction.tCV,
                  rtB.sf_MATLABFunction.s, rtB.sf_MATLABFunction.vT,
                  rtB.sf_MATLABFunction.tD, rtB.sf_MATLABFunction.sM,
                  rtB.sf_MATLABFunction.t, rtb_theta[6 * p05_tmp_0],
                  rtB.sf_MATLABFunction.oP, rtB.sf_MATLABFunction.oV, 100.0,
                  180.0, &rtB.pos_i, &rtB.vel_j2, &s);

  // Sum: '<S2>/Sum13'
  s = rtB.pos_i - psi;

  // Gain: '<S147>/Filter Coefficient' incorporates:
  //   Gain: '<S138>/Derivative Gain'
  //   Integrator: '<S139>/Filter'
  //   Sum: '<S139>/SumD'

  rtB.FilterCoefficient = (-0.0900818829328251 * s - rtX.Filter_CSTATE) *
    186.823463181414;

  // Sum: '<S153>/Sum' incorporates:
  //   Gain: '<S149>/Proportional Gain'
  //   Integrator: '<S144>/Integrator'

  rtB.Sum = (16.8294093394131 * s + rtX.Integrator_CSTATE) +
    rtB.FilterCoefficient;

  // Gain: '<S141>/Integral Gain'
  rtB.IntegralGain = 84.3967388731047 * s;
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S12>/MATLAB Function' incorporates:
    //   Constant: '<S12>/Constant'
    //   Constant: '<S12>/Constant1'
    //   Constant: '<S12>/Constant2'
    //   Delay: '<S12>/Delay One Step2'
    //   Delay: '<S12>/Delay One Step3'
    //   MATLAB Function: '<S3>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 1], rtDW.DelayOneStep2_DSTATE_e,
                   rtDW.DelayOneStep3_DSTATE_h, 100.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_m, &rtDW.sf_MATLABFunction_m);
  }

  // MATLAB Function: '<S12>/MATLAB Function1' incorporates:
  //   Constant: '<S12>/Constant1'
  //   Constant: '<S12>/Constant2'
  //   MATLAB Function: '<S3>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_m.tB, rtB.sf_MATLABFunction_m.dB,
                  rtB.sf_MATLABFunction_m.tA, rtB.sf_MATLABFunction_m.dA,
                  rtB.sf_MATLABFunction_m.dCV, rtB.sf_MATLABFunction_m.tCV,
                  rtB.sf_MATLABFunction_m.s, rtB.sf_MATLABFunction_m.vT,
                  rtB.sf_MATLABFunction_m.tD, rtB.sf_MATLABFunction_m.sM,
                  rtB.sf_MATLABFunction_m.t, rtb_theta[6 * p05_tmp_0 + 1],
                  rtB.sf_MATLABFunction_m.oP, rtB.sf_MATLABFunction_m.oV, 100.0,
                  180.0, &rtB.pos_g, &rtB.vel_j, &s);

  // Sum: '<S2>/Sum7'
  s = rtB.pos_g - phi;

  // Gain: '<S195>/Filter Coefficient' incorporates:
  //   Gain: '<S186>/Derivative Gain'
  //   Integrator: '<S187>/Filter'
  //   Sum: '<S187>/SumD'

  rtB.FilterCoefficient_l = (-0.0900818829328251 * s - rtX.Filter_CSTATE_k) *
    186.823463181414;

  // Sum: '<S201>/Sum' incorporates:
  //   Gain: '<S197>/Proportional Gain'
  //   Integrator: '<S192>/Integrator'

  rtB.Sum_d = (16.8294093394131 * s + rtX.Integrator_CSTATE_d) +
    rtB.FilterCoefficient_l;

  // Gain: '<S189>/Integral Gain'
  rtB.IntegralGain_o = 84.3967388731047 * s;
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S13>/MATLAB Function' incorporates:
    //   Constant: '<S13>/Constant'
    //   Constant: '<S13>/Constant1'
    //   Constant: '<S13>/Constant2'
    //   Delay: '<S13>/Delay One Step2'
    //   Delay: '<S13>/Delay One Step3'
    //   MATLAB Function: '<S3>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 2], rtDW.DelayOneStep2_DSTATE_p,
                   rtDW.DelayOneStep3_DSTATE_i, 100.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_n, &rtDW.sf_MATLABFunction_n);
  }

  // MATLAB Function: '<S13>/MATLAB Function1' incorporates:
  //   Constant: '<S13>/Constant1'
  //   Constant: '<S13>/Constant2'
  //   MATLAB Function: '<S3>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_n.tB, rtB.sf_MATLABFunction_n.dB,
                  rtB.sf_MATLABFunction_n.tA, rtB.sf_MATLABFunction_n.dA,
                  rtB.sf_MATLABFunction_n.dCV, rtB.sf_MATLABFunction_n.tCV,
                  rtB.sf_MATLABFunction_n.s, rtB.sf_MATLABFunction_n.vT,
                  rtB.sf_MATLABFunction_n.tD, rtB.sf_MATLABFunction_n.sM,
                  rtB.sf_MATLABFunction_n.t, rtb_theta[6 * p05_tmp_0 + 2],
                  rtB.sf_MATLABFunction_n.oP, rtB.sf_MATLABFunction_n.oV, 100.0,
                  180.0, &rtB.pos_a5, &rtB.vel_i, &s);

  // Sum: '<S2>/Sum8'
  s = rtB.pos_a5 - rtb_TransferFcn9;

  // Gain: '<S243>/Filter Coefficient' incorporates:
  //   Gain: '<S234>/Derivative Gain'
  //   Integrator: '<S235>/Filter'
  //   Sum: '<S235>/SumD'

  rtB.FilterCoefficient_f = (-0.0900818829328251 * s - rtX.Filter_CSTATE_j) *
    186.823463181414;

  // Sum: '<S249>/Sum' incorporates:
  //   Gain: '<S245>/Proportional Gain'
  //   Integrator: '<S240>/Integrator'

  rtB.Sum_f = (16.8294093394131 * s + rtX.Integrator_CSTATE_f) +
    rtB.FilterCoefficient_f;

  // Gain: '<S237>/Integral Gain'
  rtB.IntegralGain_n = 84.3967388731047 * s;
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S14>/MATLAB Function' incorporates:
    //   Constant: '<S14>/Constant'
    //   Constant: '<S14>/Constant1'
    //   Constant: '<S14>/Constant2'
    //   Delay: '<S14>/Delay One Step2'
    //   Delay: '<S14>/Delay One Step3'
    //   MATLAB Function: '<S3>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 3], rtDW.DelayOneStep2_DSTATE_f,
                   rtDW.DelayOneStep3_DSTATE_l, 100.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_f, &rtDW.sf_MATLABFunction_f);
  }

  // MATLAB Function: '<S14>/MATLAB Function1' incorporates:
  //   Constant: '<S14>/Constant1'
  //   Constant: '<S14>/Constant2'
  //   MATLAB Function: '<S3>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_f.tB, rtB.sf_MATLABFunction_f.dB,
                  rtB.sf_MATLABFunction_f.tA, rtB.sf_MATLABFunction_f.dA,
                  rtB.sf_MATLABFunction_f.dCV, rtB.sf_MATLABFunction_f.tCV,
                  rtB.sf_MATLABFunction_f.s, rtB.sf_MATLABFunction_f.vT,
                  rtB.sf_MATLABFunction_f.tD, rtB.sf_MATLABFunction_f.sM,
                  rtB.sf_MATLABFunction_f.t, rtb_theta[6 * p05_tmp_0 + 3],
                  rtB.sf_MATLABFunction_f.oP, rtB.sf_MATLABFunction_f.oV, 100.0,
                  180.0, &rtB.pos_h, &rtB.vel_es, &s);

  // Sum: '<S2>/Sum9'
  s = rtB.pos_h - rtb_TransferFcn10;

  // Gain: '<S291>/Filter Coefficient' incorporates:
  //   Gain: '<S282>/Derivative Gain'
  //   Integrator: '<S283>/Filter'
  //   Sum: '<S283>/SumD'

  rtB.FilterCoefficient_fr = (-0.0900818829328251 * s - rtX.Filter_CSTATE_c) *
    186.823463181414;

  // Sum: '<S297>/Sum' incorporates:
  //   Gain: '<S293>/Proportional Gain'
  //   Integrator: '<S288>/Integrator'

  rtB.Sum_h = (16.8294093394131 * s + rtX.Integrator_CSTATE_g) +
    rtB.FilterCoefficient_fr;

  // Gain: '<S285>/Integral Gain'
  rtB.IntegralGain_a = 84.3967388731047 * s;
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S15>/MATLAB Function' incorporates:
    //   Constant: '<S15>/Constant'
    //   Constant: '<S15>/Constant1'
    //   Constant: '<S15>/Constant2'
    //   Delay: '<S15>/Delay One Step2'
    //   Delay: '<S15>/Delay One Step3'
    //   MATLAB Function: '<S3>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 4], rtDW.DelayOneStep2_DSTATE_i,
                   rtDW.DelayOneStep3_DSTATE_f, 100.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_e, &rtDW.sf_MATLABFunction_e);
  }

  // MATLAB Function: '<S15>/MATLAB Function1' incorporates:
  //   Constant: '<S15>/Constant1'
  //   Constant: '<S15>/Constant2'
  //   MATLAB Function: '<S3>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_e.tB, rtB.sf_MATLABFunction_e.dB,
                  rtB.sf_MATLABFunction_e.tA, rtB.sf_MATLABFunction_e.dA,
                  rtB.sf_MATLABFunction_e.dCV, rtB.sf_MATLABFunction_e.tCV,
                  rtB.sf_MATLABFunction_e.s, rtB.sf_MATLABFunction_e.vT,
                  rtB.sf_MATLABFunction_e.tD, rtB.sf_MATLABFunction_e.sM,
                  rtB.sf_MATLABFunction_e.t, rtb_theta[6 * p05_tmp_0 + 4],
                  rtB.sf_MATLABFunction_e.oP, rtB.sf_MATLABFunction_e.oV, 100.0,
                  180.0, &rtB.pos_a, &rtB.vel_e, &s);

  // Sum: '<S2>/Sum10'
  s = rtB.pos_a - rtb_TransferFcn11;

  // Gain: '<S51>/Filter Coefficient' incorporates:
  //   Gain: '<S42>/Derivative Gain'
  //   Integrator: '<S43>/Filter'
  //   Sum: '<S43>/SumD'

  rtB.FilterCoefficient_b = (-0.0900818829328251 * s - rtX.Filter_CSTATE_d) *
    186.823463181414;

  // Sum: '<S57>/Sum' incorporates:
  //   Gain: '<S53>/Proportional Gain'
  //   Integrator: '<S48>/Integrator'

  rtB.Sum_n = (16.8294093394131 * s + rtX.Integrator_CSTATE_di) +
    rtB.FilterCoefficient_b;

  // Gain: '<S45>/Integral Gain'
  rtB.IntegralGain_os = 84.3967388731047 * s;
  if (rtmIsMajorTimeStep((&rtM))) {
    // MATLAB Function: '<S16>/MATLAB Function' incorporates:
    //   Constant: '<S16>/Constant'
    //   Constant: '<S16>/Constant1'
    //   Constant: '<S16>/Constant2'
    //   Delay: '<S16>/Delay One Step2'
    //   Delay: '<S16>/Delay One Step3'
    //   MATLAB Function: '<S3>/MATLAB Function2'

    MATLABFunction(rtb_theta[6 * p05_tmp_0 + 5], rtDW.DelayOneStep2_DSTATE_em,
                   rtDW.DelayOneStep3_DSTATE_fz, 100.0, 180.0, 0.001,
                   &rtB.sf_MATLABFunction_i, &rtDW.sf_MATLABFunction_i);
  }

  // MATLAB Function: '<S16>/MATLAB Function1' incorporates:
  //   Constant: '<S16>/Constant1'
  //   Constant: '<S16>/Constant2'
  //   MATLAB Function: '<S3>/MATLAB Function2'

  MATLABFunction1(rtB.sf_MATLABFunction_i.tB, rtB.sf_MATLABFunction_i.dB,
                  rtB.sf_MATLABFunction_i.tA, rtB.sf_MATLABFunction_i.dA,
                  rtB.sf_MATLABFunction_i.dCV, rtB.sf_MATLABFunction_i.tCV,
                  rtB.sf_MATLABFunction_i.s, rtB.sf_MATLABFunction_i.vT,
                  rtB.sf_MATLABFunction_i.tD, rtB.sf_MATLABFunction_i.sM,
                  rtB.sf_MATLABFunction_i.t, rtb_theta[6 * p05_tmp_0 + 5],
                  rtB.sf_MATLABFunction_i.oP, rtB.sf_MATLABFunction_i.oV, 100.0,
                  180.0, &rtB.pos, &rtB.vel, &s);

  // Sum: '<S2>/Sum11'
  s = rtB.pos - rtb_TransferFcn12;

  // Gain: '<S99>/Filter Coefficient' incorporates:
  //   Gain: '<S90>/Derivative Gain'
  //   Integrator: '<S91>/Filter'
  //   Sum: '<S91>/SumD'

  rtB.FilterCoefficient_g = (-0.0900818829328251 * s - rtX.Filter_CSTATE_i) *
    186.823463181414;

  // Sum: '<S105>/Sum' incorporates:
  //   Gain: '<S101>/Proportional Gain'
  //   Integrator: '<S96>/Integrator'

  rtB.Sum_o = (16.8294093394131 * s + rtX.Integrator_CSTATE_o) +
    rtB.FilterCoefficient_g;

  // Gain: '<S93>/Integral Gain'
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
      // Update for Delay: '<S11>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE = rtB.pos_i;

      // Update for Delay: '<S11>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE = rtB.vel_j2;

      // Update for Delay: '<S12>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_e = rtB.pos_g;

      // Update for Delay: '<S12>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_h = rtB.vel_j;

      // Update for Delay: '<S13>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_p = rtB.pos_a5;

      // Update for Delay: '<S13>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_i = rtB.vel_i;

      // Update for Delay: '<S14>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_f = rtB.pos_h;

      // Update for Delay: '<S14>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_l = rtB.vel_es;

      // Update for Delay: '<S15>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_i = rtB.pos_a;

      // Update for Delay: '<S15>/Delay One Step3'
      rtDW.DelayOneStep3_DSTATE_f = rtB.vel_e;

      // Update for Delay: '<S16>/Delay One Step2'
      rtDW.DelayOneStep2_DSTATE_em = rtB.pos;

      // Update for Delay: '<S16>/Delay One Step3'
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

  // Derivatives for TransferFcn: '<S2>/Transfer Fcn7'
  _rtXdot->TransferFcn7_CSTATE[0] = -7.0 * rtX.TransferFcn7_CSTATE[1];
  _rtXdot->TransferFcn7_CSTATE[0] -= rtX.TransferFcn7_CSTATE[2];
  _rtXdot->TransferFcn7_CSTATE[1] = rtX.TransferFcn7_CSTATE[0];
  _rtXdot->TransferFcn7_CSTATE[2] = rtX.TransferFcn7_CSTATE[1];
  _rtXdot->TransferFcn7_CSTATE[0] += rtB.Sum;

  // Derivatives for TransferFcn: '<S2>/Transfer Fcn8'
  _rtXdot->TransferFcn8_CSTATE[0] = -7.0 * rtX.TransferFcn8_CSTATE[1];
  _rtXdot->TransferFcn8_CSTATE[0] -= rtX.TransferFcn8_CSTATE[2];
  _rtXdot->TransferFcn8_CSTATE[1] = rtX.TransferFcn8_CSTATE[0];
  _rtXdot->TransferFcn8_CSTATE[2] = rtX.TransferFcn8_CSTATE[1];
  _rtXdot->TransferFcn8_CSTATE[0] += rtB.Sum_d;

  // Derivatives for TransferFcn: '<S2>/Transfer Fcn9'
  _rtXdot->TransferFcn9_CSTATE[0] = -7.0 * rtX.TransferFcn9_CSTATE[1];
  _rtXdot->TransferFcn9_CSTATE[0] -= rtX.TransferFcn9_CSTATE[2];
  _rtXdot->TransferFcn9_CSTATE[1] = rtX.TransferFcn9_CSTATE[0];
  _rtXdot->TransferFcn9_CSTATE[2] = rtX.TransferFcn9_CSTATE[1];
  _rtXdot->TransferFcn9_CSTATE[0] += rtB.Sum_f;

  // Derivatives for TransferFcn: '<S2>/Transfer Fcn10'
  _rtXdot->TransferFcn10_CSTATE[0] = -7.0 * rtX.TransferFcn10_CSTATE[1];
  _rtXdot->TransferFcn10_CSTATE[0] -= rtX.TransferFcn10_CSTATE[2];
  _rtXdot->TransferFcn10_CSTATE[1] = rtX.TransferFcn10_CSTATE[0];
  _rtXdot->TransferFcn10_CSTATE[2] = rtX.TransferFcn10_CSTATE[1];
  _rtXdot->TransferFcn10_CSTATE[0] += rtB.Sum_h;

  // Derivatives for TransferFcn: '<S2>/Transfer Fcn11'
  _rtXdot->TransferFcn11_CSTATE[0] = -7.0 * rtX.TransferFcn11_CSTATE[1];
  _rtXdot->TransferFcn11_CSTATE[0] -= rtX.TransferFcn11_CSTATE[2];
  _rtXdot->TransferFcn11_CSTATE[1] = rtX.TransferFcn11_CSTATE[0];
  _rtXdot->TransferFcn11_CSTATE[2] = rtX.TransferFcn11_CSTATE[1];
  _rtXdot->TransferFcn11_CSTATE[0] += rtB.Sum_n;

  // Derivatives for TransferFcn: '<S2>/Transfer Fcn12'
  _rtXdot->TransferFcn12_CSTATE[0] = -7.0 * rtX.TransferFcn12_CSTATE[1];
  _rtXdot->TransferFcn12_CSTATE[0] -= rtX.TransferFcn12_CSTATE[2];
  _rtXdot->TransferFcn12_CSTATE[1] = rtX.TransferFcn12_CSTATE[0];
  _rtXdot->TransferFcn12_CSTATE[2] = rtX.TransferFcn12_CSTATE[1];
  _rtXdot->TransferFcn12_CSTATE[0] += rtB.Sum_o;

  // Derivatives for Integrator: '<S139>/Filter'
  _rtXdot->Filter_CSTATE = rtB.FilterCoefficient;

  // Derivatives for Integrator: '<S144>/Integrator'
  _rtXdot->Integrator_CSTATE = rtB.IntegralGain;

  // Derivatives for Integrator: '<S187>/Filter'
  _rtXdot->Filter_CSTATE_k = rtB.FilterCoefficient_l;

  // Derivatives for Integrator: '<S192>/Integrator'
  _rtXdot->Integrator_CSTATE_d = rtB.IntegralGain_o;

  // Derivatives for Integrator: '<S235>/Filter'
  _rtXdot->Filter_CSTATE_j = rtB.FilterCoefficient_f;

  // Derivatives for Integrator: '<S240>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtB.IntegralGain_n;

  // Derivatives for Integrator: '<S283>/Filter'
  _rtXdot->Filter_CSTATE_c = rtB.FilterCoefficient_fr;

  // Derivatives for Integrator: '<S288>/Integrator'
  _rtXdot->Integrator_CSTATE_g = rtB.IntegralGain_a;

  // Derivatives for Integrator: '<S43>/Filter'
  _rtXdot->Filter_CSTATE_d = rtB.FilterCoefficient_b;

  // Derivatives for Integrator: '<S48>/Integrator'
  _rtXdot->Integrator_CSTATE_di = rtB.IntegralGain_os;

  // Derivatives for Integrator: '<S91>/Filter'
  _rtXdot->Filter_CSTATE_i = rtB.FilterCoefficient_g;

  // Derivatives for Integrator: '<S96>/Integrator'
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

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn7'
  rtX.TransferFcn7_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn8'
  rtX.TransferFcn8_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn9'
  rtX.TransferFcn9_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn10'
  rtX.TransferFcn10_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn11'
  rtX.TransferFcn11_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn12'
  rtX.TransferFcn12_CSTATE[0] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn7'
  rtX.TransferFcn7_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn8'
  rtX.TransferFcn8_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn9'
  rtX.TransferFcn9_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn10'
  rtX.TransferFcn10_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn11'
  rtX.TransferFcn11_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn12'
  rtX.TransferFcn12_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn7'
  rtX.TransferFcn7_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn8'
  rtX.TransferFcn8_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn9'
  rtX.TransferFcn9_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn10'
  rtX.TransferFcn10_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn11'
  rtX.TransferFcn11_CSTATE[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn12'
  rtX.TransferFcn12_CSTATE[2] = 0.0;

  // InitializeConditions for Integrator: '<S139>/Filter'
  rtX.Filter_CSTATE = 0.0;

  // InitializeConditions for Integrator: '<S144>/Integrator'
  rtX.Integrator_CSTATE = 0.0;

  // InitializeConditions for Integrator: '<S187>/Filter'
  rtX.Filter_CSTATE_k = 0.0;

  // InitializeConditions for Integrator: '<S192>/Integrator'
  rtX.Integrator_CSTATE_d = 0.0;

  // InitializeConditions for Integrator: '<S235>/Filter'
  rtX.Filter_CSTATE_j = 0.0;

  // InitializeConditions for Integrator: '<S240>/Integrator'
  rtX.Integrator_CSTATE_f = 0.0;

  // InitializeConditions for Integrator: '<S283>/Filter'
  rtX.Filter_CSTATE_c = 0.0;

  // InitializeConditions for Integrator: '<S288>/Integrator'
  rtX.Integrator_CSTATE_g = 0.0;

  // InitializeConditions for Integrator: '<S43>/Filter'
  rtX.Filter_CSTATE_d = 0.0;

  // InitializeConditions for Integrator: '<S48>/Integrator'
  rtX.Integrator_CSTATE_di = 0.0;

  // InitializeConditions for Integrator: '<S91>/Filter'
  rtX.Filter_CSTATE_i = 0.0;

  // InitializeConditions for Integrator: '<S96>/Integrator'
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
