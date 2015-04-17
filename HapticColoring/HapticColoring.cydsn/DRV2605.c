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

#include "DRV2605.h"


int drv2605_init(){
    int rc;
    /* Throw in delay */
    CyDelay(10);
    
    
    /* Reset the device and put into RTP Mode */
    rc = i2c_write_reg(DRV2605_ADDR, DRV2605_REG_MODE, DRV2605_DEV_RESET); 
    if(rc != HAPTIC_SUCCESS)
        return rc;
    
    CyDelay(10);
  
    LOG_INFO("DRV2605 Device ID: 0x%02x", drv2605_id());
  
    i2c_write_reg(DRV2605_ADDR, DRV2605_REG_MODE, DRV2605_MODE_REALTIME );
    CyDelay(10);
    
    /* Set INITIAL RTP Playbakck to 0 */
    i2c_write_reg(DRV2605_ADDR, DRV2605_REG_RTPIN, 0x00); 
    CyDelay(10);
    
    /* Select the approprate Library (LRA) */
    i2c_write_reg(DRV2605_ADDR, DRV2605_REG_LIBRARY, DRV2605_LIB_LRA);
    CyDelay(10);
    /* Old Adafruit Code 
    writeRegister8(DRV2605_REG_WAVESEQ1, 1); // strong click
    writeRegister8(DRV2605_REG_WAVESEQ2, 0);
  
    writeRegister8(DRV2605_REG_OVERDRIVE, 0); // no overdrive
  
    writeRegister8(DRV2605_REG_SUSTAINPOS, 0);
    writeRegister8(DRV2605_REG_SUSTAINNEG, 0);
    writeRegister8(DRV2605_REG_BREAK, 0);
    writeRegister8(DRV2605_REG_AUDIOMAX, 0x64);
    
    */
  
    /* Set the Driver to LRA Mode */
    /* TODO: Make this look less awaful */
//    i2c_write_reg(DRV2605_ADDR, DRV2605_REG_FEEDBACK, 0b10110111); /* Set LRA Mode */
//    CyDelay(10);
  
    /* Old adafruit code 
    // turn off N_ERM_LRA
    writeRegister8(DRV2605_REG_FEEDBACK, readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
    // turn on ERM_OPEN_LOOP - I have no idea why this is here 
    writeRegister8(DRV2605_REG_CONTROL3, readRegister8(DRV2605_REG_CONTROL3) | 0x20);
    */
    
    return DRV2605_SUCCESS;
}

uint8_t drv2605_id(){
    return  (i2c_read_reg(DRV2605_ADDR, DRV2605_REG_STATUS) >> 5);   
}

//int drv2605_set_waveform(uint8_t slot, uint8_t w);

int drv2605_go(){
    return i2c_write_reg(DRV2605_ADDR, DRV2605_REG_GO, DRV2605_GO);
}

int drv2605_set_mode();

int drv2605_set_rtp(uint8_t val){
    return i2c_write_reg(DRV2605_ADDR, DRV2605_REG_RTPIN , val);
}

/* Special test / demo functions */
#ifdef DRV2605_TEST
/* TODD: Add Function To trial all of the waveforms */
/* TODO: Add function to  test runing through the RTP_INPUTs */
#endif 
/* [] END OF FILE */
