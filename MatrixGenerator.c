#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main( int argc, char *argv[] )
{
	int i,j,n;
	FILE *f_out;
	sscanf(argv[1], "%d", &n);
	f_out=fopen("inputMatrix.txt","w");

	fprintf(f_out,"%d\n",n);
	for(i=0;i<n;i++)
    {
		for(j=0;j<n;j++)
		{
			if (i==j)
			fprintf(f_out,"%f\t",(float)1/(i+j+2));
			else
        	fprintf(f_out,"%f\t",(float)1/(i-j));
		}
		fprintf(f_out,"\n");
    }
	float b=1;
	for(i=0;i<n;i++)
    {
		fprintf(f_out,"%f\n",b);
    }
}
