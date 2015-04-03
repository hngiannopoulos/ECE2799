//*****************************************************************************
//*****************************************************************************
//  FILENAME: `$INSTANCE_NAME`.h
//  Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
//
//
//  DESCRIPTION: SDCard User Module C Language header file for the
//               PSoC family of devices.  This header file contains only
//               the functions that are should be used by the programmer.
//
//-----------------------------------------------------------------------------
//  The original source for this user module was purchased from
//  Efficient Computer Systems, LLC.
//-----------------------------------------------------------------------------
//
//  Copyright 2003-2006   Efficient Computer Systems, LLC
//  Licensed only for use on any Cypress PSOC Mixed-Signal Controllers.
//  All rights reserved
//
//-----------------------------------------------------------------------------
//
//         Created 12-04-03   By: Lee W. Morin and Herb Winters
//  1.00   Release 04-24-06   By: Lee Morin, Herb Winters, Eric Curtis
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2013-14. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#if !defined(`$INSTANCE_NAME`_HEADER)
#define `$INSTANCE_NAME`_HEADER

#include "`$INSTANCE_NAME`_SPI.h"
#include "`$INSTANCE_NAME`_FS.h"

#include "`$INSTANCE_NAME`_SD_CS.h"
#include "`$INSTANCE_NAME`_SD_PWR.h"

#include "CyLib.h"

//---------------------------------------------------------------------------------------------
//                                   Function Prototypes
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//                                Basic Read Write commands
//---------------------------------------------------------------------------------------------

void    `$INSTANCE_NAME`_Start(void);                       // Starts SD card module
void    `$INSTANCE_NAME`_Stop(void);                        // Stops  SD card module
uint8   `$INSTANCE_NAME`_InitCard(void);                    // Runs all commands to init card for use
uint8   `$INSTANCE_NAME`_fseek(uint8 Fptr, uint32 Offset);  // Seeks a specific offet into file
uint8   `$INSTANCE_NAME`_fgetc(uint8 Fptr);                 // Returns the next character from the file pointed to
uint8   `$INSTANCE_NAME`_fbgetc(uint8 Fptr);                // Returns the next buffered character from the file pointed to
void    `$INSTANCE_NAME`_clearerr(uint8 Fptr);              // Clears the error flags for the file
uint8   `$INSTANCE_NAME`_ferror(uint8 Fptr);                // Returns non-zero for file error, zero if no error
uint32  `$INSTANCE_NAME`_ftell(uint8 Fptr);                 // Return the current postion within the file
uint8   `$INSTANCE_NAME`_ReadSect(uint32 address);          // Read a sector

#ifdef  `$INSTANCE_NAME`_ENABLE_PRESENT
uint8   `$INSTANCE_NAME`_Present(void);                     // Returns a '1' if a card is present in the socket, '0' if not
#endif

#ifdef  `$INSTANCE_NAME`_ENABLE_WPROTECT
uint8   `$INSTANCE_NAME`_WriteProtect(void);                // Returns a '1' if the card is write protected using ther slide switch, '0' if not
#endif

#ifdef ENABLE_WRITE
uint8   `$INSTANCE_NAME`_WriteSect(uint32 address);         // Write a sector
uint8   `$INSTANCE_NAME`_fputc(uint8 Data, uint8 Fptr);     // Write a character to a file
uint8   `$INSTANCE_NAME`_fputs(uint8 *str, uint8 Fptr);     // Writes a null-terminated string to a file.
uint8   `$INSTANCE_NAME`_fputcs(uint8 *str, uint8 Fptr);    // Writes a null-terminated const string to a file.
uint8   `$INSTANCE_NAME`_fputBuff(uint8 *buff, uint16 count, uint8 Fptr);
uint8   `$INSTANCE_NAME`_fputcBuff(uint8 *buff, uint16 count, uint8 Fptr);
void    `$INSTANCE_NAME`_fflush(uint8 Fptr);                // Flush the write buffers (to the file and update dir values in FILESYSTEM mode)
#endif

//---------------------------
// Top level file functions
//---------------------------
#ifdef ENABLE_FILESYSTEM
uint8   `$INSTANCE_NAME`_fclose(uint8 Fptr);                // Closes a file pointer
uint8   `$INSTANCE_NAME`_fopen(uint8 Filename[], uint8 Mode[]);   // Opens a file as type and returns the file pointer
uint8 * `$INSTANCE_NAME`_GetFilename(uint16 Entry);         // Returns filename for directory entry specified.
uint16  `$INSTANCE_NAME`_GetFileCount(void);                // Returns the number of valid files in the root directory
uint32  `$INSTANCE_NAME`_GetFileSize(uint8 Fptr);           // Returns the file size of the file pointed to
uint8   `$INSTANCE_NAME`_feof(uint8 Fptr);                  // Returns non-zero for EOF, zero if no EOF

// ============================================================================
// = Top level writing functions
// ============================================================================
#ifdef ENABLE_WRITE
uint8   `$INSTANCE_NAME`_Remove(uint8 * Filename);          // Delete the file indicated by Filename
uint8   `$INSTANCE_NAME`_Rename(uint8 * OldFilename, uint8 * NewFilename);  // Rename a file
uint8   `$INSTANCE_NAME`_Copy(uint8 * OldFilename, uint8 * NewFilename);    // Copy a file
#endif  // End ENABLE_WRITE
#endif  // End ENABLE_FILESYSTEM

// = CardInfo defines
#define `$INSTANCE_NAME`_FORMAT_FAT12    0x10
#define `$INSTANCE_NAME`_FORMAT_FAT16    0x40
#define `$INSTANCE_NAME`_FORMAT_FAT16a   0x40
#define `$INSTANCE_NAME`_FORMAT_FAT16b   0x60
#define `$INSTANCE_NAME`_FORMAT_FAT32    0xB0
#define `$INSTANCE_NAME`_FORMAT_VALID    0xE0
#define `$INSTANCE_NAME`_FORMAT_MASK     0xF0

#define `$INSTANCE_NAME`_TYPE_NONE       0x00
#define `$INSTANCE_NAME`_TYPE_MMC        0x01
#define `$INSTANCE_NAME`_TYPE_SD         0x02
#define `$INSTANCE_NAME`_TYPE_MASK       0x03

#endif

// ============================================================================

