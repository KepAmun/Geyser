#include <iostream>
#include <sstream>
#include <math.h>
#include <QTimer>
#include <QDateTime>
#include "ParticleEngineView.h"


const double TWO_PI = 2*PI;
const double PI_OVER_TWO = PI/2;


ParticleEngineView::ParticleEngineView(QGLFormat format, QWidget *parent) :
    QGLWidget(format, parent)
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(renderTimeout()));


    m_camPhi = PI * 0.1f;
    m_camTheta = TWO_PI * 0.2f;
    m_camDistance = 150;

    m_leftButtonDown = false;
    m_rightButtonDown = false;

    m_lastUpdate = -1;
    m_lastTimer = -1;


    UpdateCamPosition();
    UpdateClicked();

}


void ParticleEngineView::initializeGL()
{
    glClearColor(0,0,0,1.0);
    glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
    glCullFace(GL_BACK);

}


void ParticleEngineView::resizeGL(int width, int height)
{
    glViewport(0,0,(GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (float)width/height, m_camDistance * 0.05, m_camDistance * 10);
}


void ParticleEngineView::UpdateClicked()
{
    m_particleEngine.setConfig(m_config);

    m_elapsedTimer.start();
    m_timer.start(0);
}


void ParticleEngineView::renderTimeout()
{
    glDraw();
}


void ParticleEngineView::onShowBoxToggled(bool checked)
{
    m_showBox = checked;
}


void ParticleEngineView::onShowAxesToggled(bool checked)
{
    m_showAxes = checked;
}


void ParticleEngineView::paintGL()
{
    qint64 now = m_elapsedTimer.elapsed();

    m_frameCount++;

    if(now - m_lastFpsUpdate > 500)
    {
        emit statusUpdated((m_frameCount * 1000.0f) / (now - m_lastFpsUpdate), m_particleEngine.GetCount());
        m_lastFpsUpdate = now;
        m_frameCount = 0;
    }


    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(m_camX, m_camY, m_camZ, 0, 0, 0, 0, 1, 0);


    glPushMatrix();

    m_particleEngine.Render(now);

    glPopMatrix();


    glPushMatrix();

    glScalef(20,20,20);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if(m_showBox)
    {
        // Render framing box

        glColor3f(0.8,0.8,0.8);

        // Top
        glBegin(GL_LINE_LOOP);
        {
            glVertex3f(1,1,1);
            glVertex3f(1,1,-1);
            glVertex3f(-1,1,-1);
            glVertex3f(-1,1,1);
        }
        glEnd();

        // Bottom
        glBegin(GL_LINE_LOOP);
        {
            glVertex3f(1,-1,1);
            glVertex3f(1,-1,-1);
            glVertex3f(-1,-1,-1);
            glVertex3f(-1,-1,1);
        }
        glEnd();

        // Sides
        glBegin(GL_LINES);
        {
            glVertex3f(1,1,1);
            glVertex3f(1,-1,1);

            glVertex3f(1,1,-1);
            glVertex3f(1,-1,-1);

            glVertex3f(-1,1,1);
            glVertex3f(-1,-1,1);

            glVertex3f(-1,1,-1);
            glVertex3f(-1,-1,-1);

        }
        glEnd();
    }


    if(m_showAxes)
    {
        // Render x,y,z axes
        glDisable(GL_DEPTH_TEST);
        glBegin(GL_LINES);
        {
            glColor3f(1,0,0); // x is red
            glVertex3f(0,0,0);
            glVertex3f(1,0,0);

            glColor3f(0,1,0); // y is blue
            glVertex3f(0,0,0);
            glVertex3f(0,1,0);

            glColor3f(0,0,1); // z is green
            glVertex3f(0,0,0);
            glVertex3f(0,0,1);
        }
        glEnd();
        glEnable(GL_DEPTH_TEST);
    }


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPopMatrix();

}


void ParticleEngineView::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton && m_leftButtonDown == false)
    {
        m_leftButtonDown = true;
    }
    else if(event->button() == Qt::RightButton && m_rightButtonDown == false)
    {
        m_rightButtonDown = true;
    }

    m_lastMouseX = event->x();
    m_lastMouseY = event->y();
}


void ParticleEngineView::mouseMoveEvent(QMouseEvent * event)
{
    int dx = event->x() - m_lastMouseX;
    int dy = event->y() - m_lastMouseY;

    const float speed = 0.01;

    if (m_leftButtonDown)
    {
        m_camTheta = (m_camTheta + (dx * speed));
        m_camPhi = (m_camPhi + (dy * speed));

        UpdateCamPosition();
    }
    else if(m_rightButtonDown)
    {
        m_camDistance *= 1 + (dy * speed);

        UpdateCamPosition();
    }

    m_lastMouseX = event->x();
    m_lastMouseY = event->y();
}


void ParticleEngineView::mouseReleaseEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton && m_leftButtonDown == true)
    {
        m_leftButtonDown = false;
    }
    else if(event->button() == Qt::RightButton && m_rightButtonDown == true)
    {
        m_rightButtonDown = false;
    }
}


void ParticleEngineView::wheelEvent(QWheelEvent * event)
{
    if (event->orientation() == Qt::Vertical)
    {
        m_camDistance *= 1 - event->delta() / 1000.0f;

        UpdateCamPosition();
    }
}


void ParticleEngineView::UpdateCamPosition()
{
    if(m_camPhi > PI_OVER_TWO * 0.99f)
        m_camPhi = PI_OVER_TWO * 0.99f;
    if(m_camPhi < -PI_OVER_TWO * 0.99f)
        m_camPhi = -PI_OVER_TWO * 0.99f;

    while(m_camTheta > TWO_PI)
        m_camTheta -= TWO_PI;
    while(m_camTheta < 0)
        m_camTheta += TWO_PI;


    if(m_camDistance < 10)
        m_camDistance = 10;
    else if(m_camDistance > 1000)
        m_camDistance = 1000;


    m_camX = m_camDistance * cos(m_camTheta) * cos(m_camPhi);
    m_camY = m_camDistance * sin(m_camPhi);
    m_camZ = m_camDistance * sin(m_camTheta) * cos(m_camPhi);
}

