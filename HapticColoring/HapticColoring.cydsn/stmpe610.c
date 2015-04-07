/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 * @author hngiannopoulos
 * Driver library for the STMPE610 Touchscren Controller
 * ========================================
*/

#include "stmpe610.h"
#define STMPE610_I2C_ADDR (0x82 >> 1)
int stmpe_init(){
    int rc = 0;
    
    /* Trigger a soft Reset */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_SYS_CTRL1, STMPE_SYS_CTRL1_RESET);
    
    /* Wait for STMPE610 To come up */
    CyDelay(10);

    /* ======== Setup Registers ======= */
    /* turn on clocks! */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_SYS_CTRL2, 0x0); 
    
    /*  Enable Touchscreen Controller  (XYZ and enable!) */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_TSC_CTRL, STMPE_TSC_CTRL_XYZ | STMPE_TSC_CTRL_EN); 
    
    /* Send Interrupt only when touch is detected */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_INT_EN, STMPE_INT_EN_TOUCHDET); 
    
    /* Use Internal Refrence voltage and use 96 clocks per conversion */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_ADC_CTRL1, STMPE_ADC_CTRL1_10BIT | (0x6 << 4));
    
    /* Set the Speed of the ADC to 6.5MhZ */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_ADC_CTRL2, STMPE_ADC_CTRL2_6_5MHZ); 
    
    /* Does What it seems like */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_TSC_CFG, STMPE_TSC_CFG_4SAMPLE | STMPE_TSC_CFG_DELAY_1MS | STMPE_TSC_CFG_SETTLE_5MS); 
    
    /* WTF??, Sets the TRange and Accuracy of pressure to Frational part 6, whole part is 2 */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_TSC_FRACTION_Z, 0x6); 
    
    /* Set Fifo length to 10 */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_FIFO_SIZE, 10);
    
    /* Set Fifo to iterrupt when it has 1 sample */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_FIFO_TH, 1); 
    
    /* Resets the FIFO */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_FIFO_STA, STMPE_FIFO_STA_RESET);
    
    /* Unreset FIFo */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_FIFO_STA, 0);    
    
    /* sets max current limiting for touchscreen to 50-80 mA Max */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_TSC_I_DRIVE, STMPE_TSC_I_DRIVE_50MA); 
    
    /* Resets all interrupts */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_INT_STA, 0xFF);
    
    /* Interrupt ActiveHigh/Rising Edge */ 
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_INT_CTRL, STMPE_INT_CTRL_POL_HIGH | STMPE_INT_CTRL_ENABLE);
    /* end of register setup */
    
    return rc;
    
}

int stmpe_getPos(pos16_t * pos){
    int rc = 0;       
    uint8_t data[4];
    int i;
    
    /* if there's no data to read */
    if(stmpe_fifo_len() == 0){
        return STMPE_NO_DATA;   
    }
    
    /* Read in data from STMPE_REG_TSC_DATA */
    for (i = 0; i < 4; i++) {
        data[i] = i2c_read_reg(STMPE610_I2C_ADDR, STMPE_REG_TSC_DATA);
    }
    
    /* Copy the results into pos16_t struct pos */
    pos->x = data[0];
    pos->x <<= 4;
    pos->x |= (data[1] >> 4);
    pos->y = data[1] & 0x0F; 
    pos->y <<= 8;
    pos->y |= data[2]; 
    pos->z = data[3];
        
//    if(i2c_read_reg(STMPE610_I2C_ADDR, 0x40) & 0x80)
        
        
    /* Clear The Data */
//    if (i2c_read_reg(STMPE610_I2C_ADDR,  STMPE_FIFO_STA) & STMPE_FIFO_STA_EMPTY)
//        i2c_write_reg(STMPE610_I2C_ADDR, STMPE_INT_STA, 0xFF);
    
    
    
    return STMPE_SUCCESS;
}

uint16_t stmpe_version(){
    uint8_t id[2] = {0};
    i2c_read_buff(STMPE_ADDR, STMPE_REG_CHIP_ID, id, 2);
    
    return (id[0] << 8) | (id[1]);
    
}

int stmpe_clearFifo(){
    
    /* Writes to FIFO_CTTL_STA to reset the fifo */
    i2c_write_reg(STMPE610_I2C_ADDR, STMPE_INT_STA, 0x01);
    return 0;
}

int stmpe_fifo_len(){
    
    /* Reads STMPE_FIFO_SIZE (0x4c)  */
    return i2c_read_reg(STMPE610_I2C_ADDR, STMPE_FIFO_SIZE);
    
}


/* [] END OF FILE */
