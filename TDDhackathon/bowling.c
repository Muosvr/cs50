#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    // int throws[] = {1,4,4,5,6,4,5,5,10,0,0,1,7,3,6,4,10,0,2,8,6};
    // int throws[] = {1,4,10,2,5,1,4,6};
    // int throws[] = {10,0,3,6};
    int throws[] = {10,0,10,0,4,2};
    int size = sizeof(throws)/sizeof(throws[0]);
    int sum = 0;
    int strike = 0;
    int spare = 0;
    int counter = 0;
    int frameCount = 0;
    // printf("%d\n",size);

    for(int i=0; i<size;i++){
        printf("%d\n",throws[i]);

        if(throws[i]==10){
            strike = 2;
            printf("Strike\n");
        }

        counter ++;
        frameCount += throws[i];
        if(counter%2==0){
            if(frameCount == 10 &&throws[i]!=0){
                printf("Spare\n");
                spare = 1;
            }
            // printf("%d\n",frameCount);
            frameCount = 0;
        }

        if(strike>0 && throws[i] != 0){
            sum += throws[i]+throws[i+1]+throws[i+2];
            strike --;
        }else if(spare>0){
            sum += throws[i]+throws[i+1];
            spare = 0;
        }else{
            sum += throws[i];
        }

        printf("Sum: %d\n",sum);
    }
    printf("%d\n",sum);
}