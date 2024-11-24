#pragma once
#include <stdint.h>
#include "../../xrCore/xrCore.h"

/// <summary>
/// Actually this must be less of sqrt(MAXFLOAT) since we store this value squared.
/// </summary>
constexpr float MAX_FLOAT = 1.0e16f;

/// <summary>
/// 
/// </summary>
constexpr uint32_t MAX_INT = 0x7fffffff;

/// <summary>
/// 
/// </summary>
constexpr bool ALLOW_ROTATE = true;

/// <summary>
/// 
/// </summary>
constexpr float SQRT2PI = 2.506628274631000502415765284811045253006f;

/// <summary>
/// 
/// </summary>
constexpr float ONE_OVER_SIGMA_EXP = (1.0f / 0.7975f);

/// <summary>
/// 
/// </summary>
constexpr float ONEOVERSQRT2PI = (1.f / SQRT2PI);

/// <summary>
/// 
/// </summary>
/// <param name="sigma"></param>
/// <returns></returns>
float NRand(float sigma);

/// <summary>
/// 
/// </summary>
/// <param name="vec"></param>
/// <returns></returns>
float noise3(const Fvector& vec);

/// <summary>
/// 
/// </summary>
/// <param name="v"></param>
/// <param name="freq"></param>
/// <param name="octaves"></param>
/// <returns></returns>
float fractalsum3(const Fvector& v, float freq, int octaves);

/// <summary>
/// 
/// </summary>
/// <param name="v"></param>
/// <param name="freq"></param>
/// <param name="octaves"></param>
/// <returns></returns>
float turbulence3(const Fvector& v, float freq, int octaves);
