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

#include "mcp23008.h"

/* Static variable for the backlight */
static uint8_t bl = MCP_PIN_BL;

uint32_t mcp_setPinMode(uint8_t in){
    /* Write IODIR Reg */
    return i2c_write_reg(MCP23008_ADDRESS, MCP23008_IODIR, in);;
}

uint32_t mcp_write(uint8_t in){
    return i2c_write_reg(MCP23008_ADDRESS, MCP23008_OLAT, (in | bl));
}

uint32_t mcp_read(uint8_t * out){
    return i2c_read_buff(MCP23008_ADDRESS, MCP23008_GPIO, out, 1);
    
}

uint32_t mcp_writeReg(uint8_t reg, uint8_t dat){
    return i2c_write_reg(MCP23008_ADDRESS, reg, dat);
}

/* Low Level LCD Functions */

uint32_t mcp_lcdWriteNib(uint8_t nib, uint8_t rs){
    uint32_t rc = 0;
    
    /* Mask and shift nib to match d4 */
    nib = nib & 0x0F;    
    nib = nib << 3;
    
    /* Write  nibble (e - 0) */
    rc |= mcp_write(nib | bl | rs);
    CyDelayUs(3);
    
    /* Write  nibble (e - 1) */
    rc |= mcp_write(nib | bl | MCP_PIN_E | rs);
    CyDelayUs(3);
      
    /* Write nibble (e - 0) */
    rc |= mcp_write(nib | bl | rs);
    CyDelay(1);
    
    return rc;
    
}

uint32_t mcp_lcdWriteCmd(uint8_t cmd){
    uint32_t rc = 0;
   
    /* Send High Nibble first */
    uint8_t nibble_high = ( (cmd >> 4) & 0x0F );
    uint8_t nibble_low  = (cmd & 0x0F);
    
    /* Write high nibble */
    rc |= mcp_lcdWriteNib(nibble_high, MCP_LCD_WR_CMD);
        
    /* Write low nibble  */
    rc |= mcp_lcdWriteNib(nibble_low, MCP_LCD_WR_CMD);   
    
    /* Delay 53 uS */
    CyDelayUs(53);
    
    return rc;
    
}

uint32_t mcp_lcdWriteChar(char chr){
    uint32_t rc = 0;
   
    /* Send High Nibble first */
    uint8_t nibble_high = ( (chr >> 4) & 0x0F );
    uint8_t nibble_low  = (chr & 0x0F);
    
    /* Write high nibble */
    rc |= mcp_lcdWriteNib(nibble_high, MCP_LCD_WR_CHR);
        
    /* Write low nibble  */
    rc |= mcp_lcdWriteNib(nibble_low, MCP_LCD_WR_CHR);   
    
    return rc;
    
}




/* [] END OF FILE */
