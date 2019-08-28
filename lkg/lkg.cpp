// lkg.cpp: ���������� ����� ����� ��� ����������� ����������.
//

//������
/* ������������� �������� ������������ ��������� (���), ��������� �������������� ����������� ��������� ( m = 4294967296, a = 982451653, c = 167 )
��������� �������������� ���
������� ����������� ��������� ������������������ (�������� ��������)*/

//���������� ����������
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <malloc.h>
#include <Windows.h> 

//��������� ����������, ������� ����� �����
unsigned long long x0, xn, m, a, c;

//���������� �������
//�������� ������� ��� ������ � �����������
//������ ����������
int find_period();
//�������� ����������
int find_power();
//������� ���������� ������ ''�������� ��-�������''
float hi_square();
//�������� �����-���������
float poker_crit();

//��������������� �������
//�������� ����������
int check_param();
//���������� ������������ ��� �����-��������
double calc_prob(int, int);

int main()
{
	//���������� ������� ���� 
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//��������� ���������� 
	int i=0;
	printf("\n��������� ��������� �����\n");
	printf("\nm = ");
	scanf_s("%lld", &m);
	printf("a = ");
	scanf_s("%lld", &a);
	printf("c = ");
	scanf_s("%lld", &c);
	/*m = 4294967296;
	a = 982451653;
	c = 167;*/
	//�������� ��������� ���������
	check_param();
	printf("\n�0 = ");
	scanf_s("%lld", &x0);
	//x0 = 19101997;
	while (i!=5)
	{
		printf("\n�������� ��������:\n1 ��������� ������ ����������\n2 ��������� �������� ����������\n3 ��������� ������� ���������� ������ ''�������� ��-�������''\n4 �������� �������� �����-���������\n5 ��������� �����\n");
		printf_s("������� ��� ���������� ��������: ");
		scanf_s("%d", &i);
		switch (i)
		{
		case 1:
			find_period();
			break;
		case 2:
			find_power();
			break;
		case 3:
			hi_square();
			break;
		case 4:
			poker_crit();
			break;
		case 5:	
			exit(0);
		default:
			printf_s("������ �������� ��� ��������\n");
		};
	}
}

//���������� �������
//��������
int find_period()
{
	int i;
	unsigned long long period = 0;
	//clock_t start, end;
	//start = time(NULL);
	xn = (x0*a + c) % m;
	do
	{
		xn = (xn*a + c) % m;
		period++;
	} while (xn != x0);
	//end = time(NULL);
	printf("������: %lld\n", (period + 1));
	//printf("����� ������: %f\n", difftime(end, start));
	return 0;
}
int find_power()
{
	int p = 0;
	int j = 0;
	unsigned long long b = a - 1;
	while ((b % 2) == 0)
	{
		p++;
		b=b/2;
	}
	j = 32 / p;
	printf("��������: %d\n", j);
	return 0;
}
float hi_square()
{
	int N = 20000;
	int k[51];
	int i;
	int j;
	int df = 50;
	float Xi = 0.0;
	xn = (x0* a + c) % m;
	for (j = 0; j<100; j++)
	{
		Xi = 0.0;
		for (i = 0; i<51; i++)
			k[i] = 0;
		for (i = 0; i < N; i++)
		{
			xn = (xn* a + c) % m;
			k[xn / ((m - 1) / 50)] = k[xn / ((m - 1) / 50)] + 1;
		}
		for (i = 0; i < 50; i++)
		{
			Xi = Xi + 1.0*(k[i] - N / df)*(k[i] - N / df) / (N / df);
		}
		printf(" %f\n", Xi);
	}
	return Xi;
}
float poker_crit()
{
	int S[5], A[5];
	double p[5] = { 1.0,1.0,1.0,1.0,1.0 };
	float h = 0.0;
	int i, g, j, s;
	xn = (x0*a + c);
	for (i = 0; i < 5; i++)
	{
		for (j = 5; j > i; j--)
		{
			p[i] = p[i] * j;
		}
		for (j = 0; j < 5; j++)
			p[i]= p[i]/5;
		p[i] = p[i]*calc_prob(5, 5 - i);
		printf(" %f", p[i]);
	}
	printf("\n");
	for (g = 0; g < 100; g++)
	{
		int A[5] = { 0 };
		int N = 20000;
		float h = 0.0;
		for (i = 0; i < N; i++)
		{
			int S[5] = { 0 };
			for (j = 0; j < 5; j++)
			{
				xn = (a*xn + c) % m;
				S[(xn) / ((m-1) / 5)] = S[(xn) / ((m-1) / 5)] + 1;
			}
			s = 4;
			for (j = 0; j < 5; j++)
			{
				if (S[j] == 0)
					s--;
			}
			A[4 - s] = A[4-s]+1;
		}
		for (i = 0; i < 5; i++)
		{
			h = h + 1.0*(A[i] - N * p[i])*(A[i] - N * p[i])/ (N * p[i]);
		}
		printf(" %f\n", h);
	}
	return(0);
}

//���������������
int check_param()
{
	int i;
	unsigned long long q, w;
	if (c != 0)
	{
		for (i = 2; i <= c; i++)
			if (c % i == 0)
			{
				printf("�������� � �� �������� ������� ������");
				main();
			}
			else
			{
				q = c;
				w = m;
				while (q && w)
				{
					if (q >= w)
					{
						q %= w;
					}
					else w %= q;
					if ((q || w) != 1)
					{
						printf("��������� M � � �� �������� ������� �������� �������");
						main();
					}
					else
					{
						q = a%c;
						if (q != 5)
						{
							printf("������� �� ������� � �� � �� ����� 5");
							main();
						}
						else
						{
							if ((a < 0.01 * m) || (0.99 * m < a))
							{
								printf("�������� � �� �������� � ������������ ����������");
								main();
							}
							else
							{
								if ((m / 4 == 0))
								{
									if ((a - 1) / 4 == 0)
									{
										printf("��������� �����");
										return 1;
									}
									else
									{
										printf("�������� A �� ��������");
										main();
									}
								}
								else
								{
									printf("��������� �����");
									return 1;
								}
							}
						}
					}
				}
			}
	}
}
double calc_prob(int k, int r)
{
	if (r == k) return 1;
	else
		if (k == 0) return 0;
		else
			if (r == 0) return 0;
			else
				return (calc_prob(k - 1, r - 1) + r*calc_prob(k - 1, r));
}