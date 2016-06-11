/*
   Write a function expand(s1,s2) that expands shorthand notation like a-z in the string s1 in to equivalent complete list abc..xyz
   */

#include<stdio.h>
#include<ctype.h>
#include<string.h>

void expand(char s1[],char s2[]){

	int i,j;
	char c,t;
	for(i=0,j=0;s1[i]!='\0';i++){	
		c = s1[i];
		switch(c){
		
			case '-':
				if(i==0)
					s2[j++]=c; // No previous character.
				else{
					t = s1[i-1];
					if(!isalnum(t))
						s2[j++]=c; // Not a alphabet or digit then just print.
					else if( s1[i+1] == '\0')
						s2[j++]=c; // trailing '-'
					else if( t > s1[i+1] ){
						s2[j++]=c; // avoid ex: c-a pattern cannot expand
					}
					else if( t == s1[i+1] )
						i++; // a-a becomes a
					else if( isalpha(t) ){

						if(islower(t) && islower(s1[i+1]) || isupper(t) && isupper(s1[i+1])){
							i++;
							while(t++!=s1[i])
								s2[j++] = t;
						}
						else
							s2[j++] = c;
						
					}
					else {
						// Number
						 // Next number as the previous number has been added already
						i++;
						while(t++!=s1[i])
							s2[j++] = t;
					}
				}
				break;

			default:
				s2[j++] = c;
		}
	}
	s2[j] = '\0';
	puts("Final String: ");
	puts(s2);

}

int main(void){
	char s1[100],s2[100];
	puts("\nEnter the String: ");
	fgets(s1,100,stdin);
	s1[strlen(s1)-1] = '\0'; // avoid \n from fgets
	expand(s1,s2);
	return 0;
}
