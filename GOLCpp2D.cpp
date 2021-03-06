//
// Created by ryan on 3/30/16.
//

#include "source_file.h"
/*****************************************************************************/
/**                                                                         **/
/**     AUTHOR: RYAN MCCONN                                                 **/
/**     ASSIGNMENT Game Of Life In Parallel                                            **/
/**     DATE 02/16/2016                                                     **/
/**                                                                         **/
/*****************************************************************************/

#include "iostream"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <utility>
using namespace std;
#include <omp.h>
#include <fstream>

#define CHUNKSIZE 1

int height;
int width;
double LIFEPROB = .35;
bool PRINT = false;
int demensions = 1000;
int MAX_LIVES = 100;
int NUM_THREADS;
string filename = "/home/ryan/Code/cs432_Parallel_C/GameOfLifeCppContiuous/GoL2DResults.txt";

void ClearScreen() //from http://www.cplusplus.com/forum/articles/10515/#msg49080
{
//    if (!cur_term)
//    {
//        int result;
//        setupterm( NULL, STDOUT_FILENO, &result );
//        if (result <= 0) return;
//    }
//
//    putp( tigetstr( "clear" ) );
}

void printTB(int size){
    int i;
    for (i = 0; i<size; i++){
        printf("#");
    }
}

//prints current array state
void print(bool **array){
    if (PRINT) {
        //system("clear");

        ClearScreen();
        int i, j;
        printTB(width + 1);
        for (i = 0; i < height; i++) {
            printf("#\n#");
            for (j = 0; j < width; j++) {
                if (array[i][j] == 1) {
                    printf("*");
                }
                else {
                    printf(" ");
                }
            }
        }
        printf("#\n");
        printTB(width + 2);
        printf("\n");
        sleep(1);
    }

}

bool nextBool()
{
    return (rand() <  LIFEPROB * ((double)RAND_MAX + 1.0));
}

//intiates Array with random values
void initArray(bool **array){
    double r;
    int i, j;
    srand48(1);
    for( i = 1;i<height-1; i++){
        for(j = 1; j < width -1; j++){
            r = drand48();//drand48_r(&localBuffer, &r);
            if(r < LIFEPROB){
                array[i][j] = 1;
            }
            else{
                array[i][j] = 0;}
        }
    }
}

int getAdjacentCellValue(bool **array, int row, int col){
//    if(row< 0||row >=height||
//       col < 0||col>=width) {return 0;}
    return (array[row][col]) ? 1 : 0;
}

int getNeighborhoodVallue(bool **array, int row, int col){
    int count = 0;
    count += getAdjacentCellValue(array, row + 1, col);
    count += getAdjacentCellValue(array, row + 1, col + 1);
    count += getAdjacentCellValue(array, row, col + 1);
    count += getAdjacentCellValue(array, row - 1, col + 1);
    count += getAdjacentCellValue(array, row - 1, col);
    count += getAdjacentCellValue(array, row - 1, col - 1);
    count += getAdjacentCellValue(array, row, col - 1);
    count += getAdjacentCellValue(array, row + 1, col - 1);

    return count;
}

bool nextLive(bool **old, bool **newlife){

    int i, j, count, chunk;
    chunk = CHUNKSIZE;
    int isDead = 1;
//#pragma omp parallel shared(old, newlife, chunk) private(i,j,count)
//    {
//#pragma omp parallel shared(old, newlife, chunk, isDead) private(i,j,count) num_threads(NUM_THREADS)
#pragma omp parallel for  shared(old, newlife, chunk) private(i,j,count) \
  num_threads(NUM_THREADS) reduction(*:isDead) collapse (2)


        for (i = 1; i < height - 1; i++) {
            for ( int j = 1; j < width - 1; j++) {
                count = getNeighborhoodVallue(old, i, j);

                if (old[i][j]) {
                    newlife[i][j] = (count == 2 || count == 3) ? true : false;
                    isDead = isDead * ((newlife[i][j]) ? 1 : 0);
                }
                else {
                    newlife[i][j] = (count == 3);
                    isDead = isDead * ((newlife[i][j]) ? 0 : 1);
                }

            }
        }
    return isDead == 0;//if isDead is zero then at least one cell has changed.
    }

bool** create2DArray(int r, int c){
    int i;
    bool **array = (bool **)malloc(r * sizeof(bool *));// bool * is different size then bool
    for (i = 0; i< r; i++)
        array[i] = (bool *)malloc(c * sizeof(bool));

    return array;
}

