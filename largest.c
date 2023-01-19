#include <stdio.h>
int main()
{
int n;
int arr[100];
printf("enter the no:of elements:");
scanf("%d", &n);

for(int i = 0; i < n; i++)
{
printf("enter number:");
scanf("%d", &arr[i]);
}

for(int i = 1; i < n; ++i)
{

if(arr[0] < arr[i])
{
arr[0] = arr[i];
}
}

printf("largest element = %d", arr[0]);

return 0;
}
