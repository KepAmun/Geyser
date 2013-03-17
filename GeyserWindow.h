#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "geyserView.h"


namespace Ui {
    class GeyserWindow;
}

class GeyserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GeyserWindow(QWidget *parent = 0);
    ~GeyserWindow();

public slots:
    void onEditingFinished();

private:
    Ui::GeyserWindow *ui;
    geyserView* m_geyserView;

private slots:
    void onStatusUpdated(float fps, int count);
};

#endif // MAINWINDOW_H
