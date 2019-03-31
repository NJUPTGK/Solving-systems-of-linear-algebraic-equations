//解AX=B，A的列数要等于X的行数，X为1列；B的行数必须等于A的行数，列数1列
//A最大为100*100的矩阵
#include "stdafx.h"
#include<iostream>
using namespace std;
int temp, i, i2, j, k, judge, judge1;
class calculate
{
	public:
		int a[100][101], n, m;
		void swapxy(int x, int y);
		int gcd(int m, int n);
		void del(int l1, int l2, int code);
};
void calculate::swapxy(int x, int y)
{
	int k, temp;
	for (k = 0; k <= n; ++k)
	{
		temp = a[x][k];
		a[x][k] = a[y][k];
		a[y][k] = temp;
	}
}
int calculate:: gcd(int m, int n)
{
	return m % n ? gcd(n, m%n) : n;//递归，求m和n的最大公约数
}
void calculate:: del(int l1, int l2, int code)
{
	if (!a[l2][l1]) return;
	int g = gcd(a[l1][l1], a[l2][l1]);
	int p1 = a[l2][l1] / g;
	int p2 = a[l1][l1] / g;
	if (code == 0)
		for (int i = l1; i < n; ++i)
		{
			a[l1][i] *= p1;
			a[l2][i] *= p2;//得到最小公倍数
			a[l2][i] -= a[l1][i];//删除
		}
	else
		for (int i = l1; i >= 0; --i)
		{
			a[l1][i] *= p1;
			a[l2][i] *= p2;//得到最小公倍数
			a[l2][i] -= a[l1][i];//删除
		}
	a[l1][n] *= p1;
	a[l2][n] *= p2;
	a[l2][n] -= a[l1][n];//处理最后的元素
}


int main()
{
	calculate eg;
	do {
		cout << "欢迎来到线性方程组求解系统" << endl;
		cout << "**************************" << endl;
		cout << "*                        *" << endl;
		cout << "*                        *" << endl;
		cout << "*                        *" << endl;
		cout << "*                        *" << endl;
		cout << "**************************" << endl;
		cout << "请输入n(矩阵行数),m(矩阵列数),然后输入矩阵:" << endl;
		cin >> eg.n>>eg.m;
		while (eg.m <eg.n || eg.m > eg.n)
		{
			cout << "n(矩阵行数)和m(矩阵列数)应该相等，请重新输入！" << endl;
			cin >> eg.n >> eg.m;
		}


		//n是行数，m是列数
		for (i = 0; i < eg.n; ++i)
		{
			for (j = 0; j <= eg.m; ++j)
			{
				cin >> eg.a[i][j];
			}
		}	//初始化
		cout << "读取完成,计算中..." << endl;
		for (i = 0; i < eg.n; ++i)
		{
			if (eg.a[i][i] == 0)
			{
				for (i2 = i + 1; i2 < eg.n; ++i2)
				{
					if (eg.a[i2][i] != 0)
					{
						eg.swapxy(i, i2);
						i2 = eg.n + 1;
					}
				}
			}
			for (i2 = i + 1; i2 < eg.n; ++i2)
			{
				eg.del(i, i2, 0);//将第i2行化为0,消成上三角
			}
		}
		for (i = eg.n - 1; i >= 0; --i)
		{
			if (eg.a[i][i] == 0)//对角线的元素如果为0，要不无解，要不有无数个解
			{
				if (eg.a[i][eg.n] != 0)
				{
					cout << "该线性方程组无解" << endl;
					cout << "继续计算请输入1，退出请输入0:" << endl;
					cin >> judge1;
					if (judge1 == 1)
						continue;
					else
						return 0;
				}
				else
				{
					cout << "该线性方程组有无数个解" << endl;
					cout << "继续计算请输入1，退出请输入0:" << endl;
					cin >> judge1;
					if (judge1 == 1)
						continue;
					else
						return 0;
				}
			}
			else
				for (i2 = i - 1; i2 >= 0; --i2)
				{
					eg.del(i, i2, 1);//将第i2行化为0,消成对角线
				}
		}
		if (judge1 == 1)
			continue;
		cout << "输出该线性方程组的解:" << endl;
		for (i = 0; i < eg.n; i++)//打印结果
		{
			cout << "X" << i + 1 << "=" << 1.0*eg.a[i][eg.n] / eg.a[i][i] << endl;
		}
		cout << "继续计算请输入1，退出请输入0:" << endl;
		cin >> judge;
		if (judge == 0)
			return 0;
	} while (judge == 1 || judge1 == 1);
	return 0;
}
