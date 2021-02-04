/*
  H2OtoHHO.cpp
*/

#include "H2OtoHHO.h"

// include this library's description file
//#include <LiquidCrystal.h>
//#include <Tone.h>
//#include "pitches.h"
//#include "LCDKeypad\LCDKeypad.h"
//#include "DFR_Key\DFR_Key.h"
//#include "AD9850\AD9850.h"

//#include <H2OtoHHO.h>
// ensure this library description is only included once

/* CREATE DFR Keypad CLASS INSTANCE */
//DFR_Key keypad;
//---------------------------------------------

/* Define Locale Variables */
//int FuncKey = 0;
//String keyString = "";
//int F_Resonace = 4243;                                                  //Variable for Locked frequency
//int hz = freqmin;
//int scalerg = 0;                                                  //Variable for SLRANGE POT
//int scale = 0;                                                    //Scale variable for manual frequency adjust buttons
//int adjfreq = freq;                                               //Resulting frequency from auto scan and fine tune - firepinto 10/27/14
//int volt = 0;
//int vmax = 0;
//int intval = 0;
//int DSS_Gateread = 0;
//int DSS_Gatef = 1;
//int duty = 512;
//int dutyP = 50;
//int minusstate = 0;                                               //Variable for minus button manual frequency adjustment
//int plusstate = 0;                                                //Variable for plus button manual frequency adjustment
//int lastMstate = 0;                                               //last state for minus button
//int lastPstate = 0;                                               //last state for plus button
//int select = 0;                                                   //variable for select button
//int lastselect = 0;                                               //last state of the select button
//int dscan = 0;                                                    //time delay between frequency increments in milliseconds
//int stpscna = 0;                                                  //Aborts scanning when equal to 1
//int stpscnb = 0;                                                  //Aborts scanning when equal to 1
//int menu = 0;                                                     //0=No field; 1=T1 field; 2=T3 field; 3=DY field; 4=DL field; 5=SR MAX field; 6=SR MIN field.

//unsigned long it = 0;
//unsigned long itlcd = 0;
//unsigned long reflcd = 250;                                       // LCD refresh rate mS
//int odd = false;
//---------------------------------------------

byte H2OtoHHO::_icon_rt_arrow[CUSTOM_CHARACTER_BYTES] = {
    B00000,
    B00100,
    B00010,
    B11111,
    B11111,
    B00010,
    B00100,
    B00000,
};

byte H2OtoHHO::_icon_up_arrow[CUSTOM_CHARACTER_BYTES] = {
    B00100,
    B01110,
    B10101,
    B00100,
    B00100,
    B00100,
    B00100,
    B00100,
};

byte H2OtoHHO::_icon_dn_arrow[CUSTOM_CHARACTER_BYTES] = {
    B00100,
    B00100,
    B00100,
    B00100,
    B00100,
    B10101,
    B01110,
    B00100,
};

byte H2OtoHHO::_icon_lf_arrow[CUSTOM_CHARACTER_BYTES] = {
    B00000,
    B00100,
    B01000,
    B11111,
    B11111,
    B01000,
    B00100,
    B00000,
};

byte H2OtoHHO::_icon_select[CUSTOM_CHARACTER_BYTES] = {
    B00000,
    B01110,
    B11111,
    B11111,
    B11111,
    B11111,
    B01110,
    B00000,
};

byte H2OtoHHO::_icon_padlock[CUSTOM_CHARACTER_BYTES] = { //custom character, it's a lock
    B01110,
    B10001,
    B10001,
    B11111,
    B11011,
    B11011,
    B11111,
    B00000};

byte H2OtoHHO::_icon_water_molecule[CUSTOM_CHARACTER_BYTES] = { //custom character, it's a Water Molecule
    B11000,
    B11000,
    B00111,
    B00111,
    B00111,
    B11000,
    B11000,
    B00000};

/*
String H2OtoHHO::_mainMenuItems[MAIN_MENU_ITEMS_COUNT] = {
    MAIN_MENU_ITEM0,
    MAIN_MENU_ITEM1,
    MAIN_MENU_ITEM2,
    MAIN_MENU_ITEM3
};
*/

