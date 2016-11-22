#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;

/*struct data
{
	int key[2];
};
struct linklist
{
	linklist *next;
	data value;
	linklist(data v,linklist *n):value(v),next(n){}
	~linklist() {if (next) delete next;}
};
void BucketSort(data *A,int N,int K,int y)
{
	linklist *Bucket[101],*p;//建立桶
	int i,j,k,M;
	M=K/100+1;
	memset(Bucket,0,sizeof(Bucket));
	for (i=1;i<=N;i++)
	{
		k=A[i].key[y]/M; //把A中的每个元素按照的范围值放入对应桶中
		Bucket[k]=new linklist(A[i],Bucket[k]);
	}
	
	for (k=j=0;k<=100;k++)
	{
		for (p=Bucket[k];p;p=p->next) j++;
		for (p=Bucket[k],i=1;p;p=p->next,i++)
			A[j-i+1]=p->value; //把桶中每个元素取出
		delete Bucket[k];
        }
}
void RadixSort(data *A,int N,int K)
{
        for (int j=1;j>=0;j--) //从低优先到高优先 LSD
		BucketSort(A,N,K,j);
}
int main()
{
	int N=100,K=1000,i;
	data *A=new data[N+1];
	for (i=1;i<=N;i++)
	{
		A[i].key[0]=rand()%K+1;
		A[i].key[1]=rand()%K+1;
	}
	
	RadixSort(A,N,K);
	
	for (i=1;i<=N;i++)
		printf("(%d,%d) ",A[i].key[0],A[i].key[1]);
	printf("\n");
	return 0;
}*/

//基数排序的主要思路:
//将所有待比较的数值统一为同样的位数长度，数位较短的数前面补0，然后从最低为开始依次进行一次稳定排序
//这样从最低位排序一直到到最高位排序完成以后，数列就变成一个有序序列
//使用桶排序
void Bucket_Sort(vector<int>&vec,int exp)
{
	vector<int> range(10,0);
	int length=vec.size();
	vector<int> temp_vec(length,0);
	int count=0;

	for(int i=0;i<length;i++)
	{
		range[(vec[i]/exp)%10]++;
	}

	for(int i=0;i<range.size();i++)
	{
		if(range[i]>0)
		{
			for(int j=0;j<range[i];j++)
			{
				temp_vec[count]=i;//通过i找不到原始的值，因此这里无法实现
				count++;
			}

		}
	}
	vec=temp_vec;
}

//使用计数排序
void Count_Sort(vector<int>&vec,int exp)
{
	vector<int> range(10,0);
	int length=vec.size();
	vector<int> temp_vec(length,0);

	for(int i=0;i<length;i++)
	{
		range[(vec[i]/exp)%10]+=1;
	}

	for(int i=1;i<range.size();i++)
		range[i]+=range[i-1];

	for(int i=length-1;i>=0;i--)
	{
		temp_vec[range[(vec[i]/exp)%10]-1]=vec[i];
		range[(vec[i]/exp)%10]--;
	}
	vec=temp_vec;
}


void Radix_Sort(vector<int>&vec,int max)
{
	for(int exp=1;max/exp>0;exp*=10)
	{
		Count_Sort(vec,exp);
	}
}

main ( int argc, char *argv[] )
{
	int i=0;
	int a[20];
	int length=0;
	int max=-1;
	printf("Input the element of Array(0 as input terminated):\n");
	
	do
	{
		scanf("%d",&a[i]);
	}while(a[i++]!=0);

	printf("the array ready to sort:\n");

	length=i-1;
	for(i=0;i<length;i++)
	{
		if(a[i]>max)
			max=a[i];
		printf("%d ",a[i]);
	}

	printf("\n");

	vector<int> vec(a,a+length);

	Radix_Sort(vec,max);

	printf("\nthe array sorted:\n");
	for(i=0;i<length;i++)
		printf("%d ",vec[i]);
	printf("\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
