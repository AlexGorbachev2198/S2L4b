#include <iostream>
#include <math.h>
#include <thread>
#include <mutex>
#include <Windows.h> 
using namespace std;
class Human_Parametrs
{
protected:
	double Weight;
	double Height;
public:
	Human_Parametrs();
	Human_Parametrs(double W, double H);
	double Get_W() { return Weight; }
	double Get_H() { return Height; }
	virtual double Index() = 0;
	~Human_Parametrs()
	{
		delete &Weight, &Height;
	}
	Human_Parametrs & operator =(Human_Parametrs& v2)
	{
		Weight = v2.Get_W();;
		Height = v2.Get_H();
		return *this;
	}
};
Human_Parametrs::Human_Parametrs(double W, double H)
{
	Weight = W;
	Height = H;
}
Human_Parametrs::Human_Parametrs()
{
	Weight = 0;
	Height = 0;
}
class Do_Bois : public Human_Parametrs
{
public:

	Do_Bois(double W, double H);
	Do_Bois();
	double Human_Parametrs::Index()
	{
		return 0.007184 * pow(Weight, 0.425)*pow(Height, 0.725);
	}
};
Do_Bois::Do_Bois(double W, double H) :
	Human_Parametrs(W, H) {}
Do_Bois::Do_Bois() :
	Human_Parametrs() {}
class Mosteller : public Human_Parametrs
{
public:
	Mosteller();
	Mosteller(double W, double H);
	double Human_Parametrs::Index()
	{
		return sqrt(Weight*Height / 3600);
	}
};
Mosteller::Mosteller(double W, double H) :
	Human_Parametrs(W, H) {}
Mosteller::Mosteller() :
	Human_Parametrs() {}
class Heycock : public Human_Parametrs
{
public:
	Heycock();
	Heycock(double W, double H);
	double Human_Parametrs::Index()
	{
		return 0.024265*pow(Weight, 0.5378)*pow(Height, 0.3964);
	}
};
Heycock::Heycock(double W, double H) :
	Human_Parametrs(W, H) {}
Heycock::Heycock() :
	Human_Parametrs() {}

HANDLE hEvent;
mutex mt;
void Print_Result(Human_Parametrs *obj)
{
	mt.lock();
	WaitForSingleObject(hEvent, INFINITE);
	cout << obj->Index() << endl;
	SetEvent(hEvent);
	mt.unlock();
}
int main()
{
	hEvent = CreateEvent(0, 1, 0, L"wow_such_threads");

	Do_Bois *a[3];
	a[0] = new Do_Bois(65, 187);
	a[1] = new Do_Bois(60, 180);
	a[2] = new Do_Bois(80, 192);

	Mosteller *b[3];
	b[0] = new Mosteller(65, 187);
	b[1] = new Mosteller(60, 180);
	b[2] = new Mosteller(80, 192);

	Heycock *c[3];
	c[0] = new Heycock(65, 187);
	c[1] = new Heycock(60, 180);
	c[2] = new Heycock(80, 192);


	for (unsigned int i = 0; i < 3; ++i)
	{
		thread t1(Print_Result, a[i]);
		thread t2(Print_Result, b[i]);
		thread t3(Print_Result, c[i]);
		t1.join();
		t2.join();
		t3.join();
	}

	system("pause");
	return 0;
}