H2OtoHHO::H2OtoHHO()
    : Screen(),
      Ctrls(),
      DSS_Pulse(DDS1_CLK_Pin, DDS1_FQ_Pin, DDS1_DATA_Pin),
      DSS_Gate(DDS0_CLK_Pin, DDS0_FQ_Pin, DDS0_DATA_Pin)
{
  /* CREATE LCDKeypad CLASS INSTANCES */
  //Screen = new LCDKeypad();
  //---------------------------------------------

  /* CREATE DFR_Key CLASS INSTANCES */
  //Ctrls = new DFR_Key();
  //---------------------------------------------

  /* CREATE AD9850 CLASS INSTANCES */
  //DSS_Gate = new AD9850(DDS0_CLK_Pin, DDS0_FQ_Pin, DDS0_DATA_Pin);                   // w_clk, fq_ud, Sdata
  //pulse = new AD9850(DDS1_CLK_Pin, DDS1_FQ_Pin, DDS1_DATA_Pin);                  // w_clk, fq_ud, Sdata
  //---------------------------------------------

  /* Initialize AD9850 CLASS INSTANCES */
  Screen.createChar(CURSOR_SELECT, _icon_select);
  Screen.createChar(CURSOR_LEFT, _icon_lf_arrow);
  Screen.createChar(CURSOR_UP, _icon_up_arrow);
  Screen.createChar(CURSOR_DOWN, _icon_dn_arrow);
  Screen.createChar(CURSOR_RIGHT, _icon_rt_arrow);
  Screen.createChar(CUSTOM_LOCK, _icon_padlock);
  Screen.createChar(CUSTOM_WATER_MOLECULE, _icon_water_molecule);

  this->DSS_Pulse.PowerUp();
  this->DSS_Gate.PowerUp();

  this->_pulse_freq.set(this->DSS_Pulse.UpdateFreqency(10.0 * DSS_LIMIT_FREQ_MIN));
  this->_gate_freq.set(this->DSS_Gate.UpdateFreqency(DSS_LIMIT_FREQ_MIN));
  this->_gate_duty.set(this->DSS_Gate.UpdateDuty(50.0));
  this->_resonance_voltge.set(0.0);
}

/*
H2OtoHHO::LoadSymbols()
{
	createChar(CURSOR_RIGHT, _c_right);
	createChar(CURSOR_UP, _c_up);
	createChar(CURSOR_DOWN, _c_down);
	createChar(CURSOR_LEFT, _c_left);
	createChar(CURSOR_SELECT, _c_select[);
	createChar(CUSTOM_LOCK, _custom_lock);
	createChar(CUSTOM_WATER_MOLECULE, _custom_watermol);
}
*/

double H2OtoHHO::DSSUpdater(DSS_Wrapper *myDSS, double freq, double phase, double duty)
{
  myDSS->UpdatePhase(phase);
  myDSS->UpdateDuty(duty);

  return myDSS->UpdateFreqency(freq);
}

/* Scans Resonant Frequency */
int H2OtoHHO::ResonanceScan()
{
  uint32_t lockFreq = 0;
  int max_interval = 0;

  Screen.clear();
  Screen.print("  SCANNING RANGE....  ");

  max_interval = (int) floor(1.0 / SCAN_PULSE_FREQ_INTERVAL);

  // Sweep frequency from 'F_Scan_min' to 'F_Scan_max'
  for (int i = 1; i < max_interval; i++)
  {
    _gate_freq.set(this->DSS_Gate.UpdateFreqency(i * SCAN_PULSE_FREQ_INTERVAL));
    _pulse_freq.set(this->DSS_Pulse.UpdateFreqency(10.0 * i * SCAN_PULSE_FREQ_INTERVAL));

    Screen.setCursor(3, 1);
    Screen.print(i);
    Screen.print(" Hz  ");
  }

  delay(200);
  lockFreq = 4243;
  Screen.print(" ");
  Screen.write(CUSTOM_LOCK);
  Screen.print(" ");
  Screen.print(lockFreq);
  Screen.print(" Hz  ");
  delay(2000);

  return lockFreq;
}
//---------------------------------------------

/* Home Screen  */
int H2OtoHHO::HomeScreen()
{
  int err_code = 0;
  //char *dispStr = NULL;
  //etl::string<10> test = "hello";

  //etl::string_stream strStre();

  //strBuff.set
  //strBuff << "009.99" << ends;

  // Clears display
  Screen.clear();

  // Format and Display Line 1
  Screen.setCursor(0, 0);
  Screen.print('G');

  Screen.setCursor(1, 0);
  //sprintf(tmpStr.c_str(), "%03.2f", _gate_freq.get());
  Screen.print(_gate_freq.get());

  //Screen.setCursor(7, 0);
  //Screen.print(getUnitPrefix(_gate_freq.get()));

  Screen.setCursor(8, 0);
  Screen.print("Hz@");

  //Screen.setCursor(11, 0);
  //sprintf(tmpStr, "%03.2f", _gate_duty.get());
  //Screen.print(tmpStr);

  Screen.setCursor(15, 0);
  Screen.print("%");

  // Format and Display Line 2
  Screen.setCursor(0, 1);
  Screen.print('P');

  Screen.setCursor(1, 1);
  Screen.print("009.99");

  Screen.setCursor(7, 1);
  Screen.print("k");

  Screen.setCursor(8, 1);
  Screen.print("Hz");

  Screen.setCursor(8, 1);
  Screen.print("Hz");

  Screen.setCursor(10, 1);
  Screen.write(CUSTOM_LOCK);

  Screen.setCursor(11, 1);
  Screen.print("09.9");

  Screen.setCursor(15, 1);
  Screen.print("V");

  return err_code;
}
//---------------------------------------------

