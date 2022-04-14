//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: RocketDeployment.cpp
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
#include "airbrake/RocketDeployment.h"
#include "airbrake/RocketDeployment_private.h"

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (std::abs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = std::floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = std::ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

// Model step function
void RocketDeployment_step(RT_MODEL_RocketDeployment_T *const RocketDeployment_M,
  ExtU_RocketDeployment_T *RocketDeployment_U, ExtY_RocketDeployment_T
  *RocketDeployment_Y)
{
  DW_RocketDeployment_T *RocketDeployment_DW = RocketDeployment_M->dwork;
  real_T Product3_idx_0;
  real_T Product3_idx_1;
  real_T alt_idx;
  real_T dep_idx;
  real_T rtb_Add_p_idx_0;
  real_T rtb_Add_p_idx_1;
  real_T rtb_Saturation;
  real_T rtb_Sum_g;
  real_T tmp;
  boolean_T exitg1;

  // Delay: '<S1>/MemoryX'
  if (RocketDeployment_DW->icLoad != 0) {
    RocketDeployment_DW->MemoryX_DSTATE[0] = 2600.0;
    RocketDeployment_DW->MemoryX_DSTATE[1] = 162.05;
  }

  // Outputs for Enabled SubSystem: '<S24>/MeasurementUpdate' incorporates:
  //   EnablePort: '<S53>/Enable'

  // Sum: '<S53>/Sum' incorporates:
  //   Constant: '<S1>/C'
  //   Constant: '<S1>/D'
  //   Delay: '<S1>/MemoryX'
  //   Inport: '<Root>/Accel_Z'
  //   Inport: '<Root>/Altitude'
  //   Product: '<S53>/C[k]*xhat[k|k-1]'
  //   Product: '<S53>/D[k]*u[k]'
  //   Sum: '<S53>/Add1'

  rtb_Sum_g = RocketDeployment_U->Altitude - ((0.0 *
    RocketDeployment_DW->MemoryX_DSTATE[1] + RocketDeployment_DW->
    MemoryX_DSTATE[0]) + 0.0 * RocketDeployment_U->Accel_Z);

  // Product: '<S53>/Product3'
  Product3_idx_0 = 0.22586543765232608 * rtb_Sum_g;
  Product3_idx_1 = 0.17697267541839251 * rtb_Sum_g;

  // End of Outputs for SubSystem: '<S24>/MeasurementUpdate'

  // Outputs for Enabled SubSystem: '<S31>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S55>/Enable'

  // Sum: '<S55>/Add1' incorporates:
  //   Constant: '<S1>/C'
  //   Delay: '<S1>/MemoryX'
  //   Inport: '<Root>/Altitude'
  //   Product: '<S55>/Product'

  rtb_Sum_g = RocketDeployment_U->Altitude - (0.0 *
    RocketDeployment_DW->MemoryX_DSTATE[1] + RocketDeployment_DW->
    MemoryX_DSTATE[0]);

  // Sum: '<S31>/Add' incorporates:
  //   Delay: '<S1>/MemoryX'
  //   Product: '<S55>/Product2'

  rtb_Add_p_idx_0 = 0.21701680388140648 * rtb_Sum_g +
    RocketDeployment_DW->MemoryX_DSTATE[0];
  rtb_Add_p_idx_1 = 0.17697267541839179 * rtb_Sum_g +
    RocketDeployment_DW->MemoryX_DSTATE[1];

  // End of Outputs for SubSystem: '<S31>/Enabled Subsystem'

  // Outport: '<Root>/Estimated Alt'
  RocketDeployment_Y->EstimatedAlt = rtb_Add_p_idx_0;

  // Outport: '<Root>/Estimated Vel'
  RocketDeployment_Y->EstimatedVel = rtb_Add_p_idx_1;

  // SampleTimeMath: '<S84>/Tsamp' incorporates:
  //   Delay: '<Root>/Delay'
  //   Gain: '<S81>/Derivative Gain'
  //
  //  About '<S84>/Tsamp':
  //   y = u * K where K = 1 / ( w * Ts )

  rtb_Sum_g = 2.0E-6 * RocketDeployment_DW->Delay_DSTATE * 20.0;

  // Sum: '<S98>/Sum' incorporates:
  //   Delay: '<Root>/Delay'
  //   Delay: '<S82>/UD'
  //   DiscreteIntegrator: '<S89>/Integrator'
  //   Gain: '<S94>/Proportional Gain'
  //   Sum: '<S82>/Diff'

  rtb_Saturation = (0.0005 * RocketDeployment_DW->Delay_DSTATE +
                    RocketDeployment_DW->Integrator_DSTATE) + (rtb_Sum_g -
    RocketDeployment_DW->UD_DSTATE);

  // Saturate: '<S96>/Saturation'
  if (rtb_Saturation > 1.0) {
    rtb_Saturation = 1.0;
  } else {
    if (rtb_Saturation < 0.0) {
      rtb_Saturation = 0.0;
    }
  }

  // End of Saturate: '<S96>/Saturation'

  // MATLAB Function: '<Root>/MATLAB Function' incorporates:
  //   Inport: '<Root>/Accel_Z'

  alt_idx = RocketDeployment_U->Accel_Z;
  dep_idx = rt_roundd_snf(rtb_Saturation / 0.02) + 1.0;
  exitg1 = false;
  while ((!exitg1) && (rtb_Add_p_idx_1 > 0.0)) {
    rtb_Add_p_idx_0 += rtb_Add_p_idx_1 * 0.01;
    rtb_Add_p_idx_1 += alt_idx * 0.01;
    alt_idx = rt_roundd_snf((rtb_Add_p_idx_0 - 2200.0) / 10.0) + 1.0;
    tmp = rt_roundd_snf(rtb_Add_p_idx_1) + 1.0;
    if (tmp <= 0.0) {
      exitg1 = true;
    } else {
      if (alt_idx > 85.0) {
        alt_idx = 85.0;
      }

      alt_idx = -9.8 - RocketDeployment_ConstP.MATLABFunction_drag_data[(((
        static_cast<int32_T>(alt_idx) - 1) * 181 + static_cast<int32_T>(tmp)) +
        (static_cast<int32_T>(dep_idx) - 1) * 15385) - 1] / 6.622449;
    }
  }

  // Outport: '<Root>/Estimated Apogee' incorporates:
  //   MATLAB Function: '<Root>/MATLAB Function'

  RocketDeployment_Y->EstimatedApogee = rtb_Add_p_idx_0;

  // Outport: '<Root>/Deployment'
  RocketDeployment_Y->Deployment = rtb_Saturation;

  // Gain: '<S86>/Integral Gain' incorporates:
  //   Delay: '<Root>/Delay'

  rtb_Saturation = 0.02 * RocketDeployment_DW->Delay_DSTATE;

  // Update for Delay: '<S1>/MemoryX'
  RocketDeployment_DW->icLoad = 0U;

  // Product: '<S24>/A[k]*xhat[k|k-1]' incorporates:
  //   Constant: '<S1>/A'
  //   Delay: '<S1>/MemoryX'

  rtb_Add_p_idx_1 = 0.05 * RocketDeployment_DW->MemoryX_DSTATE[1] +
    RocketDeployment_DW->MemoryX_DSTATE[0];
  dep_idx = 0.0 * RocketDeployment_DW->MemoryX_DSTATE[0] +
    RocketDeployment_DW->MemoryX_DSTATE[1];

  // Update for Delay: '<S1>/MemoryX' incorporates:
  //   Constant: '<S1>/B'
  //   Inport: '<Root>/Accel_Z'
  //   Product: '<S24>/B[k]*u[k]'
  //   Product: '<S53>/Product3'
  //   Sum: '<S24>/Add'

  RocketDeployment_DW->MemoryX_DSTATE[0] = (0.0012500000000000002 *
    RocketDeployment_U->Accel_Z + rtb_Add_p_idx_1) + Product3_idx_0;
  RocketDeployment_DW->MemoryX_DSTATE[1] = (0.05 * RocketDeployment_U->Accel_Z +
    dep_idx) + Product3_idx_1;

  // Update for Delay: '<Root>/Delay' incorporates:
  //   Constant: '<Root>/Constant'
  //   MATLAB Function: '<Root>/MATLAB Function'
  //   Sum: '<Root>/Sum'

  RocketDeployment_DW->Delay_DSTATE = rtb_Add_p_idx_0 - 3047.9999999999995;

  // Update for DiscreteIntegrator: '<S89>/Integrator'
  RocketDeployment_DW->Integrator_DSTATE += 0.05 * rtb_Saturation;

  // Update for Delay: '<S82>/UD'
  RocketDeployment_DW->UD_DSTATE = rtb_Sum_g;
}

// Model initialize function
void RocketDeployment_initialize(RT_MODEL_RocketDeployment_T *const
  RocketDeployment_M, ExtU_RocketDeployment_T *RocketDeployment_U,
  ExtY_RocketDeployment_T *RocketDeployment_Y)
{
  DW_RocketDeployment_T *RocketDeployment_DW = RocketDeployment_M->dwork;

  // Registration code

  // states (dwork)
  (void) std::memset(static_cast<void *>(RocketDeployment_DW), 0,
                     sizeof(DW_RocketDeployment_T));

  // external inputs
  (void)std::memset(RocketDeployment_U, 0, sizeof(ExtU_RocketDeployment_T));

  // external outputs
  (void) std::memset(static_cast<void *>(RocketDeployment_Y), 0,
                     sizeof(ExtY_RocketDeployment_T));

  // InitializeConditions for Delay: '<S1>/MemoryX'
  RocketDeployment_DW->icLoad = 1U;
}

// Model terminate function
void RocketDeployment_terminate(RT_MODEL_RocketDeployment_T *const
  RocketDeployment_M)
{
  // (no terminate code required)
  UNUSED_PARAMETER(RocketDeployment_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
