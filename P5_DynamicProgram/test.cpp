/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  dynamic programing examples
 *
 *        Version:  1.0
 *        Created:  07/01/2016 02:33:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include <string>

using namespace std;

int dp[100];

int maxsubqueue_recur(int *a,int i,int len)
{
	if(i==0)
	{
		dp[i]=1;
		return std::max(dp[i],maxsubqueue_recur(a,i+1,len));
	}
	else
	{
		dp[i]=1;
		for(int j=0;j<i;j++)
		{
			if(a[j]<a[i]&&dp[j]+1>dp[i])
				dp[i]=dp[j]+1;
		}

		if(i==len) return dp[i];
		else return std::max(dp[i],maxsubqueue_recur(a,i+1,len));
	}

}

int maxsubqueue(int *a,int len,int *end_index)
{
	int d[len];
	memset(d,0,sizeof(d));
	int i,j;
	int max_len=0;

	d[0]=1;

	for(i=1;i<len;i++)
	{
		d[i]=1;
		for(j=0;j<i;j++)
		{
			if(a[j]<=a[i]&&d[j]+1>d[i])
				d[i]=d[j]+1;
		}

		if(d[i]>max_len)
		{
			*end_index=i;
			max_len=d[i];
		}
	}
	return max_len;
}

int main()
{
	int maxlen=100;
	int n;
	int array[maxlen];
	int end_index;
	cout<<"Input the length of Array:"<<endl;
	cin>>n;
	cout<<"Input the Array:"<<endl;
	for(int i=0;i<n;i++)
		cin>>array[i];

	cout<<"The array to deal with:"<<endl;
	for(int i=0;i<n;i++)
		cout<<array[i]<<" ";
	cout<<endl;

	int max_len=maxsubqueue(array,n,&end_index);
	
	cout<<"The Maxlen Subqueue:"<<max_len<<endl;
	for(int i=end_index-max_len+1;i<=end_index;i++)
		cout<<array[i]<<" ";
	cout<<endl;
	return 0;
}
