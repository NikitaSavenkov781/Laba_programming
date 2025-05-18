#include <iostream>
#include <locale.h>
#include <typeinfo.h>

#include <cstdlib>
#include <ctime>

#define MAX_SIZE 10

using namespace std;

void set_array(float** array,int size)
{
	srand(time(NULL));
	
	
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			array[i][j] = (rand()%10000)*0.1-500;	
	}
}

void calculate_arr(float** array, int size)
{
	float summ = 0;
	float mult = 1;
	
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(array[i][j] < 0)
			{
				summ += array[i][j];
				mult *= array[i][j];
			}
		}	
	}
	if(mult != 1)
	{
		cout << "произведение отрицательных элементов = " << mult << endl;
		cout << "сумма отрицательных элементов = " << summ << endl;
	}
	else
		cout << "Нет отрицательных элементов" << endl;
}

int main()
{
	setlocale(LC_ALL,"russian");
	
	
	float inSize;
	int size;
	float** arr;
	
	while(true)
	{
		cout << "Введите размерность квадратной матрицы (целое число от 1 до 10): " << endl;

		cin >> inSize;
		 size = int(inSize);
		
		if(size >= 1 && size <= 10 && int(size) == inSize)
		{	
			break;
		}
	}
	
	arr = new float*[size];      
	for (int i = 0; i < size; ++i)
    	arr[i] = new float[size];
    	
	set_array(arr,size);
	
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			cout << " " << arr[i][j];
		cout << endl;	
	}
	
	calculate_arr(arr,size);
}
