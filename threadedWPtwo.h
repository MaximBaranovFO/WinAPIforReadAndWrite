#pragma once
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <windows.h>


using namespace std;

enum { ID_LABEL = 1,ID_IMAGE,ID_EDIT,ID_EDITWAL,ID_LIST,ID_BUTTON1,ID_COMBO,ID_BUTTON2,ID_BUTTON0,
ID_BUTTON3,ID_BUTTON4,ID_BUTTON5,ID_BUTTON6,ID_BUTTON7,ID_BUTTON8,ID_BUTTON9,
ID_BUTTONPLUS, ID_BUTTONMINUS, ID_BUTTONTIME, ID_BUTTONDIVIDE, ID_BUTTONEQUAL, ID_BUTTONRESULT,
ID_TABCTRL = 1,
ID_EDITPANEL = 2,
BTN_ADD = 3,
BTN_DEL = 4,
BTN_CLR = 5,
MAX_TAB_LEN = 15};
class threadedWPtwo
{
public:
    std::thread tTwo2;
    bool isThreadStarted = false;
    //Constructors / Destructors
    threadedWPtwo() noexcept{
        isThreadStarted = false;
    };


    int doMain(void);
    int doTwoThread(void);
    int closeTwoThread(void);
    //~bThOne();
    void setWndClass(char bukva, WNDCLASSEX wndClassInputed);
    WNDCLASSEX getWndClass(char bukva);
    char getBukva(void);
    void setCurentBukva(char bukvaForSet);

    HINSTANCE getInstance(void);
    void setCurentInstance(HINSTANCE instanceForSet);
    HWND getWnd(void);
    void setCurentWnd(HWND wndForSet);
    HWND getButton(void);
    void setCurentButton(HWND buttonForSet);

    ~threadedWPtwo(){


    };
protected:


private:
    int b;
    bool isUsedB;
    char currentBukva = 'a';

    HINSTANCE g_hInstanceParent;
    HWND		hwndParent;
    HWND button0Parent;

    std::map<std::string, std::string> g_pages;
    std::mutex g_pages_mutex;
    void save_page(const std::string &url);
    typedef std::map<char, WNDCLASSEX> ThreadedWndMap;
    ThreadedWndMap iterTWM;
};

    HINSTANCE threadedWPtwo::getInstance(void){
        return g_hInstanceParent;
    }
    void threadedWPtwo::setCurentInstance(HINSTANCE instanceForSet){
        g_hInstanceParent = instanceForSet;
    }
    HWND threadedWPtwo::getWnd(void){
        return hwndParent;
    }
    void threadedWPtwo::setCurentWnd(HWND wndForSet){
        hwndParent = wndForSet;
    }
    HWND threadedWPtwo::getButton(void){
        return button0Parent;
    }
    void threadedWPtwo::setCurentButton(HWND buttonForSet){
        button0Parent = buttonForSet;
    }
void threadedWPtwo::save_page(const std::string &url)
{
    // simulate a long page fetch
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string result = "fake content";

    std::lock_guard<std::mutex> guard(g_pages_mutex);
    g_pages[url] = result;
}
int threadedWPtwo::doMain()
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
unsigned int __stdcall mythreadTwo(void* data)
{
    HINSTANCE g_hInst;
    HWND		hwnd;
    HWND button0;
    threadedWPtwo valThis;
    g_hInst = valThis.getInstance();
    hwnd = valThis.getWnd();
    button0 = CreateWindow("Button","0",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,80,220,35,35,hwnd,(HMENU)ID_BUTTON0,g_hInst,0);
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow( hwnd );
    std::cout <<"this is work:\n 0257 mythreadTwo:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();
    return 0;
}
int threadedWPtwo::doTwoThread(void){
    /**std::thread tOne1 = thread();
        tOne1.detach();
        isThreadStarted = true;*/
            HANDLE myhandleTwo;
    unsigned threadIDTwo;

    myhandleTwo = (HANDLE)_beginthreadex(NULL, 0, &mythreadTwo, NULL, 0, &threadIDTwo);
    //do{
        //whait
    //}while(true);
    std::cout <<"this is work:\n 0886 HANDLE:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();

    WaitForSingleObject(myhandleTwo, INFINITE);
    ReleaseMutex(myhandleTwo);
    CloseHandle(myhandleTwo);
        return 0;
}
void threadedWPtwo::setWndClass(char bukva, WNDCLASSEX wndClassInputed){
    iterTWM.insert(ThreadedWndMap::value_type(bukva,wndClassInputed));
}
WNDCLASSEX threadedWPtwo::getWndClass(char bukva){
    return iterTWM.at(bukva);
}
char threadedWPtwo::getBukva(void){
    return 'a';
}
void threadedWPtwo::setCurentBukva(char bukvaForSet){
    currentBukva = bukvaForSet;
}
int threadedWPtwo::closeTwoThread(){
     tTwo2.~thread();
     return 0;
}
