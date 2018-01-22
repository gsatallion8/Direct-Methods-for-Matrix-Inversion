#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float absolute(float);

main()
{
    int i,j,k,n,i_max;
    float**A,*x,*b,temp,max;

    FILE*f_in,*f_out,*f_t;

    f_in=fopen("inputMatrix.txt","r");

    fscanf(f_in,"%d",&n);

    A=(float**)malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
    {
        A[i]=(float*)malloc(n*sizeof(float));
    }
    b=(float*)malloc(n*sizeof(float));
    x=(float*)malloc(n*sizeof(float));
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
    printf("Initializing Guassian Elemination\n");

	clock_t start_t, end_t, total_t;
	start_t = clock();

    for(i=0;i<n;i++)
    {
        max=absolute(A[i][i]);
        i_max=i;
        for(j=i+1;j<n;j++)
        {
            if(absolute(A[j][i])>max)
            {
                max=absolute(A[j][i]);
                i_max=j;
            }
        }
        printf("\tPartial Pivoting for Row %d\n",i);
        for(j=0;j<n;j++)
        {
            temp=A[i][j];
            A[i][j]=A[i_max][j];
            A[i_max][j]=temp;
        }
        temp=b[i];
        b[i]=b[i_max];
        b[i_max]=temp;

        printf("\tClearing the lower triangle at Row %d\n",i);
        for(j=0;j<i;j++)
        {
            for(k=j+1;k<n;k++)
            {
                A[i][k]-=A[i][j]*A[j][k];
            }
            b[i]-=A[i][j]*b[j];
            A[i][j]=0;
        }

        printf("\tNormalizing with respect to diagonal element at Row %d\n",i);
        for(j=i+1;j<n;j++)
        {
            A[i][j]/=A[i][i];
        }
        b[i]/=A[i][i];
        A[i][i]=1;
    }

    /*for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%f\t",A[i][j]);
        }
        printf("\n");
    }*/
    printf("\tInitializing Backward Substitution\n");
    for(i=n-1;i>=0;i--)
    {
        printf("\t\tComputing the element %d\n",i);
        x[i]=b[i];
        for(j=n-1;j>i;j--)
        {
            x[i]-=A[i][j]*x[j];
        }
    }
    printf("\tBackward Substiitution Successfully Completed\n");
    printf("Computation of the variables Successfully Completed\n");

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC *1000;
	f_t=fopen("Gauss_time.txt","a");
    fprintf(f_t,"%d\t%f\n",n,(double)total_t);
    printf("Total time taken for the Computation was %f ms\n", (double)total_t  );

    printf("Initializing Output of the Solution\n");
    f_out=fopen("GaussEliminationSolution.txt","w");
    for(i=0;i<n;i++)
    {
        fprintf(f_out,"%f\n",x[i]);
    }
    printf("Output of the Solution Successfully Completed\n");

}

float absolute(float x)
{
    if(x<0)
    return -x;
    else
    return x;
}
