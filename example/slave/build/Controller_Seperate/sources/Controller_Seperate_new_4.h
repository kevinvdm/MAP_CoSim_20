/*
 * Controller_Seperate_new_4.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Controller_Seperate_new_4".
 *
 * Model version              : 1.12
 * Simulink Coder version : 9.3 (R2020a) 18-Nov-2019
 * C source code generated on : Fri Jun  5 10:31:57 2020
 *
 * Target selection: grtfmi.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Controller_Seperate_new_4_h_
#define RTW_HEADER_Controller_Seperate_new_4_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef Controller_Seperate_new_4_COMMON_INCLUDES_
# define Controller_Seperate_new_4_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                          /* Controller_Seperate_new_4_COMMON_INCLUDES_ */

#include "Controller_Seperate_new_4_types.h"

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

#define Controller_Seperate_new_4_M_TYPE RT_MODEL_Controller_Seperate__T

/* Block signals (default storage) */
typedef struct {
  real_T Sum;                          /* '<Root>/Sum' */
} B_Controller_Seperate_new_4_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S34>/Integrator' */
  real_T Filter_DSTATE;                /* '<S29>/Filter' */
  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWs_PWORK;                      /* '<S2>/FromWs' */

  struct {
    int_T PrevIndex;
  } FromWs_IWORK;                      /* '<S2>/FromWs' */
} DW_Controller_Seperate_new_4_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Velocity;                     /* '<Root>/Velocity' */
} ExtU_Controller_Seperate_new__T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Throttle;                     /* '<Root>/Throttle' */
  real_T Vdesired;                     /* '<Root>/Vdesired' */
} ExtY_Controller_Seperate_new__T;

