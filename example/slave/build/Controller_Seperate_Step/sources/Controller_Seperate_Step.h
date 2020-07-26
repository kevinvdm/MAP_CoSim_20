/*
 * Controller_Seperate_Step.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Controller_Seperate_Step".
 *
 * Model version              : 1.2
 * Simulink Coder version : 9.3 (R2020a) 18-Nov-2019
 * C source code generated on : Sat Jul 18 15:15:21 2020
 *
 * Target selection: grtfmi.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Controller_Seperate_Step_h_
#define RTW_HEADER_Controller_Seperate_Step_h_
#include <stddef.h>
#include <string.h>
#ifndef Controller_Seperate_Step_COMMON_INCLUDES_
# define Controller_Seperate_Step_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                           /* Controller_Seperate_Step_COMMON_INCLUDES_ */

#include "Controller_Seperate_Step_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->blockIO = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->dwork = (val))
#endif

#ifndef rtmGetU
# define rtmGetU(rtm)                  ((rtm)->inputs)
#endif

#ifndef rtmSetU
# define rtmSetU(rtm, val)             ((rtm)->inputs = (val))
#endif

#ifndef rtmGetY
# define rtmGetY(rtm)                  ((rtm)->outputs)
#endif

#ifndef rtmSetY
# define rtmSetY(rtm, val)             ((rtm)->outputs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#define Controller_Seperate_Step_M_TYPE RT_MODEL_Controller_Seperate__T

/* Block signals (default storage) */
typedef struct {
  real_T Sum;                          /* '<Root>/Sum' */
} B_Controller_Seperate_Step_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S33>/Integrator' */
  real_T Filter_DSTATE;                /* '<S28>/Filter' */
} DW_Controller_Seperate_Step_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Velocity;                     /* '<Root>/Velocity' */
} ExtU_Controller_Seperate_Step_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Throttle;                     /* '<Root>/Throttle' */
  real_T Vdesired;                     /* '<Root>/Vdesired' */
} ExtY_Controller_Seperate_Step_T;

