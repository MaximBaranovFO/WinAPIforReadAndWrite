#include <iostream>
#include <thread>
#include <process.h>
#include <windows.h>
#include "intTwoSome.h"

using namespace std;
class ClassInterfaceTwoThreaded {
public:
	void set_a(int val);
	int get_a(void);
	WNDCLASSEX baseValForWndClass(void);
    void baseTwoThreadedWndClass(void);
    void baseTwoSomeThreadedWndClass(void);
private:
	int a;
	WNDCLASSEX main = { 0 };
};
int ClassInterfaceTwoThreaded::get_a(void) {
	return a;
}
void ClassInterfaceTwoThreaded::set_a(int val) {
	a = val;
}
typedef struct  _STRUCT_DATA_TWO_THREADED_
{
	int id; // used to identify the ticket id
	int tickets;
}_DATATWOTHREADED, *_pDATATWOTHREADED;
unsigned __stdcall FunTwoInterfaceThreaded(LPVOID lpParam)
{
	_pDATATWOTHREADED dataTwoThreaded = (_pDATATWOTHREADED)lpParam;
	while (TRUE)
	{
		//EnterCriticalSection(&g_cs);
		if (dataTwoThreaded->tickets > 0)
		{
			Sleep(1);
			cout << "funInterfaceThreaded: " << dataTwoThreaded->id++ ;
			cout << " *** thread 1 Interface Threaded :sell ticket: " << dataTwoThreaded->tickets-- << endl;
			//LeaveCriticalSection(&g_cs);
		}
		else
		{
			//LeaveCriticalSection(&g_cs);
			break;
		}
	}
	return 0;
}
void ClassInterfaceTwoThreaded::baseTwoThreadedWndClass(void){
    const int THREAD_NUM = 5;
    HANDLE hThread[THREAD_NUM] = {NULL,NULL,NULL,NULL,NULL};
	unsigned threadid[THREAD_NUM] = { 0 };
	_DATATHREADED stru_dataThreaded;
	for (int i = 0; i < THREAD_NUM; i++)
	    hThread[i] = (HANDLE)_beginthreadex(NULL, 0, FunTwoInterfaceThreaded, &stru_dataThreaded, 0, &threadid[i]);
	WaitForMultipleObjects(THREAD_NUM, hThread, TRUE, INFINITE);
}
void ClassInterfaceTwoThreaded::baseTwoSomeThreadedWndClass(void){
    Xtwo my_xTwo;
    std::thread tTwo(&Xtwo::do_lengthy_work, &my_xTwo);
    tTwo.join();
}
WNDCLASSEX ClassInterfaceTwoThreaded::baseValForWndClass(void){

    //WNDCLASSEX::cbClsExtra;
    //WNDCLASSEX::cbSize;
    //WNDCLASSEX::cbWndExtra;
    //WNDCLASSEX::hbrBackground;
    //WNDCLASSEX::hCursor;
    //WNDCLASSEX::hIcon;
    //WNDCLASSEX::hIconSm;
    //WNDCLASSEX::hInstance;
    //WNDCLASSEX::lpfnWndProc;
    //WNDCLASSEX::lpszClassName;
    //WNDCLASSEX::lpszMenuName;
    //WNDCLASSEX::style;


	main.cbSize = sizeof(WNDCLASSEX);
	main.hInstance = GetModuleHandle(NULL);
	main.lpszClassName = TEXT("Main");
	main.lpfnWndProc = NULL;
	RegisterClassEx(&main);
	return main;
}