/* Parameters (default storage) */
struct P_Controller_Seperate_new_4_T_ {
  real_T PIDController1_D;             /* Mask Parameter: PIDController1_D
                                        * Referenced by: '<S28>/Derivative Gain'
                                        */
  real_T PIDController1_I;             /* Mask Parameter: PIDController1_I
                                        * Referenced by: '<S31>/Integral Gain'
                                        */
  real_T PIDController1_InitialCondition;
                              /* Mask Parameter: PIDController1_InitialCondition
                               * Referenced by: '<S29>/Filter'
                               */
  real_T PIDController1_InitialConditi_g;
                              /* Mask Parameter: PIDController1_InitialConditi_g
                               * Referenced by: '<S34>/Integrator'
                               */
  real_T PIDController1_LowerSaturationL;
                              /* Mask Parameter: PIDController1_LowerSaturationL
                               * Referenced by: '<S41>/Saturation'
                               */
  real_T PIDController1_N;             /* Mask Parameter: PIDController1_N
                                        * Referenced by: '<S37>/Filter Coefficient'
                                        */
  real_T PIDController1_P;             /* Mask Parameter: PIDController1_P
                                        * Referenced by: '<S39>/Proportional Gain'
                                        */
  real_T PIDController1_UpperSaturationL;
                              /* Mask Parameter: PIDController1_UpperSaturationL
                               * Referenced by: '<S41>/Saturation'
                               */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S34>/Integrator'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S29>/Filter'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Controller_Seperate_n_T {
  const char_T *errorStatus;
  RTWSolverInfo *solverInfo;
  B_Controller_Seperate_new_4_T *blockIO;
  ExtU_Controller_Seperate_new__T *inputs;
  ExtY_Controller_Seperate_new__T *outputs;
  DW_Controller_Seperate_new_4_T *dwork;

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
extern P_Controller_Seperate_new_4_T Controller_Seperate_new_4_P;

/* External data declarations for dependent source files */
extern const char *RT_MEMORY_ALLOCATION_ERROR;
extern P_Controller_Seperate_new_4_T Controller_Seperate_new_4_P;/* parameters */

/* Model entry point functions */
extern RT_MODEL_Controller_Seperate__T *Controller_Seperate_new_4(void);
extern void Controller_Seperate_new_4_initialize(RT_MODEL_Controller_Seperate__T
  *const Controller_Seperate_new_4_M);
extern void Controller_Seperate_new_4_step(RT_MODEL_Controller_Seperate__T *
  const Controller_Seperate_new_4_M);
extern void Controller_Seperate_new_4_terminate(RT_MODEL_Controller_Seperate__T *
  Controller_Seperate_new_4_M);

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
 * '<Root>' : 'Controller_Seperate_new_4'
 * '<S1>'   : 'Controller_Seperate_new_4/PID Controller1'
 * '<S2>'   : 'Controller_Seperate_new_4/Signal Builder'
 * '<S3>'   : 'Controller_Seperate_new_4/PID Controller1/Anti-windup'
 * '<S4>'   : 'Controller_Seperate_new_4/PID Controller1/D Gain'
 * '<S5>'   : 'Controller_Seperate_new_4/PID Controller1/Filter'
 * '<S6>'   : 'Controller_Seperate_new_4/PID Controller1/Filter ICs'
 * '<S7>'   : 'Controller_Seperate_new_4/PID Controller1/I Gain'
 * '<S8>'   : 'Controller_Seperate_new_4/PID Controller1/Ideal P Gain'
 * '<S9>'   : 'Controller_Seperate_new_4/PID Controller1/Ideal P Gain Fdbk'
 * '<S10>'  : 'Controller_Seperate_new_4/PID Controller1/Integrator'
 * '<S11>'  : 'Controller_Seperate_new_4/PID Controller1/Integrator ICs'
 * '<S12>'  : 'Controller_Seperate_new_4/PID Controller1/N Copy'
 * '<S13>'  : 'Controller_Seperate_new_4/PID Controller1/N Gain'
 * '<S14>'  : 'Controller_Seperate_new_4/PID Controller1/P Copy'
 * '<S15>'  : 'Controller_Seperate_new_4/PID Controller1/Parallel P Gain'
 * '<S16>'  : 'Controller_Seperate_new_4/PID Controller1/Reset Signal'
 * '<S17>'  : 'Controller_Seperate_new_4/PID Controller1/Saturation'
 * '<S18>'  : 'Controller_Seperate_new_4/PID Controller1/Saturation Fdbk'
 * '<S19>'  : 'Controller_Seperate_new_4/PID Controller1/Sum'
 * '<S20>'  : 'Controller_Seperate_new_4/PID Controller1/Sum Fdbk'
 * '<S21>'  : 'Controller_Seperate_new_4/PID Controller1/Tracking Mode'
 * '<S22>'  : 'Controller_Seperate_new_4/PID Controller1/Tracking Mode Sum'
 * '<S23>'  : 'Controller_Seperate_new_4/PID Controller1/Tsamp - Integral'
 * '<S24>'  : 'Controller_Seperate_new_4/PID Controller1/Tsamp - Ngain'
 * '<S25>'  : 'Controller_Seperate_new_4/PID Controller1/postSat Signal'
 * '<S26>'  : 'Controller_Seperate_new_4/PID Controller1/preSat Signal'
 * '<S27>'  : 'Controller_Seperate_new_4/PID Controller1/Anti-windup/Passthrough'
 * '<S28>'  : 'Controller_Seperate_new_4/PID Controller1/D Gain/Internal Parameters'
 * '<S29>'  : 'Controller_Seperate_new_4/PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S30>'  : 'Controller_Seperate_new_4/PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S31>'  : 'Controller_Seperate_new_4/PID Controller1/I Gain/Internal Parameters'
 * '<S32>'  : 'Controller_Seperate_new_4/PID Controller1/Ideal P Gain/Passthrough'
 * '<S33>'  : 'Controller_Seperate_new_4/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S34>'  : 'Controller_Seperate_new_4/PID Controller1/Integrator/Discrete'
 * '<S35>'  : 'Controller_Seperate_new_4/PID Controller1/Integrator ICs/Internal IC'
 * '<S36>'  : 'Controller_Seperate_new_4/PID Controller1/N Copy/Disabled'
 * '<S37>'  : 'Controller_Seperate_new_4/PID Controller1/N Gain/Internal Parameters'
 * '<S38>'  : 'Controller_Seperate_new_4/PID Controller1/P Copy/Disabled'
 * '<S39>'  : 'Controller_Seperate_new_4/PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S40>'  : 'Controller_Seperate_new_4/PID Controller1/Reset Signal/Disabled'
 * '<S41>'  : 'Controller_Seperate_new_4/PID Controller1/Saturation/Enabled'
 * '<S42>'  : 'Controller_Seperate_new_4/PID Controller1/Saturation Fdbk/Disabled'
 * '<S43>'  : 'Controller_Seperate_new_4/PID Controller1/Sum/Sum_PID'
 * '<S44>'  : 'Controller_Seperate_new_4/PID Controller1/Sum Fdbk/Disabled'
 * '<S45>'  : 'Controller_Seperate_new_4/PID Controller1/Tracking Mode/Disabled'
 * '<S46>'  : 'Controller_Seperate_new_4/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S47>'  : 'Controller_Seperate_new_4/PID Controller1/Tsamp - Integral/Passthrough'
 * '<S48>'  : 'Controller_Seperate_new_4/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S49>'  : 'Controller_Seperate_new_4/PID Controller1/postSat Signal/Forward_Path'
 * '<S50>'  : 'Controller_Seperate_new_4/PID Controller1/preSat Signal/Forward_Path'
 */
#endif                             /* RTW_HEADER_Controller_Seperate_new_4_h_ */
