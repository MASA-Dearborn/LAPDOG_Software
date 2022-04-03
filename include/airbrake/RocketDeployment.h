//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: RocketDeployment.h
//
// Code generated for Simulink model 'RocketDeployment'.
//
// Model version                  : 1.182
// Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
// C/C++ source code generated on : Sun Apr  3 18:39:00 2022
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM 9
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_RocketDeployment_h_
#define RTW_HEADER_RocketDeployment_h_
#include <cmath>
#include <cstring>
#include "rtwtypes.h"
#include "RocketDeployment_types.h"
#include "rt_defines.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Block states (default storage) for system '<Root>'
typedef struct {
  real_T MemoryX_DSTATE[2];            // '<S1>/MemoryX'
  real_T Delay_DSTATE;                 // '<Root>/Delay'
  real_T Integrator_DSTATE;            // '<S89>/Integrator'
  real_T UD_DSTATE;                    // '<S82>/UD'
  uint8_T icLoad;                      // '<S1>/MemoryX'
} DW_RocketDeployment_T;

// Constant parameters (default storage)
typedef struct {
  // Expression: drag_data
  //  Referenced by: '<Root>/MATLAB Function'

  real_T MATLABFunction_drag_data[784635];
} ConstP_RocketDeployment_T;

// External inputs (root inport signals with default storage)
typedef struct {
  real_T Accel_Z;                      // '<Root>/Accel_Z'
  real_T Altitude;                     // '<Root>/Altitude'
} ExtU_RocketDeployment_T;

// External outputs (root outports fed by signals with default storage)
typedef struct {
  real_T EstimatedApogee;              // '<Root>/Estimated Apogee'
  real_T Deployment;                   // '<Root>/Deployment'
  real_T EstimatedAlt;                 // '<Root>/Estimated Alt'
  real_T EstimatedVel;                 // '<Root>/Estimated Vel'
} ExtY_RocketDeployment_T;

// Real-time Model Data Structure
struct tag_RTM_RocketDeployment_T {
  const char_T * volatile errorStatus;
  DW_RocketDeployment_T *dwork;
};

// Constant parameters (default storage)
extern const ConstP_RocketDeployment_T RocketDeployment_ConstP;

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void RocketDeployment_initialize(RT_MODEL_RocketDeployment_T *const
    RocketDeployment_M, ExtU_RocketDeployment_T *RocketDeployment_U,
    ExtY_RocketDeployment_T *RocketDeployment_Y);
  extern void RocketDeployment_step(RT_MODEL_RocketDeployment_T *const
    RocketDeployment_M, ExtU_RocketDeployment_T *RocketDeployment_U,
    ExtY_RocketDeployment_T *RocketDeployment_Y);
  extern void RocketDeployment_terminate(RT_MODEL_RocketDeployment_T *const
    RocketDeployment_M);

