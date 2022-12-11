
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "appClass.h"

#include "aThOne.h"
#include "bThOne.h"
#include "cThOne.h"



// Глобальные переменные
HINSTANCE hInst;
NOTIFYICONDATA Icon = { 0 }; // Атрибуты значка
LPCSTR pszIDStatusIcon;
void HandlePopupMenu (HWND, POINT);
void showMenu(HWND);
ClassA tmpClassA;

//aThOne athreadline;

#define IDR_POPUPMENU 11
#define WM_NOTIFYICONMSG (WM_USER + 2)

// Обработка сообщений
LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    POINT pt;
    bool isLineAused;
    std::string tmpValUsedLineA;

    //auto athreadline{new aThOne};

    //isLineAused = athreadline->get_a();
    if(isLineAused)
        tmpValUsedLineA = _T("Line A is used");
    else
        tmpValUsedLineA = _T("Line A not used");

        aThOne someObjectA;
        someObjectA.doMain();

        bThOne someObjectB;
        someObjectB.doMain();

        cThOne someObjectC;
        //someObjectC.addWindow();
        someObjectC.doMain();


	switch (message)
	{
	    // Сообщение от значка
		case WM_USER:
		    if (lParam == WM_LBUTTONDBLCLK){
                if (MessageBox(NULL, TEXT("LEFT DOUBLE CLICK Завершить работу?"), TEXT("Tray RB"), MB_YESNO) == IDYES){
                    DestroyWindow(window);
                } else {
                    tmpClassA.set_a(42);

                    std::string tmpVal = std::to_string(tmpClassA.get_a());


                    MessageBox(NULL, TEXT(tmpVal.c_str()), TEXT("Galaxy"), MB_ICONINFORMATION);
                    MessageBox(NULL, TEXT("LEFT DOUBLE CLICK, Двойной щелчок по иконке и Нет"), TEXT("Сообщение от иконки"), MB_OK);

                    GetCursorPos(&pt);	//вычисляем текущее положение курсора


                    std::string tmpValCoordX = std::to_string(pt.x);
                    std::string tmpValCoordY = std::to_string(pt.y);
                    std::string tmpValCoord = TEXT("X: ") + TEXT(tmpValCoordX)
                        + TEXT(" \nY: ") + TEXT(tmpValCoordY)
                        + TEXT(" \nand: ") + TEXT(tmpValUsedLineA);
                    MessageBox(NULL, TEXT(tmpValCoord.c_str()), TEXT("Galaxy"), MB_ICONINFORMATION);
                    HandlePopupMenu (window, pt);  //рисуем меню от координат курсора
                }


				//
		    }

		    /*if (lParam == WM_LBUTTONDOWN)
				if (MessageBox(NULL, TEXT("LEFT BUTTON Завершить работу?"), TEXT("Tray RB"), MB_YESNO) == IDYES)
					DestroyWindow(window);*/
			if (lParam == WM_RBUTTONDOWN)
				if (MessageBox(NULL, TEXT("RIGHT BUTTON Завершить работу?"), TEXT("Tray RB"), MB_YESNO) == IDYES)
					DestroyWindow(window);
			break;
		// Стандартная обработка сообщений
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(window, message, wParam, lParam);
	}
	return 0;
}

// Главная функция
int APIENTRY _tWinMain(HINSTANCE instance, HINSTANCE, LPTSTR, int)
{

	// Регистрация класса окна
	WNDCLASSEX main = { 0 };
	main.cbSize = sizeof(WNDCLASSEX);
	hInst = instance;
	main.hInstance = instance;
	main.lpszClassName = TEXT("Main");
	main.lpfnWndProc = WndProc;
	//main = tmpClassA.baseValForWndClass(main);
	RegisterClassEx(&main);

	// Создание главного окна
    HWND window = CreateWindowEx(0, TEXT("Main"), NULL, 0, 0, 0, 0, 0, NULL, NULL, instance, NULL);

    // Создание значка
	Icon.cbSize = sizeof(NOTIFYICONDATA);
	Icon.hWnd = window;
	Icon.uVersion = NOTIFYICON_VERSION;
	Icon.uCallbackMessage = WM_USER;

	//pszIDStatusIcon = MAKEINTRESOURCE(IDI_APPLICATION);
	Icon.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	Icon.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;//NIF_MESSAGE | NIF_ICON;
	lstrcpyn(Icon.szTip, "Double some or LButton menu, RButton out app", sizeof(Icon.szTip));
	Shell_NotifyIcon(NIM_ADD, &Icon);

	MessageBox(0, TEXT("Привет, Hello World"), TEXT(""), MB_ICONINFORMATION);


	// Цикл обработки сообщений
	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	// Удаление значка
	Shell_NotifyIcon(NIM_DELETE, &Icon);
	return 0;
}
void HandlePopupMenu (HWND hWnd, POINT point)
{
	HMENU hMenu;
	HMENU hMenuTrackPopup;
	LPCSTR pszIDMenu;


	if( MessageBox(NULL, TEXT("Close app YES, Рисовать меню NO?"), TEXT("Tray RB"), MB_YESNO) == IDYES)
					DestroyWindow(hWnd);

	pszIDMenu = MAKEINTRESOURCE(IDR_POPUPMENU);
	hMenu = LoadMenu (hInst, "PopupMenu");
	if (!hMenu)  return;
	hMenuTrackPopup = GetSubMenu (hMenu, 0);
	TrackPopupMenu (hMenuTrackPopup, 0, point.x, point.y, 0, hWnd, NULL);
	showMenu(hWnd);
	DestroyMenu (hMenu);
}
void showMenu(HWND hWnd)
{
   POINT pt;
   GetCursorPos(&pt);
   HMENU hMenu = CreatePopupMenu();
   if(hMenu)
   {
      InsertMenu(hMenu, -1, MF_BYPOSITION, 12345, "Main");
      InsertMenu(hMenu, -1, MF_BYPOSITION, 6789, "Settings");

      InsertMenu(hMenu, -1, MF_BYPOSITION|MF_SEPARATOR, 0, "");

      InsertMenu(hMenu, -1, MF_BYPOSITION, 98765, "About");
      InsertMenu(hMenu, -1, MF_BYPOSITION, 54321, "Exit");

      // note:	must set window to the foreground or the
      //			menu won't disappear when it should
      SetForegroundWindow(hWnd);

      TrackPopupMenu(hMenu, TPM_BOTTOMALIGN,
                     pt.x, pt.y, 0, hWnd, NULL );
      DestroyMenu(hMenu);
   }
}
