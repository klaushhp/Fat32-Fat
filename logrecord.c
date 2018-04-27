#include <string.h>

#define Logindex_base 	71
#define Logtable_base 	72

FRESULT log_recover(BYTE buf) {
	BYTE log_index;
	BYTE logbuf[512];
	FRESULT res;
		
	log_index = *(buf +LOG_Index);
	if(  disk_read(0,logbuf,Logtable_base + log_index,1) != RES_OK )
		return FR_DISK_ERR;

	switch (*( logbuf + LOG_Type ) ) {
	case LOG_Create:
		res = create_recover();

	case LOG_Update:
		res = update_recover();

	case LOG_Delete:
		res = delete_recover();

	case LOG_truncate:
		res = truncate_recover();

	case LOG_Rename:
		res = rename_recover();

	return res;

}	

void log_check (void) {
	BYTE buf[512];
	
	memset(buf,0,sizeof(buf));
	if ( disk_read(0,buf,Logtindex_base,1) != RES_OK ) 
		return -1;
	if( *(buf+LOG_Count) != 0 )
		log_recover(buf);

	return ;
}
	
 		
