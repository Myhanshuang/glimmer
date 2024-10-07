#include <stdio.h>
#include <dirent.h>   //DIR 数据类型的头文件
#include <sys/stat.h> //stat 函数的头文件
#include <string.h>
#include <stdlib.h>    //标准库的内存操作函数
#include <sys/types.h> // 可能不是必需的，但符合POSIX标准
#include <time.h>      // 获取本地时间
#include <unistd.h>
/*
    输出文件信息
*/
void print_file_info(const char *name, struct stat *statbuf)
{
    printf("%s\t", name);                    // 文件名
    printf("%ld\t", statbuf->st_size);       // 文件大小
    printf("%o\t", statbuf->st_mode & 0777); // 文件权限（仅显示最后三位）
    // 最后修改时间
    char timebuf[80];
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M", localtime(&statbuf->st_mtime));
    printf("%s\n", timebuf);
}
/*
    文件路径信息的处理
*/
void list_directory(const char *path)
{
    DIR *dir; // 来自 #include<dirent.h>
    // 声明一个指针，用于指向目录流
    struct dirent *entry;
    // 该目录下一个成员的部分信息
    // 来自 #include<dirent.h>

    // 来自 #include<sys/stat.h>
    // 存储某个成员的所有详细信息
    struct stat statbuf;

    if (!(dir = opendir(path)))
    { // 访问失败会返回0
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL)
    { // 抓取该目录下的文件
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        // 等价于sprintf, 只不过更加安全

        // stat 获取目录下文件的详细信息
        if (stat(full_path, &statbuf) == -1)
        { // 获取失败
            perror("stat");
            continue;
        }

        print_file_info(entry->d_name, &statbuf); // 输出文件的详细信息
    }
    closedir(dir); // 关闭文件流
}
/*
    程序的主函数部分
*/
int main(int argc, char *argv[])
{
    // argc 代表的是输入参数的数量
    //  argv代表的是输入的数据（根据空格分割成不同的一维字符数组）
    // printf("%s\n", argv[0]);
    if (argc < 2)
    {
        // 只有一个输入，即list命令
        chdir("..");chdir("..");chdir("..");chdir("..");chdir("..");chdir("..");chdir("..");chdir("..");chdir("..");chdir("..");
        //欸嘿嘿嘿嘿谢谢啦
        list_directory("."); // 默认列出当前目录
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            list_directory(argv[i]); // 依次列举输出
        }
    }

    return 0;
}