#include <iostream>
#include <Windows.h>
#include <random>
using namespace std;

volatile char track[50];
volatile int turtles[10] = { 0 };
volatile int finish = 0;
volatile int win = 0;

int Generate() {
    random_device rd;
    mt19937 gen(rd());
    return gen() % 3;
}

DWORD WINAPI Move(LPVOID param) {
    int id = (int)param;
    while (turtles[id] < 49) {
        int direction = Generate();
        turtles[id] += direction;

        if (turtles[id] > 49) {
            turtles[id] = 49;
        }

        Sleep(300);
    }
    finish++;
    return 0;
}

void show() {
    system("cls");
    for (int j = 0; j < 50; j++) {
        track[j] = '-';
    }
    for (int i = 0; i < 10; i++) { 
        if (turtles[i] < 50) {
            track[turtles[i]] = '0' + i; 
        }
    }
    for (int j = 0; j < 50; j++) {
        cout << track[j];
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    HANDLE hThread[10]; 
    DWORD IDThread[10];  
    for (int i = 0; i < 10; i++) { 
        hThread[i] = CreateThread(NULL, 0, Move, (LPVOID)i, 0, &IDThread[i]);
        if (hThread[i] == NULL) {
            return GetLastError();
        }
    }
    while (finish < 10) { 
        show();
        Sleep(300);
    }
    WaitForMultipleObjects(10, hThread, TRUE, INFINITE); 
    for (int i = 0; i < 10; i++) {
        CloseHandle(hThread[i]);
    }

    return 0;
}