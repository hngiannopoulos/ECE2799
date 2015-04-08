/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 * @author hngiannopoulos
 * Driver to deal with the i2c LCD.
 * ========================================
*/

#include "lcd.h"

/* -- High Level LCD Functions -- */

/* Instructions found at: 
 * http://web.alfredstate.edu/weimandn/lcd/lcd_initialization/lcd_initialization_index.html
 */

uint32_t lcd_init(){
    uint32_t rc = 0;
    
    /* -- Confirgure mcp23008 First -- */
    
    /* Set Pin Directions */
    mcp_setPinMode(MCP_PIN_MODE_VAL);
    
    /* Set Input Polarity Register */
    mcp_writeReg(MCP23008_IPOL, 0x00);
    
    /* Clear all input pins */
    mcp_write(0);
    
    /* Wait at least 100ms for poweup */
    CyDelay(100);
    
    /* --- Write First NIBs To LCD ---- */
    rc |= mcp_lcdWriteNib(MCP_LCD_FUNCTION_SET_A_NIB, MCP_LCD_WR_CMD);
    CyDelay(5);
    
    /* Write second NIB; Delay 100us */
    mcp_lcdWriteNib(MCP_LCD_FUNCTION_SET_A_NIB, MCP_LCD_WR_CMD);
    CyDelayUs(100);
    
    /* Write third NIB; Delay 100us */
    mcp_lcdWriteNib(MCP_LCD_FUNCTION_SET_A_NIB, MCP_LCD_WR_CMD);
    CyDelayUs(100);
    
    /* Write fourth NIB; Delay 55us */
    mcp_lcdWriteNib(MCP_LCD_FUNCTION_SET_B_NIB, MCP_LCD_WR_CMD);
    CyDelayUs(55);
    
    /* -- Writing Nibs Is done, commands  can be written now -- */
    mcp_lcdWriteCmd(MCP_LCD_FUNCTION_SET_C_INST);

    mcp_lcdWriteCmd(MCP_LCD_FUNCTION_SET_D_INST);
    
    /* Clear the display TODO: Change to clear funct */
    mcp_lcdWriteCmd(MCP_LCD_FUNCTION_CLEAR_SCREEN);
    
    mcp_lcdWriteCmd(MCP_LCD_ENTRY_MODE_SET);    /* Configure Cursor and LCD */
    
    /* -- Config is technically done now --- */
    
    /* Turn On lcd */
    mcp_lcdWriteCmd(MCP_LCD_CMD_LCD_ON);
    
    
    return rc;
}

uint32_t lcd_clrScreen(){
    return mcp_lcdWriteCmd(LCD_CMD_CLEAR_SCREEN);
}


uint32_t lcd_writeCmd(uint8_t cmd){
    return mcp_lcdWriteCmd(cmd);   
}

uint32_t lcd_print(const char * msg, uint8_t pos_x, uint8_t pos_y){
    uint8_t i = 0;
    uint32_t rc = 0;
    
    if( lcd_moveCursor(pos_x, pos_y) != HAPTIC_SUCCESS ){
        return HAPTIC_READ_ERROR;
    }
    
    for(i = 0; i < (LCD_WIDTH - pos_y); i++){
        if(msg[i] == 0){
            break;
         }
        rc |= mcp_lcdWriteChar(msg[i]);
    }
    
    return rc;
}


uint32_t lcd_moveCursor(uint8_t row, uint8_t pos){
    if(row > 3 || pos > LCD_WIDTH){
        return HAPTIC_WRITE_ERROR;
    }
    const uint8_t posData[4] = {LCD_ADDR_ROW_1, LCD_ADDR_ROW_2, LCD_ADDR_ROW_3, LCD_ADDR_ROW_4};
    pos = posData[row] + pos;
    
    /* Mask Out upper bits */
    pos &= 0x7F;
    
    return mcp_lcdWriteCmd(LCD_CMD_SET_DDRAM_ADDR | pos);
}

/* [] END OF FILE */
