#include<stdio.h>
#include<string.h>


#define NALLOC 1024

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
	bp = (Header *)ap -1;
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

void *callocx(int n,unsigned nbytes){
	printf("\nCalled Calloc\n");	
	Header *p, *prevp;
	unsigned nunits;
	Header *morecore(unsigned);

	nunits = (n*nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
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
			memset(p+1,0,(p->s.size-1)*sizeof(Header));	// Different from mallocx
			return (void *)(p+1);
		}
		if(p == freep) // wrap around
			if((p = morecore(nunits))==NULL)
				return NULL;
	}
}

int main(void){
	char *p = (char *) mallocx(100);
	strcpy(p,"Hello");
	puts(p);
	printf("x");
	free(p);
	printf("End of Char");
	int *x = (int *) mallocx(10*sizeof(int));
	if(x==NULL)
		printf("NUll\n");
	else{
		x[5] = 100;
		printf("%d\n",x[5]);
		free(x);
	}
	x = (int *) callocx(10,sizeof(int));
	if(x==NULL)
		printf("NUll\n");
	else{
		int i=0;
		printf("\nArray using Calloc: \n");
		for(;i<10;i++)
			printf("x[%d] = %d\n",i,x[i]);
		free(x);
	}
	return 0;
}
