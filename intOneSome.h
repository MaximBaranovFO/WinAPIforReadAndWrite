#include <thread>
using namespace std;
class X {
public:
    void do_lengthy_work();
};

void X::do_lengthy_work(){
    cout << "Some for InterfaceThreaded: " << std::this_thread::get_id() << endl;
}
