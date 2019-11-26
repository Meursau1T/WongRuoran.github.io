---
layout: post
title:  "图像顺时针旋转90度"
date:   2019-11-26 00:00:01
categories: [算法]
---

**整体思路：**

1. 把矩阵看作一层层方框累加的产物，即4x4的矩阵是2x2的框和4x4的框的叠加、3x3的矩阵是1x1的框和3x3的框的叠加。于是主函数的思路为：

    1. 选中最外层的框

    2. 如果框不能继续缩小，结束旋转

    3. 用子函数r_in旋转该框

    4. 缩小框，重复2-4步

2. 要旋转一个框需要把四条边分别旋转到下一条边，而旋转一条边则需要旋转边上的（边长-1）个点。故而，r_in的思路为：

    1. 选取框的左上角顶点，储存至临时变量tmp

    2. 推出该点逆时针转90度后所在的位置，取其值覆盖刚刚选中的点

    3. 重复操作2，直到转到左上角顶点右旋90度的位置，用tmp赋值给此点

    4. 选择下一个点，重复1-3操作，直到遍历完整条边（不包括边的右端点）


~~~
class Solution {
public:
    void r_in(vector<vector<int>>& matrix,int n,int size,int i = 0){
        if(n == 1 || i == n-1){
            return;
        }
        int st = (size - n)/2;

        int temp = matrix[st][st+i];

        matrix[st][st+i] = matrix[st+n-1-i][st];
        matrix[st+n-1-i][st] = matrix[st+n-1][st+n-1-i];
        matrix[st+n-1][st+n-1-i] = matrix[st+i][st+n-1];
        matrix[st+i][st+n-1] = temp;

        return r_in(matrix,n,size,i+1);
    }
    void rotate(vector<vector<int>>& matrix) {
        int size = matrix.size();
        int n = size;
        while(n > 0){
            r_in(matrix,n,size,0);
            n -= 2;
        }

        cout << endl;
    }
};
~~~
