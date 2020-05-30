/*
 * Controller_Seperate.c
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

#include "Controller_Seperate.h"
#include "Controller_Seperate_private.h"

/* Model step function */
void Controller_Seperate_step(RT_MODEL_Controller_Seperate_T *const
  Controller_Seperate_M)
{
  B_Controller_Seperate_T *Controller_Seperate_B = ((B_Controller_Seperate_T *)
    Controller_Seperate_M->blockIO);
  DW_Controller_Seperate_T *Controller_Seperate_DW = ((DW_Controller_Seperate_T *)
    Controller_Seperate_M->dwork);
  ExtU_Controller_Seperate_T *Controller_Seperate_U =
    (ExtU_Controller_Seperate_T *) Controller_Seperate_M->inputs;
  ExtY_Controller_Seperate_T *Controller_Seperate_Y =
    (ExtY_Controller_Seperate_T *) Controller_Seperate_M->outputs;

  /* local block i/o variables */
  real_T rtb_FromWs;
  real_T rtb_FilterCoefficient;
  real_T rtb_IntegralGain;
  real_T u0;

  /* FromWorkspace: '<S2>/FromWs' */
  {
    real_T *pDataValues = (real_T *)
      Controller_Seperate_DW->FromWs_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      Controller_Seperate_DW->FromWs_PWORK.TimePtr;
    int_T currTimeIndex = Controller_Seperate_DW->FromWs_IWORK.PrevIndex;
    real_T t = Controller_Seperate_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[14]) {
      currTimeIndex = 13;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    Controller_Seperate_DW->FromWs_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_FromWs = pDataValues[currTimeIndex];
        } else {
          rtb_FromWs = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_FromWs = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 15;
      }
    }
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/Velocity'
   */
  Controller_Seperate_B->Sum = rtb_FromWs - Controller_Seperate_U->Velocity;

  /* Gain: '<S37>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S29>/Filter'
   *  Gain: '<S28>/Derivative Gain'
   *  Sum: '<S29>/SumD'
   */
  rtb_FilterCoefficient = (Controller_Seperate_P.PIDController_D *
    Controller_Seperate_B->Sum - Controller_Seperate_DW->Filter_DSTATE) *
    Controller_Seperate_P.PIDController_N;

  /* Sum: '<S43>/Sum' incorporates:
   *  DiscreteIntegrator: '<S34>/Integrator'
   *  Gain: '<S39>/Proportional Gain'
   */
  u0 = (Controller_Seperate_P.PIDController_P * Controller_Seperate_B->Sum +
        Controller_Seperate_DW->Integrator_DSTATE) + rtb_FilterCoefficient;

  /* Saturate: '<Root>/Saturation' */
  if (u0 > Controller_Seperate_P.Saturation_UpperSat) {
    /* Outport: '<Root>/Throttle' */
    Controller_Seperate_Y->Throttle = Controller_Seperate_P.Saturation_UpperSat;
  } else if (u0 < Controller_Seperate_P.Saturation_LowerSat) {
    /* Outport: '<Root>/Throttle' */
    Controller_Seperate_Y->Throttle = Controller_Seperate_P.Saturation_LowerSat;
  } else {
    /* Outport: '<Root>/Throttle' */
    Controller_Seperate_Y->Throttle = u0;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Gain: '<S31>/Integral Gain' */
  rtb_IntegralGain = Controller_Seperate_P.PIDController_I *
    Controller_Seperate_B->Sum;

  /* Update for DiscreteIntegrator: '<S34>/Integrator' */
  Controller_Seperate_DW->Integrator_DSTATE +=
    Controller_Seperate_P.Integrator_gainval * rtb_IntegralGain;

  /* Update for DiscreteIntegrator: '<S29>/Filter' */
  Controller_Seperate_DW->Filter_DSTATE += Controller_Seperate_P.Filter_gainval *
    rtb_FilterCoefficient;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Controller_Seperate_M->Timing.clockTick0)) {
    ++Controller_Seperate_M->Timing.clockTickH0;
  }

  Controller_Seperate_M->Timing.t[0] = Controller_Seperate_M->Timing.clockTick0 *
    Controller_Seperate_M->Timing.stepSize0 +
    Controller_Seperate_M->Timing.clockTickH0 *
    Controller_Seperate_M->Timing.stepSize0 * 4294967296.0;

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
    Controller_Seperate_M->Timing.clockTick1++;
    if (!Controller_Seperate_M->Timing.clockTick1) {
      Controller_Seperate_M->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void Controller_Seperate_initialize(RT_MODEL_Controller_Seperate_T *const
  Controller_Seperate_M)
{
  DW_Controller_Seperate_T *Controller_Seperate_DW = ((DW_Controller_Seperate_T *)
    Controller_Seperate_M->dwork);

  /* Start for FromWorkspace: '<S2>/FromWs' */
  {
    static real_T pTimeValues0[] = { 0.0, 10.0, 20.0, 30.0, 30.0, 40.0, 40.0,
      50.0, 60.0, 60.0, 70.0, 80.0, 80.0, 90.0, 100.0 } ;

    static real_T pDataValues0[] = { 9.0, 9.0, 9.0, 9.0, 9.0, 5.0, 5.0, 5.0, 5.0,
      9.0, 9.0, 9.0, 5.0, 5.0, 5.0 } ;

    Controller_Seperate_DW->FromWs_PWORK.TimePtr = (void *) pTimeValues0;
    Controller_Seperate_DW->FromWs_PWORK.DataPtr = (void *) pDataValues0;
    Controller_Seperate_DW->FromWs_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for DiscreteIntegrator: '<S34>/Integrator' */
  Controller_Seperate_DW->Integrator_DSTATE =
    Controller_Seperate_P.PIDController_InitialConditio_d;

  /* InitializeConditions for DiscreteIntegrator: '<S29>/Filter' */
  Controller_Seperate_DW->Filter_DSTATE =
    Controller_Seperate_P.PIDController_InitialConditionF;
}

/* Model terminate function */
void Controller_Seperate_terminate(RT_MODEL_Controller_Seperate_T
  * Controller_Seperate_M)
{
  rt_FREE(Controller_Seperate_M->solverInfo);

  /* model code */
  rt_FREE(Controller_Seperate_M->blockIO);
  rt_FREE(Controller_Seperate_M->inputs);
  rt_FREE(Controller_Seperate_M->outputs);
  rt_FREE(Controller_Seperate_M->dwork);
  rt_FREE(Controller_Seperate_M);
}

/* Model data allocation function */
RT_MODEL_Controller_Seperate_T *Controller_Seperate(void)
{
  RT_MODEL_Controller_Seperate_T *Controller_Seperate_M;
  Controller_Seperate_M = (RT_MODEL_Controller_Seperate_T *) malloc(sizeof
    (RT_MODEL_Controller_Seperate_T));
  if (Controller_Seperate_M == NULL) {
    return NULL;
  }

  (void) memset((char *)Controller_Seperate_M, 0,
                sizeof(RT_MODEL_Controller_Seperate_T));

  {
    /* Setup solver object */
    RTWSolverInfo *rt_SolverInfo = (RTWSolverInfo *) malloc(sizeof(RTWSolverInfo));
    rt_VALIDATE_MEMORY(Controller_Seperate_M,rt_SolverInfo);
    Controller_Seperate_M->solverInfo = (rt_SolverInfo);
    rtsiSetSimTimeStepPtr(Controller_Seperate_M->solverInfo,
                          &Controller_Seperate_M->Timing.simTimeStep);
    rtsiSetTPtr(Controller_Seperate_M->solverInfo, &rtmGetTPtr
                (Controller_Seperate_M));
    rtsiSetStepSizePtr(Controller_Seperate_M->solverInfo,
                       &Controller_Seperate_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(Controller_Seperate_M->solverInfo, (&rtmGetErrorStatus
      (Controller_Seperate_M)));
    rtsiSetRTModelPtr(Controller_Seperate_M->solverInfo, Controller_Seperate_M);
  }

  rtsiSetSolverName(Controller_Seperate_M->solverInfo,"FixedStepDiscrete");

  /* block I/O */
  {
    B_Controller_Seperate_T *b = (B_Controller_Seperate_T *) malloc(sizeof
      (B_Controller_Seperate_T));
    rt_VALIDATE_MEMORY(Controller_Seperate_M,b);
    Controller_Seperate_M->blockIO = (b);
  }

  /* states (dwork) */
  {
    DW_Controller_Seperate_T *dwork = (DW_Controller_Seperate_T *) malloc(sizeof
      (DW_Controller_Seperate_T));
    rt_VALIDATE_MEMORY(Controller_Seperate_M,dwork);
    Controller_Seperate_M->dwork = (dwork);
  }

  /* external inputs */
  {
    ExtU_Controller_Seperate_T *Controller_Seperate_U =
      (ExtU_Controller_Seperate_T *) malloc(sizeof(ExtU_Controller_Seperate_T));
    rt_VALIDATE_MEMORY(Controller_Seperate_M,Controller_Seperate_U);
    Controller_Seperate_M->inputs = (((ExtU_Controller_Seperate_T *)
      Controller_Seperate_U));
  }

  /* external outputs */
  {
    ExtY_Controller_Seperate_T *Controller_Seperate_Y =
      (ExtY_Controller_Seperate_T *) malloc(sizeof(ExtY_Controller_Seperate_T));
    rt_VALIDATE_MEMORY(Controller_Seperate_M,Controller_Seperate_Y);
    Controller_Seperate_M->outputs = (Controller_Seperate_Y);
  }

  {
    B_Controller_Seperate_T *Controller_Seperate_B = ((B_Controller_Seperate_T *)
      Controller_Seperate_M->blockIO);
    DW_Controller_Seperate_T *Controller_Seperate_DW =
      ((DW_Controller_Seperate_T *) Controller_Seperate_M->dwork);
    ExtU_Controller_Seperate_T *Controller_Seperate_U =
      (ExtU_Controller_Seperate_T *) Controller_Seperate_M->inputs;
    ExtY_Controller_Seperate_T *Controller_Seperate_Y =
      (ExtY_Controller_Seperate_T *) Controller_Seperate_M->outputs;
    rtsiSetSimTimeStep(Controller_Seperate_M->solverInfo, MAJOR_TIME_STEP);
    rtmSetTPtr(Controller_Seperate_M, &Controller_Seperate_M->Timing.tArray[0]);
    Controller_Seperate_M->Timing.stepSize0 = 0.01;

    /* block I/O */
    (void) memset(((void *) Controller_Seperate_B), 0,
                  sizeof(B_Controller_Seperate_T));

    /* states (dwork) */
    (void) memset((void *)Controller_Seperate_DW, 0,
                  sizeof(DW_Controller_Seperate_T));

    /* external inputs */
    Controller_Seperate_U->Velocity = 0.0;

    /* external outputs */
    Controller_Seperate_Y->Throttle = 0.0;
  }

  return Controller_Seperate_M;
}
