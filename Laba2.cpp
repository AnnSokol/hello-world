#include <iostream>
#include <fstream>

using namespace std;

int** CrArr(int n, int m)//функция возвращает динамический массив заданных размеров
{
	int** arr = new int* [n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[m];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			arr[i][j] = 0;      //Заполняем массив нулями
		}
	}
	return arr;
}

void PrintArr(int** arr, int n, int m) //функция, которая выводит массив в консоль
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Arrsmf(int** ArrR, int** Arrsm, int r, bool b)//функция возвращает массив (матрицу) смежности
{
	for (int i = 0; i < r; i++)//заполняем массив единицами
	{

		if (b == true)
		{
			int i1 = ArrR[i][0] - 1;
			int j1 = ArrR[i][1] - 1;
			Arrsm[i1][j1] = 1;
		}
		else
		{
			int i1 = ArrR[i][0] - 1;
			int j1 = ArrR[i][1] - 1;
			Arrsm[i1][j1] = 1;
			Arrsm[j1][i1] = 1;
		}
	}


}

void Arrpow(int** ArrRast, int** Arrsm, int w) //алогиртм Флоид-Уоршера (для нахождения путей в массиве смежности)
{
	int sss = 1000000000;//Метка для массива(тоже самое бесконечности)	

	for (int i = 0; i < w; i++)//Находим вершины где нет путей 
	{
		for (int j = 0; j < w; j++)
		{
			if (Arrsm[i][j] == 0 && i != j)
				ArrRast[i][j] = sss;    //помечаем нулевые значения переменной, кроме основной диагонали
			else
				ArrRast[i][j] = Arrsm[i][j];

		}
	}

	for (int l = 0; l < w; l++) //алгортм марицы кратчайших расстояний
	{
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (ArrRast[i][l] + ArrRast[l][j] < ArrRast[i][j])
					ArrRast[i][j] = ArrRast[i][l] + ArrRast[l][j];
			}
		}
	}

	for (int i = 0; i < w; i++)//Возвращаем первоначальное значение помеченным элементам
	{
		for (int j = 0; j < w; j++)
		{
			if (ArrRast[i][j] == sss)
			{
				ArrRast[i][j] = 0;
			}
		}
	}
}

void Arrdostf(int** ArrDost, int** ArrRast, int w)
{
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if ((ArrRast[i][j] == 0) || (i == j))//Если элемент на главной диагонали или равен нулю
				ArrDost[i][j] = 1;				//присваиваем значение 1
			else ArrDost[i][j] = ArrRast[i][j];
		}
	}
}

void Pervchast(int w, int** Arrsm)
{
	int esmin = 0;//Минимальный эксцентриситет графа
	int esmax = 0;//Максимальный эксцентриситет графа
	int indx = 0;//Переменная размера массива индексов центров графа
	int* Arrstw = new int[w];//массив степеней вершин


	for (int i = 0; i < w; i++)
	{
		int t = 0;//временная переменная степени вершины графа
		for (int j = 0; j < w; j++)
		{
			if (Arrsm[i][j] == 1)//заполняем массив степеней графа
				t++;
		}
		Arrstw[i] = t;
	}
	for (int i = 0; i < w; i++)//вычисляем максимальный эксцентриситет
	{
		if (Arrstw[i] > esmax)
			esmax = Arrstw[i];
	}

	esmin = esmax;//присваиваем значение максимального эксцентриситета переменной минимального

	for (int i = 0; i < w; i++)//находим минимальный эксцентриситет
	{
		if (Arrstw[i] <= esmin)
		{
			esmin = Arrstw[i];
			indx++;
		}
	}


	int* Arrind = new int[indx];//массив индексов центров графа
	indx = 0;//переопределяем индекс

	for (int j = 0; j < w; j++)
	{
		if (Arrstw[j] == esmin)
		{
			Arrind[indx] = j + 1;
			indx++;
		}

	}
	////////////ВЫВОДИМ РЕЗУЛЬТАТ/////////////
	cout << "Диаметр графа - " << esmax << endl;
	cout << "Радиус графа - " << esmin << endl;
	cout << "Номера центров графа" << endl;
	for (int i = 0; i < indx; i++) //вывод всех элементов массива
	{
		cout << Arrind[i] << endl;
	}
	cout << endl;

	int indx1 = esmax - 1;
	int* Arrur = new int[indx1];
	for (int i = esmin; i <= esmax; i++)
	{
		cout << "Вершины яруса - " << i << endl;
		for (int j = 0; j < w; j++)
		{
			if (Arrstw[j] == i)
				cout << j + 1 << " ";
		}
		cout << endl;
	}
}

