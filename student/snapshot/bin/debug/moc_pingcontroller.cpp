/****************************************************************************
** Meta object code from reading C++ file 'pingcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../pingcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pingcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PingController_t {
    QByteArrayData data[10];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PingController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PingController_t qt_meta_stringdata_PingController = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PingController"
QT_MOC_LITERAL(1, 15, 8), // "sendPing"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "UdpChat"
QT_MOC_LITERAL(4, 33, 12), // "sendSnapshot"
QT_MOC_LITERAL(5, 46, 4), // "data"
QT_MOC_LITERAL(6, 51, 7), // "strData"
QT_MOC_LITERAL(7, 59, 3), // "str"
QT_MOC_LITERAL(8, 63, 2), // "ip"
QT_MOC_LITERAL(9, 66, 4) // "read"

    },
    "PingController\0sendPing\0\0UdpChat\0"
    "sendSnapshot\0data\0strData\0str\0ip\0read"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PingController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x0a /* Public */,
       6,    2,   44,    2, 0x0a /* Public */,
       9,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,
    QMetaType::Void,

       0        // eod
};

void PingController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PingController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendPing(); break;
        case 1: _t->UdpChat(); break;
        case 2: _t->sendSnapshot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->strData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->read(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PingController::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_PingController.data,
    qt_meta_data_PingController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PingController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PingController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PingController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PingController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
