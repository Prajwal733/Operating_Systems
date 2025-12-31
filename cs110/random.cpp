template <typename T>
class ThreadSafePQ {
    std::priority_queue<T> pq;
    std::mutex mtx;
    std::condition_variable cv;

public:
    void push(T value) {
        // Your code here
        std::lock_guard lck(mtx);
        pq.push(value);
        cv.notify_one(); // only one thread can proceed. 
    }

    T pop() {
        // Your code here
        std::unique_lock lck(mtx);
        cv.wait(lck, [&pq]() {
            return pq.size() != 0;
        });

        T top_item = pq.top();
        pq.pop();
        lck.unlock();

        // do work on top_item
        top_item.do_work();
    }
};

// Misses lot of corner cases :(
class LRU {
public:
    LRU (int capacity) capacity_(capacity) {
        head_ = NULL;
        tail_ = NULL;
    }

    ~LRU() {
        while (head_) {
            Node* delete_node = head_;
            head_ = head_->next;
            delete delete_node;
        }
    }

    LRU(LRU& other) = delete; // not copyable
    LRU operator= (LRU& other) = delete;

    int Get(int key) {
        auto it = key_to_node_.find(key);

        if (it == key_to_node_.end()) {
            return -1;
        }

        int value = it->second.value; // value stored in the Node. 
        MarkRecentlyAccessed(it->second);
    }

    void Put(int key, int value) {
        auto it = key_to_node_.find(key);

        if (it == key_to_node_.end()) {
            Node* new_node = new Node();
            new_node->key = key;
            new_node->value = value;

            key_to_node_[key] = new_node;
            UpdateHeadToNode(new_node);
            capacity_--;
            EvictIfExceeded();
        } else {
            it->second.value = value;
            MarkRecentlyAccessed(it->second);
        }
    }

private:
    struct Node {
        int key;
        int value;
        Node* next;
        Node* previous;
    };

    void MarkRecentlyAccessed(Node* node) {
        if (tail_ == node) {
            tail_ = tail_->previous;
        }

        if (node->previous) {
            node->previous->next = node->next;
        }

        if (node->next) {
            node->next->previous = node->previous;
        }
    
        node->previous = NULL;
        UpdateHeadToNode(node);
    }

    void UpdateHeadToNode(Node* node) {
        if (head_ != node) {
            head_->previous = node;
            node->next = head_;
            head_ = node;
        }
    }

    void EvictIfExceeded() {
        if (capacity_ == -1) {
            Node* node_to_delete = tail_;
            int key_to_erase = node_to_delete->key;

            tail_ = tail_->previous;
            if (tail_ == NULL) { // if capacity itself is 1. 
                head_ = NULL;
            }

            key_to_node_.erase(key_to_erase);
            delete node_to_delete;
        }
    }

    int capacity_;
    Node* head_;
    Node* tail_;
    map<int, Node*> key_to_node_;
};
