#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define Str_Len 1000

#define Search_Str_Len 100

/*
 * 部分匹配表的产生
 * 部分匹配值是指匹配字符串的前缀和后缀最长的共有元素的长度
 * 前缀:除了最后一个字符外，一个字符串的全部头部组合
 * 后缀：除了第一个字符外，一个字符串的全部尾部组合
 */

/*
 * 对于给定的模式串:ABCDABD,它的最大长度表及next数组分别如下
 * 最大长度表:包括该字符在内的字符串前后缀最大公共元素长度
 * next数组:next[j]表示j索引之前的字符串中有多大长度的相同前缀后缀即将最大长度表右移1位得到
举例:
模式串       A  B  C  D  A  B  D
最大长度值   0  0  0  0  1  2  0
next数组     -1 0  0  0  0  1  2
优化后next   -1 0  0  0  -1 0  2

KMP算法的时间复杂度O(N+M)
 * */


int kmp_next(char *base,int next[])  
{  
    int k=-1;
    int j=0;
    next[0]=-1;
    int len=strlen(base);  
    while(j<len) 
    {
	//base[j]表示前缀 base[k]表示后缀
        if(k==-1||base[j]==base[k])
	{
		++k;
		++j;
		next[j]=k;
	}
	else
		k=next[k];
    }  
}  
  
//优化目的:模式串的base[j]不能等于base[next[j]]
int kmp_next_opt(char *base,int next[])  
{  
    int k=-1;
    int j=0;
    next[0]=-1;
    int len=strlen(base);  
    while(j<len-1) 
    {  
	    
        if(k==-1||base[j]==base[k])
	{
		++k;
		++j;
		if(base[j]!=base[k])
			next[j]=k;
		else
			next[j]=next[k];
	}
	else
		k=next[k];
    }  
}  
int kmp_search(char *init_str,char *base,int *next,int init_str_len,int base_len)  
{  
     int i,j;  
     i=0;j=0;  
 
     printf("init_str:%d %s\n",init_str_len,init_str);
     printf("search str:%d %s\n",base_len,base);

     while(i<init_str_len&&j<base_len)  
     {
	//如果j=-1或者当前字符匹配成功
        if(j==-1||init_str[i]==base[j])  
        {  
            i++;
	    j++;  
        }  
        else  
        { 
	    //相当于模式串右移j-next[j]
	    //即已匹配字符串-失配字符的上一位所对应的最大长度值,这里已匹配字符是j,next[j]代表后者
	    j=next[j];  
        }  
     }  

     if(j==base_len)  
     {  
	 printf("find the last index:%d\n",i);
         return i-j;  
     }  
     return -1;  
} 

int main()  
{  
    int i=0;
    char init_str[Str_Len];  
    int index=0;
    char search_str[Search_Str_Len];
    int next[Search_Str_Len];
    int search_len=0;
    int init_str_len=0;

    printf("Input Initial String:\n");
    gets(init_str);
    init_str_len=strlen(init_str);

    printf("Input Search String:\n");

    gets(search_str);
    search_len=strlen(search_str);
    
    printf("\ninit_str:%s len:%d\n",init_str,init_str_len);
    printf("search_str:%s len:%d\n",search_str,search_len);
    
    //kmp_next(search_str,next);
    kmp_next_opt(search_str,next);

    printf("\nCreate Partial Match Table\n");
    for(i=0;i<search_len;i++)
    {
        printf("%d ",next[i]);  
    }
    printf("\n");
    
    index=kmp_search(init_str,search_str,next,init_str_len,search_len);

    printf("begin index of matched:%d\n",index);                    
    
    return 0;  
}  
