<https://github.com/huihut/interview>

## 相关知识点

### C++的四种多态机制 [The Four Polymorphisms in C++](https://catonmat.net/cpp-polymorphism)

> These polymorphisms also go by different names in C++,
>
> - Subtype polymorphism is also known as **runtime polymorphism**.
> - Parametric polymorphism is also known as **compile-time polymorphism**.
> - Ad-hoc polymorphism is also known as **overloading**.
> - Coercion is also known as **(implicit or explicit) casting**.

### [C++中的虚函数表实现机制以及用C语言对其进行的模拟实现](https://blog.twofei.com/496/)

### delete this 合法吗？

> [Is it legal (and moral) for a member function to say delete this?](https://isocpp.org/wiki/faq/freestore-mgmt#delete-this)

### [如何定义一个只能在堆上（栈上）生成对象的类?](https://www.nowcoder.com/questionTerminal/0a584aa13f804f3ea72b442a065a7618)

### `std::sort`排序算法 - [Introsort](https://en.wikipedia.org/wiki/Introsort)

> Introsort or introspective sort is a hybrid sorting algorithm that provides both fast average performance and (asymptotically) optimal worst-case performance. It begins with quicksort, it switches to heapsort when the recursion depth exceeds a level based on (the logarithm of) the number of elements being sorted and it switches to insertion sort when the number of elements is below some threshold. This combines the good parts of the three algorithms, with practical performance comparable to quicksort on typical data sets and worst-case O(n log n) runtime due to the heap sort. Since the three algorithms it uses are comparison sorts, it is also a comparison sort.

```
procedure sort(A : array):
    let maxdepth = ⌊log2(length(A))⌋ × 2
    introsort(A, maxdepth)

procedure introsort(A, maxdepth):
    n ← length(A)
    if n < 16:
        insertionsort(A)
    else if maxdepth = 0:
        heapsort(A)
    else:
        p ← partition(A)  // assume this function does pivot selection, p is the final position of the pivot
        introsort(A[1:p-1], maxdepth - 1)
        introsort(A[p+1:n], maxdepth - 1)
```

相关原理分析：[知无涯之std::sort源码剖析](https://feihu.me/blog/2014/sgi-std-sort/)
相关排序算法时间复杂度：[link](https://github.com/huihut/interview#%E6%8E%92%E5%BA%8F)

### C语言如何实现面向对象编程？

- 封装 (通过组合的形式，把数据和函数指针聚合在结构体中)
- 继承 (嵌套基类定义)
- 多态 (手动加虚指针和虚表，并手动赋值函数指针)

### 函数调用约定 [参数传递和命名约定](https://learn.microsoft.com/zh-cn/cpp/cpp/argument-passing-and-naming-conventions?view=msvc-170)


### 线程安全的单例模式 [C++ 线程安全的单例模式](https://greedysky.github.io/2020/10/05/C++%20%E7%BA%BF%E7%A8%8B%E5%AE%89%E5%85%A8%E7%9A%84%E5%8D%95%E4%BE%8B%E6%A8%A1%E5%BC%8F/)

### `std::vector`扩容因子的选择，**1.5**和**2**

倍数扩容的的时间复杂度为一个常数，现多选择1.5，原因是可以重用之前释放的空间（`1111 < 10000`）。

### 线程池、内存池

## 缺少的技能

- [ ] 数据库
- [ ] Linux
- [ ] 网络编程的I/O多路复用
- [ ] 手撕数据结构
- [ ] 手撕算法
- [ ] 剑指Offer
- [ ] 智能指针完整实现
