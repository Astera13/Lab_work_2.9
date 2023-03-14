#define _CRT_SECURE_NO_WARNINGS
/*Зинченко Данил
Вариант 5
Создать класс четырехугольник, члены класса – координаты 4-х точек.
Предусмотреть в классе методы проверки существования четырехугольника вычисления
и вывода сведений о фигуре – длины сторон, диагоналей, периметр, площадь.
Создать производный класс – параллелограмм, предусмотреть в классе проверку,
является ли фигура параллелограммом. Написать программу, демонстрирующую
работу с классом: дано N четырехугольников и M параллелограммов, найти среднюю
площадь N четырехугольников и параллелограммы наименьшей и наибольшей
площади.

Создать класс окружность с закрытым полем радиус. Предусмотреть в классе
методы вычисления и вывода сведений о фигуре – площади, длины окружности.
Добавить метод в класс окружность, который изменяет радиус в зависимости от
переданного описанного параллелограмма.
Добавить ассоциацию окружность вписана в параллелограмм. В выводе сведений о
параллелограмме выводить информацию об окружности.*/

#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>


using namespace std;

class Point {
public:

	int x, y;

	Point() {
		x = 0;
		y = 0;
	}

	Point(int _x, int _y) {
		x = _x;
		y = _y;
	}
	
	virtual ~Point() {};

	double to(Point _P1)
	{
		return sqrt((x - _P1.x) * (x - _P1.x) + (y - _P1.y) * (y - _P1.y));
	}
};

class Quadrangle
{

public:

	Point P1, P2, P3, P4;

	Quadrangle()
	{
		int x, y;
		cout << "Введите координаты первой вершины (через пробел): ";
		cin >> x >> y;
		P1 = Point(x, y);
		cout << "\n";
		cout << "Введите координаты второй вершины (через пробел): ";
		cin >> x >> y;
		P2 = Point(x, y);
		cout << "\n";
		cout << "Введите координаты третьей вершины (через пробел): ";
		cin >> x >> y;
		P3 = Point(x, y);
		cout << "\n";
		cout << "Введите координаты четвертой вершины (через пробел): ";
		cin >> x >> y;
		P4 = Point(x, y);
		cout << "\n";
	}

	virtual ~Quadrangle(){};

	bool existence();
	double square();
	double perimeter();
	double poluperimetr(Point P1, Point P2, Point P3);
	void info();
};

bool Quadrangle::existence() // провервка существования
{
	double dec1 = P1.to(P2) - (P2.to(P3) + P3.to(P4) + P4.to(P1));		//неисправимо из-за невозможности выведения универсальной формулы
	double dec2 = P2.to(P3) - (P1.to(P2) + P3.to(P4) + P4.to(P1));
	double dec3 = P3.to(P4) - (P2.to(P3) + P1.to(P2) + P4.to(P1));
	double dec4 = P4.to(P1) - (P2.to(P3) + P3.to(P4) + P1.to(P2));

	if ((dec1 >= 0) || (dec2 >= 0) || (dec3 >= 0) || (dec4 >= 0))
	{
		return false;
	}
	else
	{
		return true;
	}
}

double Quadrangle::poluperimetr(Point P1, Point P2, Point P3) {
	double p1 = (P1.to(P2) + P2.to(P3) + P1.to(P3)) / 2;
	return (sqrt(p1 * (p1 - P1.to(P2)) * (p1 - P2.to(P3)) * (p1 - P1.to(P3))));
}

double Quadrangle::square()
{
	return(poluperimetr(P1, P2, P3) + poluperimetr(P3, P4, P1));
}

double Quadrangle::perimeter()
{
	return (P1.to(P2) + P2.to(P3) + P3.to(P4) + P4.to(P1));
}

void Quadrangle::info()
{
	cout << "сторона 1 = " << P1.to(P2) << "\t" << "сторона 2 = " << P2.to(P3) << "\t" << "сторона 3 = " << P3.to(P4) << "\t" \
		<< "сторона 4 = " << P4.to(P1) << "\t" << "диагональ 13 = " << P1.to(P3) << "\t" << "диагональ 24 = " << P2.to(P4) << "\t" \
		<< "периметр = " << perimeter() << "\t" << "площадь = " << square() << "\n";
}

