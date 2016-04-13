//
// Created by ryan on 3/30/16.
//

#include "GOFCpp.h"
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

#define CHUNKSIZE 1

int height;
int width;
double LIFEPROB = .35;
bool PRINT = true;
int demensions = 15;
int MAX_LIVES = 10;


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

bool equ(bool **old, bool **newlife){
    int i, j;//count?
    bool result = true;
    for( i = 0;i<height; i++){
        for(j = 0; j < width; j++){

            if(old[i][j] != newlife[i][j]){
                result = false;
            }

        }
    }
    return result;
}

int live(bool **old, bool **newlife){

    bool livesEquals;
    int i, j, count, lifeCount, chunk;
    chunk = CHUNKSIZE;
#pragma omp parallel shared(old, newlife, lifeCount, chunk, livesEquals) private(i,j, count)
    {
        do{
#pragma omp for schedule(guided,chunk)
            for (i = 1; i < height - 1; i++) {
                for ( int j = 1; j < width - 1; j++) {
                    count = getNeighborhoodVallue(old, i, j);

                    if (old[i][j]) {
                        newlife[i][j] = (count == 2 || count == 3) ? true : false;
                    }
                    else {
                        newlife[i][j] = (count == 3);
                    }

                }
            }
#pragma omp barrier
#pragma omp master
            {
                print(old);
                lifeCount++;
            }

#pragma omp for schedule(guided,chunk)
            for (i = 1; i < height - 1; i++) {
                for ( int j = 1; j < width - 1; j++) {
                    count = getNeighborhoodVallue(newlife, i, j);

                    if (newlife[i][j]) {
                        old[i][j] = (count == 2 || count == 3) ? true : false;
                    }
                    else {
                        old[i][j] = (count == 3);
                    }

                }
            }
#pragma omp barrier
#pragma omp master
            {
                print(old);
                lifeCount++;
                livesEquals = equ(old, newlife);
            }
#pragma omp barrier
        }
        while(!livesEquals && lifeCount < MAX_LIVES );

    }
    return lifeCount;
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


int main(int argc, char *argv[]){
    height = demensions;
    width = demensions;

    struct timeval tvBegin, tvEnd, tvDiff;
    double time_used;



    bool **arrayA = create2DArrayB(height, width);        //[height][width];
    bool **arrayB = create2DArrayB(height, width);        //[height][width];
    int count = 0;


    initArray(arrayA);
    print(arrayA);

    gettimeofday(&tvBegin, NULL);

    count = live(arrayA,arrayB);

    gettimeofday(&tvEnd, NULL);
    time_used = (tvEnd.tv_sec - tvBegin.tv_sec);

    timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
    printf("Parallel Sections Game of Life\n");

    time_used = (double)(((tvEnd.tv_sec*1000000 + tvEnd.tv_usec) - (tvBegin.tv_sec*1000000 + tvBegin.tv_usec))/1000000.0);
    printf("%f lives: %f\n",(double) tvEnd.tv_sec, (double) tvBegin.tv_sec);
    printf("Parrallel Run Time for %d lives: %f",count, time_used);
    printf("\nAverage Run Time per life for %d lives: %f",count, (time_used/count));

    return 0;
}