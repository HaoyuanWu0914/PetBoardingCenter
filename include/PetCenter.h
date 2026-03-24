#ifndef PET_CENTER_H
#define PET_CENTER_H

#include <string>

#include "CommonTypes.h"
#include "LimitedList.h"

namespace boarding {

class Pet;

// PetCenter 负责动态存储宠物对象，并统一管理内存。
class PetCenter {
private:
    // petArray 是一个二级指针，指向动态分配的 Pet* 数组。
    Pet** petArray;
    // petCount 表示当前实际保存了多少只宠物。
    int petCount;
    // petCapacity 表示 petArray 当前最多能容纳多少个指针。
    int petCapacity;
    // operationHistory 用于记录最近的操作日志。
    LimitedList<std::string, 20> operationHistory;

    // copyFrom 负责执行深拷贝。
    void copyFrom(const PetCenter& other);
    // destroyData 负责释放当前对象持有的所有动态资源。
    void destroyData();
    // expandCapacity 在容量不足时扩容。
    void expandCapacity();

public:
    // DEFAULT_CAPACITY 表示初始默认容量。
    static const int DEFAULT_CAPACITY = 4;

    // 一组构造、析构和赋值函数体现资源管理类的“三/五法则”思想。
    explicit PetCenter(int initialCapacity = DEFAULT_CAPACITY);
    PetCenter(const PetCenter& other);
    ~PetCenter();

    PetCenter& operator=(const PetCenter& other);

    // addPet 把新建的宠物对象交给中心管理。
    bool addPet(Pet* newPetPointer);
    // containsPetId 用于判断编号是否已存在。
    bool containsPetId(int targetPetId) const;
    // isEmpty 用于快速判断当前是否为空。
    bool isEmpty() const;
    // size 返回当前记录数。
    int size() const;

    // findPetById 根据编号查找宠物对象。
    Pet* findPetById(int targetPetId) const;
    // 下标运算符为遍历和保存文件提供方便的只读访问。
    Pet* operator[](int index) const;

    // clear 删除全部宠物记录。
    void clear();
    // forEachPet 通过函数指针对所有宠物做统一操作。
    void forEachPet(PetAction actionFunction) const;
    // sortBy 按指定字段排序。
    void sortBy(SortField sortField);

    // 下面这些统计函数分别服务于菜单中的分析功能。
    double calculateTotalDailyFee() const;
    double calculateTotalProjectedIncome() const;
    double calculateAverageAge() const;
    int countByKind(PetKind petKind) const;
    int longestStayDays() const;

    // recordOperation 负责追加一条操作历史。
    void recordOperation(const std::string& operationText);
    // getOperationHistory 返回历史容器的只读引用。
    const LimitedList<std::string, 20>& getOperationHistory() const;
};

}  // namespace boarding

#endif
