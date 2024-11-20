//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: URController.h
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
#ifndef RTW_HEADER_URController_h_
#define RTW_HEADER_URController_h_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "URController_types.h"
#include <cstring>

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef ODE4_INTG
#define ODE4_INTG

// ODE4 Integration Data
struct ODE4_IntgData {
  real_T *y;                           // output
  real_T *f[4];                        // derivatives
};

#endif

// Class declaration for model URController
class URController final
{
  // public data and function members
 public:
  // Block signals for system '<S13>/MATLAB Function'
  struct B_MATLABFunction {
    real_T tB;                         // '<S13>/MATLAB Function'
    real_T dB;                         // '<S13>/MATLAB Function'
    real_T tA;                         // '<S13>/MATLAB Function'
    real_T dA;                         // '<S13>/MATLAB Function'
    real_T dCV;                        // '<S13>/MATLAB Function'
    real_T tCV;                        // '<S13>/MATLAB Function'
    real_T s;                          // '<S13>/MATLAB Function'
    real_T vT;                         // '<S13>/MATLAB Function'
    real_T tD;                         // '<S13>/MATLAB Function'
    real_T sM;                         // '<S13>/MATLAB Function'
    real_T t;                          // '<S13>/MATLAB Function'
    real_T oP;                         // '<S13>/MATLAB Function'
    real_T oV;                         // '<S13>/MATLAB Function'
  };

  // Block states (default storage) for system '<S13>/MATLAB Function'
  struct DW_MATLABFunction {
    real_T timeBrake;                  // '<S13>/MATLAB Function'
    real_T distanceBrake;              // '<S13>/MATLAB Function'
    real_T timeAccelerate;             // '<S13>/MATLAB Function'
    real_T distanceAccelerate;         // '<S13>/MATLAB Function'
    real_T distanceConstVelocity;      // '<S13>/MATLAB Function'
    real_T timeConstVelocity;          // '<S13>/MATLAB Function'
    real_T timeDecelerate;             // '<S13>/MATLAB Function'
    real_T shape;                      // '<S13>/MATLAB Function'
    real_T velTop;                     // '<S13>/MATLAB Function'
    real_T signM;                      // '<S13>/MATLAB Function'
    real_T oldPoseRef;                 // '<S13>/MATLAB Function'
    real_T oldPos;                     // '<S13>/MATLAB Function'
    real_T oldVel;                     // '<S13>/MATLAB Function'
    real_T time;                       // '<S13>/MATLAB Function'
    boolean_T timeBrake_not_empty;     // '<S13>/MATLAB Function'
    boolean_T distanceBrake_not_empty; // '<S13>/MATLAB Function'
    boolean_T timeAccelerate_not_empty;// '<S13>/MATLAB Function'
    boolean_T distanceAccelerate_not_empty;// '<S13>/MATLAB Function'
    boolean_T distanceConstVelocity_not_empty;// '<S13>/MATLAB Function'
    boolean_T timeConstVelocity_not_empty;// '<S13>/MATLAB Function'
    boolean_T timeDecelerate_not_empty;// '<S13>/MATLAB Function'
    boolean_T shape_not_empty;         // '<S13>/MATLAB Function'
    boolean_T velTop_not_empty;        // '<S13>/MATLAB Function'
    boolean_T signM_not_empty;         // '<S13>/MATLAB Function'
    boolean_T oldPoseRef_not_empty;    // '<S13>/MATLAB Function'
    boolean_T oldPos_not_empty;        // '<S13>/MATLAB Function'
    boolean_T oldVel_not_empty;        // '<S13>/MATLAB Function'
    boolean_T time_not_empty;          // '<S13>/MATLAB Function'
  };

