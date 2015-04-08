/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 * @author hngiannopoulos
 * ========================================
*/

#include "project.h"
#include "i2c_driver.h"
#include "log.h"

#ifndef MCP23008_H_
#define MCP23008_H_
    
/* i2c Address */
#define MCP23008_ADDRESS 0x20
    
/* MCP Register MAP */
#define MCP23008_IODIR      0x00 /* IO Direction REG (1 - IN 0 - OUT )Per pin */
#define MCP23008_IPOL       0x01 /* Input Polarity Reg (1 - Inverted ) Per Pin */
#define MCP23008_GPINTEN    0x02 /* Inetrrupt On change Mask (Per Pin */
#define MCP23008_DEFVAL     0x03 /* Default Register Value */
#define MCP23008_INTCON     0x04
#define MCP23008_IOCON      0x05
#define MCP23008_GPPU       0x06 /* Pull Up Register Pin */
#define MCP23008_INTF       0x07 /* Interrupt Flag Reg */
#define MCP23008_INTCAP     0x08 /* Intettupt Capture Register */
#define MCP23008_GPIO       0x09 /* GPIO Port IN Register Writing Changes OLAT REG */
#define MCP23008_OLAT       0x0A /* OUTPUT REGISTER */

/* MCP PIN Names */
#define MCP_PIN_RS  (1<<1) /* OUT */
#define MCP_PIN_E   (1<<2) /* OUT */
#define MCP_PIN_D4  (1<<3) /* OUT */
#define MCP_PIN_D5  (1<<4) /* OUT */
#define MCP_PIN_D6  (1<<5) /* OUT */
#define MCP_PIN_D7  (1<<6) /* OUT / IN (Busy Flag ) */
#define MCP_PIN_BL  (1<<7) /* Backlight */
    
#define MCP_PIN_MODE_VAL 0

/* defines for writing char or cmd */
#define MCP_LCD_WR_CMD 0
#define MCP_LCD_WR_CHR MCP_PIN_RS
    
/* Special Startup Instructions */
#define MCP_LCD_FUNCTION_SET_A_NIB  0x3 
#define MCP_LCD_FUNCTION_SET_B_NIB  0x2
#define MCP_LCD_FUNCTION_SET_C_INST 0x28 /* Sets 4 bit interface; 2 lines; 5x7 font */
#define MCP_LCD_FUNCTION_SET_D_INST 0x08 /* Follows Flowchart */
#define MCP_LCD_FUNCTION_CLEAR_SCREEN 0x01 /* Clear Screen, then delay 3ms */
#define MCP_LCD_ENTRY_MODE_SET 0x06 /* Cusor Inc; Disp not shift; */
#define MCP_LCD_CMD_LCD_ON 0x0C /* Turn Cursor; No  Blink */


    
/** Sets Pin Modes.
 * @param in bit mask to set.
 * @return HAPTIC_SUCCESS or HAPTIC_ERROR 
 */
uint32_t mcp_setPinMode(uint8_t in);

/** Sets Pin Outputs.
 * @param in bit mask to set.
 * @return HAPTIC_SUCCESS or HAPTIC_ERROR 
 */
uint32_t mcp_write(uint8_t in);

/** Sets Pin Outputs.
 * @param out ptr to write results to.
 * @return HAPTIC_SUCCESS or HAPTIC_ERROR 
 */
uint32_t mcp_read(uint8_t * out);
   
/** Writes a value to the specified MCP23008 reg.
 * @param reg The register to write into.
 * @param dat The value to write into the register.
 * @return HAPTIC_SUCCESS or HAPTIC_ERROR
 */
uint32_t mcp_writeReg(uint8_t reg, uint8_t dat);


/* Low Level LCD Functions */

/** Writes a command to the LCD.
 * @param cmd The command to be written.
 * @return HAPTIC_SUCCESS or HAPTIC_ERROR
 */
uint32_t mcp_lcdWriteCmd(uint8_t cmd);

/** Writes a character to the LCD.
 * @param chr The character to be written.
 * @return HAPTIC_SUCCESS or HAPTIC_ERROR
 */
uint32_t mcp_lcdWriteChar(char chr);
    
/** Writes a single nibble (4-Bits) to the disp.
 * @param nib The 4 bits to send.
 * @param rs Either MCP_LCD_WR_CMD or MCP_LCD_WR_CHR
 * @return HAPTIC_SUCCESS or HAPTIC_ERROR
 */
uint32_t mcp_lcdWriteNib(uint8_t nib, uint8_t rs);

    
    
#endif

/* [] END OF FILE */
