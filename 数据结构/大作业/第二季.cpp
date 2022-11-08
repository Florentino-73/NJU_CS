#include<iostream>
using namespace std;

/*
* 使用二叉搜索树，外层为n的循环，内层先插入一个新节点，再输出当前第k大的树
*/

//二叉搜索树节点
struct Node
{
    Node* left = nullptr;
    Node* right = nullptr;
    int val = -1;
    int left_num = 0;
    int right_num = 0;
};

int main()
{
    int m, n;
    cin >> m >> n;
    Node* root = nullptr;
    for (int i = 1; i <= n; i++)
    {
        Node* p = new Node;
        scanf("%d", &p->val);
        if (root == nullptr) //对第一个数做特判，因为第一个输出的数就是它本身
        {
            root = p;
            printf("%d ", p->val);
            continue;
        }

        // 插入新节点p
        Node* cur = root;
        while (true)
        {
            if (p->val > cur->val) //比当前节点值大, 那么插入到节点的右边
            {
                cur->right_num++;
                if (cur->right == nullptr) //右子树为空, 直接插入即可
                {
                    cur->right = p;
                    break;
                }
                else
                {
                    cur = cur->right;    //迭代, 插入到右子树
                }
            }
            else
            {
                cur->left_num++;
                if (cur->left == nullptr) //与插入到右边的过程类似
                {
                    cur->left = p;
                    break;
                }
                else
                {
                    cur = cur->left;
                }
            }
        }

        // 找第k大的数, 先计算一下k
        int k = i / m;
        if (k * m < i)
            k++;

        //找到并输出第k大的节点
        int larger = 0;
        cur = root;
        while (true)
        {
            if (cur->right_num + 1 + larger == k) //判断当前节点是不是第k大
            {
                printf("%d ", cur->val);
                break;
            }
            else if (cur->right_num + 1 + larger > k) //当前数不够大, 向右子树寻找
            {
                cur = cur->right;
            }
            else //当前数大了，向左子树寻找，larger记录了当前右边又多少比自己大的数
            {
                larger += cur->right_num + 1;
                cur = cur->left;
            }
        }
    }
    cout << endl;
    return 0;
}