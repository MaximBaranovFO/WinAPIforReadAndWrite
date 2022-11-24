#pragma once
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <windows.h>


using namespace std;
class threadedWPthree
{
public:
    std::thread tThree3;
    bool isThreadStarted = false;
    //Constructors / Destructors
    threadedWPthree() noexcept{
        isThreadStarted = false;
    };


    int doMain(void);
    int doThreeThread(void);
    int closeThreeThread(void);
    //~bThOne();
    void setWndClass(char bukva, WNDCLASSEX wndClassInputed);
    WNDCLASSEX getWndClass(char bukva);
    char getBukva(void);
    void setCurentBukva(char bukvaForSet);
    ~threadedWPthree(){


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

void threadedWPthree::save_page(const std::string &url)
{
    // simulate a long page fetch
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string result = "fake content";

    std::lock_guard<std::mutex> guard(g_pages_mutex);
    g_pages[url] = result;
}
int threadedWPthree::doMain()
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
unsigned int __stdcall mythreadThree(void* data)
{
    std::cout <<"this is work:\n 0346 mythreadThree:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();
    return 0;
}
int threadedWPthree::doThreeThread(void){
    /**std::thread tOne1 = thread();
        tOne1.detach();
        isThreadStarted = true;*/
            HANDLE myhandleThree;
    unsigned threadIDThree;

    myhandleThree = (HANDLE)_beginthreadex(NULL, 0, &mythreadThree, NULL, 0, &threadIDThree);
    //do{
        //whait
    //}while(true);
    std::cout <<"this is work:\n 1173 HANDLE:Id from C++ API: 0x"<< std::hex << std::this_thread::get_id();

    WaitForSingleObject(myhandleThree, INFINITE);
    ReleaseMutex(myhandleThree);
    CloseHandle(myhandleThree);
        return 0;
}
void threadedWPthree::setWndClass(char bukva, WNDCLASSEX wndClassInputed){
    iterTWM.insert(ThreadedWndMap::value_type(bukva,wndClassInputed));
}
WNDCLASSEX threadedWPthree::getWndClass(char bukva){
    return iterTWM.at(bukva);
}
char threadedWPthree::getBukva(void){
    return 'a';
}
void threadedWPthree::setCurentBukva(char bukvaForSet){
    currentBukva = bukvaForSet;
}
int threadedWPthree::closeThreeThread(){
     tThree3.~thread();
     return 0;
}
