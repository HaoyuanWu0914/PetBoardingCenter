#include "../include/PetCenter.h"

#include <sstream>

#include "../include/Pet.h"
#include "../include/Utility.h"

namespace boarding {

// --------------------------------------------------------------------
// PetCenter.cpp 是整个项目的数据管理核心。
// 它负责：
// 1. 保存所有 Pet* 指针。
// 2. 统一管理动态内存。
// 3. 提供查找、排序、统计等功能。
// 4. 记录最近操作历史。
// 5. 演示二级指针、深拷贝、函数指针和模板函数的结合使用。
// 因此这个文件既是业务核心，也是课程知识点最集中的部分。
// --------------------------------------------------------------------

// 构造函数创建一个动态数组来保存 Pet* 指针。
PetCenter::PetCenter(int initialCapacity)
    : petArray(0),
      petCount(0),
      petCapacity(initialCapacity > 0 ? initialCapacity : DEFAULT_CAPACITY) {
    // petCapacity 决定初始最多能保存多少条记录。
    petArray = new Pet*[petCapacity];

    // 先把所有槽位初始化为空指针。
    for (int index = 0; index < petCapacity; ++index) {
        petArray[index] = 0;
    }

    // 记录系统创建时的第一条日志。
    recordOperation("寄养中心已创建。");
}

// 拷贝构造函数通过 copyFrom 完成深拷贝。
PetCenter::PetCenter(const PetCenter& other)
    : petArray(0),
      petCount(0),
      petCapacity(DEFAULT_CAPACITY) {
    copyFrom(other);
}

// 析构函数负责释放当前对象持有的所有动态资源。
PetCenter::~PetCenter() {
    destroyData();
}

// 赋值运算符同样需要遵循资源管理类的深拷贝规则。
PetCenter& PetCenter::operator=(const PetCenter& other) {
    if (this != &other) {
        // 先释放旧资源，再复制新资源。
        destroyData();
        copyFrom(other);
    }

    return *this;
}

// copyFrom 逐项复制另一个 PetCenter 的状态和宠物对象。
void PetCenter::copyFrom(const PetCenter& other) {
    // 先复制普通成员。
    petCapacity = other.petCapacity;
    petCount = other.petCount;
    operationHistory = other.operationHistory;

    // 再为当前对象创建自己的指针数组。
    petArray = new Pet*[petCapacity];

    for (int index = 0; index < petCapacity; ++index) {
        petArray[index] = 0;
    }

    // 最关键的一步是逐个 clone，确保这里执行的是深拷贝。
    // 如果只复制指针地址，两个 PetCenter 会共享同一批对象。
    for (int index = 0; index < petCount; ++index) {
        petArray[index] = other.petArray[index] == 0 ? 0 : other.petArray[index]->clone();
    }
}

// destroyData 统一负责释放宠物对象和指针数组。
void PetCenter::destroyData() {
    if (petArray != 0) {
        // 先释放数组中每一只真实存在的宠物对象。
        for (int index = 0; index < petCount; ++index) {
            delete petArray[index];
            petArray[index] = 0;
        }

        // 再释放保存指针的数组本身。
        delete[] petArray;
    }

    // 最后把对象状态恢复为空。
    petArray = 0;
    petCount = 0;
    petCapacity = 0;
}

// expandCapacity 在容量不足时重新申请更大的数组。
void PetCenter::expandCapacity() {
    // 这里采用翻倍扩容，逻辑简单也足够直观。
    const int newCapacity = petCapacity * 2;
    Pet** newArray = new Pet*[newCapacity];

    // 新数组先全部置为空指针。
    for (int index = 0; index < newCapacity; ++index) {
        newArray[index] = 0;
    }

    // 把旧数组中的指针逐个迁移到新数组。
    for (int index = 0; index < petCount; ++index) {
        newArray[index] = petArray[index];
    }

    // 释放旧数组并更新成员指向。
    delete[] petArray;
    petArray = newArray;
    petCapacity = newCapacity;
}

// addPet 把新建宠物对象交给寄养中心统一管理。
bool PetCenter::addPet(Pet* newPetPointer) {
    // 空指针没有业务意义，直接拒绝加入。
    if (newPetPointer == 0) {
        return false;
    }

    // 编号重复会影响查询唯一性，因此直接拒绝。
    if (containsPetId(newPetPointer->getPetId())) {
        return false;
    }

    // 如果数组已满，则先执行扩容。
    if (petCount >= petCapacity) {
        expandCapacity();
    }

    // 在数组尾部存入新对象。
    petArray[petCount] = newPetPointer;
    ++petCount;

    // 记录一条可读的新增日志。
    std::ostringstream operationText;
    operationText << "新增宠物记录: " << newPetPointer->getPetName()
                  << " (编号 " << newPetPointer->getPetId() << ")";
    recordOperation(operationText.str());
    return true;
}

// containsPetId 判断某个编号是否已经被占用。
bool PetCenter::containsPetId(int targetPetId) const {
    return findPetById(targetPetId) != 0;
}

// isEmpty 用于判断当前是否还没有任何记录。
bool PetCenter::isEmpty() const {
    return petCount == 0;
}

// size 返回当前保存的宠物总数。
int PetCenter::size() const {
    return petCount;
}

// findPetById 按编号顺序查找对应的宠物对象。
Pet* PetCenter::findPetById(int targetPetId) const {
    // 这里使用顺序查找，是因为教学项目更强调可读性。
    for (int index = 0; index < petCount; ++index) {
        if (petArray[index] != 0 && petArray[index]->getPetId() == targetPetId) {
            return petArray[index];
        }
    }

    return 0;
}

// 下标运算符让外部可以像访问数组一样访问宠物指针。
Pet* PetCenter::operator[](int index) const {
    // 越界访问时返回空指针，避免非法访问。
    if (index < 0 || index >= petCount) {
        return 0;
    }

    return petArray[index];
}

// clear 删除当前全部宠物记录，但保留容器对象本身。
void PetCenter::clear() {
    // 逐个删除当前保存的宠物对象。
    for (int index = 0; index < petCount; ++index) {
        delete petArray[index];
        petArray[index] = 0;
    }

    // 逻辑长度归零即可表示当前为空。
    petCount = 0;
    recordOperation("已清空当前所有宠物记录。");
}

// forEachPet 借助函数指针把同一个动作应用到所有宠物对象上。
void PetCenter::forEachPet(PetAction actionFunction) const {
    // 动作函数为空时，说明没有可执行操作。
    if (actionFunction == 0) {
        return;
    }

    // 逐个把宠物对象交给外部回调函数处理。
    for (int index = 0; index < petCount; ++index) {
        actionFunction(*petArray[index]);
    }
}

// sortBy 根据不同字段对宠物数组执行排序。
void PetCenter::sortBy(SortField sortField) {
    // 使用冒泡排序是为了让算法过程更容易看懂。
    for (int outerIndex = 0; outerIndex < petCount - 1; ++outerIndex) {
        for (int innerIndex = 0; innerIndex < petCount - outerIndex - 1; ++innerIndex) {
            // shouldSwap 决定当前相邻两项是否需要交换。
            bool shouldSwap = false;

            // leftPet 和 rightPet 表示参与比较的两个对象。
            const Pet* leftPet = petArray[innerIndex];
            const Pet* rightPet = petArray[innerIndex + 1];

            // 根据排序字段决定比较哪一个属性。
            switch (sortField) {
            case SortField::ById:
                shouldSwap = leftPet->getPetId() > rightPet->getPetId();
                break;
            case SortField::ByName:
                shouldSwap = leftPet->getPetName() > rightPet->getPetName();
                break;
            case SortField::ByAge:
                shouldSwap = leftPet->getPetAge() > rightPet->getPetAge();
                break;
            case SortField::ByDailyFee:
                shouldSwap = leftPet->calculateDailyFee() > rightPet->calculateDailyFee();
                break;
            }

            if (shouldSwap) {
                // 交换时复用模板交换函数，而不是手写三行交换代码。
                util::swapValues(petArray[innerIndex], petArray[innerIndex + 1]);
            }
        }
    }

    recordOperation("已按指定字段完成排序。");
}

// calculateTotalDailyFee 汇总所有宠物的单日收费。
double PetCenter::calculateTotalDailyFee() const {
    // totalFee 用来累加每天的总寄养费用。
    double totalFee = 0.0;

    for (int index = 0; index < petCount; ++index) {
        totalFee += petArray[index]->calculateDailyFee();
    }

    return totalFee;
}

// calculateTotalProjectedIncome 统计全部订单的预计总收入。
double PetCenter::calculateTotalProjectedIncome() const {
    // totalIncome 用来累加所有订单的预计总金额。
    double totalIncome = 0.0;

    for (int index = 0; index < petCount; ++index) {
        totalIncome += util::calculateProjectedIncome(
            petArray[index]->calculateDailyFee(),
            petArray[index]->getStayPlan().stayDays);
    }

    return totalIncome;
}

// calculateAverageAge 统计当前宠物的平均年龄。
double PetCenter::calculateAverageAge() const {
    // 没有记录时直接返回 0，避免除以 0。
    if (petCount == 0) {
        return 0.0;
    }

    // totalAge 用于累计所有宠物年龄。
    int totalAge = 0;

    for (int index = 0; index < petCount; ++index) {
        // 每只宠物的年龄都加入总和。
        totalAge += petArray[index]->getPetAge();
    }

    // 用总年龄除以记录数得到平均年龄。
    return static_cast<double>(totalAge) / petCount;
}

// countByKind 统计某一种宠物的数量。
int PetCenter::countByKind(PetKind petKind) const {
    // count 保存最终统计结果。
    int count = 0;

    for (int index = 0; index < petCount; ++index) {
        if (petArray[index]->getPetKind() == petKind) {
            ++count;
        }
    }

    return count;
}

// longestStayDays 计算所有记录中的最大寄养天数。
int PetCenter::longestStayDays() const {
    // longestValue 会不断被更新成当前已知最大值。
    int longestValue = 0;

    for (int index = 0; index < petCount; ++index) {
        longestValue = util::largerValue(longestValue, petArray[index]->getStayPlan().stayDays);
    }

    return longestValue;
}

// recordOperation 追加一条新的操作日志。
void PetCenter::recordOperation(const std::string& operationText) {
    operationHistory.add(operationText);
}

// getOperationHistory 返回最近操作历史的只读引用。
const LimitedList<std::string, 20>& PetCenter::getOperationHistory() const {
    return operationHistory;
}

}  // namespace boarding
