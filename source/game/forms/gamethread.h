#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QThread>

class GameThread : public QThread
{
    Q_OBJECT
public:
    explicit GameThread(QObject *parent = 0);

    virtual void run() override;

signals:
    
public slots:
    
};

#endif // GAMETHREAD_H
