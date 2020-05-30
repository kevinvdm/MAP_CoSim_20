/*
 * Controller_Seperate.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Controller_Seperate".
 *
 * Model version              : 1.5
 * Simulink Coder version : 9.3 (R2020a) 18-Nov-2019
 * C source code generated on : Sat May 30 22:32:42 2020
 *
 * Target selection: grtfmi.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Controller_Seperate_h_
#define RTW_HEADER_Controller_Seperate_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef Controller_Seperate_COMMON_INCLUDES_
# define Controller_Seperate_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                /* Controller_Seperate_COMMON_INCLUDES_ */

#include "Controller_Seperate_types.h"

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

#define Controller_Seperate_M_TYPE     RT_MODEL_Controller_Seperate_T

/* Block signals (default storage) */
typedef struct {
  real_T Sum;                          /* '<Root>/Sum' */
} B_Controller_Seperate_T;

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
} DW_Controller_Seperate_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Velocity;                     /* '<Root>/Velocity' */
} ExtU_Controller_Seperate_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Throttle;                     /* '<Root>/Throttle' */
} ExtY_Controller_Seperate_T;

/* Parameters (default storage) */
struct P_Controller_Seperate_T_ {
  real_T PIDController_D;              /* Mask Parameter: PIDController_D
                                        * Referenced by: '<S28>/Derivative Gain'
                                        */
  real_T PIDController_I;              /* Mask Parameter: PIDController_I
                                        * Referenced by: '<S31>/Integral Gain'
                                        */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S29>/Filter'
                               */
  real_T PIDController_InitialConditio_d;
                              /* Mask Parameter: PIDController_InitialConditio_d
                               * Referenced by: '<S34>/Integrator'
                               */
  real_T PIDController_N;              /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S37>/Filter Coefficient'
                                        */
  real_T PIDController_P;              /* Mask Parameter: PIDController_P
                                        * Referenced by: '<S39>/Proportional Gain'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S34>/Integrator'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S29>/Filter'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: 0
                                        * Referenced by: '<Root>/Saturation'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Controller_Seperate_T {
  const char_T *errorStatus;
  RTWSolverInfo *solverInfo;
  B_Controller_Seperate_T *blockIO;
  ExtU_Controller_Seperate_T *inputs;
  ExtY_Controller_Seperate_T *outputs;
  DW_Controller_Seperate_T *dwork;

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
extern P_Controller_Seperate_T Controller_Seperate_P;

/* External data declarations for dependent source files */
extern const char *RT_MEMORY_ALLOCATION_ERROR;
extern P_Controller_Seperate_T Controller_Seperate_P;/* parameters */

/* Model entry point functions */
extern RT_MODEL_Controller_Seperate_T *Controller_Seperate(void);
extern void Controller_Seperate_initialize(RT_MODEL_Controller_Seperate_T *const
  Controller_Seperate_M);
extern void Controller_Seperate_step(RT_MODEL_Controller_Seperate_T *const
  Controller_Seperate_M);
extern void Controller_Seperate_terminate(RT_MODEL_Controller_Seperate_T
  * Controller_Seperate_M);

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
 * '<Root>' : 'Controller_Seperate'
 * '<S1>'   : 'Controller_Seperate/PID Controller'
 * '<S2>'   : 'Controller_Seperate/Signal Builder'
 * '<S3>'   : 'Controller_Seperate/PID Controller/Anti-windup'
 * '<S4>'   : 'Controller_Seperate/PID Controller/D Gain'
 * '<S5>'   : 'Controller_Seperate/PID Controller/Filter'
 * '<S6>'   : 'Controller_Seperate/PID Controller/Filter ICs'
 * '<S7>'   : 'Controller_Seperate/PID Controller/I Gain'
 * '<S8>'   : 'Controller_Seperate/PID Controller/Ideal P Gain'
 * '<S9>'   : 'Controller_Seperate/PID Controller/Ideal P Gain Fdbk'
 * '<S10>'  : 'Controller_Seperate/PID Controller/Integrator'
 * '<S11>'  : 'Controller_Seperate/PID Controller/Integrator ICs'
 * '<S12>'  : 'Controller_Seperate/PID Controller/N Copy'
 * '<S13>'  : 'Controller_Seperate/PID Controller/N Gain'
 * '<S14>'  : 'Controller_Seperate/PID Controller/P Copy'
 * '<S15>'  : 'Controller_Seperate/PID Controller/Parallel P Gain'
 * '<S16>'  : 'Controller_Seperate/PID Controller/Reset Signal'
 * '<S17>'  : 'Controller_Seperate/PID Controller/Saturation'
 * '<S18>'  : 'Controller_Seperate/PID Controller/Saturation Fdbk'
 * '<S19>'  : 'Controller_Seperate/PID Controller/Sum'
 * '<S20>'  : 'Controller_Seperate/PID Controller/Sum Fdbk'
 * '<S21>'  : 'Controller_Seperate/PID Controller/Tracking Mode'
 * '<S22>'  : 'Controller_Seperate/PID Controller/Tracking Mode Sum'
 * '<S23>'  : 'Controller_Seperate/PID Controller/Tsamp - Integral'
 * '<S24>'  : 'Controller_Seperate/PID Controller/Tsamp - Ngain'
 * '<S25>'  : 'Controller_Seperate/PID Controller/postSat Signal'
 * '<S26>'  : 'Controller_Seperate/PID Controller/preSat Signal'
 * '<S27>'  : 'Controller_Seperate/PID Controller/Anti-windup/Passthrough'
 * '<S28>'  : 'Controller_Seperate/PID Controller/D Gain/Internal Parameters'
 * '<S29>'  : 'Controller_Seperate/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S30>'  : 'Controller_Seperate/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S31>'  : 'Controller_Seperate/PID Controller/I Gain/Internal Parameters'
 * '<S32>'  : 'Controller_Seperate/PID Controller/Ideal P Gain/Passthrough'
 * '<S33>'  : 'Controller_Seperate/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S34>'  : 'Controller_Seperate/PID Controller/Integrator/Discrete'
 * '<S35>'  : 'Controller_Seperate/PID Controller/Integrator ICs/Internal IC'
 * '<S36>'  : 'Controller_Seperate/PID Controller/N Copy/Disabled'
 * '<S37>'  : 'Controller_Seperate/PID Controller/N Gain/Internal Parameters'
 * '<S38>'  : 'Controller_Seperate/PID Controller/P Copy/Disabled'
 * '<S39>'  : 'Controller_Seperate/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S40>'  : 'Controller_Seperate/PID Controller/Reset Signal/Disabled'
 * '<S41>'  : 'Controller_Seperate/PID Controller/Saturation/Passthrough'
 * '<S42>'  : 'Controller_Seperate/PID Controller/Saturation Fdbk/Disabled'
 * '<S43>'  : 'Controller_Seperate/PID Controller/Sum/Sum_PID'
 * '<S44>'  : 'Controller_Seperate/PID Controller/Sum Fdbk/Disabled'
 * '<S45>'  : 'Controller_Seperate/PID Controller/Tracking Mode/Disabled'
 * '<S46>'  : 'Controller_Seperate/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S47>'  : 'Controller_Seperate/PID Controller/Tsamp - Integral/Passthrough'
 * '<S48>'  : 'Controller_Seperate/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S49>'  : 'Controller_Seperate/PID Controller/postSat Signal/Forward_Path'
 * '<S50>'  : 'Controller_Seperate/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_Controller_Seperate_h_ */
