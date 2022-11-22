#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <Windowsx.h>
#include <process.h>
#include <tchar.h>
#include <commctrl.h>
#include "threadedWPone.h"
#include "threadedWPtwo.h"
#include "threadedWPthree.h"



#define THIS_CLASSNAME "E2 Tray Icon Demo Window"

    #define ID_ABOUT       2000

    #define ID_EXIT        2001

using namespace std;

    static BOOL g_bModalState = FALSE; //Is messagebox shown

UINT test_message = 0;
int countWalletWindow = 0;
int countSize = 0;
static bool isTrayCreateAndRun = false;
static char nowValAZ = 'a';
static bool isWndClassListEmpty = true;

static HWND hWndGlobal;
static UINT uIDGlobal;
static UINT uCallbackMsgGlobal;

static threadedWPone tmpThreadedWPone;
static threadedWPtwo tmpThreadedWPtwo;
static threadedWPthree tmpThreadedWPthree;

typedef std::map<char, WNDCLASSEX> ThreadedWndMap;
ThreadedWndMap iterTWM;

bool isMinWndClassCreated(void);
void setWndClass(char, WNDCLASSEX);
WNDCLASSEX getWndClass(char);
WNDCLASSEX initialWndClass(void);
void threadedChanges(NOTIFYICONDATA);
BOOL ShowPopupMenu(HWND, POINT, int);
void AddTrayIcon(HWND, UINT, UINT, UINT);
void RemoveTrayIcon(HWND, UINT);
unsigned int panelAddition(HWND, UINT, WPARAM, LPARAM);
unsigned int windowAddition(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK mouseKeyboardMove(HWND, UINT, WPARAM, LPARAM);
//long __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
LRESULT CALLBACK WindowProcedure(HWND window, UINT msg, WPARAM wp, LPARAM lp)
{

    tmpThreadedWPthree.doThreeThread();

    /*if (test_message == msg) {
        //printf("Got it !\n"); // to console
        std::cout <<"\nif msg:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id()<<" count of: "<<countSize
            <<" msg: "<<msg;
        return 0;
    }
    else {
            countSize++;
            std::cout <<"\nelse msg:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id()<<" count of: "<<countSize
            <<" msg: "<<msg;
            return DefWindowProc(window, msg, wp, lp);
    }*/

    panelAddition(window, msg, wp, lp);
    	// выборка и обработка сообщений
	switch (msg)
	{

    case WM_CREATE:
        // Вызывается, когда впервые создается окно
         return(0);

    case WM_PAINT:
         // Вызывается, когда окно обновляется
         return(0);
	case WM_LBUTTONUP:
		 // реакция на сообщение
		MessageBox(window, TEXT("Вы кликнули!"), TEXT("событие"), 0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);  // реакция на сообщение
		break;
	default:
	    mouseKeyboardMove(window, msg, wp, lp);

		// все сообщения не обработанные Вами обработает сама Windows
		return DefWindowProc(window, msg, wp, lp);
	}
	return 0;

}
static HWND window = NULL;
static HWND windowWal = NULL;
static HWND windowPanel1 = NULL;
static HWND windowPanel2 = NULL;
static HWND windowPanel3 = NULL;
static HWND windowWalPanel1 = NULL;
static HWND windowWalPanel2 = NULL;
static HWND windowWalPanel3 = NULL;
void SendMeMessage(HWND _window)
{
    window = _window;
    test_message = RegisterWindowMessage("TEST");
    PostMessage(window, test_message, 0, 0);
}
void SendWalMessage(HWND _windowWal)
{
    windowWal = _windowWal;
    test_message = RegisterWindowMessage("TEST wallet");
    PostMessage(windowWal, test_message, 0, 0);
}

unsigned int __stdcall mythread(void* data)
{



    const LPCSTR myclass = "myclass";

    TCHAR szWindowClass[]= "QWERTY";
    /*WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
        0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
        LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW + 1),
        0, myclass, LoadIcon(0,IDI_APPLICATION) };*/

        //InitCommonControls();

    //WNDCLASSEX wndclass = {0};
    WNDCLASSEX wndclass = initialWndClass();
    //wndclass.cbClsExtra
    //wndclass.cbSize
    //wndclass.cbWndExtra
    //wndclass.hbrBackground
    //wndclass.hCursor
    //wndclass.hIcon
    //wndclass.hIconSm
    //wndclass.hInstance
    //wndclass.lpfnWndProc
    //wndclass.lpszClassName
    //wndclass.lpszMenuName
    //wndclass.style

    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.lpszClassName = szWindowClass; // Имя класса окна
    wndclass.lpfnWndProc = WindowProcedure; // Функция окна
    wndclass.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Стандартная иконка
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL,IDC_ARROW); // Стандартный курсор
    wndclass.lpszMenuName = NULL; // Нет меню
    wndclass.cbClsExtra = 0; // Нет дополнительных данных класса
    wndclass.cbWndExtra = 0; // Нет дополнительных данных окна
    // Заполнение окна белым цветом
    wndclass.hbrBackground = (HBRUSH)(NULL_BRUSH);


    isMinWndClassCreated();

    isWndClassListEmpty = false;
    std::cout <<"\nRegisterClassEx:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();

    if (RegisterClassEx(&wndclass))
    {

        /**

        */
        /*window = CreateWindowEx(0, myclass, "title",
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle(0), 0);*/
        window = CreateWindowEx(WS_EX_WINDOWEDGE,
                              szWindowClass,
               _T("title"),
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT,0,CW_USEDEFAULT,0,
               NULL, (HMENU)NULL, GetModuleHandle(NULL), NULL);





        /*tmpThreadedWPone.Create(_T("oneThread"),
                                0,
                                0,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                GetModuleHandle(NULL),
                                (HMENU)NULL);*/

        windowPanel1 = CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME, _T("STATIC"), _T("Panel 1"),
               WS_CHILD|WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE|SS_SUNKEN,
               0, 0, 300,300, window,  (HMENU)NULL, GetModuleHandle(0), (LPVOID)NULL);
        windowPanel2 = CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME, _T("STATIC"), _T("Panel 2"),
               WS_CHILD|WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE|SS_SUNKEN,
               303, 0, 300,300, window,  (HMENU)NULL, GetModuleHandle(0), (LPVOID)NULL);
        windowPanel3 = CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME, _T("STATIC"), _T("Panel 3"),
               WS_CHILD|WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE|SS_SUNKEN,
               606, 0, 300,300, window,  (HMENU)NULL, GetModuleHandle(0), (LPVOID)NULL);

        if (window)
        {
            std::cout <<"\ntrue CreateWindowEx:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();
            SendMeMessage(window);
            ShowWindow(window, SW_SHOWDEFAULT);
            MSG msg;
            while (GetMessage(&msg, 0, 0, 0)) DispatchMessage(&msg);
        } else {
            std::cout <<"\nfalse CreateWindowEx:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();
            std::cout <<"\nGetLastError() returns: "<<GetLastError()<<"\n";
            MessageBox(NULL, _T("Create window failed!"), _T("Error!"), MB_OK | MB_ICONERROR);
        }
    } else {
        std::cout <<"\nfalse RegisterClassEx:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();
        std::cout <<"\nGetLastError() returns: "<<GetLastError()<<"\n";
    }
    //std::cout << "iterTWM.at('a') == " << iterTWM.at('a') << std::endl;
    WNDCLASSEX nowTmpWndclass = iterTWM.at('a');
    //nowTmpWndclass.cbClsExtra
    //nowTmpWndclass.cbSize
    //nowTmpWndclass.cbWndExtra
    //nowTmpWndclass.hbrBackground
    //nowTmpWndclass.hCursor
    //nowTmpWndclass.hIcon
    //nowTmpWndclass.hIconSm
    //nowTmpWndclass.hInstance
    //nowTmpWndclass.lpfnWndProc
    //nowTmpWndclass.lpszClassName
    //nowTmpWndclass.lpszMenuName
    //nowTmpWndclass.style
    return 0;
}
bool isMinWndClassCreated(void){
    WNDCLASSEX wndclassCreationTmp;
    char creationValOfChar = 'a';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'b';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'c';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'd';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'e';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'f';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'g';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'h';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'i';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'j';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'k';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'l';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'm';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'n';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'o';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'p';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'q';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'r';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 's';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 't';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'u';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'v';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'w';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'x';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'y';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    creationValOfChar = 'z';
    wndclassCreationTmp = initialWndClass();
    setWndClass(creationValOfChar,wndclassCreationTmp);
    if(true) return true;
    return false;
}
void setWndClass(char bukva, WNDCLASSEX wndClassInputed){
    iterTWM.insert(ThreadedWndMap::value_type(bukva,wndClassInputed));
}
WNDCLASSEX getWndClass(char bukva){
    return iterTWM.at(bukva);
}
int main()
{
    tmpThreadedWPtwo.doTwoThread();
    HANDLE myhandle;
    unsigned threadID;

    myhandle = (HANDLE)_beginthreadex(NULL, 0, &mythread, NULL, 0, &threadID);
    //do{
        //whait
    //}while(true);
    std::cout <<"this is work:\nHANDLE:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();

    WaitForSingleObject(myhandle, INFINITE);
    ReleaseMutex(myhandle);
    CloseHandle(myhandle);

    return 0;
}
LRESULT CALLBACK mouseKeyboardMove(HWND windowIn, UINT msgIn, WPARAM wpIn, LPARAM lpIn){
        // вычисление координат центра экрана
	    RECT screen_rect;
	    //GetWindowRect(GetDesktopWindow(),&screen_rect); // разрешение экрана
	    GetWindowRect(windowIn,&screen_rect);
	    int x = screen_rect.right / 2 - 150;
	    int y = screen_rect.bottom / 2 - 75;

	    POINT curPosIter;


	    if(msgIn == WM_RBUTTONDBLCLK)
            std::cout << "\nR***RBUTTONDBLCLK" <<" X "<< GET_X_LPARAM(lpIn) <<" Y "<< GET_Y_LPARAM(lpIn);
	    if(msgIn == WM_RBUTTONDOWN)
	        std::cout << "\nR---RBUTTONDOWN" <<" X "<< GET_X_LPARAM(lpIn) <<" Y "<< GET_Y_LPARAM(lpIn);
        if(msgIn == WM_RBUTTONUP){
            std::cout << "\nR+++RBUTTONUP" <<" X "<< GET_X_LPARAM(lpIn) <<" Y "<< GET_Y_LPARAM(lpIn);
            MessageBox(window, TEXT("Вы кликнули, RBUTTONUP!"), TEXT("событие"), 0);
            windowAddition(windowIn, msgIn, wpIn, lpIn);
            //ShowPopupMenu(windowIn, curPosIter, 0);


            //tmpThreadedWPone.setWndClass(tmpThreadedWPone.getBukva(),wndclassWal);
            //bool returnetdWal = tmpThreadedWPone.Create();
            tmpThreadedWPone.doOneThread();
            tmpThreadedWPone.doTwoThread();
        }

	    if(msgIn == WM_LBUTTONDBLCLK)
	        std::cout << "\nL***LBUTTONDBLCLK" <<" X "<< GET_X_LPARAM(lpIn) <<" Y "<< GET_Y_LPARAM(lpIn);
	    if(msgIn == WM_LBUTTONDOWN)
	        std::cout << "\nL---LBUTTONDOWN" <<" X "<< GET_X_LPARAM(lpIn) <<" Y "<< GET_Y_LPARAM(lpIn);
	    if(msgIn == WM_LBUTTONUP)
            std::cout << "\nL+++LBUTTONUP" <<" X "<< GET_X_LPARAM(lpIn) <<" Y "<< GET_Y_LPARAM(lpIn);

	        TOOLINFO ti = { 0 };
            ti.cbSize = TTTOOLINFO_V1_SIZE;
            ti.uFlags = TTF_SUBCLASS;
            ti.hwnd = windowIn;
            ti.hinst = GetModuleHandle(0);
            ti.lpszText = (TCHAR *)_T("This is Tooltip for Button.");
            GetClientRect(windowIn, &ti.rect);

             static bool bCreated = false;


             if(isTrayCreateAndRun){
        if(msgIn == WM_DESTROY){
            if(bCreated)
            {

            }
            PostQuitMessage(0);
        }
        if(msgIn == WM_CREATE){

            bCreated = true;
        }
             }
            int xPos = GET_X_LPARAM(lpIn);
            int yPos = GET_Y_LPARAM(lpIn);

	    countSize++;
            std::cout <<"\ndefault msg:Id this thread from C++ API: 0x"<< std::hex << std::this_thread::get_id()<<" count of: "<<countSize
            <<" msg: "<<msgIn<<"\n x: "<<x<<" left "<<ti.rect.left<<" right "<<ti.rect.right<<" X "<<xPos
            <<"\n y: "<<y<<" bottom "<<ti.rect.bottom<<" top "<<ti.rect.top<<" Y "<<yPos;



        return 0;
}
unsigned int windowAddition(HWND windowInPrev, UINT msgInPrev, WPARAM wpInPrev, LPARAM lpInPrev){

        if( countWalletWindow > 3 )
            return 0;

    countWalletWindow++;
    const LPCSTR myclass = "myclassWal";

    TCHAR szWindowClassWal[]= "wallet";
    /*WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
        0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
        LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW + 1),
        0, myclass, LoadIcon(0,IDI_APPLICATION) };*/

        //InitCommonControls();

    WNDCLASSEX wndclassWal = {0};

    //wndclass.cbClsExtra
    //wndclass.cbSize
    //wndclass.cbWndExtra
    //wndclass.hbrBackground
    //wndclass.hCursor
    //wndclass.hIcon
    //wndclass.hIconSm
    //wndclass.hInstance
    //wndclass.lpfnWndProc
    //wndclass.lpszClassName
    //wndclass.lpszMenuName
    //wndclass.style

    wndclassWal.cbSize = sizeof(WNDCLASSEX);
    wndclassWal.hInstance = GetModuleHandle(NULL);
    wndclassWal.lpszClassName = szWindowClassWal; // Имя класса окна
    wndclassWal.lpfnWndProc = WindowProcedure; // Функция окна
    wndclassWal.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
    wndclassWal.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Стандартная иконка
    wndclassWal.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wndclassWal.hCursor = LoadCursor(NULL,IDC_ARROW); // Стандартный курсор
    wndclassWal.lpszMenuName = NULL; // Нет меню
    wndclassWal.cbClsExtra = 0; // Нет дополнительных данных класса
    wndclassWal.cbWndExtra = 0; // Нет дополнительных данных окна
    // Заполнение окна белым цветом
    wndclassWal.hbrBackground = (HBRUSH)(NULL_BRUSH);


    getWndClass(nowValAZ);
    tmpThreadedWPone.setWndClass(tmpThreadedWPone.getBukva(),wndclassWal);
    std::cout <<"\nRegisterClassEx:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();

    if (RegisterClassEx(&wndclassWal))
    {

        std::string sCaption = "title wallet - " + countWalletWindow;
        /**
          HWND CreateWindowExA(
            [in]           DWORD     dwExStyle,
            [in, optional] LPCSTR    lpClassName,
            [in, optional] LPCSTR    lpWindowName,
            [in]           DWORD     dwStyle,
            [in]           int       X,
            [in]           int       Y,
            [in]           int       nWidth,
            [in]           int       nHeight,
            [in, optional] HWND      hWndParent,
            [in, optional] HMENU     hMenu,
            [in, optional] HINSTANCE hInstance,
            [in, optional] LPVOID    lpParam
          );
          WM_DESTROY
          BOOL DestroyWindow(
              [in] HWND hWnd
          );
        */
        /*window = CreateWindowEx(0, myclass, "title",
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle(0), 0);*/
        windowWal = CreateWindowEx(WS_EX_WINDOWEDGE,
                              szWindowClassWal,
               sCaption.c_str(),//_T("title wallet"),//countWalletWindow
               WS_OVERLAPPEDWINDOW | WS_SYSMENU,
               CW_USEDEFAULT,0,CW_USEDEFAULT,0,
               NULL, (HMENU)NULL, GetModuleHandle(NULL), NULL);


        windowWalPanel1 = CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME, _T("STATIC"), _T("Panel 1"),
               WS_CHILD|WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE|SS_SUNKEN,
               0, 0, 300,300, windowWal,  (HMENU)NULL, GetModuleHandle(0), (LPVOID)NULL);
        windowWalPanel2 = CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME, _T("STATIC"), _T("Panel 2"),
               WS_CHILD|WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE|SS_SUNKEN,
               303, 0, 300,300, windowWal,  (HMENU)NULL, GetModuleHandle(0), (LPVOID)NULL);
        windowWalPanel3 = CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME, _T("STATIC"), _T("Panel 3"),
               WS_CHILD|WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE|SS_SUNKEN,
               606, 0, 300,300, windowWal,  (HMENU)NULL, GetModuleHandle(0), (LPVOID)NULL);




        if (windowWal)
        {
            std::cout <<"\ntrue CreateWindowEx:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();
            SendWalMessage(windowWal);
            ShowWindow(windowWal, SW_SHOWDEFAULT);
            MSG msg;
            while (GetMessage(&msg, 0, 0, 0)) DispatchMessage(&msg);
        } else {
            std::cout <<"\nfalse CreateWindowEx:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();
            std::cout <<"\nGetLastError() returns: "<<GetLastError()<<"\n";
            MessageBox(NULL, _T("Create window wallet failed!"), _T("Error!"), MB_OK | MB_ICONERROR);
        }
    } else {
        std::cout <<"\nfalse RegisterClassEx:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();
        std::cout <<"\nGetLastError() returns: "<<GetLastError()<<"\n";
    }

    return 0;
}
WNDCLASSEX initialWndClass(void){
    SYSTEMTIME st, lt;

    GetSystemTime(&st);
    GetLocalTime(&lt);
    std::string initNameWndClass = "wndClassInitedAt"
        + st.wYear
        + st.wMonth
        + st.wDay
        + st.wHour
        + st.wMinute
        + st.wSecond
        + st.wMilliseconds;

    TCHAR szWindowClassWalInitial[]= "QWERTY";
    WNDCLASSEX wndclassWalInitial = {0};

    //wndclass.cbClsExtra
    //wndclass.cbSize
    //wndclass.cbWndExtra
    //wndclass.hbrBackground
    //wndclass.hCursor
    //wndclass.hIcon
    //wndclass.hIconSm
    //wndclass.hInstance
    //wndclass.lpfnWndProc
    //wndclass.lpszClassName
    //wndclass.lpszMenuName
    //wndclass.style

    wndclassWalInitial.cbSize = sizeof(WNDCLASSEX);
    wndclassWalInitial.hInstance = NULL;
    wndclassWalInitial.lpszClassName = initNameWndClass.c_str(); // Имя класса окна
    wndclassWalInitial.lpfnWndProc = WindowProcedure; // Функция окна
    wndclassWalInitial.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
    wndclassWalInitial.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Стандартная иконка
    wndclassWalInitial.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wndclassWalInitial.hCursor = LoadCursor(NULL,IDC_ARROW); // Стандартный курсор
    wndclassWalInitial.lpszMenuName = NULL; // Нет меню
    wndclassWalInitial.cbClsExtra = 0; // Нет дополнительных данных класса
    wndclassWalInitial.cbWndExtra = 0; // Нет дополнительных данных окна
    // Заполнение окна белым цветом
    wndclassWalInitial.hbrBackground = (HBRUSH)(NULL_BRUSH);
    return wndclassWalInitial;
}
unsigned int panelAddition(HWND windowInPanel, UINT msgInPanel, WPARAM wpInPanel, LPARAM lpInPanel){
          switch (msgInPanel) {



        case WM_CREATE:

          hWndGlobal = windowInPanel;
          uIDGlobal = 1;
          uCallbackMsgGlobal = WM_APP;
          AddTrayIcon( windowInPanel, 1, WM_APP, 0 );

          return 0;



        case WM_CLOSE:

          RemoveTrayIcon (windowInPanel, 1);

          PostQuitMessage(0);                                 //Sends WM_QUIT message

          return DefWindowProc( windowInPanel, msgInPanel, wpInPanel, lpInPanel ); //Calls WM_DESTROY



        case WM_COMMAND:

          switch (LOWORD(wpInPanel)) {

            if ( g_bModalState ) { return 1; }



            case ID_ABOUT:

              g_bModalState = TRUE;

              MessageBox( windowInPanel, TEXT("Hi!"), TEXT("Title"), MB_ICONINFORMATION | MB_OK );

              g_bModalState = FALSE;

              return 0;



            case ID_EXIT:

              PostMessage( windowInPanel, WM_CLOSE, 0, 0 );

              return 0;

          }

          return 0;



        case WM_APP:

          switch (lpInPanel) {



            case WM_LBUTTONDBLCLK:

              MessageBox( windowInPanel, TEXT("Hi!"), TEXT("Title"), MB_ICONINFORMATION | MB_OK );

              return 0;



            case WM_RBUTTONUP:

              SetForegroundWindow( windowInPanel );


              //ShowPopupMenu(windowInPanel, NULL, -1 );
              /**/
                  const int IDM_SUDARCHIVE = 300;
                  const int IDM_ABOUT = 250;
                  const int IDM_YANDEX = 150;
                  const int IDM_GOOGLE = 200;
                  const int IDM_EXIT = 100;

                    POINT pt;
                    GetCursorPos(&pt);

                    HMENU hmenu = CreatePopupMenu();
                    InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING, IDM_ABOUT, _T("О программе"));
                    InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING, IDM_SUDARCHIVE, _T("Суд Архив"));
                    InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING, IDM_YANDEX, _T("Яндекс"));
                    InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING, IDM_GOOGLE, _T("Google"));
                    InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING, IDM_EXIT, _T("Выход"));

                    SetForegroundWindow(windowInPanel);

                    int cmd = TrackPopupMenu(hmenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN | TPM_NONOTIFY | TPM_RETURNCMD, pt.x, pt.y, 0, windowInPanel, NULL);

                    PostMessage(windowInPanel, WM_NULL, 0, 0);

                    if (cmd == IDM_ABOUT)
                    {
                        MessageBox( windowInPanel, TEXT("POPup Hi, about!"), TEXT("POPup Title 1"), MB_ICONINFORMATION | MB_OK );
                    }
                    if (cmd == IDM_YANDEX)
                    {
                        MessageBox( windowInPanel, TEXT("POPup Hi, yandex!"), TEXT("POPup Title 2"), MB_ICONINFORMATION | MB_OK );
                        ShellExecute(0, 0, "http://www.yandex.ru", 0, 0 , SW_SHOW );
                    }
                    if (cmd == IDM_GOOGLE)
                    {
                        MessageBox( windowInPanel, TEXT("POPup Hi, google!"), TEXT("POPup Title 3"), MB_ICONINFORMATION | MB_OK );
                        ShellExecute(0, 0, "http://www.google.com", 0, 0 , SW_SHOW );
                    }
                    if (cmd == IDM_SUDARCHIVE)
                    {
                        MessageBox( windowInPanel, TEXT("POPup Hi, archive!"), TEXT("POPup Title 5"), MB_ICONINFORMATION | MB_OK );
                        ShellExecute(0, 0, "https://sudrf.cntd.ru/search?query&number=2-1802%2F2010", 0, 0 , SW_SHOW );
                    }
                    if (cmd == IDM_EXIT)
                    {
                        MessageBox( windowInPanel, TEXT("POPup Hi and bye!"), TEXT("POPup Title 4"), MB_ICONINFORMATION | MB_OK );
                    }
              /**/

              PostMessage( windowInPanel, WM_APP + 1, 0, 0 );

              return 0;

          }

          return 0;



      }



      return DefWindowProc( windowInPanel, msgInPanel, wpInPanel, lpInPanel );

}
//===================================================================================

    //ShowPopupMenu

    //===================================================================================

    BOOL ShowPopupMenu( HWND hWnd, POINT *curpos, int wDefaultItem ) {





      //ADD MENU ITEMS.------------------------------------------------------------------

      HMENU hPop = CreatePopupMenu();

      if ( g_bModalState ) { return FALSE; }

      InsertMenu( hPop, 0, MF_BYPOSITION | MF_STRING, ID_ABOUT, "About..." );

      InsertMenu( hPop, 1, MF_BYPOSITION | MF_STRING, ID_EXIT , "Exit" );



      //CAN DO WITHOUT STUFF.------------------------------------------------------------

      SetMenuDefaultItem( hPop, ID_ABOUT, FALSE );

      SetFocus          ( hWnd );

      SendMessage       ( hWnd, WM_INITMENUPOPUP, (WPARAM)hPop, 0 );



      //SHOW POPUP MENU.-----------------------------------------------------------------

      {

        //GET CURSOR POSITION TO CREATE POPUP THERE.-------------------------------------

        POINT pt;

        if (!curpos) {

          GetCursorPos( &pt );

          curpos = &pt;

        }



        {

          //DISPLAT MENU AND WAIT FOR SELECTION.-----------------------------------------

          WORD cmd = TrackPopupMenu( hPop, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD | TPM_NONOTIFY, curpos->x, curpos->y, 0, hWnd, NULL );



          //SEND MESSAGE MAPPED TO SELECTED ITEM.----------------------------------------

          SendMessage( hWnd, WM_COMMAND, cmd, 0 );

        }

      }



      DestroyMenu(hPop);



      return 0;

    }



    //===================================================================================

    //RemoveTrayIcon

    //===================================================================================

    void RemoveTrayIcon( HWND hWnd, UINT uID ) {

      NOTIFYICONDATA  nid;

                      nid.hWnd = hWnd;

                      nid.uID  = uID;



      Shell_NotifyIcon( NIM_DELETE, &nid );

    }



    //===================================================================================

    //AddTrayIcon

    //===================================================================================

    void AddTrayIcon( HWND hWnd, UINT uID, UINT uCallbackMsg, UINT uIcon ) {



      //CREATE SYSTEN TRAY ICON.---------------------------------------------------------------------

      NOTIFYICONDATA  nid;

                      nid.hWnd             = hWnd;

                      nid.uID              = uID;

                      nid.uFlags           = NIF_ICON | NIF_MESSAGE | NIF_TIP;

                      nid.uCallbackMessage = uCallbackMsg;



      //ExtractIconEx( "C:/_bmv/DesktopGitHub/WinAPIforReadAndWrite/ico/cloud_icon_124378.ico", 0, NULL, &(nid.hIcon), 1 );

      ExtractIconEx( "ico/cloud_icon_124378.ico", 0, NULL, &(nid.hIcon), 1 );
      strcpy       (nid.szTip, "Tool Tip view");



      //SEND MESSAGE TO SYSTEM TRAY TO ADD ICON.--------------------------------------------

      Shell_NotifyIcon( NIM_ADD, &nid );



      ExtractIconEx( "ico/countdown_icon_124379.ico", 0, NULL, &(nid.hIcon), 1 );
      Shell_NotifyIcon(NIM_MODIFY, &nid);

      threadedChanges(nid);

    }
    void changeTrayIcon(NOTIFYICONDATA  nidInputed){

        do{
                //threadedWPone::doMain();
        //threadedWPone tmpThreadedWPone;
        //tmpThreadedWPone.doMain();
            //tmpThreadedWPone.doMain();
            tmpThreadedWPone.doOneThread();

            std::this_thread::sleep_for(std::chrono::seconds(5));
            Shell_NotifyIcon( NIM_ADD, &nidInputed );

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/brightness_video_icon_124377.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/cloud_icon_124378.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/countdown_icon_124379.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/crop_icon_124380.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/duplicate_icon_124381.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/expand_icon_124383.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/film_role_icon_124384.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/headphone_icon_124385.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/hide_icon_124386.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/laptop_icon_124387.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/megaphone_music_sound_speaker_voice_volume_icon_124388.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/microphone_icon_124389.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/share_export_data_network_icon_229067.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            ExtractIconEx( "ico/thumbs_up_like_feedback_favourite_icon_229078.ico", 0, NULL, &(nidInputed.hIcon), 1 );
            Shell_NotifyIcon(NIM_MODIFY, &nidInputed);

            std::this_thread::sleep_for(std::chrono::seconds(5));
            Shell_NotifyIcon( NIM_DELETE, &nidInputed );
                  NOTIFYICONDATA  nidInputed;


                      nidInputed.hWnd             = hWndGlobal;

                      nidInputed.uID              = uIDGlobal;

                      nidInputed.uFlags           = NIF_ICON | NIF_MESSAGE | NIF_TIP;

                      nidInputed.uCallbackMessage = uCallbackMsgGlobal;
                      ExtractIconEx( "ico/cloud_icon_124378.ico", 0, NULL, &(nidInputed.hIcon), 1 );
      strcpy       (nidInputed.szTip, "Tool Tip view 5");
      Shell_NotifyIcon( NIM_ADD, &nidInputed );
        }while(true);

    }
    void threadedChanges(NOTIFYICONDATA  nidIn){
        //std::thread t1 = std::thread::thread();
        std::thread t1(changeTrayIcon, nidIn);
        t1.detach();
    }
