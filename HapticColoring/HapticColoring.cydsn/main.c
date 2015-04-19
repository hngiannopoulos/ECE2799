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


void update_capsense(){
    /* Update all baselines */
    CapSense_UpdateEnabledBaselines();

    /* Start scanning all enabled sensors */
    CapSense_ScanEnabledWidgets();

    /* Wait for scanning to complete */
    while(CapSense_IsBusy() != 0)
    {
    	/* Loop until condition true */
    }
}


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
    
//    /* Dump the number of files on the sd card */
//    uint16_t filenum = sdfs_numfiles("");
//    FILINFO file;
//    uint16_t i = 0;
//    for(i = 0; i <= filenum; i++){
//        file = sdfs_getFileNum("", i);
//        LOG_WARN("FILE %s", file.fname);
//        
//    }
    
    
    CyDelay(1000);

}


FILINFO selectFile(char * dir){
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t old_j = 99;
    FILINFO fno; 
    uint8_t sdNumfiles = sdfs_numfiles(dir);
    
    uint8_t old_scrollPos = 0; 
    uint16_t scrollPos;
    
    char files[3][LCD_WIDTH];

    while(1){
        /* ===== Deal Checking Capsense ====== */
        
        update_capsense();

        scrollPos = slider_update(CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS), (SCROLL_PER_FILE * sdNumfiles));
        
        /* Check to see if the scroll position changed */
        if(scrollPos != old_scrollPos){
            old_scrollPos = scrollPos;
            
            j = scrollPos / SCROLL_PER_FILE;
            
            /* Draw updated fileselect screen */
            if(j != old_j){
            
                memset(files, 0 , sizeof(files));
                LOG_INFO(" J = %i",  j);
                lcd_clrScreen();
                lcd_print(0,0, "Select Img:");
                
                /* Set J to approprate # */
                for(i = 0; ((i + j )<= sdNumfiles) && (i < 3) ; i++){
                    fno = sdfs_getFileNum(dir, i + j);
                    strncpy(files[i], fno.fname, LCD_WIDTH);
                    
                    lcd_print(i+1 , 1, files[i]);
                    LOG_INFO(fno.fname, 0);
                    
                }
                
                /* Draw the Selector thing */
                lcd_print( 2, 0, ">");
                old_j = j;
                
            }   /* END: Draw Updated Fileselect screen */
            
        }   /* END: Update for Scroll Pos */
        
        
        /* Check Select Button Status */
        
        if(CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN)){
            /* set fno to the right file */
            return sdfs_getFileNum(dir, j + 1);
        }

    }
    LOG_WARN("NEXT", 0);
    
    return fno;   
}

int main()
{
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
        
        /* TODO: Load Image from memory */
        
        lcd_clrScreen();
        lcd_print(0,0, fno.fname);        
        
        /* TODO: Setup Callibration for specific Image */
        
        while(1){
            
            /* Check Back Button */
            update_capsense();
            if(CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN)){
                break;   
            }
            
            /* TODO: IMG Processing HERE */
               
        }
        
        
    } /* END: Main While(1) */

     
}




/* [] END OF FILE */
