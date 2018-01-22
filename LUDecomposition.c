#include <stdio.h>
#include <stdlib.h>
#include <time.h>

main()
{
    int i,j,k,n,i_max;
    float**A,**U,**L,*x,*y,*b,temp,max;

    FILE*f_in,*f_out,*f_t;

    f_in=fopen("inputMatrix.txt","r");

    fscanf(f_in,"%d",&n);

    A=(float**)malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
    {
        A[i]=(float*)malloc(n*sizeof(float));
    }

    L=(float**)malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
    {
        L[i]=(float*)malloc(n*sizeof(float));
    }

    U=(float**)malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
    {
        U[i]=(float*)malloc(n*sizeof(float));
    }

    b=(float*)malloc(n*sizeof(float));
    x=(float*)malloc(n*sizeof(float));
    y=(float*)malloc(n*sizeof(float));

    printf("Initializing Input\n");

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
    printf("Input Successfully Completed\n");
    printf("Initializing Solution of the equations\n");
    printf("\tInitializing LU Decomposition\n");
	
	clock_t start_t, end_t, total_t;
	start_t = clock();

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            L[i][j]=0;
            U[i][j]=0;
        }
    }
    for(i=0;i<n;i++)
    {
        U[i][i]=1;
    }

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(j<=i)
            {
                L[i][j]=A[i][j];
                for(k=0;k<j;k++)
                {
                    L[i][j]-=L[i][k]*U[k][j];
                }
            }
            else
            {
                U[i][j]=A[i][j];
                for(k=0;k<i;k++)
                {
                    U[i][j]-=L[i][k]*U[k][j];
                }
                U[i][j]/=L[i][i];
            }
        }
    }
    printf("\tLU Decomposition Successfull\n");

//    for(i=0;i<n;i++)
//    {
//        for(j=0;j<n;j++)
//        {
//            printf("%f\t",L[i][j]);
//        }
//        printf("\n");
//    }

    printf("\tInitializing Forward Substitution\n");
    for(i=0;i<n;i++)
    {
        y[i]=b[i];
        for(j=0;j<i;j++)
        {
            y[i]-=L[i][j]*y[j];
        }
        y[i]/=L[i][i];
    }
    printf("\tForward Substitution Successfully Completed\n");
    printf("\tInitializing Backward Substitution\n");
    for(i=n-1;i>=0;i--)
    {
        x[i]=y[i];
        for(j=n-1;j>i;j--)
        {
            x[i]-=U[i][j]*x[j];
        }
    }
    printf("\tBackward Substitution Successfully Completed\n");
    printf("Solution of the Equations Obtained Successfully\n");
	
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC *1000;
	f_t=fopen("LUD_time.txt","a");
    fprintf(f_t,"%d\t%f\n",n,(double)total_t);
	printf("Total time taken for the Computation was %f ms\n", (double)total_t  );

    f_out=fopen("LUDecompositionSolution.txt","w");
    printf("Initializing Output of the Solution\n");
    for(i=0;i<n;i++)
    {
        fprintf(f_out,"%f\n",x[i]);
    }
    printf("Output Successfully Completed\n");
}
