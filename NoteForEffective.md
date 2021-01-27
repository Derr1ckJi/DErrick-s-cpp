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
原因在于derived class对象内的base class成分会在derived class自身成分之前被构造妥当。而此处的base class如果其构造函数是一个virtual，则该virtual函数绝不会下降到derived阶层，且此时derived class的成员变量尚未初始化，这样必然导致问题。同理，析构函数也是如此。

### 条款10
*"Have assignment operators return a reference to *this."*  
遵循赋值操作的协议，在重定义操作符时令其返回一个reference指向操作符的左侧。  

### 条款11(反复阅读）
*"Handle assignment to self in operator="*
- 确保当对象自我赋值时operator=有良好的行为。其中技术包括比较来元对象和目标对象的地址、语句顺序细节、以及copy-and-swap.  
- 这个条款主要针对可能出现的对象被赋值给自己的现象，在自行管理资源的时候，可能会掉入在停止资源之前意外释放了它的陷阱。  
- 除以上之外，还要注意自我赋值操作的意外安全性，也就是说new操作导致的异常（可能是由于分配时内存不足或copy构造函数抛出异常），最直接的解决方案就是注意在赋值所给指针指向的对象之前别删除该指针。  

### 条款12
*"Copy all parts of an object."*  
如果你为class函数添加一个成员变量，你必须同时修改其copying函数，否则复制操作会漏掉新加入的成员变量。  
更重要的问题会出现在derived class身上，要谨记任何时候你只要承担起“为derived class撰写copying函数”的责任，必须很小心地复制其base class部分。如果这些部分是private类型的，无法直接访问，那么你就应当调用相应的base class函数。

### 条款13(反复阅读）
*"Use objects to manage resource."*  
将资源放入对象内，我们可以依赖C++的析构函数自动调用机制，确保资源的释放。
- 为防止资源泄露，请使用RAII对象，它们在构造函数中获得资源并在析构函数中释放资源。  
- 两个常被使用的RAII classes分别是tr1：：shared_ptr&auto_ptr，前者通常是更好的选择，因为其copy行为比较直观。若选择auto_ptr，复制动作会使被复制者指向null。  
ps.RAII----Resource Acquisition is Initialization.资源取得时机即是初始化时机。  
此处对两种指针做详细介绍：
#### auto_ptr
“类指针(pointer-like)对象”，所谓的“智能指针”，智能之处在于其析构函数自动对其所指的对象调用delete。其操作原则为：**获得资源后立即放入管理对象，一旦对象被销毁，资源也会立即被释放**，这也被称为**RAII守则**。需要注意的是，由于auto_ptr的机制，一定不能让多个auto_ptr同时指向同一个对象，否则该对象会被多次删除，导致未定义行为。为了预防这个问题，anto_ptr具备一个特殊性质，当其被复制或者值传递时，被复制者会编程null，而复制所得的指针会指向原目标对象。
#### shared_ptr
该指针属于引用计数型智慧指针RCSP(reference-counting smart pointer)，能够追踪同时有多少对象指向某个资源，并在无人指向资源时自动删除该资源。  
同时auto_ptr和shared_ptr都在其析构函数内做delete而不是delete[]，所以动态分配所得的array并不能使用这两种指针进行释放空间资源。

### 条款14 
*"Think carefully about copying behavior in resource-managing classes."*  
当RAII对象被复制时，必须一并复制它所管理的资源，所以资源的copying行为决定RAII对象的copying行为。  
深入一层，当面临RAII对象被复制时，一般有以下两种做法：1.禁止复制；2.对底层资源使用引用计数法(shared_ptr提供“删除器”机制)。

### 条款15 
*"Provide access to raw resources in resource-managing classes."*  
API通常要求直接访问原始资源作为参数，而使用如auto_ptr以及shared_ptr等指针作为参数是无法通过编译的，所以每一个RAII class应该提供一个取得其所管理的原始资源的方法。对原始资源的访问可以经由显式转换或隐式转换，一般而言显式转换更安全，隐式转换更方便，但也可能增加错误发生机会。  