bool** create2DArrayB(int r, int c){
    int i;
    bool **array = (bool **)malloc(r * sizeof(bool *));
    array[0]= (bool*)malloc(r * c * sizeof(bool));//%P print pointer address

    for(i = 0; i < r; i++)
        array[i] = (*array + c * i);

    return array;
}

bool** create2DArrayC(int r, int c){
    int i;
    bool *temp;
    bool **array = (bool **)malloc(r * sizeof(bool *));
    array[0]= (bool*)malloc(r * c * sizeof(bool));

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

pair<double, int> testRun(){
    height = demensions;
    width = demensions;

    struct timeval tvBegin, tvEnd, tvDiff;
    double time_used;

    bool **arrayA = create2DArrayB(height, width);        //[height][width];
    bool **arrayB = create2DArrayB(height, width);        //[height][width];
    int count = 0;

    initArray(arrayA);
    print(arrayA);
    bool alive = true;

    gettimeofday(&tvBegin, NULL);
    do{
        nextLive(arrayA,arrayB);
        print(arrayB);

        alive = nextLive(arrayB,arrayA);
        print(arrayA);
        count++;
    }
    while(alive && count < MAX_LIVES );

    gettimeofday(&tvEnd, NULL);

    timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
    time_used = (double)(((tvEnd.tv_sec*1000000 + tvEnd.tv_usec) - (tvBegin.tv_sec*1000000 + tvBegin.tv_usec))/1000000.0);
    pair<double, int> result(time_used, count);
    return result;
}

int touchFile(const char* filename){
    if (FILE *file = fopen(filename, "r")) {
        fclose(file);

    } else {
        std::ofstream outfile;
        outfile.open(filename, std::ios_base::app);
        outfile << "Testing...\n******************************************\n";
        outfile << "Name,\tTestRun,\tThread #,\tDemensions,\t AverageTime,\n";
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
        string temp(argv[4]);
        filename = temp;
    }

    pair<double, int> result = testRun();
    for(int i = 0; i < test; i++){
        result = testRun();
        if (result.second == MAX_LIVES){
            ++actualTest;
            totalTime += result.first;
        } else{
            std::cout << "Early Death\n";
        }
    }

    double ave_time_used = totalTime/(actualTest * MAX_LIVES);



    std::cout<<"\n******************************************\n";
    printf("%d * %d Game of Life 2D For %d threads\n", demensions, demensions, NUM_THREADS);
    printf("Parrallel Run Time for %d test of %d lives", actualTest,MAX_LIVES);
    printf("\nAverage Run Time per life for %d lives: %f\n",MAX_LIVES, (ave_time_used));
    std::cout<<"\n******************************************\n";

    touchFile(filename.c_str());

    FILE * pFile;
    pFile = fopen (filename.c_str(),"a");
    fprintf(pFile,"GoL2D,\t%d,\t%d,\t%d,\t%f, \n",actualTest ,NUM_THREADS ,demensions, (ave_time_used));
    fclose (pFile);

    return 0;
}


//
//height = demensions;
//width = demensions;
//
//std::cout << "please enter desired nuber of Threads : ";
//std::cin >> NUM_THREADS;
//
//struct timeval tvBegin, tvEnd, tvDiff;
//double time_used;
//
//
//bool **arrayA = create2DArrayB(height, width);        //[height][width];
//bool **arrayB = create2DArrayB(height, width);        //[height][width];
//int count = 0;
//
//
//initArray(arrayA);
//print(arrayA);
//bool alive = true;
//
//gettimeofday(&tvBegin, NULL);
//do{
//nextLive(arrayA,arrayB);
//print(arrayB);
//
//alive = nextLive(arrayB,arrayA);
//print(arrayA);
//count++;
//}
//while(alive && count < MAX_LIVES );
//
//gettimeofday(&tvEnd, NULL);
//time_used = (tvEnd.tv_sec - tvBegin.tv_sec);
//
//timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
//std::cout<<"\n******************************************\n";
//
//time_used = (double)(((tvEnd.tv_sec*1000000 + tvEnd.tv_usec) - (tvBegin.tv_sec*1000000 + tvBegin.tv_usec))/1000000.0);
//printf("%d * %d Game of Life 2D For %d threads\n", demensions, demensions, NUM_THREADS);
//printf("Parrallel Run Time for %d lives: %f",count, time_used);
//printf("\nAverage Run Time per life for %d lives: %f",count, (time_used/count));
//
//return 0;