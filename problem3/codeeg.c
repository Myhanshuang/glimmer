// 通过滚动数组实现动态规划

int solve(int n) // before
{
    int f[100][2];
    for(int i = 1; i <= n ; i ++){
        for(int j = 1; j <= n ; j ++){
            f[i][j % 2] = max(f[i - 1][(j + 1) % 2] , f[i][(j + 1) % 2]);//意义不明的动态规划转移柿子
        }
    }
}

int solve(int n) // after
{
    int f[2][100];
    for(int i = 1; i <= n ; i ++){
        for(int j = 1; j <= n ; j ++){
            f[i % 2][j] = max(f[(i + 1) % 2][j] , f[(i + 1) % 2][j - 1]);
        }
    }
}

//解释：之前是一个 n * 2 的矩阵，而后变成了一个 2 * n 的矩阵
//在后者之中，数据的连续性更好，更能降低 Cache Miss 的发生概率

//(我之前还真的前面那么写的)