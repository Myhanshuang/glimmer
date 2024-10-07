#include <stdio.h>
#include <dirent.h>   //DIR 数据类型的头文件
#include <sys/stat.h> //stat 函数的头文件
#include <string.h>
#include <stdlib.h>    //标准库的内存操作函数
#include <time.h>      // 获取本地时间
#include <unistd.h>    //chdir
#include <sys/types.h> // 可能不是必需的，但符合POSIX标准
char path[256][256];
int cnt;

void learn() // to learn the structure
{
    // chdir("..");chdir("..");chdir("..");chdir("..");chdir("..");chdir("..");chdir("..");chdir("..");chdir("..");chdir("..");
    // struct stat buf;
    // stat(".", &buf);
    // stat("..", &buf);
    // DIR *n = opendir(".");
    // struct dirent *now;
    // now = readdir(n);
    // struct stat noww;
    // stat(now->d_name, &noww);
    // printf("%d\n%d\n%d\n", now->d_ino, buf.st_ino, noww.st_ino);
    // printf("%s\n", now->d_name);
    // now = readdir(n);
    // printf("%s\n", now->d_name);

    // chdir("..");

    // stat(".", &buf);
    // DIR *fat = opendir(".");
    // struct dirent *fp = readdir(fat);
    // struct stat fpt;
    // stat(fp->d_name, &fpt);
    // printf("%s\n", fp->d_name);
    // do
    // {
    //     fp = readdir(fat);
    //     if (fp == NULL)
    //         return;
    //     stat(fp->d_name, &fpt);
    //     // printf("%s\n", fp->d_name);
    // } while (fp->d_name[0] != '.');
    // printf("%d\n%d\n%d\n", fp->d_ino, buf.st_ino, fpt.st_ino);

    // 寻找.文件

    // do{
    //     now = readdir(n);
    //     if(now == NULL)
    //         return;
    //     printf("%s\n", now->d_name);
    // } while (now->d_name[0] != '.');
    // printf("%lu\n%lu\n", now->d_ino, buf.st_ino);
}

void print_work_directy()
{
    // 获取当前目录的inode 然后在父目录中找inode一样的，存储path
    while (1)
    {
        // 判断到达根目录
        struct stat nowdata, fatherdata;

        if (stat(".", &nowdata) == -1) // 获取当前目录的inode
        {
            perror("open nowdata fail");
            exit(EXIT_FAILURE);
        }

        if (stat("..", &fatherdata) == -1) // 获取父目录的inode
        {
            perror("open fattherdata fail");
            exit(EXIT_FAILURE);
        }
        if (nowdata.st_ino == fatherdata.st_ino)
            return;

        // 在父目录里查找和当前目录inode一致的文件，记录名字
        DIR *f;
        if ((f = opendir("..")) == NULL)
        {
            perror("open now fail");
            exit(EXIT_FAILURE);
        }
        struct dirent *fa;
        do
        {
            if ((fa = readdir(f)) == NULL)
            {
                perror("readdir father fail");
                exit(EXIT_FAILURE);
            }
        } while (fa->d_ino != nowdata.st_ino);
        // strcpy(path[cnt++], fa->d_name);
        for (int i = 0; i < strlen(fa->d_name); i++)
        {
            path[cnt][i] = fa->d_name[i];
        }
        cnt++;
        // puts("sadfhoahsdf");
        closedir(f);
        chdir("..");
    }
}

int main(int argc, char *argv[])
{
    freopen("stdout.out", "w", stdout);
    // learn();
    print_work_directy();
    // printf("%d\n", cnt);
    for (int i = cnt - 1; i >= 0; i--)
        printf("/%s", path[i]);
}