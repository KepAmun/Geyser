#ifndef GEYSERWINDOW_H
#define GEYSERWINDOW_H

#include <QMainWindow>
#include "ParticleEngineView.h"


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
    ParticleEngineView* m_particleEngineView;

private slots:
    void onStatusUpdated(float fps, int count);
};

#endif // GEYSERWINDOW_H
