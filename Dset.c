#include <stdio.h>
#include <stdlib.h>
int sets[10][25], size[10], n = 0;	
int find(int data)
{
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < size[i]; j++)
			if(data == sets[i][j])
				return i+1;
	return 0;
}
void create()
{
	int i;
	printf("Enter number of elements in set:\t");
	scanf("%d", &size[n]);
	printf("Enter the elements:\n");
	for(i = 0; i < size[n]; i++)
	{
		scanf("%d", &sets[n][i]);
		if(find(sets[n][i]) > 0)
		{
			printf("%d is already present in the disjoint set %d\n", sets[n][i], find(sets[n][i]));
			sets[n][i--] = 0;
		}
	}
	n++;
}
void union_(int i, int j)
{
	int _union[size[i] + size[j]], k=0, l;
	for(l = 0; l < size[i]; l++)
		_union[k++] = sets[i][l];
	for(l = 0; l < size[j]; l++)
		_union[k++] = sets[j][l];
	printf("The union set is: ");
	for(l = 0; l < k; l++)
		printf("%d ",_union[l]);
	printf("\n");	
}
void main()
{
	int choice, data, i, j;
	do {
		printf("1.Create a Set\t 2.Find element\t 3.Union (Press any other no. to exit)\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1: create();
					break;
			case 2: printf("Enter the element to find: ");
					scanf("%d", &data);
					if(find(data) > 0)
						printf("%d is present in the set %d\n", data, find(data));
					else
						printf("%d is not present in the disjoint sets\n", data);
					break;
			case 3: printf("Enter the two sets (1 for set 1, 2 for set 2...) :\n");
					scanf("%d %d", &i, &j);
					union_(i-1, j-1);
					break;
			default: exit(0);				
		}
	}while(1);
}
