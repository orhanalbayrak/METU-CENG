/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/* 
 * Please fill in the following student struct 
 */
team_t team = {
    "2264471",              /* Student ID */

    "Orhan ALBAYRAK",     /* full name */
    "albayrak.orhan@metu.edu.tr",  /* email address */

    "",                   /* leave blank */
    ""                    /* leave blank */
};


/***************
 * Sobel KERNEL
 ***************/

/******************************************************
 * Your different versions of the sobel functions  go here
 ******************************************************/

/* 
 * naive_sobel - The naive baseline version of Sobel 
 */
char naive_sobel_descr[] = "sobel: Naive baseline implementation";
void naive_sobel(int dim,int *src, int *dst) {
    int i,j,k,l;
    int ker[3][3] = {{-1, 0, 1}, 
                     {-2, 0, 2}, 
                     {-1, 0, 1}};  




    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++) {	
	   dst[j*dim+i]=0;

            if(!((i == 0) || (i == dim-1) || (j == 0) || (j == dim-1))){
            
            for(k = -1; k <= 1; k++)
                for(l = -1; l <= 1; l++) {
                 dst[j*dim+i]=dst[j*dim+i]+src[(j + l)*dim+(i + k)] * ker[(l+1)][(k+1)]; 
                }
                
      }
      
}
}
/* 
 * sobel - Your current working version of sobel
 * IMPORTANT: This is the version you will be graded on
 */

char sobel_descr[] = "Dot product: Current working version";
void sobel(int dim,int *src,int *dst) 
{
	int p,dimm1=dim-1,*dest=dst,*sorc=src;
	for(p=0;p<dim+1;p++)
		*(dest +p)=0;
	


	for(p=dim+1;p<dim*dimm1;p++){


				*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1) 
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);

	p++;

				*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);
	p++;
	*(dest +p)=  - *(sorc + p -dim-1)
				+ *(sorc + p -1)*(-2)
				- *(sorc + p +dim-1)
				+ *(sorc + p -dim+1)
				+ *(sorc + p +1) * 2
				+ *(sorc + p +dim+1);


				p++;
            
            	*(dest +p)=  - *(sorc + p -dim-1)
			+ *(sorc + p -1)*(-2)
			- *(sorc + p +dim-1)
			+ *(sorc + p -dim+1)
			+ *(sorc + p +1) * 2
			+ *(sorc + p +dim+1);
p++;
		    *(dest +p)=  - *(sorc + p -dim-1)
			+ *(sorc + p -1)*(-2)
			- *(sorc + p +dim-1)
			+ *(sorc + p -dim+1)
			+ *(sorc + p +1) * 2
			+ *(sorc + p +dim+1);
              
				
    }
    for (int a=0;a<dim;a++){
	
		*(dest+a*dim+dim-1) = 0;
		*(dest+a*dim) = 0; 
	}
    for(;p<dim*dim;p++)
    	*(dest +p)=0;
}





/*********************************************************************
 * register_sobel_functions - Register all of your different versions
 *     of the sobel functions  with the driver by calling the
 *     add_sobel_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_sobel_functions() {
    add_sobel_function(&naive_sobel, naive_sobel_descr);   
    add_sobel_function(&sobel, sobel_descr);   
    /* ... Register additional test functions here */
}




/***************
 * MIRROR KERNEL
 ***************/

/******************************************************
 * Your different versions of the mirror func  go here
 ******************************************************/

/* 
 * naive_mirror - The naive baseline version of mirror 
 */
char naive_mirror_descr[] = "Naive_mirror: Naive baseline implementation";
void naive_mirror(int dim,int *src,int *dst) {
    
 	 int i,j;

  for(j = 0; j < dim; j++)
        for(i = 0; i < dim; i++) {
            dst[RIDX(j,i,dim)]=src[RIDX(j,dim-1-i,dim)];

        }

}


/* 
 * mirror - Your current working version of mirror
 * IMPORTANT: This is the version you will be graded on
 */
char mirror_descr[] = "Mirror: Current working version";
void mirror(int dim,int *src,int *dst) 
{

    
 	 int i,j,k=-dim, t;

  for(j = 0; j < dim; j++){
  		k+=dim;
  		t = k+dim-1;
        for(i = 0; i < dim;) {
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;
            dst[(k+i)]=src[t-i]; i++;


        }
    }

}

/*********************************************************************
 * register_mirror_functions - Register all of your different versions
 *     of the mirror functions  with the driver by calling the
 *     add_mirror_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_mirror_functions() {
    add_mirror_function(&naive_mirror, naive_mirror_descr);   
    add_mirror_function(&mirror, mirror_descr);   
    /* ... Register additional test functions here */
}

