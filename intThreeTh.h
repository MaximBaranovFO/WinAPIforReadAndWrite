#include <iostream>
#include <thread>
#include <process.h>
#include <windows.h>
#include "intThreeSome.h"

using namespace std;
class ClassInterfaceThreeThreaded {
public:
	void set_a(int val);
	int get_a(void);
	WNDCLASSEX baseValForWndClass(void);
    void baseThreeThreadedWndClass(void);
    void baseThreeSomeThreadedWndClass(void);
private:
	int a;
	WNDCLASSEX main = { 0 };
};
int ClassInterfaceThreeThreaded::get_a(void) {
	return a;
}
void ClassInterfaceThreeThreaded::set_a(int val) {
	a = val;
}
typedef struct  _STRUCT_DATA_THREE_THREADED_
{
	int id; // used to identify the ticket id
	int tickets;
}_DATATHREETHREADED, *_pDATATHREETHREADED;
unsigned __stdcall FunThreeInterfaceThreaded(LPVOID lpParam)
{
	_pDATATHREETHREADED dataThreeThreaded = (_pDATATHREETHREADED)lpParam;
	while (TRUE)
	{
		//EnterCriticalSection(&g_cs);
		if (dataThreeThreaded->tickets > 0)
		{
			Sleep(1);
			cout << "funInterfaceThreaded: " << dataThreeThreaded->id++ ;
			cout << " *** thread 1 Interface Threaded :sell ticket: " << dataThreeThreaded->tickets-- << endl;
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
void ClassInterfaceThreeThreaded::baseThreeThreadedWndClass(void){
    const int THREAD_NUM = 5;
    HANDLE hThread[THREAD_NUM] = {NULL,NULL,NULL,NULL,NULL};
	unsigned threadid[THREAD_NUM] = { 0 };
	_DATATHREETHREADED stru_dataThreaded;
	for (int i = 0; i < THREAD_NUM; i++)
	    hThread[i] = (HANDLE)_beginthreadex(NULL, 0, FunThreeInterfaceThreaded, &stru_dataThreaded, 0, &threadid[i]);
	WaitForMultipleObjects(THREAD_NUM, hThread, TRUE, INFINITE);
}
void ClassInterfaceThreeThreaded::baseThreeSomeThreadedWndClass(void){
    Xthree my_xThree;
    std::thread tTwo(&Xthree::do_lengthy_work, &my_xThree);
    tTwo.join();
}

