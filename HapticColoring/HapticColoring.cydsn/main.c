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
#include "i2c_driver.h"
// #include "mcp23008.h"
#include "lcd.h"
#include "pff.h"
#include "slider.h"


#include "stmpe610.h"
#include "drv2605.h"

#define STMPE610_I2C_ADDR (0x82 >> 1)
#define DRV2605L_I2C_ADDR (0xB4 >> 1)

FATFS fatfs;			/* File system object */
DIR dir;				/* Directory object */
FILINFO fno;			/* File information object */


/**  Initializes the i2c Interface 
 *  @return 1 - Success 0 - Failure
*/
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
        lcd_print("TOUCHSCREEN: ERR", 0, 0); 
        
    }
    else{
        lcd_print("TOUCHSCREEN: OK", 0, 0); 
    }
    
    /* Initiallize the Haptic Controller */
    drv2605_init();
    rc = drv2605_init();
    if(rc != HAPTIC_SUCCESS){
        LOG_ERROR("DRV2605 Init FAIL rc = %i", rc);
        lcd_print("DRV2605: ERR", 1, 0);
    }
    else{
        lcd_print("DRV2605 : OK", 1, 0); 
    }
    
    /* Initiallize SD Card */
    LOG_INFO("Mount a volume.", 0);
	rc = pf_mount(&fatfs);
	if (rc != FR_OK){
        lcd_print("SD CARD: ERR", 2, 0);
        LOG_ERROR("SD CARD MOUNT FAILED", 0);
    }
    else{
        lcd_print("SD CARD: SUCCESS", 2, 0);
        
        /* Show the number of files */
        char lcd[20] = {0};
        snprintf(lcd, 20, "SD Card Files: %i", sdfs_numfiles("") );
        lcd_print(lcd, 3, 0);
        LOG_INFO("SD CARD MOUNT Success", 0);
    }
    
    
    
    CyDelay(1000);

}

void die (		/* Stop with dying message */
	FRESULT rc	/* FatFs return value */
)
{
	LOG_ERROR("Failed with rc=%u.", rc);
	for (;;) ;
}

int main()
{
    /* Start Initilization routine */
    init();
    
    
    char lcd0[16] = {0};
    char lcd1[16] = {0};
    
    LED_Write(0);
    
    
    log_log(LOG_LEVEL_INFO, __func__, "Enter Main");
    
    /* Enable global interrupts */
    CyGlobalIntEnable;    
    CapSense_Start();	
    
    /* Initialize baselines */ 
    CapSense_InitializeAllBaselines();
    
    LOG_INFO("Baselines ", 0);
    
    int currentPos;
    
    lcd_clrScreen();
    while(1u)
    {
        /* Update all baselines */
        CapSense_UpdateEnabledBaselines();
        
   		/* Start scanning all enabled sensors */
    	CapSense_ScanEnabledWidgets();
    
        /* Wait for scanning to complete */
		while(CapSense_IsBusy() != 0)
		{
			/* Loop until condition true */
		}
        
        
        currentPos = slider_update(CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS));
        snprintf(lcd1, 16, "Master: %i                ", currentPos);
        lcd_print(lcd1, 0, 0);
        
        
    }
     
}




/* [] END OF FILE */
