#ifndef LIMITED_LIST_H
#define LIMITED_LIST_H

namespace boarding {

// 类模板配合非类型模板参数，演示第 14 章的代码复用思想。
template <typename T, int Capacity>
class LimitedList {
private:
    // items 是固定容量的顺序表，用来保存最近历史记录等小规模数据。
    T items[Capacity];
    // currentSize 表示当前已经使用了多少个元素位置。
    int currentSize;

public:
    // 初始化时把逻辑长度设置为 0，表示当前还没有元素。
    LimitedList() : currentSize(0) {
    }

    // add 尝试把新元素加入顺序表。
    // 如果容量已满，就丢弃最旧元素并保留最新元素。
    bool add(const T& item) {
        if (currentSize < Capacity) {
            items[currentSize] = item;
            ++currentSize;
            return true;
        }

        for (int index = 1; index < Capacity; ++index) {
            items[index - 1] = items[index];
        }

        items[Capacity - 1] = item;
        return false;
    }

    // size 返回当前有效元素个数。
    int size() const {
        return currentSize;
    }

    // 下标运算符方便像数组一样访问内部元素。
    const T& operator[](int index) const {
        return items[index];
    }

    // clear 只重置逻辑长度，不必逐个销毁元素。
    void clear() {
        currentSize = 0;
    }
};

}  // namespace boarding

#endif
