#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define Str_Len 1000
#define Search_Str_Len 100

/*
 * 朴素算法的时间复杂度
 * 外层循环(N-M+1),内存循环M，因此O((N-M+1)*M)=O(N*M)
 * */

int native_search(char *init_str,char *base,unsigned int init_str_len,unsigned int base_len)  
{  
     int i,j;  
     i=0;j=0;  
 
     while(i<init_str_len)  
     {  
        if(init_str[i]!=base[j])  
        {  
            i=i-j+1;
	    j=0;
        }  
        else  
        {  
            i++;
	    j++;
        }  
        
        if(j==base_len)  
        {  
             return i-base_len;  
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
     
    index=native_search(init_str,search_str,init_str_len,search_len);
    printf("begin index of matched:%d\n",index);                    
    
    return 0;  
}  
