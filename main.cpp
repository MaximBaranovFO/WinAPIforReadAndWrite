#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif


#include "windows.h"
#include <commctrl.h>
/**002 - Start section*/
#include <wchar.h>
#include <strsafe.h>
/**002 - End section*/

/**004 - Start section*//**004 - End section*/
LRESULT CALLBACK WinProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WinProcedureTabControl(HWND, UINT, WPARAM, LPARAM);
/**002 - Start section*/
void CreateControls(HWND);
void GetSelectedDate(HWND, HWND);
/**002 - End section*/
void CreateButtonsControls(HWND);

/**004 - Start section*/
HWND hTabControl, hEdit;
/**004 - End section*/

/**002 - Start section*/
HWND hStat;
HWND hMonthCal;
/**002 - End section*/
/**001 - Start section*/
enum { ID_LABEL = 1,ID_IMAGE,ID_EDIT,ID_LIST,ID_BUTTON1,ID_COMBO,ID_BUTTON2,ID_BUTTON0,
ID_BUTTON3,ID_BUTTON4,ID_BUTTON5,ID_BUTTON6,ID_BUTTON7,ID_BUTTON8,ID_BUTTON9,
ID_BUTTONPLUS, ID_BUTTONMINUS, ID_BUTTONTIME, ID_BUTTONDIVIDE, ID_BUTTONEQUAL, ID_BUTTONRESULT,
ID_TABCTRL = 1,
ID_EDITPANEL = 2,
BTN_ADD = 3,
BTN_DEL = 4,
BTN_CLR = 5,
MAX_TAB_LEN = 15};

LRESULT CALLBACK WinProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInst;
TCHAR	szAppName[]	= TEXT("Calculator");
TCHAR	szWinClass[]	= TEXT("WIN_CLASS");

HWND static_label;
HWND edit;
HWND list;
//number
HWND button0;
HWND button1;
HWND button2;
HWND button3;
HWND button4;
HWND button5;
HWND button6;
HWND button7;
HWND button8;
HWND button9;
//operation
HWND buttonPlus;
HWND buttonMinus;
HWND buttonTime;
HWND buttonDivide;
HWND buttonEqual;
//result
HWND buttonResult;

HWND		hwndCalendar;

int WINAPI WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		PSTR lpCmdLine,
		int nCmdShow){

	MSG			msg;
	WNDCLASS	wcMain;
	HWND		hwnd;
	HWND		hwndCalendar;
	g_hInst = hInstance;
/**004 - Start section*/
    WNDCLASSW wcTabControl = {0};
    wcTabControl.lpszClassName = L"Tab control";
    wcTabControl.hInstance     = hInstance;
    wcTabControl.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wcTabControl.lpfnWndProc   = WinProcedure;
    wcTabControl.hCursor       = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wcTabControl);
    CreateWindowW(wcTabControl.lpszClassName, L"Tab control",
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  CW_USEDEFAULT, CW_USEDEFAULT, 544, 375,(HWND) NULL,
						(HMENU) NULL,
						(HINSTANCE) hInstance,
						(void *) NULL);
/**004 - End section*/
	wcMain.cbClsExtra		= 0;
	wcMain.cbWndExtra		= 0;
	wcMain.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcMain.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wcMain.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcMain.hInstance		= hInstance;
	wcMain.lpfnWndProc		= WinProcedure;
	wcMain.lpszClassName	= szWinClass;
	wcMain.lpszMenuName		= NULL;
	wcMain.style			= CS_HREDRAW | CS_VREDRAW;

 	if( !RegisterClass(&wcMain))
	{
		MessageBox(NULL, TEXT("Error registering class"), TEXT("ERROR"), MB_OK);
		return 0;
	}
/**001 - End section*/
/**002 - Start section*/
	 WNDCLASSW wcCalendar = {0};
 wcCalendar.lpszClassName = L"Month Calendar";
 wcCalendar.hInstance = hInstance;
 wcCalendar.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
 wcCalendar.lpfnWndProc = WinProcedure;
 wcCalendar.hCursor = LoadCursor(0, IDC_ARROW);

 RegisterClassW(&wcCalendar);

 hwndCalendar = CreateWindowW(wcCalendar.lpszClassName,
                      L"Month Calendar",
 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
 CW_USEDEFAULT,
 CW_USEDEFAULT,
 250,
 300,
 (HWND) NULL,
						(HMENU) NULL,
						(HINSTANCE) hInstance,
						(void *) NULL);

/**002 - End section*/
/**001 - Start section*/
	hwnd = CreateWindow(szWinClass,
						szAppName,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						544,
						375,
						(HWND) NULL,
						(HMENU) NULL,
						(HINSTANCE) hInstance,
						(void *) NULL);
