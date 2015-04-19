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

#ifndef SLIDER_H_
#define SLIDER_H_
    
#include "project.h"
#include "log.h"


   
/** Updates slider value based on pos.
 * @param pos 16-Bit number for slider position.
 * @return master slider pos.
 */  
int slider_update(uint16_t pos, uint16_t max);

/** Sets the Master Slider Value.
 * @param pos Position to set the master value to.
 * @return The master slider position.
 */
int slider_set(int pos);

/** Gets the Current Slider Position.
 * @return The Current master slider position.
 * 
 */
int slider_get();



#endif

/* [] END OF FILE */
