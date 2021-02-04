/*
  H2OtoHHO.h
*/


// ensure this library description is only included once
#ifndef H2OtoHHO_h
#define H2OtoHHO_h

// library interface constant definitions
#define CUSTOM_CHARACTER_BYTES 8

// library interface description
#define SCAN_PULSE_FREQ_INTERVAL 50.0 //Scan interval resolution for pulse trigger frequency auto tune scale in hertz (Hz).
#define SCAN_PULSE_FREQ_MIN 500.0     //Lower bound of pulse trigger frequency auto tune scale in hertz (Hz).
#define SCAN_PULSE_FREQ_MAX 5000.0    //Upper bound of pulse trigger frequency auto tune scale in hertz (Hz).
#define SCAN_GATE_FREQ_INTERVAL 10.0  //Scan interval resolution for gate trigger frequency auto tune scale in hertz (Hz).
#define SCAN_GATE_FREQ_MIN 1.0        //Lower bound of gate trigger frequency auto tune scale in hertz (Hz).
#define SCAN_GATE_FREQ_MAX 1000.0     //Upper bound of gate trigger frequency auto tune scale in hertz (Hz).
#define SCAN_GATE_DUTY_INTERVAL 5.0  //Scan interval resolution for gate trigger duty cycle auto tune scale as percentage (%).
#define SCAN_GATE_DUTY_MIN 5.0       //Lower bound of gate trigger duty cycle auto tune scale as percentage (%).
#define SCAN_GATE_DUTY_MAX 95.0      //Upper bound of gate trigger duty cycle auto tune scale as percentage (%).

#define CURSOR_SELECT 0
#define CURSOR_LEFT 1
#define CURSOR_UP 2
#define CURSOR_DOWN 3
#define CURSOR_RIGHT 4
#define CUSTOM_WATER_MOLECULE 5
#define CUSTOM_LOCK 6

#define DISPLAY_LINES_ROWS 2
#define DISPLAY_LINES_COLUMNS 16

#define CONFIG_FILE "uix_config.xml"
#define CONFIG_LOCALE "EN-JM"
//#define UNIT_MERTIC_PREFIX {'G','M','K',' ','m','u','p'}
#define UNIT_MERTIC_PREFIX "GMK mup"

#define MAIN_MENU_ITEMS_COUNT 4
#define MAIN_MENU_ITEM0 " 1. Resonance Re-Scan."
#define MAIN_MENU_ITEM1 " 2. [Option #2]"
#define MAIN_MENU_ITEM2 " 3. Debug Mode"
#define MAIN_MENU_ITEM3 " 4. Exit Menu!"

#define SUB_MENU1_COUNT 4
#define SUB_MENU1_ITEM0 " 1. Option 1"
#define SUB_MENU1_ITEM1 " 2. Option 2"
#define SUB_MENU1_ITEM2 " 3. Option 3"
#define SUB_MENU1_ITEM3 " 4. Back..."

/* I\O PIN MAPPING AD9850 MODULE 0- TriggerRamp TriggerPulseuency Generator  */
#define DDS0_CLK_Pin 22
#define DDS0_FQ_Pin 23
#define DDS0_DATA_Pin 24
#define DDS0_RESET_Pin 25

/* I\O PIN MAPPING AD9850 MODULE 1- Pulse TriggerPulseuency Generator */
#define DDS1_CLK_Pin 26
#define DDS1_FQ_Pin 27
#define DDS1_DATA_Pin 28
#define DDS1_RESET_Pin 29

/* I\O PIN MAPPING BUZZER MODULE  */
//const uint8_t Buzzer_Pin = 30;
//const unsigned int BuzzerToneFq = NOTE_C4;
//const unsigned long BuzzerShortTone = 500;
//const unsigned long BuzzerLongTone = 1000;

/* CREATE BUZZER CLASS INSTANCE */
//Tone buzzer[1];
//buzzer[0].begin(Buzzer_Pin);


#include "etl_profile.h"
#include <etl/string.h>
#include <etl/observer.h>
//#include <iomanip>
//#include <string>
//#include "xmlParser/xmlParser.h"

//#include "UIX_SCHEMA/uix_schema.hxx"
//#include "UIX_SCHEMA/uix_schema-pimpl.hxx"


#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#if defined(ARDUINO)
#include <LCDKeypad.h>
#include <DFR_Key.h>
#include "DSS_Wrapper/DSS_Wrapper.cpp"
#endif

//#include <stdio.h>  // to get "printf" function
//#include <stdlib.h> // to get "free" function
//#include <math.h>


//using namespace std;
using namespace etl;

template <typename T>
class Attribute
{
protected:
  T m_val;

public:
  T *getAddress() { return &m_val; }
  T get() { return m_val; }
  void set(T v) { m_val = v; }
};

class H2OtoHHO
{
private:
  Attribute<double> _pulse_freq;
  Attribute<double> _gate_freq;
  Attribute<double> _gate_duty;
  Attribute<double> _resonance_voltge;
  //etl::string<DISPLAY_LINES_ROWS> _display_chars[DISPLAY_LINES_COLUMNS];

protected:
  static byte _icon_rt_arrow[];
  static byte _icon_up_arrow[];
  static byte _icon_dn_arrow[];
  static byte _icon_lf_arrow[];
  static byte _icon_select[];
  static byte _icon_padlock[];
  static byte _icon_water_molecule[];
  //static String _mainMenuItems[];

public:
  LCDKeypad Screen;
  DFR_Key Ctrls;
  DSS_Wrapper DSS_Pulse;
  DSS_Wrapper DSS_Gate;

  H2OtoHHO();
  int ResonanceScan();
  int HomeScreen();
  int MainMenu();
  int UpdateKeypress(int keypress);
  double DSSUpdater(DSS_Wrapper *myDSS, double freq, double phase = 0.0, double duty = 50.0);

  //int getConfigData(String cfgfile = CONFIG_FILE, String locale = CONFIG_LOCALE);
  //char getUnitPrefix(double val);
};

#endif