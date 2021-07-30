#include <stdio.h>
#define SIZE 8

int interpolation_search(int *, int);

int main(){
    int array[SIZE]={13,21,34,55,69,73,84,101};
    int index=interpolation_search(array,84);
    printf("%d\n",index);
    return 0;
}

int interpolation_search(int *array, int number){
    int left=0;
    int right=SIZE-1;

    while(number >= array[left] &&  number <= array[right] && left <= right){
        int index;
        //interpolation to find the index
        index=left+(number-array[left])/(array[right]-array[left])*(right-left);

        //when left meet right
        if(left==right){
            if(array[left]==number) return left;
            else return -1;
        }

        //if the number appear at the index
        if(number==array[index]) return index;

        //if the number is greater than array[index]
        else if(number > array[index]) left=index+1;

        //if the number is smaller than array[index]
        else right=index-1;
    }
    //the element isn't in the array
    return -1;
}