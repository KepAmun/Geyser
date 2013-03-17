#ifndef PARTICLE_H
#define PARTICLE_H

#include <time.h>
#include <GL/glu.h>
#include <QTimer>

#include "vector3f.h"

class Particle
{
private:

    static GLUquadric * m_quadric;

    qint64 m_creationTime;
    qint64 m_lifeSpan;
    qint64 m_lastUpdate;

    Vector3f m_position, m_velocity, m_acceleration;

    float m_colorStart[3], m_colorEnd[3];
    float m_sizeStart, m_sizeEnd;

public:

    Particle();
    ~Particle(void);

    void Init(Vector3f initialPosition, Vector3f initialVelocity, Vector3f acceleration, float* colorStart, float* colorEnd, float sizeStart, float sizeEnd, qint64 lifeSpan, qint64 creationTime);
    void Reset();

    bool IsDead(qint64 now);

    float GetPosition();

    void Update(qint64 now);
    void Render();

};


#endif // PARTICLE_H
