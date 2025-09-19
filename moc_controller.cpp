/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "controller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSet>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Controller_t {
    QByteArrayData data[26];
    char stringdata0[375];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Controller_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Controller_t qt_meta_stringdata_Controller = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Controller"
QT_MOC_LITERAL(1, 11, 20), // "ButtonClickedHandler"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 25), // "ServoButtonClickedHandler"
QT_MOC_LITERAL(4, 59, 23), // "FunButtonClickedHandler"
QT_MOC_LITERAL(5, 83, 20), // "onTcpClientConnected"
QT_MOC_LITERAL(6, 104, 2), // "ip"
QT_MOC_LITERAL(7, 107, 4), // "port"
QT_MOC_LITERAL(8, 112, 18), // "onAddCameraClicked"
QT_MOC_LITERAL(9, 131, 12), // "onFrameReady"
QT_MOC_LITERAL(10, 144, 3), // "img"
QT_MOC_LITERAL(11, 148, 28), // "onDetectListSelectionChanged"
QT_MOC_LITERAL(12, 177, 9), // "QSet<int>"
QT_MOC_LITERAL(13, 187, 11), // "selectedIds"
QT_MOC_LITERAL(14, 199, 20), // "onRectangleConfirmed"
QT_MOC_LITERAL(15, 220, 12), // "RectangleBox"
QT_MOC_LITERAL(16, 233, 4), // "rect"
QT_MOC_LITERAL(17, 238, 30), // "onNormalizedRectangleConfirmed"
QT_MOC_LITERAL(18, 269, 22), // "NormalizedRectangleBox"
QT_MOC_LITERAL(19, 292, 8), // "normRect"
QT_MOC_LITERAL(20, 301, 7), // "absRect"
QT_MOC_LITERAL(21, 309, 13), // "onPlanApplied"
QT_MOC_LITERAL(22, 323, 8), // "PlanData"
QT_MOC_LITERAL(23, 332, 4), // "plan"
QT_MOC_LITERAL(24, 337, 23), // "onDetectionDataReceived"
QT_MOC_LITERAL(25, 361, 13) // "detectionData"

    },
    "Controller\0ButtonClickedHandler\0\0"
    "ServoButtonClickedHandler\0"
    "FunButtonClickedHandler\0onTcpClientConnected\0"
    "ip\0port\0onAddCameraClicked\0onFrameReady\0"
    "img\0onDetectListSelectionChanged\0"
    "QSet<int>\0selectedIds\0onRectangleConfirmed\0"
    "RectangleBox\0rect\0onNormalizedRectangleConfirmed\0"
    "NormalizedRectangleBox\0normRect\0absRect\0"
    "onPlanApplied\0PlanData\0plan\0"
    "onDetectionDataReceived\0detectionData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Controller[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    2,   72,    2, 0x0a /* Public */,
       8,    0,   77,    2, 0x08 /* Private */,
       9,    1,   78,    2, 0x08 /* Private */,
      11,    1,   81,    2, 0x08 /* Private */,
      14,    1,   84,    2, 0x08 /* Private */,
      17,    2,   87,    2, 0x08 /* Private */,
      21,    1,   92,    2, 0x08 /* Private */,
      24,    1,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,    6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 15,   19,   20,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, QMetaType::QString,   25,

       0        // eod
};

void Controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Controller *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ButtonClickedHandler(); break;
        case 1: _t->ServoButtonClickedHandler(); break;
        case 2: _t->FunButtonClickedHandler(); break;
        case 3: _t->onTcpClientConnected((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 4: _t->onAddCameraClicked(); break;
        case 5: _t->onFrameReady((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 6: _t->onDetectListSelectionChanged((*reinterpret_cast< const QSet<int>(*)>(_a[1]))); break;
        case 7: _t->onRectangleConfirmed((*reinterpret_cast< const RectangleBox(*)>(_a[1]))); break;
        case 8: _t->onNormalizedRectangleConfirmed((*reinterpret_cast< const NormalizedRectangleBox(*)>(_a[1])),(*reinterpret_cast< const RectangleBox(*)>(_a[2]))); break;
        case 9: _t->onPlanApplied((*reinterpret_cast< const PlanData(*)>(_a[1]))); break;
        case 10: _t->onDetectionDataReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSet<int> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Controller::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Controller.data,
    qt_meta_data_Controller,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Controller.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
