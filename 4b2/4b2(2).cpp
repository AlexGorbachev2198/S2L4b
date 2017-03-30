#include <Windows.h>
#include <conio.h>
#include <iostream>
using namespace std;
int main()
{
	HANDLE hEvent; 
	hEvent = OpenEvent(EVENT_ALL_ACCESS,TRUE,L"wow_such_threads");
	if (hEvent == 0)
	{
		cout << "Open error";
		_getch();
		return 0;
	}
	cout << "Press TAB button to run threads" << endl;
	while (!GetAsyncKeyState(VK_TAB)) {}
	_getch();
	SetEvent(hEvent); 
	cout << "Press space button to finish threads" << endl;
	while (!GetAsyncKeyState(VK_SPACE)) {}
	_getch();
	ResetEvent(hEvent);
	cout << "Press backspace button to close the application" << endl;
	while (!GetAsyncKeyState(VK_BACK)) {}
	_getch();
	return 0;
}
