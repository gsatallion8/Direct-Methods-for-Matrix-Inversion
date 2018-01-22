#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Invert(float**,float**,int);
float Cofactor(float**,int,int,int);
float Determinant(float**,int);
void SquareMatrixMultiply(float**,float**,float**,int);


main()
{
    int i,j,k,n;
    float **A,**A_inv,*b,*x,**Identity,det;

    FILE*f_in,*f_out,*f_out1;

    f_in = fopen("inputMatrix.txt","r");

    fscanf(f_in,"%d",&n);


    A=(float**)malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
    {
        A[i]=(float*)malloc(n*sizeof(float));
    }

    A_inv=(float**)malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
    {
        A_inv[i]=(float*)malloc(n*sizeof(float));
    }
	b=(float*)malloc(n*sizeof(float));
	x=(float*)malloc(n*sizeof(float));


    Identity=(float**)malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
    {
        Identity[i]=(float*)malloc(n*sizeof(float));
    }


    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            fscanf(f_in,"%f",&A[i][j]);
        }
    }
	for(i=0;i<n;i++)
    {
        fscanf(f_in,"%f",&b[i]);
    }


//    for(i=0;i<n;i++)
//    {
//        for(j=0;j<n;j++)
//        {
//            scanf("%f",&A[i][j]);
//        }
//    }


    printf("Input Successful\nThe matrix loaded is:\n");

    /*for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%f\t",A[i][j]);
        }
        printf("\n");
    }*/

    printf("Initiating Inversion\n\tInitiating Adjoint matrix Computation\n");

	clock_t start_t, end_t, total_t;
	start_t = clock();

    Invert(A,A_inv,n);

    printf("\tAdjoint matrix computation Successful\n\tComputing Determinant\n");

    det=Determinant(A,n);

    printf("\tDeterminant Computation Successful\n");
    printf("Inversion Successful\n");
	for(i=0;i<n;i++)
	{
		x[i]=0;
		for(j=0;j<n;j++)
		{
			x[i]+=A_inv[i][j]*b[j]/det;
		}
	}

	end_t = clock();
	total_t = ((double)end_t - (double)start_t) / CLOCKS_PER_SEC *1000;
	FILE*f_out_time;
	f_out_time=fopen("Coff_time.txt","a");
    fprintf(f_out_time,"%d\t%f\n",n,(double)total_t);

    f_out=fopen("MatrixInversionSolution.txt","w");
    for(i=0;i<n;i++)
    {
        fprintf(f_out,"%f\n",x[i]);
    }
    f_out1 = fopen("inverseMatrix.txt","w");

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            A_inv[i][j]=A_inv[i][j]/det;
            fprintf(f_out1,"%f\t",A_inv[i][j]);
        }
        fprintf(f_out1,"\n");
    }

    printf("Output Successful\n");

    //printf("Initiation of Matrix multiplication\n");

    //SquareMatrixMultiply(A_inv,A,Identity,n);

    //printf("The multiplication of the inverse and the matrix gave:\n");

    /*for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%f\t",Identity[i][j]);
        }
        printf("\n");
    }*/
}

void Invert(float**A,float**A_,int n)
{
    int i,j,k;

    for(i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            printf("\t\tComputing Cofactor of %d,%d\n",i,j);
            A_[j][i] = Cofactor(A,i,j,n);
        }
    }
}

float Cofactor(float**A,int i,int j,int n)
{
    float**B;
    int k,l,m;

    B=(float**)malloc((n-1)*sizeof(float*));
    for(k=0;k<n-1;k++)
    {
        B[k]=(float*)malloc((n-1)*sizeof(float));
    }

    for(k=0;k<i;k++)
    {
        for(l=0;l<j;l++)
        {
            B[k][l] = A[k][l];
        }
        for(l=j+1;l<n;l++)
        {
            B[k][l-1] = A[k][l];
        }
    }
    for(k=i+1;k<n;k++)
    {
        for(l=0;l<j;l++)
        {
            B[k-1][l] = A[k][l];
        }
        for(l=j+1;l<n;l++)
        {
            B[k-1][l-1] = A[k][l];
        }
    }

    if((i+j)%2)
    m=-1;
    else
    m=1;

    return m*Determinant(B,n-1);
}

float Determinant(float**A,int n)
{
    if(n==1)
    return A[0][0];
    else
    {
        int i,j;
        float det=0;
        for(i=0;i<n;i++)
        {
            det+=A[i][0]*Cofactor(A,i,0,n);
        }
        return det;
    }
}

void SquareMatrixMultiply(float**A,float**B,float**C,int n)
{
    int i,j,k;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            C[i][j]=0;
            for(k=0;k<n;k++)
            {
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
}
