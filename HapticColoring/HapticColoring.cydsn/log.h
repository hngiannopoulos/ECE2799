/* ========================================
 * @file log.h
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * @author hngiannopoulos
 * Sets up an extendable Logging System using the 
 * provided SW_UART
 * ========================================
*/

#include <project.h>

#define LOG_EN
#define LOG_MAX_LOG_LEN 64

/* Define Logging Levels */
#define LOG_LEVEL_ERROR   4
#define LOG_LEVEL_WARN    3
#define LOG_LEVEL_INFO    2
#define LOG_LEVEL_TRACE   1
    
/* Error Codes */
#define HAPTIC_SUCCESS      0
#define HAPTIC_WRITE_ERROR  1
#define HAPTIC_READ_ERROR   2

/* Define Log Level */
#define LOG_LEVEL LOG_LEVEL_INFO

#if LOG_LEVEL <= LOG_LEVEL_TRACE
#define LOG_TRACE(format, ...) log_log(LOG_LEVEL_TRACE, __func__,  format, __VA_ARGS__);
#else 
#define LOG_TRACE(format, ...)
#endif 

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LOG_INFO(format, ...) log_log(LOG_LEVEL_INFO, __func__,  format, __VA_ARGS__);
#else 
#define LOG_INFO(format, ...)
#endif 

#if LOG_LEVEL <= LOG_LEVEL_WARN
#define LOG_WARN(format, ...) log_log(LOG_LEVEL_WARN, __func__,  format, __VA_ARGS__);
#else 
#define LOG_WARN(format, ...)
#endif 

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LOG_ERROR(format, ...) log_log(LOG_LEVEL_ERROR, __func__,  format, __VA_ARGS__);
#else 
#define LOG_ERROR(format, ...)
#endif 



#ifndef LOG_H_
#define LOG_H_
    
inline uint32_t log_log(uint8_t level, const char* function, char * format, ...);
    
    
#endif

/* [] END OF FILE */
