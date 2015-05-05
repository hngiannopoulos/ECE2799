/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include "log.h"
/* TODO: Remove i2c Driver from main */
#include "lcd.h"
#include "pff.h"
#include "slider.h"
#include "stmpe610.h"
#include "drv2605.h"
#include "device.h"


FATFS fatfs;			/* File system object */
DIR dir;				/* Directory object */
FILINFO fno;			/* File information object */
FRESULT res;

void init(){
    int rc;
    I2C_Start();
    
    /* initiallize the LCD */
    rc = lcd_init();
    if(rc != HAPTIC_SUCCESS){
        LOG_ERROR("LCD Init FAIL rc = %i", rc);   
    }
    
    
    /* Initialize the Touchscreen Controller */
    rc = stmpe_init();
    if(rc != HAPTIC_SUCCESS){
        LOG_ERROR("STMPE Init FAIL rc = %i", rc);
        lcd_print(0, 0, "TOUCHSCREEN: ERR"); 
        
    }
    else{
        lcd_print(0, 0, "TOUCHSCREEN: OK"); 
    }
    
    /* Initiallize the Haptic Controller */
    drv2605_init();
    rc = drv2605_init();
    if(rc != HAPTIC_SUCCESS){
        LOG_ERROR("DRV2605 Init FAIL rc = %i", rc);
        lcd_print(1, 0, "DRV2605: ERR");
    }
    else{
        lcd_print(1, 0, "DRV2605 : OK"); 
    }
    
    /* Initiallize SD Card */
    LOG_INFO("Mount a volume.", 0);
	rc = pf_mount(&fatfs);
	if (rc != FR_OK){
        lcd_print(2, 0, "SD CARD: ERR" );
        LOG_ERROR("SD CARD MOUNT FAILED", 0);
    }
    else{
        lcd_print(2, 0 , "SD CARD: SUCCESS");
        lcd_print( 3, 0, "SD Card Files %i ", sdfs_numfiles(""));
        LOG_INFO("SD CARD MOUNT Success", 0);
    }
    CyDelay(1000);

}

int main()
{
    /* Declare Local Variables */
    int rc;
    pos16_t pos;
    pos16_t pos_max;
    pos16_t pos_min;
    
    /* Start Initilization routine */
    init();
    
    LED_Write(0);
    
    
    log_log(LOG_LEVEL_INFO, __func__, "Enter Main");
    
    /* Enable global interrupts */
    CyGlobalIntEnable;    
    CapSense_Start();	
    
    /* Initialize baselines */ 
    CapSense_InitializeAllBaselines();
    
    LOG_INFO("Baselines  Set ", 0);
    
    while(1){
        FILINFO fno = selectFile("");
        
        /* Open the file */
        rc = pf_open(fno.fname);
        if(rc != 0){
            lcd_clrScreen();
            lcd_print(0, 0, "FILE OPEN ERR");
            CyDelay(5000);
        }
        
        /*                  y x */
      uint8_t file_buff[12][20] = {{0}};
        uint br;
        
        res = pf_read((uint8_t *)file_buff, 240, &br);
        
        LOG_WARN("%i bytes read", br);
        LOG_WARN((char*)file_buff, 0);
        
        
        
        
        /* TODO: Load Image from memory */
        
        /* TODO NEXT: Convert to return POS16_t */
        
        /* Reset the touchscreen controller */
        /* TODO: more gracefully reset controller */
        stmpe_init();
        tc_callibrate(&pos_max, 
                    &pos_min);
        
        lcd_clrScreen();
        lcd_print(0, 0, "Callibrated!");
        lcd_print(1, 0, "Max:(%i, %i)", pos_max.x, pos_max.y);
        lcd_print(2, 0, "Min:(%i, %i)", pos_min.x, pos_min.y);
        
        uint8_t f_buff[2];
        while(1){

            /* Check Back Button */
            update_capsense();
            if(CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN)){
                LOG_WARN("OK", 0);
                break;   
            }

            /* Code to print out touchscreen Pos */
            rc = stmpe_getPos(&pos);
            
            pos16_t lastPos;
            if(rc == 0){
                pos = map_pos(pos, pos_min, pos_max);
                
                
                /* If the position changes */
                if(pos.x != lastPos.x || pos.y != lastPos.y){
                    lastPos = pos;
                    /* lookup the pos in the file */
                    LOG_WARN("FPOS %i", ((RESOLUTION_X_BYTE ) * pos.y)  +  (pos.x / 8));
                    rc = pf_lseek(((RESOLUTION_X_BYTE ) * pos.y)  +  (pos.x / 8));      
                    if(rc != 0){
                        /* handdle the error */   
                        LOG_ERROR("SD READ ERROR ", 0);
                    }
                    else{
                        rc = pf_read(f_buff, 1, &br);
                        if(rc != 0 || br == 0 ){
                            LOG_WARN("RC %i, read %i %i", rc, br, f_buff[0]);
                            
                        }
                        
                        
                        if(f_buff[0] != 0xFF){
                            LOG_WARN("FB: %i", f_buff[0]);
                            drv2605_set_rtp(126);
                            LED_Write(1);   
                        }
                        else{
                            LED_Write(0);
                            drv2605_set_rtp(0);
                            
                        }
                    }
                    drv2605_go();
                }
                
                /* Do image Processing here */
                LOG_WARN("Pos x =  %05i y = %05i z = %05i", pos.x, pos.y, pos.z);
            }
            else{
                drv2605_set_rtp(0);
                LED_Write(0);
                drv2605_go();
                
            }

               
        }
        
        //
    } /* END: Main While(1) */

     
}




/* [] END OF FILE */
