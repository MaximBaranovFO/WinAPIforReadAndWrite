#include <thread>
using namespace std;
class Xtwo {
public:
    void do_lengthy_work();
};

void Xtwo::do_lengthy_work(){
    std::this_thread::yield();
    cout << "\n--- --- ---Two Some for InterfaceThreaded: " << std::this_thread::get_id() << endl;
}
