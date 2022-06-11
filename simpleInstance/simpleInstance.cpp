#include <iostream>
using namespace std;
class SingLaten
{
private:
public:
    SingLaten(){
        cout << "construct function" << endl;
    };
    // 让拷贝构造函数和操作符重载是禁用的状态
    SingLaten(const SingLaten& p) = delete;
    SingLaten& operator = (const SingLaten& p) = delete;
    static SingLaten& getInstance(){
        static SingLaten instance;
        return instance;
    }
    ~SingLaten(){

    };
};


class singlePattern {
private:
	singlePattern() {
        cout << "construct function1" << endl;
    };
	static singlePattern* p;
public:
	static singlePattern* instance();

	class CG {
	public:
		~CG() {
			if (singlePattern::p != nullptr) {
				delete singlePattern::p;
				singlePattern::p = nullptr;
			}
		}
	};
};

singlePattern* singlePattern::p = new singlePattern();
singlePattern* singlePattern::instance() {
	return p;
}
 
int main() {
    // static SingLaten& p1 = SingLaten::getInstance();
    // // 只会实体化一个对象
    // static SingLaten& p2 = SingLaten::getInstance();
    return 0;
}


