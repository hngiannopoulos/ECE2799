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

/** Returns a fileobject of the number of the file in the directory.

*/
FILINFO sdfs_getFileNum(char * folder, uint8_t file){
    
    DIR dir;				/* Directory object */
	FILINFO fno;			/* File information object */
    FRESULT rc;
    
    fno.fname[0] = 0;
    
    uint16_t files = 0; 
    uint8_t i = 0;
    
    rc = pf_opendir(&dir, folder);
    
    for (i = 0; i < file; i++) {
		rc = pf_readdir(&dir, &fno);	/* Read a directory item */
		if (rc || !fno.fname[0]) break;	/* Error or end of dir */
        
        /* If the file is not a directory */
		if (fno.fattrib != AM_DIR)
            files++;
	}
    

    
    return fno;
}

int sdfs_fileNameList(char * folder, uint8_t startFile, uint8_t len, char ** list){
    
    FILINFO fno;
    uint8_t i = 0;
    for(i = 0; i < 3; i++){
        fno = sdfs_getFileNum(folder, (i + startFile));
        if(!fno.fname[0] ){
            fno.fname[0] = 0;
            break;
            
        }
        
        /* copy the filename 1 position into the string */
        else{
            LOG_WARN("%s", fno.fname);
        }
        // strncpy(list[i]+1, fno.fname, len);
    }
    return fno.fattrib;
}



/* [] END OF FILE */
