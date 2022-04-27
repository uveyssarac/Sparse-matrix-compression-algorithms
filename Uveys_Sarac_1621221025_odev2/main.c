#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "compress.h"
#define M 6
#define N 6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int row=M;
int col=N;
int count;
void printArray(int m, int *array);
int main(int argc, char *argv[]) {
	
	int **A, *nz, *col_ind, *row_ptr, *row_ind, *col_ptr, *rows, *cols;
	int i,j, random1, random2;
	srand(time(NULL));
	
	A = (int **) malloc(sizeof(int *) * M);			// ----> Double pointer matris olu�turma
	for(i=0; i<M; i++){								// 
		A[i] = (int *)malloc(sizeof(int) * N);		//
	}												//
	
	for(i=0; i< M; i++){							// -----> Matrise rastgele eleman atama
		for(j=0; j< N; j++){						//
			random1=rand()%11;						//
			*(*(A+i)+j)= random1;					//
		}											//
	}
	for(i=0; i< M*N/2; i++){						// -----> Matrisin elemanlar�n�n �o�unu s�f�r yapma
		random1=rand()%M;							//
		random2=rand()%N;							//
		*(*(A+random1)+random2)=0;					//
	}
	for (i = 0; i < M; i++) {						// -----> Ka� adet s�f�rdan farkl� say� oldu�u bulundu
        for (j = 0; j < N; j++){					//	      �rnek matris Count=19
	        if(*(*(A+i)+j) != 0){					//
	      	count++;								//
		    }
        }	
    }
    nz = (int*)malloc(count * sizeof(int));			// -----> Bulunan sayi ve malloc ile diziler olu�turuldu
    col_ind = (int*)malloc(count * sizeof(int));	//			
    row_ptr = (int*)malloc((M+1) * sizeof(int));	//
    row_ind = (int*)malloc(count * sizeof(int));	//			
    col_ptr = (int*)malloc((M+1) * sizeof(int));	//
    rows = (int*)malloc(count * sizeof(int));		//
    cols = (int*)malloc(count * sizeof(int));		//
    
    
    printf("*** ILK MATRIS****\n");					// -----> �lk random olu�turalan matrisi yazd�rma
	for (i = 0; i < M; i++) {						// 
      	for (j = 0; j < N; j++){					//
        printf("%d\t", A[i][j]);					//
        }											//
      puts("");										//
    }
    puts("");
    printf("****COMPRESS_CRS****\n");				//
    puts("");										//
	compress_CRS(A,nz,col_ind, row_ptr);			// ----> Compress_CRS i�lemi
	printf("NZ = ");								// ---->Nz'yi yazd�rma
	printArray(count, nz);							//
	printf("COL_IND = ");							// ----> col_ind'i yazd�rma
	printArray(count, col_ind);						//
	printf("ROW_PTR = ");							// ----> row_ptr'yi yazd�rma
	printArray(M+1, row_ptr);						//
	int **matris_CRS;								// ----> Decompress i�lemi �ncesi decompresslenecek matris olu�turma
	matris_CRS=decompress_CRS(nz,col_ind,row_ptr);	// ----> Decompress i�lemini matrise atama
	puts("");										//
	printf("****DECOMPRESS MATRIS_CRS****\n");
    for (i = 0; i < M; i++) {						// ----> Matris_CRS' yi yazd�rma
      	for (j = 0; j < N; j++){					//
        printf("%d\t",matris_CRS[i][j] );			//
        }											//
    puts("");  
	}
	puts("\n------------------------------------"); 
	puts("------------------------------------\n");
	printf("****COMPRESS_CCS****\n");				//
	compress_CCS(A,nz,row_ind, col_ptr);			// ----> Compress_CCS i�lemi
	printf("NZ = ");								// ----> Nz'yi yazd�rma
	printArray(count, nz);							//
	printf("ROW_IND = ");							// ----> row_ind'i yazd�rma
	printArray(count, row_ind);						//
	printf("COL_PTR = ");							// ----> col_ptr'yi yazd�rma
	printArray(M+1, col_ptr);						//
	int **matris_CCS;								// ----> Decompress i�lemi �ncesi decompresslenecek matris olu�turma
	matris_CCS=decompress_CCS(nz, row_ind, col_ptr);// ----> Decompress i�lemini matrise atama
	puts("");									  	//
	printf("****DECOMPRESS MATRIS_CCS****\n");		//
    for (i = 0; i < M; i++) {						// ----> Matris_CCS' yi yazd�rma
      	for (j = 0; j < N; j++){                    //
        printf("%d\t",matris_CCS[i][j] );			//
        }											//
    puts("");  
	}
	puts("\n------------------------------------"); 
	puts("------------------------------------\n");
	printf("****COMPRESS_IJ****\n");
	compress_IJ(A,nz,rows, cols);					// ----> Compress_IJ i�lemi
	printf("NZ = ");								// ----> Nz'yi yazd�rma 
	printArray(count, nz);							//									
	printf("ROWs = ");								// ----> Rows'u yazd�rma
	printArray(count, rows);						//										
	printf("COLS = ");								// ----> Cols'u yazd�rma
	printArray(count, cols);						//										//
	int **matris_IJ;								// ----> Decompress i�lemi �ncesi decompresslenecek matris olu�turma
	matris_IJ=decompress_IJ(nz, rows, cols);		// ----> Decompress i�lemini matrise atama
	puts("");									  	//
	printf("****DECOMPRESS MATRIS_IJ****\n");
    for (i = 0; i < M; i++) {						// ----> Matris_IJ' yi yazd�rma
      	for (j = 0; j < N; j++){                    //
        printf("%d\t",matris_IJ[i][j] );         	//
        }											//
    puts("");  
	}
	
	system("pause");


   return 0;
}
	void printArray(int m, int *array){
		int i;
		for (i = 0; i < m; i++){
      	printf("%d ", *(array+i) );
      }
   		puts("");
	}
	
	
	
	

