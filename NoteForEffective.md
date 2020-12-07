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

### 条款5
*"Know what functions C++ silently writes and calls."*  
Sometimes由程序员所编写的空class并不是看上去的那样一个空类，编译器会为它偷偷声明一个copy构造函数，一个copy assignmen操作符（通常来说是“=”）以及一个析构函数。  
但也存在不适用的情况，党你打算在一个内含reference成员的class内支持赋值操作（assignment），你必须自己定义copy assignment操作符。
### 条款6
*"Explicitly disallow the use of compiler-generated functions you do not want."*  
当定义的某个class对象需要具备唯一性质的时候，为驳回编译器自动提供的机能，即**条款5**中的内容，可将相应的成员函数声明为private并且不予实现，或者使用一个专门为了阻止copying动作而设计的base class。  

### 条款7
*"Declare destructors virtual in polymorphic base class."*  
当一个derived class对象经由一个base class指针被删除，而该base class带着一个non-virtual析构函数，其结果通常是对象的derived部分没有被销毁。极易造成资源泄露。  
所以带有多态性之的base classed应该声明一个virtual析构函数，换言之，如果class带有任何的virtual函数，则它就应当拥有一个virtual析构函数。  
反言之，当class的设计目的不是作为base class使用，或者不具备多态性质，就不该声明virtual析构函数。 

### 条款8
*"Prevent exceptions from leaving destructors"*  
C++不喜欢析构函数吐出异常。如果需要对某个操作函数运行期间抛出的一场作出反应，那么class应该提供一个普通函数（而非在析构函数中）执行该操作。

### 条款9
*"Never call virtual functions during construction or destruction."*

### 条款10
*"Have assignment operators return a reference to *this."*
