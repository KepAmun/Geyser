#ifndef PARTICLEENGINEVIEW_H
#define PARTICLEENGINEVIEW_H

#include <QGLWidget>
#include <GL/glu.h>
#include <QTimer>
#include <QElapsedTimer>
#include <QMouseEvent>
#include "ParticleEngine.h"

class ParticleEngineView : public QGLWidget
{
    Q_OBJECT

private:
    ParticleEngine m_particleEngine;
    ParticleEngine::Configuration m_config;

    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;


    float m_camPhi;
    float m_camTheta;
    float m_camDistance;
    float m_camX;
    float m_camY;
    float m_camZ;

    bool m_leftButtonDown;
    bool m_rightButtonDown;
    int m_lastMouseX;
    int m_lastMouseY;


    void UpdateClicked();

    void UpdateCamPosition();


    qint64 m_lastUpdate;
    qint64 m_lastTimer;
    qint64 m_lastFpsUpdate;
    int m_frameCount;


    bool m_showBox, m_showAxes;

public:
    explicit ParticleEngineView(QGLFormat format, QWidget *parent = 0);
    void setConfig(ParticleEngine::Configuration config){ m_particleEngine.setConfig(config); }


protected:
    void initializeGL();
    void resizeGL(int x, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);

signals:
    void statusUpdated(float fps, int count);

public slots:
    void renderTimeout();
    void onShowBoxToggled(bool checked);
    void onShowAxesToggled(bool checked);

};

#endif // PARTICLEENGINEVIEW_H