### 编辑于2021.1.11 研究生阶段的第一个寒假
放假两天，荒废两天，之后开始了我的经典反省，虽然没什么用，但是这么多年也就这么过来了。本意是想在github记录下这半年，有些什么不一样的地方，我又成长了些什么，但细想之下，这些没什么值得说的，所以今天重拾effective之后，在此洋洋洒洒想到哪儿写到哪儿，且算是我的一些小感受吧。越成长越清楚自己是个没什么本事也没什么理想抱负的人，我在零下几度湿冷的南通用冰凉的手指敲下这些文字，我以前一直觉得父亲是个没什么本事的人，现在也一样，但我也算理解了一些他的无奈吧。作为一个男性活在这个社会活在这个世界，想只靠自己就能活的多么优雅，简直是不可能的事情，更多时候，狼狈地活着，才更是一种常态，所以我会被告知，想要混的好一点，要学会厚着脸皮。我这个社交恐惧症，又时不时的好面子一下，怎么做到这些事情啊。这个问题暂时是想不出结果的，所以只能安慰自己，车到山前必有路，同龄人中我也不算太差劲的，peer pressure也不算太大的问题。前几天也跟家里聊起找工作的事情，说起这个问题其实我挺不乐观的，实验室学到的这些本事不太能够支持我去跟计算机科学与技术、软件工程这些专业走出来的大佬们去抢岗位，但直接进入研究所我又有些些复杂的感觉。所以这个寒假即使没找到什么靠谱的实习，也好好**努力**吧。


### 条款16
*"Use the same form in corresponding uses of new and delete."*        
如果你在new表达式中使用了[]来创建一个数组空间，必须在相应的delete表达式中也使用[]，vise versa.  
此外，最好尽量不要对数组形式做typedefs动作。

### 条款17
*"Stored news obhjects in smart pointers in standalone statements."*         
以独立语句将newed对象存储于智能指针内，如果不这样做，一旦异常被抛出，有可能导致难以察觉的资料泄露。

### 条款18
*"Make interfaces easy to use correctly and hard  to use incorrectly."*           
为防止接口被传入错误参数，有时可以考虑导入新类型。

### 条款19
*"Treat class design as type design."*     
设计优秀的classes是一项艰巨的工作，需要考虑以下列出的诸多问题：创建和销毁、对象的初始化和赋值、pass-by-value的可行性、操作符和函数、继承等等。

### 条款20  
*"Prefer pass-by-reference-to-const to pass-by-value."*   
继承自C语言，缺省情况下C++以by value方式传递对象至函数。在这个传递过程中，会产生一个实参的副本作为初值，调用端获得的即使这个副本，这些副本的创建和销毁就会调用对象的构造和析构函数，所以当以值传递的形式调用自定义类型时，或许自定义对象中有很多个成员变量，此时会增加很多无意义的运行内存开销。而pass-by-reference属于更为高效的传递方式，避免了不必要的程序开销，也可以避免对象切割问题。需要注意的是，对于内置类型以及STL的迭代器和函数对象，pass-by-value往往更加恰当。
   
### 条款21     
*"Don't try to return a reference when you must return an object."*    
As the foregoing case goes, 作为程序员要学会判断什么时候能够返回引用而什么时候只能返回value，在函数中我们经常会遇到返回一个被计算得到的临时变量，此时如果我们一旦返回其引用，那么该返回值其实是一个已经被销毁的对象，而这样的程序是一定会出问题的。   
所以绝对不要返回pointer或reference指向一个local stack对象，或返回reference指向一个heap-allocated对象，或返回pointer或reference指向一个local static对象而有可能同时需要多个这一的对象。

### 条款22   
*"Declare data members private."*   
切记将成员变量声明为private。这可赋予客户访问数据的一致性、可细微划分访问控制、允诺约束条件获得保证，并提供class作者以充分的实现弹性。仅允许用户调用函数、而不是直接修改数据，这一举措能使得你对成员变量的处理有更精确的控制。   
此外，protected不比public更具封装性。

***--Q:如何判断成员变量的封装性？***  
> --A:成员变量的封装性与成员变量的内容改变时所破坏的代码数量成反比。

### 条款23  
*"Prefer non-member non-friend functions to member functions."*   
相对于member函数，non-member函数具有更好的封装性，较为自然的做法是将这个non-member函数与相关的class置于同一个namespace内。

### 条款24  
*"Declare non-member functions when type conversions should apply to all parameters."*  
如果需要为某一个函数的所有参数（包括被this指针所指的那个隐喻参数）进行类型转换，那么该函数必须是个non-member。正如本条款中所举的例子，常见于各种双目运算符重载中。

### 条款25
*"Consider support for a non-throwing swap."*   


