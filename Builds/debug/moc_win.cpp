/****************************************************************************
** Meta object code from reading C++ file 'win.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../win.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'win.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_myButton[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_myButton[] = {
    "myButton\0\0TypeOfFucnForBtn\0myClicked(int)\0"
    "ChangeSig()\0"
};

void myButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        myButton *_t = static_cast<myButton *>(_o);
        switch (_id) {
        case 0: _t->myClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->ChangeSig(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData myButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject myButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_myButton,
      qt_meta_data_myButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &myButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *myButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *myButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_myButton))
        return static_cast<void*>(const_cast< myButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int myButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void myButton::myClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_Win[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x0a,
      23,    4,    4,    4, 0x0a,
      38,    4,    4,    4, 0x0a,
      69,   58,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Win[] = {
    "Win\0\0enterInDatabase()\0showDataBase()\0"
    "showFunctionsOfDb()\0TypeOfFunc\0"
    "useDbFunction(int)\0"
};

void Win::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Win *_t = static_cast<Win *>(_o);
        switch (_id) {
        case 0: _t->enterInDatabase(); break;
        case 1: _t->showDataBase(); break;
        case 2: _t->showFunctionsOfDb(); break;
        case 3: _t->useDbFunction((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Win::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Win::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Win,
      qt_meta_data_Win, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Win::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Win::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Win::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Win))
        return static_cast<void*>(const_cast< Win*>(this));
    return QWidget::qt_metacast(_clname);
}

int Win::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
