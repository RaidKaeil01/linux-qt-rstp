/****************************************************************************
** Meta object code from reading C++ file 'MultiStreamManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "MultiStreamManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MultiStreamManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MultiStreamManager_t {
    QByteArrayData data[14];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MultiStreamManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MultiStreamManager_t qt_meta_stringdata_MultiStreamManager = {
    {
QT_MOC_LITERAL(0, 0, 18), // "MultiStreamManager"
QT_MOC_LITERAL(1, 19, 10), // "frameReady"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6), // "handle"
QT_MOC_LITERAL(4, 38, 5), // "frame"
QT_MOC_LITERAL(5, 44, 15), // "streamConnected"
QT_MOC_LITERAL(6, 60, 3), // "url"
QT_MOC_LITERAL(7, 64, 18), // "streamDisconnected"
QT_MOC_LITERAL(8, 83, 11), // "streamError"
QT_MOC_LITERAL(9, 95, 5), // "error"
QT_MOC_LITERAL(10, 101, 12), // "onFrameReady"
QT_MOC_LITERAL(11, 114, 25), // "onConnectionStatusChanged"
QT_MOC_LITERAL(12, 140, 9), // "connected"
QT_MOC_LITERAL(13, 150, 15) // "onErrorOccurred"

    },
    "MultiStreamManager\0frameReady\0\0handle\0"
    "frame\0streamConnected\0url\0streamDisconnected\0"
    "streamError\0error\0onFrameReady\0"
    "onConnectionStatusChanged\0connected\0"
    "onErrorOccurred"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MultiStreamManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       5,    2,   54,    2, 0x06 /* Public */,
       7,    2,   59,    2, 0x06 /* Public */,
       8,    2,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   69,    2, 0x08 /* Private */,
      11,    1,   72,    2, 0x08 /* Private */,
      13,    1,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QImage,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    4,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void MultiStreamManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MultiStreamManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->frameReady((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QImage(*)>(_a[2]))); break;
        case 1: _t->streamConnected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->streamDisconnected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->streamError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->onFrameReady((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 5: _t->onConnectionStatusChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->onErrorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MultiStreamManager::*)(int , const QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiStreamManager::frameReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MultiStreamManager::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiStreamManager::streamConnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MultiStreamManager::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiStreamManager::streamDisconnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MultiStreamManager::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiStreamManager::streamError)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MultiStreamManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MultiStreamManager.data,
    qt_meta_data_MultiStreamManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MultiStreamManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MultiStreamManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MultiStreamManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MultiStreamManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void MultiStreamManager::frameReady(int _t1, const QImage & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MultiStreamManager::streamConnected(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MultiStreamManager::streamDisconnected(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MultiStreamManager::streamError(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
