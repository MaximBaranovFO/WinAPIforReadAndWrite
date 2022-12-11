#pragma once
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <windows.h>


using namespace std;

class threadedWPfour
{
public:
    std::thread tOne1;
    bool isThreadStarted = false;
    //Constructors / Destructors
    threadedWPfour() noexcept{
        isThreadStarted = false;
    };

    HWND getWndHWNDClass(char bukva);
    int doMain(void);
    int doFourThread(void);
    int doTwoThread(void);
    int closeOneThread(void);
    //~bThOne();
    void setWndHWNDClass(char bukva, HWND wndClassInputed);

    char getBukva(void);
    void setCurentBukva(char bukvaForSet);

    LRESULT CALLBACK WindowProcedureOne(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK initalWindowProcedure(HWND, UINT, WPARAM, LPARAM);
    WNDCLASSEX initialWndClass(void);
    ~threadedWPfour(){


    };
protected:


private:
    int b;
    bool isUsedB;
    char currentBukva = 'a';
    std::map<std::string, std::string> g_pages;
    std::mutex g_pages_mutex;
    void save_page(const std::string &url);
    typedef std::map<char, HWND> ThreadedWndMap;
    ThreadedWndMap iterTWM;

};

void threadedWPfour::save_page(const std::string &url)
{
    // simulate a long page fetch
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string result = "fake content";

    std::lock_guard<std::mutex> guard(g_pages_mutex);
    g_pages[url] = result;
}
int threadedWPfour::doMain()
{
    std::thread t1 = thread();
    std::thread t2 = thread();
    std::thread t3 = thread();
    //std::thread t1(save_page, "http://foo");
    //std::thread t2(save_page, "http://bar");
    //t1.join();
    //t2.join();
    //t3.join();
    t1.detach();
    t2.detach();
    t3.detach();


    MessageBox(0, TEXT("two threads run and join"), TEXT("WARning"), MB_ICONINFORMATION);

    // safe to access g_pages without lock now, as the threads are joined
    for (const auto &pair : g_pages) {
        std::cout << pair.first << " => " << pair.second << '\n';
    }

    return 0;
}
HWND __stdcall threadedWPfour::getWndHWNDClass(char bukva){
    HWND returnetd;// = iterTWM.at(bukva);
    iterTWM.at(bukva);
    return returnetd;
}
unsigned int __stdcall mythreadFour(void* data)
{


    std::thread tFour = thread();
    //tFour();
    HWND nowEdit;// = getWndHWNDClass('a');
    //nowEdit = threadedWPfour::iterTWM.at('a');
    SetWindowText(nowEdit,"Result");
    //Сюда добавить переменную окна edit и обновлять ее цифрой генератор цифр?
    std::cout <<"\nthis is work:\n 0489 mythreadFour: inner Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();
    return 0;
}
int threadedWPfour::doFourThread(void){
    /**std::thread tOne1 = thread();
        tOne1.detach();
        isThreadStarted = true;*/
            HANDLE myhandleOne;
    unsigned threadIDOne;

    myhandleOne = (HANDLE)_beginthreadex(NULL, 0, &mythreadFour, NULL, 0, &threadIDOne);
    //do{
        //whait
    //}while(true);
    std::cout <<"\nthis is work:\n 0947 threadedWPfour::doFourThread, HANDLE:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();

    WaitForSingleObject(myhandleOne, INFINITE);
    ReleaseMutex(myhandleOne);
    CloseHandle(myhandleOne);
        return 0;
}

void threadedWPfour::setWndHWNDClass(char bukva, HWND wndClassInputed){
    iterTWM.insert(ThreadedWndMap::value_type(bukva,wndClassInputed));
}

char threadedWPfour::getBukva(void){
    return 'a';
}
void threadedWPfour::setCurentBukva(char bukvaForSet){
    currentBukva = bukvaForSet;
}
LRESULT CALLBACK threadedWPfour::WindowProcedureOne(HWND window, UINT msg, WPARAM wp, LPARAM lp)
{
    if(msg == WM_CREATE){

        MessageBox(NULL, _T("Create window?"), _T("Error!"), MB_OK | MB_ICONHAND);
        bool bCreated = true;
    }

    if(msg == WM_APP){
        MessageBox(NULL, _T("WM_APP, window?"), _T("Error!"), MB_OK | MB_ICONHAND);
    }
   	// выборка и обработка сообщений
	switch (msg)
	{


	case WM_DESTROY:
		PostQuitMessage(0);  // реакция на сообщение
		break;
	default:
		// все сообщения не обработанные Вами обработает сама Windows
		return DefWindowProc(window, msg, wp, lp);
	}
	return 0;

}
unsigned int __stdcall fourCreate(void* data)
    {
        MessageBox(NULL, _T("CreateWindowEx start!\n"), _T("Error!"), MB_OK | MB_ICONASTERISK);
    HINSTANCE hinst;
    HWND hwndMain;
    WNDCLASSEX wnd;
    MSG msg;

    hinst = GetModuleHandle( NULL );
    memset( &wnd, 0, sizeof( wnd ) );
    wnd.cbSize = sizeof( wnd );
    wnd.lpszClassName = "threadedWPfour::fourCreate";
    wnd.lpfnWndProc = (WNDPROC)&threadedWPone::WindowProcedureOne;

    wnd.hIcon = NULL;//LoadIcon(NULL, IDI_WINLOGO); // Стандартная иконка
    wnd.hIconSm = NULL;//LoadIcon(NULL, IDI_WINLOGO);
    wnd.hInstance = hinst;

    int result = RegisterClassEx( &wnd );
    if( !result )
    {
        MessageBox(NULL, _T("RegisterClassEx error, failed!" + GetLastError()), _T("Error!"), MB_OK | MB_ICONERROR);
        printf("RegisterClassEx error: %d\r\n", GetLastError() );
    }

    hwndMain = CreateWindowEx
        (
        0, //extended styles
        wnd.lpszClassName, //class name
        "Main Window", //window name
        WS_OVERLAPPEDWINDOW, //style tags
        CW_USEDEFAULT, //horizontal position
        CW_USEDEFAULT, //vertical position
        CW_USEDEFAULT, //width
        CW_USEDEFAULT, //height
        (HWND) NULL, //parent window
        (HMENU) NULL, //class menu
        (HINSTANCE) wnd.hInstance, //some HINSTANCE pointer
        NULL //Create Window Data?
        );

    if( !hwndMain )
    {

        MessageBox(NULL, _T("CreateWindowEx error, failed!\n" + GetLastError()), _T("Error!"), MB_OK | MB_ICONERROR);
        printf("Oh shi- %d\n", GetLastError() );
    }
    ShowWindow( hwndMain, SW_SHOWDEFAULT );
    UpdateWindow( hwndMain );

    // Run the main message loop.
    BOOL bRetVal;

    while ((bRetVal = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if (bRetVal == -1)
        {
            MessageBox(NULL, TEXT("Error encountered in message loop!"), NULL, MB_OK);
            return 1;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return 0;
}
int threadedWPfour::doTwoThread(void){
    /**std::thread tOne1 = thread();
        tOne1.detach();
        isThreadStarted = true;*/
            HANDLE myhandleOne;
    unsigned threadIDTwo;

    myhandleOne = (HANDLE)_beginthreadex(NULL, 0, &fourCreate, NULL, 0, &threadIDTwo);
    //do{
        //whait
    //}while(true);
    std::cout <<"\nthis is work:\n 0910 HANDLE:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();

    WaitForSingleObject(myhandleOne, INFINITE);
    ReleaseMutex(myhandleOne);
    CloseHandle(myhandleOne);
        return 0;
}
LRESULT CALLBACK threadedWPfour::initalWindowProcedure(
   HWND   hWndOne,
   UINT   MsgOne,
   WPARAM wParamOne,
   LPARAM lParamOne
){
    switch (MsgOne)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
return DefWindowProc(hWndOne, MsgOne, wParamOne, lParamOne);
}
WNDCLASSEX threadedWPfour::initialWndClass(void){
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
    //wndclassWalInitial.lpfnWndProc = (WNDPROC)&WindowProcedureOne; // Функция окна
    wndclassWalInitial.lpfnWndProc = DefWindowProc;
    //wndclassWalInitial.lpfnWndProc = initalWindowProcedure;
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
int threadedWPfour::closeOneThread(){
     tOne1.~thread();
     return 0;
}
