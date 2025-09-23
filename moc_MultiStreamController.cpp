/****************************************************************************
** Meta object code from reading C++ file 'MultiStreamController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "MultiStreamController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MultiStreamController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MultiStreamController_t {
    QByteArrayData data[25];
    char stringdata0[313];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MultiStreamController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MultiStreamController_t qt_meta_stringdata_MultiStreamController = {
    {
QT_MOC_LITERAL(0, 0, 21), // "MultiStreamController"
QT_MOC_LITERAL(1, 22, 11), // "streamAdded"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 6), // "handle"
QT_MOC_LITERAL(4, 42, 3), // "url"
QT_MOC_LITERAL(5, 46, 13), // "streamRemoved"
QT_MOC_LITERAL(6, 60, 15), // "streamConnected"
QT_MOC_LITERAL(7, 76, 18), // "streamDisconnected"
QT_MOC_LITERAL(8, 95, 11), // "streamError"
QT_MOC_LITERAL(9, 107, 5), // "error"
QT_MOC_LITERAL(10, 113, 13), // "videoSelected"
QT_MOC_LITERAL(11, 127, 11), // "globalIndex"
QT_MOC_LITERAL(12, 139, 13), // "layoutChanged"
QT_MOC_LITERAL(13, 153, 10), // "GridLayout"
QT_MOC_LITERAL(14, 164, 6), // "layout"
QT_MOC_LITERAL(15, 171, 11), // "pageChanged"
QT_MOC_LITERAL(16, 183, 4), // "page"
QT_MOC_LITERAL(17, 188, 12), // "onFrameReady"
QT_MOC_LITERAL(18, 201, 5), // "frame"
QT_MOC_LITERAL(19, 207, 17), // "onStreamConnected"
QT_MOC_LITERAL(20, 225, 20), // "onStreamDisconnected"
QT_MOC_LITERAL(21, 246, 13), // "onStreamError"
QT_MOC_LITERAL(22, 260, 14), // "onVideoClicked"
QT_MOC_LITERAL(23, 275, 19), // "onGridLayoutChanged"
QT_MOC_LITERAL(24, 295, 17) // "onGridPageChanged"

    },
    "MultiStreamController\0streamAdded\0\0"
    "handle\0url\0streamRemoved\0streamConnected\0"
    "streamDisconnected\0streamError\0error\0"
    "videoSelected\0globalIndex\0layoutChanged\0"
    "GridLayout\0layout\0pageChanged\0page\0"
    "onFrameReady\0frame\0onStreamConnected\0"
    "onStreamDisconnected\0onStreamError\0"
    "onVideoClicked\0onGridLayoutChanged\0"
    "onGridPageChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MultiStreamController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x06 /* Public */,
       5,    2,   94,    2, 0x06 /* Public */,
       6,    2,   99,    2, 0x06 /* Public */,
       7,    2,  104,    2, 0x06 /* Public */,
       8,    2,  109,    2, 0x06 /* Public */,
      10,    2,  114,    2, 0x06 /* Public */,
      12,    1,  119,    2, 0x06 /* Public */,
      15,    1,  122,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    2,  125,    2, 0x08 /* Private */,
      19,    2,  130,    2, 0x08 /* Private */,
      20,    2,  135,    2, 0x08 /* Private */,
      21,    2,  140,    2, 0x08 /* Private */,
      22,    1,  145,    2, 0x08 /* Private */,
      23,    1,  148,    2, 0x08 /* Private */,
      24,    1,  151,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,    3,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, QMetaType::Int,   16,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QImage,    3,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, QMetaType::Int,   16,

       0        // eod
};

void MultiStreamController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MultiStreamController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->streamAdded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->streamRemoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->streamConnected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->streamDisconnected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->streamError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->videoSelected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->layoutChanged((*reinterpret_cast< GridLayout(*)>(_a[1]))); break;
        case 7: _t->pageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onFrameReady((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QImage(*)>(_a[2]))); break;
        case 9: _t->onStreamConnected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->onStreamDisconnected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 11: _t->onStreamError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 12: _t->onVideoClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->onGridLayoutChanged((*reinterpret_cast< GridLayout(*)>(_a[1]))); break;
        case 14: _t->onGridPageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MultiStreamController::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiStreamController::streamAdded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MultiStreamController::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiStreamController::streamRemoved)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MultiStreamController::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiStreamController::streamConnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MultiStreamController::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiStreamController::streamDisconnected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MultiStreamController::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiStreamController::streamError)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MultiStreamController::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiStreamController::videoSelected)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MultiStreamController::*)(GridLayout );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiStreamController::layoutChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MultiStreamController::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiStreamController::pageChanged)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MultiStreamController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MultiStreamController.data,
    qt_meta_data_MultiStreamController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MultiStreamController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MultiStreamController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MultiStreamController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MultiStreamController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MultiStreamController::streamAdded(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MultiStreamController::streamRemoved(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MultiStreamController::streamConnected(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MultiStreamController::streamDisconnected(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MultiStreamController::streamError(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MultiStreamController::videoSelected(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MultiStreamController::layoutChanged(GridLayout _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MultiStreamController::pageChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
