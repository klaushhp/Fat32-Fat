#include <string.h>
#include "logrecord.h"


#define Logindex_base 	71
#define Logtable_base 	72


FRESULT create_recover() {
    
	printf("hahahaha create_recover success\n");
	return 0;
}

FRESULT update_recover() {

	return 0;
}

FRESULT delete_recover() {

	return 0;
}

FRESULT truncate_recover() {

	return 0;
}

FRESULT rename_recover() {

	return 0;
}




FRESULT log_recover(BYTE *buf) {
	BYTE log_index;
	BYTE logbuf[512];
	FRESULT res;
		
	log_index = *( buf + LOG_Index );
	if(  disk_read(0,logbuf,Logtable_base + log_index,1) != RES_OK )
		return FR_DISK_ERR;

	switch (*( logbuf + LOG_Type ) ) {
	case LOG_Create:
		res = create_recover();
		break;

	case LOG_Update:
		res = update_recover();
 		break;

	case LOG_Delete:
		res = delete_recover();
		break;

	case LOG_Truncate:
		res = truncate_recover();
		break;

	case LOG_Rename:
		res = rename_recover();
		break;

	}	

	return res;

}	


FRESULT log_check (void) {
	BYTE buf[512];
	
	memset(buf,0,sizeof(buf));
	if ( disk_read(0,buf,Logindex_base,1) != RES_OK ) 
		return FR_DISK_ERR;
	if( *(buf+LOG_Count) != 0 )
		log_recover(buf);

	return 0;
}
	
 		
