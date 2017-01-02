#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define Str_Len 1000

#define Search_Str_Len 100

#define MAX_CHAR 1000
#define SIZE 256

#define MAX(x,y) (x)>(y)?(x):(y)

/*
 * 相比KMP算法的匹配是从模式串的开头开始匹配，BM算法从模式串的结尾开始匹配
 * 算法复杂度O(N)
 */

/*计算后缀数组
 * suff[i]就是求模式串中以i位置字符为后缀和以最后一个字符为后缀的公共后缀串的长度
 * 举例：
 * 模式串 b c a b a b a b
 * suff[] 1 0 0 2 0 4 0 8 
 * */

void suffix(char *pattern,int m,int suff[])
{
	int i,j;
	int k;
	suff[m-1]=m;
	for(i=m-2;i>=0;i--)
	{
		j=i;
		while(j>=0&&pattern[j]==pattern[m-1-i+j])
			j--;
		suff[i]=i-j;
	}
}

void suffix_opt(char *pattern,int m,int suff[])
{
	int f,g,i;
	suff[m-1]=m;
	g=m-1;
	for(i=m-2;i>=0;i--)
	{
		if(i>g&&suff[i+m-1-f]<i-g)
			suff[i]=suff[i+m-1-f];
		else
		{
			if(i<g)
				g=i;
			f=i;
			while(g>=0&&pattern[g]==pattern[g+m-1-f])
				g--;
			suff[i]=f-g;
		}

	}
}

/*
 * 计算坏字符数组bmBc[]
 * Case1:坏字符在模式串中有出现,则bmBC['v']表示字符v在模式串中最后一次出现的位置距离模式串串尾的长度
 * Case2:坏字符没有在模式串中出现，则bmBC['v']=模式串的长度
 * 右移的位数bmBc['v']-(m-1-i)=bmBc['v']-m+1+i
 * */

void PrebmBC(char *pattern,int m,int bmBc[])
{
	int i=0;
	for(i=0;i<256;i++)
		bmBc[i]=m;
	/*不包括最后一位字符的计算
	因为最后一个字符的的bmBc为0，右移的位数即0-m+1+i<=0,不合理*/
	for(i=0;i<m-1;i++)
	{
		bmBc[pattern[i]]=m-1-i;
	}
}

/*
 * 计算好后缀数组bmGs[]
 * Case1:模式串中有字串和好后缀完全匹配，则将最靠右的那个字串移动到好后缀的位置继续进行匹配
 * Case2:如果不存在和好后缀完全匹配的子串，则在好后缀中找到具有如下特征的最长子串，使得P[m-s...m]=P[0...s]
 * Case3:如果完全不存在和好后缀匹配的子串，则右移整个模式串
 * */

void PrebmGs(char *pattern,int m,int bmGs[])
{
	int i,j;
	int suff[SIZE];
	//计算后缀数组
	suffix(pattern,m,suff);

	//Case3
	for(i=0;i<m;i++)
		bmGs[i]=m;

	//Case2
	j=0;
	for(i=m-1;i>=0;i--)
	{
		if(suff[i]==i+1)
		{
			for(;j<m-1-i;j++)
			{
				if(bmGs[j]==m)
					bmGs[j]=m-1-i;
			}
		}
	}

	//Case1
	for(i=0;i<=m-2;i++)
		bmGs[m-1-suff[i]]=m-1-i;
}

void print(int *array,int n,char *arrayName)
{
	int i;
	printf("%s: \n",arrayName);
	for(i=0;i<n;i++)
		printf("%d ",array[i]);
	printf("\n");

}


int bm_search(char *init_str,char *pattern,int init_str_len,int pattern_len)  
{  
     int i,j;
     int bmBc[MAX_CHAR],bmGs[SIZE];
     PrebmBC(pattern,pattern_len,bmBc);
     PrebmGs(pattern,pattern_len,bmGs);

     j=0;
     while(j<=init_str_len-pattern_len)
     {
	     for(i=pattern_len-1;i>=0&&pattern[i]==init_str[i+j];i--);
	     if(i<0)
	     {
		     return j;
	     }
	     else
	     {
		     j+=MAX(bmBc[init_str[i+j]]-pattern_len+1+i,bmGs[i]);
	     }
     }

     return -1;
 
} 

int main()  
{  
    int i=0;
    char init_str[Str_Len];  
    int index=0;
    char search_str[Search_Str_Len];
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
    
    
    index=bm_search(init_str,search_str,init_str_len,search_len);

    printf("begin index of matched:%d\n",index);                    
    
    return 0;  
}  
