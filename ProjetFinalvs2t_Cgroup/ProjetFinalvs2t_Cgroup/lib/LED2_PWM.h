//*****************************************************************************
//*****************************************************************************
//  FILENAME: LED2_PWM.h
//   Version: 2.5, Updated on 2014/7/14 at 8:14:50
//  Generated by PSoC Designer 5.4.2946
//
//  DESCRIPTION: PWM16 User Module C Language interface file
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2014. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef LED2_PWM_INCLUDE
#define LED2_PWM_INCLUDE

#include <m8c.h>

#pragma fastcall16 LED2_PWM_EnableInt
#pragma fastcall16 LED2_PWM_DisableInt
#pragma fastcall16 LED2_PWM_Start
#pragma fastcall16 LED2_PWM_Stop
#pragma fastcall16 LED2_PWM_wReadCounter              // Read  DR0
#pragma fastcall16 LED2_PWM_WritePeriod               // Write DR1
#pragma fastcall16 LED2_PWM_wReadPulseWidth           // Read  DR2
#pragma fastcall16 LED2_PWM_WritePulseWidth           // Write DR2

// The following symbols are deprecated.
// They may be omitted in future releases
//
#pragma fastcall16 wLED2_PWM_ReadCounter              // Read  DR0 (Deprecated)
#pragma fastcall16 wLED2_PWM_ReadPulseWidth           // Read  DR2 (Deprecated)


//-------------------------------------------------
// Prototypes of the LED2_PWM API.
//-------------------------------------------------

extern void LED2_PWM_EnableInt(void);                  // Proxy Class 1
extern void LED2_PWM_DisableInt(void);                 // Proxy Class 1
extern void LED2_PWM_Start(void);                      // Proxy Class 1
extern void LED2_PWM_Stop(void);                       // Proxy Class 1
extern WORD LED2_PWM_wReadCounter(void);               // Proxy Class 2
extern void LED2_PWM_WritePeriod(WORD wPeriod);        // Proxy Class 1
extern WORD LED2_PWM_wReadPulseWidth(void);            // Proxy Class 1
extern void LED2_PWM_WritePulseWidth(WORD wPulseWidth);// Proxy Class 1

// The following functions are deprecated.
// They may be omitted in future releases
//
extern WORD wLED2_PWM_ReadCounter(void);            // Deprecated
extern WORD wLED2_PWM_ReadPulseWidth(void);         // Deprecated


//-------------------------------------------------
// Constants for LED2_PWM API's.
//-------------------------------------------------

#define LED2_PWM_CONTROL_REG_START_BIT         ( 0x01 )
#define LED2_PWM_INT_REG_ADDR                  ( 0x0df )
#define LED2_PWM_INT_MASK                      ( 0x20 )


//--------------------------------------------------
// Constants for LED2_PWM user defined values
//--------------------------------------------------

#define LED2_PWM_PERIOD                        ( 0x8fa )
#define LED2_PWM_PULSE_WIDTH                   ( 0xa6 )


//-------------------------------------------------
// Register Addresses for LED2_PWM
//-------------------------------------------------

#pragma ioport  LED2_PWM_COUNTER_LSB_REG:   0x050          //DR0 Count register LSB
BYTE            LED2_PWM_COUNTER_LSB_REG;
#pragma ioport  LED2_PWM_COUNTER_MSB_REG:   0x054          //DR0 Count register MSB
BYTE            LED2_PWM_COUNTER_MSB_REG;
#pragma ioport  LED2_PWM_PERIOD_LSB_REG:    0x051          //DR1 Period register LSB
BYTE            LED2_PWM_PERIOD_LSB_REG;
#pragma ioport  LED2_PWM_PERIOD_MSB_REG:    0x055          //DR1 Period register MSB
BYTE            LED2_PWM_PERIOD_MSB_REG;
#pragma ioport  LED2_PWM_COMPARE_LSB_REG:   0x052          //DR2 Compare register LSB
BYTE            LED2_PWM_COMPARE_LSB_REG;
#pragma ioport  LED2_PWM_COMPARE_MSB_REG:   0x056          //DR2 Compare register MSB
BYTE            LED2_PWM_COMPARE_MSB_REG;
#pragma ioport  LED2_PWM_CONTROL_LSB_REG:   0x053          //Control register LSB
BYTE            LED2_PWM_CONTROL_LSB_REG;
#pragma ioport  LED2_PWM_CONTROL_MSB_REG:   0x057          //Control register MSB
BYTE            LED2_PWM_CONTROL_MSB_REG;
#pragma ioport  LED2_PWM_FUNC_LSB_REG:  0x150              //Function register LSB
BYTE            LED2_PWM_FUNC_LSB_REG;
#pragma ioport  LED2_PWM_FUNC_MSB_REG:  0x154              //Function register MSB
BYTE            LED2_PWM_FUNC_MSB_REG;
#pragma ioport  LED2_PWM_INPUT_LSB_REG: 0x151              //Input register LSB
BYTE            LED2_PWM_INPUT_LSB_REG;
#pragma ioport  LED2_PWM_INPUT_MSB_REG: 0x155              //Input register MSB
BYTE            LED2_PWM_INPUT_MSB_REG;
#pragma ioport  LED2_PWM_OUTPUT_LSB_REG:    0x152          //Output register LSB
BYTE            LED2_PWM_OUTPUT_LSB_REG;
#pragma ioport  LED2_PWM_OUTPUT_MSB_REG:    0x156          //Output register MSB
BYTE            LED2_PWM_OUTPUT_MSB_REG;
#pragma ioport  LED2_PWM_INT_REG:       0x0df              //Interrupt Mask Register
BYTE            LED2_PWM_INT_REG;


//-------------------------------------------------
// LED2_PWM Macro 'Functions'
//-------------------------------------------------

#define LED2_PWM_Start_M \
   ( LED2_PWM_CONTROL_LSB_REG |=  LED2_PWM_CONTROL_REG_START_BIT )

#define LED2_PWM_Stop_M  \
   ( LED2_PWM_CONTROL_LSB_REG &= ~LED2_PWM_CONTROL_REG_START_BIT )

#define LED2_PWM_EnableInt_M   \
   M8C_EnableIntMask(  LED2_PWM_INT_REG, LED2_PWM_INT_MASK )

#define LED2_PWM_DisableInt_M  \
   M8C_DisableIntMask( LED2_PWM_INT_REG, LED2_PWM_INT_MASK )

#endif
// end of file LED2_PWM.h
