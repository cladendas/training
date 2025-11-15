#include <print>
#include <queue>
#include <mutex>
#include <vector>

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> data;
    std::mutex m;
public:
    ThreadSafeQueue() = default;

    void push(T value) {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(value));
    }
    
    std::optional<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if (empty()) {
            return std::nullopt;
        } else {
            T elem = std::move(data.front());
            data.pop();
            return elem;
        }
    } 
    
    bool empty() const noexcept {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }

    ~ThreadSafeQueue() {}
};


int main() {

    return 0;
}