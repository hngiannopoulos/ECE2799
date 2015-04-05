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

#include "stmpe610.h"

#define STMPE610_I2C_ADDR (0x82 >> 1)
#define DRV2605L_I2C_ADDR (0xB4 >> 1)


/**  Initializes the i2c Interface 
 *  @return 1 - Success 0 - Failure
*/
int i2c_init(){
    uint32 rc;
    I2C_Start();
    
    /* Initialize the Touchscreen Controller */
    stmpe_init();
    
    /* Log the Chip Address */
    LOG_INFO( "STMP Chip Addr %04X", stmpe_version());
    
    
    
    /* Working Implementatyion */
   // LOG_TRACE("i2c REG READ %02X, %02X", i2c_read_reg(STMPE610_I2C_ADDR, 0x00), i2c_read_reg(STMPE610_I2C_ADDR, 0x01));
    
    /* Write To Touchscreen */
//    i2c_write_reg(STMPE610_I2C_ADDR, 0x10, 0x02);
//    LOG_TRACE("i2c STMP READ %02X", i2c_read_reg(STMPE610_I2C_ADDR, 0xF0));
    

    
    
    
    /* And Read back the value */
    /* end of working Implementation */
    
    
    
    return rc;
}

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    i2c_init();
    log_log(LOG_LEVEL_INFO, __func__, "Enter Main");
    
    pos16_t pos;
    int rc;

    
    
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        
        rc = stmpe_getPos(&pos);
        if(rc == 0)
            LOG_INFO("Pos x =  %05i y = %05i z = %05i", pos.x, pos.y, pos.z);
        
     
    }
}



/* [] END OF FILE */
