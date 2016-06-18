/*
   Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs, based on the routines of this section. You may also find getch and ungetch helpful.
   */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASHSIZE 101
#define MAXLEN 200
#define BUFSIZE 1000
#define STATE_OUT 321
#define STATE_IN_NO_NAME 322
#define STATE_IN_WITH_NAME 323


static int state = STATE_OUT; // Initial state


char buf[BUFSIZE];
int bufp = 0;


int getch(FILE *fp){
	return (bufp > 0)? buf[--bufp] : fgetc(fp);
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("\nUngetch: Too many characters");
	else
		buf[bufp++] = c;
}

// Data structure to store the definitions
typedef struct list{
	struct list *next;
	char *name;
	char *defn;
}nlist;

static nlist *hashtab[HASHSIZE]; // Pointer Table


// Hash
unsigned hash(char *s){

	unsigned hashval;
	
	for(hashval=0; *s!='\0'; s++)
		hashval = *s + 31 * hashval;

	return hashval%HASHSIZE;
}


//Lookup

nlist *lookup(char *s){

	nlist *np;
	
	for(np = hashtab[hash(s)];np!=NULL;np=np->next)
		if(strcmp(np->name,s) == 0)
			return np;
	return NULL;
}

// Install

nlist *install(char *name,char *defn){

	nlist *np;
	unsigned hashval;
	hashval = hash(name);

	if((np = lookup(name))== NULL){

		np = (nlist *) malloc(sizeof(nlist));
		if((np->name=strdup(name))==NULL)
			return NULL;
		np->next = NULL;
		if(hashtab[hashval]==NULL){
			hashtab[hashval] = np;
		} else {
			np->next = hashtab[hashval];
			hashtab[hashval] = np;
		}
	}
	else
		free((void *) np->defn);

	if((np->defn = strdup(defn))==NULL)
		return NULL;
	return np;
}


// Print the Lookup Table
void print_all_def(){
	int i=0;
	for(;i<HASHSIZE;i++){
		if(hashtab[i]!=NULL){
			nlist *p = hashtab[i];
			while(p!=NULL){
				printf("LABEL: %s DEFN: %s\n",p->name,p->defn);
				p = p->next;
			}
		}
	}
}

int getword(char *word,int lim,FILE *fp){
	
	int c;
	char *w = word;

	while(isspace(c = getch(fp)));
	if(c==EOF){
		if(state == STATE_OUT)
			return -1;
		else{
			puts("Error: Incorrect definition\n");
			return -1;
		}
	}
	// Word should be identifier in STATE_IN_WITH_NAME to name the definition
	if(isalpha(c) || c=='_' || (state == STATE_OUT) || state==STATE_IN_WITH_NAME)
		*w++=c;
	if(!isalpha(c) && c!='_' && state!=STATE_OUT && state!=STATE_IN_WITH_NAME){
		*w = '\0';
		return w-word;
	}
	for(; --lim>0; w++){
		*w = getch(fp);
		if(state!=STATE_IN_WITH_NAME){
			// Name of definition must be a valid identifier
			if((!isalnum(*w) && *w!='_')){
				ungetch(*w);
				break;
			}
		}
		else
			if(isspace(*w)) // Definition can be any character
				break;
	}
	*w = '\0';
	return w-word;
}

int main(void){
	puts("\nCheck t6.txt to understand the below output:\n");	
	char line[MAXLEN];
	FILE *fp = fopen("t6.txt","r");
	char *name,*defn,*p;
	int len;
	if(fp!=NULL){
		while((len = getword(line,MAXLEN,fp)>0)){
			switch(state){

				case STATE_OUT:
					if(strcmp(line,"#define")==0)
						state = STATE_IN_NO_NAME;
					else{
						/*
						   Check if line is present in lookup table,
						   if yes, substitute the definition, else print as it is.
						   */
						nlist *np;
						if((np=lookup(line))==NULL)
							printf("%s ",line);
						else
							printf("%s ",np->defn);
					}	
					break;
				case STATE_IN_NO_NAME:
					// Received name for definition
					name = (char *) malloc(len);
					strcpy(name,line);
					state = STATE_IN_WITH_NAME;
					break;
				case STATE_IN_WITH_NAME:
					// Received defn for name
					defn = (char *) malloc(len);
					strcpy(defn,line);
					// Update the lookup table
					if(install(name,defn)==NULL){
						puts("Insert Error");
						return -1;
					}
					state = STATE_OUT;
					break;
			}
		}
		// Print the Lookup Table
		printf("\nLookup Table Now: \n");
		print_all_def();
		fclose(fp);
	}
	return 0;
}

