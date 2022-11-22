#pragma once
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <windows.h>


using namespace std;
class threadedWPone
{
public:
    std::thread tOne1;
    bool isThreadStarted = false;
    //Constructors / Destructors
    threadedWPone() noexcept{
        isThreadStarted = false;
    };


    int doMain(void);
    int doOneThread(void);
    int doTwoThread(void);
    int closeOneThread(void);
    //~bThOne();
    void setWndClass(char bukva, WNDCLASSEX wndClassInputed);
    WNDCLASSEX getWndClass(char bukva);
    char getBukva(void);
    void setCurentBukva(char bukvaForSet);

    LRESULT CALLBACK WindowProcedureOne(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK initalWindowProcedure(HWND, UINT, WPARAM, LPARAM);
    WNDCLASSEX initialWndClass(void);
    ~threadedWPone(){


    };
protected:


private:
    int b;
    bool isUsedB;
    char currentBukva = 'a';
    std::map<std::string, std::string> g_pages;
    std::mutex g_pages_mutex;
    void save_page(const std::string &url);
    typedef std::map<char, WNDCLASSEX> ThreadedWndMap;
    ThreadedWndMap iterTWM;
};

void threadedWPone::save_page(const std::string &url)
{
    // simulate a long page fetch
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string result = "fake content";

    std::lock_guard<std::mutex> guard(g_pages_mutex);
    g_pages[url] = result;
}
int threadedWPone::doMain()
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
unsigned int __stdcall mythreadOne(void* data)
{

    std::cout <<"this is work:\nmythreadOne:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();
    return 0;
}
int threadedWPone::doOneThread(void){
    /**std::thread tOne1 = thread();
        tOne1.detach();
        isThreadStarted = true;*/
            HANDLE myhandleOne;
    unsigned threadIDOne;

    myhandleOne = (HANDLE)_beginthreadex(NULL, 0, &mythreadOne, NULL, 0, &threadIDOne);
    //do{
        //whait
    //}while(true);
    std::cout <<"this is work:\nHANDLE:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();

    WaitForSingleObject(myhandleOne, INFINITE);
    ReleaseMutex(myhandleOne);
    CloseHandle(myhandleOne);
        return 0;
}

void threadedWPone::setWndClass(char bukva, WNDCLASSEX wndClassInputed){
    iterTWM.insert(ThreadedWndMap::value_type(bukva,wndClassInputed));
}
WNDCLASSEX threadedWPone::getWndClass(char bukva){
    return iterTWM.at(bukva);
}
char threadedWPone::getBukva(void){
    return 'a';
}
void threadedWPone::setCurentBukva(char bukvaForSet){
    currentBukva = bukvaForSet;
}
LRESULT CALLBACK threadedWPone::WindowProcedureOne(HWND window, UINT msg, WPARAM wp, LPARAM lp)
{
    if(msg == WM_CREATE){

        MessageBox(NULL, _T("Create window?"), _T("Error!"), MB_OK | MB_ICONHAND);
        bool bCreated = true;
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
unsigned int __stdcall twoCreate(void* data)
    {
        MessageBox(NULL, _T("CreateWindowEx start!\n"), _T("Error!"), MB_OK | MB_ICONASTERISK);
    HINSTANCE hinst;
    HWND hwndMain;
    WNDCLASSEX wnd;
    MSG msg;

    hinst = GetModuleHandle( NULL );
    memset( &wnd, 0, sizeof( wnd ) );
    wnd.cbSize = sizeof( wnd );
    wnd.lpszClassName = "threadedWPone::twoCreate";
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
        WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME| WS_POPUP | WS_BORDER | WS_SYSMENU, //extended styles
        wnd.lpszClassName, //class name
        "Main Window", //window name
        WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL | WS_MINIMIZEBOX, //style tags
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
int threadedWPone::doTwoThread(void){
    /**std::thread tOne1 = thread();
        tOne1.detach();
        isThreadStarted = true;*/
            HANDLE myhandleOne;
    unsigned threadIDTwo;

    myhandleOne = (HANDLE)_beginthreadex(NULL, 0, &twoCreate, NULL, 0, &threadIDTwo);
    //do{
        //whait
    //}while(true);
    std::cout <<"this is work:\nHANDLE:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();

    WaitForSingleObject(myhandleOne, INFINITE);
    ReleaseMutex(myhandleOne);
    CloseHandle(myhandleOne);
        return 0;
}
LRESULT CALLBACK threadedWPone::initalWindowProcedure(
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
WNDCLASSEX threadedWPone::initialWndClass(void){
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
int threadedWPone::closeOneThread(){
     tOne1.~thread();
     return 0;
}