#ifdef __cplusplus

}
#endif

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Est Alt' : Unused code path elimination
//  Block '<Root>/Est Vel' : Unused code path elimination
//  Block '<S4>/CovarianceZ' : Unused code path elimination
//  Block '<S47>/Data Type Duplicate' : Unused code path elimination
//  Block '<S48>/Data Type Duplicate' : Unused code path elimination
//  Block '<S49>/Conversion' : Unused code path elimination
//  Block '<S49>/Data Type Duplicate' : Unused code path elimination
//  Block '<S50>/Conversion' : Unused code path elimination
//  Block '<S50>/Data Type Duplicate' : Unused code path elimination
//  Block '<S7>/Data Type Duplicate' : Unused code path elimination
//  Block '<S8>/Data Type Duplicate' : Unused code path elimination
//  Block '<S9>/Data Type Duplicate' : Unused code path elimination
//  Block '<S10>/Data Type Duplicate' : Unused code path elimination
//  Block '<S12>/Data Type Duplicate' : Unused code path elimination
//  Block '<S13>/Data Type Duplicate' : Unused code path elimination
//  Block '<S14>/Data Type Duplicate' : Unused code path elimination
//  Block '<S15>/Conversion' : Unused code path elimination
//  Block '<S15>/Data Type Duplicate' : Unused code path elimination
//  Block '<S16>/Data Type Duplicate' : Unused code path elimination
//  Block '<S17>/Data Type Duplicate' : Unused code path elimination
//  Block '<S18>/Data Type Duplicate' : Unused code path elimination
//  Block '<S20>/Data Type Duplicate' : Unused code path elimination
//  Block '<S21>/Data Type Duplicate' : Unused code path elimination
//  Block '<S1>/G' : Unused code path elimination
//  Block '<S1>/H' : Unused code path elimination
//  Block '<S1>/N' : Unused code path elimination
//  Block '<S1>/P0' : Unused code path elimination
//  Block '<S1>/Q' : Unused code path elimination
//  Block '<S1>/R' : Unused code path elimination
//  Block '<S45>/CheckSignalProperties' : Unused code path elimination
//  Block '<S46>/CheckSignalProperties' : Unused code path elimination
//  Block '<S82>/DTDup' : Unused code path elimination
//  Block '<Root>/Real Alt' : Unused code path elimination
//  Block '<Root>/Real Az' : Unused code path elimination
//  Block '<S47>/Conversion' : Eliminate redundant data type conversion
//  Block '<S48>/Conversion' : Eliminate redundant data type conversion
//  Block '<S20>/Conversion' : Eliminate redundant data type conversion
//  Block '<S24>/Reshape' : Reshape block reduction
//  Block '<S1>/ReshapeX0' : Reshape block reduction
//  Block '<S1>/Reshapeu' : Reshape block reduction
//  Block '<S1>/Reshapexhat' : Reshape block reduction
//  Block '<S1>/Reshapey' : Reshape block reduction


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
//  '<Root>' : 'RocketDeployment'
//  '<S1>'   : 'RocketDeployment/Kalman Filter'
//  '<S2>'   : 'RocketDeployment/MATLAB Function'
//  '<S3>'   : 'RocketDeployment/PID Controller'
//  '<S4>'   : 'RocketDeployment/Kalman Filter/CalculatePL'
//  '<S5>'   : 'RocketDeployment/Kalman Filter/CalculateYhat'
//  '<S6>'   : 'RocketDeployment/Kalman Filter/CovarianceOutputConfigurator'
//  '<S7>'   : 'RocketDeployment/Kalman Filter/DataTypeConversionA'
//  '<S8>'   : 'RocketDeployment/Kalman Filter/DataTypeConversionB'
//  '<S9>'   : 'RocketDeployment/Kalman Filter/DataTypeConversionC'
//  '<S10>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionD'
//  '<S11>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionEnable'
//  '<S12>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionG'
//  '<S13>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionH'
//  '<S14>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionN'
//  '<S15>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionP'
//  '<S16>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionP0'
//  '<S17>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionQ'
//  '<S18>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionR'
//  '<S19>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionReset'
//  '<S20>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionX'
//  '<S21>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionX0'
//  '<S22>'  : 'RocketDeployment/Kalman Filter/DataTypeConversionu'
//  '<S23>'  : 'RocketDeployment/Kalman Filter/MemoryP'
//  '<S24>'  : 'RocketDeployment/Kalman Filter/Observer'
//  '<S25>'  : 'RocketDeployment/Kalman Filter/ReducedQRN'
//  '<S26>'  : 'RocketDeployment/Kalman Filter/Reset'
//  '<S27>'  : 'RocketDeployment/Kalman Filter/Reshapeyhat'
//  '<S28>'  : 'RocketDeployment/Kalman Filter/ScalarExpansionP0'
//  '<S29>'  : 'RocketDeployment/Kalman Filter/ScalarExpansionQ'
//  '<S30>'  : 'RocketDeployment/Kalman Filter/ScalarExpansionR'
//  '<S31>'  : 'RocketDeployment/Kalman Filter/UseCurrentEstimator'
//  '<S32>'  : 'RocketDeployment/Kalman Filter/checkA'
//  '<S33>'  : 'RocketDeployment/Kalman Filter/checkB'
//  '<S34>'  : 'RocketDeployment/Kalman Filter/checkC'
//  '<S35>'  : 'RocketDeployment/Kalman Filter/checkD'
//  '<S36>'  : 'RocketDeployment/Kalman Filter/checkEnable'
//  '<S37>'  : 'RocketDeployment/Kalman Filter/checkG'
//  '<S38>'  : 'RocketDeployment/Kalman Filter/checkH'
//  '<S39>'  : 'RocketDeployment/Kalman Filter/checkN'
//  '<S40>'  : 'RocketDeployment/Kalman Filter/checkP0'
//  '<S41>'  : 'RocketDeployment/Kalman Filter/checkQ'
//  '<S42>'  : 'RocketDeployment/Kalman Filter/checkR'
//  '<S43>'  : 'RocketDeployment/Kalman Filter/checkReset'
//  '<S44>'  : 'RocketDeployment/Kalman Filter/checkX0'
//  '<S45>'  : 'RocketDeployment/Kalman Filter/checku'
//  '<S46>'  : 'RocketDeployment/Kalman Filter/checky'
//  '<S47>'  : 'RocketDeployment/Kalman Filter/CalculatePL/DataTypeConversionL'
//  '<S48>'  : 'RocketDeployment/Kalman Filter/CalculatePL/DataTypeConversionM'
//  '<S49>'  : 'RocketDeployment/Kalman Filter/CalculatePL/DataTypeConversionP'
//  '<S50>'  : 'RocketDeployment/Kalman Filter/CalculatePL/DataTypeConversionZ'
//  '<S51>'  : 'RocketDeployment/Kalman Filter/CalculatePL/Ground'
//  '<S52>'  : 'RocketDeployment/Kalman Filter/CalculateYhat/Ground'
//  '<S53>'  : 'RocketDeployment/Kalman Filter/Observer/MeasurementUpdate'
//  '<S54>'  : 'RocketDeployment/Kalman Filter/ReducedQRN/Ground'
//  '<S55>'  : 'RocketDeployment/Kalman Filter/UseCurrentEstimator/Enabled Subsystem'
//  '<S56>'  : 'RocketDeployment/PID Controller/Anti-windup'
//  '<S57>'  : 'RocketDeployment/PID Controller/D Gain'
//  '<S58>'  : 'RocketDeployment/PID Controller/Filter'
//  '<S59>'  : 'RocketDeployment/PID Controller/Filter ICs'
//  '<S60>'  : 'RocketDeployment/PID Controller/I Gain'
//  '<S61>'  : 'RocketDeployment/PID Controller/Ideal P Gain'
//  '<S62>'  : 'RocketDeployment/PID Controller/Ideal P Gain Fdbk'
//  '<S63>'  : 'RocketDeployment/PID Controller/Integrator'
//  '<S64>'  : 'RocketDeployment/PID Controller/Integrator ICs'
//  '<S65>'  : 'RocketDeployment/PID Controller/N Copy'
//  '<S66>'  : 'RocketDeployment/PID Controller/N Gain'
//  '<S67>'  : 'RocketDeployment/PID Controller/P Copy'
//  '<S68>'  : 'RocketDeployment/PID Controller/Parallel P Gain'
//  '<S69>'  : 'RocketDeployment/PID Controller/Reset Signal'
//  '<S70>'  : 'RocketDeployment/PID Controller/Saturation'
//  '<S71>'  : 'RocketDeployment/PID Controller/Saturation Fdbk'
//  '<S72>'  : 'RocketDeployment/PID Controller/Sum'
//  '<S73>'  : 'RocketDeployment/PID Controller/Sum Fdbk'
//  '<S74>'  : 'RocketDeployment/PID Controller/Tracking Mode'
//  '<S75>'  : 'RocketDeployment/PID Controller/Tracking Mode Sum'
//  '<S76>'  : 'RocketDeployment/PID Controller/Tsamp - Integral'
//  '<S77>'  : 'RocketDeployment/PID Controller/Tsamp - Ngain'
//  '<S78>'  : 'RocketDeployment/PID Controller/postSat Signal'
//  '<S79>'  : 'RocketDeployment/PID Controller/preSat Signal'
//  '<S80>'  : 'RocketDeployment/PID Controller/Anti-windup/Passthrough'
//  '<S81>'  : 'RocketDeployment/PID Controller/D Gain/Internal Parameters'
//  '<S82>'  : 'RocketDeployment/PID Controller/Filter/Differentiator'
//  '<S83>'  : 'RocketDeployment/PID Controller/Filter/Differentiator/Tsamp'
//  '<S84>'  : 'RocketDeployment/PID Controller/Filter/Differentiator/Tsamp/Internal Ts'
//  '<S85>'  : 'RocketDeployment/PID Controller/Filter ICs/Internal IC - Differentiator'
//  '<S86>'  : 'RocketDeployment/PID Controller/I Gain/Internal Parameters'
//  '<S87>'  : 'RocketDeployment/PID Controller/Ideal P Gain/Passthrough'
//  '<S88>'  : 'RocketDeployment/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S89>'  : 'RocketDeployment/PID Controller/Integrator/Discrete'
//  '<S90>'  : 'RocketDeployment/PID Controller/Integrator ICs/Internal IC'
//  '<S91>'  : 'RocketDeployment/PID Controller/N Copy/Disabled wSignal Specification'
//  '<S92>'  : 'RocketDeployment/PID Controller/N Gain/Passthrough'
//  '<S93>'  : 'RocketDeployment/PID Controller/P Copy/Disabled'
//  '<S94>'  : 'RocketDeployment/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S95>'  : 'RocketDeployment/PID Controller/Reset Signal/Disabled'
//  '<S96>'  : 'RocketDeployment/PID Controller/Saturation/Enabled'
//  '<S97>'  : 'RocketDeployment/PID Controller/Saturation Fdbk/Disabled'
//  '<S98>'  : 'RocketDeployment/PID Controller/Sum/Sum_PID'
//  '<S99>'  : 'RocketDeployment/PID Controller/Sum Fdbk/Disabled'
//  '<S100>' : 'RocketDeployment/PID Controller/Tracking Mode/Disabled'
//  '<S101>' : 'RocketDeployment/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S102>' : 'RocketDeployment/PID Controller/Tsamp - Integral/Passthrough'
//  '<S103>' : 'RocketDeployment/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S104>' : 'RocketDeployment/PID Controller/postSat Signal/Forward_Path'
//  '<S105>' : 'RocketDeployment/PID Controller/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_RocketDeployment_h_

//
// File trailer for generated code.
//
// [EOF]
//
