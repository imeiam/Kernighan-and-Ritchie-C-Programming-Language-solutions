/*
   Sort with options:
	# -f =  Case insensitive sorting.
	# -d = Only numbers, letters and blanks	
	# -n = Sort by score only.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LINES 10
#define MAX_LEN 1000
#define MAX_LINES 100


// Fields in the line.
typedef struct x{
	char str[100];
	int score;
}node;


// Array to maintain all the nodes
node arr_node[MAX_LINES];
int node_count=0;


// Sort the nodes based on three flags.
void sort(node arr_node[],int n,int fold_flag,int d_flag,int n_flag){

	int i;
	char *p;
	node temp;

	if(n_flag){
// Sort based on scores only
		for(i=0;i<n-1;i++){

			if(arr_node[i].score > arr_node[i+1].score){
				temp = arr_node[i];
				arr_node[i] = arr_node[i+1];
				arr_node[i+1] = temp;
				i=-1;
			}
		}
	}
	else{
		// SORT based on Names only
		for(i=0;i<n-1;i++){
			if(strcustomcmp(arr_node[i].str,strlen(arr_node[i].str),arr_node[i+1].str,arr_node[i+1].str,strlen(arr_node[i+1].str),fold_flag,d_flag)>0){
				temp = arr_node[i];
				arr_node[i] = arr_node[i+1];
				arr_node[i+1] = temp;
				i=-1;
			}
		}
	}
}
	
int strcustomcmp(char *s,int slen,char *t,int tlen,int f_flag,int d_flag){

		if(d_flag){

			while( !isalnum(*s) && !isspace(*s)){
				if(*s=='\0')
					return 1;// meaning non comparable strings will occur at the end
				s++;
			}
			while( !isalnum(*t) && !isspace(*t)){
				if(*t=='\0')
					return -1; // to show t>s. Same reason as above;
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
			if(*s=='\0' || *t == '\0')
				return (slen>tlen)? 1:-1; // Return longer string
			if(d_flag){
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
	int d_flag=0,f_flag=0,n_flag=0;
	int i;
	for(i=1;i<argc;i++){
		if(strcmp(argv[i],"-f") ==  0){
			if(n_flag){
				printf("\nError: Use -fd or -n and not both\n");
				return 0;
			}
			f_flag = 1;
		} else if(strcmp(argv[i],"-d") == 0){
			if(n_flag){
				printf("\nError: Use -fd or -n and not both\n");
				return 0;
			}
			d_flag = 1;
		} else if(strcmp(argv[i],"-fd") == 0  ||  strcmp(argv[i],"-df")==0){
			if(n_flag){
				printf("\nError: Use -fd or -n and not both\n");
				return 0;
			}
			f_flag = 1;
			d_flag = 1;
		} else if(strcmp(argv[i],"-n") == 0){
			if(d_flag || f_flag){
				printf("\nError: Use -fd or -n and not both\n");
				return 0;
			}
			n_flag = 1;
		}
		else{
			printf("\nError: Illegal Option\n");
			return 0;
		}
	}
	printf("D - %d F - %d\n N-%d\n",d_flag,f_flag,n_flag);
	FILE *fp  = fopen("t17.txt","r");
	if(fp!=NULL){
		while((len = getlinex(line,MAX_LEN,fp)) != 0){
			lines[line_count] = (char *) malloc (MAX_LEN);
			strcpy(lines[line_count++],line);
			if(line_count == MAX_LINES)
				break;
		}
		int i;
		char *delim;
		for(i=0;i<line_count;i++){
			delim = strrchr(lines[i],'^');
			if(delim!=NULL){
				*delim++ = '\0';
				arr_node[node_count].score = atoi(delim);
				strcpy(arr_node[node_count].str,lines[i]);
				node_count++;
			}
		}
		sort(arr_node,node_count,f_flag,d_flag,n_flag);
		puts("Results: ");
		for(i=0;i<node_count;i++){
			printf("%s - %d \n",arr_node[i].str,arr_node[i].score);
//			printf("%d\n",arr_node[i].score);
		}
		fclose(fp);
	}
	return 0;
}
