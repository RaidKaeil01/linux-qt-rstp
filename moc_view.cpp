/****************************************************************************
** Meta object code from reading C++ file 'view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_View_t {
    QByteArrayData data[25];
    char stringdata0[382];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_View_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_View_t qt_meta_stringdata_View = {
    {
QT_MOC_LITERAL(0, 0, 4), // "View"
QT_MOC_LITERAL(1, 5, 18), // "rectangleConfirmed"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "RectangleBox"
QT_MOC_LITERAL(4, 38, 4), // "rect"
QT_MOC_LITERAL(5, 43, 28), // "normalizedRectangleConfirmed"
QT_MOC_LITERAL(6, 72, 22), // "NormalizedRectangleBox"
QT_MOC_LITERAL(7, 95, 7), // "absRect"
QT_MOC_LITERAL(8, 103, 17), // "gridLayoutChanged"
QT_MOC_LITERAL(9, 121, 7), // "gridNum"
QT_MOC_LITERAL(10, 129, 11), // "streamAdded"
QT_MOC_LITERAL(11, 141, 3), // "url"
QT_MOC_LITERAL(12, 145, 13), // "streamRemoved"
QT_MOC_LITERAL(13, 159, 6), // "handle"
QT_MOC_LITERAL(14, 166, 23), // "videoDisplayModeChanged"
QT_MOC_LITERAL(15, 190, 9), // "multiMode"
QT_MOC_LITERAL(16, 200, 16), // "onRectangleDrawn"
QT_MOC_LITERAL(17, 217, 20), // "onRectangleConfirmed"
QT_MOC_LITERAL(18, 238, 20), // "onRectangleCancelled"
QT_MOC_LITERAL(19, 259, 17), // "onGridModeChanged"
QT_MOC_LITERAL(20, 277, 23), // "onAddMultiStreamClicked"
QT_MOC_LITERAL(21, 301, 26), // "onRemoveMultiStreamClicked"
QT_MOC_LITERAL(22, 328, 17), // "onPrevPageClicked"
QT_MOC_LITERAL(23, 346, 17), // "onNextPageClicked"
QT_MOC_LITERAL(24, 364, 17) // "onPageJumpClicked"

    },
    "View\0rectangleConfirmed\0\0RectangleBox\0"
    "rect\0normalizedRectangleConfirmed\0"
    "NormalizedRectangleBox\0absRect\0"
    "gridLayoutChanged\0gridNum\0streamAdded\0"
    "url\0streamRemoved\0handle\0"
    "videoDisplayModeChanged\0multiMode\0"
    "onRectangleDrawn\0onRectangleConfirmed\0"
    "onRectangleCancelled\0onGridModeChanged\0"
    "onAddMultiStreamClicked\0"
    "onRemoveMultiStreamClicked\0onPrevPageClicked\0"
    "onNextPageClicked\0onPageJumpClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_View[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       5,    2,   92,    2, 0x06 /* Public */,
       8,    1,   97,    2, 0x06 /* Public */,
      10,    1,  100,    2, 0x06 /* Public */,
      12,    1,  103,    2, 0x06 /* Public */,
      14,    1,  106,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,  109,    2, 0x08 /* Private */,
      17,    1,  112,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x08 /* Private */,
      19,    0,  116,    2, 0x08 /* Private */,
      20,    0,  117,    2, 0x08 /* Private */,
      21,    0,  118,    2, 0x08 /* Private */,
      22,    0,  119,    2, 0x08 /* Private */,
      23,    0,  120,    2, 0x08 /* Private */,
      24,    0,  121,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 3,    4,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Bool,   15,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<View *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->rectangleConfirmed((*reinterpret_cast< const RectangleBox(*)>(_a[1]))); break;
        case 1: _t->normalizedRectangleConfirmed((*reinterpret_cast< const NormalizedRectangleBox(*)>(_a[1])),(*reinterpret_cast< const RectangleBox(*)>(_a[2]))); break;
        case 2: _t->gridLayoutChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->streamAdded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->streamRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->videoDisplayModeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->onRectangleDrawn((*reinterpret_cast< const RectangleBox(*)>(_a[1]))); break;
        case 7: _t->onRectangleConfirmed((*reinterpret_cast< const RectangleBox(*)>(_a[1]))); break;
        case 8: _t->onRectangleCancelled(); break;
        case 9: _t->onGridModeChanged(); break;
        case 10: _t->onAddMultiStreamClicked(); break;
        case 11: _t->onRemoveMultiStreamClicked(); break;
        case 12: _t->onPrevPageClicked(); break;
        case 13: _t->onNextPageClicked(); break;
        case 14: _t->onPageJumpClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (View::*)(const RectangleBox & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::rectangleConfirmed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (View::*)(const NormalizedRectangleBox & , const RectangleBox & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::normalizedRectangleConfirmed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (View::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::gridLayoutChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (View::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::streamAdded)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (View::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::streamRemoved)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (View::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::videoDisplayModeChanged)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject View::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_View.data,
    qt_meta_data_View,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *View::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_View.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void View::rectangleConfirmed(const RectangleBox & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void View::normalizedRectangleConfirmed(const NormalizedRectangleBox & _t1, const RectangleBox & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void View::gridLayoutChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void View::streamAdded(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void View::streamRemoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void View::videoDisplayModeChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
