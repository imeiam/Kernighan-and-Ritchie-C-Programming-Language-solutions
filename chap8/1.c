/*
   Rewrite the program cat from Chapter 7 using read
   , write , open and close instead of their standard library equivalents. Perform experiments
   to determine the relative speeds of the two versions.

   */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char *argv[]){

	int fd;
	char line[BUFSIZ];
	int n;
	if(argc == 1){
		while((n=read(0,line,BUFSIZ))>0){

			// Default - If no arguments Use stdin and stdout
			if(write(1,line,n)!=n){
				puts("Write Error!");
				return 0;
			}
		}
	}
	else{
		while(--argc>0){
			if((fd=open(*++argv, O_RDONLY , 0 ))!=-1){

				// Format display
				line[0] = '\0';
				strcat(line,"\n\n");
				strcat(line,*argv);
				strcat(line," : \n\n");
				char *p = line;
				while(*p){
					write(1,p,1);
					p++;
				}

				// Main logic
				while((n=read(fd,line,BUFSIZ))>0){
					if(write(1,line,n)!=n){
						puts("Write Error!");
						return 0;
					}
				}
				close(fd);
			}
			else{
				puts("File Read Error!");
				return 0;
			}
		}
	}
	return 0;
}
