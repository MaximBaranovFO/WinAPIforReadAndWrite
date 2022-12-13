#include <Windows.h>
#include <process.h>
#include <iostream>
#include "intOneTh.h"
using namespace std;

typedef struct  _STRUCT_DATA_
{
	int id; // used to identify the ticket id
	int tickets;
}_DATA, *_pDATA;

//CRITICAL_SECTION g_cs;
unsigned __stdcall Fun1(LPVOID lpParam);
unsigned __stdcall Fun2(LPVOID lpParam);
unsigned __stdcall Fun3(LPVOID lpParam);

int main()
{

	HANDLE hThread[3] = { NULL,NULL,NULL };
	unsigned threadid[3] = { 0 };
	_DATA stru_data;

	stru_data.id = 0;
	stru_data.tickets = 200;

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, Fun1, &stru_data, 0, &threadid[0]);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, Fun2, &stru_data, 0, &threadid[1]);
	hThread[2] = (HANDLE)_beginthreadex(NULL, 0, Fun3, &stru_data, 0, &threadid[2]);



        ClassInterfaceOneThreaded *someThOneInt;
		//someThOneInt->baseValForWndClass();
        someThOneInt->baseSomeThreadedWndClass();
	//InitializeCriticalSection(&g_cs);
	Sleep(4000);
	//LeaveCriticalSection(&g_cs);
    WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
}

unsigned __stdcall Fun1(LPVOID lpParam)
{
	_pDATA data = (_pDATA)lpParam;
	while (TRUE)
	{
		//EnterCriticalSection(&g_cs);
		if (data->tickets > 0)
		{
			Sleep(1);
			cout << "fun1: " << data->id++ ;
			cout << " *** thread 1 :sell ticket: " << data->tickets-- << endl;
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

unsigned __stdcall Fun2(LPVOID lpParam)
{
	_pDATA data = (_pDATA)lpParam;
	while (TRUE)
	{
		//EnterCriticalSection(&g_cs);
		if (data->tickets > 0)
		{
			Sleep(1);
			cout << "fun2: " << data->id++ ;
			cout << " === thread 2:sell ticket: " << data->tickets-- << endl;
		//	LeaveCriticalSection(&g_cs);
		}
		else
		{
			//LeaveCriticalSection(&g_cs);
			break;
		}
	}
	return 0;
}
unsigned __stdcall Fun3(LPVOID lpParam)
{
	_pDATA data = (_pDATA)lpParam;
	while (TRUE)
	{
		//EnterCriticalSection(&g_cs);
		if (data->tickets > 0)
		{
			Sleep(1);
			cout << "fun3: " << data->id++ ;
			cout << " === thread 3:sell ticket: " << data->tickets-- << endl;
		//	LeaveCriticalSection(&g_cs);
		}
		else
		{
			//LeaveCriticalSection(&g_cs);
			break;
		}

		//ClassInterfaceOneThreaded *someThOneInt;
		//someThOneInt->baseValForWndClass();
        //someThOneInt->baseSomeThreadedWndClass();
	}
	return 0;
}
