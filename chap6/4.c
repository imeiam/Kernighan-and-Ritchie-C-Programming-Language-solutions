/*
   Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurrence. Precede each word by its count.
  
   */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BUFSIZE 1000
#define MAXLEN 100

#define GROUP_MAX 1000
#define COMP_INDEX_LIMIT_DEFAULT 1

char buf[BUFSIZE];
int bufp = 0;

typedef struct var{
	char word[MAXLEN];
	int count;
	struct var *left;
	struct var *right;
}word;



word *root  = NULL;

void copy_var(word *s,word *t){

	strcpy(s->word,t->word);
	s->count = t->count;
	s->left = t->left;
	s->right = t->right;

}


word *add_to_tree(word *root,word *p){

	if(root == NULL){
		root = (word *) malloc(sizeof(word));
		copy_var(root,p);
	}
	else{
		// For descending order
		if(strcasecmp(p->word,root->word)>0)
			root->left = add_to_tree(root->left,p);
		else if(strcasecmp(p->word,root->word)<0)
			root->right = add_to_tree(root->right,p);
		else
			root->count++; // Same word occuring again
	}
	return root;
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
		return w-word;
	}
	for(; --lim>0; w++){
		*w = getch(fp);
		if(!isalpha(*w)){
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return w-word;
}



word *create_node(char *w){

	word *a = (word *) malloc(sizeof(word));
	strcpy(a->word,w);
	a->count = 1; // Found one already.
	a->left = NULL;
	a->right= NULL;
	return a;
}

void traverse_tree(word *root){

	if(root!=NULL){
		traverse_tree(root->left);
		printf("Count: %d - Word: %s\n",root->count,root->word);
		traverse_tree(root->right);
	}
}

int main(int argc,char *argv[]){

	char line[MAXLEN];
	FILE *fp = fopen("t4.txt","r");
	if(fp!=NULL){
		while(getword(line,MAXLEN,fp)!=-1){
			if(line[0]!='\0'){	
				//puts(line);
				word *node = create_node(line);
				//puts(node->word);
				root = add_to_tree(root,node);
			}
		}
		fclose(fp);
		puts("Results:");
		traverse_tree(root);
	}
	return 0;
}
