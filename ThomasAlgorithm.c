#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

main( int argc, char *argv[] )
{
    int i,j,k,n,i_max;
    float**A,*x,*y,*b,*alpha,*beta,temp,max;

    FILE*f_in,*f_out;

    //f_in=fopen("inputMatrix_.txt","r");

    //fscanf(f_in,"%d",&n);
	sscanf(argv[1], "%d", &n);

    A=(float**)malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
    {
        A[i]=(float*)malloc(n*sizeof(float));
    }
    b=(float*)malloc(n*sizeof(float));
    x=(float*)malloc(n*sizeof(float));
    y=(float*)malloc(n*sizeof(float));
    alpha=(float*)malloc(n*sizeof(float));
    beta=(float*)malloc(n*sizeof(float));
	
	for(i=1;i<n-1;i++)
	{
		for(j=0;j<n;j++)
		{
			A[i][j]=0;
		}
		A[i][i+1]=1;
		A[i][i]=-2;
		A[i][i-1]=1;
	}
	for(i=0;i<n;i++)
	{
		A[0][i]=0;
		A[n-1][i]=0;
	}
	A[0][0]=1;
	A[n-1][n-1]=1;
	
	float g,K,dx,L;
	L=1;
	dx=L/n;
	g=1;
	K=10;
	b[0]=400;
	for(i=1;i<n-1;i++)
	{
		b[i]=-g*dx*dx/K;
	}
	b[n-1]=600;

	FILE*f_t;
	float start_t, end_t, total_t;
	start_t = clock();
    beta[0]=A[0][1]/A[0][0];
    for(i=1;i<n-1;i++)
    {
        beta[i]=A[i][i+1]/(A[i][i]-A[i][i-1]*beta[i-1]);
		//printf("%f\t%f\n",beta[i],(A[i][i]-A[i][i-1]*beta[i-1]));
    }

    alpha[0]=b[0]/A[0][0];
    for(i=1;i<n;i++)
    {
        alpha[i]=(b[i]-A[i][i-1]*alpha[i-1])/(A[i][i]-A[i][i-1]*beta[i-1]);
		//printf("%f\n",alpha[i]);
    }

	f_out=fopen("ThomasSolution.txt","w");
    x[n-1]=alpha[n-1];
    for(i=n-2;i>=0;i--)
    {
        x[i]=alpha[i]-beta[i]*x[i+1];
    }
	end_t = clock();
	total_t = (end_t - start_t)/ CLOCKS_PER_SEC*1000;
	f_t=fopen("Thomas_time.txt","a");
    fprintf(f_t,"%d\t%10.9f\n",n,total_t);
	for(i=0;i<n;i++)
	{
		fprintf(f_out,"%f\n",x[i]);
	}
}
