#pragma once

#include "minfft.h"


namespace das
{
  void fft_real_forward(const TArray<float> & real_signal, TArray<float2> & complex_frequencies, Context * context, LineInfoArg * at);
  void fft_calculate_magnitudes(const TArray<float2> & complex_frequencies, TArray<float> & magnitudes, Context * context, LineInfoArg * at);
  void fft_calculate_normalized_magnitudes(const TArray<float2> & complex_frequencies, TArray<float> & magnitudes, Context * context, LineInfoArg * at);
  void fft_calculate_log_magnitudes(const TArray<float2> & complex_frequencies, TArray<float> & magnitudes, Context * context, LineInfoArg * at);
  void fft_real_inverse(const TArray<float2> & complex_frequencies, TArray<float> & real_signal, Context * context, LineInfoArg * at);
}
