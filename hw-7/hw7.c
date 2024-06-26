/*  Starter MPI/C code pi approximation */
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
 double f(double);

double f(double a)
{
    return (4.0 / (1.0 + a*a));
}

int main(int argc,char *argv[])
{
    int done = 0, myid, numprocs;
    uint64_t i;
    uint64_t n;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;
    double startwtime = 0.0, endwtime;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    FILE *fp = fopen("results.txt", "w");

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);

    fprintf(stdout,"Process %d of %d on %s\n",
	    myid, numprocs, processor_name);
    int runs = 0;
    while (!done) {
        if (myid == 0) {
	        startwtime = MPI_Wtime();
        }
        MPI_Bcast(&runs, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (runs == 10)
            done = 1;
        else {
            n = 10;
            for (uint64_t i = 0; i < runs; i++) {
                n *= 10;
            }
            h   = 1.0 / (double) n;
            sum = 0.0;
	    /* A slightly better approach starts from large i and works back */
            for (i = myid + 1; i <= n; i += numprocs)
            {
                x = h * ((double)i - 0.5);
                sum += f(x);
            }
            mypi = h * sum;

            MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

            if (myid == 0) {
                printf("with %"PRIu64" intervals\npi is approximately %.16f, Error is %.16f\n",
                       n, pi, fabs(pi - PI25DT));
		        endwtime = MPI_Wtime();
		        printf("wall clock time = %f\n", endwtime-startwtime);
                fprintf(fp, "%"PRIu64"\t%.16f\t%.16f\t%.8f\n", n, pi, fabs(pi - PI25DT), endwtime-startwtime);
		        fflush( stdout );
                runs++;
	        }
        }
    }
    fclose(fp);
    MPI_Finalize();
    return 0;
}