  // Block signals (default storage)
  struct B {
    real_T FilterCoefficient;          // '<S56>/Filter Coefficient'
    real_T Sum;                        // '<S62>/Sum'
    real_T IntegralGain;               // '<S50>/Integral Gain'
    real_T FilterCoefficient_c;        // '<S107>/Filter Coefficient'
    real_T Sum_b;                      // '<S113>/Sum'
    real_T IntegralGain_f;             // '<S101>/Integral Gain'
    real_T FilterCoefficient_cd;       // '<S158>/Filter Coefficient'
    real_T Sum_k;                      // '<S164>/Sum'
    real_T IntegralGain_c;             // '<S152>/Integral Gain'
    real_T FilterCoefficient_m;        // '<S209>/Filter Coefficient'
    real_T Sum_j;                      // '<S215>/Sum'
    real_T IntegralGain_l;             // '<S203>/Integral Gain'
    real_T FilterCoefficient_d;        // '<S260>/Filter Coefficient'
    real_T Sum_m;                      // '<S266>/Sum'
    real_T IntegralGain_g;             // '<S254>/Integral Gain'
    real_T FilterCoefficient_b;        // '<S311>/Filter Coefficient'
    real_T Sum_h;                      // '<S317>/Sum'
    real_T IntegralGain_m;             // '<S305>/Integral Gain'
    real_T pos;                        // '<S18>/MATLAB Function1'
    real_T vel;                        // '<S18>/MATLAB Function1'
    real_T pos_l;                      // '<S17>/MATLAB Function1'
    real_T vel_h;                      // '<S17>/MATLAB Function1'
    real_T pos_m;                      // '<S16>/MATLAB Function1'
    real_T vel_j;                      // '<S16>/MATLAB Function1'
    real_T pos_n;                      // '<S15>/MATLAB Function1'
    real_T vel_i;                      // '<S15>/MATLAB Function1'
    real_T pos_ms;                     // '<S14>/MATLAB Function1'
    real_T vel_c;                      // '<S14>/MATLAB Function1'
    real_T pos_d;                      // '<S13>/MATLAB Function1'
    real_T vel_c3;                     // '<S13>/MATLAB Function1'
    real_T vel_p;                      // '<S12>/velConvert'
    real_T vel_hy;                     // '<S11>/velConvert'
    real_T vel_cx;                     // '<S10>/velConvert'
    real_T vel_ha;                     // '<S9>/velConvert'
    real_T vel_k;                      // '<S8>/velConvert'
    real_T vel_cp;                     // '<S7>/velConvert'
    B_MATLABFunction sf_MATLABFunction_e;// '<S18>/MATLAB Function'
    B_MATLABFunction sf_MATLABFunction_cn;// '<S17>/MATLAB Function'
    B_MATLABFunction sf_MATLABFunction_ow;// '<S16>/MATLAB Function'
    B_MATLABFunction sf_MATLABFunction_c;// '<S15>/MATLAB Function'
    B_MATLABFunction sf_MATLABFunction_o;// '<S14>/MATLAB Function'
    B_MATLABFunction sf_MATLABFunction_j;// '<S13>/MATLAB Function'
  };

  // Block states (default storage) for system '<Root>'
  struct DW {
    real_T DelayOneStep2_DSTATE;       // '<S13>/Delay One Step2'
    real_T DelayOneStep3_DSTATE;       // '<S13>/Delay One Step3'
    real_T DelayOneStep2_DSTATE_i;     // '<S14>/Delay One Step2'
    real_T DelayOneStep3_DSTATE_m;     // '<S14>/Delay One Step3'
    real_T DelayOneStep2_DSTATE_p;     // '<S15>/Delay One Step2'
    real_T DelayOneStep3_DSTATE_e;     // '<S15>/Delay One Step3'
    real_T DelayOneStep2_DSTATE_m;     // '<S16>/Delay One Step2'
    real_T DelayOneStep3_DSTATE_p;     // '<S16>/Delay One Step3'
    real_T DelayOneStep2_DSTATE_f;     // '<S17>/Delay One Step2'
    real_T DelayOneStep3_DSTATE_mr;    // '<S17>/Delay One Step3'
    real_T DelayOneStep2_DSTATE_b;     // '<S18>/Delay One Step2'
    real_T DelayOneStep3_DSTATE_k;     // '<S18>/Delay One Step3'
    DW_MATLABFunction sf_MATLABFunction_e;// '<S18>/MATLAB Function'
    DW_MATLABFunction sf_MATLABFunction_cn;// '<S17>/MATLAB Function'
    DW_MATLABFunction sf_MATLABFunction_ow;// '<S16>/MATLAB Function'
    DW_MATLABFunction sf_MATLABFunction_c;// '<S15>/MATLAB Function'
    DW_MATLABFunction sf_MATLABFunction_o;// '<S14>/MATLAB Function'
    DW_MATLABFunction sf_MATLABFunction_j;// '<S13>/MATLAB Function'
  };

