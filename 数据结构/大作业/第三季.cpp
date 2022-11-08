#include<iostream>
using namespace std;
const int N = 1005; //最大顶点数
const int INF = 1e9; //无穷大
int a[N][N], d[N], flag[N];

void init(int n) //初始化
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                a[i][j] = 0;
            else
                a[i][j] = INF;
        }
    }
}

void Dij(int n, int s) //单源最短通路问题
{
    //除源点以外所有点标记为0
    for (int i = 0; i < n; i++)
        flag[i] = 0;
    flag[s] = 1;

    for (int i = 0; i < n - 1; i++) //共执行n-1次，直到所有点都被标记
    {
        int min = INF;
        int v = 0;
        for (int j = 0; j < n; j++)
        {
            //找到未被标记的且d[j]值最小的顶点，记为v
            if (flag[j] == 0 && d[j] < min)
            {
                min = d[j];
                v = j;
            }
        }
        flag[v] = 1; //最后找到的这个点标记，之后遍历会跳过它
        for (int j = 0; j < n; j++)
        {
            //对于未被标记且满足三角不等式的顶点，更新数值
            if (flag[j] == 0 && d[v] + a[v][j] < d[j])
            {
                //d[j]表示s到j的距离，d[v]+a[v][j]表示s经v到j的距离
                d[j] = d[v] + a[v][j];
            }
        }
    }
}

int main()
{
    int n, m, s, e;
    cin >> n >> m >> s >> e;
    init(n);

    for (int i = 0; i < m; i++)
    {
        int p; //交通线途径国家数量
        cin >> p;
        int* b = new int[p];
        for (int j = 0; j < p; j++)
            cin >> b[j];
        for (int j = 0; j < p - 1; j++)
        {
            int time;
            cin >> time;
            a[b[j]][b[j + 1]] = min(a[b[j]][b[j + 1]], time); //避免重复输入

            //考略到是无向图，还要保持对称性
            int min_num = min(a[b[j]][b[j + 1]], a[b[j + 1]][b[j]]);
            a[b[j]][b[j + 1]] = min_num;
            a[b[j + 1]][b[j]] = min_num;
        }
    }

    //初始化距离数组
    for (int i = 0; i < n; i++)
        d[i] = a[s][i];

    //Dijkstra算法求源点s到其他点的最短通路
    Dij(n, s);

    //输出结果
    if (d[e] == INF)
        cout << -1 << endl; //不存在通路
    else
        cout << d[e] << endl;

    return 0;
}