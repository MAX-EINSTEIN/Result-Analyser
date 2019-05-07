#ifndef PYTHREAD_H
#define PYTHREAD_H
#include <QThread>

class PyThread:public QThread
{
public:
    PyThread();
    void run();
};

class UIThread:public QThread
{
public:
    UIThread();
    void run();
};

#endif // PYTHREAD_H