int main()
{

	setlocale(LC_ALL, "Russian");

	int n = 0;//кол-во строк в массиве и файле(кол-во ребер)
	int m = 2;//кол-во столбцов(вершины ребер графа)

	ifstream in("gr.txt");//создание файлового потока

	char* lines = new char[100];//массив строк файла
	ifstream base("gr.txt");
	while (!base.eof())         //подсчитываем кол-во строк в файле
	{
		base.getline(lines, 100, '\n');
		n++;
	}
	base.close();

	in.seekg(0, ios::beg);//переводим каретку в начало файла
	in.clear();

	int** Arr = CrArr(n, m);//массив для матрицы из ребер

	for (int i = 0; i < n; i++) //Заполняем массив данными из файла
	{
		for (int j = 0; j < m; j++)
		{
			in >> Arr[i][j];
		}
	}


	int w = Arr[0][0];//количество вершин графа
	int r = Arr[0][1];//количество ребер графа

	int** ArrR;//масив содержащий только ребра графа
	int x = n - 1;//кол-во строк в масииве ребер
	ArrR = CrArr(x, m);

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < m; j++)
		{
			ArrR[i][j] = Arr[i + 1][j];
		}
	}

	cout << "Введите часть лабораторной (1(не ориентированая) или 2(ориентированая))" << endl;
	int c;//Переменная номера части лабораторной
	cin >> c;
	bool b = false;
	if (c == 1)
	{
		b = false;
	}
	else if (c == 2)
	{
		b = true;
	}

	cout << "Массив ребер графа" << endl;
	PrintArr(ArrR, r, m);

	cout << "Матрица смежности" << endl;
	int** Arrsm = CrArr(w, w); //Матрица смежности (размер матрицы - кол-во вершин графа
	Arrsmf(ArrR, Arrsm, r, b);//Заполняем матрицу смежности
	PrintArr(Arrsm, w, w);//выводим в консоль матрицу

	cout << "Матрица расстояний" << endl;
	int** ArrRast = CrArr(w, w);//Матрица расстояний
	Arrpow(ArrRast, Arrsm, w);//заполняем матрицу расстояний
	PrintArr(ArrRast, w, w);//выводим в консоль матрицу

	cout << "Матрица доступности" << endl;
	int** ArrDost = CrArr(w, w);//Матрица доступности
	Arrdostf(ArrDost, ArrRast, w);//заполняем матрицу доступности
	PrintArr(ArrDost, w, w);//выводим матрицу в консоль

	if (b == false)//Диаметр, радиус, центр и ярусы графа(1ая часть)
	{
		Pervchast(w, Arrsm);
	}
	else
	{
		//Связность графа

		int* Arrstw = new int[w];//массив степеней вершин

		for (int i = 0; i < w; i++)
		{
			int t = 0;//временная переменная степени вершины графа
			for (int j = 0; j < w; j++)
			{
				if (Arrsm[i][j] == 1)//заполняем массив степеней графа
					t++;
			}
			Arrstw[i] = t;
		}
		int stwer = 0;//переменная считающая сколько вершин имеют степень - ноль
		for (int i = 0; i < w; i++)
		{
			if (Arrstw[i] == 0)
				stwer++;
		}
		if (stwer != 0)
			cout << "Граф не связный" << endl;


		int tempd = 1;//переменная подсчитывающая кол-во ячеек массива смежности с единицой
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (Arrsm[i][j] == 1)
					tempd++;
			}
		}
		int tempc = w * w;//количество ячеек массива
		if (tempc == tempd)
			cout << "Массив сильно связный" << endl;

	}
	cin.get();


}