#include <vector>
#include <utility>

template<typename T>
class SmartArray {
private:
    std::vector<T> data;
public:
    SmartArray(const std::vector<T> _data) : data(_data) {}
    ~SmartArray() = default;
    SmartArray(const SmartArray& other) : data(other.data) {}

    SmartArray& operator=(const SmartArray& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    SmartArray(std::vector<T>&& _data) : data(std::move(_data)) {}

    SmartArray& operator=(SmartArray&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

};