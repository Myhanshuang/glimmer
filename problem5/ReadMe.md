### 2024090904002-胡杨-CS-05 

#### 课前准备

见 [preclass.c](https://github.com/Myhanshuang/glimmer/blob/main/problem5/preclass.c) 和 [preclass](https://github.com/Myhanshuang/glimmer/blob/main/problem5/img/preclass.png)

#### 任务 1

- 为什么会出现这样的现象（指 0.1 + 0.2 != 0.3 ）？
  - 计算机存储小数的时候，采用的是基于二进制的科学计数法。小数点后 n 位的 1 代表的是 $2^{-n}$。此时，注意到 $1/10$ 不能写成有限位二进制表示，则必然会发生截断。同理 $1/5$ 也会发生截断而产生精度丢失，导致了上面柿子的成立。
  - 因此，在判断两个浮点数是否相等的时候，应当考虑的是二者的差是否在一个合理的区间内，而不是直接选择用 “==” 进行判断。
-  该如何获得精确值呢？
  - 可以采取使用类似高精度整形数的存储方式，用字符数组储存、重写四则运算的方式。

- 课前热身：见 [task1.c](https://github.com/Myhanshuang/glimmer/blob/main/problem5/task1.c) 。

#### 任务 2

- 自定义见 [head.h](https://github.com/Myhanshuang/glimmer/blob/main/problem5/inc/head.h) 
- 结构体内存布局：以最长的数据类型为基本单位，每次尝试给成员分配空间的时候，先优先考虑之前分配余下的空间够不够，不够再选择分配一个基本单位量的空间。（如此分配的原因是为了尽可能自然对齐）因此，我在构建结构体的时候，选择使用尽可能小的单位(char)使浪费的空间尽可能小。
- [step1](https://github.com/Myhanshuang/glimmer/blob/main/problem5/img/tsak2_1.png) ：见 [task2_1.c](https://github.com/Myhanshuang/glimmer/blob/main/problem5/task2_1.c)
- [step2](https://github.com/Myhanshuang/glimmer/blob/main/problem5/img/tsak2_2.png) ：见 [task2_2.c](https://github.com/Myhanshuang/glimmer/blob/main/problem5/task2_2.c)

#### [任务 3](https://github.com/Myhanshuang/glimmer/blob/main/problem5/img/tsak3.png) 

见 [step3.c](https://github.com/Myhanshuang/glimmer/blob/main/problem5/task3.c) 



### 写在最后

- 使用了 overflow 提升鲁棒性（虽然不太能防住逆天输入乱搞）
- 留下了未来的一丢丢可扩展空间
- 我讨厌一辈子的局部变量（误
- 重新组织了程序逻辑
  - build 为 Cmake 专属文件夹
  - inc 为头文件专属文件夹
  - rsc 为文件依赖专属文件夹
  - test 为测试文件专属文件夹
    - in 为输入
    - out 为输出
  - img 为图片文件夹
  - 放在外面的都是要求提交的代码
- 及时与我交流不足之处我会很快爬起来改的感谢Orz
