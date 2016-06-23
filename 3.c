/*
   Design and write _flushbuf , fflush and fclose. 
Note: This solution uses field based approach to handle flags as a continuation of the previous solution
 */

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

#define EOF (-1)
#define OPEN_MAX 20 // Maximum files that can be open
#define PERMS 0766



// Field based approach for flags
typedef struct _flags{
	int _READ;
	int _WRITE;
	int _UNBUF;
	int _EOF;
	int _ERR;
}flags;

// File Data structre.

typedef struct _iobuf {
	int cnt;
	char *ptr;
	char *base;
	struct _flags flags;
	int fd;
}FILEx;

FILEx _iob[OPEN_MAX];


int _fillbuffx(FILEx *f);


#define getcx(p) (--(p)->cnt >= 0? (unsigned char) *(p)->ptr++:_fillbufx(p))

#define putcx(x,p) (--(p)->cnt >= 0? *(p)->ptr++=(x):_flushbufx((x),p))




//Check if Slot is empty by checking if all fields are
//empty in the flags structure


int is_empty(struct _flags flags){
	if(!flags._READ && !flags._WRITE && !flags._UNBUF &&
			!flags._EOF && !flags._ERR)
		return 1;
	return 0;
}



FILEx *fopenx(char *name,char *mode){
	
	int fd;
	FILEx *fp;
	// Invalid Input
	if( *mode != 'r' && *mode != 'w' && *mode != 'a' )
		return NULL;

	// Check for free slot
	for( fp= _iob; fp< _iob + OPEN_MAX ; fp++)
		if(is_empty(fp->flags))
			break;
	// If FULL return NULL
	if( fp>= _iob+OPEN_MAX )
		return NULL;
	// Create file on Write Mode
	if( *mode == 'w')
		fd = creat(name,PERMS);
	// Append Mode - If file not present create one
	else if( *mode == 'a') {
		if((fd = open(name,O_WRONLY,0))==-1)
			fd = creat(name,PERMS);
		lseek(fd,0L,2); // Go to end, in case of append
	}
	else
		fd = open(name,O_RDONLY,0);
	if(fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt=0;
	if(*mode == 'r')
		fp->flags._READ = 1;
	else
		fp->flags._WRITE = 1;
	return fp;
}



int _fillbufx(FILEx *fp){

	int bufsize;

	if(fp->flags._READ == 0)
		return EOF;
	bufsize = (fp->flags._UNBUF != 0)? 1:BUFSIZ;
	if(fp->base == NULL)
		if((fp->base = (char *) malloc (bufsize))==NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd,fp->ptr,bufsize);
	if(--fp->cnt< 0){

		if(fp->cnt == -1)
			fp->flags._EOF=1;
		else
			fp->flags._ERR=1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}




//fflushx
int fflushx(FILEx *fp){
	
	int bufsize = (fp->flags._UNBUF != 0)? 1:BUFSIZ;

	if(fp==NULL){
	}
	else if(fp->flags._WRITE == 0)
		return EOF;
	else{
		//Flush the output buffer
		if(write(fp->fd,fp->base,bufsize-fp->cnt)!=bufsize-fp->cnt){
			puts("fflush -Write Error");
			return EOF;
		}
		fp->cnt = bufsize;
		fp->ptr = fp->base;
	}
	return 0;
}







// _flushbufx
int _flushbufx(char c,FILEx *fp){

	int bufsize;
	
	// If fp is not an output stream return NULL
	if(fp->flags._WRITE == 0)
		return EOF;

	bufsize = (fp->flags._UNBUF != 0)? 1:BUFSIZ;
	
	if(fp->base == NULL){
		if((fp->base = (char *) malloc (bufsize))==NULL)
			return EOF;
		fp->cnt = bufsize;
		fp->ptr = fp->base;
	}
	else{
		//This function is called only when 
		//buffer is Full or Buffer is NULL
		write(fp->fd,fp->base,bufsize);
		fp->cnt = bufsize;
		fp->ptr = fp->base;
	}
	if(write(fp->fd,&c,1)!=1){
		puts("Write Error!");
		return EOF;
	}
	return 0;
}






void clear_flags(struct _flags flags){

	flags._READ =0;
        flags._WRITE=0;
	flags._UNBUF=0;
	flags._EOF  =0;
	flags._ERR=0;
}

// fclosex

int fclosex(FILEx *fp){
	if(fp==NULL)
		return -1;
	fflushx(fp); // Clears the output buffer for an output stream	
	fp->cnt=0;
	fp->base=NULL;
	fp->ptr= NULL;
	clear_flags(fp->flags);
	return close(fp->fd);
}




int main(void){
	/* TESTING READ OPERATION	
	FILEx *fp = fopenx("test.c","r");
	if(fp!=NULL){	
		char c;
		// getcx is a macro defined above
		while((c=getcx(fp))!=EOF)
			putchar(c);
	}
	else
		puts("Error"); */


	// TESTING WRITE OPERATION	
	FILEx *fp = fopenx("writeone.txt","w");
	if(fp!=NULL){	
		char c;
		puts("Enter the String to write to file:(End with $)");
		while((c=getchar())!='$'){
			putcx(c,fp);
		}
		if(fclosex(fp) ==0)
			puts("File close - Success");
		else 
			puts("File close - Failure");
	}
	return 0;
}
