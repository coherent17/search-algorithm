#include <stdio.h>
#define SIZE 10

int recursive_binary_search(int *, int, int, int);

int main(){
    int array[SIZE]={1,2,3,4,5,6,7,8,9,10};
    int index;
    printf("recursive_binary_search:");
    index=recursive_binary_search(array,0,SIZE-1,3);
    printf("%d\n",index);


    return 0;
}

int recursive_binary_search(int *array, int left, int right, int number){
    if(left<=right){
        //mid point index:
        int mid=left+(right-left)/2;
        
        //check if the number is at mid
        if(array[mid]==number) return mid;

        //if number is greater than mid, search right array
        else if(number>array[mid]) return recursive_binary_search(array, mid+1, right, number);

        //if number is smaller than mid, search left side
        else return recursive_binary_search(array, left, mid-1, number);

    }
    //the element isn't in the array
    return -1;
}