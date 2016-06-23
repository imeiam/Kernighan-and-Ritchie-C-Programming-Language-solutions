/*
   Write fseek.
   To avoid confusion, my implementation of standard definitions have a suffix "x" 
Note: This solution uses field based approach to handle flags as a continuation of the previous solution
 
 */

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

#define EOF (-1)
#define OPEN_MAX 20 // Maximum files that can be open
#define PERMS 0666


#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2


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
	if(fp->base == NULL){
		if((fp->base = (char *) malloc (bufsize))==NULL)
			return EOF;
	}
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


int fflushx(FILEx *fp){
	

	if(fp==NULL){
		for(fp=_iob;fp<_iob+OPEN_MAX;fp++){
			if(is_empty(fp->flags))
				continue;
			fflushx(fp); // Recursively calling fflushx as in this loop fp can never be NULL.
		}
	}
	else if(fp->flags._WRITE == 0)
		return EOF;
	else{
		//Flush the output buffer
		int bufsize = (fp->flags._UNBUF != 0)? 1:BUFSIZ;
		if(write(fp->fd,fp->base,bufsize-fp->cnt)!=bufsize-fp->cnt){
			puts("fflush -Write Error");
			return EOF;
		}
		fp->cnt = bufsize;
		fp->ptr = fp->base;
	}
	return 0;
}


int fseekx(FILEx *fp,int offset,int origin){
	
	if(fp==NULL)
		return EOF;
	if(fp->flags._WRITE != 0){
		fflushx(fp);
		return EOF;
	} else if(fp->flags._READ != 0){
		int bufsize = (fp->flags._UNBUF != 0)? 1:BUFSIZ;
		switch(origin){
			case SEEK_SET:
				if(offset<0)
					return EOF;
				if(lseek(fp->fd,offset,SEEK_SET)<0){
					return EOF;//Error
				}
				fp->ptr = fp->base;
				fp->cnt = 0; // Request reload of buffer
				break;
			case SEEK_END:	
				if(offset>0)
					return EOF;
				if(lseek(fp->fd,offset,SEEK_END)<0){
					puts("Seek Error");
					return EOF;
				}
				fp->ptr = fp->base;
				fp->cnt=0; // Request reload of buffer
				break;
			case SEEK_CUR:
				if(offset>0){
					if(lseek(fp->fd,offset,SEEK_CUR)<0)
						return EOF;
					fp->ptr = fp->base;
					fp->cnt=0; // Request reload of buffer as buffer might not be full
				} else if(offset<0){
					// Use the same Buffer instead of reloading.
					if(offset<=bufsize-(fp->cnt)){
						fp->ptr = fp->ptr - offset;
					}
					else{
						if(lseek(fp->fd,offset,SEEK_CUR)<0)
							return EOF;
						fp->ptr = fp->base;
						fp->cnt=0;
					}
				}
		}	
	}	
	return 0;
}



int main(void){
	
	FILEx *fp = fopenx("ctest.txt","r");
	if(fp!=NULL){	
		char c;
		// getcx is a macro defined above
		fseekx(fp,5L,SEEK_CUR);
		while((c=getcx(fp))!=EOF){
			putchar(c);
		}
	}
	return 0;
}
