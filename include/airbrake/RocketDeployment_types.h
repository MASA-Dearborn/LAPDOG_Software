//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: RocketDeployment_types.h
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
#ifndef RTW_HEADER_RocketDeployment_types_h_
#define RTW_HEADER_RocketDeployment_types_h_
#include "rtwtypes.h"

// Model Code Variants
#ifndef DEFINED_TYPEDEF_FOR_struct_vpm6FqcbiI86sgApPlqvxB_
#define DEFINED_TYPEDEF_FOR_struct_vpm6FqcbiI86sgApPlqvxB_

typedef struct {
  real_T precision;
  real_T step_size;
  real_T raw[126];
  real_T max;
  real_T min;
  real_T len;
} struct_vpm6FqcbiI86sgApPlqvxB;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_j2876VLQPqxMZ2laX30lRC_
#define DEFINED_TYPEDEF_FOR_struct_j2876VLQPqxMZ2laX30lRC_

typedef struct {
  real_T step_size;
  real_T raw[126];
  real_T len;
} struct_j2876VLQPqxMZ2laX30lRC;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_sihpxvGhLiEejioGgEktIB_
#define DEFINED_TYPEDEF_FOR_struct_sihpxvGhLiEejioGgEktIB_

typedef struct {
  real_T raw[126];
} struct_sihpxvGhLiEejioGgEktIB;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_uuzHnlRCYU7or97oNVCNSD_
#define DEFINED_TYPEDEF_FOR_struct_uuzHnlRCYU7or97oNVCNSD_

typedef struct {
  struct_vpm6FqcbiI86sgApPlqvxB vel;
  struct_vpm6FqcbiI86sgApPlqvxB alt;
  struct_j2876VLQPqxMZ2laX30lRC deployment;
  struct_sihpxvGhLiEejioGgEktIB drag;
} struct_uuzHnlRCYU7or97oNVCNSD;

#endif

// Forward declaration for rtModel
typedef struct tag_RTM_RocketDeployment_T RT_MODEL_RocketDeployment_T;

#endif                                 // RTW_HEADER_RocketDeployment_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
