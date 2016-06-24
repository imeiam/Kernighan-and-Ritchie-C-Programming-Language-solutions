/*
   malloc accepts a size request without checking its plausibility.
   free believes that the block it is asked to free contains a valid size field.
   Improve these routines so they take more pains with error checking.
   */

#include<stdio.h>
#include<string.h>


#define NALLOC 1024
#define MAXALLOC 429496729

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

int main(void){
	char *p = (char *) mallocx(10);
	strcpy(p,"Hello");
	puts(p);
	printf("x");
	free(p);
	printf("End of Char");
	p = (char *)mallocx(4294967295);	
	return 0;
}