  // Continuous states (default storage)
  struct X {
    real_T Integrator_CSTATE;          // '<S7>/Integrator'
    real_T Integrator_CSTATE_g;        // '<S8>/Integrator'
    real_T Integrator_CSTATE_o;        // '<S9>/Integrator'
    real_T Integrator_CSTATE_c;        // '<S10>/Integrator'
    real_T Integrator_CSTATE_k;        // '<S11>/Integrator'
    real_T Integrator_CSTATE_gj;       // '<S12>/Integrator'
    real_T transfunc2_CSTATE[2];       // '<S7>/trans func2'
    real_T Filter_CSTATE;              // '<S48>/Filter'
    real_T Integrator_CSTATE_m;        // '<S53>/Integrator'
    real_T transfunc2_CSTATE_o[2];     // '<S8>/trans func2'
    real_T Filter_CSTATE_a;            // '<S99>/Filter'
    real_T Integrator_CSTATE_j;        // '<S104>/Integrator'
    real_T transfunc2_CSTATE_ow[2];    // '<S9>/trans func2'
    real_T Filter_CSTATE_c;            // '<S150>/Filter'
    real_T Integrator_CSTATE_a;        // '<S155>/Integrator'
    real_T transfunc2_CSTATE_c[2];     // '<S10>/trans func2'
    real_T Filter_CSTATE_f;            // '<S201>/Filter'
    real_T Integrator_CSTATE_an;       // '<S206>/Integrator'
    real_T transfunc2_CSTATE_j[2];     // '<S11>/trans func2'
    real_T Filter_CSTATE_m;            // '<S252>/Filter'
    real_T Integrator_CSTATE_ji;       // '<S257>/Integrator'
    real_T transfunc2_CSTATE_k[2];     // '<S12>/trans func2'
    real_T Filter_CSTATE_n;            // '<S303>/Filter'
    real_T Integrator_CSTATE_f;        // '<S308>/Integrator'
  };

  // State derivatives (default storage)
  struct XDot {
    real_T Integrator_CSTATE;          // '<S7>/Integrator'
    real_T Integrator_CSTATE_g;        // '<S8>/Integrator'
    real_T Integrator_CSTATE_o;        // '<S9>/Integrator'
    real_T Integrator_CSTATE_c;        // '<S10>/Integrator'
    real_T Integrator_CSTATE_k;        // '<S11>/Integrator'
    real_T Integrator_CSTATE_gj;       // '<S12>/Integrator'
    real_T transfunc2_CSTATE[2];       // '<S7>/trans func2'
    real_T Filter_CSTATE;              // '<S48>/Filter'
    real_T Integrator_CSTATE_m;        // '<S53>/Integrator'
    real_T transfunc2_CSTATE_o[2];     // '<S8>/trans func2'
    real_T Filter_CSTATE_a;            // '<S99>/Filter'
    real_T Integrator_CSTATE_j;        // '<S104>/Integrator'
    real_T transfunc2_CSTATE_ow[2];    // '<S9>/trans func2'
    real_T Filter_CSTATE_c;            // '<S150>/Filter'
    real_T Integrator_CSTATE_a;        // '<S155>/Integrator'
    real_T transfunc2_CSTATE_c[2];     // '<S10>/trans func2'
    real_T Filter_CSTATE_f;            // '<S201>/Filter'
    real_T Integrator_CSTATE_an;       // '<S206>/Integrator'
    real_T transfunc2_CSTATE_j[2];     // '<S11>/trans func2'
    real_T Filter_CSTATE_m;            // '<S252>/Filter'
    real_T Integrator_CSTATE_ji;       // '<S257>/Integrator'
    real_T transfunc2_CSTATE_k[2];     // '<S12>/trans func2'
    real_T Filter_CSTATE_n;            // '<S303>/Filter'
    real_T Integrator_CSTATE_f;        // '<S308>/Integrator'
  };

  // State disabled
  struct XDis {
    boolean_T Integrator_CSTATE;       // '<S7>/Integrator'
    boolean_T Integrator_CSTATE_g;     // '<S8>/Integrator'
    boolean_T Integrator_CSTATE_o;     // '<S9>/Integrator'
    boolean_T Integrator_CSTATE_c;     // '<S10>/Integrator'
    boolean_T Integrator_CSTATE_k;     // '<S11>/Integrator'
    boolean_T Integrator_CSTATE_gj;    // '<S12>/Integrator'
    boolean_T transfunc2_CSTATE[2];    // '<S7>/trans func2'
    boolean_T Filter_CSTATE;           // '<S48>/Filter'
    boolean_T Integrator_CSTATE_m;     // '<S53>/Integrator'
    boolean_T transfunc2_CSTATE_o[2];  // '<S8>/trans func2'
    boolean_T Filter_CSTATE_a;         // '<S99>/Filter'
    boolean_T Integrator_CSTATE_j;     // '<S104>/Integrator'
    boolean_T transfunc2_CSTATE_ow[2]; // '<S9>/trans func2'
    boolean_T Filter_CSTATE_c;         // '<S150>/Filter'
    boolean_T Integrator_CSTATE_a;     // '<S155>/Integrator'
    boolean_T transfunc2_CSTATE_c[2];  // '<S10>/trans func2'
    boolean_T Filter_CSTATE_f;         // '<S201>/Filter'
    boolean_T Integrator_CSTATE_an;    // '<S206>/Integrator'
    boolean_T transfunc2_CSTATE_j[2];  // '<S11>/trans func2'
    boolean_T Filter_CSTATE_m;         // '<S252>/Filter'
    boolean_T Integrator_CSTATE_ji;    // '<S257>/Integrator'
    boolean_T transfunc2_CSTATE_k[2];  // '<S12>/trans func2'
    boolean_T Filter_CSTATE_n;         // '<S303>/Filter'
    boolean_T Integrator_CSTATE_f;     // '<S308>/Integrator'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T ori_theta_arr[6];           // '<Root>/ori_theta_arr'
    real_T desire_pos_orient_arr[6];   // '<Root>/desire_pos_orient_arr'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T actual_theta_arr[6];        // '<Root>/actual_theta_arr'
    real_T pos_arr[3];                 // '<Root>/pos_arr'
    real_T ori_arr[3];                 // '<Root>/ori_arr'
  };

