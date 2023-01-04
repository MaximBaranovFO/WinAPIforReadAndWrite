#include <thread>
#include <windows.h>
#include <Windows.h>
#include <Windowsx.h>

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

using namespace std;
class Xthree {
public:

    void AddTrayIcon(HWND, UINT, UINT, UINT);
    LRESULT CALLBACK WindowProcedure(HWND window, UINT msg, WPARAM wp, LPARAM lp);
    WNDCLASSEX baseValForWndClass(void);
    void do_lengthy_work();
private:
    static HWND hWndGlobal;
    static UINT uIDGlobal;
    static UINT uCallbackMsgGlobal;
};
    //===================================================================================

    void Xthree::AddTrayIcon( HWND hWnd, UINT uID, UINT uCallbackMsg, UINT uIcon ) {



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

      //threadedChanges(nid);

    }
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
	main.lpfnWndProc = (WNDPROC)&WindowProcedure;


	main.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
    main.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Стандартная иконка
    main.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    main.hCursor = LoadCursor(NULL,IDC_ARROW); // Стандартный курсор
    main.lpszMenuName = NULL; // Нет меню
    main.cbClsExtra = 0; // Нет дополнительных данных класса
    main.cbWndExtra = 0; // Нет дополнительных данных окна
    // Заполнение окна белым цветом
    main.hbrBackground = (HBRUSH)(NULL_BRUSH);

	if(RegisterClassEx(&main))
    {

        static HWND window = NULL;

        MessageBox(window, TEXT("Вы запустили! 0154"), TEXT("событие"), 0);

               TCHAR szWindowClass[]= "QWERTY";
        window = ::CreateWindowEx(0,
                                TEXT("tI_EmptyProject"),
                                TEXT("title"),
                                WS_OVERLAPPEDWINDOW, //https://retina.news.mail.ru/pic/89/9f/image54391268_951c6df9bd5478a3e724d67a771e7d09.jpg
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                HWND_DESKTOP,
                                (HMENU)NULL,
                                HINST_THISCOMPONENT,
                                NULL);

        if (!window)
        {
            std::cout <<"\n 0302 false CreateWindowEx:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();
            std::cout <<"\n 0476 GetLastError() returns: "<<GetLastError()<<"\n";
            MessageBox(NULL, TEXT("Create window failed!"), TEXT("Error!"), MB_OK | MB_ICONERROR);
        }
        ShowWindow(window, SW_SHOWDEFAULT);
               UpdateWindow(window);
               MSG msg;
               while (GetMessage(&msg, 0, 0, 0)) DispatchMessage(&msg);
    }
    else
    {
        std::cout <<"\n 0144 GetLastError() returns: "<<GetLastError()<<"\n";
    }
	return main;
}
LRESULT CALLBACK Xthree::WindowProcedure(HWND window, UINT msg, WPARAM wp, LPARAM lp)
{
    	PAINTSTRUCT	ps;
	HDC			hdc;
    	switch (msg)
	{

    case WM_CREATE:
          MessageBox(window, TEXT("Вы запустили! 1151"), TEXT("событие"), 0);
          Xthree::AddTrayIcon( window, 1, WM_APP, 0 );
        // Вызывается, когда впервые создается окно
         return(0);
    case WM_PAINT:
         // Вызывается, когда окно обновляется
            hdc = BeginPaint(window, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			EndPaint(window, &ps);
         return(0);
    case WM_LBUTTONUP:
		 // реакция на сообщение
		MessageBox(window, TEXT("Вы кликнули! 0755"), TEXT("событие"), 0);
		break;
    case WM_DESTROY:
		PostQuitMessage(0);  // реакция на сообщение
		break;
	default:
		return DefWindowProc(window, msg, wp, lp);
	}
	return 0;

}
void Xthree::do_lengthy_work(){
    std::this_thread::yield();
    cout << "\n||| ||| |||Three Some for InterfaceThreaded: " << std::this_thread::get_id() << endl;
    baseValForWndClass();
}
