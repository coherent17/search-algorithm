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

此種方法的優點是原陣列內部的元素不需要是排序過後的，因此若有新的元素加入陣列也可以直接搜尋，但是缺點是倘若被搜尋的元素是在陣列的末端，那麼將會耗費相當巨量的時間。

#### 時間複雜度:
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

### **二元搜尋(Binary search)**
#### 或稱為二分搜尋法，可以在"已排序"的序列中進行高效率的搜尋。
![image alt](https://d18l82el6cdm1i.cloudfront.net/uploads/bePceUMnSG-binary_search_gif.gif)
取已排序資料中間index的值來跟被搜尋的數來比較，若非此數，則將資料以中間索引分半。若較小，則選擇較小的那半資料，再取較小那半資料中間的數字來比大小，反之亦然，持續重複步驟，便能找到該數。

#### 時間複雜度:
Note:假設有陣列中有$n$個元素
*    Best Case:$O(1)$，剛好中間的數值就是被搜索的數值
*    Worst Case:$O(log(n))$，最慘需要折半對比$log_2(n)$次。

#### C code:
有兩種版本，一種是用迴圈的，另一種則是用遞迴。  
在這邊有一個特別需要注意到的事情為中點的計算方式:
```c=
int mid=(left+right)/2;
```
若是使用這種計算方法，當$left$及$right$的總和超過$int$的範圍，那麼這邊將會出現不可預期的錯誤。
當($left+right>2^{31}-1$)將會溢位。那要如何改善呢?
```c=
int mid=left+(right-left)/2;
```
透過上面終點位置取法的改變，因為$right \geq left$，因此$right-left$就不會出現overflow的情形了!
##### 迴圈版(iterative binary search):
```c=
#include <stdio.h>
#define SIZE 10

int iterative_binary_search(int *, int, int, int);

int main(){
    int array[SIZE]={1,2,3,4,5,6,7,8,9,10};
    int index;
    printf("iterative_binary_search:");
    index=iterative_binary_search(array,0,SIZE-1,8);
    printf("%d\n",index);
    return 0;
}

int iterative_binary_search(int *array, int left, int right, int number){
    while(left<=right){
        //mid point index:
        int mid=left+(right-left)/2;

        //check if the number is at mid
        if(array[mid]==number) return mid;
        
        //if number is greater than mid, search right array
        else if(number>array[mid]) left=mid+1;

        //if number is smaller than mid, search left side
        else right=mid-1;
    }
    //the element isn't in the array
    return -1;
}
```
code:https://github.com/coherent17/search-algorithm/blob/main/search/iterative_binary_search.c
##### 遞迴版(recursive binary search):
```c=
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
```
code:https://github.com/coherent17/search-algorithm/blob/main/search/recursive_binary_search.c  

用binary search的優點是非常有效率，可以看到worst case中，他的時間複雜度為$O(log(n))$，拿實際一點的數字來舉例，當有64筆資料，則最多需要試$log_2(64)=6$次，而當有128筆資料，則最多需要試$log_2(128)=7$次，可以看出隨著$n$增加，所需要試的次數增長是趨緩的。雖然使用binary search效率高，但是在使用binary search上有一個大前提是該數列必須要是"已排序"的數列。

### **指數搜尋(Exponential search)**
#### 為二分搜尋法的變形，可以在已排序後的陣列較快速的找到被搜尋的數值，不像Binary search是有邊界限制的。且被搜尋的數排在序列的越前面，效率越高。能夠縮小binary search進行的範圍，使其效率比binary search高。
![image alt](https://img.magiclen.org/albums/exponential-search/animation-541x141.gif)  
逐次比較被搜尋數與序列中index為2的冪次的數，直到被搜尋的數字大於序列中index為$2^k$的數，則針對$array[2^{k-1}:2^{k}-1]$進行binary search，即可找出該數。  
Note that:  
若$2^{k}-1$已經超出陣列的長度了，那麼我們將取陣列最後一個元素為binary search的右端點，因此真正再進行binary search的陣列為$array[2^{k-1}:min(2^{k}-1,size\ of\ array)]$
舉例說明:  

假設要找的數字為$47$
| 0   |  1  | 2   | 3   | 4   | 5   | 6   | 7   |  8  |  9  |
| --- |:---:| --- | --- | --- | --- | --- | --- |:---:|:---:|
| 2   |  9  | 30  | 32  | 38  | 47  | 61  | 69  | 79  | 81  |

*    Step 1:先比較$array[2^0]$是否大於被搜尋的數字47?      9<47
*    Step 2:再依序比較$array[2^1],array[2^2],array[2^3]$，發現到$array[2^3]$時，其數值已經大於被搜索的數字了。
*    Step 3:此時已經將binary search的範圍縮小到$array[2^{2}:2^{3}-1]$，再進行binary search即可找到被搜索數。

#### 時間複雜度:
Note:假設有陣列中有$n$個元素
*    Best Case:$O(1)$，剛好一開始的數值就是被搜索的數值
*    Worst Case:$O(log(n))$，當被搜索數接近陣列的開頭，效率會高於binary search

#### C code:
```c=
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
```
code:https://github.com/coherent17/search-algorithm/blob/main/search/exponential_search.c

### **插補搜尋(Interpolation search)**
#### 一樣是二分搜尋法的變形，不過尋找中間點的index改為使用數學中的內插法來進行。

此被搜尋的數列必須為"已排序的數列"，取最小及最大的兩點算出斜率，而後透過數學上的內插法去計算該被搜尋數的可能位置在哪裡，而後以那點為中點，最小及最大為範圍，進行比較，若該數大於剛剛算出的中點，則將剛剛的中點改為下界，再次使用內插法算出該數可能的位置。反之亦然。

#### 內插法:
設$(left,data[left])$,$(right,data[right])$為上限及下限的索引及所對應的數值。  

兩點間的斜率為:  
*    $\frac{data[right]-data[left]}{right-left}$
                                        
使用點斜式造出通過此二點的線:  

*    $y-data[left]=\frac{data[right]-data[left]}{right-left}(x-left)$  

設被搜尋數為$number$，而透過內插法求出他可能的索引值為$index$  
將$(index,number)$代入上式整理後可以得到我們預期被搜索數出現的$index$為:  
*    $index=left+\frac{number-data[left]}{data[right]-data[left]}(right-left)$  

而後我們去比較$data[index]$與$number$的關係:
*    **Three cases**:  
        *    Case 1:$number = data[index]$ 
        *    Case 2:$number > data[index]$ 
        *    Case 3:$number < data[index]$  

若為Case 1，那就成功找到該數了，若為Case 2，則將剛剛的$left$改為$index+1$，而後繼續使用內插法算出新的$index$直到找到數字為止。若為Case 3，則將剛剛的$right$改為$index-1$，而後繼續使用內插法算出新的$index$直到找到數字為止。

#### 舉例說明:

假設要找的數字為$84$
| 0   |  1  | 2   | 3   | 4   | 5   | 6   | 7   |
| --- |:---:| --- | --- | --- | --- | --- | --- |
| 13  | 21  | 34  | 55  | 69  | 73  | 84  | 101 | 

透過內插法，可以得知$index:$  
$index=0+\frac{84-13}{101-13}(7-0)=5.6 \sim 5$  

| 0   |  1  | 2   | 3   | 4   | 5                 | 6   |  7  |
| --- |:---:| --- | --- | --- | ----------------- | --- |:---:|
| 13  | 21  | 34  | 55  | 69  | $\color{red}{73}$ | 84  | 101 |

由於$73$小於被搜索的數，因此將對後面的資料進行同樣的搜索，即將$left$改為剛剛算出來的$5+1$。
因此新的$index:$  
$index=6+\frac{84-84}{101-73}(7-5)=6$

| 0   |  1  | 2   | 3   | 4   | 5   | 6                 |  7  |
| --- |:---:| --- | --- | --- | --- | ----------------- |:---:|
| 13  | 21  | 34  | 55  | 69  | 73  | $\color{red}{84}$ | 101 |

成功找到該被搜尋數了!  

#### 時間複雜度:
Note:假設有陣列中有$n$個元素
*    Best Case:$O(1)$，透過內插法直接找到正確的索引值(資料為線性分布)
*    Worst Case:$O(n)$，近似線的公式與實際上誤差很大，每次都剛好只有排除一個元素

#### C code:
```c=
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
```
code:https://github.com/coherent17/search-algorithm/blob/main/search/interpolation_search.c