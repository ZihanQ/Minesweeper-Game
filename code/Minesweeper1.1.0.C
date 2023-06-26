/*
    @Author: Zihan Qiu
    @Date: 2023.5.18
    @version: 1.1.0
*/

#include <stdio.h>
#include <string.h>
#define N 26
#define M 32

char mineField[N][M];
char gameField[N][M];
int row, col, mine;
int vis[N][M];

void initMine(void);                                                                // 输入处理1：记录雷区大小与雷数;
void initNum(void);                                                                 // 输入处理2：存储雷区布局;
void getOption(void);                                                               // 进行操作;
int leftButton(int x0, int y0);                                                     // 左键操作;
int rightButton(int op, int x0, int y0, int mineCount);                             // 右键操作(包含两种操作);
int close(int x, int y);                                                            // 关闭操作;
int doubleClick(int x0, int y0);                                                    // 双键操作;
int check(int op, int x0, int y0);                                                  // 功能组件：负责检查周围八格情况;
int fieldPrint(int flag, int opened, int needOpen, int optionCount, int mineCount); // 输出

int main(void)
{
    initMine();
    initNum();
    getOption();
    return 0;
}

void initMine(void)
{
    int size;
    scanf("%d", &size);
    const int initRow[4] = {0, 9, 16, 16}, initCol[4] = {0, 9, 16, 30}, initMine[4] = {0, 10, 40, 99};
    if (size == 4)
    {
        scanf("%d%d%d", &row, &col, &mine);
    }
    else
    {
        row = initRow[size];
        col = initCol[size];
        mine = initMine[size];
    }
}

void initNum(void)
{
    for (int i = 1; i <= row; i++)
        scanf("%s", mineField[i] + 1);
    for (int i = 1; i <= row; i++)
        for (int j = 1; j <= col; j++)
            gameField[i][j] = '.';
}

void getOption(void)
{
    // flag表示状态:0为游戏进行,1为结束;
    int optionCount = 0, temp = 0, mineCount = 0, flag = 0, needOpen = row * col - mine, opened = 0;
    int op, x, y;
    while (!flag)
    {
        optionCount++; // 操作次数
        scanf("%d%d%d", &op, &x, &y);
        // 三种操作：
        if (op == 1)
        {
            memset(vis, 0, sizeof(vis));
            temp = leftButton(x, y); // 0为踩雷,1为无效操作;
            if (temp == -1)
                flag = 1; // 失败
            else
                opened += temp;
        }
        else if (op == 2 || op == 3)
        {
            temp = rightButton(op, x, y, mineCount);
            if (temp == 2)
                mineCount++;
            else if (temp == 3)
                mineCount--;
        }
        else if (op == 4)
        {
            temp = close(x, y);
            if (temp == 1)
                mineCount--;
        }
        else
        {
            temp = doubleClick(x, y);
            if (temp == -1)
                flag = 1;
            else
                opened += temp;
        }
        flag = fieldPrint(flag, opened, needOpen, optionCount, mineCount);
    }
}

int leftButton(int x0, int y0)
{
    int mines = 0, total = 0;
    int dx[3] = {0, -1, 1}, dy[3] = {0, -1, 1};
    vis[x0][y0] = 1;

    if (gameField[x0][y0] != '.' && gameField[x0][y0] != '?')
        return 0;
    else if (mineField[x0][y0] == '*')
        return -1;

    mines = check(1, x0, y0);
    if (mines == 0)
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                int x = x0 + dx[i], y = y0 + dy[j];
                if (x <= row && x >= 1 && y <= col && y >= 1 && mineField[x][y] != '*' && !vis[x][y])
                {
                    int s = leftButton(x, y);
                    total += s;
                }
            }
    }
    gameField[x0][y0] = '0' + mines;
    total++;
    return total;
}

int rightButton(int op, int x0, int y0, int mineCount)
{
    char x = gameField[x0][y0];
    int temp = 0;
    if (x != '!' && x != '?' && x != '.')
        return 1;
    if (op == 2)
    {
        if (x == '!')
            temp = 1; // 无效操作;
        else
        {
            temp = 2;
            gameField[x0][y0] = '!';
        }
    }
    else if (op == 3)
    {
        if (x == '?')
            temp = 1; // 无效操作
        else if (x == '!')
            temp = 3;
        gameField[x0][y0] = '?';
    }
    return temp;
}

int close(int x, int y)
{
    int temp = 0;
    if (gameField[x][y] == '!')
        temp = 1;
    if (gameField[x][y] == '!' || gameField[x][y] == '?')
        gameField[x][y] = '.';
    return temp;
}

int doubleClick(int x0, int y0)
{
    int total = 0, sum = gameField[x0][y0] - '0', flag = 0;
    flag = check(2, x0, y0);
    if (flag != 1 || sum > 8 || sum < 0)
        return flag;
    int dx[3] = {0, -1, 1}, dy[3] = {0, -1, 1};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            int x = x0 + dx[i], y = y0 + dy[j];
            if (x <= row && x >= 1 && y <= col && y >= 1 && gameField[x][y] == '.')
            {
                int s = leftButton(x, y);
                total += s;
            }
        }
    return total;
}

int check(int op, int x0, int y0)
{
    int temp = 0, right = 0, mines = 0, flag = 0;
    const int dx[3] = {0, -1, 1}, dy[3] = {0, -1, 1};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            int x = x0 + dx[i], y = y0 + dy[j];
            if (x <= row && x >= 1 && y <= col && y >= 1)
            {
                if (mineField[x][y] == '*')
                    mines++;
                if (op == 2 && gameField[x][y] == '!')
                    temp++;
                if (op == 2 && gameField[x][y] == '!' && mineField[x][y] == '*')
                    right++;
            }
        }
    if (op == 1)
        return mines;
    if (right == mines)
        flag = 1; // 合法
    else if (mines == temp && right < mines)
        flag = -1; // 标错，游戏结束
    else
        flag = 0; // 标少，无效
    return flag;
}

int fieldPrint(int flag, int opened, int needOpen, int optionCount, int mineCount)
{
    // 三种状态：
    if (opened == needOpen)
    {
        flag = 2;
        printf("Game over, you win\n");
    }
    else if (flag == 0)
        printf("Game in progress\n");
    else if (flag == 1)
        printf("Hit mine, you lose\n");
    printf("%d %d\n", optionCount, mine - mineCount);
    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= col; j++)
        {
            if ((flag == 1 || flag == 2) && mineField[i][j] == '*')
                printf("*");
            else
                printf("%c", gameField[i][j]);
        }
        printf("\n");
    }
    return flag;
}
