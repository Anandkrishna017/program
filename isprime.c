#include<stdio.h>
#include <stdbool.h>
bool isPrime(int n)
{
if(n == 0 || n == 1)
{
return false;
}

if(n == 2 || n == 3)
{
return true;
}

for(int i = 5; i * i <= n; i = i+6)
{
if(n % i == 0)
{
return false;
}
}
return true;
}



int main()
{
int n;
printf("Enter the no:");
scanf("%d", &n);
if(isPrime(n))
{
printf("%d is a prime\n", n);
}
else
{
printf("%d is not a prime\n", n);
}

return 0;
}
