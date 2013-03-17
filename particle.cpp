
#include <iostream>
#include "randomhelper.h"
#include "particle.h"



GLUquadric* Particle::m_quadric;

Particle::Particle()
{
    m_creationTime = -1;

    m_quadric = gluNewQuadric();
}


Particle::~Particle()
{

}


void Particle::Init(Vector3f initialPosition, Vector3f initialVelocity, Vector3f acceleration, float colorStart[3], float colorEnd[3], float sizeStart, float sizeEnd, qint64 lifeSpan, qint64 creationTime)
{
    Reset();

    m_position = initialPosition;

    m_velocity = initialVelocity;

    m_acceleration = acceleration;

    m_colorStart[0] = colorStart[0];
    m_colorStart[1] = colorStart[1];
    m_colorStart[2] = colorStart[2];

    m_colorEnd[0] = colorEnd[0];
    m_colorEnd[1] = colorEnd[1];
    m_colorEnd[2] = colorEnd[2];

    m_sizeStart = sizeStart;
    m_sizeEnd = sizeEnd;


    m_lifeSpan = lifeSpan;

    m_creationTime = creationTime;

    m_lastUpdate = m_creationTime;
}


void Particle::Reset()
{
    m_creationTime = -1;
}


bool Particle::IsDead(qint64 now)
{
    return m_creationTime < 0 || now - m_creationTime > m_lifeSpan;
}


void Particle::Update(qint64 now)
{
    qint64 timeDelta  = now - m_lastUpdate;

    m_lastUpdate = now;

    float timeRatio = ((float)timeDelta/1000);

    m_velocity += m_acceleration * timeRatio;

    m_position += m_velocity * timeRatio;
}


void Particle::Render()
{
    glPushMatrix();

    glTranslatef(m_position.GetX(),m_position.GetY(),m_position.GetZ());

    qint64 age = m_lastUpdate - m_creationTime;

    float ageRatio = (float)age/m_lifeSpan;

    float red =     (1-ageRatio)*m_colorStart[0] + ageRatio*m_colorEnd[0];
    float green =   (1-ageRatio)*m_colorStart[1] + ageRatio*m_colorEnd[1];
    float blue =    (1-ageRatio)*m_colorStart[2] + ageRatio*m_colorEnd[2];
    glColor3f(red, green, blue);

    float size = (m_sizeEnd-m_sizeStart) * ageRatio + m_sizeStart;

    //gluDisk(m_quadric,0,size/2,10,1);
    gluSphere(m_quadric,size/2,8,4);

    //glBegin(GL_TRIANGLES);
    //{
    //    glVertex3f(size,-size,0);
    //    glVertex3f(-size,-size,0);
    //    glVertex3f(0,size,0);
    //}
//    glBegin(GL_QUADS);
//    {
//        glVertex3f(-size,-size,0);
//        glVertex3f(-size,size,0);
//        glVertex3f(size,size,0);
//        glVertex3f(size,-size,0);
//    }
    glEnd();

    glPopMatrix();
}
