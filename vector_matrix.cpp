//
// Created by ryan on 4/20/16.
//
/*****************************************************************************/
/**                                                                         **/
/**     AUTHOR: RYAN MCCONN                                                 **/
/**     ASSIGNMENT Game Of Life In Parallel                                            **/
/**     DATE 02/16/2016                                                     **/
/**                                                                         **/
/*****************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <utility>
#include <fstream>
#include <omp.h>

using namespace std;

#define CHUNKSIZE 1

int height;
int width;
double LIFEPROB = .35;
bool PRINT = false;
int demensions = 1000;
int NUM_THREADS;
string filename = "/home/ryan/Code/cs432_Parallel_C/GameOfLifeCppContiuous/vectorMatrixResults.txt";

void printTB(int size){
    int i;
    for (i = 0; i<size; i++){
        printf("#");
    }
}

//prints current array state
void print(double **array){
    if (PRINT) {
        //system("clear");


        int i, j;
        printTB(width + 1);
        for (i = 0; i < height; i++) {
            printf("#\n#");
            for (j = 0; j < width; j++) {

                    printf( " %f.2 ", array[i][j] );

            }
        }
        printf("#\n");
        printTB(width + 2);
        printf("\n");
        sleep(1);
    }

}

//intiates Array with random values
void initArray(double **array){
    int i, j;
    srand48(1);
    for( i = 1;i<height-1; i++){
        for(j = 1; j < width -1; j++){
            array[i][j]  = drand48()*100.0;
        }
    }
}

void initVector(double *array){
    int i;
    srand48(1);
    for( i = 1;i<height-1; i++){
            array[i]  = drand48()*100.0;

    }
}

int** create2DArray(int r, int c){
    int i;
    int **array = (int **)malloc(r * sizeof(int *));// int * is different size then int
    for (i = 0; i< r; i++)
        array[i] = (int *)malloc(c * sizeof(int));

    return array;
}

double** create2DArrayB(int r, int c){
    int i;
    double **array = (double **)malloc(r * sizeof(double *));
    array[0]= (double*)malloc(r * c * sizeof(double));//%P print pointer address

    for(i = 0; i < r; i++)
        array[i] = (*array + c * i);

    return array;
}

double* create1DArrayB(int r){
    int i;
    double *array = (double *)malloc(r * sizeof(double));
    return array;
}

double** create2DArrayC(int r, int c){
    int i;
    double *temp;
    double **array = (double **)malloc(r * sizeof(double *));
    array[0]= (double*)malloc(r * c * sizeof(double));

    for(i = 0; i < r; i++)
        array[i] = (*array + c * i);

    return array;
}

/* Return 1 if the difference is negative, otherwise 0.  */
int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff<0);
}


double vectors_dot_prod(double *x, double *y, int n)
{
    double res = 0.0;
    int i;
    for (i = 0; i < n; i++)
    {
        res += x[i] * y[i];
    }
    return res;
}

void matrix_vector_mult(double **mat, double *vec, double *result, int rows, int cols) {

    int chunk, i;
    chunk = CHUNKSIZE;
#pragma omp parallel for  shared(mat, vec, result, chunk, rows, cols) private(i) \
  num_threads(NUM_THREADS) schedule(guided,chunk)
    // in matrix form: result = mat * vec;;
        for (i = 0; i < rows; i++) {
            result[i] = vectors_dot_prod(mat[i], vec, cols);
        }

}


double testRun(){
    height = demensions;
    width = demensions;

    struct timeval tvBegin, tvEnd, tvDiff;
    double time_used;

    double **arrayA = create2DArrayB(height, width);        //[height][width];
    double *vector = create1DArrayB(height);        //[height];
    double *vectorResult = create1DArrayB(height);
    int count = 0;


    initArray(arrayA);
    initVector(vector);
    print(arrayA);

    gettimeofday(&tvBegin, NULL);
        matrix_vector_mult(arrayA, vector, vectorResult,height,width);
    gettimeofday(&tvEnd, NULL);

    timeval_subtract(&tvDiff, &tvEnd, &tvBegin);

    time_used = (double)(((tvEnd.tv_sec*1000000 + tvEnd.tv_usec) - (tvBegin.tv_sec*1000000 + tvBegin.tv_usec))/1000000.0);

    double result = time_used;
    return result;
}

int touchFile(const char* filename){
    if (FILE *file = fopen(filename, "r")) {
        fclose(file);

    } else {
        cout<<"creating OutPutFile" <<endl;
        std::ofstream outfile;
        outfile.open(filename, std::ios_base::app);
        outfile << "Testing...\n******************************************\n";
        outfile << "Name,\tTestRuns,\tThread #,\tDemensions,\t AverageTime,\n";
        outfile.close();
    }
}


int main(int argc, char *argv[]){

    int test, actualTest = 0;
    int temp_demensions;
    double totalTime;
    if (argc >= 3)
    {
        NUM_THREADS = atoi(argv[1]);
        test = atoi(argv[2]);
        temp_demensions = atoi(argv[3]);
    }else {

        std::cout << "please enter desired nuber of Threads : ";
        std::cin >> NUM_THREADS;
        std::cout << "please enter desired nuber of Test : ";
        std::cin >> test;
        std::cout << "please enter desired size or 0: ";
        std::cin >> temp_demensions;
    }
    if(temp_demensions != 0){
        demensions = temp_demensions;
    }
    if (argc > 4){
        std::string temp(argv[4]);
        filename = temp;
    }

    double result = testRun();
    cout<<result<<endl;
    for(int i = 0; i < test; i++){
        result = testRun();
            ++actualTest;
            totalTime += result;
        cout<<"test"<<endl;

    }

    double ave_time_used = totalTime/(actualTest);



    touchFile(filename.c_str());

    std::cout<<"\n******************************************\n";
    printf("%d * %d Matrix * Vector for %d threads\n", demensions, demensions, NUM_THREADS);
    printf("Parrallel Run Time for %d test", actualTest);
    printf("\nAverage Run Time per operation: %f\n", (ave_time_used));
    std::cout<<"\n******************************************\n";
//////////////////////////////////////////////////////////////////////////////////////////


    FILE * pFile;
    pFile = fopen (filename.c_str(),"a");
    fprintf(pFile,"Vector1D,\t%d,\t%d,\t%d,\t%f, \n",actualTest ,NUM_THREADS ,demensions, (ave_time_used));
    fclose (pFile);

    return 0;

}

