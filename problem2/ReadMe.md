## problem2：2024090904002-胡杨-CS-02

 **答案输出在 answer.out,** ~~下次别这样了求求了瓦达西什么都会做的~~

- 一编：在被 T1 折磨疯的时候写 ~~我真的是服了我还不如没有零基础的来得方便（CE 不查自己捣鼓半天自找的）~~

  - 很简单一个破事：本人高中打 OI 学的是 C++，然后此处切换到 C 经常忘记自己所用语言的区别，然后被狠狠地上了一课，详情如下……

  - 在 C 中，结构体是与 C ++ 不同的。

    - 定义中，C++ 比 C 更加简洁

      ```c++
      struct node{
      	int data;
      	node *next
      };//c++
      ```

      而在 C 中，有两种可行的方法，但是 **绝对与 C 有区别！！！**（指在结构体中使用的那个）

      - 第一种是选择随处使用 `struct node valname;`
      - 第二种是选择使用 `typedef struct node`

      但是无论哪一种，都不是 C++的定义方式！！！

  - 总而言之，这下是真的狠狠地吃了苦头了，一定得摆脱自己之前定式思维。
  
- 二编：这一切都源于指针……

  - 写份代码问 AI 被狠狠地骂了一通（目死）
  - 找资源习惯于在 OI wiki 上找的蒟蒻又吃苦头了……
  - 可没有人告诉我结构体指针在使用之前要先分配空间……

- 三编：终于完成 Part1 了救命

  - 学到的东西简直太多了（痛哭流涕）被 C 的 struct 又狠狠地折磨了一番，幸好有 Kimi 教我语法（躺下）
    - 1、链表结构体定义的时候，它在结构体里面是 **不能** 使用出来简化的名字定义的。还记得上古年代的 CSDN 狠狠坑了我一把，且与 C++ 不同，只要有了简化的名字，就 **不能** 用 `struct name val` 进行定义……
    - 2、结构体指针在赋值时，倘若没有用指针给它进行初始化，一定要 **先分配空间再初始化！！！！！** ~~（感谢 kimi 救我狗命）~~
    - 3、C 里面与 C++ 不同， 没有 `nullptr`， 不能使用 null 进行赋值，得用 NULL ！！！
    - 4、关于分配内存：看见后面有个专题是与之相关的，所以这里就直接先背了（）后面再研究。 ~~指不定一去不复返了~~
    - 5、养成好习惯，写循展可以，但是别把自己玩没了（死）
    - 6、摸了一把文件流

  - 多嘴一句，说实话哈，之前 C++ 打 OI 的时候，链表全是 vector，完全没有接触过这种形式的链表，我发现摆脱 STL之后我简直是个废人，看来很多东西还是要好好从头开始，向下深掘的……

- 四编：为什么最终的字符串很不对劲啊救命，怎么看都有一个 glimmer 的单词在吧……

  - 警钟撅烂：数组下标不要越界……（虽然我觉得标算不会出这个 bug
  
- 五编：…………

  - 求求你，求求你，不要再做这种事了，我什么都会做的！！！！


