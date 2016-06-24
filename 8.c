/*
   Write a routine bfree(p,n) that will free an arbitrary block p of n characters into
   the free list maintained by malloc and free. By using bfree, a user can add a 
   static or external array to the free list at any time.
   */

#include<stdio.h>
#include<string.h>


#define NALLOC 1024
#define MAXALLOC 429496729

#define STATIC_ARR_SIZE 1000

static char arr[STATIC_ARR_SIZE];

typedef long Align;

union header{
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};

typedef union header Header;


static Header base;
static Header *freep = NULL;



void free(void *ap){

	printf("\nCalled Free\n");	
	Header *bp, *p;
	if(ap==NULL)
		return;
	bp = (Header *)ap -1;
	if(bp==NULL)
		return;
	for( p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if( p>=p->s.ptr && ( bp > p || bp < p->s.ptr))
			break;
	if(bp + bp->s.size == p->s.ptr){
		bp->s.size+= p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if( p+ p->s.size == bp){
		p->s.size+=bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}

static Header *morecore(unsigned nu){

	printf("\nCalled morecore\n");	
	char *cp;
	Header *up;

	char *sbrk(int);

	if(nu<NALLOC)
		nu = NALLOC;
	cp = (char *)sbrk(nu*sizeof(Header));
	if( cp == (char *)-1)
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	free((void *)(up+1));
	return freep;

}

void *mallocx(unsigned nbytes){
	printf("\nCalled Malloc\n");
	if(nbytes >= (unsigned) MAXALLOC || nbytes == 0){
		puts("Error: Cannot allocate. Size limit exceed");
		return NULL;
	}
	Header *p, *prevp;
	unsigned nunits;
	Header *morecore(unsigned);

	nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
	if((prevp=freep)==NULL){
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for(p=prevp->s.ptr; ; prevp = p,p = p->s.ptr){
		if(p->s.size >= nunits){
			if(p->s.size == nunits )
				prevp->s.ptr = p->s.ptr;
			else{
				p->s.size-=nunits;
				p+=p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if(p == freep) // wrap around
			if((p = morecore(nunits))==NULL)
				return NULL;
	}
}

int bfree(char *p,unsigned n){

	// Error Checking
	if(p==NULL || n == 0)
		return -1;
	
	if(sizeof(Header)>=n){
		printf("\nError: Cannot form a block");
	}

	if(freep == NULL){
		// Create a starting point
		base.s.ptr = freep = &base;
		base.s.size=0;	
	}
	int nunits = n/sizeof(Header);
	int skipsize = n%sizeof(Header); // This is to follow strict alignment
	p+=skipsize;// Modify start
	Header *up = (Header *) p;
	up->s.size = nunits;
	// Insert Block into freelist
	up->s.ptr = freep->s.ptr;
	freep->s.ptr = up;
	return 0;
}


int main(void){
	bfree(arr,STATIC_ARR_SIZE);
	char *p = (char *) mallocx(10);
	strcpy(p,"Hello");
	puts(p);
	free(p);
	printf("Note: Though freelist is NULL initially,\nmorecore function is not called as bfree is added to freelist.\nCommenting bfree, mallocx calls morecore for more memory\n");
	return 0;
}
