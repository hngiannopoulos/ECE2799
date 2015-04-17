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

#include "slider.h"

/* Static Global Variable for Master Pos */
static int masterPos = 100;

int slider_update(uint16_t currentPos){
    static uint16_t lastpos = 0;
    static uint16_t startTouch = 0;
    
    /* If the value changes */
    if(lastpos != currentPos){

        /* ON Touch DETECTED */
        if(lastpos == 65535 && currentPos != 65535){
            /* Save Current Pos */
            startTouch = currentPos;
        }
        
        /* ON TOUCH RELEASED */
        else if(lastpos != 65535 && currentPos == 65535){
            /* Update MasterPos */
            masterPos += (int)(lastpos - startTouch);
        }
        
        /* Update LastPos */
        lastpos = currentPos;
        if(currentPos != 65535)
            return  masterPos + (int)(currentPos - startTouch);
        else
            return  masterPos;
        
    }
        
    /* Otherwise just return masterPos */
    else{
        return masterPos;
    }
       
}

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


/* [] END OF FILE */
