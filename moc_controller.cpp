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
    QByteArrayData data[34];
    char stringdata0[480];
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
QT_MOC_LITERAL(8, 112, 25), // "onVideoDisplayModeChanged"
QT_MOC_LITERAL(9, 138, 9), // "multiMode"
QT_MOC_LITERAL(10, 148, 19), // "onGridLayoutChanged"
QT_MOC_LITERAL(11, 168, 7), // "gridNum"
QT_MOC_LITERAL(12, 176, 13), // "onStreamAdded"
QT_MOC_LITERAL(13, 190, 3), // "url"
QT_MOC_LITERAL(14, 194, 15), // "onStreamRemoved"
QT_MOC_LITERAL(15, 210, 6), // "handle"
QT_MOC_LITERAL(16, 217, 18), // "onAddCameraClicked"
QT_MOC_LITERAL(17, 236, 12), // "onFrameReady"
QT_MOC_LITERAL(18, 249, 3), // "img"
QT_MOC_LITERAL(19, 253, 28), // "onDetectListSelectionChanged"
QT_MOC_LITERAL(20, 282, 9), // "QSet<int>"
QT_MOC_LITERAL(21, 292, 11), // "selectedIds"
QT_MOC_LITERAL(22, 304, 20), // "onRectangleConfirmed"
QT_MOC_LITERAL(23, 325, 12), // "RectangleBox"
QT_MOC_LITERAL(24, 338, 4), // "rect"
QT_MOC_LITERAL(25, 343, 30), // "onNormalizedRectangleConfirmed"
QT_MOC_LITERAL(26, 374, 22), // "NormalizedRectangleBox"
QT_MOC_LITERAL(27, 397, 8), // "normRect"
QT_MOC_LITERAL(28, 406, 7), // "absRect"
QT_MOC_LITERAL(29, 414, 13), // "onPlanApplied"
QT_MOC_LITERAL(30, 428, 8), // "PlanData"
QT_MOC_LITERAL(31, 437, 4), // "plan"
QT_MOC_LITERAL(32, 442, 23), // "onDetectionDataReceived"
QT_MOC_LITERAL(33, 466, 13) // "detectionData"

    },
    "Controller\0ButtonClickedHandler\0\0"
    "ServoButtonClickedHandler\0"
    "FunButtonClickedHandler\0onTcpClientConnected\0"
    "ip\0port\0onVideoDisplayModeChanged\0"
    "multiMode\0onGridLayoutChanged\0gridNum\0"
    "onStreamAdded\0url\0onStreamRemoved\0"
    "handle\0onAddCameraClicked\0onFrameReady\0"
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
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x0a /* Public */,
       3,    0,   90,    2, 0x0a /* Public */,
       4,    0,   91,    2, 0x0a /* Public */,
       5,    2,   92,    2, 0x0a /* Public */,
       8,    1,   97,    2, 0x0a /* Public */,
      10,    1,  100,    2, 0x0a /* Public */,
      12,    1,  103,    2, 0x0a /* Public */,
      14,    1,  106,    2, 0x0a /* Public */,
      16,    0,  109,    2, 0x08 /* Private */,
      17,    1,  110,    2, 0x08 /* Private */,
      19,    1,  113,    2, 0x08 /* Private */,
      22,    1,  116,    2, 0x08 /* Private */,
      25,    2,  119,    2, 0x08 /* Private */,
      29,    1,  124,    2, 0x08 /* Private */,
      32,    1,  127,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,    6,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,   18,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void, 0x80000000 | 26, 0x80000000 | 23,   27,   28,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void, QMetaType::QString,   33,

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
        case 4: _t->onVideoDisplayModeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->onGridLayoutChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onStreamAdded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->onStreamRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onAddCameraClicked(); break;
        case 9: _t->onFrameReady((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 10: _t->onDetectListSelectionChanged((*reinterpret_cast< const QSet<int>(*)>(_a[1]))); break;
        case 11: _t->onRectangleConfirmed((*reinterpret_cast< const RectangleBox(*)>(_a[1]))); break;
        case 12: _t->onNormalizedRectangleConfirmed((*reinterpret_cast< const NormalizedRectangleBox(*)>(_a[1])),(*reinterpret_cast< const RectangleBox(*)>(_a[2]))); break;
        case 13: _t->onPlanApplied((*reinterpret_cast< const PlanData(*)>(_a[1]))); break;
        case 14: _t->onDetectionDataReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
