#ifndef HANDLEMANAGER_H
#define HANDLEMANAGER_H

#include <QObject>
#include <QVector>
#include <QQueue>
#include <QMutex>
#include <QMutexLocker>
#include <QSharedPointer>

/**
 * @brief 带版本号的句柄管理器，用于管理多路视频流资源
 * @tparam T 资源类型，必须继承自QObject
 */
template <typename T>
class HandleManager {
public:
    using Handle = int;  // 使用 int 类型作为句柄

    static_assert(std::is_base_of<QObject, T>::value, "T must inherit from QObject");

    HandleManager() = default;

    // 创建句柄，关联资源
    Handle createHandle(T* resource) {
        QMutexLocker locker(&mutex_);

        quint32 index;
        quint32 version;

        if (!freeList_.isEmpty()) {
            index = freeList_.dequeue();              // 从回收列表中取出索引
            version = entries_[index].version + 1;   // 更新版本号
        } else {
            index = static_cast<quint32>(entries_.size());
            version = 1;                             // 初始版本号为 1
            entries_.append(HandleEntry());         // 初始化新的条目
        }

        entries_[index].resource = QSharedPointer<T>(resource);
        entries_[index].version = version;

        return encodeHandle(index, version);         // 返回编码后的句柄
    }

    // 释放句柄
    void releaseHandle(Handle handle) {
        QMutexLocker locker(&mutex_);

        quint32 index, version;
        decodeHandle(handle, index, version);

        if (index >= static_cast<quint32>(entries_.size()) || entries_[index].version != version) {
            return; // 非法或已释放的句柄，忽略
        }

        auto& entry = entries_[index];
        entry.resource.clear();          // 清空资源
        freeList_.enqueue(index);        // 将索引加入回收列表
    }

    // 根据句柄获取资源
    T* getResource(Handle handle) const {
        QMutexLocker locker(&mutex_);

        quint32 index, version;
        decodeHandle(handle, index, version);

        if (index >= static_cast<quint32>(entries_.size()) || entries_[index].version != version) {
            return nullptr; // 非法或已释放的句柄
        }

        return entries_[index].resource.data();
    }

    // 获取所有有效的句柄
    QList<Handle> getAllHandles() const {
        QMutexLocker locker(&mutex_);
        QList<Handle> handles;
        
        for (int i = 0; i < entries_.size(); ++i) {
            if (entries_[i].resource) {
                handles.append(encodeHandle(i, entries_[i].version));
            }
        }
        return handles;
    }

    // 获取资源数量
    int size() const {
        QMutexLocker locker(&mutex_);
        int count = 0;
        for (const auto& entry : entries_) {
            if (entry.resource) {
                count++;
            }
        }
        return count;
    }

private:
    struct HandleEntry {
        QSharedPointer<T> resource;  // 使用 QSharedPointer 管理资源
        quint32 version = 0;         // 版本号

        HandleEntry() : resource(nullptr), version(0) {} // 默认构造函数
        HandleEntry(QSharedPointer<T> res, quint32 ver) : resource(std::move(res)), version(ver) {}
    };

    QVector<HandleEntry> entries_;   // 句柄表
    QQueue<quint32> freeList_;       // 自由链表（回收队列）
    mutable QMutex mutex_;           // 线程安全锁

    // 编码句柄，将索引和版本号合成为一个整数
    Handle encodeHandle(quint32 index, quint32 version) const {
        return (version << 16) | (index & 0xFFFF); // 高 16 位是版本号，低 16 位是索引
    }

    // 解码句柄，拆分为索引和版本号
    void decodeHandle(Handle handle, quint32& index, quint32& version) const {
        version = static_cast<quint32>(handle >> 16);
        index = static_cast<quint32>(handle & 0xFFFF);
    }
};

#endif // HANDLEMANAGER_H