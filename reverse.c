#include<stdio.h>
int main()
{
int n,ld;
printf("enter the no:");
scanf("%d", &n);
int rev = 0;

while(n > 0)
{
ld = n % 10;
rev = rev * 10 + ld;
n = n/10;
}

printf("reversed no: %d\n",rev);
return 0;
} 
