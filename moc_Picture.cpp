/****************************************************************************
** Meta object code from reading C++ file 'Picture.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "Picture.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Picture.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Picture_t {
    QByteArrayData data[12];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Picture_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Picture_t qt_meta_stringdata_Picture = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Picture"
QT_MOC_LITERAL(1, 8, 13), // "onPrevClicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "onNextClicked"
QT_MOC_LITERAL(4, 37, 14), // "onCloseClicked"
QT_MOC_LITERAL(5, 52, 24), // "onScreenshotAlbumClicked"
QT_MOC_LITERAL(6, 77, 19), // "onAlarmAlbumClicked"
QT_MOC_LITERAL(7, 97, 20), // "onSliderValueChanged"
QT_MOC_LITERAL(8, 118, 5), // "value"
QT_MOC_LITERAL(9, 124, 13), // "onJumpToImage"
QT_MOC_LITERAL(10, 138, 13), // "onDeleteImage"
QT_MOC_LITERAL(11, 152, 18) // "onSortOrderChanged"

    },
    "Picture\0onPrevClicked\0\0onNextClicked\0"
    "onCloseClicked\0onScreenshotAlbumClicked\0"
    "onAlarmAlbumClicked\0onSliderValueChanged\0"
    "value\0onJumpToImage\0onDeleteImage\0"
    "onSortOrderChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Picture[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    1,   64,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,
      10,    0,   68,    2, 0x08 /* Private */,
      11,    0,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Picture::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Picture *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onPrevClicked(); break;
        case 1: _t->onNextClicked(); break;
        case 2: _t->onCloseClicked(); break;
        case 3: _t->onScreenshotAlbumClicked(); break;
        case 4: _t->onAlarmAlbumClicked(); break;
        case 5: _t->onSliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onJumpToImage(); break;
        case 7: _t->onDeleteImage(); break;
        case 8: _t->onSortOrderChanged(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Picture::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Picture.data,
    qt_meta_data_Picture,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Picture::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Picture::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Picture.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Picture::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
