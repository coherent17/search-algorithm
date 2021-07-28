#include <stdio.h>
#define SIZE 10

int find_min(int, int);
int binary_search(int *, int , int , int);
int exponential_search(int *,int);

int main(){
    int array[SIZE]={1,2,3,4,5,6,7,8,9,10};
    int index=exponential_search(array,8);
    printf("%d\n",index);
    return 0;
}

int find_min(int a, int b){
    if(a<=b) return a;
    else return b; 
}

int exponential_search(int *array,int number){
    if(array[0]==number) return 0;

    //find the index to do the binary search
    int index=1;
    while(index<SIZE && array[index]<=number){
        index*=2;
    }

    //do the binary search at array[index/2+1]~array[min(index-1,size of array)]
    return binary_search(array, (index/2),find_min(index-1,SIZE-1),number);
}

//use recursive binary search
int binary_search(int *array, int left, int right, int number){
    if(left<=right){
        //mid point index:
        int mid=left+(right-left)/2;
        
        //check if the number is at mid
        if(array[mid]==number) return mid;

        //if number is greater than mid, search right array
        else if(number>array[mid]) return binary_search(array, mid+1, right, number);

        //if number is smaller than mid, search left side
        else return binary_search(array, left, mid-1, number);

    }
    //the element isn't in the array
    return -1;
}