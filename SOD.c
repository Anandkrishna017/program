#include <stdio.h>
int main()
{
 int num;
 printf("enter the num: ");
 scanf("%d", &num);
 
 int temp = num, rem, sum = 0;
 
 while(temp > 0)
 {
   rem = temp % 10;
   temp = temp /10;
   sum = sum + rem;
 }
 
 printf("sum of digits : %d", sum);
 
 return 0;
 }
