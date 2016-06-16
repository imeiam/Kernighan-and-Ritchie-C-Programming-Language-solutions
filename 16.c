/*

   Sort with options:

	# -f =  Case insensitive sorting.
	# -d =  Only numbers, letters and blanks

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LINES 10
#define MAX_LEN 1000
#define MAX_LINES 100

void sort(char *lines[],int n,int fold_flag,int d_flag){

	int i;
	char *p;

	if(fold_flag){
		for(i=0;i<n-1;i++){
			if(strcustomcmp(lines[i],strlen(lines[i]),lines[i+1],strlen(lines[i+1]),fold_flag,d_flag)>0){
				p = lines[i];
				lines[i] = lines[i+1];
				lines[i+1] = p;
				i=-1;
			}
		}
	}
	else{
		for(i=0;i<n-1;i++){
			if(strcustomcmp(lines[i],strlen(lines[i]),lines[i+1],strlen(lines[i+1]),fold_flag,d_flag)>0){
				p = lines[i];
				lines[i] = lines[i+1];
				lines[i+1] = p;
				i=-1;
			}
		}
	}
}

int strcustomcmp(char *s,int slen,char *t,int tlen,int f_flag,int d_flag){

		if(d_flag){

			while( !isalnum(*s) && !isspace(*s)){
				if(*s=='\0'){
					//printf("\nError: String contains only invalid chars\n");// Cannot compare.
					//exit(0);
					return 1;// meaning non comparable strings will occur at the end
				}
				s++;
			}
			while( !isalnum(*t) && !isspace(*t)){
				if(*t=='\0'){
					//printf("\nError: String contains only invalid chars\n");// Cannot compare.
					//exit(0);
					return -1; // to show t>s. Same reason as above;
				}
				t++;
			}
		}

		while(1){

			char sc,tc;
			if(f_flag){
				// when fold flag is enabled.
				sc = tolower(*s);
				tc = tolower(*t);
			}
			else{
				sc = *s;
				tc = *t;
			}		
			if(sc != tc)
				break; // exit loop on not equal;
			s++;
			t++;
			while( !isalnum(*s) && !isspace(*s)){
				if(*s=='\0')
					return (slen>tlen)? 1:-1; // Return longer string
				s++;
			}
			while( !isalnum(*t) && !isspace(*t)){
				if(*t=='\0')
					return (slen>tlen)? 1:-1; // Return longer string
				t++;
			}
		}
		return (f_flag)? (tolower(*s) - tolower(*t)):(*s-*t);
}

int getlinex(char s[], int lim,FILE *fp)
{
	int c, i;
    	for (i = 0; i < lim - 1 && (c = fgetc(fp)) != EOF && c != '\n'; i++)
	 	s[i] = c;
	s[i] = '\0';
	return i;
}


int main(int argc,char *argv[]){
	char *lines[MAX_LINES];
	int len;
	char line[MAX_LEN];
	int line_count=0;
	int d_flag=0,f_flag=0;
	int i;
	for(i=1;i<argc;i++){
		if(strcmp(argv[i],"-f") ==  0){
			f_flag = 1;
		} else if(strcmp(argv[i],"-d") == 0){
			d_flag = 1;
		} else if(strcmp(argv[i],"-fd") == 0  ||  strcmp(argv[i],"-df")==0){
			f_flag = 1;
			d_flag = 1;
		}
		else{
			printf("\nError: Illegal Option\n");
			return 0;
		}
	}
	printf("D - %d F - %d\n",d_flag,f_flag);
	FILE *fp  = fopen("t16.txt","r");
	if(fp!=NULL){
		while((len = getlinex(line,MAX_LEN,fp)) != 0){
			lines[line_count] = (char *) malloc (MAX_LEN);
			strcpy(lines[line_count++],line);
			if(line_count == MAX_LINES)
				break;
		}
		int i;
		sort(lines,line_count,f_flag,d_flag);
		puts("Results: ");
		for(i=0;i<line_count;i++)
			puts(lines[i]);
		fclose(fp);
	}
	return 0;
}
