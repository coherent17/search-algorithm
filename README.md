# **Algorithm 演算法搜尋筆記**
**[此筆記的原始碼](https://hackmd.io/qi8shArlSsS09WCNOVLyow?both)**
---
## 搜尋演算法
*    線性搜尋(Linear search)
*    二元搜尋(Binary search)
*    指數搜尋(Exponential search)
*    插補搜尋(Interpolation search)
*    費氏搜尋(Fibonacci search)

### **線性搜尋(Linear search)**
#### 從第一個元素開始，依照順序，接續判斷是否為要搜索的元素，非常簡單。
![image alt](https://www.tutorialspoint.com/data_structures_algorithms/images/linear_search.gif)

#### 時間複雜度與空間複雜度:
Note:假設有陣列中有$n$個元素
*    Best Case:$O(1)$，剛好第一個index就是被搜索的元素
*    Worst Case:$O(n)$，被搜索的元素在陣列末端，因此需要執行$n$次比對的步驟。

#### C code:
```c=
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
```
code:https://github.com/coherent17/search-algorithm/blob/main/search/linear_search.c