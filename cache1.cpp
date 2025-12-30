#include <iostream>
#include <vector>
#include <chrono>

struct Data {
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
       auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start_);

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

// output: 29401
// when ran with N = 100, output: 0 nanoseconds
