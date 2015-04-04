/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 * @author hngiannopoulos
 * Loging File
 * ========================================
*/

#include <project.h>
#include <stdarg.h>
#include <stdio.h>
#include "log.h"

/* Define Macro / Function Wrapper for putstring */
#define LOG_PUTSTRING(ptr) SW_UART_PutString(ptr)
#define LOG_CRLF() SW_UART_PutCRLF()

#ifdef LOG_EN
/** Creates a log message and prints it to LOG_PUTSTRING()
 *
 * @param level LOG_LEVEL See: LOG_ERROR, LOG_WARN etc.
 * @param char ptr to char array of message format
 * @param additional parameters
 * @return 0 if error otherwise # of chars sent
*/
inline uint32_t log_log(uint8_t level, const char* function, char * format, ...){
    
    /* Init MSG buffer */ 
    char msg[LOG_MAX_LOG_LEN] = {0};
    
    int pos = 0;
    
    /* Copy Log info into Beginning of bufer */
    pos = snprintf(msg, (LOG_MAX_LOG_LEN ), "<%i> [%s]:" , level, function);
    
    va_list args;
    va_start(args, format);
    
    /* Copy the rest of the message into msg */
    pos = vsnprintf(msg + pos, (LOG_MAX_LOG_LEN - pos ), format, args);
    
    LOG_PUTSTRING(msg);
    SW_UART_PutCRLF();
    
    return pos;    
    
}

#endif





/* [] END OF FILE */