/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 * @author hngiannopoulos
 * Library to drive the DRV2605 Haptic Feedback Controller 
 * ========================================
*/

#include <project.h>
#include "i2c_driver.h"
#include "log.h"

#ifndef DRV2605_H_
#define DRV2605_H_
  
#define DRV2605_SUCCESS 0

/* Start of Register #defines */

    
#define DRV2605_ADDR (0xB4 >> 1)

#define DRV2605_REG_STATUS 0x00
#define DRV2605_REG_MODE 0x01
#define DRV2605_MODE_INTTRIG  0x00
#define DRV2605_MODE_EXTTRIGEDGE  0x01
#define DRV2605_MODE_EXTTRIGLVL  0x02
#define DRV2605_MODE_PWMANALOG  0x03
#define DRV2605_MODE_AUDIOVIBE  0x04
#define DRV2605_MODE_REALTIME  0x05
#define DRV2605_MODE_DIAGNOS  0x06
#define DRV2605_MODE_AUTOCAL  0x07
    
        
#define DRV2605_DEV_RESET (1<<7)
#define DRV2605_STANDBY (1<<6)


#define DRV2605_REG_RTPIN 0x02 /* RTP Register */

/* LIBRARY Registers */    
#define DRV2605_REG_LIBRARY     0x03
#define DRV2605_LIB_EMPTY       0
#define DRV2605_LIB_TS2200A     1
#define DRV2605_LIB_TS2200B     2
#define DRV2605_LIB_TS2200C     3
#define DRV2605_LIB_TS2200D     4
#define DRV2605_LIB_TS2200E     5
#define DRV2605_LIB_TS2200F     7
#define DRV2605_LIB_LRA         6 /* This is the one we want */

    

#define DRV2605_REG_WAVESEQ1 0x04
#define DRV2605_REG_WAVESEQ2 0x05
#define DRV2605_REG_WAVESEQ3 0x06
#define DRV2605_REG_WAVESEQ4 0x07
#define DRV2605_REG_WAVESEQ5 0x08
#define DRV2605_REG_WAVESEQ6 0x09
#define DRV2605_REG_WAVESEQ7 0x0A
#define DRV2605_REG_WAVESEQ8 0x0B

#define DRV2605_REG_GO  0x0C
#define DRV2605_GO      0x01
        
#define DRV2605_REG_OVERDRIVE 0x0D
#define DRV2605_REG_SUSTAINPOS 0x0E
#define DRV2605_REG_SUSTAINNEG 0x0F
#define DRV2605_REG_BREAK 0x10
#define DRV2605_REG_AUDIOCTRL 0x11
#define DRV2605_REG_AUDIOLVL 0x12
#define DRV2605_REG_AUDIOMAX 0x13
#define DRV2605_REG_RATEDV 0x16
#define DRV2605_REG_CLAMPV 0x17
#define DRV2605_REG_AUTOCALCOMP 0x18
#define DRV2605_REG_AUTOCALEMP 0x19
    
#define DRV2605_REG_FEEDBACK 0x1A /* We care about this one */
#define DRV2605_LRA_MODE (1 << 7 )
    
#define DRV2605_REG_CONTROL1 0x1B
#define DRV2605_REG_CONTROL2 0x1C
#define DRV2605_REG_CONTROL3 0x1D
#define DRV2605_REG_CONTROL4 0x1E
#define DRV2605_REG_VBAT 0x21
#define DRV2605_REG_LRARESON 0x22
    

/* Function Prototypes */
   
/** Returns the Device ID field in the device Status Register.
  * @return Device ID.
            4 - DRV2604
            3 - DRV2605
            6 - DRV2604L
            7 - DRV2605L
  */
uint8_t drv2605_id();    

/** Initiallized (Programms) the drv2605.
  * @returns 0 - success otherwise error 
  */
int drv2605_init();

/** Sets a waveform pattern.
 * @param slot The slot the waveform will go int
 * @param w Register name for the waveform
 */
int drv2605_set_waveform(uint8_t slot, uint8_t w);

/** Selects the haptic library on the DRV2605.
 * @param lib See DRV2605_LIB_* for possible inputs.
 * @note since we are using a LRA instead of an ERM, we can ignore this.
 */
int drv2605_select_library(uint8_t lib);

/** Sets the GO bit in the drv2605. 
 * @return 0 Success or 1 for errors.
 */
int drv2605_go();

/** Sets the DRV2605 Playback mode.
 * @reutrn 0 - success, 1 any errors 
 */
int drv2605_set_mode();

/** Sets the Real time playback Register.
 * @param val Value for the RTP Register.
 * @return 0 - success, 1 any errors 
 */
int drv2605_set_rtp(uint8_t val);

/* Special test / demo functions */
#ifdef DRV2605_TEST
/* TODD: Add Function To trial all of the waveforms */
/* TODO: Add function to  test runing through the RTP_INPUTs */
#endif 

/* TODO: Add auto callibration Functions */


#endif 
/* [] END OF FILE */
