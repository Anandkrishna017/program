#include <stdio.h>
int main()
{
int n;
printf("enter n");
scanf("%d", &n);
int f1=0, f2 = 1;
if(n == 1)
{
printf("%d\n",f1);
return 0;
}
if(n == 2)
{
printf("%d %d\n", f1, f2);
return 0;
}
printf("%d %d ", f1,f2);
for(int i = 3; i <= n; i++)
{
f2 = f1+f2;
f1 = f2-f1;
printf("%d ", f2);
}
printf("\n");
return 0;
}