/**001 - End section*/
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	ShowWindow(hwndCalendar, nCmdShow);
	UpdateWindow(hwndCalendar);

	while (GetMessage(&msg, (HWND) NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WinProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    /**001 - Start section*/
	PAINTSTRUCT	ps;
	HDC			hdc;
LPNMHDR lpNmHdr;
	switch(msg){
		case WM_CREATE:
		    /**001 - End section*/
		    /**004 - Start section*/
		        WinProcedureTabControl(hwnd, msg, wParam, lParam);
		    /**004 - End section*/
		    //HINSTANCE inst = GetModuleHandle(NULL);
            /**003 - Start section*/
			CreateButtonsControls(hwnd);
            /**003 - End section*/



            /**002 - Start section*/
            CreateControls(hwndCalendar);

 break;

 case WM_NOTIFY:

 lpNmHdr = (LPNMHDR) lParam;

 if (lpNmHdr->code == MCN_SELECT) {
 GetSelectedDate(hMonthCal, hStat);
 }
  break;
  /**002 - End section*/
  /**001 - Start section*/
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			return 0;
		case WM_COMMAND: //Command from Child windows and menus are under this message
            switch(wParam) //the ID is wParam
            {
                case ID_BUTTON0: //check for our button ID
					{
					// Static labels dont do messages
                    //we can set the text directly though

						SetWindowText(edit,"0");
						break;
					}

				case ID_BUTTON1:
					{
						SetWindowText(edit,"1");
						break;
					}

				case ID_BUTTON2:
					{
						SetWindowText(edit,"2");
						break;
					}

				case ID_BUTTON3:
					{
						SetWindowText(edit,"3");
						break;
					}

				case ID_BUTTON4:
					{
						SetWindowText(edit,"4");
						break;
					}

				case ID_BUTTON5:
					{
						SetWindowText(edit,"5");
						break;
					}

				case ID_BUTTON6:
					{
						SetWindowText(edit,"6");
						break;
					}

				case ID_BUTTON7:
					{
						SetWindowText(edit,"7");
						break;
					}

				case ID_BUTTON8:
					{
						SetWindowText(edit,"8");
						break;
					}

				case ID_BUTTON9:
					{
						SetWindowText(edit,"9");
						break;
					}

				case ID_BUTTONPLUS:
					{
						SetWindowText(edit,"+");
						break;
					}

				case ID_BUTTONMINUS:
					{
						SetWindowText(edit,"-");
						break;
					}

				case ID_BUTTONTIME:
					{
						SetWindowText(edit,"*");
						break;
					}

				case ID_BUTTONDIVIDE:
					{
						SetWindowText(edit,"/");
						break;
					}
				case ID_BUTTONEQUAL:
					{
						SetWindowText(edit,"=");
						break;
					}
                case ID_BUTTONRESULT:
					{
						SetWindowText(edit,"Result");
						break;
					}
            }//switch.
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break; // pass to DefWindowProc(...) as well
		case WM_CLOSE:
			DestroyWindow(hwnd);
			DestroyWindow(hwndCalendar);
			break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	/**001 - End section*/
/**002 - Start section*/
	void CreateControls(HWND hwndCalendarInner) {

 hStat = CreateWindowW(WC_STATICW, L"",
 WS_CHILD | WS_VISIBLE, 80, 240, 80, 30,
 hwndCalendar, (HMENU)1, NULL, NULL);

 INITCOMMONCONTROLSEX icex;

 icex.dwSize = sizeof(icex);
 icex.dwICC = ICC_DATE_CLASSES;
 InitCommonControlsEx(&icex);

 hMonthCal = CreateWindowW(MONTHCAL_CLASSW, L"",
 WS_BORDER | WS_CHILD | WS_VISIBLE | MCS_NOTODAYCIRCLE,
 20, 20, 200, 200, hwndCalendar, (HMENU)2, NULL, NULL);
}

void GetSelectedDate(HWND hMonthCal, HWND hStat) {

 SYSTEMTIME time;
 const int dsize = 20;
 wchar_t buf[dsize];

 ZeroMemory(&time, sizeof(SYSTEMTIME));
 SendMessage(hMonthCal, MCM_GETCURSEL, 0, (LPARAM) &time);

 size_t cbDest = dsize * sizeof(wchar_t);
 StringCbPrintfW(buf, cbDest, L"%d-%d-%d",
 time.wYear, time.wMonth, time.wDay);

 SetWindowTextW(hStat, buf);
}
/**002 - End section*/
/**003 - Start section*/
void CreateButtonsControls(HWND hwndButtons) {
            static_label = CreateWindow("Static","Please Enter A Number",WS_CHILD | WS_VISIBLE,35,15,175,25,hwndButtons,0,g_hInst,0);
			edit = CreateWindow("Edit", NULL,WS_BORDER | NULL | WS_CHILD | WS_VISIBLE | NULL | NULL ,35,45,175,20,hwndButtons,(HMENU)ID_EDIT,g_hInst,0);

			button0 = CreateWindow("Button","0",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,80,220,35,35,hwndButtons,(HMENU)ID_BUTTON0,g_hInst,0);
			button1 = CreateWindow("Button","1",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,35,170,35,35,hwndButtons,(HMENU)ID_BUTTON1,g_hInst,0);
			button2 = CreateWindow("Button","2",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,80,170,35,35,hwndButtons,(HMENU)ID_BUTTON2,g_hInst,0);
			button3 = CreateWindow("Button","3",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,125,170,35,35,hwndButtons,(HMENU)ID_BUTTON3,g_hInst,0);
			button4 = CreateWindow("Button","4",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,35,120,35,35,hwndButtons,(HMENU)ID_BUTTON4,g_hInst,0);
			button5 = CreateWindow("Button","5",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,80,120,35,35,hwndButtons,(HMENU)ID_BUTTON5,g_hInst,0);
			button6 = CreateWindow("Button","6",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,125,120,35,35,hwndButtons,(HMENU)ID_BUTTON6,g_hInst,0);
			button7 = CreateWindow("Button","7",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,35,70,35,35,hwndButtons,(HMENU)ID_BUTTON7,g_hInst,0);
			button8 = CreateWindow("Button","8",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,80,70,35,35,hwndButtons,(HMENU)ID_BUTTON8,g_hInst,0);
			button9 = CreateWindow("Button","9",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,125,70,35,35,hwndButtons,(HMENU)ID_BUTTON9,g_hInst,0);

			buttonDivide = CreateWindow("Button","/",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,170,70,35,35,hwndButtons,(HMENU)ID_BUTTONDIVIDE,g_hInst,0);
			buttonTime = CreateWindow("Button","*",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,170,120,35,35,hwndButtons,(HMENU)ID_BUTTONTIME,g_hInst,0);
			buttonMinus = CreateWindow("Button","-",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,170,170,35,35,hwndButtons,(HMENU)ID_BUTTONMINUS,g_hInst,0);
			buttonPlus = CreateWindow("Button","+",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,170,220,35,35,hwndButtons,(HMENU)ID_BUTTONPLUS,g_hInst,0);
			buttonEqual = CreateWindow("Button","=",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,125,220,35,35,hwndButtons,(HMENU)ID_BUTTONEQUAL,g_hInst,0);

			buttonResult = CreateWindow("Button","Result",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,15,220,55,35,hwndButtons,(HMENU)ID_BUTTONRESULT,g_hInst,0);
}
/**003 - End section*/
/**004 - End section*/
LRESULT CALLBACK WinProcedureTabControl(HWND hwndTabControl, UINT msg, WPARAM wParam, LPARAM lParam){
        TCITEMW tie;
    wchar_t text[4];
    LRESULT count, id;
    INITCOMMONCONTROLSEX icex;

    switch(msg) {

        case WM_CREATE:

            icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
            icex.dwICC = ICC_TAB_CLASSES;
            InitCommonControlsEx(&icex);

            hTabControl = CreateWindowW(WC_TABCONTROLW, NULL, WS_CHILD | WS_VISIBLE,
                0, 0, 200, 150, hwndTabControl,(HMENU) ID_TABCTRL, NULL, NULL);

            hEdit = CreateWindowW(WC_EDITW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
                250, 20, 100, 25, hwndTabControl, (HMENU) ID_EDITPANEL, NULL, NULL);

            SendMessage(hEdit, EM_SETLIMITTEXT, MAX_TAB_LEN, 0);

            CreateWindowW(WC_BUTTONW, L"Add", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                250, 50, 100, 25, hwndTabControl, (HMENU) BTN_ADD, NULL, NULL);

            CreateWindowW(WC_BUTTONW, L"Delete", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                250, 80, 100, 25, hwndTabControl, (HMENU) BTN_DEL, NULL, NULL);

            CreateWindowW(WC_BUTTONW, L"Clear", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                250, 110, 100, 25, hwndTabControl, (HMENU) BTN_CLR, NULL, NULL);
            break;

        case WM_COMMAND:

            switch(LOWORD(wParam)) {

                case BTN_ADD:

                    GetWindowTextW(hEdit, text, 375);

                    if (lstrlenW(text) != 0 ) {

                        tie.mask = TCIF_TEXT;
                        tie.pszText = text;
                        count = SendMessageW(hTabControl, TCM_GETITEMCOUNT, 0, 0);
                        SendMessageW(hTabControl, TCM_INSERTITEMW, count,
                            (LPARAM) (LPTCITEM) &tie);
                    }
                    break;

                case BTN_DEL:

                    id = SendMessageW(hTabControl, TCM_GETCURSEL, 0, 0);

                    if (id != -1) {

                       SendMessageW(hTabControl, TCM_DELETEITEM, 0, id);
                    }
                    break;

                case BTN_CLR:

                    SendMessageW(hTabControl, TCM_DELETEALLITEMS, 0, 0);
                    break;
            }
            break;

        case WM_DESTROY:

            PostQuitMessage(0);
            break;
    }

    return(DefWindowProcW(hwndTabControl, msg, wParam, lParam));
}
/**004 - Start section*/
