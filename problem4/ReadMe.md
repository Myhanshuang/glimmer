## problem4：2024090904002-胡杨-CS-04

### Part 1: Answer questions

- Q1 : 为什么要使用字符数组来表示大数？
  - A1 : 字符数组没有位数限制，优于 int 或 long long。同时单个 char 类型的占用空间为 1 byte， int 则为 2 ~ 4 byte，一旦位数多起来占用空间差距会被明显拉大。（与用数组相比有空间优势） ~~虽然我还是喜欢用 int 省去那么一步（bushi）~~
- Q2 ：如何处理大数运算中的进位和借位问题？
  - A2：省流：模拟。可以完全参照我们列竖式进行计算的方式，进行模拟。（用一个专门的变量存丢到下一位就是了撒）
- Q3：如何处理负数？
  - A3：可以考虑为字符数组添加一个 bool 标识符或者直接用最后一位 / 第一位进行标记，还有使用结构体封装（扩展性特别好，我后面就是用的它）。 ~~(方法多了去了~~)~~

### Part2

- step1 ： 见 [storage.c](https://github.com/Myhanshuang/glimmer/blob/main/problem4/storage.c) && [step1.png](https://github.com/Myhanshuang/glimmer/blob/main/problem4/step1.png)
- step2 ： 见 [plus.c](https://github.com/Myhanshuang/glimmer/blob/main/problem4/plus.c) && [step2.png](https://github.com/Myhanshuang/glimmer/blob/main/problem4/step2.png)
- step3 ： 见 [superplus.c](https://github.com/Myhanshuang/glimmer/blob/main/problem4/superplus.c) && [step3.png](https://github.com/Myhanshuang/glimmer/blob/main/problem4/step3.png)

### Part 3：从表达式中提取操作数和操作符

- 见 [Part3.png](https://github.com/Myhanshuang/glimmer/blob/main/problem4/Part3.png) && [fetch.c](https://github.com/Myhanshuang/glimmer/blob/main/problem4/fetcht.c)

### Part 4：打包四则运算

- 不是，哥们，怎么这里这么上强度啊（）
- 幸好不用考虑复杂度，要不然我写这么臭肯定要被我高中教练打死过去（）。
- 见 Part4_i.png && [final.c](https://github.com/Myhanshuang/glimmer/blob/main/problem4/final.c)
  - [Part4_1](https://github.com/Myhanshuang/glimmer/blob/main/problem4/Part4_1.png)
  - [Part4_2](https://github.com/Myhanshuang/glimmer/blob/main/problem4/Part4_2.png)
  - [Part4_3](https://github.com/Myhanshuang/glimmer/blob/main/problem4/Part4_3.png)
  - [Part4_4](https://github.com/Myhanshuang/glimmer/blob/main/problem4/Part4_4.png)


### 意外收获

- C 函数传参实际上是丢个地址过去，所以函数内实际上是指针的操作。
- 当想在函数内部进行交换的时候，一定要选择在指针的前面加上 `*`，因为我们希望的是交换指针指向的东西，而不是指针本身。
- 函数内给另一函数传参的时候，本身就是指针了，就不需要加取地址符了（我是弱智）
- 想念 C ++ STL 的第 N 天呜呜呜……
- 不同位数的数进行运算的时候别忘了补 0 呜呜呜……
- 补个锤子的 0 我直接当 int 用了呜呜呜呜呜呜呜呜呜呜呜

- 怎么有弱智忘记了负数减负数啊啊啊啊啊滚回去重写了


### 说点别的

说实话，这是我第一次挑战高精度运算的整体打包，从头到尾自己推导自己实现（虽然复杂度是会被打死的程度），历时两天整，是一段非常非常有价值的经历。 ~~期间熬夜太久高数课打瞌睡还被抓包了呜呜呜。~~ 从来没有哪一次维护过这么长的代码，从来没有哪一次深入理解传址到这次这个程度（对于函数），从来没有哪一次自己纯手写完全丢掉 STL （是的我被 vector 重载运算符惯坏了，离开了真的浑身难受）~~还有从来没有哪一次能扣 BUG 扣到如此情绪失控到发疯~~

这次写高精代码，狠狠地让我领略了一番 C 的魅力呜呜呜……

写到这里，我可以自豪地说，这份代码能完全解决两个高精数的四则运算！
