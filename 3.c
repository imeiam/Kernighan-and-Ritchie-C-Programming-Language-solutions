/*
   Write a cross-referencer that prints a list of all words in a document, and, for each word, a list of the line numbers on which it occurs. Remove noise words like "the," "and," and so on.
   */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BUFSIZE 1000
#define MAXLEN 100
#define MAX_STOP_WORDS 1500

char buf[BUFSIZE];
int bufp = 0;

int line_no = 1;


//char *stopword_arr[]  = {"include", "main" ,"return","int","char","void","maximus","\0"};
char *stopword_arr[MAX_STOP_WORDS];
int stopword_count=0;


int word_count = 0;
int filtered_word_count = 0;

int bin_search_stopword_arr(char find[]){

	int low,high;
	high = stopword_count-1;
	low =0;
	while(low<=high){
		int mid = (low+high)/2;
		//printf("%s -- %s + low: %d high %d mid %d \n",stopword_arr[mid],find,low,high,mid);
		int comp = strcmp(find,stopword_arr[mid]);
		if(comp == 0)
			return mid;
		else if(comp<0)
			high=mid-1;
		else
			low=mid+1;
	}
	return -1;
}

int getch(FILE *fp){
	return (bufp > 0)? buf[--bufp] : fgetc(fp);
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("\nUngetch: Too many characters");
	else
		buf[bufp++] = c;
}


int getlinex(char s[],int lim,FILE *fp){

	char *p = s;
	char c;
	while( --lim>0 && (c=fgetc(fp)) && c!='\n' && c!=EOF)
		*p++ = c;
	*p = '\0';
	return p-s;
}


// getword returns the length of the word.
int getword(char *word,int lim,FILE *fp){
	
	int c;
	char *w = word;

	while(isspace(c = getch(fp)));
	if(c==EOF)
		return -1;
	
	// Words must begin with alpha
	if(isalpha(c))
		*w++=c;

	if(!isalpha(c)){
		*w = '\0';
		if(c == '\n')
			line_no++;
		return w-word;
	}
	for(; --lim>0; w++){
		*w = getch(fp);
		if(*w=='\n')
			line_no++;

		if(!isalpha(*w)){
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return w-word;
}



// For using binary search

void sort_stopword_arr(){
	int i=0;
	char *t;
	for(i=0;i<stopword_count-1;i++){
		if(strcmp(stopword_arr[i],stopword_arr[i+1])>0){
			t = stopword_arr[i];
			stopword_arr[i] = stopword_arr[i+1];
			stopword_arr[i+1] = t;
			i = -1;
		}
	}
}

int main(int argc,char *argv[]){

	char line[MAXLEN];
	FILE *fp = fopen("t3.txt","r");
	if(fp!=NULL){

		// Add stop words
		FILE *swp = fopen("t3_stop.txt","r");
		if(swp==NULL)
			return 0;
		int len;
		while((len=getlinex(line,MAXLEN,swp))>0){
			stopword_arr[stopword_count] = (char *) malloc(len);
			strcpy(stopword_arr[stopword_count],line);
			stopword_count++;
		}
			
		// Calculate no of stopwords
		int i=0;
		//while(stopword_arr[i++][0]!='\0')
		//	stopword_count++;

		// Sort stopwords for binary search
		
		//sort_stopword_arr();

		// Sort list
		for(i=0;i<stopword_count;i++)
			puts(stopword_arr[i]);

		puts("Results: ");
		while(getword(line,MAXLEN,fp)!=-1){
			word_count++;
			if(line[0]!='\0' && bin_search_stopword_arr(line)==-1){
				printf("Word: %s - Line no: %d\n",line,line_no);
				filtered_word_count++;
			}
		}
		fclose(fp);
		printf("\nTotal No of words: %d\n",word_count);
		printf("\nTotal No of words after filtering: %d\n",filtered_word_count);
	}
	return 0;
}
