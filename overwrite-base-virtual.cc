#include <iostream>

class I33base1 {                                                            
public:                                                                      
    virtual float foo(int &a) {
        std::cout << "i33 base" << std::endl;
        return 0.0;
    }
    virtual float foo() { return 0.0; }
};

class I33child1 : public I33base1 {
public:
    virtual float foo() { return 0.0; }
};

void test() {
  int j;
  I33child1 c1;
  c1.foo(j);
}
