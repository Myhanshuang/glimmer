#include "../inc/head.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

void swap(char *a, char *b)
{
    char x = *a;
    *a = *b;
    *b = x;
}
void init(PointFixedNum *x)
{
    memset(x, 0, sizeof *x);
}

int findmax(PointFixedNum a, PointFixedNum b)//判断 a 和 b 的大小
{
    if(a.IntLenth > b.IntLenth) return 1;
    else if(a.IntLenth < b.IntLenth) return 0;
    else 
    {
        for(int i = 0; i < a.IntLenth; i ++)
        {
            if(a.IntNum[i] > b.IntNum[i])return 1;
            else if(a.IntNum[i] < b.IntNum[i]) return 0;
        }
        for(int i = 0; i < max(a.PointLenth, b.PointLenth); i ++)
        {
            if(a.PointNum[i] > b.PointNum[i])return 1;
            else if(a.PointNum[i] < b.PointNum[i]) return 0;
        }
    }
    return 1;
}

void transform(PointFixedNum *BeiChuShu, int base1, int base2) // transform BeiChuShu from base1 to base2
{
    PointFixedNum Shang, YuShu, temp = *BeiChuShu;
    init(& YuShu); init(& Shang);
    int now, posint, posdouble = 0;
    // 整数部分
    while (BeiChuShu->IntLenth > 0 && !(BeiChuShu->IntLenth == 1 && BeiChuShu->IntNum[0] == 0)) // 高精除低精，取余运算
    {
        now = 0;
        posint = 0;
        Shang.IntLenth = BeiChuShu->IntLenth;
        while (posint < BeiChuShu->IntLenth)
        {
            now = now * base1 + BeiChuShu->IntNum[posint];
            Shang.IntNum[posint] = now / base2;
            now %= base2;
            posint++;
        }
        // 一轮运算结束之后，商是倒序存储的
        YuShu.IntNum[YuShu.IntLenth++] = now; // 先取余是低位
        posint = 0;
        while (posint <= Shang.IntLenth && Shang.IntNum[posint] == 0)
            posint++; // 清除前导零
        init(BeiChuShu);
        for (int i = posint; i < Shang.IntLenth; i++) // 被除数 = 除数
            BeiChuShu->IntNum[BeiChuShu->IntLenth] = Shang.IntNum[i], BeiChuShu->IntLenth ++;
        init(&Shang);
    }
    reverseint(& YuShu);
    // 小数部分
    if (base1 == 2 && base2 == 10) // 2 to 10
    {
        PointFixedNum basicidx, bs, tt, res; // basicidx 是当前位要乘的，bs是恒为0.5
        init(& bs); init(& basicidx); init(&res);
        bs.PointLenth = 1;
        bs.PointNum[0] = 5;
        basicidx.IntLenth = 1;
        basicidx.IntNum[0] = 1;
        posdouble = 0;
        while (posdouble < temp.PointLenth)
        { // 高精求和
            multiply(basicidx, bs, &tt);
            basicidx = tt;
            // basicidx *= bs;
            init(&tt);
            int x = temp.PointNum[posdouble];
            if(x == 1)add(res, basicidx, &tt);
            else tt = res;
            res = tt;
            posdouble++;
        }
        YuShu.PointLenth = res.PointLenth;
        for (int i = 0; i < res.PointLenth; i++)
            YuShu.PointNum[i] = res.PointNum[i];
    }
    else if (base1 == 10) // 10 to any less than 10
    {
        PointFixedNum emptynum, tt; init( & tt);
        temp.IntLenth = 0;
        temp.IntNum[0] = 0;
        while (YuShu.PointLenth <= 32 && temp.PointLenth != 0)
        {
            tt.IntLenth = 1;
            tt.IntNum[0] = base2;
            multiply(tt, temp, &emptynum);
            // if want to get better to solve any over 10, change the two lines
            YuShu.PointNum[YuShu.PointLenth++] = emptynum.IntNum[0];
            emptynum.IntNum[0] = 0;
            emptynum.IntLenth = 1;
            temp = emptynum;
        }
    }
    else
        printf("i can't solve!!!!!!");
    if(base2 == 10)YuShu.jz = 'D';
    else if(base2 == 2)YuShu.jz = 'B';
    else ;
    init(BeiChuShu);
    *BeiChuShu = YuShu;
}

void reverseint(PointFixedNum *a)//翻转整数部分
{
    for (int i = 0; i < a->IntLenth / 2; i++)
    {
        char x = a->IntNum[a->IntLenth - i - 1];
        a->IntNum[a->IntLenth - i - 1] = a->IntNum[i];
        a->IntNum[i] = x;
    }
}

void reversedouble(PointFixedNum *a)//翻转小数部分
{
    for (int i = 0; i < a->PointLenth; i++)
    {
        char x = a->PointNum[a->PointLenth - i - 1];
        a->PointNum[a->PointLenth - i - 1] = a->PointNum[i];
        a->PointNum[i] = x;
    }
}

void reverse(char *a, int len)//翻转数组
{
    for (int i = 0; i < len; i++)
    {
        char x = *(a + len - i - 1);
        
        *(a + len - i - 1) = *(a + i);
        *(a + i) = x;
    }
}

int isop(char x)//是不是符号
{
    switch (x)
    {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 1;
    default:
        return 0;
    }
}

int isdig(char x)//是不是数字
{
    if (x >= '0' && x <= '9')
        return 1;
    return 0;
}