  // Real-time Model Data Structure
  struct RT_MODEL {
    const char_T *errorStatus;
    RTWSolverInfo solverInfo;
    X *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    XDis *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T CTOutputIncnstWithState;
    real_T odeY[30];
    real_T odeF[4][30];
    ODE4_IntgData intgData;

    //
    //  Sizes:
    //  The following substructure contains sizes information
    //  for many of the model attributes such as inputs, outputs,
    //  dwork, sample times, etc.

    struct {
      int_T numContStates;
      int_T numPeriodicContStates;
      int_T numSampTimes;
    } Sizes;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      uint32_T clockTick0;
      time_T stepSize0;
      uint32_T clockTick1;
      SimTimeStep simTimeStep;
      boolean_T stopRequestedFlag;
      time_T *t;
      time_T tArray[2];
    } Timing;
  };

  // Copy Constructor
  URController(URController const&) = delete;

  // Assignment Operator
  URController& operator= (URController const&) & = delete;

  // Move Constructor
  URController(URController &&) = delete;

  // Move Assignment Operator
  URController& operator= (URController &&) = delete;

  // Real-Time Model get method
  URController::RT_MODEL * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU *pExtU)
  {
    rtU = *pExtU;
  }

  // Root outports get method
  const ExtY &getExternalOutputs() const
  {
    return rtY;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  URController();

  // Destructor
  ~URController();

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // private data and function members
 private:

  // Block signals
  B rtB;

  // Block states
  DW rtDW;

  // Block continuous states
  X rtX;

  // private member function(s) for subsystem '<S7>/velConvert'
  static void velConvert(real_T rtu_vol, real_T rtu_maxVel, real_T rtu_maxVol,
    real_T *rty_vel);

  // private member function(s) for subsystem '<S7>/voltageConvert'
  static void voltageConvert(real_T rtu_vel, real_T rtu_maxVel, real_T
    rtu_maxVol, real_T *rty_voltage);

  // private member function(s) for subsystem '<S13>/MATLAB Function'
  static void MATLABFunction(real_T rtu_posRef, real_T rtu_pos, real_T rtu_vel,
    real_T rtu_maxAcc, real_T rtu_maxVel, real_T rtu_CYCLE_FREQ,
    B_MATLABFunction *localB, DW_MATLABFunction *localDW);

  // private member function(s) for subsystem '<S13>/MATLAB Function1'
  static void MATLABFunction1(real_T rtu_timeBrake, real_T rtu_distanceBrake,
    real_T rtu_timeAccelerate, real_T rtu_distanceAccelerate, real_T
    rtu_distanceConstVelocity, real_T rtu_timeConstVelocity, real_T rtu_shape,
    real_T rtu_velTop, real_T rtu_timeDecelerate, real_T rtu_signM, real_T
    rtu_deltaTime, real_T rtu_posRef, real_T rtu_oldPos, real_T rtu_oldVel,
    real_T rtu_maxAcc, real_T rtu_maxVel, real_T *rty_pos, real_T *rty_vel,
    real_T *rty_acc);

  // private member function(s) for subsystem '<Root>'
  void inv(const real_T x[16], real_T y[16]);
  real_T norm(const real_T x[4]);
  void expand_atan2(const real_T a_data[], const int32_T a_size[3], const real_T
                    b_data[], const int32_T b_size[3], real_T c_data[], int32_T
                    c_size[3]);

  // Continuous states update member function
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  // Derivatives member function
  void URController_derivatives();

  // Real-Time Model
  RT_MODEL rtM;
};

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'URController'
//  '<S1>'   : 'URController/MATLAB Function'
//  '<S2>'   : 'URController/MainControl'
//  '<S3>'   : 'URController/forwardkinematics1'
//  '<S4>'   : 'URController/MainControl/Control System'
//  '<S5>'   : 'URController/MainControl/Kinematic calculator'
//  '<S6>'   : 'URController/MainControl/isInitialized'
//  '<S7>'   : 'URController/MainControl/Control System/DC motor system1'
//  '<S8>'   : 'URController/MainControl/Control System/DC motor system2'
//  '<S9>'   : 'URController/MainControl/Control System/DC motor system3'
//  '<S10>'  : 'URController/MainControl/Control System/DC motor system4'
//  '<S11>'  : 'URController/MainControl/Control System/DC motor system5'
//  '<S12>'  : 'URController/MainControl/Control System/DC motor system6'
//  '<S13>'  : 'URController/MainControl/Control System/motionGenerator1'
//  '<S14>'  : 'URController/MainControl/Control System/motionGenerator2'
//  '<S15>'  : 'URController/MainControl/Control System/motionGenerator3'
//  '<S16>'  : 'URController/MainControl/Control System/motionGenerator4'
//  '<S17>'  : 'URController/MainControl/Control System/motionGenerator5'
//  '<S18>'  : 'URController/MainControl/Control System/motionGenerator7'
//  '<S19>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14'
//  '<S20>'  : 'URController/MainControl/Control System/DC motor system1/velConvert'
//  '<S21>'  : 'URController/MainControl/Control System/DC motor system1/voltageConvert'
//  '<S22>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Anti-windup'
//  '<S23>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/D Gain'
//  '<S24>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Filter'
//  '<S25>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Filter ICs'
//  '<S26>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/I Gain'
//  '<S27>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Ideal P Gain'
//  '<S28>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Ideal P Gain Fdbk'
//  '<S29>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Integrator'
//  '<S30>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Integrator ICs'
//  '<S31>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/N Copy'
//  '<S32>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/N Gain'
//  '<S33>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/P Copy'
//  '<S34>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Parallel P Gain'
//  '<S35>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Reset Signal'
//  '<S36>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Saturation'
//  '<S37>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Saturation Fdbk'
//  '<S38>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Sum'
//  '<S39>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Sum Fdbk'
//  '<S40>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Tracking Mode'
//  '<S41>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Tracking Mode Sum'
//  '<S42>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Tsamp - Integral'
//  '<S43>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Tsamp - Ngain'
//  '<S44>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/postSat Signal'
//  '<S45>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/preSat Signal'
//  '<S46>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Anti-windup/Passthrough'
//  '<S47>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/D Gain/Internal Parameters'
//  '<S48>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Filter/Cont. Filter'
//  '<S49>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Filter ICs/Internal IC - Filter'
//  '<S50>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/I Gain/Internal Parameters'
//  '<S51>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Ideal P Gain/Passthrough'
//  '<S52>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Ideal P Gain Fdbk/Disabled'
//  '<S53>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Integrator/Continuous'
//  '<S54>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Integrator ICs/Internal IC'
//  '<S55>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/N Copy/Disabled'
//  '<S56>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/N Gain/Internal Parameters'
//  '<S57>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/P Copy/Disabled'
//  '<S58>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Parallel P Gain/Internal Parameters'
//  '<S59>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Reset Signal/Disabled'
//  '<S60>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Saturation/Passthrough'
//  '<S61>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Saturation Fdbk/Disabled'
//  '<S62>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Sum/Sum_PID'
//  '<S63>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Sum Fdbk/Disabled'
//  '<S64>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Tracking Mode/Disabled'
//  '<S65>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Tracking Mode Sum/Passthrough'
//  '<S66>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Tsamp - Integral/TsSignalSpecification'
//  '<S67>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/Tsamp - Ngain/Passthrough'
//  '<S68>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/postSat Signal/Forward_Path'
//  '<S69>'  : 'URController/MainControl/Control System/DC motor system1/PID Controller14/preSat Signal/Forward_Path'
//  '<S70>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14'
//  '<S71>'  : 'URController/MainControl/Control System/DC motor system2/velConvert'
//  '<S72>'  : 'URController/MainControl/Control System/DC motor system2/voltageConvert'
//  '<S73>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Anti-windup'
//  '<S74>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/D Gain'
//  '<S75>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Filter'
//  '<S76>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Filter ICs'
//  '<S77>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/I Gain'
//  '<S78>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Ideal P Gain'
//  '<S79>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Ideal P Gain Fdbk'
//  '<S80>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Integrator'
//  '<S81>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Integrator ICs'
//  '<S82>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/N Copy'
//  '<S83>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/N Gain'
//  '<S84>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/P Copy'
//  '<S85>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Parallel P Gain'
//  '<S86>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Reset Signal'
//  '<S87>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Saturation'
//  '<S88>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Saturation Fdbk'
//  '<S89>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Sum'
//  '<S90>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Sum Fdbk'
//  '<S91>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Tracking Mode'
//  '<S92>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Tracking Mode Sum'
//  '<S93>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Tsamp - Integral'
//  '<S94>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Tsamp - Ngain'
//  '<S95>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/postSat Signal'
//  '<S96>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/preSat Signal'
//  '<S97>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Anti-windup/Passthrough'
//  '<S98>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/D Gain/Internal Parameters'
//  '<S99>'  : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Filter/Cont. Filter'
//  '<S100>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Filter ICs/Internal IC - Filter'
//  '<S101>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/I Gain/Internal Parameters'
//  '<S102>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Ideal P Gain/Passthrough'
//  '<S103>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Ideal P Gain Fdbk/Disabled'
//  '<S104>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Integrator/Continuous'
//  '<S105>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Integrator ICs/Internal IC'
//  '<S106>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/N Copy/Disabled'
//  '<S107>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/N Gain/Internal Parameters'
//  '<S108>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/P Copy/Disabled'
//  '<S109>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Parallel P Gain/Internal Parameters'
//  '<S110>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Reset Signal/Disabled'
//  '<S111>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Saturation/Passthrough'
//  '<S112>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Saturation Fdbk/Disabled'
//  '<S113>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Sum/Sum_PID'
//  '<S114>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Sum Fdbk/Disabled'
//  '<S115>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Tracking Mode/Disabled'
//  '<S116>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Tracking Mode Sum/Passthrough'
//  '<S117>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Tsamp - Integral/TsSignalSpecification'
//  '<S118>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/Tsamp - Ngain/Passthrough'
//  '<S119>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/postSat Signal/Forward_Path'
//  '<S120>' : 'URController/MainControl/Control System/DC motor system2/PID Controller14/preSat Signal/Forward_Path'
//  '<S121>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14'
//  '<S122>' : 'URController/MainControl/Control System/DC motor system3/velConvert'
//  '<S123>' : 'URController/MainControl/Control System/DC motor system3/voltageConvert'
//  '<S124>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Anti-windup'
//  '<S125>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/D Gain'
//  '<S126>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Filter'
//  '<S127>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Filter ICs'
//  '<S128>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/I Gain'
//  '<S129>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Ideal P Gain'
//  '<S130>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Ideal P Gain Fdbk'
//  '<S131>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Integrator'
//  '<S132>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Integrator ICs'
//  '<S133>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/N Copy'
//  '<S134>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/N Gain'
//  '<S135>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/P Copy'
//  '<S136>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Parallel P Gain'
//  '<S137>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Reset Signal'
//  '<S138>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Saturation'
//  '<S139>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Saturation Fdbk'
//  '<S140>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Sum'
//  '<S141>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Sum Fdbk'
//  '<S142>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Tracking Mode'
//  '<S143>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Tracking Mode Sum'
//  '<S144>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Tsamp - Integral'
//  '<S145>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Tsamp - Ngain'
//  '<S146>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/postSat Signal'
//  '<S147>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/preSat Signal'
//  '<S148>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Anti-windup/Passthrough'
//  '<S149>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/D Gain/Internal Parameters'
//  '<S150>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Filter/Cont. Filter'
//  '<S151>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Filter ICs/Internal IC - Filter'
//  '<S152>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/I Gain/Internal Parameters'
//  '<S153>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Ideal P Gain/Passthrough'
//  '<S154>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Ideal P Gain Fdbk/Disabled'
//  '<S155>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Integrator/Continuous'
//  '<S156>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Integrator ICs/Internal IC'
//  '<S157>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/N Copy/Disabled'
//  '<S158>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/N Gain/Internal Parameters'
//  '<S159>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/P Copy/Disabled'
//  '<S160>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Parallel P Gain/Internal Parameters'
//  '<S161>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Reset Signal/Disabled'
//  '<S162>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Saturation/Passthrough'
//  '<S163>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Saturation Fdbk/Disabled'
//  '<S164>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Sum/Sum_PID'
//  '<S165>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Sum Fdbk/Disabled'
//  '<S166>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Tracking Mode/Disabled'
//  '<S167>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Tracking Mode Sum/Passthrough'
//  '<S168>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Tsamp - Integral/TsSignalSpecification'
//  '<S169>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/Tsamp - Ngain/Passthrough'
//  '<S170>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/postSat Signal/Forward_Path'
//  '<S171>' : 'URController/MainControl/Control System/DC motor system3/PID Controller14/preSat Signal/Forward_Path'
//  '<S172>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14'
//  '<S173>' : 'URController/MainControl/Control System/DC motor system4/velConvert'
//  '<S174>' : 'URController/MainControl/Control System/DC motor system4/voltageConvert'
//  '<S175>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Anti-windup'
//  '<S176>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/D Gain'
//  '<S177>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Filter'
//  '<S178>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Filter ICs'
//  '<S179>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/I Gain'
//  '<S180>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Ideal P Gain'
//  '<S181>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Ideal P Gain Fdbk'
//  '<S182>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Integrator'
//  '<S183>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Integrator ICs'
//  '<S184>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/N Copy'
//  '<S185>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/N Gain'
//  '<S186>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/P Copy'
//  '<S187>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Parallel P Gain'
//  '<S188>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Reset Signal'
//  '<S189>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Saturation'
//  '<S190>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Saturation Fdbk'
//  '<S191>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Sum'
//  '<S192>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Sum Fdbk'
//  '<S193>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Tracking Mode'
//  '<S194>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Tracking Mode Sum'
//  '<S195>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Tsamp - Integral'
//  '<S196>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Tsamp - Ngain'
//  '<S197>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/postSat Signal'
//  '<S198>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/preSat Signal'
//  '<S199>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Anti-windup/Passthrough'
//  '<S200>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/D Gain/Internal Parameters'
//  '<S201>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Filter/Cont. Filter'
//  '<S202>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Filter ICs/Internal IC - Filter'
//  '<S203>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/I Gain/Internal Parameters'
//  '<S204>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Ideal P Gain/Passthrough'
//  '<S205>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Ideal P Gain Fdbk/Disabled'
//  '<S206>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Integrator/Continuous'
//  '<S207>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Integrator ICs/Internal IC'
//  '<S208>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/N Copy/Disabled'
//  '<S209>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/N Gain/Internal Parameters'
//  '<S210>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/P Copy/Disabled'
//  '<S211>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Parallel P Gain/Internal Parameters'
//  '<S212>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Reset Signal/Disabled'
//  '<S213>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Saturation/Passthrough'
//  '<S214>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Saturation Fdbk/Disabled'
//  '<S215>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Sum/Sum_PID'
//  '<S216>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Sum Fdbk/Disabled'
//  '<S217>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Tracking Mode/Disabled'
//  '<S218>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Tracking Mode Sum/Passthrough'
//  '<S219>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Tsamp - Integral/TsSignalSpecification'
//  '<S220>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/Tsamp - Ngain/Passthrough'
//  '<S221>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/postSat Signal/Forward_Path'
//  '<S222>' : 'URController/MainControl/Control System/DC motor system4/PID Controller14/preSat Signal/Forward_Path'
//  '<S223>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14'
//  '<S224>' : 'URController/MainControl/Control System/DC motor system5/velConvert'
//  '<S225>' : 'URController/MainControl/Control System/DC motor system5/voltageConvert'
//  '<S226>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Anti-windup'
//  '<S227>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/D Gain'
//  '<S228>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Filter'
//  '<S229>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Filter ICs'
//  '<S230>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/I Gain'
//  '<S231>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Ideal P Gain'
//  '<S232>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Ideal P Gain Fdbk'
//  '<S233>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Integrator'
//  '<S234>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Integrator ICs'
//  '<S235>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/N Copy'
//  '<S236>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/N Gain'
//  '<S237>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/P Copy'
//  '<S238>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Parallel P Gain'
//  '<S239>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Reset Signal'
//  '<S240>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Saturation'
//  '<S241>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Saturation Fdbk'
//  '<S242>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Sum'
//  '<S243>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Sum Fdbk'
//  '<S244>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Tracking Mode'
//  '<S245>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Tracking Mode Sum'
//  '<S246>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Tsamp - Integral'
//  '<S247>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Tsamp - Ngain'
//  '<S248>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/postSat Signal'
//  '<S249>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/preSat Signal'
//  '<S250>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Anti-windup/Passthrough'
//  '<S251>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/D Gain/Internal Parameters'
//  '<S252>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Filter/Cont. Filter'
//  '<S253>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Filter ICs/Internal IC - Filter'
//  '<S254>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/I Gain/Internal Parameters'
//  '<S255>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Ideal P Gain/Passthrough'
//  '<S256>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Ideal P Gain Fdbk/Disabled'
//  '<S257>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Integrator/Continuous'
//  '<S258>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Integrator ICs/Internal IC'
//  '<S259>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/N Copy/Disabled'
//  '<S260>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/N Gain/Internal Parameters'
//  '<S261>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/P Copy/Disabled'
//  '<S262>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Parallel P Gain/Internal Parameters'
//  '<S263>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Reset Signal/Disabled'
//  '<S264>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Saturation/Passthrough'
//  '<S265>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Saturation Fdbk/Disabled'
//  '<S266>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Sum/Sum_PID'
//  '<S267>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Sum Fdbk/Disabled'
//  '<S268>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Tracking Mode/Disabled'
//  '<S269>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Tracking Mode Sum/Passthrough'
//  '<S270>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Tsamp - Integral/TsSignalSpecification'
//  '<S271>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/Tsamp - Ngain/Passthrough'
//  '<S272>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/postSat Signal/Forward_Path'
//  '<S273>' : 'URController/MainControl/Control System/DC motor system5/PID Controller14/preSat Signal/Forward_Path'
//  '<S274>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14'
//  '<S275>' : 'URController/MainControl/Control System/DC motor system6/velConvert'
//  '<S276>' : 'URController/MainControl/Control System/DC motor system6/voltageConvert'
//  '<S277>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Anti-windup'
//  '<S278>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/D Gain'
//  '<S279>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Filter'
//  '<S280>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Filter ICs'
//  '<S281>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/I Gain'
//  '<S282>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Ideal P Gain'
//  '<S283>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Ideal P Gain Fdbk'
//  '<S284>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Integrator'
//  '<S285>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Integrator ICs'
//  '<S286>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/N Copy'
//  '<S287>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/N Gain'
//  '<S288>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/P Copy'
//  '<S289>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Parallel P Gain'
//  '<S290>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Reset Signal'
//  '<S291>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Saturation'
//  '<S292>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Saturation Fdbk'
//  '<S293>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Sum'
//  '<S294>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Sum Fdbk'
//  '<S295>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Tracking Mode'
//  '<S296>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Tracking Mode Sum'
//  '<S297>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Tsamp - Integral'
//  '<S298>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Tsamp - Ngain'
//  '<S299>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/postSat Signal'
//  '<S300>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/preSat Signal'
//  '<S301>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Anti-windup/Passthrough'
//  '<S302>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/D Gain/Internal Parameters'
//  '<S303>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Filter/Cont. Filter'
//  '<S304>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Filter ICs/Internal IC - Filter'
//  '<S305>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/I Gain/Internal Parameters'
//  '<S306>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Ideal P Gain/Passthrough'
//  '<S307>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Ideal P Gain Fdbk/Disabled'
//  '<S308>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Integrator/Continuous'
//  '<S309>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Integrator ICs/Internal IC'
//  '<S310>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/N Copy/Disabled'
//  '<S311>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/N Gain/Internal Parameters'
//  '<S312>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/P Copy/Disabled'
//  '<S313>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Parallel P Gain/Internal Parameters'
//  '<S314>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Reset Signal/Disabled'
//  '<S315>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Saturation/Passthrough'
//  '<S316>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Saturation Fdbk/Disabled'
//  '<S317>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Sum/Sum_PID'
//  '<S318>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Sum Fdbk/Disabled'
//  '<S319>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Tracking Mode/Disabled'
//  '<S320>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Tracking Mode Sum/Passthrough'
//  '<S321>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Tsamp - Integral/TsSignalSpecification'
//  '<S322>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/Tsamp - Ngain/Passthrough'
//  '<S323>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/postSat Signal/Forward_Path'
//  '<S324>' : 'URController/MainControl/Control System/DC motor system6/PID Controller14/preSat Signal/Forward_Path'
//  '<S325>' : 'URController/MainControl/Control System/motionGenerator1/MATLAB Function'
//  '<S326>' : 'URController/MainControl/Control System/motionGenerator1/MATLAB Function1'
//  '<S327>' : 'URController/MainControl/Control System/motionGenerator2/MATLAB Function'
//  '<S328>' : 'URController/MainControl/Control System/motionGenerator2/MATLAB Function1'
//  '<S329>' : 'URController/MainControl/Control System/motionGenerator3/MATLAB Function'
//  '<S330>' : 'URController/MainControl/Control System/motionGenerator3/MATLAB Function1'
//  '<S331>' : 'URController/MainControl/Control System/motionGenerator4/MATLAB Function'
//  '<S332>' : 'URController/MainControl/Control System/motionGenerator4/MATLAB Function1'
//  '<S333>' : 'URController/MainControl/Control System/motionGenerator5/MATLAB Function'
//  '<S334>' : 'URController/MainControl/Control System/motionGenerator5/MATLAB Function1'
//  '<S335>' : 'URController/MainControl/Control System/motionGenerator7/MATLAB Function'
//  '<S336>' : 'URController/MainControl/Control System/motionGenerator7/MATLAB Function1'
//  '<S337>' : 'URController/MainControl/Kinematic calculator/MATLAB Function'
//  '<S338>' : 'URController/MainControl/Kinematic calculator/MATLAB Function1'
//  '<S339>' : 'URController/MainControl/Kinematic calculator/MATLAB Function2'
//  '<S340>' : 'URController/forwardkinematics1/MATLAB Function'

#endif                                 // RTW_HEADER_URController_h_

//
// File trailer for generated code.
//
// [EOF]
//
