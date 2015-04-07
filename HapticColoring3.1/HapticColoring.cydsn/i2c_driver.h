/* ========================================
 *  @file i2c.h
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 * @author hngiannopoulos
 * An i2c Driver that uses existing PSoC i2c stuff 
 * ========================================
*/

#include <project.h>

#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

    
/** Reads a number of bytes from a register on a specific device.
 * @param dev_addr Right Alligned i2c Address.
 * @param reg Register to read from.
 * @param dat pointer to an array to read data into.
 * @param n number of bytes to read.
 * @return most recent i2c Status
*/
uint32_t i2c_read_buff(uint32_t dev_addr, uint8_t reg, uint8_t * dat, uint8_t n);

/** Writes a number of bytes to a register on a specific device.
 * @param dev_addr Right Alligned i2c Address.
 * @param reg Register to write to.
 * @param dat pointer to an array from which to write data.
 * @param n number of bytes to write.
 * @return most recent i2c Status
*/
uint32_t i2c_write_buff(uint32_t dev_addr, uint8_t reg, uint8_t * dat, uint8_t n);

    
/** Reads a  bytes from a register on a specific device.
 * @param dev_addr Right Alligned i2c Address.
 * @param reg Register to read from.

 * @return most recent i2c Status
*/
uint32_t i2c_read_reg(uint32_t dev_addr, uint8_t reg);

/** Writes a  bytes to a register on a specific device.
 * @param dev_addr Right Alligned i2c Address.
 * @param reg Register to write to.
 * @param dat pointer to an array from which to write data.
 * @return the read value
*/
uint32_t i2c_write_reg(uint32_t dev_addr, uint8_t reg, uint8_t  dat);
    
    
#endif 
/* [] END OF FILE */
