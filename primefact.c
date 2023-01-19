#include <stdio.h>
int main()
{
 int i, j, num, flag;
 
 printf("enter the num:");
 scanf("%d", &num);
 
 printf("prime factors are: ");
 
 for(i = 2; i <= num; i++)
 {
  if(num % i == 0)
  {
    flag = 1;
    for(j = 2; j <= i/2; j++)
    {
     if(i % j == 0)
     {
       flag = 0;
       break;
     }
    }
    
    if(flag == 1)
    {
     printf("%d ", i);
    }
   } 
  }
 return 0;
 } 
