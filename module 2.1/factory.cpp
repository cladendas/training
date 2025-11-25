#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include <print>
#include <cmath>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};

class Circle: public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override {
        return M_PI * radius * radius;
    }

    double perimeter() const override {
        return 2 * M_PI * radius;
    }
};

class Rectangle: public Shape {
private:
    double width;
    double height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }
};

class Factory {
private:
    using Creator = std::function<std::unique_ptr<Shape>()>;
    std::unordered_map<std::string, Creator> _creators;
public:
    static Factory& instance() {
        static Factory factory;
        return factory;
    }

    void registerCreator(const std::string& type, Creator creator) {
        _creators[type] = std::move(creator);
    }

    std::unique_ptr<Shape> create(const std::string& type) {
        auto it = _creators.find(type);

        if (it != _creators.end()) {
            return it->second();
        }

        throw std::invalid_argument("Unknow type: " + type);
    }

    std::vector<std::string> getAvailableTypes() const {
        std::vector<std::string> types;
        for (const auto& [type, _] : _creators)
        {
            types.emplace_back(type);
        }
        return types;
    }
};

int main() {

    auto& factory = Factory::instance();

    factory.registerCreator("Circle", []() {
        return std::make_unique<Circle>(5.0);
    });

    factory.registerCreator("Rectangle", []() {
        return std::make_unique<Rectangle>(4, 5);
    });

    for (const auto& type : factory.getAvailableTypes())
    {
        std::println("{}", type);
    }

    try {
        auto circle = factory.create("Circle");
        auto rectangle = factory.create("Rectangle");

        std::println("Circle area: {}", circle->area());
        std::println("Rectangle perimeter: {}", rectangle->perimeter());

    } catch (const std::exception& e) {
        std::println("Error: {}", e.what());
    }
    

    return 0;
}