class Parallelogram;
class Circle
{
protected:

	Parallelogram* _p;

private:

	double r;

public:

	Circle()
	{
		r = 0;
		_p = 0;
	}

	virtual ~Circle(){};

	void parallelogram_sv(Parallelogram* _p);
	double crcl_square();
	double length();
	void info_circle();
	double get_radius();
	void set_radius(Point P1, Point P2, Point P3, Point P4);
};

void Circle::parallelogram_sv(Parallelogram* p)
{
	Circle::_p = p;
}

double Circle::crcl_square()
{
	return( M_PI * r * r);
}

double Circle::length()
{
	return (2 * M_PI * r);
}

void Circle::info_circle()
{
	cout << "Площадь:" << crcl_square() << "\t" << "Длина:" << length() << "\n";
}

double Circle::get_radius()
{
	return r;
}

void Circle::set_radius(Point P1, Point P2, Point P3, Point P4)
{
	if (P1.to(P2) == P3.to(P4))
	{
		r = (P1.to(P3) * P2.to(P4) / (4 * P1.to(P3)));
	}
}

class Parallelogram : public Quadrangle
{
protected:
	Circle* _r = NULL;
public:

	Parallelogram() {};

	virtual ~Parallelogram(){};

	void circle_sv(Circle* _r);
	bool existence_par();
	void info_par();
};

void Parallelogram::circle_sv(Circle* r)
{
	Parallelogram::_r = r;
}

bool Parallelogram::existence_par()
{
	if (P1.to(P3) * P1.to(P3) + P2.to(P4) * P2.to(P4) == P1.to(P2) * P1.to(P2) + P2.to(P3) * P2.to(P3) + P3.to(P4) * P3.to(P4) + P4.to(P1) * P4.to(P1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Parallelogram::info_par()
{
	cout << "сторона 1 = " << P1.to(P2) << "\t" << "сторона 2 = " << P2.to(P3) << "\t" << "сторона 3 = " << P3.to(P4) << "\t" \
		<< "сторона 4 = " << P4.to(P1) << "\t" << "диагональ 13 = " << P1.to(P3) << "\t" << "диагональ 24 = " << P2.to(P4) << "\t" \
		<< "периметр = " << perimeter() << "\t" << "площадь = " << square() << "\n";

	if (_r != NULL)
	{
		_r->info_circle();
	}

};

int main()
{
	int N, M; Quadrangle* A; Parallelogram* B; Circle* C; double Sum = 0, min = 1000000, max = 0;

	setlocale(LC_ALL, "Russian");

	cout << "Введите число четырехугольников: ";
	cin >> N;
	cout << "Введите число параллелограммов: ";
	cin >> M;

	A = new Quadrangle[N];
	B = new Parallelogram[M];
	C = new Circle[M];
	
	cout << "Четырехугольники: \n";

	for (int i = 0; i < N; i++)
	{
		cout << i + 1 << ".";
		if (A[i].existence() == true)
		{
			Sum = Sum + A[i].square();
			A[i].info();
		}
		if (A[i].existence() == false)
		{
			break;
		}
	}
	cout << "Средняя площадь четырехугольников: " << Sum / N << "\n";

	for (int i = 0; i < M; i++)
	{
		cout << i + 1 << ".";
		if (B[i].existence_par() == true)
		{

			C[i].set_radius(B[i].P1, B[i].P2, B[i].P3, B[i].P4);
			C[i].crcl_square();
			C[i].length();

			B[i].circle_sv(&C[i]);
			if (B[i].square() > max)
			{
				max = B[i].square();
				B[i].info_par();
			}
			if (B[i].square() < min)
			{
				min = B[i].square();
				B[i].info_par();
			}
		}
		if (B[i].existence_par() == false)
		{
			break;
		}
	}
	cout << "Максимальная площадь параллелограмма: " << max << "\n";
	cout << "Минимальная площадь параллелограмма: " << min << "\n";

}