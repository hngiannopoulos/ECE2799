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
#include "device.h"

/* Static Global Variable for Master Pos */
static int masterPos = 100;

int slider_update(uint16_t currentPos, uint16_t max){
    static uint16_t lastpos = 0;
    static uint16_t startTouch = 0;
    
    max++;
    
    /* If the value changes */
    if(lastpos != currentPos){

        /* ON Touch DETECTED */
        if(lastpos == 65535 && currentPos != 65535){
            /* Save Current Pos */
            startTouch = currentPos;
            LOG_INFO("TOUCH",0);
        }
        
        /* ON TOUCH RELEASED */
        else if(lastpos != 65535 && currentPos == 65535){
            /* Update MasterPos */
            masterPos = constrain(masterPos + (int)(lastpos - startTouch), 0, max);
            LOG_INFO("RELEASE", 0);
        }
        
        /* Update LastPos */
        lastpos = currentPos;
        if(currentPos != 65535 )
            return  constrain(masterPos + (int)(currentPos - startTouch), 0, max);
        else
            return  constrain(masterPos, 0, max);
        
    }
        
    /* Otherwise just return masterPos */
    else{
        if(currentPos != 65535){
            return constrain((masterPos + (int)(currentPos - startTouch)), 0, max);
        }
        else{
            return constrain(masterPos, 0, max);
        }
    }
       
}

int slider_set(int pos){
    masterPos = pos;
    return pos;
}

int slider_get(){
    return masterPos;
}


/* [] END OF FILE */
