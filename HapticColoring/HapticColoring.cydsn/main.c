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

#include "stmpe610.h"
#include "drv2605.h"

#define STMPE610_I2C_ADDR (0x82 >> 1)
#define DRV2605L_I2C_ADDR (0xB4 >> 1)


/**  Initializes the i2c Interface 
 *  @return 1 - Success 0 - Failure
*/
void i2c_init(){
    uint32 rc;
    I2C_Start();
    
    /* Initialize the Touchscreen Controller */
    stmpe_init();
    
    /* Log the Chip Address */
    LOG_INFO( "STMP Chip Addr %04X", stmpe_version());
    
    /* Initiallize the Haptic Controller */
    // drv2605_init();
    
    // LOG_INFO("drv2605 Setup", 0);
    char hello[] = "HELLO12345678909ABCDEFG";
    char world[] = "WORLD";
    LOG_INFO("lcd_init rc: %i", lcd_init());
    LOG_INFO("MCP23008 rc: %i", lcd_print(hello, 0, 0));
    LOG_INFO("MCP23008 rc: %i", lcd_print(world, 1, 0));

    
    
    
    
    /* Working Implementatyion */
   // LOG_TRACE("i2c REG READ %02X, %02X", i2c_read_reg(STMPE610_I2C_ADDR, 0x00), i2c_read_reg(STMPE610_I2C_ADDR, 0x01));
    
    /* Write To Touchscreen */
//    i2c_write_reg(STMPE610_I2C_ADDR, 0x10, 0x02);
//    LOG_TRACE("i2c STMP READ %02X", i2c_read_reg(STMPE610_I2C_ADDR, 0xF0));
    

    
    
    
    /* And Read back the value */
    /* end of working Implementation */

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
    
    FATFS fatfs;			/* File system object */
	DIR dir;				/* Directory object */
	FILINFO fno;			/* File information object */
	UINT bw, br, i;
	BYTE buff[64];
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LED_Write(0);
   // i2c_init();
    log_log(LOG_LEVEL_INFO, __func__, "Enter Main");
    
    int rc;

    LOG_WARN("Mounting Volume", 0);
	rc = pf_mount(&fatfs);
	if (rc) die(rc);
    
    LOG_WARN("Open root directory.", 0);
    rc = pf_opendir(&dir, "");
    if (rc) die(rc);
	LOG_WARN("Directory listing...", 0);
	for (;;) {

		rc = pf_readdir(&dir, &fno);	/* Read a directory item */
		if (rc || !fno.fname[0]) break;	/* Error or end of dir */
		if (fno.fattrib & AM_DIR){
			LOG_WARN("   <dir>  %s\n", fno.fname);
        }
		else{
			LOG_WARN("%8lu  %s\n", fno.fsize, fno.fname);
        }
	}
	if (rc) die(rc);
    
 
    for(;;)
    {
      
     
    }
}



/* [] END OF FILE */
