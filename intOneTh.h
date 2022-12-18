#include <iostream>
#include <thread>
#include <process.h>
#include <windows.h>
#include "intOneSome.h"

using namespace std;
class ClassInterfaceOneThreaded {
public:
	void set_a(int val);
	int get_a(void);
	WNDCLASSEX baseValForWndClass(void);
    void baseThreadedWndClass(void);
    void baseSomeThreadedWndClass(void);
private:
	int a;
	WNDCLASSEX main = { 0 };
};
int ClassInterfaceOneThreaded::get_a(void) {
	return a;
}
void ClassInterfaceOneThreaded::set_a(int val) {
	a = val;
}
typedef struct  _STRUCT_DATA_THREADED_
{
	int id; // used to identify the ticket id
	int tickets;
}_DATATHREADED, *_pDATATHREADED;
unsigned __stdcall FunInterfaceThreaded(LPVOID lpParam)
{
	_pDATATHREADED dataThreaded = (_pDATATHREADED)lpParam;
	while (TRUE)
	{
		//EnterCriticalSection(&g_cs);
		if (dataThreaded->tickets > 0)
		{
			Sleep(1);
			cout << "funInterfaceThreaded: " << dataThreaded->id++ ;
			cout << " *** thread 1 Interface Threaded :sell ticket: " << dataThreaded->tickets-- << endl;
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
void ClassInterfaceOneThreaded::baseThreadedWndClass(void){
    const int THREAD_NUM = 5;
    HANDLE hThread[THREAD_NUM] = {NULL,NULL,NULL,NULL,NULL};
	unsigned threadid[THREAD_NUM] = { 0 };
	_DATATHREADED stru_dataThreaded;
	for (int i = 0; i < THREAD_NUM; i++)
	    hThread[i] = (HANDLE)_beginthreadex(NULL, 0, FunInterfaceThreaded, &stru_dataThreaded, 0, &threadid[i]);
	WaitForMultipleObjects(THREAD_NUM, hThread, TRUE, INFINITE);
}
void ClassInterfaceOneThreaded::baseSomeThreadedWndClass(void){
    X my_x;
    std::thread t(&X::do_lengthy_work, &my_x);
    t.join();
    baseThreadedWndClass();
}
WNDCLASSEX ClassInterfaceOneThreaded::baseValForWndClass(void){

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
