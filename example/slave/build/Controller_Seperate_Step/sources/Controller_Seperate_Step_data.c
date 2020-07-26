/*
 * Controller_Seperate_Step_data.c
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

/* Block parameters (default storage) */
P_Controller_Seperate_Step_T Controller_Seperate_Step_P = {
  /* Mask Parameter: PIDController2_D
   * Referenced by: '<S27>/Derivative Gain'
   */
  0.00731732532974105,

  /* Mask Parameter: PIDController2_I
   * Referenced by: '<S30>/Integral Gain'
   */
  0.984756295868629,

  /* Mask Parameter: PIDController2_InitialCondition
   * Referenced by: '<S28>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController2_InitialConditi_j
   * Referenced by: '<S33>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController2_LowerSaturationL
   * Referenced by: '<S40>/Saturation'
   */
  0.0,

  /* Mask Parameter: PIDController2_N
   * Referenced by: '<S36>/Filter Coefficient'
   */
  165.684780243972,

  /* Mask Parameter: PIDController2_P
   * Referenced by: '<S38>/Proportional Gain'
   */
  0.183841666477947,

  /* Mask Parameter: PIDController2_UpperSaturationL
   * Referenced by: '<S40>/Saturation'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<Root>/Step'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Step'
   */
  1.0,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S33>/Integrator'
   */
  0.01,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S28>/Filter'
   */
  0.01
};
