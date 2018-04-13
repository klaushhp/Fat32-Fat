#include "ff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
PARTITION VolToPart[] = {
    {0,1},
    {0,2}
};
#endif
 int main(int argc, const char *argv[])
{
	FATFS fs;
	FIL fil1,fil2,fil3;
	FRESULT res;
	UINT bw;
	BYTE work[FF_MAX_SS];
	BYTE buf[256];
	FSIZE_t fptr;

    DWORD plist[] = {50,50,0,0};
	
	res = f_fdisk(0,plist,work);
	if(res != FR_OK) {
		printf("fail to f_fdisk,res = %d\n",res);
		return -1;
	}


    res = f_mkfs("",FM_FAT32,4096,work,sizeof(work));
	if(res != FR_OK) {
		printf("fail to mkfs,res = %d\n",res);
		return -1;
	}


	
    res = f_mount(&fs,"",0) ;
    if(res != FR_OK) {
		printf("fail to mount,res = %d\n",res);
		return -1;
	}

#if 1

	res = f_open(&fil1,"hello.txt",FA_CREATE_NEW|FA_WRITE);
	if(res != FR_OK) {	
		printf("fail to open hello.txt,res = %d\n",res);
		return -1;
	}	
       
	res = f_write(&fil1,"hello,world!\r\n",15,&bw);

	if(res != FR_OK) {	
		printf("fail to write to  hello.txt,res = %d\n",res);
		return -1;
	}

	printf("%d bytes are wrote to hello.txt\n",bw);


	f_close(&fil1);



    res = f_open(&fil2,"duangduang.txt",FA_CREATE_NEW|FA_WRITE|FA_READ);
	if(res != FR_OK) {	
		printf("fail to open duangduang.txt,res = %d\n",res);
		return -1;
	}	
       
    res = f_write(&fil2,"long long ago!lalala\r\n",22,&bw);

	if(res != FR_OK) {	
		printf("fail to write to  duangduang.txt,res = %d\n",res);
		return -1;
	}

	printf("%d bytes are wrote to duangduang.txt\n",bw);

    f_lseek(&fil2,0);
    memset(buf,0,sizeof(buf));
    res = f_read(&fil2,buf,sizeof(fil2),&bw);
    if(res != FR_OK) {
        printf("fail to read duangduang.txt,res = %d\n",res);
        return -1;
    }
	printf("%s\n",buf);

	f_close(&fil2);

	f_rename("hello.txt","hi.txt");
	f_mkdir("0:/dudu");
#endif

	f_mkdir("0:/dudu");
 	res = f_open(&fil3,"dudu/didi.txt",FA_CREATE_NEW|FA_WRITE|FA_READ);
  	res = f_write(&fil3,"hello,world!\r\n",15,&bw);

	f_close(&fil3);

	return 0;
}
