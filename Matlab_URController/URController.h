//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: URController.h
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
  // Block signals (default storage)
  struct B {
    real_T FilterCoefficient;          // '<S43>/Filter Coefficient'
    real_T Sum;                        // '<S49>/Sum'
    real_T IntegralGain;               // '<S37>/Integral Gain'
    real_T FilterCoefficient_c;        // '<S235>/Filter Coefficient'
    real_T Sum_l;                      // '<S241>/Sum'
    real_T IntegralGain_h;             // '<S229>/Integral Gain'
    real_T FilterCoefficient_n;        // '<S283>/Filter Coefficient'
    real_T Sum_e;                      // '<S289>/Sum'
    real_T IntegralGain_k;             // '<S277>/Integral Gain'
    real_T FilterCoefficient_f;        // '<S187>/Filter Coefficient'
    real_T Sum_a;                      // '<S193>/Sum'
    real_T IntegralGain_j;             // '<S181>/Integral Gain'
    real_T FilterCoefficient_n4;       // '<S139>/Filter Coefficient'
    real_T Sum_j;                      // '<S145>/Sum'
    real_T IntegralGain_g;             // '<S133>/Integral Gain'
    real_T FilterCoefficient_l;        // '<S91>/Filter Coefficient'
    real_T Sum_m;                      // '<S97>/Sum'
    real_T IntegralGain_p;             // '<S85>/Integral Gain'
  };

  // Continuous states (default storage)
  struct X {
    real_T TransferFcn1_CSTATE[3];     // '<S1>/Transfer Fcn1'
    real_T Filter_CSTATE;              // '<S35>/Filter'
    real_T Integrator_CSTATE;          // '<S40>/Integrator'
    real_T TransferFcn2_CSTATE[3];     // '<S1>/Transfer Fcn2'
    real_T TransferFcn3_CSTATE[3];     // '<S1>/Transfer Fcn3'
    real_T TransferFcn5_CSTATE[3];     // '<S1>/Transfer Fcn5'
    real_T TransferFcn4_CSTATE[3];     // '<S1>/Transfer Fcn4'
    real_T TransferFcn6_CSTATE[3];     // '<S1>/Transfer Fcn6'
    real_T Filter_CSTATE_g;            // '<S227>/Filter'
    real_T Integrator_CSTATE_l;        // '<S232>/Integrator'
    real_T Filter_CSTATE_b;            // '<S275>/Filter'
    real_T Integrator_CSTATE_o;        // '<S280>/Integrator'
    real_T Filter_CSTATE_o;            // '<S179>/Filter'
    real_T Integrator_CSTATE_f;        // '<S184>/Integrator'
    real_T Filter_CSTATE_b0;           // '<S131>/Filter'
    real_T Integrator_CSTATE_ot;       // '<S136>/Integrator'
    real_T Filter_CSTATE_p;            // '<S83>/Filter'
    real_T Integrator_CSTATE_j;        // '<S88>/Integrator'
  };

  // State derivatives (default storage)
  struct XDot {
    real_T TransferFcn1_CSTATE[3];     // '<S1>/Transfer Fcn1'
    real_T Filter_CSTATE;              // '<S35>/Filter'
    real_T Integrator_CSTATE;          // '<S40>/Integrator'
    real_T TransferFcn2_CSTATE[3];     // '<S1>/Transfer Fcn2'
    real_T TransferFcn3_CSTATE[3];     // '<S1>/Transfer Fcn3'
    real_T TransferFcn5_CSTATE[3];     // '<S1>/Transfer Fcn5'
    real_T TransferFcn4_CSTATE[3];     // '<S1>/Transfer Fcn4'
    real_T TransferFcn6_CSTATE[3];     // '<S1>/Transfer Fcn6'
    real_T Filter_CSTATE_g;            // '<S227>/Filter'
    real_T Integrator_CSTATE_l;        // '<S232>/Integrator'
    real_T Filter_CSTATE_b;            // '<S275>/Filter'
    real_T Integrator_CSTATE_o;        // '<S280>/Integrator'
    real_T Filter_CSTATE_o;            // '<S179>/Filter'
    real_T Integrator_CSTATE_f;        // '<S184>/Integrator'
    real_T Filter_CSTATE_b0;           // '<S131>/Filter'
    real_T Integrator_CSTATE_ot;       // '<S136>/Integrator'
    real_T Filter_CSTATE_p;            // '<S83>/Filter'
    real_T Integrator_CSTATE_j;        // '<S88>/Integrator'
  };

  // State disabled
  struct XDis {
    boolean_T TransferFcn1_CSTATE[3];  // '<S1>/Transfer Fcn1'
    boolean_T Filter_CSTATE;           // '<S35>/Filter'
    boolean_T Integrator_CSTATE;       // '<S40>/Integrator'
    boolean_T TransferFcn2_CSTATE[3];  // '<S1>/Transfer Fcn2'
    boolean_T TransferFcn3_CSTATE[3];  // '<S1>/Transfer Fcn3'
    boolean_T TransferFcn5_CSTATE[3];  // '<S1>/Transfer Fcn5'
    boolean_T TransferFcn4_CSTATE[3];  // '<S1>/Transfer Fcn4'
    boolean_T TransferFcn6_CSTATE[3];  // '<S1>/Transfer Fcn6'
    boolean_T Filter_CSTATE_g;         // '<S227>/Filter'
    boolean_T Integrator_CSTATE_l;     // '<S232>/Integrator'
    boolean_T Filter_CSTATE_b;         // '<S275>/Filter'
    boolean_T Integrator_CSTATE_o;     // '<S280>/Integrator'
    boolean_T Filter_CSTATE_o;         // '<S179>/Filter'
    boolean_T Integrator_CSTATE_f;     // '<S184>/Integrator'
    boolean_T Filter_CSTATE_b0;        // '<S131>/Filter'
    boolean_T Integrator_CSTATE_ot;    // '<S136>/Integrator'
    boolean_T Filter_CSTATE_p;         // '<S83>/Filter'
    boolean_T Integrator_CSTATE_j;     // '<S88>/Integrator'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T ori_theta_arr[6];           // '<Root>/ori_theta_arr'
    real_T desire_pos_orient_arr[6];   // '<Root>/desire_pos_orient_arr'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T actual_theta_arr[6];        // '<Root>/actual_theta_arr'
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

  // Block continuous states
  X rtX;

  // private member function(s) for subsystem '<Root>'
  void inv(const real_T x[16], real_T y[16]);
  real_T norm(const real_T x[4]);

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
//  '<S1>'   : 'URController/Control System'
//  '<S2>'   : 'URController/Kinematic calculator'
//  '<S3>'   : 'URController/Control System/PID Controller1'
//  '<S4>'   : 'URController/Control System/PID Controller2'
//  '<S5>'   : 'URController/Control System/PID Controller3'
//  '<S6>'   : 'URController/Control System/PID Controller4'
//  '<S7>'   : 'URController/Control System/PID Controller5'
//  '<S8>'   : 'URController/Control System/PID Controller6'
//  '<S9>'   : 'URController/Control System/PID Controller1/Anti-windup'
//  '<S10>'  : 'URController/Control System/PID Controller1/D Gain'
//  '<S11>'  : 'URController/Control System/PID Controller1/Filter'
//  '<S12>'  : 'URController/Control System/PID Controller1/Filter ICs'
//  '<S13>'  : 'URController/Control System/PID Controller1/I Gain'
//  '<S14>'  : 'URController/Control System/PID Controller1/Ideal P Gain'
//  '<S15>'  : 'URController/Control System/PID Controller1/Ideal P Gain Fdbk'
//  '<S16>'  : 'URController/Control System/PID Controller1/Integrator'
//  '<S17>'  : 'URController/Control System/PID Controller1/Integrator ICs'
//  '<S18>'  : 'URController/Control System/PID Controller1/N Copy'
//  '<S19>'  : 'URController/Control System/PID Controller1/N Gain'
//  '<S20>'  : 'URController/Control System/PID Controller1/P Copy'
//  '<S21>'  : 'URController/Control System/PID Controller1/Parallel P Gain'
//  '<S22>'  : 'URController/Control System/PID Controller1/Reset Signal'
//  '<S23>'  : 'URController/Control System/PID Controller1/Saturation'
//  '<S24>'  : 'URController/Control System/PID Controller1/Saturation Fdbk'
//  '<S25>'  : 'URController/Control System/PID Controller1/Sum'
//  '<S26>'  : 'URController/Control System/PID Controller1/Sum Fdbk'
//  '<S27>'  : 'URController/Control System/PID Controller1/Tracking Mode'
//  '<S28>'  : 'URController/Control System/PID Controller1/Tracking Mode Sum'
//  '<S29>'  : 'URController/Control System/PID Controller1/Tsamp - Integral'
//  '<S30>'  : 'URController/Control System/PID Controller1/Tsamp - Ngain'
//  '<S31>'  : 'URController/Control System/PID Controller1/postSat Signal'
//  '<S32>'  : 'URController/Control System/PID Controller1/preSat Signal'
//  '<S33>'  : 'URController/Control System/PID Controller1/Anti-windup/Passthrough'
//  '<S34>'  : 'URController/Control System/PID Controller1/D Gain/Internal Parameters'
//  '<S35>'  : 'URController/Control System/PID Controller1/Filter/Cont. Filter'
//  '<S36>'  : 'URController/Control System/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S37>'  : 'URController/Control System/PID Controller1/I Gain/Internal Parameters'
//  '<S38>'  : 'URController/Control System/PID Controller1/Ideal P Gain/Passthrough'
//  '<S39>'  : 'URController/Control System/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S40>'  : 'URController/Control System/PID Controller1/Integrator/Continuous'
//  '<S41>'  : 'URController/Control System/PID Controller1/Integrator ICs/Internal IC'
//  '<S42>'  : 'URController/Control System/PID Controller1/N Copy/Disabled'
//  '<S43>'  : 'URController/Control System/PID Controller1/N Gain/Internal Parameters'
//  '<S44>'  : 'URController/Control System/PID Controller1/P Copy/Disabled'
//  '<S45>'  : 'URController/Control System/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S46>'  : 'URController/Control System/PID Controller1/Reset Signal/Disabled'
//  '<S47>'  : 'URController/Control System/PID Controller1/Saturation/Passthrough'
//  '<S48>'  : 'URController/Control System/PID Controller1/Saturation Fdbk/Disabled'
//  '<S49>'  : 'URController/Control System/PID Controller1/Sum/Sum_PID'
//  '<S50>'  : 'URController/Control System/PID Controller1/Sum Fdbk/Disabled'
//  '<S51>'  : 'URController/Control System/PID Controller1/Tracking Mode/Disabled'
//  '<S52>'  : 'URController/Control System/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S53>'  : 'URController/Control System/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S54>'  : 'URController/Control System/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S55>'  : 'URController/Control System/PID Controller1/postSat Signal/Forward_Path'
//  '<S56>'  : 'URController/Control System/PID Controller1/preSat Signal/Forward_Path'
//  '<S57>'  : 'URController/Control System/PID Controller2/Anti-windup'
//  '<S58>'  : 'URController/Control System/PID Controller2/D Gain'
//  '<S59>'  : 'URController/Control System/PID Controller2/Filter'
//  '<S60>'  : 'URController/Control System/PID Controller2/Filter ICs'
//  '<S61>'  : 'URController/Control System/PID Controller2/I Gain'
//  '<S62>'  : 'URController/Control System/PID Controller2/Ideal P Gain'
//  '<S63>'  : 'URController/Control System/PID Controller2/Ideal P Gain Fdbk'
//  '<S64>'  : 'URController/Control System/PID Controller2/Integrator'
//  '<S65>'  : 'URController/Control System/PID Controller2/Integrator ICs'
//  '<S66>'  : 'URController/Control System/PID Controller2/N Copy'
//  '<S67>'  : 'URController/Control System/PID Controller2/N Gain'
//  '<S68>'  : 'URController/Control System/PID Controller2/P Copy'
//  '<S69>'  : 'URController/Control System/PID Controller2/Parallel P Gain'
//  '<S70>'  : 'URController/Control System/PID Controller2/Reset Signal'
//  '<S71>'  : 'URController/Control System/PID Controller2/Saturation'
//  '<S72>'  : 'URController/Control System/PID Controller2/Saturation Fdbk'
//  '<S73>'  : 'URController/Control System/PID Controller2/Sum'
//  '<S74>'  : 'URController/Control System/PID Controller2/Sum Fdbk'
//  '<S75>'  : 'URController/Control System/PID Controller2/Tracking Mode'
//  '<S76>'  : 'URController/Control System/PID Controller2/Tracking Mode Sum'
//  '<S77>'  : 'URController/Control System/PID Controller2/Tsamp - Integral'
//  '<S78>'  : 'URController/Control System/PID Controller2/Tsamp - Ngain'
//  '<S79>'  : 'URController/Control System/PID Controller2/postSat Signal'
//  '<S80>'  : 'URController/Control System/PID Controller2/preSat Signal'
//  '<S81>'  : 'URController/Control System/PID Controller2/Anti-windup/Passthrough'
//  '<S82>'  : 'URController/Control System/PID Controller2/D Gain/Internal Parameters'
//  '<S83>'  : 'URController/Control System/PID Controller2/Filter/Cont. Filter'
//  '<S84>'  : 'URController/Control System/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S85>'  : 'URController/Control System/PID Controller2/I Gain/Internal Parameters'
//  '<S86>'  : 'URController/Control System/PID Controller2/Ideal P Gain/Passthrough'
//  '<S87>'  : 'URController/Control System/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S88>'  : 'URController/Control System/PID Controller2/Integrator/Continuous'
//  '<S89>'  : 'URController/Control System/PID Controller2/Integrator ICs/Internal IC'
//  '<S90>'  : 'URController/Control System/PID Controller2/N Copy/Disabled'
//  '<S91>'  : 'URController/Control System/PID Controller2/N Gain/Internal Parameters'
//  '<S92>'  : 'URController/Control System/PID Controller2/P Copy/Disabled'
//  '<S93>'  : 'URController/Control System/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S94>'  : 'URController/Control System/PID Controller2/Reset Signal/Disabled'
//  '<S95>'  : 'URController/Control System/PID Controller2/Saturation/Passthrough'
//  '<S96>'  : 'URController/Control System/PID Controller2/Saturation Fdbk/Disabled'
//  '<S97>'  : 'URController/Control System/PID Controller2/Sum/Sum_PID'
//  '<S98>'  : 'URController/Control System/PID Controller2/Sum Fdbk/Disabled'
//  '<S99>'  : 'URController/Control System/PID Controller2/Tracking Mode/Disabled'
//  '<S100>' : 'URController/Control System/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S101>' : 'URController/Control System/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S102>' : 'URController/Control System/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S103>' : 'URController/Control System/PID Controller2/postSat Signal/Forward_Path'
//  '<S104>' : 'URController/Control System/PID Controller2/preSat Signal/Forward_Path'
//  '<S105>' : 'URController/Control System/PID Controller3/Anti-windup'
//  '<S106>' : 'URController/Control System/PID Controller3/D Gain'
//  '<S107>' : 'URController/Control System/PID Controller3/Filter'
//  '<S108>' : 'URController/Control System/PID Controller3/Filter ICs'
//  '<S109>' : 'URController/Control System/PID Controller3/I Gain'
//  '<S110>' : 'URController/Control System/PID Controller3/Ideal P Gain'
//  '<S111>' : 'URController/Control System/PID Controller3/Ideal P Gain Fdbk'
//  '<S112>' : 'URController/Control System/PID Controller3/Integrator'
//  '<S113>' : 'URController/Control System/PID Controller3/Integrator ICs'
//  '<S114>' : 'URController/Control System/PID Controller3/N Copy'
//  '<S115>' : 'URController/Control System/PID Controller3/N Gain'
//  '<S116>' : 'URController/Control System/PID Controller3/P Copy'
//  '<S117>' : 'URController/Control System/PID Controller3/Parallel P Gain'
//  '<S118>' : 'URController/Control System/PID Controller3/Reset Signal'
//  '<S119>' : 'URController/Control System/PID Controller3/Saturation'
//  '<S120>' : 'URController/Control System/PID Controller3/Saturation Fdbk'
//  '<S121>' : 'URController/Control System/PID Controller3/Sum'
//  '<S122>' : 'URController/Control System/PID Controller3/Sum Fdbk'
//  '<S123>' : 'URController/Control System/PID Controller3/Tracking Mode'
//  '<S124>' : 'URController/Control System/PID Controller3/Tracking Mode Sum'
//  '<S125>' : 'URController/Control System/PID Controller3/Tsamp - Integral'
//  '<S126>' : 'URController/Control System/PID Controller3/Tsamp - Ngain'
//  '<S127>' : 'URController/Control System/PID Controller3/postSat Signal'
//  '<S128>' : 'URController/Control System/PID Controller3/preSat Signal'
//  '<S129>' : 'URController/Control System/PID Controller3/Anti-windup/Passthrough'
//  '<S130>' : 'URController/Control System/PID Controller3/D Gain/Internal Parameters'
//  '<S131>' : 'URController/Control System/PID Controller3/Filter/Cont. Filter'
//  '<S132>' : 'URController/Control System/PID Controller3/Filter ICs/Internal IC - Filter'
//  '<S133>' : 'URController/Control System/PID Controller3/I Gain/Internal Parameters'
//  '<S134>' : 'URController/Control System/PID Controller3/Ideal P Gain/Passthrough'
//  '<S135>' : 'URController/Control System/PID Controller3/Ideal P Gain Fdbk/Disabled'
//  '<S136>' : 'URController/Control System/PID Controller3/Integrator/Continuous'
//  '<S137>' : 'URController/Control System/PID Controller3/Integrator ICs/Internal IC'
//  '<S138>' : 'URController/Control System/PID Controller3/N Copy/Disabled'
//  '<S139>' : 'URController/Control System/PID Controller3/N Gain/Internal Parameters'
//  '<S140>' : 'URController/Control System/PID Controller3/P Copy/Disabled'
//  '<S141>' : 'URController/Control System/PID Controller3/Parallel P Gain/Internal Parameters'
//  '<S142>' : 'URController/Control System/PID Controller3/Reset Signal/Disabled'
//  '<S143>' : 'URController/Control System/PID Controller3/Saturation/Passthrough'
//  '<S144>' : 'URController/Control System/PID Controller3/Saturation Fdbk/Disabled'
//  '<S145>' : 'URController/Control System/PID Controller3/Sum/Sum_PID'
//  '<S146>' : 'URController/Control System/PID Controller3/Sum Fdbk/Disabled'
//  '<S147>' : 'URController/Control System/PID Controller3/Tracking Mode/Disabled'
//  '<S148>' : 'URController/Control System/PID Controller3/Tracking Mode Sum/Passthrough'
//  '<S149>' : 'URController/Control System/PID Controller3/Tsamp - Integral/TsSignalSpecification'
//  '<S150>' : 'URController/Control System/PID Controller3/Tsamp - Ngain/Passthrough'
//  '<S151>' : 'URController/Control System/PID Controller3/postSat Signal/Forward_Path'
//  '<S152>' : 'URController/Control System/PID Controller3/preSat Signal/Forward_Path'
//  '<S153>' : 'URController/Control System/PID Controller4/Anti-windup'
//  '<S154>' : 'URController/Control System/PID Controller4/D Gain'
//  '<S155>' : 'URController/Control System/PID Controller4/Filter'
//  '<S156>' : 'URController/Control System/PID Controller4/Filter ICs'
//  '<S157>' : 'URController/Control System/PID Controller4/I Gain'
//  '<S158>' : 'URController/Control System/PID Controller4/Ideal P Gain'
//  '<S159>' : 'URController/Control System/PID Controller4/Ideal P Gain Fdbk'
//  '<S160>' : 'URController/Control System/PID Controller4/Integrator'
//  '<S161>' : 'URController/Control System/PID Controller4/Integrator ICs'
//  '<S162>' : 'URController/Control System/PID Controller4/N Copy'
//  '<S163>' : 'URController/Control System/PID Controller4/N Gain'
//  '<S164>' : 'URController/Control System/PID Controller4/P Copy'
//  '<S165>' : 'URController/Control System/PID Controller4/Parallel P Gain'
//  '<S166>' : 'URController/Control System/PID Controller4/Reset Signal'
//  '<S167>' : 'URController/Control System/PID Controller4/Saturation'
//  '<S168>' : 'URController/Control System/PID Controller4/Saturation Fdbk'
//  '<S169>' : 'URController/Control System/PID Controller4/Sum'
//  '<S170>' : 'URController/Control System/PID Controller4/Sum Fdbk'
//  '<S171>' : 'URController/Control System/PID Controller4/Tracking Mode'
//  '<S172>' : 'URController/Control System/PID Controller4/Tracking Mode Sum'
//  '<S173>' : 'URController/Control System/PID Controller4/Tsamp - Integral'
//  '<S174>' : 'URController/Control System/PID Controller4/Tsamp - Ngain'
//  '<S175>' : 'URController/Control System/PID Controller4/postSat Signal'
//  '<S176>' : 'URController/Control System/PID Controller4/preSat Signal'
//  '<S177>' : 'URController/Control System/PID Controller4/Anti-windup/Passthrough'
//  '<S178>' : 'URController/Control System/PID Controller4/D Gain/Internal Parameters'
//  '<S179>' : 'URController/Control System/PID Controller4/Filter/Cont. Filter'
//  '<S180>' : 'URController/Control System/PID Controller4/Filter ICs/Internal IC - Filter'
//  '<S181>' : 'URController/Control System/PID Controller4/I Gain/Internal Parameters'
//  '<S182>' : 'URController/Control System/PID Controller4/Ideal P Gain/Passthrough'
//  '<S183>' : 'URController/Control System/PID Controller4/Ideal P Gain Fdbk/Disabled'
//  '<S184>' : 'URController/Control System/PID Controller4/Integrator/Continuous'
//  '<S185>' : 'URController/Control System/PID Controller4/Integrator ICs/Internal IC'
//  '<S186>' : 'URController/Control System/PID Controller4/N Copy/Disabled'
//  '<S187>' : 'URController/Control System/PID Controller4/N Gain/Internal Parameters'
//  '<S188>' : 'URController/Control System/PID Controller4/P Copy/Disabled'
//  '<S189>' : 'URController/Control System/PID Controller4/Parallel P Gain/Internal Parameters'
//  '<S190>' : 'URController/Control System/PID Controller4/Reset Signal/Disabled'
//  '<S191>' : 'URController/Control System/PID Controller4/Saturation/Passthrough'
//  '<S192>' : 'URController/Control System/PID Controller4/Saturation Fdbk/Disabled'
//  '<S193>' : 'URController/Control System/PID Controller4/Sum/Sum_PID'
//  '<S194>' : 'URController/Control System/PID Controller4/Sum Fdbk/Disabled'
//  '<S195>' : 'URController/Control System/PID Controller4/Tracking Mode/Disabled'
//  '<S196>' : 'URController/Control System/PID Controller4/Tracking Mode Sum/Passthrough'
//  '<S197>' : 'URController/Control System/PID Controller4/Tsamp - Integral/TsSignalSpecification'
//  '<S198>' : 'URController/Control System/PID Controller4/Tsamp - Ngain/Passthrough'
//  '<S199>' : 'URController/Control System/PID Controller4/postSat Signal/Forward_Path'
//  '<S200>' : 'URController/Control System/PID Controller4/preSat Signal/Forward_Path'
//  '<S201>' : 'URController/Control System/PID Controller5/Anti-windup'
//  '<S202>' : 'URController/Control System/PID Controller5/D Gain'
//  '<S203>' : 'URController/Control System/PID Controller5/Filter'
//  '<S204>' : 'URController/Control System/PID Controller5/Filter ICs'
//  '<S205>' : 'URController/Control System/PID Controller5/I Gain'
//  '<S206>' : 'URController/Control System/PID Controller5/Ideal P Gain'
//  '<S207>' : 'URController/Control System/PID Controller5/Ideal P Gain Fdbk'
//  '<S208>' : 'URController/Control System/PID Controller5/Integrator'
//  '<S209>' : 'URController/Control System/PID Controller5/Integrator ICs'
//  '<S210>' : 'URController/Control System/PID Controller5/N Copy'
//  '<S211>' : 'URController/Control System/PID Controller5/N Gain'
//  '<S212>' : 'URController/Control System/PID Controller5/P Copy'
//  '<S213>' : 'URController/Control System/PID Controller5/Parallel P Gain'
//  '<S214>' : 'URController/Control System/PID Controller5/Reset Signal'
//  '<S215>' : 'URController/Control System/PID Controller5/Saturation'
//  '<S216>' : 'URController/Control System/PID Controller5/Saturation Fdbk'
//  '<S217>' : 'URController/Control System/PID Controller5/Sum'
//  '<S218>' : 'URController/Control System/PID Controller5/Sum Fdbk'
//  '<S219>' : 'URController/Control System/PID Controller5/Tracking Mode'
//  '<S220>' : 'URController/Control System/PID Controller5/Tracking Mode Sum'
//  '<S221>' : 'URController/Control System/PID Controller5/Tsamp - Integral'
//  '<S222>' : 'URController/Control System/PID Controller5/Tsamp - Ngain'
//  '<S223>' : 'URController/Control System/PID Controller5/postSat Signal'
//  '<S224>' : 'URController/Control System/PID Controller5/preSat Signal'
//  '<S225>' : 'URController/Control System/PID Controller5/Anti-windup/Passthrough'
//  '<S226>' : 'URController/Control System/PID Controller5/D Gain/Internal Parameters'
//  '<S227>' : 'URController/Control System/PID Controller5/Filter/Cont. Filter'
//  '<S228>' : 'URController/Control System/PID Controller5/Filter ICs/Internal IC - Filter'
//  '<S229>' : 'URController/Control System/PID Controller5/I Gain/Internal Parameters'
//  '<S230>' : 'URController/Control System/PID Controller5/Ideal P Gain/Passthrough'
//  '<S231>' : 'URController/Control System/PID Controller5/Ideal P Gain Fdbk/Disabled'
//  '<S232>' : 'URController/Control System/PID Controller5/Integrator/Continuous'
//  '<S233>' : 'URController/Control System/PID Controller5/Integrator ICs/Internal IC'
//  '<S234>' : 'URController/Control System/PID Controller5/N Copy/Disabled'
//  '<S235>' : 'URController/Control System/PID Controller5/N Gain/Internal Parameters'
//  '<S236>' : 'URController/Control System/PID Controller5/P Copy/Disabled'
//  '<S237>' : 'URController/Control System/PID Controller5/Parallel P Gain/Internal Parameters'
//  '<S238>' : 'URController/Control System/PID Controller5/Reset Signal/Disabled'
//  '<S239>' : 'URController/Control System/PID Controller5/Saturation/Passthrough'
//  '<S240>' : 'URController/Control System/PID Controller5/Saturation Fdbk/Disabled'
//  '<S241>' : 'URController/Control System/PID Controller5/Sum/Sum_PID'
//  '<S242>' : 'URController/Control System/PID Controller5/Sum Fdbk/Disabled'
//  '<S243>' : 'URController/Control System/PID Controller5/Tracking Mode/Disabled'
//  '<S244>' : 'URController/Control System/PID Controller5/Tracking Mode Sum/Passthrough'
//  '<S245>' : 'URController/Control System/PID Controller5/Tsamp - Integral/TsSignalSpecification'
//  '<S246>' : 'URController/Control System/PID Controller5/Tsamp - Ngain/Passthrough'
//  '<S247>' : 'URController/Control System/PID Controller5/postSat Signal/Forward_Path'
//  '<S248>' : 'URController/Control System/PID Controller5/preSat Signal/Forward_Path'
//  '<S249>' : 'URController/Control System/PID Controller6/Anti-windup'
//  '<S250>' : 'URController/Control System/PID Controller6/D Gain'
//  '<S251>' : 'URController/Control System/PID Controller6/Filter'
//  '<S252>' : 'URController/Control System/PID Controller6/Filter ICs'
//  '<S253>' : 'URController/Control System/PID Controller6/I Gain'
//  '<S254>' : 'URController/Control System/PID Controller6/Ideal P Gain'
//  '<S255>' : 'URController/Control System/PID Controller6/Ideal P Gain Fdbk'
//  '<S256>' : 'URController/Control System/PID Controller6/Integrator'
//  '<S257>' : 'URController/Control System/PID Controller6/Integrator ICs'
//  '<S258>' : 'URController/Control System/PID Controller6/N Copy'
//  '<S259>' : 'URController/Control System/PID Controller6/N Gain'
//  '<S260>' : 'URController/Control System/PID Controller6/P Copy'
//  '<S261>' : 'URController/Control System/PID Controller6/Parallel P Gain'
//  '<S262>' : 'URController/Control System/PID Controller6/Reset Signal'
//  '<S263>' : 'URController/Control System/PID Controller6/Saturation'
//  '<S264>' : 'URController/Control System/PID Controller6/Saturation Fdbk'
//  '<S265>' : 'URController/Control System/PID Controller6/Sum'
//  '<S266>' : 'URController/Control System/PID Controller6/Sum Fdbk'
//  '<S267>' : 'URController/Control System/PID Controller6/Tracking Mode'
//  '<S268>' : 'URController/Control System/PID Controller6/Tracking Mode Sum'
//  '<S269>' : 'URController/Control System/PID Controller6/Tsamp - Integral'
//  '<S270>' : 'URController/Control System/PID Controller6/Tsamp - Ngain'
//  '<S271>' : 'URController/Control System/PID Controller6/postSat Signal'
//  '<S272>' : 'URController/Control System/PID Controller6/preSat Signal'
//  '<S273>' : 'URController/Control System/PID Controller6/Anti-windup/Passthrough'
//  '<S274>' : 'URController/Control System/PID Controller6/D Gain/Internal Parameters'
//  '<S275>' : 'URController/Control System/PID Controller6/Filter/Cont. Filter'
//  '<S276>' : 'URController/Control System/PID Controller6/Filter ICs/Internal IC - Filter'
//  '<S277>' : 'URController/Control System/PID Controller6/I Gain/Internal Parameters'
//  '<S278>' : 'URController/Control System/PID Controller6/Ideal P Gain/Passthrough'
//  '<S279>' : 'URController/Control System/PID Controller6/Ideal P Gain Fdbk/Disabled'
//  '<S280>' : 'URController/Control System/PID Controller6/Integrator/Continuous'
//  '<S281>' : 'URController/Control System/PID Controller6/Integrator ICs/Internal IC'
//  '<S282>' : 'URController/Control System/PID Controller6/N Copy/Disabled'
//  '<S283>' : 'URController/Control System/PID Controller6/N Gain/Internal Parameters'
//  '<S284>' : 'URController/Control System/PID Controller6/P Copy/Disabled'
//  '<S285>' : 'URController/Control System/PID Controller6/Parallel P Gain/Internal Parameters'
//  '<S286>' : 'URController/Control System/PID Controller6/Reset Signal/Disabled'
//  '<S287>' : 'URController/Control System/PID Controller6/Saturation/Passthrough'
//  '<S288>' : 'URController/Control System/PID Controller6/Saturation Fdbk/Disabled'
//  '<S289>' : 'URController/Control System/PID Controller6/Sum/Sum_PID'
//  '<S290>' : 'URController/Control System/PID Controller6/Sum Fdbk/Disabled'
//  '<S291>' : 'URController/Control System/PID Controller6/Tracking Mode/Disabled'
//  '<S292>' : 'URController/Control System/PID Controller6/Tracking Mode Sum/Passthrough'
//  '<S293>' : 'URController/Control System/PID Controller6/Tsamp - Integral/TsSignalSpecification'
//  '<S294>' : 'URController/Control System/PID Controller6/Tsamp - Ngain/Passthrough'
//  '<S295>' : 'URController/Control System/PID Controller6/postSat Signal/Forward_Path'
//  '<S296>' : 'URController/Control System/PID Controller6/preSat Signal/Forward_Path'
//  '<S297>' : 'URController/Kinematic calculator/MATLAB Function'
//  '<S298>' : 'URController/Kinematic calculator/MATLAB Function1'
//  '<S299>' : 'URController/Kinematic calculator/MATLAB Function2'

#endif                                 // RTW_HEADER_URController_h_

//
// File trailer for generated code.
//
// [EOF]
//
