# DErrick-s-cpp

//2020.7.11 start from a emulator development project.

//以此readme文件作为一个琐碎的笔记本 
//2020.9.28
《关于程序的时间复杂度》
definition：渐近时间复杂度 若存在函数 f（n），使得当n趋近于无穷大时，T（n）/ f（n）的极限值为不等于零的常数，则称 f（n）是T（n）的同数量级函数。记作 T（n）= O（f（n）），称O（f（n）） 为算法的渐进时间复杂度，简称时间复杂度。
通俗来说，是一种横向比较不同程序语句时间复杂度的衡量。将程序的时间规模用他的量级来表示。

对于数组元素的访问属于O（1）复杂度操作。通常对于每一次操作能够去掉一半元素的算法，例如二分搜索，其复杂度为O（logn）。用strcmp比较两个具有n个字符的串需要O(n)时间。常规的矩阵乘算法是O(n^3)，因为算出每个元素都需要将n对 元素相乘并加到一起，所有元素的个数是n^2。
指数时间算法通常来源于需要求出所有可能结果。

较难理解的例题：
斐波那契数列计算递归函数
Fibonacci(int n){
if(n<=1) return 1;
else return(fibonacci(n-1)+fibonacci(n-2));
}
该递归算法的时间复杂度为O（2^n）.
