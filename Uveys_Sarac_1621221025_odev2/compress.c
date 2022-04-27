#include <stdio.h>
#include <stdlib.h>
#include "compress.h"

extern int row;
extern int col;
extern int count;
void compress_IJ(int **A, int *nz, int *rows, int *cols){
	int i, j, tmp=0;
	
	for (i = 0; i < row; i++) {					// -----> Dizilere sayýlar yerleþtirildi
        for (j = 0; j < col; j++){				// -----> nz=(10,-2,3,9,3,7,8,7,3,8,7,5,8,9,9,13,4,2,-1)
	        if(*(*(A+i)+j) != 0){				// -----> cols=(0,4,0,1,5,1,2,3,0,2,3,4,1,3,4,5,1,4,5)	
	      	*(nz+tmp)=A[i][j];					// -----> rows=(0,0,1,1,1,2,2,2,3,3,3,3,4,4,4,4,5,5,5)	
			*(rows+tmp)=i;            	     	//
	      	*(cols+tmp)=j;                  	//
	      	tmp++;                           	//
		    }
        }	
    }
}

int **decompress_IJ(int *nz, int *rows, int *cols){
	
	int **B, i,j;
	
	B = (int **) malloc(sizeof(int *) * row);	//----> Double pointer ile return edeceðimiz matrisi oluþturma
	for(i=0; i<row; i++){						// 
		B[i] = (int *)malloc(sizeof(int) * col);//
	} 
	for(i=0; i< row; i++){						// ----> Matrisin tün elemanlarýný sýfýrlama
		for(j=0; j< col; j++){					//
			*(*(B+i)+j)= 0;						//
		}										//
	}
	for(i=0; i<count; i++){						// ----> Matrisin elemanlarýný nz, rows ve cols dizilerindeki bilgiler ile doldýrma 
		B[*(rows+i)][*(cols+i)]=*(nz+i);
		
	}
	return B;
	
}

void compress_CRS(int **A, int *nz, int *col_ind, int *row_ptr){
	int i, j, tmp=0;
	
    for (i = 0; i < row; i++) {					// -----> Dizilere sayýlar yerleþtirildi
        for (j = 0; j < col; j++){				// -----> nz=(10,-2,3,9,3,7,8,7,3,8,7,5,8,9,9,13,4,2,-1)
	        if(*(*(A+i)+j) != 0){				// -----> col_ind=(0,4,0,1,5,1,2,3,0,2,3,4,1,3,4,5,1,4,5)	
	      	*(nz+tmp)=A[i][j];					//	    
	      	*(col_ind+tmp)=j;					//
	      	tmp++;
		    }
        }	
    }
    	tmp=0;											    
    for (i = 0; i < row; i++) {					// -----> row_ptr dizisine sayýlar yerleþtirildi
        *(row_ptr+i)=tmp;						//	-----> row_ptr=(0,2,5,8,12,16,19)
        for (j = 0; j < col; j++){				//		  
	        if(A[i][j] != 0){					//	
	        tmp++;								//
	       	}									//
	    }										//
	}
	*(row_ptr+row)=*(nz+count-1);				//--------> row_ptr'nin son elemanýný ekledik
		
      	
}

int **decompress_CRS(int *nz, int *col_ind, int *row_ptr){
	
	int **B, i,j;

	B = (int **) malloc(sizeof(int *) * row);	//----> Double pointer matris oluþturma
	for(i=0; i<row; i++){						// 
	B[i] = (int *)malloc(sizeof(int) * col); 	//
	} 
	for(i=0; i< row; i++){						//  -----> Matrisin tüm elemanlarýný sýfýrlama
		for(j=0; j< col; j++){					//
			*(*(B+i)+j)= 0;						//
		}										//
	}
	int tmp=0;									// ----> Matrisin elemanlarýný nz, col_ind ve row_ptr dizilerindeki bilgiler ile doldýrma 
	for(i=0; i<count; i++){						//
	B[tmp][*(col_ind+i)]=*(nz+i);				//
		if(i==row_ptr[tmp+1]-1){				//
		tmp++;									//
		}										//
	}
	
	
	return B;
}

void compress_CCS(int **A, int *nz, int *row_ind, int *col_ptr){
	int i, j, tmp=0;
	 	
    for (i = 0; i < row; i++) {					// -------> Dizilere sayýlar yerleþtirildi
        for (j = 0; j < col; j++){				//          nz=(10,3,3,9,7,8,4,8,8,7,7,9,-2,5,9,2,3,13,-1)
	        if(*(*(A+j)+i) != 0){				//		   row_ind=(0,1,3,1,2,4,5,2,3,2,3,4,0,3,4,5,1,4,5)	
	      	*(nz+tmp)=*(*(A+j)+i);				//	    
	      	*(row_ind+tmp)=j;					//
	      	tmp++;
		    }
        }	
    }
    	tmp=0;									//
        for (i = 0; i < row; i++) {				// -----> Dizilere sayýlar yerleþtirildi
        	*(col_ptr+i)=tmp;					// -----> col_ptr=(0,3,7,9,12,16,-1)
        	for (j = 0; j < col; j++){			//		  
	        	if(A[j][i] != 0){				//
	        	tmp++;
	       		}
	        }	
		}
		*(col_ptr+col)=*(nz+count-1);			// -----> col_ptr'nin son elemanýný ekledik
	
}

int **decompress_CCS(int *nz, int *row_ind, int *col_ptr){
	
	int **B, i,j;
	
	B = (int **) malloc(sizeof(int *) * row);	// ----> Double pointer matrix oluþturma
	for(i=0; i<row; i++){						// 
		B[i] = (int *)malloc(sizeof(int) * col);//
	} 
	for(i=0; i< row; i++){						// -----> Matrisin tüm elemanlarýný sýfýrlama
		for(j=0; j< col; j++){					//
			*(*(B+i)+j)= 0;						//
		}										//
	}
	int tmp=0;									// ---->Matrisin elemanlarýný nz, row_ind ve col_ptr dizilerindeki bilgiler ile doldýrma           
		for(i=0; i<count; i++){					//
		B[*(row_ind+i)][tmp]=nz[i];				//
			if(i==col_ptr[tmp+1]-1){			//
			tmp++;								//
			}									//
	}
	
	
	return B;
	
}

