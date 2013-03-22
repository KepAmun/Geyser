#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

#include <vector>
#include <list>
#include <GL/gl.h>
#include <QDateTime>

#include "Particle.h"

using namespace std;



class ParticleEngine
{
public:

    struct Configuration
    {
        Configuration()
        {
            particlesPerSec =  200;

            lifeSpanMin = 4;
            lifeSpanMax = 6;

            sizeStart = 3;
            sizeEnd = 0;

            speedMin = 20;
            speedMax = 30;
            thetaMin = 20;
            thetaMax = 60;
            phiMin = 60;
            phiMax = 70;

            acceleration = Vector3f(0,-9.80665,0);

            colorStart[0] = 1.0;
            colorStart[1] = 0.8;
            colorStart[2] = 0.2;

            colorEnd[0] = 0.8;
            colorEnd[1] = 0.0;
            colorEnd[2] = 0.0;
        }

        int particlesPerSec;

        float lifeSpanMin, lifeSpanMax;

        float sizeStart, sizeEnd;

        float speedMin, speedMax;
        float thetaMin, thetaMax, phiMin, phiMax;

        Vector3f acceleration;

        float colorStart[4], colorEnd[4];
    };

private:
    list<Particle> m_particles;

    qint64 m_startTime;
    qint64 m_lastUpdate;
    qint64 m_lastSpawn;

    Configuration m_config;

    void InitParticle(Particle & particle, qint64 now);

public:

    ParticleEngine();

    void setConfig(Configuration config);

    int GetCount();

    void Render(qint64 now);
};


#endif // PARTICLEENGINE_H
