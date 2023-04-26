//
// Created by Woojin Choi on 2022/07/07.
//

#ifndef STL_STL_VECTOR_H
#define STL_STL_VECTOR_H


#include <iostream>
using namespace std;

template <typename T> /// T, S, U, V
class STLVector {
private:
    T *array_;
    size_t size_;
    size_t capacity_;

    class Iterator {
    private:
        T *array_;
    public:
        Iterator(T *array = nullptr) : array_(array) { /// 객체 생성과 동시에 멤버 변수를 초기화
        }

        Iterator &operator++() {
            ++array_;
            return *this;
        }

        Iterator &operator++(int) {
            array_++;
            return *this;
        }

        Iterator &operator--() {
            --array_;
            return *this;
        }

        Iterator operator--(int) {
            array_--;
            return *this;
        }

        Iterator &operator+=(int value) {
            array_ += value;
            return *this;
        }

        Iterator &operator-=(int value) {
            array_ -= value;
            return *this;
        }

        T &operator[](int index) {
            return array_[index];
        }

        T &operator*() {
            return *array_;
        }

        Iterator operator+(int value) {
            return array_ + value;
        }

        Iterator operator-(int value) {
            return array_ - value;
        }

        int operator-(const Iterator &kIterator) { /// 상대적 거리를 계산하기 위해 -연산자 재할당
            return array_ - kIterator.array_;
        }

        bool operator==(const Iterator &kIterator) {
            return array_ == kIterator.array_;
        }

        bool operator!=(const Iterator &kIterator) {
            return array_ != kIterator.array_;
        }
    };

    class ReverseIterator {
    private:
        T *array_;
    public:
        ReverseIterator(T *array = nullptr) : array_(array) { /// 객체 생성과 동시에 멤버 변수를 초기화
        }

        ReverseIterator &operator++() {
            --array_;
            return *this;
        }

        ReverseIterator &operator++(int) {
            array_--;
            return *this;
        }

        ReverseIterator &operator--() {
            ++array_;
            return *this;
        }

        ReverseIterator &operator--(int) {
            array_++;
            return *this;
        }

        ReverseIterator &operator+=(int value) {
            array_ -= value;
            return *this;
        }

        ReverseIterator &operator-=(int value) {
            array_ += value;
            return *this;
        }

        T &operator[](int index) {
            return array_[index];
        }

        T &operator*() {
            return *array_;
        }

        ReverseIterator operator+(int value) {
            return array_ - value;
        }

        ReverseIterator operator-(int value) {
            return array_ + value;
        }

        bool operator==(const ReverseIterator &kReverseIterator) {
            return array_ == kReverseIterator.array_;
        }

        bool operator!=(const ReverseIterator &kReverseIterator) {
            return array_ != kReverseIterator.array_;
        }
    };
public:
    typedef Iterator Iterator;
    typedef ReverseIterator ReverseIterator;

    STLVector() {
        size_ = 0;
        capacity_ = 0;
        array_ = new T[capacity_];
    }

    STLVector(size_t size) {
        size_ = size;
        capacity_ = size;
        array_ = new T[size];

        for (size_t i = 0; i < size; i++) {
            array_[i] = T();
        }
    }

    STLVector(size_t size, T value) {
        size_ = size;
        capacity_ = size;
        array_ = new T[size];

        for (int i = 0; i < size; i++) {
            array_[i] = value;
        }
    }

    ~STLVector() {
        delete[] array_;
    }

    STLVector &operator=(const STLVector &kSTLVector) {
        T *temp = new T[kSTLVector.size_];

        for (size_t i = 0; i < kSTLVector.size_; i++) {
            temp[i] = kSTLVector.array_[i];
        }

        delete[] array_;

        size_ = kSTLVector.size_;
        capacity_ = kSTLVector.size_;
        array_ = temp;

        return *this;
    }