/* Parameters (default storage) */
struct P_Controller_Seperate_Step_T_ {
  real_T PIDController2_D;             /* Mask Parameter: PIDController2_D
                                        * Referenced by: '<S27>/Derivative Gain'
                                        */
  real_T PIDController2_I;             /* Mask Parameter: PIDController2_I
                                        * Referenced by: '<S30>/Integral Gain'
                                        */
  real_T PIDController2_InitialCondition;
                              /* Mask Parameter: PIDController2_InitialCondition
                               * Referenced by: '<S28>/Filter'
                               */
  real_T PIDController2_InitialConditi_j;
                              /* Mask Parameter: PIDController2_InitialConditi_j
                               * Referenced by: '<S33>/Integrator'
                               */
  real_T PIDController2_LowerSaturationL;
                              /* Mask Parameter: PIDController2_LowerSaturationL
                               * Referenced by: '<S40>/Saturation'
                               */
  real_T PIDController2_N;             /* Mask Parameter: PIDController2_N
                                        * Referenced by: '<S36>/Filter Coefficient'
                                        */
  real_T PIDController2_P;             /* Mask Parameter: PIDController2_P
                                        * Referenced by: '<S38>/Proportional Gain'
                                        */
  real_T PIDController2_UpperSaturationL;
                              /* Mask Parameter: PIDController2_UpperSaturationL
                               * Referenced by: '<S40>/Saturation'
                               */
  real_T Step_Time;                    /* Expression: 1
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Step_Y0;                      /* Expression: 0
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Step_YFinal;                  /* Expression: 1
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S33>/Integrator'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S28>/Filter'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Controller_Seperate_S_T {
  const char_T *errorStatus;
  RTWSolverInfo *solverInfo;
  B_Controller_Seperate_Step_T *blockIO;
  ExtU_Controller_Seperate_Step_T *inputs;
  ExtY_Controller_Seperate_Step_T *outputs;
  DW_Controller_Seperate_Step_T *dwork;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_Controller_Seperate_Step_T Controller_Seperate_Step_P;

/* External data declarations for dependent source files */
extern const char *RT_MEMORY_ALLOCATION_ERROR;
extern P_Controller_Seperate_Step_T Controller_Seperate_Step_P;/* parameters */

/* Model entry point functions */
extern RT_MODEL_Controller_Seperate__T *Controller_Seperate_Step(void);
extern void Controller_Seperate_Step_initialize(RT_MODEL_Controller_Seperate__T *
  const Controller_Seperate_Step_M);
extern void Controller_Seperate_Step_step(RT_MODEL_Controller_Seperate__T *const
  Controller_Seperate_Step_M);
extern void Controller_Seperate_Step_terminate(RT_MODEL_Controller_Seperate__T *
  Controller_Seperate_Step_M);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Controller_Seperate_Step'
 * '<S1>'   : 'Controller_Seperate_Step/PID Controller2'
 * '<S2>'   : 'Controller_Seperate_Step/PID Controller2/Anti-windup'
 * '<S3>'   : 'Controller_Seperate_Step/PID Controller2/D Gain'
 * '<S4>'   : 'Controller_Seperate_Step/PID Controller2/Filter'
 * '<S5>'   : 'Controller_Seperate_Step/PID Controller2/Filter ICs'
 * '<S6>'   : 'Controller_Seperate_Step/PID Controller2/I Gain'
 * '<S7>'   : 'Controller_Seperate_Step/PID Controller2/Ideal P Gain'
 * '<S8>'   : 'Controller_Seperate_Step/PID Controller2/Ideal P Gain Fdbk'
 * '<S9>'   : 'Controller_Seperate_Step/PID Controller2/Integrator'
 * '<S10>'  : 'Controller_Seperate_Step/PID Controller2/Integrator ICs'
 * '<S11>'  : 'Controller_Seperate_Step/PID Controller2/N Copy'
 * '<S12>'  : 'Controller_Seperate_Step/PID Controller2/N Gain'
 * '<S13>'  : 'Controller_Seperate_Step/PID Controller2/P Copy'
 * '<S14>'  : 'Controller_Seperate_Step/PID Controller2/Parallel P Gain'
 * '<S15>'  : 'Controller_Seperate_Step/PID Controller2/Reset Signal'
 * '<S16>'  : 'Controller_Seperate_Step/PID Controller2/Saturation'
 * '<S17>'  : 'Controller_Seperate_Step/PID Controller2/Saturation Fdbk'
 * '<S18>'  : 'Controller_Seperate_Step/PID Controller2/Sum'
 * '<S19>'  : 'Controller_Seperate_Step/PID Controller2/Sum Fdbk'
 * '<S20>'  : 'Controller_Seperate_Step/PID Controller2/Tracking Mode'
 * '<S21>'  : 'Controller_Seperate_Step/PID Controller2/Tracking Mode Sum'
 * '<S22>'  : 'Controller_Seperate_Step/PID Controller2/Tsamp - Integral'
 * '<S23>'  : 'Controller_Seperate_Step/PID Controller2/Tsamp - Ngain'
 * '<S24>'  : 'Controller_Seperate_Step/PID Controller2/postSat Signal'
 * '<S25>'  : 'Controller_Seperate_Step/PID Controller2/preSat Signal'
 * '<S26>'  : 'Controller_Seperate_Step/PID Controller2/Anti-windup/Passthrough'
 * '<S27>'  : 'Controller_Seperate_Step/PID Controller2/D Gain/Internal Parameters'
 * '<S28>'  : 'Controller_Seperate_Step/PID Controller2/Filter/Disc. Forward Euler Filter'
 * '<S29>'  : 'Controller_Seperate_Step/PID Controller2/Filter ICs/Internal IC - Filter'
 * '<S30>'  : 'Controller_Seperate_Step/PID Controller2/I Gain/Internal Parameters'
 * '<S31>'  : 'Controller_Seperate_Step/PID Controller2/Ideal P Gain/Passthrough'
 * '<S32>'  : 'Controller_Seperate_Step/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S33>'  : 'Controller_Seperate_Step/PID Controller2/Integrator/Discrete'
 * '<S34>'  : 'Controller_Seperate_Step/PID Controller2/Integrator ICs/Internal IC'
 * '<S35>'  : 'Controller_Seperate_Step/PID Controller2/N Copy/Disabled'
 * '<S36>'  : 'Controller_Seperate_Step/PID Controller2/N Gain/Internal Parameters'
 * '<S37>'  : 'Controller_Seperate_Step/PID Controller2/P Copy/Disabled'
 * '<S38>'  : 'Controller_Seperate_Step/PID Controller2/Parallel P Gain/Internal Parameters'
 * '<S39>'  : 'Controller_Seperate_Step/PID Controller2/Reset Signal/Disabled'
 * '<S40>'  : 'Controller_Seperate_Step/PID Controller2/Saturation/Enabled'
 * '<S41>'  : 'Controller_Seperate_Step/PID Controller2/Saturation Fdbk/Disabled'
 * '<S42>'  : 'Controller_Seperate_Step/PID Controller2/Sum/Sum_PID'
 * '<S43>'  : 'Controller_Seperate_Step/PID Controller2/Sum Fdbk/Disabled'
 * '<S44>'  : 'Controller_Seperate_Step/PID Controller2/Tracking Mode/Disabled'
 * '<S45>'  : 'Controller_Seperate_Step/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S46>'  : 'Controller_Seperate_Step/PID Controller2/Tsamp - Integral/Passthrough'
 * '<S47>'  : 'Controller_Seperate_Step/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S48>'  : 'Controller_Seperate_Step/PID Controller2/postSat Signal/Forward_Path'
 * '<S49>'  : 'Controller_Seperate_Step/PID Controller2/preSat Signal/Forward_Path'
 */
#endif                              /* RTW_HEADER_Controller_Seperate_Step_h_ */
