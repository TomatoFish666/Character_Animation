#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argv , char * argc[])
{
    FILE* fp=NULL;
    int i=0,j=0,k=0;
    char tmp[100][200];

    fp = fopen(argc[1],"r");
    if(fp == NULL){
        printf("The %s is not exit!",argc[1]); 
        exit(-1);
    }

    while(fp != NULL){

        /* Read a whole character picture and print it per loop. */
        for(i=0;i<61;i++){
            fgets(tmp[i],sizeof('a')*160,fp);         
        }
    
        for(i=0;i<61;i++){
            printf("%s",tmp[i]);
        }
        
        /* clear the screen, but it's not necessary
         * printf("\033[2J");
         */
        /* reset the cursor */
        printf("\033[61A");
        printf("\033[162D");
        usleep(33150);
    } 

    fclose(fp);
    return 0;
}
