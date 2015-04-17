/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * @author hngiannopoulos
 * ========================================
*/

#include "project.h"
#include "log.h"
#include "pff.h"

uint16_t sdfs_numfiles(char* folder){
    DIR dir;				/* Directory object */
	FILINFO fno;			/* File information object */
    FRESULT rc;
    
    uint16_t files = 0; 
    
    rc = pf_opendir(&dir, folder);
    
    for (;;) {
		rc = pf_readdir(&dir, &fno);	/* Read a directory item */
		if (rc || !fno.fname[0]) break;	/* Error or end of dir */
        
        /* If the file is not a directory */
		if (fno.fattrib != AM_DIR)
            files++;
	}
    
    
    

    return files;
}



/* [] END OF FILE */
