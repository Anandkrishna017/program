#include <stdio.h>

int superSet[25], setA[25], setB[25];
int bitA[25], bitB[25];
int _union[25], _intersection[25], _difference[25];
int size, sizeA, sizeB;

void get_display(int arr[], int j, int size)
{
	int i;
	for(i = 0; i < size; i++)
		if(j)
			scanf("%d", &arr[i]);
		else
			printf("%d ", arr[i]);
}

int search(int ele)
{
	int i;
	for(i = 0; i < size; i++)
		if(superSet[i] == ele)
			return i;
	return -1;
}
void generate()
{
	int i, pos;
	for(i = 0; i < sizeA; i++)
	{
		pos = search(setA[i]);
		if(pos >= 0)
			bitA[pos] = 1;
	}
	for(i = 0; i < sizeB; i++)
	{
		pos = search(setB[i]);
		if(pos >= 0)
			bitB[pos] = 1;
	}	
	for(i = 0; i < size; i++)
		_union[i] = bitA[i] | bitB[i];
	for(i = 0; i < size; i++)
		_intersection[i] = bitA[i] & bitB[i];
	for(i = 0; i < size; i++)
		_difference[i] = bitA[i] & (!bitB[i]);
	printf("\nBit String representation of Set A:\t");
	get_display(bitA, 0, size);
	printf("\nBit String representation of Set B:\t");
	get_display(bitB, 0, size);
	printf("\nUnion Operation Result:\t");
	get_display(_union, 0, size);
	printf("\n");
	int sizeI = sizeof(_intersection)/sizeof(_intersection[0]);
	for(i = 0; i < sizeI; i++)
	{
	  if(_intersection[i] == 1)
	  {
	    printf("%d ", superSet[i]);
	    }
	}
	printf("\n");
	printf("\nIntersection Operation Result:\t");
	get_display(_intersection, 0, size);
	printf("\n");
	int sizeU = sizeof(_union)/sizeof(_union[0]);
	for(i = 0; i < sizeU; i++)
	{
	  if(_union[i] == 1)
	  {
	    printf("%d ", superSet[i]);
	    }
	}
	printf("\n");
	printf("\nDifference Operation Result:\t");
	get_display(_difference, 0, size);
}
void main()
{
	printf("Enter size of super set, set A and set B respectively: ");
	scanf("%d", &size);
	scanf("%d", &sizeA);
	scanf("%d", &sizeB);
	printf("Enter super set: ");
	get_display(superSet, 1, size);
	printf("Enter set A: ");
	get_display(setA, 1, sizeA);
	printf("Enter set B: ");
	get_display(setB, 1, sizeB);
	generate();
}

