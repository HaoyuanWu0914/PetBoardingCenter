#include "../include/FileStorage.h"

#include <fstream>

#include "../include/Pet.h"
#include "../include/PetCenter.h"
#include "../include/PetFactory.h"

namespace boarding {

// ---------------------------------------------------------------
// FileStorage.cpp 负责把内存中的对象状态写到文件，
// 或者把文件内容重新恢复为对象。
// 它体现了 fstream 文件读写、对象序列化、反序列化等知识点。
// ---------------------------------------------------------------

// saveCenter 负责把当前所有记录写入文本文件。
bool FileStorage::saveCenter(const PetCenter& petCenter, const std::string& filePath) {
    // outputFile 表示目标输出文件流。
    std::ofstream outputFile(filePath.c_str());

    // 文件无法打开时，直接返回失败。
    if (!outputFile.is_open()) {
        return false;
    }

    // 这里先制作一个快照对象，便于演示拷贝构造和深拷贝。
    // 这样即使后续保存逻辑扩展，也不会意外改动原对象。
    PetCenter snapshotCenter(petCenter);

    // 文件首行作为说明头，便于人工查看用途。
    outputFile << "# PetBoardingCenter data file" << '\n';

    // 后续每一行都保存一只宠物的序列化结果。
    for (int index = 0; index < snapshotCenter.size(); ++index) {
        // serializeData 会返回“单个对象的一行完整文本”。
        outputFile << snapshotCenter[index]->serializeData() << '\n';
    }

    // 正常写完全部数据后返回 true。
    return true;
}

// loadCenter 负责从文本文件恢复系统中的全部宠物数据。
bool FileStorage::loadCenter(PetCenter& petCenter, const std::string& filePath, int& loadedCount) {
    // inputFile 表示输入文件流。
    std::ifstream inputFile(filePath.c_str());

    // 文件不存在或打不开时，无法继续读取。
    if (!inputFile.is_open()) {
        return false;
    }

    // 先读入临时中心，全部成功后再整体赋值给正式对象。
    PetCenter temporaryCenter;
    std::string textLine;
    loadedCount = 0;

    while (std::getline(inputFile, textLine)) {
        // 每次尝试把一行文本恢复成一个 Pet 对象。
        Pet* loadedPet = PetFactory::createFromSavedLine(textLine);

        if (loadedPet != 0) {
            // 能成功 add 说明这一条记录有效且编号未冲突。
            if (temporaryCenter.addPet(loadedPet)) {
                ++loadedCount;
            } else {
                // 如果临时中心拒绝接收，必须手动释放对象。
                delete loadedPet;
            }
        }
    }

    // 用赋值运算符整体替换当前系统中的旧数据。
    petCenter = temporaryCenter;
    petCenter.recordOperation("已从文件加载宠物数据。");

    // 执行到这里说明本次加载流程已经完整结束。
    return true;
}

}  // namespace boarding
