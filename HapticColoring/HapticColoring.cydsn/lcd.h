/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 * @author hngiannopoulos
 * 
 * ========================================
*/

#include "project.h"
#include "mcp23008.h"

#define LCD_MEM

/* Change these for diffrent size LCDs */
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

/* @note not all rows are valid */
#define LCD_ADDR_ROW_1 0x00
#define LCD_ADDR_ROW_2 0x40
#define LCD_ADDR_ROW_3 0x14
#define LCD_ADDR_ROW_4 0x54

#define LCD_CMD_CLEAR_SCREEN    0x01 /* Clear Screen, */
#define LCD_CMD_SET_DDRAM_ADDR  0x80 /* Add Cursor Pos to this to move */

#ifndef LCD_H_
#define LCD_H_

/** Initiallized the lcd interface.
 * @return HAPTIC_SUCCESS or HAPTIC_ERROR
 */
uint32_t lcd_init();

/** Clears the whole LCD Screen.
 * @return HAPTIC_SUCCESS or HAPTIC_ERROR.
 * @note This function will block for about 3ms.
 */
uint32_t lcd_clrScreen();

/** Sends a command to the LCD.
 * @param cmd 8-Bit command to send.
 * @return HAPTIC_SUCCESS or HAPTIC_ERROR.
 */
uint32_t lcd_writeCmd(uint8_t cmd);

/** Puts a string on the display.
 * @param msg Pointer to message string.
 * @param pos_x X - position of the string.
 * @param pos_y Y - position of the string.
 * @return HAPTIC_SUCCESS or HAPTIC_ERROR.
 * @note this will only copy the same number of bits as LCD_WIDTH.
 */
uint32_t lcd_print(const char * msg, uint8_t pos_x, uint8_t pos_y);

/** Moves the cursor.
 * @param row row.
 * @param pos position in row.
 * @return HAPTIC_SUCCESS or HAPTIC_ERROR.
 */
uint32_t lcd_moveCursor(uint8_t row, uint8_t pos);

#endif
/* [] END OF FILE */
