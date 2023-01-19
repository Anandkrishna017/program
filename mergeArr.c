#include <stdio.h>
void main()
{
int arr1[50],arr2[50],arr[100],i,j,k,n1,n2;
printf("enter n1, n2: ");
scanf("%d %d", &n1, &n2);
printf("enter the first array\n");
for(i = 0; i < n1; i++)
{
scanf("%d", &arr1[i]);
for(j = 0; j < i; j++)
{
if (arr1[j] > arr1[i])
{
int temp = arr1[j];
arr1[j] = arr1[i];
arr1[i] = temp;
}
}
}
printf("enter the second  array\n");
for(i = 0; i < n2; i++)
{
scanf("%d", &arr2[i]);
for(j = 0; j < i; j++)
{
if (arr2[j] > arr2[i])
{
int temp1 = arr2[j];
arr2[j] = arr2[i];
arr2[i] = temp1;
}
}
}

for(i = 0, j = 0, k = 0; i < n1 && j < n2; k++)
{
if(arr1[i] < arr2[j])
{
arr[k] = arr1[i++];
}
else
{
arr[k] = arr2[j++];;
}
}

while(i < n1)
{
arr[k++] = arr1[i++];
}
while(j < n2)
{
arr[k++] = arr2[j++];
}
printf("array1\n");
for(i = 0; i < n1; i++)
{
 printf("%d ", arr1[i]);
}
printf("\narray2\n");
for(i = 0; i < n2; i++)
{
 printf("%d ", arr2[i]);
}
printf("\nMerged array\n");

for(i = 0; i < n1+n2; i++)
{
 printf("%d ", arr[i]);
}
printf("\n");

}


