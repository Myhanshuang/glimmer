### CS-MEDIUM-03 实验：Linux命令行实现 ——2024090904002——胡杨

### linux 配置

- linux 配置是在几百万年前看基础要求的时候就搞了，现在不咋能想得起来（）大致就是去造个镜像，然后用 VMware 挂载就完了，可能是我选择的是比较傻瓜化的 Ubuntu ？
- 顺带一提，安完可千万别忘了  `sodo apt upgrade` && `sodo apt update`，找不到包 99% 的问题都是忘了这个命令

### 阅读 myls.c 并学习

- 阅读程序从主函数开始吧
  - 主函数括号里有两个参数，第一个代表的是输入的参数的个数，第二个是具体的每个参数。参数的划分由每一行内的空格进行。例如 `ls ..` 就是两个参数，argv[0] 恒定为文件的名称，argv[1 ~ argc] 则是参数，此时 argv[0] = “myls” （不含文件扩展名），argv[1] = "ls"，argv[2] = ".."。
  - 可以打开 myls.c 查看我的学习顺手注释（

- 根据主函数的跳转，来到 list_directory 函数
  - DIR 是一种文件类型，用于指向目录。其在 `#include<dirent.h>` 中有定义，是一个类似于结构体的变量，里面存储着各种信息，具体等会会列出。但是它并不允许用户直接访问其中的成员，要求通过函数的方式访问。函数等会也会列出。此处试图去访问用户输入的目录，失败作出错误标记后即刻返回，成功则获得该目录下文件的信息。
    - 成员  （并没有什么价值去了解里面有啥，反正也不让你用）

      ```c
       struct __dirstream   
         {   
          void *__fd;    
          char *__data;    
          int __entry_data;    
          char *__ptr;    
          int __entry_ptr;    
          size_t __allocation;    
          size_t __size;    
          __libc_lock_define (, __lock)    
         };   
      
      typedef struct __dirstream DIR; 
      ```

    - 函数（这才是关键）

      ```c
      DIR *opendir(const char *pathname)
      //打开文件目录，返回值是 DIR 指针，作用是给一些其他的函数使用（你动不了的放弃吧）
      ```

    - 其实还有想说的

      - 类似 FILE 是文件指针一样，DIR 作为文件夹指针一样也有各种读取，包括顺序读取（readdir），中途跳转（rewinddir）。

  - struct dirent 存储着目录下文件的部分信息（少），且索引性极强，具体信息少得可怜

    - 原型

      ```c
      struct dirent
      {
      　　long d_ino; /* inode number 索引节点号 */
          //我谢谢你啊这么写的人，它是有问题的
          //第 n 次 readdir 时，获得的是目录下为第 n 个文件的信息
          off_t d_off; /* offset to this dirent 在目录文件中的偏移 */
          unsigned short d_reclen; /* length of this d_name 文件名长 */
          unsigned char d_type; /* the type of d_name 文件类型 */
          char d_name [NAME_MAX+1]; /* file name (null-terminated)文件名，最长255字符 */
      }
      ```

    - 这里我不得不批评一些*解压器你真的就用长的要死的压缩包名字作文件夹名字啊？你找死呐？

    - **文件名最长 255 字符！**

  - struct stat 是一个结构体变量，用于存储文件的**详细**信息。其在 `#include<sys/stat.h>` 中有定义。成员稍后列出，它允许直接访问成员，同时也有一套函数。

    - 原型
  
      ```c
      struct stat {
              mode_t     st_mode;       //文件访问权限
              ino_t      st_ino;       //索引节点号
              dev_t      st_dev;        //文件使用的设备号
              dev_t      st_rdev;       //设备文件的设备号
              nlink_t    st_nlink;      //文件的硬连接数
              uid_t      st_uid;        //所有者用户识别号
              gid_t      st_gid;        //组识别号
              off_t      st_size;       //以字节为单位的文件容量
              time_t     st_atime;      //最后一次访问该文件的时间
              time_t     st_mtime;      //最后一次修改该文件的时间
              time_t     st_ctime;      //最后一次改变该文件状态的时间
              blksize_t st_blksize;    //包含该文件的磁盘块的大小
              blkcnt_t   st_blocks;     //该文件所占的磁盘块
            };
      ```

  - 这里我们其实就可以明白搞到某个文件详细信息要怎么做了：先 opendir 拿到目录（*DIR），再对目录 readdir 得到目录下的所有文件（返回为 struct dirent ），最后再 stat 每一个文件，获取详细信息。

  - 开了文件流记得关，有的人已经死了有一会了（
  
