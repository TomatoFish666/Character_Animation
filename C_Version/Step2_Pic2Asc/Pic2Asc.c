#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cv.h>
#include <highgui.h>

void Usage()    /* How to use this program. */
{
    printf("\nUsage: ./Pic2Asc <pictureName> <targetFileName>\n\n");
    printf("For Example:\n");
    printf("Here is the directory tree of current directory:\n");
    printf(".\n");
    printf("|\n");
    printf("|---Pic2Asc.c\n");
    printf("|\n");
    printf("|---test.jpg\n");
    printf("|\n");
    printf("|---Ascii.txt\n\n");
    printf("Then I want to transform 'test.jpg' into Ascii characters and save the result into 'Ascii.txt'.\n\n");
    printf("Run the command:\n");
    printf("./Pic2Asc test.jpg Ascii.txt\n\n");
}

char asc[]={    ' ','`','.',',',':','~','"','i','!','^','<','c','+','?','t','7',
                '{','u','3','0','p','w','4','A','8','D','X','%','#','H','M','@' };

int gray[]={    255,247,239,231,223,215,207,199,191,183,175,167,159,151,143,135,
                127,119,111,103,95,87,79,71,63,55,47,39,31,23,15,7  };

/* find the first number greater than the grayLevel of the pixel 
 * return the index of the number
 */

int SearchGray(int tar) 
{
    int left=0, right=31 , mid=0;
    while(left <= right){
        mid = (left + right)>>1;
        if(tar == gray[mid]){
            return mid;
        }else if(tar > gray[mid]){
            right = mid-1; 
        }else{
            left = mid+1; 
        }
    }
    return right;
}

int main(int argc , char * argv[])
{
    IplImage * pImg = NULL;
    FILE * fp = NULL;
    CvScalar s;         /* pixel's RGB, but saved as BRG  */
    int grayLevel = 0;  /* grayLevel = s.val[0]*/
    int i=0 , j=0;


    /* Print usage. */
    if(argc <= 1 || argc >= 4){
        Usage(); 
        exit(-1);
    }

    /* Load the picture which will be transformed. */
    pImg = cvLoadImage(argv[1],0);
    if(pImg == NULL){
        printf("The Picture is not exist! Exit\n"); 
        exit(-1);
    }

    /* The targetFile which saves result (the ASCII characters). */
    fp = fopen(argv[2],"a"); 
    if( fp == NULL ){
        printf("The file is not exist! Exit\n"); 
        exit(-1);
    }

    /* -1, default number of three channels
     * 0 , force to convert the image into grayscale
     * 1 , read the color chart
     * 
     * I have used the 0 in cvLoadImage()，
     * so the valueB = valueG = valueR = Gray  
     */
    for(i = 0 ; i < pImg->height ; ){
        for(j = 0 ; j < pImg->width ; ){
            s = cvGet2D(pImg,i,j); 
            grayLevel = s.val[0];
            /* for test:
             * fprintf(fp,"%d,",grayLevel);
             */
            fprintf(fp,"%c",asc[SearchGray(grayLevel)]);
            j += 5;
        } 
        fprintf(fp,"\n");
        i += 10;
    }
    fprintf(fp,"\n");

    fclose(fp); 
    cvReleaseImage(&pImg);
    return 0;
}
