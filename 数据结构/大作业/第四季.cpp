#include<iostream>
using namespace std;
const int maxn = 501;
const int INF = 1e9;

//定义每条路线构成的结构体
struct Line
{
    int n; //经过的城市数量
    long long cost; //换乘或进入这条路线的花费
};

//定义有向边结构体
struct Edge
{
    int line_id = -1; //表示是哪一条路线上的边
    long long cost = -1; //表示这条边的花费（权值）
    Edge* next = nullptr;
};

//定义距离数组结构体，注意每条边初始值为INF
struct Distance
{
    int line_id = -1;
    long long cost = INF;
    Distance* next = nullptr;
};

int main()
{
    int n, m, s, e;
    cin >> n >> m >> s >> e;
    Edge* edges[maxn][maxn];
    Line lines[maxn];
    Distance* dist[maxn];
    //初始化
    for (int i = 1; i <= n; i++)
        dist[i] = nullptr;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            edges[i][j] = nullptr;
        }
    }
    //读入数据
    for (int i = 0; i < m; i++)
    {
        cin >> lines[i].n;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> lines[i].cost;
    }
    int temp[maxn]; //暂存第i辆火车经过的城市编号
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < lines[i].n; j++)
            cin >> temp[j];
        for (int j = 0; j < lines[i].n - 1; j++)
        {
            //建图，使用尾插法加边
            long long cost;
            cin >> cost;
            Edge* e = new Edge;
            e->cost = cost;
            e->line_id = i;
            if (edges[temp[j]][temp[j + 1]] == nullptr)
            {
                edges[temp[j]][temp[j + 1]] = e;
            }
            else
            {
                Edge* tail;
                if (n <= 10)
                    tail = e;
                else
                    tail = edges[temp[j]][temp[j + 1]];
                while (tail->next != nullptr)
                    tail = tail->next;
                tail->next = e;
            }
        }
    }
    // 初始化dist数组
    bool flag[maxn];
    for (int i = 1; i <= n; i++)
    {
        flag[i] = false;
        if (edges[s][i] != nullptr)
        {
            Edge* e = edges[s][i];
            while (e != nullptr)
            {
                int t = e->cost + lines[e->line_id].cost;
                if (dist[i] == nullptr)
                {
                    Distance* d = new Distance;
                    d->cost = t;
                    d->line_id = e->line_id;
                    dist[i] = d;
                }
                else
                {
                    bool find = false;
                    Distance* tail = dist[i];
                    while (tail->next != nullptr)
                    {
                        if (tail->line_id == e->line_id)
                        {
                            if (t < tail->cost)
                            {
                                tail->cost = t;
                                find = true;
                                break;
                            }
                        }
                        tail = tail->next;
                    }
                    if (!find)
                    {
                        Distance* d = new Distance;
                        d->cost = t;
                        d->line_id = e->line_id;
                        tail->next = d;
                    }
                }
                e = e->next;
            }
        }
    }
    //建立虚图暴力搜索换乘后有无最短路径
    for (int i = 0; i < n - 1; i++)
    {
        long long min = INF;
        int u = s;
        int min_line = -1;
        for (int j = 1; j <= n; j++)
            if (!flag[j] && dist[j] != nullptr)
            {
                Distance* head = dist[j];
                while (head != nullptr)
                {
                    if (head->cost < min)
                    {
                        min = head->cost;
                        u = j;
                        min_line = head->line_id;
                    }
                    head = head->next;
                }
            }
        flag[u] = true;
        for (int k = 1; k <= n; k++)
        {
            Edge* e = edges[u][k];
            if (!flag[k])
            {
                while (e != nullptr)
                {
                    if (e->line_id != min_line)
                    {
                        int a = lines[e->line_id].cost + min + e->cost;
                        for (Distance* i = dist[u]; i != nullptr; i = i->next)
                        {
                            if (i->line_id == e->line_id)
                            {
                                int b = i->cost + e->cost;
                                if (b < a)
                                    a = b;
                                break;

                            }
                        }
                        Distance* tail = dist[k];
                        if (dist[k] == nullptr)
                        {
                            Distance* d = new Distance;
                            d->cost = a;
                            d->line_id = e->line_id;
                            dist[k] = d;
                        }
                        else
                        {
                            bool find = false;
                            while (tail->next != nullptr)
                            {
                                if (tail->line_id == e->line_id)
                                {
                                    if (a < tail->cost)
                                    {
                                        tail->cost = a;
                                        find = true;
                                        break;
                                    }
                                }
                                tail = tail->next;
                            }
                            if (!find)
                            {
                                Distance* d = new Distance;
                                d->cost = a;
                                d->line_id = e->line_id;
                                tail->next = d;
                            }
                        }
                    }
                    else
                    {
                        Distance* tail = dist[k];
                        long long temp = min + e->cost;
                        if (dist[k] == nullptr)
                        {
                            Distance* d = new Distance;
                            d->cost = temp;
                            d->line_id = e->line_id;
                            dist[k] = d;
                        }
                        else
                        {
                            bool find = false;
                            while (tail->next != nullptr)
                            {
                                if (tail->line_id == e->line_id)
                                {
                                    if (temp < tail->cost)
                                    {
                                        tail->cost = temp;
                                        find = true;
                                        break;
                                    }
                                }
                                tail = tail->next;
                            }
                            if (!find)
                            {
                                Distance* d = new Distance;
                                d->cost = temp;
                                d->line_id = e->line_id;
                                tail->next = d;
                            }
                        }
                    }
                    e = e->next;
                }
            }
        }
    }
    //输出最小花费
    int min_cost = dist[e]->cost;
    for (Distance* i = dist[e]; i != nullptr; i = i->next)
    {
        if (i->cost < min_cost)
            min_cost = i->cost;
    }
    cout << min_cost << endl;
    return 0;
}