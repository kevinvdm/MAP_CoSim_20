/*
 * Controller_Seperate_data.c
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

/* Block parameters (default storage) */
P_Controller_Seperate_T Controller_Seperate_P = {
  /* Mask Parameter: PIDController_D
   * Referenced by: '<S28>/Derivative Gain'
   */
  0.0,

  /* Mask Parameter: PIDController_I
   * Referenced by: '<S31>/Integral Gain'
   */
  0.291167347206045,

  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S29>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_d
   * Referenced by: '<S34>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S37>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_P
   * Referenced by: '<S39>/Proportional Gain'
   */
  0.0793781958518769,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S34>/Integrator'
   */
  0.01,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S29>/Filter'
   */
  0.01,

  /* Expression: 1
   * Referenced by: '<Root>/Saturation'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Saturation'
   */
  0.0
};
