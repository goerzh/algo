#ifndef ALGO_VEC_TEST_H
#define ALGO_VEC_TEST_H

#include <cstdlib>
#include <vector>

namespace myalgo {

void *mymemcpy(void *dst, const void *src, size_t count) {
    if (dst == nullptr || src == nullptr)
        return nullptr;
    char *pdest = (char *) (dst);
    const char *psrc = (char *) (src);
    int n = count;
    //pdest地址高于psrc地址，且有重叠
    if (pdest > psrc && pdest < psrc + count) {
        for (size_t i = n - 1; i != -1; --i) {
            pdest[i] = psrc[i];//从高到低赋值
        }
    }
        //pdest地址低于psrc地址，且有重叠
    else if (pdest < psrc && pdest > psrc - count) {
        for (size_t i = 0; i < n; i++) {
            pdest[i] = psrc[i];//从低到高赋值
        }
    }
    return dst;
}

template<typename T>
class Vec {
public:
    typedef T value_type;

    explicit Vec(int cap) : cap(cap), len(0), v_len(0) {
        pointer = (T *) malloc(cap * sizeof(T));
        for (int i = 0; i < cap; i++) {
            pointer[i] = 0;
        }
    }

    Vec() : Vec(10) {}

    void insert(int index, T value) {
        assert(index <= len);
        check_cap();
        if (index < len) {
            memcpy(pointer + index + 1, pointer + index, len - index);
        }
        pointer[index] = value;
        len++;
        v_len++;
    }

    void push_back(T value) {
        check_cap();

        pointer[len] = value;
        len++;
        v_len++;
    }

    T get(int index) {
        int offset = get_offset(index);
        int new_index = index + offset;

        assert(new_index < v_len);
        return pointer[index + offset];
    }

    void remove(int index) {
        mark.push_back(index);
        std::sort(mark.begin(), mark.end());
        len--;
    }

    int capital() {
        return cap;
    }

    ~Vec() {
        free(pointer);
    }

private:
    int get_offset(int index) {
        int count = 0;
        for (auto i = mark.begin(); i != mark.end(); ++i) {
            if (*i <= index) {
                count++;
            }
        }

        return count;
    }

    void gc() {
        if (len != v_len) {
            for (auto i = mark.begin(); i != mark.end(); ++i) {
                mymemcpy(pointer + *i, pointer + *i + 1, len - *i);
            }
            v_len = len;
        }
    }

    void check_cap() {
        if (v_len >= cap) {
            gc();
            reset();
        }
    }

    void reset() {
        if (v_len >= cap) {
            cap *= 2;
            T *tem_p = (T *) malloc(cap * sizeof(T));
            for (int i = 0; i < v_len; ++i) {
                tem_p[i] = pointer[i];
            }
            free(pointer);
            pointer = tem_p;
        }
    }

private:
    T *pointer;
    int len;
    int v_len;
    int cap;
    std::vector<int> mark;
};
}

#endif //ALGO_VEC_TEST_H
