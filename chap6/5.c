/*
   Write a function undef that will remove a name and definition from the table maintained by lookup and install .
   */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASHSIZE 101
#define MAXLEN 200

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


int getlinex(char *str,int lim,FILE *fp){

	char *p = str,c;
	while(--lim>0 && (c = fgetc(fp)) && c!=EOF && c!='\n')
		*p++ = c;
	*p = '\0';
	return p-str;
}

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

int undef(char *name){
	
	unsigned hashval = hash(name);

	nlist *np = hashtab[hashval];

	nlist *temp;
	if(np!=NULL){
		if(strcasecmp(np->name,name)==0){
			hashtab[hashval] = np->next;
			free((void *)np);
			return 1;
		}
		else{
			while(np->next!=NULL){
				if(strcasecmp(np->next->name,name)==0){
					temp = np->next;
					np->next = temp->next;
					free((void *)temp);
					return 1;
				}
			}
		}
	}
	return -1;
}

int main(void){
	
	char line[MAXLEN],*p;
	FILE *fp = fopen("t5.txt","r");
	if(fp!=NULL){
		while(getlinex(line,MAXLEN,fp)>0){
			p= strchr(line,'$');
			if(p==NULL){
				puts("Invalid input - Line should be \"akil$adeshwar\"");
				return 0;
			}
			*p++='\0';
			if(install(line,p)==NULL){
				puts("\nInsert Error!");
				return 0;
			}
		}
		print_all_def();
		fclose(fp);
	}
	puts("Enter the Label to remove: ");
	fgets(line,MAXLEN,stdin);
	line[strlen(line)-1]='\0'; // avoid newline from fgets
	if(undef(line)!=-1){
		puts("\nLabel Table Now:");
		print_all_def();	
	} else
		puts("\nError! Invalid label\n");
	return 0;
}

