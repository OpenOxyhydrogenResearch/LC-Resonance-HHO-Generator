/*
  DSS_WRAPPER.CPP
*/

#include "DSS_Wrapper/DSS_Wrapper.h"

DSS_Wrapper::DSS_Wrapper(char clk_pin, char freq_pin, char data_pin)
    : AD9850(clk_pin, freq_pin, data_pin)
{
}

void DSS_Wrapper::PowerDown()
{
  this->down();

  return;
}

void DSS_Wrapper::PowerUp()
{
  this->up();

  return;
}

double DSS_Wrapper::UpdateFreqency(double freq)
{
  return this->_setLimits(freq, DSS_LIMIT_FREQ_MIN, DSS_LIMIT_FREQ_MAX, (1 / DSS_LIMIT_FREQ_MAX));
}

double DSS_Wrapper::UpdatePhase(double phase)
{
  return this->_setLimits(phase, DSS_LIMIT_PHASE_MIN, DSS_LIMIT_PHASE_MAX, (1 / DSS_LIMIT_PHASE_MAX));
}

double DSS_Wrapper::UpdateDuty(double duty)
{
  return this->_setLimits(duty, DSS_LIMIT_DUTY_MIN, DSS_LIMIT_DUTY_MAX);
}



double DSS_Wrapper::_setLimits(double val, double min_limit, double max_limit, double resolution)
{
  double normalized = 0.0;

  if (val < min_limit)
  {
    normalized = min_limit;
  }
  else if (val > max_limit)
  {
    normalized = max_limit;
  }

  if (abs(resolution) > 0.0)
  {
    normalized = floor(normalized / abs(resolution)) * (1 / abs(resolution));
  }

  return normalized;
}