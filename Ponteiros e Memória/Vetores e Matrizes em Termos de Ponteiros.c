#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void fillArray(int *array, int size);
void printArray(int arr[], int size);
void allocMatrix3D(int rows, int columns, int layers);
void fillMatrix(int ***matrix, int rows, int columns, int layers);
void printMatrix(int ***matrix, int rows, int columns, int layers);


int main()
{
	int size=0, rows=0, columns=0, layers=0;

	printf("Type array length: ");
	scanf("%d", &size);
	printf("Type 3d matrix dimentions length: ");
	scanf("%d %d %d", &rows, &columns, &layers);

	int vector[size], *array=NULL; // vector[] → *array, because both are pointers that point to a starting address
	if (size >= 1)
		array = (int *) malloc(size * sizeof(int));

	srand(time(NULL));

	fillArray(array, size);
	printf("\n");
	fillArray(vector, size);
	printf("\n");

	allocMatrix3D(rows, columns, layers);

	free(array);

	return 0;
}


void fillArray(int *arr, int size)
{
	if (size < 1)
		return;

	for (int i = 0; i < size; i++)
	{
		*(arr + i) = rand() % 50; // arr[+i] → *(arr + i), because it moves to the next allocated address
	}

	printArray(arr, size);
}

void printArray(int arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%d", arr[i]);

		if (i < (size - 1))
			printf(", ");
	}
	printf("\n");
}


void allocMatrix3D(int rows, int columns, int layers)
{
	if (rows < 1 || columns < 1 || layers < 1)
		return;

	int ***matrix = (int ***) malloc(rows * sizeof(int **));

	for (int i = 0; i < rows; i++)
	{
		matrix[i] = (int **) malloc(columns * sizeof(int *));
		for (int j = 0; j < columns; ++j)
		{
			matrix[i][j] = (int *) malloc(layers * sizeof(int));
		}
	}

	fillMatrix(matrix, rows, columns, layers);

	//free(matrix)	WRONG! First you need to release all elements, starting with the innermost layer
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; ++j)
		{
			free(matrix[i][j]);
		}
		free(matrix[i]);
	}
	free(matrix);
}

void fillMatrix(int ***matrix, int rows, int columns, int layers)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; ++j)
		{
			for (int k = 0; k < layers; ++k)
			{
				matrix[i][j][k] = *(*(*(matrix +i) +j) +k) = rand() % 10; // matrix[][][] → ***matrix
			}
		}
	}

	printMatrix(matrix, rows, columns, layers);
}

void printMatrix(int ***matrix, int rows, int columns, int layers)
{
	if (rows < 1 || columns < 1 || layers < 1)
		return;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; ++j)
		{
			for (int k = 0; k < layers; ++k)
			{
				printf("%d", matrix[i][j][k]);

				if (k < (layers - 1))
					printf(", ");
			}

			if (j < (columns - 1))
				printf(" | ");
		}

		printf("\n");
	}
}

