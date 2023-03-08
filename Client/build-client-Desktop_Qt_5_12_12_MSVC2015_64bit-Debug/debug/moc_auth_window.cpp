/****************************************************************************
** Meta object code from reading C++ file 'auth_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../client/include/auth_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'auth_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_auth_window_t {
    QByteArrayData data[9];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_auth_window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_auth_window_t qt_meta_stringdata_auth_window = {
    {
QT_MOC_LITERAL(0, 0, 11), // "auth_window"
QT_MOC_LITERAL(1, 12, 20), // "login_button_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 23), // "register_button_clicked"
QT_MOC_LITERAL(4, 58, 22), // "on_lineEdit_textEdited"
QT_MOC_LITERAL(5, 81, 4), // "arg1"
QT_MOC_LITERAL(6, 86, 24), // "on_lineEdit_2_textEdited"
QT_MOC_LITERAL(7, 111, 26), // "on_loginPushButton_clicked"
QT_MOC_LITERAL(8, 138, 29) // "on_registerPushButton_clicked"

    },
    "auth_window\0login_button_clicked\0\0"
    "register_button_clicked\0on_lineEdit_textEdited\0"
    "arg1\0on_lineEdit_2_textEdited\0"
    "on_loginPushButton_clicked\0"
    "on_registerPushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_auth_window[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   46,    2, 0x08 /* Private */,
       6,    1,   49,    2, 0x08 /* Private */,
       7,    0,   52,    2, 0x08 /* Private */,
       8,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void auth_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<auth_window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->login_button_clicked(); break;
        case 1: _t->register_button_clicked(); break;
        case 2: _t->on_lineEdit_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_lineEdit_2_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_loginPushButton_clicked(); break;
        case 5: _t->on_registerPushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (auth_window::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&auth_window::login_button_clicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (auth_window::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&auth_window::register_button_clicked)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject auth_window::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_auth_window.data,
    qt_meta_data_auth_window,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *auth_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *auth_window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_auth_window.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int auth_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void auth_window::login_button_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void auth_window::register_button_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
