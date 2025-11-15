#include <print>
#include <mutex>
#include <vector>
#include <type_traits>
#include <thread>

template<typename T>
requires std::is_arithmetic_v<T>
class Accumulate {
private:
    T sum;
    std::mutex m;

    void accumulate(typename std::vector<T>::const_iterator begin,
                    typename std::vector<T>::const_iterator end) {
        T tmp_sum = T{};
        for (auto it = begin; it != end; it++) {
            tmp_sum += *it;
        }
        
        std::lock_guard<std::mutex> lock(m);
        sum += tmp_sum;
    }
public:
    Accumulate() : sum(T{}) {}
    T parallel_accumulate(const std::vector<T>& values) {
        if (values.empty()) {
            return T{};
        } else if (values.size() == 1) {
            return values[0];
        } else {
            sum = T{};
            auto middle = values.begin() + (values.size() / 2);
            std::thread t_1(&Accumulate::accumulate, this, values.begin(), middle);
            std::thread t_2(&Accumulate::accumulate, this, middle, values.end());

            t_1.join();
            t_2.join();

            return sum;
        }
    }
};


int main() {

    return 0;
}