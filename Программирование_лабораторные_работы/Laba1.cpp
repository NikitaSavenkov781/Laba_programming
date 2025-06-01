#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <ctime>

#define MAX_SIZE 10

using namespace std;

class Matrix {
private:
    float** array;
    int size;

public:
    Matrix(int size) : size(size)
	{
        array = new float*[size];
        for (int i = 0; i < size; ++i) 
		{
            array[i] = new float[size];
        }
    }

    ~Matrix() 
	{
        for (int i = 0; i < size; ++i) 
		{
            delete[] array[i];
        }
        delete[] array;
    }

    void set_array() 
	{
        srand(time(NULL));
        for (int i = 0; i < size; i++) 
		{
            for (int j = 0; j < size; j++) 
			{
                array[i][j] = (rand() % 10000) * 0.1f - 500;
            }
        }
    }

    void print_array()  
	{
        for (int i = 0; i < size; i++) 
		{
            for (int j = 0; j < size; j++)
			 {
                cout << " " << array[i][j];
            }
            cout << endl;
        }
    }

    void calculate_arr()  
	{
        float summ = 0;
        float mult = 1;
        bool has_negative = false;

        for (int i = 0; i < size; i++) 
		{
            for (int j = 0; j < size; j++) 
			{
                if (array[i][j] < 0)
				 {
                    summ += array[i][j];
                    mult *= array[i][j];
                    has_negative = true;
                }
            }
        }

        if (has_negative) 
		{
            cout << "Ïðîèçâåäåíèå îòðèöàòåëüíûõ ýëåìåíòîâ = " << mult << endl;
            cout << "Ñóììà îòðèöàòåëüíûõ ýëåìåíòîâ = " << summ << endl;
        } else {
            cout << "Íåò îòðèöàòåëüíûõ ýëåìåíòîâ" << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "russian");

    float inSize;
    int size;

    while (true) {
        cout << "Ââåäèòå ðàçìåðíîñòü êâàäðàòíîé ìàòðèöû (öåëîå ÷èñëî îò 1 äî 10): " << endl;
        cin >> inSize;
        size = int(inSize);

        if (size >= 1 && size <= 10 && size == inSize) {
            break;
        }
    }

    Matrix matrix(size);

    matrix.set_array();
    matrix.print_array();
    matrix.calculate_arr();

    return 0;
}
