#include <print>

class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void draw() = 0;
};

class Painter_1: public Drawable {
public: 
    void draw() override {
        int a = 45;
        std::print("painter 1: {}", a);
    }
};

class Painter_2: public Drawable {
public: 
    void draw() override {
        int a = 45;
        int b = 44;
        std::print("painter 2: {}, {}", a, b);
    }
};