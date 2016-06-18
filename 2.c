/*
   Write a program that reads a C program and prints in alphabetical order each group of variable names that are identical in the first 6 characters but different somewhere thereafter. Don't count words within strings and comments. Make 6 a parameter that can be set from the command line.
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

char *keyword_arr[]  = {"include", "main" ,"return","int","char","void","\0"};
int keyword_count=0;


typedef struct var{
	char word[MAXLEN];
	int count;
	struct var *left;
	struct var *right;
}variable;



variable *root  = NULL;

variable groups[GROUP_MAX];
int group_count=0;

int cmp_index_limit = COMP_INDEX_LIMIT_DEFAULT;


void copy_var(variable *s,variable *t){

	strcpy(s->word,t->word);
	s->count = t->count;
	s->left = t->left;
	s->right = t->right;

}


variable *add_to_tree(variable *root,variable *p){

	if(root == NULL){
		root = (variable *) malloc(sizeof(variable));
		copy_var(root,p);
	}
	else{
		if(strcmp(p->word,root->word)<0)
			root->left = add_to_tree(root->left,p);
		else if(strcmp(p->word,root->word)>0)
			root->right = add_to_tree(root->right,p);
		else
			root->count++; // Same word occuring again
	}
	return root;
}


variable *add_to_group(variable *p){

	int i=0,inserted_flag=0;
	for(;i<group_count;i++){
		if(strncmp(groups[i].word,p->word,cmp_index_limit)==0){
			add_to_tree(&groups[i],p);
			inserted_flag=1;
		}
	}
	if(!inserted_flag){
		copy_var(&groups[group_count],p);
		group_count++;
	}
}

int bin_search_keyword_arr(char find[]){

	int low,high;
	high = keyword_count-1;
	low =0;
	while(low<=high){
		int mid = (low+high)/2;
		//printf("%s -- %s + low: %d high %d mid %d \n",keyword_arr[mid],find,low,high,mid);
		int comp = strcmp(find,keyword_arr[mid]);
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


// getword returns the length of the word.
// Word can begin with an underscore.
int getword(char *word,int lim,FILE *fp){
	
	int c;
	char *w = word;

	while(isspace(c = getch(fp)));
	if(c==EOF)
		return -1;
	
	// Word begin with alpha or _
	if(isalpha(c) || c=='_')
		*w++=c;
	//Remove <*>
	if(c=='<'){
		while(c!='>')
			c = getch(fp);
	}

	//Remove comments
	if(c=='/'){
		c = getch(fp);
		if(c=='/'){
			while(c!='\n' && c!=EOF)
				c = getch(fp); // skip till end of line.
		}
		else if(c=='*'){
			while(1){
				c = getch(fp); 
				if(c == '*'){
					c = getch(fp);
					if(c=='/' || c==EOF)
						break; // break on abrupt end of file.
				}
				if(c == EOF)
					break; // break on abrupt end of file.
			}
		}
	}

	//Remove string constants
	if(c=='"'){
		do{
			c = getch(fp);
		}while(c!='"' && c!=EOF);
	}

	if(!isalpha(c) && c!='_'){
		*w = '\0';
		return w-word;
	}
	for(; --lim>0; w++){
		*w = getch(fp);

		if(!isalnum(*w) && *w!='_'){
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return w-word;
}



// For using binary search
void sort_keyword_arr(){
	int i=0;
	char *t;
	for(i=0;i<keyword_count-1;i++){
		if(strcmp(keyword_arr[i],keyword_arr[i+1])>0){
			t = keyword_arr[i];
			keyword_arr[i] = keyword_arr[i+1];
			keyword_arr[i+1] = t;
			i = -1;
		}
	}
}

variable *create_node(char *w){

	variable *a = (variable *) malloc(sizeof(variable));
	strcpy(a->word,w);
	a->count = 1; // Found one already.
	a->left = NULL;
	a->right= NULL;
	return a;
}

void traverse_tree(variable *root){

	if(root!=NULL){
		traverse_tree(root->left);
		printf("%s - Count: %d \n",root->word,root->count);
		traverse_tree(root->right);
	}
}

int main(int argc,char *argv[]){

	char line[MAXLEN];
	FILE *fp = fopen("t2.txt","r");
	if(fp!=NULL){

		if(argc>1){
			cmp_index_limit = atoi(argv[1]);
		}
		// Calculate no of keywords
		int i=0;
		while(keyword_arr[i++][0]!='\0')
			keyword_count++;
		// Sort keywords for binary search
		
		sort_keyword_arr();

		// Sort list
		/*for(i=0;i<keyword_count;i++)
			puts(keyword_arr[i]); */


		puts("Results: ");
		while(getword(line,MAXLEN,fp)!=-1){
			if(line[0]!='\0' && bin_search_keyword_arr(line)==-1){	
				// line should not be null and must not be a keyword.
				//puts(line);
				variable *node = create_node(line);
				//puts(node->word);
				add_to_group(node);
			}
		}
		fclose(fp);

		for(i=0;i<group_count;i++){
			printf("Group - %d \n",i+1);
			traverse_tree(&groups[i]);
			putchar('\n');
		}
	}
	return 0;
}
