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
#include "log.h"
/* TODO: Remove i2c Driver from main */
#include "i2c_driver.h"
// #include "mcp23008.h"
#include "lcd.h"

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
    // stmpe_init();
    
    /* Log the Chip Address */
    // LOG_INFO( "STMP Chip Addr %04X", stmpe_version());
    
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

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LED_Write(0);
    i2c_init();
    log_log(LOG_LEVEL_INFO, __func__, "Enter Main");
    
    pos16_t pos;
    int rc;

    LED_Write(1);
    
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Code to print out touchscreen Pos */
        /*
        rc = stmpe_getPos(&pos);
        if(rc == 0)
            LOG_INFO("Pos x =  %05i y = %05i z = %05i", pos.x, pos.y, pos.z);
        */ 
        /* end of code */
        
        /* Code to Test Haptic Feedback */
        /*
        uint8_t i;
        for(i = 0; i < 0x7F; i++){
            drv2605_set_rtp(i);
            CyDelay(50);
            drv2605_go();
            LOG_INFO("Vibe Strength: %i", i);
            
        }
        */
     
    }
}



/* [] END OF FILE */
