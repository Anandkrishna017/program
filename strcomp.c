#include <stdio.h>

int compare(char a[], char b[])
{
 int flag = 0, i = 0, len1 = 0, len2 = 0;
 
 for(int j = 0; a[j] != '\0'; j++)
 {
  len1++;
 }
 for(int j = 0; b[j] != '\0'; j++)
 {
  len2++;
 }
 
 if(len1 != len2)
 {
  return 1;
 }
 while(a[i] != '\0' && b[i] != '\0')
 {
   if(a[i] != b [i])
   {
     flag = 1;
     break;
   }
   i++;
 }
 if (flag == 0)
 {
  return 0;
 }
 else 
 {
  return 1;
 }
}

int main()
{
 char str1[20], str2[20];
 printf("enter the first string: ");
 scanf("%s", str1);
 printf("enter the second string: ");
 scanf("%s", str2);
 
 int c = compare(str1, str2);
 
 if(c == 0)
 {
  printf("The strings are same\n");
 }
 else
 {
  printf("The strings are not same\n"); 
 }
 
 return 0;
 }
