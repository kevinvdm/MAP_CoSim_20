/*
 * Controller_Seperate_new_4_data.c
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

#include "Controller_Seperate_new_4.h"
#include "Controller_Seperate_new_4_private.h"

/* Block parameters (default storage) */
P_Controller_Seperate_new_4_T Controller_Seperate_new_4_P = {
  /* Mask Parameter: PIDController1_D
   * Referenced by: '<S28>/Derivative Gain'
   */
  0.0,

  /* Mask Parameter: PIDController1_I
   * Referenced by: '<S31>/Integral Gain'
   */
  0.267664175895377,

  /* Mask Parameter: PIDController1_InitialCondition
   * Referenced by: '<S29>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController1_InitialConditi_g
   * Referenced by: '<S34>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController1_LowerSaturationL
   * Referenced by: '<S41>/Saturation'
   */
  0.0,

  /* Mask Parameter: PIDController1_N
   * Referenced by: '<S37>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController1_P
   * Referenced by: '<S39>/Proportional Gain'
   */
  0.0477568828118149,

  /* Mask Parameter: PIDController1_UpperSaturationL
   * Referenced by: '<S41>/Saturation'
   */
  1.0,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S34>/Integrator'
   */
  0.01,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S29>/Filter'
   */
  0.01
};
