#include <iostream>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

class Task {
public:
    Task(std::string s) : s_(s) {
    };

    void CompleteTask() {
        std::cout << "Completed: " << s_ << std::endl;
    }

private:
    std::string s_;
};

class WorkingThread {
public:
    WorkingThread(std::function<void()> f) : f_(f), exit_signal_(false) {
    }

    void StartWorking() {
        while (true) {
            std::unique_lock lck(task_mtx_);

            task_signal_.wait(lck, [this]() {
                return task_.size() || exit_signal_;
            });

            if (task_.size() == 0) {
                return;
            }

            Task t = task_.front();
            task_.pop();
            lck.unlock();

            f_();
            t.CompleteTask();
        }
    }

    void AddTask(Task new_task) {
        std::lock_guard lck(task_mtx_);
        task_.push(new_task);
        task_signal_.notify_one();
    }

    void SignalExit() {
        std::lock_guard lck(task_mtx_);
        exit_signal_ = true;
        task_signal_.notify_one();
    }

private:
    std::function<void()> f_;
    std::queue<Task> task_;
    std::mutex task_mtx_;
    bool exit_signal_;
    std::condition_variable task_signal_;
};

/*
    Three kind of operations
        1. read
        2. write 
        3. delete 
*/

int main() {
    WorkingThread read_object([]() {
        std::cout << "Read thread" << std::endl;
    });
    std::thread read_thread(&WorkingThread::StartWorking, std::ref(read_object));

    WorkingThread write_object([]() {
        std::cout << "write thread" << std::endl;
    });
    std::thread write_thread(&WorkingThread::StartWorking, std::ref(write_object));

    WorkingThread update_object([]() {
        std::cout << "update thread" << std::endl;
    });
    std::thread update_thread(&WorkingThread::StartWorking, std::ref(update_object));

    while (true) {
        int op;
        std::string op_str;
        std::cin >> op;

        std::cout << op << std::endl;
        if (op == 0) {
            // exit signal
            read_object.SignalExit();
            write_object.SignalExit();
            update_object.SignalExit();
            break;
        }

        std::cin >> op_str;
        Task t(op_str);
        switch (op) {
            case 1: {
                        read_object.AddTask(t);
                        break;
                    }   
            case 2: {
                        write_object.AddTask(t);
                        break;
                    }  
            case 3: {
                        update_object.AddTask(t);
                        break;
                    }
            default: // ignore
                     break; // redundant? can remove it 
        }
    }

    std::cout << "Waiting for the worker threads to exit" << std::endl;
    read_thread.join();
    write_thread.join();
    update_thread.join();

    std::cout << "Closing text editor application" << std::endl;
    return 0;
}
