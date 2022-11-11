https://github.com/huihut/interview

- C++的四种多态机制 [The Four Polymorphisms in C++](https://catonmat.net/cpp-polymorphism)
> These polymorphisms also go by different names in C++,
>
> - Subtype polymorphism is also known as **runtime polymorphism**.
> - Parametric polymorphism is also known as **compile-time polymorphism**.
> - Ad-hoc polymorphism is also known as **overloading**.
> - Coercion is also known as **(implicit or explicit) casting**.

- [C++中的虚函数表实现机制以及用C语言对其进行的模拟实现](https://blog.twofei.com/496/)
- delete this 合法吗？
> [Is it legal (and moral) for a member function to say delete this?](https://isocpp.org/wiki/faq/freestore-mgmt#delete-this)

- [如何定义一个只能在堆上（栈上）生成对象的类?](https://www.nowcoder.com/questionTerminal/0a584aa13f804f3ea72b442a065a7618)

- `std::sort`排序算法 - [Introsort](https://en.wikipedia.org/wiki/Introsort)

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
