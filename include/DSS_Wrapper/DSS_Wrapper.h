/*
  DSS_Wrapper.H
*/

// ensure this library description is only included once
#ifndef DSS_WRAPPER_h
#define DSS_WRAPPER_h

#define DSS_LIMIT_FREQ_MIN 8.0e-9
#define DSS_LIMIT_FREQ_MAX 125.0e6

#define DSS_LIMIT_PHASE_MIN 5.0e-9
#define DSS_LIMIT_PHASE_MAX 2.0e8

#define DSS_LIMIT_DUTY_MIN 0.01
#define DSS_LIMIT_DUTY_MAX 99.99

#define DSS_EXT_CLK_TIMING EX_CLK

#include <AD9850.h>
#include <math.h>

class DSS_Wrapper : public AD9850
{
private:
  double _setLimits(double val, double min_limit, double max_limit, double resolution = 0.0);

public:
  DSS_Wrapper(char clk_pin, char freq_pin, char data_pin);
  void PowerDown();
  void PowerUp();
  double UpdateFreqency(double freq);
  double UpdatePhase(double phase);
  double UpdateDuty(double duty);
  
};

#endif
