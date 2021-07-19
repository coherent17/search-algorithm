#include <stdio.h>
#define SIZE 10

int linear_search(int *, int);

int main(){
    int array[SIZE]={1,6,5,7,9,5,4,2,8,10};
    int index;
    index=linear_search(array,5);
    printf("%d\n",index);
    return 0;
}

int linear_search(int *array, int number){
    int index=0;
    for(index=0;index<SIZE;index++){
        if(array[index]==number){
            return index;
        }
    }
    //if the element doesn't appear in the array
    return -1;
}