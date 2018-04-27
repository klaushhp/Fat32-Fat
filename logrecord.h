#include <stdio.h>
#include "integer.h"
#include "ff.h"
#include "diskio.h"


/* Power off safe log record structure */
typedef struct {
	BYTE 	dir_name[11]; 		/* Short name */
	BYTE 	dir_attr;           /* File attributes */
	BYTE    dir_lfnct; 			/* Long File names Entries Count */
	BYTE 	logtype; 			/* 0x01-Create 0x02-Update 0x03-Delete 0x04-Truncate 
									0x05-rename 0x00-DIR log operation of previous record */
	DWORD 	dir_dclst; 			/* Directory cluster in which this 32 bytes directory entry exist */
	WORD 	dir_index;        	/* This ponits to 32 bytes directory entry */
	WORD    fstclst_hi; 		/* high word of this entry's first cluster number 
									if DIR log is Update then this value indicates high word of last cluster before update */
	DWORD 	dir_clst; 			/* */
	WORD 	fstclst_lo; 		/* Low word of this entry's first cluster number
							   		If DIR log is Update then this value indicates low word of last cluster before update */
	DWORD 	filesize; 			/* File size in bytes */
} LOG;


/* Log record index structure */
typedef struct {
	BYTE 	log_index;      	/* point to current log */
	BYTE 	log_count; 			/* Log records count */
	BYTE 	fat1_dirty;         /* 0:fat1 is clean  1:fat1 is dirty */
	BYTE  	fat2_dirty; 		/* 0:fat2 is clean  1:fat2 is dirty */
}LOGINDEX;


/* Log table structure related member offset */
#define LOG_Name 			0
#define LOG_Attr 			11
#define LOG_LfnCnt          12
#define LOG_Type 			13
#define LOG_Dclst 			14
#define LOG_Dirindex 		18
#define LOG_FstClstHi 		20
#define LOG_Dirclst 		22
#define LOG_FstClstLo   	26
#define LOG_FileSize   		28

/* Log type */
#define LOG_Previous 		0x00
#define LOG_Create 			0x01
#define LOG_Update  		0x02
#define LOG_Delete 			0x03
#define LOG_Truncate 		0x04
#define LOG_Rename  		0x05


/* Log record index structure related member offset */
#define LOG_Index 			0
#define LOG_Count 			1
#define FAT1_Dirty 			2
#define FAT2_Dirty  		3