/* Main Menu Function  */
int H2OtoHHO::MainMenu()
{
  int k = 0, exitCode = -1, SelectedItem = 0;
  //, keypress= 0;

  do
  {
    //keypress = H2OtoHHO::button();

    switch (Screen.button())
    {
      //case KEYPAD_RIGHT:
      //  break;

    case KEYPAD_UP:
      if (SelectedItem > 0)
      {
        SelectedItem--;
        //Screen.setCursor(0, 1);
        //Screen.print(_mainMenuItems[SelectedItem]);
        delay(2000);
      }
      //else
      // buzzer.play( NOTE_C4, BuzzerShortTone );

      //exitCode = 0;
      break;

    case KEYPAD_DOWN:
      if (SelectedItem < MAIN_MENU_ITEMS_COUNT)
      {
        SelectedItem++;
        //Screen.setCursor(0, 1);
        //Screen.print(_mainMenuItems[SelectedItem]);
        delay(2000);
      }
      //else
      //buzzer.play( NOTE_C4, BuzzerShortTone );

      //exitCode = 0;
      break;

      //case KEYPAD_LEFT:
      //  break;

    case KEYPAD_SELECT:
      Screen.begin(16, 2);
      Screen.clear();
      Screen.print("     MAIN");
      Screen.setCursor(0, 1);
      Screen.print("     MENU");
      delay(3000);

      for (k = 0; k < 16; k++)
      {
        Screen.scrollDisplayLeft();
        delay(200);
      }

      MainMenu();

      break;

    default:
      exitCode = 0;
    }

  } while (exitCode != -1);

  return exitCode;
}
//---------------------------------------------

/* Updates Display upon Keypress */
int H2OtoHHO::UpdateKeypress(int keyPress)
{
  //if (keyPress != KEYPAD_NONE)
  //{
  Screen.clear();
  Screen.setCursor(0, 0);
  Screen.print("Current Key:");
  Screen.setCursor(0, 1);
  Screen.print(keyPress);
  Screen.print(" => ");
  Screen.print(analogRead(0));
  Screen.print(", ");
  Screen.print(Screen.button());
  delay(1000);
  //}
  return EXIT_SUCCESS;
}
//---------------------------------------------

/* Updates Display upon Keypress */
/*
int getConfigData(String cfgfile = CONFIG_FILE, String locale = CONFIG_LOCALE)
{
  int lenStr = cfgfile.length() + 1;

  char *xmlfile = new char[lenStr];

  cfgfile.toCharArray(xmlfile, lenStr);

  // this open and parse the XML file:
  XMLNode xConfigNode = XMLNode::openFileHelper(xmlfile, "ConfigFile");

  // this prints DisplayElement name attribute:
  XMLNode xNode = xConfigNode.getChildNode("DisplayElement");
  printf("'DisplayElement' name is: '%s'\n", xNode.getChildNode("DisplayElement").getAttribute("name"));

  // this prints "Hello world!":
  printf("Text inside Header tag is :'%s'\n", xNode.getText());

  // this gets the number of "NumericPredictor" tags:
  xNode = xConfigNode.getChildNode("RegressionModel").getChildNode("RegressionTable");
  int n = xNode.nChildNode("NumericPredictor");

  // this prints the "coefficient" value for all the "NumericPredictor" tags:
  for (int i = 0; i < n; i++)
    printf("coeff %i=%f\n", i + 1, atof(xNode.getChildNode("NumericPredictor", i).getAttribute("coefficient")));

  // this prints a formatted ouput based on the content of the first "Extension" tag of the XML file:
  char *t = xConfigNode.getChildNode("Extension").createXMLString(true);
  printf("%s\n", t);
  free(t);

  return EXIT_SUCCESS;
}
*/
//---------------------------------------------

/* Updates Display upon Keypress */
char getUnitPrefix(double val)
{
  int order = 0;
  char *prefixArray = NULL;

  String prefixStr = UNIT_MERTIC_PREFIX;
  prefixArray = new char[prefixStr.length() + 1];

  prefixStr.toCharArray(prefixArray, sizeof(prefixArray));

  for (int i = -3; i <= 3; i++)
  {
    if ((val * 1 / pow(10, 3 * i)) <= 1.0)
    {
      order = i;
      break;
    }
  }

  return prefixArray[order + 3];
}
//---------------------------------------------
