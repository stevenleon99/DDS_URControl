//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: URController.h
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
    real_T FilterCoefficient;          // '<S149>/Filter Coefficient'
    real_T Sum;                        // '<S155>/Sum'
    real_T IntegralGain;               // '<S143>/Integral Gain'
    real_T FilterCoefficient_l;        // '<S197>/Filter Coefficient'
    real_T Sum_d;                      // '<S203>/Sum'
    real_T IntegralGain_o;             // '<S191>/Integral Gain'
    real_T FilterCoefficient_f;        // '<S245>/Filter Coefficient'
    real_T Sum_f;                      // '<S251>/Sum'
    real_T IntegralGain_n;             // '<S239>/Integral Gain'
    real_T FilterCoefficient_fr;       // '<S293>/Filter Coefficient'
    real_T Sum_h;                      // '<S299>/Sum'
    real_T IntegralGain_a;             // '<S287>/Integral Gain'
    real_T FilterCoefficient_b;        // '<S53>/Filter Coefficient'
    real_T Sum_n;                      // '<S59>/Sum'
    real_T IntegralGain_os;            // '<S47>/Integral Gain'
    real_T FilterCoefficient_g;        // '<S101>/Filter Coefficient'
    real_T Sum_o;                      // '<S107>/Sum'
    real_T IntegralGain_i;             // '<S95>/Integral Gain'
    real_T pos;                        // '<S18>/MATLAB Function1'
    real_T vel;                        // '<S18>/MATLAB Function1'
    real_T pos_a;                      // '<S17>/MATLAB Function1'
    real_T vel_e;                      // '<S17>/MATLAB Function1'
    real_T pos_h;                      // '<S16>/MATLAB Function1'
    real_T vel_es;                     // '<S16>/MATLAB Function1'
    real_T pos_a5;                     // '<S15>/MATLAB Function1'
    real_T vel_i;                      // '<S15>/MATLAB Function1'
    real_T pos_g;                      // '<S14>/MATLAB Function1'
    real_T vel_j;                      // '<S14>/MATLAB Function1'
    real_T pos_i;                      // '<S13>/MATLAB Function1'
    real_T vel_j2;                     // '<S13>/MATLAB Function1'
    B_MATLABFunction sf_MATLABFunction_i;// '<S18>/MATLAB Function'
    B_MATLABFunction sf_MATLABFunction_e;// '<S17>/MATLAB Function'
    B_MATLABFunction sf_MATLABFunction_fe;// '<S16>/MATLAB Function'
    B_MATLABFunction sf_MATLABFunction_n;// '<S15>/MATLAB Function'
    B_MATLABFunction sf_MATLABFunction_m;// '<S14>/MATLAB Function'
    B_MATLABFunction sf_MATLABFunction_f;// '<S13>/MATLAB Function'
  };

  // Block states (default storage) for system '<Root>'
  struct DW {
    real_T DelayOneStep2_DSTATE;       // '<S13>/Delay One Step2'
    real_T DelayOneStep3_DSTATE;       // '<S13>/Delay One Step3'
    real_T DelayOneStep2_DSTATE_e;     // '<S14>/Delay One Step2'
    real_T DelayOneStep3_DSTATE_h;     // '<S14>/Delay One Step3'
    real_T DelayOneStep2_DSTATE_p;     // '<S15>/Delay One Step2'
    real_T DelayOneStep3_DSTATE_i;     // '<S15>/Delay One Step3'
    real_T DelayOneStep2_DSTATE_f;     // '<S16>/Delay One Step2'
    real_T DelayOneStep3_DSTATE_l;     // '<S16>/Delay One Step3'
    real_T DelayOneStep2_DSTATE_i;     // '<S17>/Delay One Step2'
    real_T DelayOneStep3_DSTATE_f;     // '<S17>/Delay One Step3'
    real_T DelayOneStep2_DSTATE_em;    // '<S18>/Delay One Step2'
    real_T DelayOneStep3_DSTATE_fz;    // '<S18>/Delay One Step3'
    DW_MATLABFunction sf_MATLABFunction_i;// '<S18>/MATLAB Function'
    DW_MATLABFunction sf_MATLABFunction_e;// '<S17>/MATLAB Function'
    DW_MATLABFunction sf_MATLABFunction_fe;// '<S16>/MATLAB Function'
    DW_MATLABFunction sf_MATLABFunction_n;// '<S15>/MATLAB Function'
    DW_MATLABFunction sf_MATLABFunction_m;// '<S14>/MATLAB Function'
    DW_MATLABFunction sf_MATLABFunction_f;// '<S13>/MATLAB Function'
  };

  // Continuous states (default storage)
  struct X {
    real_T TransferFcn7_CSTATE[3];     // '<S4>/Transfer Fcn7'
    real_T TransferFcn8_CSTATE[3];     // '<S4>/Transfer Fcn8'
    real_T TransferFcn9_CSTATE[3];     // '<S4>/Transfer Fcn9'
    real_T TransferFcn10_CSTATE[3];    // '<S4>/Transfer Fcn10'
    real_T TransferFcn11_CSTATE[3];    // '<S4>/Transfer Fcn11'
    real_T TransferFcn12_CSTATE[3];    // '<S4>/Transfer Fcn12'
    real_T Filter_CSTATE;              // '<S141>/Filter'
    real_T Integrator_CSTATE;          // '<S146>/Integrator'
    real_T Filter_CSTATE_k;            // '<S189>/Filter'
    real_T Integrator_CSTATE_d;        // '<S194>/Integrator'
    real_T Filter_CSTATE_j;            // '<S237>/Filter'
    real_T Integrator_CSTATE_f;        // '<S242>/Integrator'
    real_T Filter_CSTATE_c;            // '<S285>/Filter'
    real_T Integrator_CSTATE_g;        // '<S290>/Integrator'
    real_T Filter_CSTATE_d;            // '<S45>/Filter'
    real_T Integrator_CSTATE_di;       // '<S50>/Integrator'
    real_T Filter_CSTATE_i;            // '<S93>/Filter'
    real_T Integrator_CSTATE_o;        // '<S98>/Integrator'
  };

  // State derivatives (default storage)
  struct XDot {
    real_T TransferFcn7_CSTATE[3];     // '<S4>/Transfer Fcn7'
    real_T TransferFcn8_CSTATE[3];     // '<S4>/Transfer Fcn8'
    real_T TransferFcn9_CSTATE[3];     // '<S4>/Transfer Fcn9'
    real_T TransferFcn10_CSTATE[3];    // '<S4>/Transfer Fcn10'
    real_T TransferFcn11_CSTATE[3];    // '<S4>/Transfer Fcn11'
    real_T TransferFcn12_CSTATE[3];    // '<S4>/Transfer Fcn12'
    real_T Filter_CSTATE;              // '<S141>/Filter'
    real_T Integrator_CSTATE;          // '<S146>/Integrator'
    real_T Filter_CSTATE_k;            // '<S189>/Filter'
    real_T Integrator_CSTATE_d;        // '<S194>/Integrator'
    real_T Filter_CSTATE_j;            // '<S237>/Filter'
    real_T Integrator_CSTATE_f;        // '<S242>/Integrator'
    real_T Filter_CSTATE_c;            // '<S285>/Filter'
    real_T Integrator_CSTATE_g;        // '<S290>/Integrator'
    real_T Filter_CSTATE_d;            // '<S45>/Filter'
    real_T Integrator_CSTATE_di;       // '<S50>/Integrator'
    real_T Filter_CSTATE_i;            // '<S93>/Filter'
    real_T Integrator_CSTATE_o;        // '<S98>/Integrator'
  };

  // State disabled
  struct XDis {
    boolean_T TransferFcn7_CSTATE[3];  // '<S4>/Transfer Fcn7'
    boolean_T TransferFcn8_CSTATE[3];  // '<S4>/Transfer Fcn8'
    boolean_T TransferFcn9_CSTATE[3];  // '<S4>/Transfer Fcn9'
    boolean_T TransferFcn10_CSTATE[3]; // '<S4>/Transfer Fcn10'
    boolean_T TransferFcn11_CSTATE[3]; // '<S4>/Transfer Fcn11'
    boolean_T TransferFcn12_CSTATE[3]; // '<S4>/Transfer Fcn12'
    boolean_T Filter_CSTATE;           // '<S141>/Filter'
    boolean_T Integrator_CSTATE;       // '<S146>/Integrator'
    boolean_T Filter_CSTATE_k;         // '<S189>/Filter'
    boolean_T Integrator_CSTATE_d;     // '<S194>/Integrator'
    boolean_T Filter_CSTATE_j;         // '<S237>/Filter'
    boolean_T Integrator_CSTATE_f;     // '<S242>/Integrator'
    boolean_T Filter_CSTATE_c;         // '<S285>/Filter'
    boolean_T Integrator_CSTATE_g;     // '<S290>/Integrator'
    boolean_T Filter_CSTATE_d;         // '<S45>/Filter'
    boolean_T Integrator_CSTATE_di;    // '<S50>/Integrator'
    boolean_T Filter_CSTATE_i;         // '<S93>/Filter'
    boolean_T Integrator_CSTATE_o;     // '<S98>/Integrator'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T ori_theta_arr[6];           // '<Root>/ori_theta_arr'
    real_T desire_pos_orient_arr[6];   // '<Root>/desire_pos_orient_arr'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T actual_theta_arr[6];        // '<Root>/actual_theta_arr'
    real_T Output[3];                  // '<Root>/Output'
    real_T Output1[3];                 // '<Root>/Output1'
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
//  '<S2>'   : 'URController/Subsystem'
//  '<S3>'   : 'URController/forwardkinematics1'
//  '<S4>'   : 'URController/Subsystem/Control System'
//  '<S5>'   : 'URController/Subsystem/Kinematic calculator'
//  '<S6>'   : 'URController/Subsystem/isInitialized'
//  '<S7>'   : 'URController/Subsystem/Control System/PID Controller10'
//  '<S8>'   : 'URController/Subsystem/Control System/PID Controller11'
//  '<S9>'   : 'URController/Subsystem/Control System/PID Controller13'
//  '<S10>'  : 'URController/Subsystem/Control System/PID Controller6'
//  '<S11>'  : 'URController/Subsystem/Control System/PID Controller8'
//  '<S12>'  : 'URController/Subsystem/Control System/PID Controller9'
//  '<S13>'  : 'URController/Subsystem/Control System/motionGenerator1'
//  '<S14>'  : 'URController/Subsystem/Control System/motionGenerator2'
//  '<S15>'  : 'URController/Subsystem/Control System/motionGenerator3'
//  '<S16>'  : 'URController/Subsystem/Control System/motionGenerator4'
//  '<S17>'  : 'URController/Subsystem/Control System/motionGenerator5'
//  '<S18>'  : 'URController/Subsystem/Control System/motionGenerator7'
//  '<S19>'  : 'URController/Subsystem/Control System/PID Controller10/Anti-windup'
//  '<S20>'  : 'URController/Subsystem/Control System/PID Controller10/D Gain'
//  '<S21>'  : 'URController/Subsystem/Control System/PID Controller10/Filter'
//  '<S22>'  : 'URController/Subsystem/Control System/PID Controller10/Filter ICs'
//  '<S23>'  : 'URController/Subsystem/Control System/PID Controller10/I Gain'
//  '<S24>'  : 'URController/Subsystem/Control System/PID Controller10/Ideal P Gain'
//  '<S25>'  : 'URController/Subsystem/Control System/PID Controller10/Ideal P Gain Fdbk'
//  '<S26>'  : 'URController/Subsystem/Control System/PID Controller10/Integrator'
//  '<S27>'  : 'URController/Subsystem/Control System/PID Controller10/Integrator ICs'
//  '<S28>'  : 'URController/Subsystem/Control System/PID Controller10/N Copy'
//  '<S29>'  : 'URController/Subsystem/Control System/PID Controller10/N Gain'
//  '<S30>'  : 'URController/Subsystem/Control System/PID Controller10/P Copy'
//  '<S31>'  : 'URController/Subsystem/Control System/PID Controller10/Parallel P Gain'
//  '<S32>'  : 'URController/Subsystem/Control System/PID Controller10/Reset Signal'
//  '<S33>'  : 'URController/Subsystem/Control System/PID Controller10/Saturation'
//  '<S34>'  : 'URController/Subsystem/Control System/PID Controller10/Saturation Fdbk'
//  '<S35>'  : 'URController/Subsystem/Control System/PID Controller10/Sum'
//  '<S36>'  : 'URController/Subsystem/Control System/PID Controller10/Sum Fdbk'
//  '<S37>'  : 'URController/Subsystem/Control System/PID Controller10/Tracking Mode'
//  '<S38>'  : 'URController/Subsystem/Control System/PID Controller10/Tracking Mode Sum'
//  '<S39>'  : 'URController/Subsystem/Control System/PID Controller10/Tsamp - Integral'
//  '<S40>'  : 'URController/Subsystem/Control System/PID Controller10/Tsamp - Ngain'
//  '<S41>'  : 'URController/Subsystem/Control System/PID Controller10/postSat Signal'
//  '<S42>'  : 'URController/Subsystem/Control System/PID Controller10/preSat Signal'
//  '<S43>'  : 'URController/Subsystem/Control System/PID Controller10/Anti-windup/Passthrough'
//  '<S44>'  : 'URController/Subsystem/Control System/PID Controller10/D Gain/Internal Parameters'
//  '<S45>'  : 'URController/Subsystem/Control System/PID Controller10/Filter/Cont. Filter'
//  '<S46>'  : 'URController/Subsystem/Control System/PID Controller10/Filter ICs/Internal IC - Filter'
//  '<S47>'  : 'URController/Subsystem/Control System/PID Controller10/I Gain/Internal Parameters'
//  '<S48>'  : 'URController/Subsystem/Control System/PID Controller10/Ideal P Gain/Passthrough'
//  '<S49>'  : 'URController/Subsystem/Control System/PID Controller10/Ideal P Gain Fdbk/Disabled'
//  '<S50>'  : 'URController/Subsystem/Control System/PID Controller10/Integrator/Continuous'
//  '<S51>'  : 'URController/Subsystem/Control System/PID Controller10/Integrator ICs/Internal IC'
//  '<S52>'  : 'URController/Subsystem/Control System/PID Controller10/N Copy/Disabled'
//  '<S53>'  : 'URController/Subsystem/Control System/PID Controller10/N Gain/Internal Parameters'
//  '<S54>'  : 'URController/Subsystem/Control System/PID Controller10/P Copy/Disabled'
//  '<S55>'  : 'URController/Subsystem/Control System/PID Controller10/Parallel P Gain/Internal Parameters'
//  '<S56>'  : 'URController/Subsystem/Control System/PID Controller10/Reset Signal/Disabled'
//  '<S57>'  : 'URController/Subsystem/Control System/PID Controller10/Saturation/Passthrough'
//  '<S58>'  : 'URController/Subsystem/Control System/PID Controller10/Saturation Fdbk/Disabled'
//  '<S59>'  : 'URController/Subsystem/Control System/PID Controller10/Sum/Sum_PID'
//  '<S60>'  : 'URController/Subsystem/Control System/PID Controller10/Sum Fdbk/Disabled'
//  '<S61>'  : 'URController/Subsystem/Control System/PID Controller10/Tracking Mode/Disabled'
//  '<S62>'  : 'URController/Subsystem/Control System/PID Controller10/Tracking Mode Sum/Passthrough'
//  '<S63>'  : 'URController/Subsystem/Control System/PID Controller10/Tsamp - Integral/TsSignalSpecification'
//  '<S64>'  : 'URController/Subsystem/Control System/PID Controller10/Tsamp - Ngain/Passthrough'
//  '<S65>'  : 'URController/Subsystem/Control System/PID Controller10/postSat Signal/Forward_Path'
//  '<S66>'  : 'URController/Subsystem/Control System/PID Controller10/preSat Signal/Forward_Path'
//  '<S67>'  : 'URController/Subsystem/Control System/PID Controller11/Anti-windup'
//  '<S68>'  : 'URController/Subsystem/Control System/PID Controller11/D Gain'
//  '<S69>'  : 'URController/Subsystem/Control System/PID Controller11/Filter'
//  '<S70>'  : 'URController/Subsystem/Control System/PID Controller11/Filter ICs'
//  '<S71>'  : 'URController/Subsystem/Control System/PID Controller11/I Gain'
//  '<S72>'  : 'URController/Subsystem/Control System/PID Controller11/Ideal P Gain'
//  '<S73>'  : 'URController/Subsystem/Control System/PID Controller11/Ideal P Gain Fdbk'
//  '<S74>'  : 'URController/Subsystem/Control System/PID Controller11/Integrator'
//  '<S75>'  : 'URController/Subsystem/Control System/PID Controller11/Integrator ICs'
//  '<S76>'  : 'URController/Subsystem/Control System/PID Controller11/N Copy'
//  '<S77>'  : 'URController/Subsystem/Control System/PID Controller11/N Gain'
//  '<S78>'  : 'URController/Subsystem/Control System/PID Controller11/P Copy'
//  '<S79>'  : 'URController/Subsystem/Control System/PID Controller11/Parallel P Gain'
//  '<S80>'  : 'URController/Subsystem/Control System/PID Controller11/Reset Signal'
//  '<S81>'  : 'URController/Subsystem/Control System/PID Controller11/Saturation'
//  '<S82>'  : 'URController/Subsystem/Control System/PID Controller11/Saturation Fdbk'
//  '<S83>'  : 'URController/Subsystem/Control System/PID Controller11/Sum'
//  '<S84>'  : 'URController/Subsystem/Control System/PID Controller11/Sum Fdbk'
//  '<S85>'  : 'URController/Subsystem/Control System/PID Controller11/Tracking Mode'
//  '<S86>'  : 'URController/Subsystem/Control System/PID Controller11/Tracking Mode Sum'
//  '<S87>'  : 'URController/Subsystem/Control System/PID Controller11/Tsamp - Integral'
//  '<S88>'  : 'URController/Subsystem/Control System/PID Controller11/Tsamp - Ngain'
//  '<S89>'  : 'URController/Subsystem/Control System/PID Controller11/postSat Signal'
//  '<S90>'  : 'URController/Subsystem/Control System/PID Controller11/preSat Signal'
//  '<S91>'  : 'URController/Subsystem/Control System/PID Controller11/Anti-windup/Passthrough'
//  '<S92>'  : 'URController/Subsystem/Control System/PID Controller11/D Gain/Internal Parameters'
//  '<S93>'  : 'URController/Subsystem/Control System/PID Controller11/Filter/Cont. Filter'
//  '<S94>'  : 'URController/Subsystem/Control System/PID Controller11/Filter ICs/Internal IC - Filter'
//  '<S95>'  : 'URController/Subsystem/Control System/PID Controller11/I Gain/Internal Parameters'
//  '<S96>'  : 'URController/Subsystem/Control System/PID Controller11/Ideal P Gain/Passthrough'
//  '<S97>'  : 'URController/Subsystem/Control System/PID Controller11/Ideal P Gain Fdbk/Disabled'
//  '<S98>'  : 'URController/Subsystem/Control System/PID Controller11/Integrator/Continuous'
//  '<S99>'  : 'URController/Subsystem/Control System/PID Controller11/Integrator ICs/Internal IC'
//  '<S100>' : 'URController/Subsystem/Control System/PID Controller11/N Copy/Disabled'
//  '<S101>' : 'URController/Subsystem/Control System/PID Controller11/N Gain/Internal Parameters'
//  '<S102>' : 'URController/Subsystem/Control System/PID Controller11/P Copy/Disabled'
//  '<S103>' : 'URController/Subsystem/Control System/PID Controller11/Parallel P Gain/Internal Parameters'
//  '<S104>' : 'URController/Subsystem/Control System/PID Controller11/Reset Signal/Disabled'
//  '<S105>' : 'URController/Subsystem/Control System/PID Controller11/Saturation/Passthrough'
//  '<S106>' : 'URController/Subsystem/Control System/PID Controller11/Saturation Fdbk/Disabled'
//  '<S107>' : 'URController/Subsystem/Control System/PID Controller11/Sum/Sum_PID'
//  '<S108>' : 'URController/Subsystem/Control System/PID Controller11/Sum Fdbk/Disabled'
//  '<S109>' : 'URController/Subsystem/Control System/PID Controller11/Tracking Mode/Disabled'
//  '<S110>' : 'URController/Subsystem/Control System/PID Controller11/Tracking Mode Sum/Passthrough'
//  '<S111>' : 'URController/Subsystem/Control System/PID Controller11/Tsamp - Integral/TsSignalSpecification'
//  '<S112>' : 'URController/Subsystem/Control System/PID Controller11/Tsamp - Ngain/Passthrough'
//  '<S113>' : 'URController/Subsystem/Control System/PID Controller11/postSat Signal/Forward_Path'
//  '<S114>' : 'URController/Subsystem/Control System/PID Controller11/preSat Signal/Forward_Path'
//  '<S115>' : 'URController/Subsystem/Control System/PID Controller13/Anti-windup'
//  '<S116>' : 'URController/Subsystem/Control System/PID Controller13/D Gain'
//  '<S117>' : 'URController/Subsystem/Control System/PID Controller13/Filter'
//  '<S118>' : 'URController/Subsystem/Control System/PID Controller13/Filter ICs'
//  '<S119>' : 'URController/Subsystem/Control System/PID Controller13/I Gain'
//  '<S120>' : 'URController/Subsystem/Control System/PID Controller13/Ideal P Gain'
//  '<S121>' : 'URController/Subsystem/Control System/PID Controller13/Ideal P Gain Fdbk'
//  '<S122>' : 'URController/Subsystem/Control System/PID Controller13/Integrator'
//  '<S123>' : 'URController/Subsystem/Control System/PID Controller13/Integrator ICs'
//  '<S124>' : 'URController/Subsystem/Control System/PID Controller13/N Copy'
//  '<S125>' : 'URController/Subsystem/Control System/PID Controller13/N Gain'
//  '<S126>' : 'URController/Subsystem/Control System/PID Controller13/P Copy'
//  '<S127>' : 'URController/Subsystem/Control System/PID Controller13/Parallel P Gain'
//  '<S128>' : 'URController/Subsystem/Control System/PID Controller13/Reset Signal'
//  '<S129>' : 'URController/Subsystem/Control System/PID Controller13/Saturation'
//  '<S130>' : 'URController/Subsystem/Control System/PID Controller13/Saturation Fdbk'
//  '<S131>' : 'URController/Subsystem/Control System/PID Controller13/Sum'
//  '<S132>' : 'URController/Subsystem/Control System/PID Controller13/Sum Fdbk'
//  '<S133>' : 'URController/Subsystem/Control System/PID Controller13/Tracking Mode'
//  '<S134>' : 'URController/Subsystem/Control System/PID Controller13/Tracking Mode Sum'
//  '<S135>' : 'URController/Subsystem/Control System/PID Controller13/Tsamp - Integral'
//  '<S136>' : 'URController/Subsystem/Control System/PID Controller13/Tsamp - Ngain'
//  '<S137>' : 'URController/Subsystem/Control System/PID Controller13/postSat Signal'
//  '<S138>' : 'URController/Subsystem/Control System/PID Controller13/preSat Signal'
//  '<S139>' : 'URController/Subsystem/Control System/PID Controller13/Anti-windup/Passthrough'
//  '<S140>' : 'URController/Subsystem/Control System/PID Controller13/D Gain/Internal Parameters'
//  '<S141>' : 'URController/Subsystem/Control System/PID Controller13/Filter/Cont. Filter'
//  '<S142>' : 'URController/Subsystem/Control System/PID Controller13/Filter ICs/Internal IC - Filter'
//  '<S143>' : 'URController/Subsystem/Control System/PID Controller13/I Gain/Internal Parameters'
//  '<S144>' : 'URController/Subsystem/Control System/PID Controller13/Ideal P Gain/Passthrough'
//  '<S145>' : 'URController/Subsystem/Control System/PID Controller13/Ideal P Gain Fdbk/Disabled'
//  '<S146>' : 'URController/Subsystem/Control System/PID Controller13/Integrator/Continuous'
//  '<S147>' : 'URController/Subsystem/Control System/PID Controller13/Integrator ICs/Internal IC'
//  '<S148>' : 'URController/Subsystem/Control System/PID Controller13/N Copy/Disabled'
//  '<S149>' : 'URController/Subsystem/Control System/PID Controller13/N Gain/Internal Parameters'
//  '<S150>' : 'URController/Subsystem/Control System/PID Controller13/P Copy/Disabled'
//  '<S151>' : 'URController/Subsystem/Control System/PID Controller13/Parallel P Gain/Internal Parameters'
//  '<S152>' : 'URController/Subsystem/Control System/PID Controller13/Reset Signal/Disabled'
//  '<S153>' : 'URController/Subsystem/Control System/PID Controller13/Saturation/Passthrough'
//  '<S154>' : 'URController/Subsystem/Control System/PID Controller13/Saturation Fdbk/Disabled'
//  '<S155>' : 'URController/Subsystem/Control System/PID Controller13/Sum/Sum_PID'
//  '<S156>' : 'URController/Subsystem/Control System/PID Controller13/Sum Fdbk/Disabled'
//  '<S157>' : 'URController/Subsystem/Control System/PID Controller13/Tracking Mode/Disabled'
//  '<S158>' : 'URController/Subsystem/Control System/PID Controller13/Tracking Mode Sum/Passthrough'
//  '<S159>' : 'URController/Subsystem/Control System/PID Controller13/Tsamp - Integral/TsSignalSpecification'
//  '<S160>' : 'URController/Subsystem/Control System/PID Controller13/Tsamp - Ngain/Passthrough'
//  '<S161>' : 'URController/Subsystem/Control System/PID Controller13/postSat Signal/Forward_Path'
//  '<S162>' : 'URController/Subsystem/Control System/PID Controller13/preSat Signal/Forward_Path'
//  '<S163>' : 'URController/Subsystem/Control System/PID Controller6/Anti-windup'
//  '<S164>' : 'URController/Subsystem/Control System/PID Controller6/D Gain'
//  '<S165>' : 'URController/Subsystem/Control System/PID Controller6/Filter'
//  '<S166>' : 'URController/Subsystem/Control System/PID Controller6/Filter ICs'
//  '<S167>' : 'URController/Subsystem/Control System/PID Controller6/I Gain'
//  '<S168>' : 'URController/Subsystem/Control System/PID Controller6/Ideal P Gain'
//  '<S169>' : 'URController/Subsystem/Control System/PID Controller6/Ideal P Gain Fdbk'
//  '<S170>' : 'URController/Subsystem/Control System/PID Controller6/Integrator'
//  '<S171>' : 'URController/Subsystem/Control System/PID Controller6/Integrator ICs'
//  '<S172>' : 'URController/Subsystem/Control System/PID Controller6/N Copy'
//  '<S173>' : 'URController/Subsystem/Control System/PID Controller6/N Gain'
//  '<S174>' : 'URController/Subsystem/Control System/PID Controller6/P Copy'
//  '<S175>' : 'URController/Subsystem/Control System/PID Controller6/Parallel P Gain'
//  '<S176>' : 'URController/Subsystem/Control System/PID Controller6/Reset Signal'
//  '<S177>' : 'URController/Subsystem/Control System/PID Controller6/Saturation'
//  '<S178>' : 'URController/Subsystem/Control System/PID Controller6/Saturation Fdbk'
//  '<S179>' : 'URController/Subsystem/Control System/PID Controller6/Sum'
//  '<S180>' : 'URController/Subsystem/Control System/PID Controller6/Sum Fdbk'
//  '<S181>' : 'URController/Subsystem/Control System/PID Controller6/Tracking Mode'
//  '<S182>' : 'URController/Subsystem/Control System/PID Controller6/Tracking Mode Sum'
//  '<S183>' : 'URController/Subsystem/Control System/PID Controller6/Tsamp - Integral'
//  '<S184>' : 'URController/Subsystem/Control System/PID Controller6/Tsamp - Ngain'
//  '<S185>' : 'URController/Subsystem/Control System/PID Controller6/postSat Signal'
//  '<S186>' : 'URController/Subsystem/Control System/PID Controller6/preSat Signal'
//  '<S187>' : 'URController/Subsystem/Control System/PID Controller6/Anti-windup/Passthrough'
//  '<S188>' : 'URController/Subsystem/Control System/PID Controller6/D Gain/Internal Parameters'
//  '<S189>' : 'URController/Subsystem/Control System/PID Controller6/Filter/Cont. Filter'
//  '<S190>' : 'URController/Subsystem/Control System/PID Controller6/Filter ICs/Internal IC - Filter'
//  '<S191>' : 'URController/Subsystem/Control System/PID Controller6/I Gain/Internal Parameters'
//  '<S192>' : 'URController/Subsystem/Control System/PID Controller6/Ideal P Gain/Passthrough'
//  '<S193>' : 'URController/Subsystem/Control System/PID Controller6/Ideal P Gain Fdbk/Disabled'
//  '<S194>' : 'URController/Subsystem/Control System/PID Controller6/Integrator/Continuous'
//  '<S195>' : 'URController/Subsystem/Control System/PID Controller6/Integrator ICs/Internal IC'
//  '<S196>' : 'URController/Subsystem/Control System/PID Controller6/N Copy/Disabled'
//  '<S197>' : 'URController/Subsystem/Control System/PID Controller6/N Gain/Internal Parameters'
//  '<S198>' : 'URController/Subsystem/Control System/PID Controller6/P Copy/Disabled'
//  '<S199>' : 'URController/Subsystem/Control System/PID Controller6/Parallel P Gain/Internal Parameters'
//  '<S200>' : 'URController/Subsystem/Control System/PID Controller6/Reset Signal/Disabled'
//  '<S201>' : 'URController/Subsystem/Control System/PID Controller6/Saturation/Passthrough'
//  '<S202>' : 'URController/Subsystem/Control System/PID Controller6/Saturation Fdbk/Disabled'
//  '<S203>' : 'URController/Subsystem/Control System/PID Controller6/Sum/Sum_PID'
//  '<S204>' : 'URController/Subsystem/Control System/PID Controller6/Sum Fdbk/Disabled'
//  '<S205>' : 'URController/Subsystem/Control System/PID Controller6/Tracking Mode/Disabled'
//  '<S206>' : 'URController/Subsystem/Control System/PID Controller6/Tracking Mode Sum/Passthrough'
//  '<S207>' : 'URController/Subsystem/Control System/PID Controller6/Tsamp - Integral/TsSignalSpecification'
//  '<S208>' : 'URController/Subsystem/Control System/PID Controller6/Tsamp - Ngain/Passthrough'
//  '<S209>' : 'URController/Subsystem/Control System/PID Controller6/postSat Signal/Forward_Path'
//  '<S210>' : 'URController/Subsystem/Control System/PID Controller6/preSat Signal/Forward_Path'
//  '<S211>' : 'URController/Subsystem/Control System/PID Controller8/Anti-windup'
//  '<S212>' : 'URController/Subsystem/Control System/PID Controller8/D Gain'
//  '<S213>' : 'URController/Subsystem/Control System/PID Controller8/Filter'
//  '<S214>' : 'URController/Subsystem/Control System/PID Controller8/Filter ICs'
//  '<S215>' : 'URController/Subsystem/Control System/PID Controller8/I Gain'
//  '<S216>' : 'URController/Subsystem/Control System/PID Controller8/Ideal P Gain'
//  '<S217>' : 'URController/Subsystem/Control System/PID Controller8/Ideal P Gain Fdbk'
//  '<S218>' : 'URController/Subsystem/Control System/PID Controller8/Integrator'
//  '<S219>' : 'URController/Subsystem/Control System/PID Controller8/Integrator ICs'
//  '<S220>' : 'URController/Subsystem/Control System/PID Controller8/N Copy'
//  '<S221>' : 'URController/Subsystem/Control System/PID Controller8/N Gain'
//  '<S222>' : 'URController/Subsystem/Control System/PID Controller8/P Copy'
//  '<S223>' : 'URController/Subsystem/Control System/PID Controller8/Parallel P Gain'
//  '<S224>' : 'URController/Subsystem/Control System/PID Controller8/Reset Signal'
//  '<S225>' : 'URController/Subsystem/Control System/PID Controller8/Saturation'
//  '<S226>' : 'URController/Subsystem/Control System/PID Controller8/Saturation Fdbk'
//  '<S227>' : 'URController/Subsystem/Control System/PID Controller8/Sum'
//  '<S228>' : 'URController/Subsystem/Control System/PID Controller8/Sum Fdbk'
//  '<S229>' : 'URController/Subsystem/Control System/PID Controller8/Tracking Mode'
//  '<S230>' : 'URController/Subsystem/Control System/PID Controller8/Tracking Mode Sum'
//  '<S231>' : 'URController/Subsystem/Control System/PID Controller8/Tsamp - Integral'
//  '<S232>' : 'URController/Subsystem/Control System/PID Controller8/Tsamp - Ngain'
//  '<S233>' : 'URController/Subsystem/Control System/PID Controller8/postSat Signal'
//  '<S234>' : 'URController/Subsystem/Control System/PID Controller8/preSat Signal'
//  '<S235>' : 'URController/Subsystem/Control System/PID Controller8/Anti-windup/Passthrough'
//  '<S236>' : 'URController/Subsystem/Control System/PID Controller8/D Gain/Internal Parameters'
//  '<S237>' : 'URController/Subsystem/Control System/PID Controller8/Filter/Cont. Filter'
//  '<S238>' : 'URController/Subsystem/Control System/PID Controller8/Filter ICs/Internal IC - Filter'
//  '<S239>' : 'URController/Subsystem/Control System/PID Controller8/I Gain/Internal Parameters'
//  '<S240>' : 'URController/Subsystem/Control System/PID Controller8/Ideal P Gain/Passthrough'
//  '<S241>' : 'URController/Subsystem/Control System/PID Controller8/Ideal P Gain Fdbk/Disabled'
//  '<S242>' : 'URController/Subsystem/Control System/PID Controller8/Integrator/Continuous'
//  '<S243>' : 'URController/Subsystem/Control System/PID Controller8/Integrator ICs/Internal IC'
//  '<S244>' : 'URController/Subsystem/Control System/PID Controller8/N Copy/Disabled'
//  '<S245>' : 'URController/Subsystem/Control System/PID Controller8/N Gain/Internal Parameters'
//  '<S246>' : 'URController/Subsystem/Control System/PID Controller8/P Copy/Disabled'
//  '<S247>' : 'URController/Subsystem/Control System/PID Controller8/Parallel P Gain/Internal Parameters'
//  '<S248>' : 'URController/Subsystem/Control System/PID Controller8/Reset Signal/Disabled'
//  '<S249>' : 'URController/Subsystem/Control System/PID Controller8/Saturation/Passthrough'
//  '<S250>' : 'URController/Subsystem/Control System/PID Controller8/Saturation Fdbk/Disabled'
//  '<S251>' : 'URController/Subsystem/Control System/PID Controller8/Sum/Sum_PID'
//  '<S252>' : 'URController/Subsystem/Control System/PID Controller8/Sum Fdbk/Disabled'
//  '<S253>' : 'URController/Subsystem/Control System/PID Controller8/Tracking Mode/Disabled'
//  '<S254>' : 'URController/Subsystem/Control System/PID Controller8/Tracking Mode Sum/Passthrough'
//  '<S255>' : 'URController/Subsystem/Control System/PID Controller8/Tsamp - Integral/TsSignalSpecification'
//  '<S256>' : 'URController/Subsystem/Control System/PID Controller8/Tsamp - Ngain/Passthrough'
//  '<S257>' : 'URController/Subsystem/Control System/PID Controller8/postSat Signal/Forward_Path'
//  '<S258>' : 'URController/Subsystem/Control System/PID Controller8/preSat Signal/Forward_Path'
//  '<S259>' : 'URController/Subsystem/Control System/PID Controller9/Anti-windup'
//  '<S260>' : 'URController/Subsystem/Control System/PID Controller9/D Gain'
//  '<S261>' : 'URController/Subsystem/Control System/PID Controller9/Filter'
//  '<S262>' : 'URController/Subsystem/Control System/PID Controller9/Filter ICs'
//  '<S263>' : 'URController/Subsystem/Control System/PID Controller9/I Gain'
//  '<S264>' : 'URController/Subsystem/Control System/PID Controller9/Ideal P Gain'
//  '<S265>' : 'URController/Subsystem/Control System/PID Controller9/Ideal P Gain Fdbk'
//  '<S266>' : 'URController/Subsystem/Control System/PID Controller9/Integrator'
//  '<S267>' : 'URController/Subsystem/Control System/PID Controller9/Integrator ICs'
//  '<S268>' : 'URController/Subsystem/Control System/PID Controller9/N Copy'
//  '<S269>' : 'URController/Subsystem/Control System/PID Controller9/N Gain'
//  '<S270>' : 'URController/Subsystem/Control System/PID Controller9/P Copy'
//  '<S271>' : 'URController/Subsystem/Control System/PID Controller9/Parallel P Gain'
//  '<S272>' : 'URController/Subsystem/Control System/PID Controller9/Reset Signal'
//  '<S273>' : 'URController/Subsystem/Control System/PID Controller9/Saturation'
//  '<S274>' : 'URController/Subsystem/Control System/PID Controller9/Saturation Fdbk'
//  '<S275>' : 'URController/Subsystem/Control System/PID Controller9/Sum'
//  '<S276>' : 'URController/Subsystem/Control System/PID Controller9/Sum Fdbk'
//  '<S277>' : 'URController/Subsystem/Control System/PID Controller9/Tracking Mode'
//  '<S278>' : 'URController/Subsystem/Control System/PID Controller9/Tracking Mode Sum'
//  '<S279>' : 'URController/Subsystem/Control System/PID Controller9/Tsamp - Integral'
//  '<S280>' : 'URController/Subsystem/Control System/PID Controller9/Tsamp - Ngain'
//  '<S281>' : 'URController/Subsystem/Control System/PID Controller9/postSat Signal'
//  '<S282>' : 'URController/Subsystem/Control System/PID Controller9/preSat Signal'
//  '<S283>' : 'URController/Subsystem/Control System/PID Controller9/Anti-windup/Passthrough'
//  '<S284>' : 'URController/Subsystem/Control System/PID Controller9/D Gain/Internal Parameters'
//  '<S285>' : 'URController/Subsystem/Control System/PID Controller9/Filter/Cont. Filter'
//  '<S286>' : 'URController/Subsystem/Control System/PID Controller9/Filter ICs/Internal IC - Filter'
//  '<S287>' : 'URController/Subsystem/Control System/PID Controller9/I Gain/Internal Parameters'
//  '<S288>' : 'URController/Subsystem/Control System/PID Controller9/Ideal P Gain/Passthrough'
//  '<S289>' : 'URController/Subsystem/Control System/PID Controller9/Ideal P Gain Fdbk/Disabled'
//  '<S290>' : 'URController/Subsystem/Control System/PID Controller9/Integrator/Continuous'
//  '<S291>' : 'URController/Subsystem/Control System/PID Controller9/Integrator ICs/Internal IC'
//  '<S292>' : 'URController/Subsystem/Control System/PID Controller9/N Copy/Disabled'
//  '<S293>' : 'URController/Subsystem/Control System/PID Controller9/N Gain/Internal Parameters'
//  '<S294>' : 'URController/Subsystem/Control System/PID Controller9/P Copy/Disabled'
//  '<S295>' : 'URController/Subsystem/Control System/PID Controller9/Parallel P Gain/Internal Parameters'
//  '<S296>' : 'URController/Subsystem/Control System/PID Controller9/Reset Signal/Disabled'
//  '<S297>' : 'URController/Subsystem/Control System/PID Controller9/Saturation/Passthrough'
//  '<S298>' : 'URController/Subsystem/Control System/PID Controller9/Saturation Fdbk/Disabled'
//  '<S299>' : 'URController/Subsystem/Control System/PID Controller9/Sum/Sum_PID'
//  '<S300>' : 'URController/Subsystem/Control System/PID Controller9/Sum Fdbk/Disabled'
//  '<S301>' : 'URController/Subsystem/Control System/PID Controller9/Tracking Mode/Disabled'
//  '<S302>' : 'URController/Subsystem/Control System/PID Controller9/Tracking Mode Sum/Passthrough'
//  '<S303>' : 'URController/Subsystem/Control System/PID Controller9/Tsamp - Integral/TsSignalSpecification'
//  '<S304>' : 'URController/Subsystem/Control System/PID Controller9/Tsamp - Ngain/Passthrough'
//  '<S305>' : 'URController/Subsystem/Control System/PID Controller9/postSat Signal/Forward_Path'
//  '<S306>' : 'URController/Subsystem/Control System/PID Controller9/preSat Signal/Forward_Path'
//  '<S307>' : 'URController/Subsystem/Control System/motionGenerator1/MATLAB Function'
//  '<S308>' : 'URController/Subsystem/Control System/motionGenerator1/MATLAB Function1'
//  '<S309>' : 'URController/Subsystem/Control System/motionGenerator2/MATLAB Function'
//  '<S310>' : 'URController/Subsystem/Control System/motionGenerator2/MATLAB Function1'
//  '<S311>' : 'URController/Subsystem/Control System/motionGenerator3/MATLAB Function'
//  '<S312>' : 'URController/Subsystem/Control System/motionGenerator3/MATLAB Function1'
//  '<S313>' : 'URController/Subsystem/Control System/motionGenerator4/MATLAB Function'
//  '<S314>' : 'URController/Subsystem/Control System/motionGenerator4/MATLAB Function1'
//  '<S315>' : 'URController/Subsystem/Control System/motionGenerator5/MATLAB Function'
//  '<S316>' : 'URController/Subsystem/Control System/motionGenerator5/MATLAB Function1'
//  '<S317>' : 'URController/Subsystem/Control System/motionGenerator7/MATLAB Function'
//  '<S318>' : 'URController/Subsystem/Control System/motionGenerator7/MATLAB Function1'
//  '<S319>' : 'URController/Subsystem/Kinematic calculator/MATLAB Function'
//  '<S320>' : 'URController/Subsystem/Kinematic calculator/MATLAB Function1'
//  '<S321>' : 'URController/Subsystem/Kinematic calculator/MATLAB Function2'
//  '<S322>' : 'URController/forwardkinematics1/MATLAB Function'

#endif                                 // RTW_HEADER_URController_h_

//
// File trailer for generated code.
//
// [EOF]
//
