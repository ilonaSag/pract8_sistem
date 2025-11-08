
#include <iostream>
#include <Windows.h>
using namespace std;
volatile char turtles[5];
volatile char arr[50];
volatile int finish_turtle = 0;
int Generate() {
	return rand() % 3;
}
DWORD WINAPI Move(LPVOID ID) {
	int position = 0;
	while (true) {
		for (int i = 0; i < 5;i++) {
			if (turtles[position] >= 50)
				finish_turtle++;
		}
		if (finish_turtle == 5)
			break;
		int direction = Generate();
		turtles[position] += direction;
		Sleep(100);

	}
	return 0;
}
void show() {
	system("cls");
	for (int i = 0; i < 5; i++) {
		cout << "Черепаха " << i+1 << ":";
		for (int j = 0; j < 50;j++) {
			if (j == turtles[i])
				cout << '0';
			else
				cout << '-';
		}
		cout << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	srand(GetTickCount64());
	int inc = 1;
	HANDLE hThread[5];
	DWORD IDThread[5];
	for (int i = 0; i < 5;i++) {
		hThread[i] = CreateThread(NULL, 0, Move, (void*)(i+1), 0, &IDThread[i]);
		if (hThread[i] == NULL) return GetLastError();
	}
	while (finish_turtle!=5) {
		show();
		Sleep(1000);
	}
	for (int i = 0; i < 5; i++) {
		CloseHandle(hThread[i]);
	}
	return 0;
}
