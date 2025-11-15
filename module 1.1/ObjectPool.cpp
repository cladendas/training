#include <memory>
#include <stack>
#include <vector>
#include <mutex>
#include <optional>

struct Some_class {
    int num;
    std::string name;
};


template<typename T>
class ObjectPool {
private:
    std::stack<std::unique_ptr<T>> available;
    std::vector<std::unique_ptr<T>> in_use;
    std::mutex m;
public:
    ObjectPool(const size_t& count) {
        for (size_t i = 0; i < count; i++) {
            available.push(std::make_unique<T>());
        }
        in_use.reserve(count / 2);
    }

    std::unique_ptr<T> acquire() {
        std::lock_guard<std::mutex> lock(m);
        if (available.empty()) {
            return nullptr; // или бросить исключение
        }
        
        auto obj = std::move(available.top());
        available.pop();
        in_use.push_back(std::move(obj));
        
        // Создаем специальный unique_ptr с custom deleter для автоматического возврата
        return std::unique_ptr<T>(in_use.back().get(), [this](T* ptr) {
            this->release(ptr);
        });
    }

    void release(T* object) {
        std::lock_guard<std::mutex> lock(m);
        
        // Находим и перемещаем объект обратно в available
        auto it = std::find_if(in_use.begin(), in_use.end(),
            [object](const std::unique_ptr<T>& ptr) {
                return ptr.get() == object;
            });
            
        if (it != in_use.end()) {
            available.push(std::move(*it));
            in_use.erase(it);
        }
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return available.empty();
    }

    size_t available_count() const {
        std::lock_guard<std::mutex> lock(m);
        return available.size();
    }

    size_t in_use_count() const {
        std::lock_guard<std::mutex> lock(m);
        return in_use.size();
    }
};


int main() {


    return 0;
}