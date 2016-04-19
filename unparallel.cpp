//
// Created by ryan on 3/30/16.
//

#include "unparallel.h"
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
using namespace std;

#define CHUNKSIZE 5

int height;
int width;
double LIFEPROB = .35;
bool PRINT = false;
int demensions = 1000;
int MAX_LIVES = 100;


void ClearScreen() //from http://www.cplusplus.com/forum/articles/10515/#msg49080
{

    printf("\n\n");
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
            r = drand48();
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

void nextLive(bool **old, bool **newlife){

    int i, j, count;

    for (i = 1; i < height - 1; i++) {
        for ( j = 1; j < width - 1; j++) {
            count = getNeighborhoodVallue(old, i, j);

            if (old[i][j]) {
                newlife[i][j] = (count == 2 || count == 3) ? true : false;
            }
            else {
                newlife[i][j] = (count == 3);
            }

        }
    }
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

pair<double, int> testRun(int fdemensions){
    height = fdemensions;
    width = fdemensions;

    struct timeval tvBegin, tvEnd, tvDiff;
    double time_used;



    bool **arrayA = create2DArrayB(height, width);        //[height][width];
    bool **arrayB = create2DArrayB(height, width);        //[height][width];
    int count = 0;


    initArray(arrayA);
    print(arrayA);

    gettimeofday(&tvBegin, NULL);

    do {
        nextLive(arrayA, arrayB);
        print(arrayB);

        count++;

        nextLive(arrayB, arrayA);
        print(arrayA);
        count++;
    }
    while (!equ(arrayA, arrayB) && count < MAX_LIVES);

    gettimeofday(&tvEnd, NULL);

    timeval_subtract(&tvDiff, &tvEnd, &tvBegin);

    time_used = (double) (((tvEnd.tv_sec * 1000000 + tvEnd.tv_usec) - (tvBegin.tv_sec * 1000000 + tvBegin.tv_usec)) /
                          1000000.0);

    pair<double, int> result(time_used, count);
    return result;
}


int main(int argc, char *argv[]) {
    int test, actualTest = 0;
    double totalTime;
    std::cout << "please enter desired number of Test : ";
    std::cin >> test;
    int temp_demensions;
    std::cout << "please enter desired size or 0: ";
    std::cin >> temp_demensions;
    if(temp_demensions != 0){
        demensions = temp_demensions;
    }

    pair<double, int> result = testRun(demensions);
    cout<< (result.first/result.second);
    for(int i = 0; i < test; i++){
        result = testRun(demensions);
        if (result.second == MAX_LIVES){
            ++actualTest;
            totalTime += result.first;
        } else{
            std::cout << "Early Death\n";
        }
    }

    double ave_time_used = totalTime/(actualTest * MAX_LIVES);
    std::cout<<"\n******************************************\n";

    printf("UNParallel %d * %d Game of Life\n", demensions, demensions);
    printf("Run Time for %d test of %d lives", actualTest,MAX_LIVES);
    printf("\nAverage Run Time per life for %d lives: %f",MAX_LIVES, (ave_time_used));

    return 0;
}

