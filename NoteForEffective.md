# 阅读笔记 of effective C++     
### 条款1     
Cplusplus should be treated as a multiparadigm programming language. We need to accept the concept that Cplusplus is composed of 4 sublanguanges, including *C language, Object-Oriented C++, Template C++, STL*.  
其中，第二部分属于C++在C语言基础上所提升的部分，也是当被问到C++与C的区别是最先应该想到的答案；第四部分所说的是STL这一模板程序库， 
它对容器(container),迭代器(iterator),算法(algorithm),以及函数对象(functioi)的规约有极佳的紧密配合与协调。
而C++的高效编程守则视情况而变化，取决于你使用C++的那一部分sublanguage。

### 条款2
*"Prefer consts, enums, and inlines to #defines."*  
换句话说，宁可以编译器替换处理器，说的是一个道理。  
我们对预处理器的需求在不断降低，但并非完全消除。毕竟#include以及#ifndef等会继续扮演控制编译的重要角色，目前还未到预处理器全面引退的时候，但应当明确给与它更长更频繁的假期。  

### 条款3
*"Use const whenever possible."*  
!区分指针常量和常量指针以及指向数值常量的指针常量。  
用中文说上面这段话过于拗口，所以  
Differentiate between pointer of a const data & const pointer of a data.  

### 条款4  
*"Make sure that objects are initialized before they're used."*   
- 为内置型对象进行手动初始化；  
- 构造函数最好使用成员初值列(member initialization list)， 且初值列列出的成员变量，其排列次序应当和class中的声明次序相同；    
- 尽量以local static对象代替non-local static对象，合理安排系统中各个互相影响的类的初始化顺序。

