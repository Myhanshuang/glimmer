#include "../inc/head.h"

void solve_less(PointFixedNum a, PointFixedNum b, PointFixedNum *c)
{
    if (findmax(a, b)) // a > b
    {
        c->sign = 0;
        less(a, b, c);
    }
    else
    {
        less(b, a, c);
        c->sign = -1;
    }
}

void add(PointFixedNum a, PointFixedNum b, PointFixedNum *c) // ac
{
    memset(c, 0, sizeof(PointFixedNum)); // 你信吗，sizeof c 可是会死人的
    // 我忘记了没加 * 就是指针本身了我服了这东西搞死我了
    c->PointLenth = max(a.PointLenth, b.PointLenth);
    c->IntLenth = max(a.IntLenth, b.IntLenth) + 1;
    for (int i = c->PointLenth - 1; i >= 0; i--)
    {
        int t = (c->PointNum[i] + a.PointNum[i] + b.PointNum[i]);
        c->PointNum[i] = t % 10;
        if (i == 0)
            c->IntNum[0] = t / 10; // 放在0上，因为翻转
        else
            c->PointNum[i - 1] = t / 10;
    }
    while (c->PointLenth - 1 >= 0 && c->PointNum[c->PointLenth - 1] == 0)
        c->PointLenth--; // 去后0
    reverseint(&a);
    reverseint(&b);
    if (c->IntLenth - 1 > 32)
    {
        c->IntOverflow = 1;
        return;
    }
    for (int i = 0; i < c->IntLenth; i++) // 我要恨一辈子的局部变量/哭，这个-1我找了几百年
    {
        int t = c->IntNum[i] + a.IntNum[i] + b.IntNum[i];
        c->IntNum[i] = t % 10;
        c->IntNum[i + 1] = t / 10;
    }
    while (c->IntLenth >= 1 && c->IntNum[c->IntLenth - 1] == 0)
        c->IntLenth--;
    reverseint(c);
    c->jz = 'D';
}

void less(PointFixedNum a, PointFixedNum b, PointFixedNum *c) // ac
{
    //(|a| > |b|)
    memset(c, 0, sizeof *c);
    // 先小数，可能借位
    c->PointLenth = max(a.PointLenth, b.PointLenth);
    for (int i = c->PointLenth - 1; i >= 0; i--)
    {
        c->PointNum[i] = a.PointNum[i] - b.PointNum[i];
        if (c->PointNum[i] < 0 && i == 0)
        {
            a.IntNum[a.IntLenth - 1]--; // 数组最高位是最低位！
            c->PointNum[i] += 10;
        }
        else if (c->PointNum[i] < 0)
        {
            c->PointNum[i] += 10;
            a.PointNum[i - 1]--;
        }
    }
    while (c->PointLenth - 1 >= 0 && c->PointNum[c->PointLenth - 1] == 0)
        c->PointLenth--; // 去后0
    reverseint(&a);
    reverseint(&b);
    // 整数
    c->IntLenth = a.IntLenth;
    for (int i = 0; i < a.IntLenth; i++)
    {
        c->IntNum[i] = a.IntNum[i] - b.IntNum[i];
        if (c->IntNum[i] < 0)
            c->IntNum[i] += 10, a.IntNum[i + 1]--;
    }
    while (c->IntLenth >= 1 && c->IntNum[c->IntLenth - 1] == 0)
        c->IntLenth--;
    reverseint(c);
    c->jz = 'D';
}
// 向函数内传参的时候，一定检查参数的初始值是多少！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
void multiply(PointFixedNum a, PointFixedNum b, PointFixedNum *c) // ac
{
    // 把小数点去掉，直接乘起来再加回去小数点
    memset(c, 0, sizeof *c);
    char num1[100], num2[100], num3[200];
    // 去小数点
    for (int i = 0; i < a.IntLenth; i++)
        num1[i] = a.IntNum[i];
    for (int i = a.IntLenth; i < a.PointLenth + a.IntLenth; i++)
        num1[i] = a.PointNum[i - a.IntLenth];
    for (int i = 0; i < b.IntLenth; i++)
        num2[i] = b.IntNum[i];
    for (int i = b.IntLenth; i < b.PointLenth + b.IntLenth; i++)
        num2[i] = b.PointNum[i - b.IntLenth];

    // reverse(num1, a.PointLenth + a.IntLenth);
    // reverse(num2, b.PointLenth + b.IntLenth);
    // 局部变量，修改传址为什么不行？？？
    for (int i = 0; i < (a.PointLenth + a.IntLenth) / 2; i++)
        swap(&num1[i], &num1[a.PointLenth + a.IntLenth - i - 1]);

    for (int i = 0; i < (b.PointLenth + b.IntLenth) / 2; i++)
        swap(&num2[i], &num2[b.PointLenth + b.IntLenth - i - 1]);

    // 高精乘
    memset(num3, 0, sizeof num3);
    int len3 = b.PointLenth + b.IntLenth + a.PointLenth + a.IntLenth;
    for (int i = 0; i < a.PointLenth + a.IntLenth; i++)
    {
        for (int j = 0; j < b.PointLenth + b.IntLenth; j++)
        {
            int t = num3[i + j] + num1[i] * num2[j];
            num3[i + j] = t % 10;
            num3[i + j + 1] += t / 10;
        }
    }
    // 加小数点,划分整数小数
    int bg = 0, ed = len3 - 1;
    while (num3[bg] == 0 && bg < b.PointLenth + a.PointLenth) // 去零再反转
        bg++;
    for (int i = b.PointLenth + a.PointLenth - 1; i >= bg; i--)
    {
        c->PointNum[c->PointLenth++] = num3[i];
    }
    // reversedouble(c); why it do not work?????

    while (num3[ed] == 0 && ed > b.PointLenth + a.PointLenth)
        ed--; // 去零再反转
    for (int i = b.PointLenth + a.PointLenth; i <= ed; i++)
    {
        if (i - (b.PointLenth + a.PointLenth) > 32)
        {
            c->IntOverflow = 1;
            return;
        }
        c->IntNum[c->IntLenth++] = num3[i];
    }
    reverseint(c); // why it works?????

    c->jz = 'D';
    // 确定进制和符号
    if (a.sign == b.sign)
        c->sign = 0;
    else
        c->sign = -1;
}

void calculate(char op, int t1, int t2, PointFixedNum *temp) // 考虑符号的加减法
{
    if (op == '+')
    {
        if (num[t1].sign == num[t2].sign)
        {
            add(num[t1], num[t2], temp);
            temp->sign = num[t1].sign;
        }
        else
        {
            if (num[t1].sign == 0)
            {
                solve_less(num[t1], num[t2], temp);
            }
            else
            {
                solve_less(num[t2], num[t1], temp);
            }
        }
    }
    else // t1 - t2
    {
        if (num[t2].sign == -1 && num[t1].sign == 0)
        {
            num[t2].sign = 0;
            add(num[t1], num[t2], temp);
            temp->sign = 0;
        }

        else if (num[t2].sign == 0 && num[t1].sign == -1)
        {
            num[t1].sign = -1;
            add(num[t1], num[t2], temp);
            temp->sign = -1;
        }
        else if (num[t1].sign == -1 && num[t2].sign == -1)
        {
            num[t1].sign = num[t2].sign = 0;
            solve_less(num[t2], num[t1], temp);
        }
        else
        {
            solve_less(num[t1], num[t2], temp);
        }
    }
}