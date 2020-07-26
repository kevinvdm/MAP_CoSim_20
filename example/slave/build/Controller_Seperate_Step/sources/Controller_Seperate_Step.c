/*
 * Controller_Seperate_Step.c
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

#include "Controller_Seperate_Step.h"
#include "Controller_Seperate_Step_private.h"

/* Model step function */
void Controller_Seperate_Step_step(RT_MODEL_Controller_Seperate__T *const
  Controller_Seperate_Step_M)
{
  B_Controller_Seperate_Step_T *Controller_Seperate_Step_B =
    ((B_Controller_Seperate_Step_T *) Controller_Seperate_Step_M->blockIO);
  DW_Controller_Seperate_Step_T *Controller_Seperate_Step_DW =
    ((DW_Controller_Seperate_Step_T *) Controller_Seperate_Step_M->dwork);
  ExtU_Controller_Seperate_Step_T *Controller_Seperate_Step_U =
    (ExtU_Controller_Seperate_Step_T *) Controller_Seperate_Step_M->inputs;
  ExtY_Controller_Seperate_Step_T *Controller_Seperate_Step_Y =
    (ExtY_Controller_Seperate_Step_T *) Controller_Seperate_Step_M->outputs;

  /* local block i/o variables */
  real_T rtb_FilterCoefficient;
  real_T rtb_IntegralGain;
  real_T rtb_Step;
  real_T u0;

  /* Step: '<Root>/Step' */
  if (Controller_Seperate_Step_M->Timing.t[0] <
      Controller_Seperate_Step_P.Step_Time) {
    rtb_Step = Controller_Seperate_Step_P.Step_Y0;
  } else {
    rtb_Step = Controller_Seperate_Step_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/Velocity'
   */
  Controller_Seperate_Step_B->Sum = rtb_Step -
    Controller_Seperate_Step_U->Velocity;

  /* Gain: '<S36>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S28>/Filter'
   *  Gain: '<S27>/Derivative Gain'
   *  Sum: '<S28>/SumD'
   */
  rtb_FilterCoefficient = (Controller_Seperate_Step_P.PIDController2_D *
    Controller_Seperate_Step_B->Sum - Controller_Seperate_Step_DW->Filter_DSTATE)
    * Controller_Seperate_Step_P.PIDController2_N;

  /* Sum: '<S42>/Sum' incorporates:
   *  DiscreteIntegrator: '<S33>/Integrator'
   *  Gain: '<S38>/Proportional Gain'
   */
  u0 = (Controller_Seperate_Step_P.PIDController2_P *
        Controller_Seperate_Step_B->Sum +
        Controller_Seperate_Step_DW->Integrator_DSTATE) + rtb_FilterCoefficient;

  /* Saturate: '<S40>/Saturation' */
  if (u0 > Controller_Seperate_Step_P.PIDController2_UpperSaturationL) {
    /* Outport: '<Root>/Throttle' */
    Controller_Seperate_Step_Y->Throttle =
      Controller_Seperate_Step_P.PIDController2_UpperSaturationL;
  } else if (u0 < Controller_Seperate_Step_P.PIDController2_LowerSaturationL) {
    /* Outport: '<Root>/Throttle' */
    Controller_Seperate_Step_Y->Throttle =
      Controller_Seperate_Step_P.PIDController2_LowerSaturationL;
  } else {
    /* Outport: '<Root>/Throttle' */
    Controller_Seperate_Step_Y->Throttle = u0;
  }

  /* End of Saturate: '<S40>/Saturation' */

  /* Outport: '<Root>/Vdesired' */
  Controller_Seperate_Step_Y->Vdesired = rtb_Step;

  /* Gain: '<S30>/Integral Gain' */
  rtb_IntegralGain = Controller_Seperate_Step_P.PIDController2_I *
    Controller_Seperate_Step_B->Sum;

  /* Update for DiscreteIntegrator: '<S33>/Integrator' */
  Controller_Seperate_Step_DW->Integrator_DSTATE +=
    Controller_Seperate_Step_P.Integrator_gainval * rtb_IntegralGain;

  /* Update for DiscreteIntegrator: '<S28>/Filter' */
  Controller_Seperate_Step_DW->Filter_DSTATE +=
    Controller_Seperate_Step_P.Filter_gainval * rtb_FilterCoefficient;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Controller_Seperate_Step_M->Timing.clockTick0)) {
    ++Controller_Seperate_Step_M->Timing.clockTickH0;
  }

  Controller_Seperate_Step_M->Timing.t[0] =
    Controller_Seperate_Step_M->Timing.clockTick0 *
    Controller_Seperate_Step_M->Timing.stepSize0 +
    Controller_Seperate_Step_M->Timing.clockTickH0 *
    Controller_Seperate_Step_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.01, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    Controller_Seperate_Step_M->Timing.clockTick1++;
    if (!Controller_Seperate_Step_M->Timing.clockTick1) {
      Controller_Seperate_Step_M->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void Controller_Seperate_Step_initialize(RT_MODEL_Controller_Seperate__T *const
  Controller_Seperate_Step_M)
{
  DW_Controller_Seperate_Step_T *Controller_Seperate_Step_DW =
    ((DW_Controller_Seperate_Step_T *) Controller_Seperate_Step_M->dwork);

  /* InitializeConditions for DiscreteIntegrator: '<S33>/Integrator' */
  Controller_Seperate_Step_DW->Integrator_DSTATE =
    Controller_Seperate_Step_P.PIDController2_InitialConditi_j;

  /* InitializeConditions for DiscreteIntegrator: '<S28>/Filter' */
  Controller_Seperate_Step_DW->Filter_DSTATE =
    Controller_Seperate_Step_P.PIDController2_InitialCondition;
}

/* Model terminate function */
void Controller_Seperate_Step_terminate(RT_MODEL_Controller_Seperate__T
  * Controller_Seperate_Step_M)
{
  rt_FREE(Controller_Seperate_Step_M->solverInfo);

  /* model code */
  rt_FREE(Controller_Seperate_Step_M->blockIO);
  rt_FREE(Controller_Seperate_Step_M->inputs);
  rt_FREE(Controller_Seperate_Step_M->outputs);
  rt_FREE(Controller_Seperate_Step_M->dwork);
  rt_FREE(Controller_Seperate_Step_M);
}

/* Model data allocation function */
RT_MODEL_Controller_Seperate__T *Controller_Seperate_Step(void)
{
  RT_MODEL_Controller_Seperate__T *Controller_Seperate_Step_M;
  Controller_Seperate_Step_M = (RT_MODEL_Controller_Seperate__T *) malloc(sizeof
    (RT_MODEL_Controller_Seperate__T));
  if (Controller_Seperate_Step_M == NULL) {
    return NULL;
  }

  (void) memset((char *)Controller_Seperate_Step_M, 0,
                sizeof(RT_MODEL_Controller_Seperate__T));

  {
    /* Setup solver object */
    RTWSolverInfo *rt_SolverInfo = (RTWSolverInfo *) malloc(sizeof(RTWSolverInfo));
    rt_VALIDATE_MEMORY(Controller_Seperate_Step_M,rt_SolverInfo);
    Controller_Seperate_Step_M->solverInfo = (rt_SolverInfo);
    rtsiSetSimTimeStepPtr(Controller_Seperate_Step_M->solverInfo,
                          &Controller_Seperate_Step_M->Timing.simTimeStep);
    rtsiSetTPtr(Controller_Seperate_Step_M->solverInfo, &rtmGetTPtr
                (Controller_Seperate_Step_M));
    rtsiSetStepSizePtr(Controller_Seperate_Step_M->solverInfo,
                       &Controller_Seperate_Step_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(Controller_Seperate_Step_M->solverInfo,
                          (&rtmGetErrorStatus(Controller_Seperate_Step_M)));
    rtsiSetRTModelPtr(Controller_Seperate_Step_M->solverInfo,
                      Controller_Seperate_Step_M);
  }

  rtsiSetSolverName(Controller_Seperate_Step_M->solverInfo,"FixedStepDiscrete");

  /* block I/O */
  {
    B_Controller_Seperate_Step_T *b = (B_Controller_Seperate_Step_T *) malloc
      (sizeof(B_Controller_Seperate_Step_T));
    rt_VALIDATE_MEMORY(Controller_Seperate_Step_M,b);
    Controller_Seperate_Step_M->blockIO = (b);
  }

  /* states (dwork) */
  {
    DW_Controller_Seperate_Step_T *dwork = (DW_Controller_Seperate_Step_T *)
      malloc(sizeof(DW_Controller_Seperate_Step_T));
    rt_VALIDATE_MEMORY(Controller_Seperate_Step_M,dwork);
    Controller_Seperate_Step_M->dwork = (dwork);
  }

  /* external inputs */
  {
    ExtU_Controller_Seperate_Step_T *Controller_Seperate_Step_U =
      (ExtU_Controller_Seperate_Step_T *) malloc(sizeof
      (ExtU_Controller_Seperate_Step_T));
    rt_VALIDATE_MEMORY(Controller_Seperate_Step_M,Controller_Seperate_Step_U);
    Controller_Seperate_Step_M->inputs = (((ExtU_Controller_Seperate_Step_T *)
      Controller_Seperate_Step_U));
  }

  /* external outputs */
  {
    ExtY_Controller_Seperate_Step_T *Controller_Seperate_Step_Y =
      (ExtY_Controller_Seperate_Step_T *) malloc(sizeof
      (ExtY_Controller_Seperate_Step_T));
    rt_VALIDATE_MEMORY(Controller_Seperate_Step_M,Controller_Seperate_Step_Y);
    Controller_Seperate_Step_M->outputs = (Controller_Seperate_Step_Y);
  }

  {
    B_Controller_Seperate_Step_T *Controller_Seperate_Step_B =
      ((B_Controller_Seperate_Step_T *) Controller_Seperate_Step_M->blockIO);
    DW_Controller_Seperate_Step_T *Controller_Seperate_Step_DW =
      ((DW_Controller_Seperate_Step_T *) Controller_Seperate_Step_M->dwork);
    ExtU_Controller_Seperate_Step_T *Controller_Seperate_Step_U =
      (ExtU_Controller_Seperate_Step_T *) Controller_Seperate_Step_M->inputs;
    ExtY_Controller_Seperate_Step_T *Controller_Seperate_Step_Y =
      (ExtY_Controller_Seperate_Step_T *) Controller_Seperate_Step_M->outputs;
    rtsiSetSimTimeStep(Controller_Seperate_Step_M->solverInfo, MAJOR_TIME_STEP);
    rtmSetTPtr(Controller_Seperate_Step_M,
               &Controller_Seperate_Step_M->Timing.tArray[0]);
    Controller_Seperate_Step_M->Timing.stepSize0 = 0.01;

    /* block I/O */
    (void) memset(((void *) Controller_Seperate_Step_B), 0,
                  sizeof(B_Controller_Seperate_Step_T));

    /* states (dwork) */
    (void) memset((void *)Controller_Seperate_Step_DW, 0,
                  sizeof(DW_Controller_Seperate_Step_T));

    /* external inputs */
    Controller_Seperate_Step_U->Velocity = 0.0;

    /* external outputs */
    (void) memset((void *)Controller_Seperate_Step_Y, 0,
                  sizeof(ExtY_Controller_Seperate_Step_T));
  }

  return Controller_Seperate_Step_M;
}
