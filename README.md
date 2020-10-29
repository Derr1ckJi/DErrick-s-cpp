# DErrick-s-cpp

//2020.7.11 start from a emulator development project.

//以此readme文件作为一个琐碎的笔记本 <br>
//2020.9.28  

#**《关于程序的时间复杂度》**  

definition：渐近时间复杂度 若存在函数 f（n），使得当n趋近于无穷大时，T（n）/ f（n）的极限值为不等于零的常数，则称 f（n）是T（n）的同数量级函数。记作 T（n）= O（f（n）），称O（f（n）） 为算法的渐进时间复杂度，简称时间复杂度。
通俗来说，是一种横向比较不同程序语句时间复杂度的衡量。将程序的时间规模用他的量级来表示。

对于数组元素的访问属于O（1）复杂度操作。通常对于每一次操作能够去掉一半元素的算法，例如二分搜索，其复杂度为O（logn）。用strcmp比较两个具有n个字符的串需要O(n)时间。常规的矩阵乘算法是O(n^3)，因为算出每个元素都需要将n对 元素相乘并加到一起，所有元素的个数是n^2。
指数时间算法通常来源于需要求出所有可能结果。

##***较难理解的例题***：
斐波那契数列计算递归函数
```
Fibonacci(int n){
if(n<=1) return 1;
else return(fibonacci(n-1)+fibonacci(n-2));
}
```
该递归算法的时间复杂度为~~O(n^2)~~O（2^n）.
*************************************************

相对于时间复杂度来说，空间复杂度更容易理解。可以简单的分析需要的存储空间大小即可得出。
例如，一维数组a[n]的空间复杂度即为n，而二维数组b[n][m]的空间复杂度即为n*m。

**线性表**：一个开始节点、一个终端节点。其他节点各有一个前驱和一个后继
分为顺序存储和链式存储
区别在于顺序存储的地址是连续的，而链式存储则不然。
顺序存储与数组具有相似性，体现在地址连续、随机存取、依次存放、类型相同。顺序表与数组的区别在于线性表表长可变，但数组长度不可动态定义。

   ps. dinamic definition of an array
`   std::cin<<a;`
`    int *array = new int[a]; `
    
//链式存储代码定义：
``` 
typedef struct Lnode
  {Elemtype data;
   struct Lnode *next
  }Lnode;
  p = (Lnode*)malloc(sizeof(Lnode));//动态内存分配
  free(p);//释放内存 
  ```
  
同时，与c语言中malloc和free这一组操作对应的，在c++中有new和delete
在此指出new和malloc的区别，这也是一道非常经典的面试题：
1.new是关键字，malloc是库函数，需要头文件支持；
2.使用new申请的内存无需指定大小，而malloc需要将申请的内存大小作为参数
3.new操作成功后直接返回相应类型的指针，而malloc操作成功后返回void型指针，需要进行强制类型转换；
4.new可以为自定义类型开辟存储区，但malloc不行；
5.new（delete）可重载；
6.new调用构造函数并分配内存，但malloc只进行内存分配工作；
7.new从自由存储区上为动态对象分配内存空间，而malloc从堆上动态分配内存；
8.new操作失败时会抛出bac—malloc异常，malloc分配内存失败是返回NULL。

~引入链表的表头节点概念
区别销毁与清空链表：销毁指将包括头节点在内的所有节点全部释放，清空表示保留头节点，释放剩余节点，头节点指针为空。


操作    |  顺序表  |   链表
--     |:--:      |--:
查询（修改）|   O(1)   |   O(n)
插入（删除）|   O(n)   |   O(n)
  
##c++语法创建不规则二维数组
```
int numberofRows = 5;
int length[5]={6,3,4,2,7};
int **irregularArray = new int* [numberofRows]
;

for(int i=0; i<numberofRows; i++)
   irregularArray[i] = new int [length[i]];
```