    bool operator==(const STLVector &kSTLVector) {
        if (size_ != kSTLVector.size_) {
            return false;
        }

        for (size_t i = 0; i < size_; i++) {
            if (array_[i] != kSTLVector.array_[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const STLVector &kSTLVector) {
        if (size_ == kSTLVector.size_) {
            return false;
        }

        for (size_t i = 0; i < size_; i++) {
            if (array_[i] == kSTLVector.array_[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator>(const STLVector &kSTLVector) {
        return size_ < kSTLVector.size_;
    }

    bool operator<(const STLVector &kSTLVector) {
        return size_ > kSTLVector.size_;
    }

    T &operator[](int index) {
        return array_[index];
    }

    void PushBack(T value) {
        if (size_ + 1 >= capacity_) {
            if (capacity_ == 0) {
                Reserve(capacity_ + 1);
            } else {
                Reserve(capacity_ * 2);
            }
        }

        array_[size_++] = value;
    }

    void PopBack() {
        size_--;
    }

    void Assign(size_t size, T value) {
        delete[] array_;

        size_ = size;
        capacity_ = size;
        array_ = new T[size];

        for (size_t i = 0; i < size; i++) {
            array_[i] = value;
        }
    }

    T &At(int index) {
        if (index <= size_ - 1) {
            return array_[index];
        } else {
            throw out_of_range("vector"); /// 예외 발생
        }
    }

    T &Front() {
        return array_[0];
    }

    T &Back() {
        return array_[size_ - 1];
    }

    void Swap(STLVector &stl_vector) {
        T *temp_array = array_;
        size_t temp_size = size_;
        size_t temp_capacity = capacity_;

        delete[] array_;

        array_ = stl_vector.array_;
        size_ = stl_vector.size_;
        capacity_ = stl_vector.capacity_;

        delete[] stl_vector.array_;

        stl_vector.array_ = temp_array;
        stl_vector.size_ = temp_size;
        stl_vector.capacity_ = temp_capacity;
    }

    void Reserve(size_t new_capacity) {
        capacity_ = new_capacity;
        T *temp = new T[new_capacity];

        for (size_t i = 0; i < size_; i++) {
            temp[i] = array_[i];
        }

        delete[] array_;
        array_ = temp;
    }

    void Resize(size_t new_size) {
        T *temp = new T[new_size];

        if (new_size > size_) {
            for (size_t i = 0; i < new_size; i++) {
                temp[i] = array_[i];
            }
        } else {
            for (size_t i = 0; i < new_size; i++) {
                temp[i] = array_[i];
            }
        }

        delete[] array_;

        size_ = new_size;
        capacity_ = new_size;
        array_ = temp;
    }

    void Resize(size_t new_size, int value) {
        T *temp = new T[new_size];

        if (new_size > size_) {
            for (size_t i = 0; i < new_size; i++) {
                if (i > size_ - 1) {
                    temp[i] = value;
                } else {
                    temp[i] = array_[i];
                }
            }
        } else {
            for (size_t i = 0; i < new_size; i++) {
                temp[i] = array_[i];
            }
        }

        delete[] array_;

        size_ = new_size;
        capacity_ = new_size;
        array_ = temp;
    }

    bool Empty() {
        return size_ == 0;
    }

    void Clear() {
        size_ = 0;
    }

    int Size() {
        return size_;
    }

    int Capacity() {
        return capacity_;
    }

    Iterator Begin() {
        return Iterator(array_);
    }

    Iterator End() {
        return Iterator(array_ + size_);
    }

    ReverseIterator RBegin() {
        return ReverseIterator(array_ + (size_ - 1));
    }

    ReverseIterator REnd() {
        return ReverseIterator(array_ - 1);
    }

    Iterator Insert(Iterator position, T value) {
        size_t index = position - array_;

        if (size_ + 1 >= capacity_) {
            Reserve(capacity_ * 2);
        }

        for (size_t i = size_; i > index; i--) {
            array_[i] = array_[i - 1];
        }

        array_[index] = value;
        size_++;

        return Iterator(array_ + index);
    }

    Iterator Insert(Iterator position, size_t amount, T value) {
        size_t index = position - array_;
        size_t new_capacity = capacity_ * 2;

        if (size_ + amount >= capacity_) {
            if (size_ + amount > new_capacity) {
                Reserve(size_ + amount);
            } else {
                Reserve(new_capacity);
            }
        }

        for (size_t i = size_ + amount; i > index; i--) {
            array_[i] = array_[i - amount];
        }

        for (size_t i = 0; i < amount; i++) {
            array_[index + i] = value;
        }

        size_ += amount;

        return Iterator(array_ + index);
    }

    Iterator Insert(Iterator position, Iterator start, Iterator end) {
        size_t index = position - array_;
        size_t size = end - start;
        size_t new_capacity = capacity_ * 2;

        if (size_ + size >= capacity_) {
            if (size_ + size > new_capacity) {
                Reserve(size_ + size);
            } else {
                Reserve(new_capacity);
            }
        }

        for (size_t i = size_ + size; i > index; i--) {
            array_[i] = array_[i - size];
        }

        for (size_t i = 0; i < size; i++) {
            array_[index + i] = *start;
            start++;
        }

        size_ += size;
        return Iterator(array_ + index);
    }

    void Erase(Iterator position) {
        size_t index = position - array_;

        for (size_t i = index + 1; i < size_; i++) {
            array_[i - 1] = array_[i];
        }

        size_--;
    }

    void Erase(Iterator start, Iterator end) {
        size_t start_index = start - array_;
        size_t end_index = end - array_;
        size_t distance = end_index - start_index;

        for (size_t i = end_index; i < size_; i++) {
            array_[i - distance] = array_[i];
        }

        size_ -= distance;
    }
};

#endif //STL_STL_VECTOR_H