- 根据函数的相关调用，最后来到了 print_file_info 函数

  - strftime 函数用于给一个字符串填充时间信息，比较方便的一点是它可以定制格式。
  -  ~~st_mode & 0777 别忘了二进制的 & 运算的作用（）~~实际上我想说的是，为什么要取最后三位。
    - linux 下文件的权限的保存方式是放在一个十位的串里面。第一位是文件类型，后面的九位每三位分为一组，三组依次是属主权限、属组（用户组）权限、其他权限。三位分别代表有无读、写、执行的权限。r（4）read，w（2）write，x（1）execute，-（0）没有权限。特殊权限位另说。
    - 特别注意：如果你只有 x 权限，是无法运行程序的。你还必须有 r 权限，才能跑得起来。
    - 特别注意：如果你没有文件的 w 权限，但是却有父目录的 w 权限，那么你可以对文件进行删除、重命名。
    - 综上所述，我们此处获得的其实是其他用户的权限。

- perror：等价于你在错误的地方用字符串将错误的地方存储起来，在运行结束前输出这个错误信息。

- 结束了……？还没有……难道你就不好奇那些头文件么（）

  - sys/stat.h 里面有提及文件类型：普通文件，目录文件，块特殊文件，字符特殊文件，套接字，FIFO，符号链接.
    - 特殊文件：在 unix 下，一切的东西都被视为文件。也就是说，像是终端被视为字符特殊文件，像是外界 USB 存储器被视为块特殊文件。块字面上就比字符要大的多，它的读写更高效。在块还没有写完的时候，它会留在缓冲区。
    - 套接字：（评：意义不明的翻译 socket）用于进程之间相互通信（也包括 & 外界网络）
    - FIFO ：省流：大小固定的队列式文件。不过它实质上是缓存器，用于缓解 IO 速率不一致的时候的效率降低。分为异步时钟的 FIFO 和 同步时钟的 FIFO。
    - 符号（软）链接：区别于硬链接作为文件的另一个备份，连接到同一个 inode 上，软链接类似于文件的快捷方式。

### 开始写 pwd 吧！

![](https://i-blog.csdnimg.cn/blog_migrate/7c235fd7d68fcba43d398934a60f9337.png)

~~我**的沃吐了我真的服了我的 markdown 啊~~

在试图迅速解决问题的时候遇见了无法解决的问题，遂回去重新探索一下。

现在重新简述一下我遇到的问题……

```c++
DIR *n = opendir(".");
struct dirent *now;
now = readdir(n);
struct stat noww;
stat(now->d_name, &noww);
printf("%d\n%d\n", now->d_ino, noww.st_ino);
```

得到输出两个一致。那么现在有两个情况：

- 1、与科普一致，同时 "." 恒为第一个文件
- 2、？

尝试输出 d_name ，得到的却是 “myls.c”

那么也就是说，实际上科普是有问题的……

你知道这浪费了我多少时间吗……（暴怒



继续探索

```c
struct stat buf;
stat(".", &buf);
DIR *n = opendir(".");
struct dirent *now;
now = readdir(n);
struct stat noww;
stat(now->d_name, &noww);
printf("%d\n,buf.st_ino);
do{
    now = readdir(n);
    if(now == NULL)
        return;
    printf("%s\n", now->d_name);
} while (now->d_name[0] != '.');
printf("%lu\n%lu\n", now->d_ino, buf.st_ino);
```

容易发现，输出的三个数字都是一样的，那么也就是说，这三种寻找方式都是等价的，可以灵活运用。

“.” 虽说是一个目录，但同时也其实是一个文件。

```c
struct stat buf;
stat("..", &buf);
chdir("..");
DIR *fat = opendir(".");
struct dirent *fp = readdir(fat);
struct stat fpt;
stat(fp->d_name, &fpt);
printf("%d\n%d\n%d\n", fp->d_ino, buf.st_ino, fpt.st_ino);
```

容易发现 1、3 的输出一致，但是为什么和第二个不一样呢？

尝试输出 fp->d_name 观测。输出是 problem6，也就是说，我们此刻应该去寻找一个东西能对应上，不用多想，就能想到去找 "." 文件。

```c
struct stat buf;
stat("..", &buf);
chdir(".."); 
DIR *fat = opendir(".");
struct dirent *fp = readdir(fat);
struct stat fpt;
stat(fp->d_name, &fpt);
printf("%s\n", fp->d_name);
do{
    fp = readdir(fat);
    if(fp == NULL)
        return;
    stat(fp->d_name, &fpt);
    // printf("%s\n", fp->d_name);
} while (fp->d_name[0] != '.');
printf("%d\n%d\n%d\n", fp->d_ino, buf.st_ino, fpt.st_ino);
```

很好，现在如我们所预期的，确实一样了。

那么现在我们就可以有这样一个基本思路：

获取当前目录(".")的inode 然后在父目录中找inode一样的，存储path，依次重复进行。

不过在这之前，还得考虑一下终止条件：当 "." && ".."一致的时候，可以终止，不过我需要确认以下这个东西确实在根目录存在。那就浅浅偷一下奶绿的 myls.c 啦（

结果证明确实存在，所以就直接开写吧（）

写！

比预期的简单好多啊啊啊啊我恨伪科普…………



