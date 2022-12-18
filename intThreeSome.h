#include <thread>
#include <windows.h>
#include <Windows.h>
#include <Windowsx.h>
using namespace std;
class Xthree {
public:
    WNDCLASSEX baseValForWndClass(void);
    void do_lengthy_work();
};
WNDCLASSEX Xthree::baseValForWndClass(void){

    std::cout <<"\n 0397 GetLastError() returns: "<<GetLastError()<<"\n";
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

    WNDCLASSEX main;
	main.cbSize = sizeof(WNDCLASSEX);
	main.hInstance = GetModuleHandle(NULL);
	main.lpszClassName = TEXT("Main");
	main.lpfnWndProc = NULL;
	if(RegisterClassEx(&main))
    {
        static HWND window = NULL;
               TCHAR szWindowClass[]= "QWERTY";
               window = CreateWindowEx(WS_EX_WINDOWEDGE,
                              szWindowClass,
               "title",
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT,0,CW_USEDEFAULT,0,
               NULL, (HMENU)NULL, GetModuleHandle(NULL), NULL);
        if (window)
        {
               ShowWindow(window, SW_SHOWDEFAULT);
               MSG msg;
               while (GetMessage(&msg, 0, 0, 0)) DispatchMessage(&msg);
        }
        else {
            std::cout <<"\n 0302 false CreateWindowEx:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();
            std::cout <<"\n 0476 GetLastError() returns: "<<GetLastError()<<"\n";
            MessageBox(NULL, "Create window failed!", "Error!", MB_OK | MB_ICONERROR);
        }
    }
    else
    {
        std::cout <<"\n 0144 GetLastError() returns: "<<GetLastError()<<"\n";
    }
	return main;
}
void Xthree::do_lengthy_work(){
    std::this_thread::yield();
    cout << "\n||| ||| |||Three Some for InterfaceThreaded: " << std::this_thread::get_id() << endl;
    baseValForWndClass();
}
