/* ========================================
 * @file i2c.c
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 * @author hngiannopoulos
 * Lib to better handle i2c reads and writes.
 * ========================================
*/

#include <project.h>
#include "i2c_driver.h"
#include "log.h"

uint32_t i2c_read_buff(uint32_t dev_addr, uint8_t reg, uint8_t * dat, uint8_t n){
    uint32 rc = 0;
    int i = 0;
    
    I2C_I2CMasterSendStart(dev_addr, I2C_I2C_WRITE_XFER_MODE);
    /* TODO; Add error checking so i2c doesnt fly into the weeds */
    I2C_I2CMasterWriteByte( reg);
    I2C_I2CMasterSendRestart(dev_addr, I2C_I2C_READ_XFER_MODE);
    
    /* Copy In the Approprate ammount of data */
    for(i = 0; i < (n - 1); i++){
        dat[i] = (uint8_t) I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA);
    }
    /* For the last read make sure to send a NACK */
    dat[i] = (uint8_t) I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA);
    rc = I2C_I2CMasterSendStop();
    
    return rc;
}


uint32_t i2c_write_buff(uint32_t dev_addr, uint8_t reg, uint8_t * dat, uint8_t n){
    uint32 rc = 0;
    int i = 0;
    
    /* Start the i2c Connection */
    I2C_I2CMasterSendStart(dev_addr, I2C_I2C_WRITE_XFER_MODE);
    /* TODO; Add error checking so i2c doesnt fly into the weeds */
    I2C_I2CMasterWriteByte( reg );
    
    /* Copy In the Approprate ammount of data */
    for(i = 0; i < n; i++){
        I2C_I2CMasterWriteByte( dat[i] );
        log_log(LOG_LEVEL_INFO, __func__, "Transfering %i %x", i, dat[i]);
    }
    
    /* Send the stop bit */
    rc = I2C_I2CMasterSendStop();
    return rc;
}

uint32_t i2c_read_reg(uint32_t dev_addr, uint8_t reg){
    uint32_t data = 0;
    
    I2C_I2CMasterSendStart(dev_addr, I2C_I2C_WRITE_XFER_MODE);
    /* TODO; Add error checking so i2c doesnt fly into the weeds */
    I2C_I2CMasterWriteByte( reg);
    I2C_I2CMasterSendRestart(dev_addr, I2C_I2C_READ_XFER_MODE);

    /* For the last read make sure to send a NACK */
    data =  I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA);
    LOG_TRACE( "Read %x" , data);
    I2C_I2CMasterSendStop();
    
    return data;
}


uint32_t i2c_write_reg(uint32_t dev_addr, uint8_t reg, uint8_t dat){
    int rc = 0;
    /* Start the i2c Connection */
    rc = I2C_I2CMasterSendStart(dev_addr, I2C_I2C_WRITE_XFER_MODE);
    /* TODO; Add error checking so i2c doesnt fly into the weeds */
    I2C_I2CMasterWriteByte( reg );
    
 
    I2C_I2CMasterWriteByte( dat );
    LOG_TRACE( "Transfering %02x" , dat);

    /* Send the stop bit */
    I2C_I2CMasterSendStop();
    return rc;
}


/* [] END OF FILE */
