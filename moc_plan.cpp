/****************************************************************************
** Meta object code from reading C++ file 'plan.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "plan.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plan.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Plan_t {
    QByteArrayData data[11];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Plan_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Plan_t qt_meta_stringdata_Plan = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Plan"
QT_MOC_LITERAL(1, 5, 11), // "planApplied"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "PlanData"
QT_MOC_LITERAL(4, 27, 4), // "plan"
QT_MOC_LITERAL(5, 32, 26), // "onPlanListSelectionChanged"
QT_MOC_LITERAL(6, 59, 9), // "onNewPlan"
QT_MOC_LITERAL(7, 69, 10), // "onSavePlan"
QT_MOC_LITERAL(8, 80, 12), // "onDeletePlan"
QT_MOC_LITERAL(9, 93, 11), // "onApplyPlan"
QT_MOC_LITERAL(10, 105, 17) // "onFormDataChanged"

    },
    "Plan\0planApplied\0\0PlanData\0plan\0"
    "onPlanListSelectionChanged\0onNewPlan\0"
    "onSavePlan\0onDeletePlan\0onApplyPlan\0"
    "onFormDataChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Plan[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,
       9,    0,   56,    2, 0x08 /* Private */,
      10,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Plan::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Plan *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->planApplied((*reinterpret_cast< const PlanData(*)>(_a[1]))); break;
        case 1: _t->onPlanListSelectionChanged(); break;
        case 2: _t->onNewPlan(); break;
        case 3: _t->onSavePlan(); break;
        case 4: _t->onDeletePlan(); break;
        case 5: _t->onApplyPlan(); break;
        case 6: _t->onFormDataChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Plan::*)(const PlanData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Plan::planApplied)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Plan::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Plan.data,
    qt_meta_data_Plan,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Plan::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Plan::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Plan.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Plan::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void Plan::planApplied(const PlanData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
