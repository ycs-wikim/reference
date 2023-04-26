//
// Created by Woojin Choi on 2022/07/11.
//

#ifndef STL_STL_PAIR_H
#define STL_STL_PAIR_H


#include <iostream>
using namespace std;

template <typename T, typename S>
class STLPair {
private:

public:
    T first;
    S second;

    STLPair() : first(T()), second(S()) {
    }

    STLPair(T first, S second) : first(first), second(second) {
    }

    bool operator==(const STLPair<T, S> &kSTLPair) {
        if (first == kSTLPair.first) {
            if (second == kSTLPair.second) {
                return true;
            }
        }

        return false;
    }

    bool operator!=(const STLPair<T, S> &kSTLPair) {
        if (first != kSTLPair.first) {
            return true;
        }

        if (second != kSTLPair.second) {
            return true;
        }

        return false;
    }

    bool operator<(const STLPair<T, S> &kSTLPair) {
        if (first < kSTLPair.first) {
            return true;
        }

        if (second < kSTLPair.second) {
            return true;
        }

        return false;
    }

    bool operator>(const STLPair<T, S> &kSTLPair) {
        if (first > kSTLPair.first) {
            return true;
        }

        if (second > kSTLPair.second) {
            return true;
        }

        return false;
    }

    bool operator>=(const STLPair<T, S> &kSTLPair) {
        if (first >= kSTLPair.first) {
            if (second >= kSTLPair.second) {
                return true;
            }
        }

        return false;
    }

    bool operator<=(const STLPair<T, S> &kSTLPair) {
        if (first <= kSTLPair.first) {
            if (second <= kSTLPair.second) {
                return true;
            }
        }

        return false;
    }

    STLPair &operator=(const STLPair<T, S> &kSTLPair) {
        first = kSTLPair.first;
        second = kSTLPair.second;

        return *this;
    }

    void Swap(STLPair<T, S> &stl_pair) {
        T temp_first = first;
        S temp_second = second;

        first = stl_pair.first;
        second = stl_pair.second;

        stl_pair.first = temp_first;
        stl_pair.second = temp_second;
    }
};

template <typename T, typename S>
STLPair<T, S> MakePair(T first, S second) {
    return STLPair<T, S>{first, second};
}


#endif //STL_STL_PAIR_H
