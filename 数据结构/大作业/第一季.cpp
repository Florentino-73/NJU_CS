#include<stdio.h>
using namespace std;

/*
//使用桶排序，对于一个元素个数为size，数据范围是(0-max)的数组A
//我们可以创建一个大小为max+1的辅助数组B[max+1]，每个元素B[i]表示值为i的数有几个
//从头遍历A，读取A[i]时对应的B[A[i]]值加一(类似于hash)
//从头遍历B，每个大于0的元素的下标即排序后A数组的值，元素大小即这个值的个数
//重新赋值给A，排序完成，时间复杂度O(n+m)
*/

void BucketSort(int* A, int max, int size)
{
    int* B = new int[max + 1];
    for (int i = 0; i < max + 1; i++)
    {
        //B数组初始化
        B[i] = 0;
    }
    int i, j, count = 0;
    for (i = 0; i < size; i++)
    {
        //遍历A数组，A数组每个元素作为下标，对应B数组中的元素+1
        B[A[i]] += 1;
    }
    for (i = 0; i <= max; i++)
    {
        //遍历B数组，此时下标即排序后A数组中的值，重新赋值到数组A中
        if (B[i] > 0)
        {
            for (j = 0; j < B[i]; j++)
            {
                A[count] = i;
                count++;
            }
        }
    }
}

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    int* A = new int[n];
    int max = 1; //记录数组A中的最大值，获取范围
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
        if (A[i] > max)
            max = A[i];
    }
    BucketSort(A, max, n);
    printf("%d", A[n - m]);
    return 0;
}