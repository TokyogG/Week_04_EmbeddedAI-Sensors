#pragma once
#include <array>
#include <cstddef>

template <typename T, std::size_t Capacity>
class RingBuffer {
public:
    static_assert(Capacity > 0, "Capacity must be > 0");

    bool push(const T& item) {
        if (full_) {
            // overwrite oldest (common embedded policy)
            tail_ = (tail_ + 1) % Capacity;
        }
        buf_[head_] = item;
        head_ = (head_ + 1) % Capacity;
        full_ = (head_ == tail_);
        return true;
    }

    bool pop(T& out) {
        if (empty()) return false;
        out = buf_[tail_];
        full_ = false;
        tail_ = (tail_ + 1) % Capacity;
        return true;
    }

    bool empty() const { return (!full_ && head_ == tail_); }
    bool full()  const { return full_; }

    std::size_t size() const {
        if (full_) return Capacity;
        if (head_ >= tail_) return head_ - tail_;
        return Capacity + head_ - tail_;
    }

    constexpr std::size_t capacity() const { return Capacity; }

private:
    std::array<T, Capacity> buf_{};
    std::size_t head_ = 0; // next write
    std::size_t tail_ = 0; // next read
    bool full_ = false;
};