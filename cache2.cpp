#include <iostream>
#include <vector>
#include <chrono>

struct alignas(1 << 24) Data {
    int item;
};

class CountTime {
public:
    CountTime() = default;
    ~CountTime() = default;

    void NoteStart() {
        start_ = std::chrono::steady_clock::now();
    }

    int GetDuration() {
       auto end = std::chrono::steady_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start_);

       return duration.count();
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> start_;
};

int main() {
    const int N = 100;
    CountTime c;

    std::vector<Data> all_data(N);

    c.NoteStart();
    for (int i=0;i<N;i++) {
        all_data[i].item = i + 5;
    }

    for (int i=0;i<N;i++) {
        all_data[i];
    }
    std::cout << c.GetDuration() << std::endl;

    return 0;
}

// output: 95222 (time is high because of padding added, L1 cache usual size is 64 Bytes)
// when ran with N = 100, and alignas (1 << 24) (more than L3 cache? 2-64 MB?) 6402 nanoseconds (0 vs 6402)
