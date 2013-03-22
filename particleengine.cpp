
#include <iostream>
#include "ParticleEngine.h"
#include "RandomHelper.h"

const float PI = 2 * acos(0.0f);
const float DEG_TO_RAD = PI / 180;

ParticleEngine::ParticleEngine(void)
{
    m_startTime = 0;
    m_lastUpdate = 0;
    m_lastSpawn = 0;
}


ParticleEngine::~ParticleEngine(void)
{
}


void ParticleEngine::setConfig(Configuration config)
{
    m_config = config;
}


int ParticleEngine::GetCount()
{
    return m_particles.size();
}


void ParticleEngine::InitParticle(Particle & particle, qint64 now)
{
    Vector3f position;

    float speed = RandomHelper::GetFloat(m_config.speedMin, m_config.speedMax);

    float theta = RandomHelper::GetFloat( m_config.thetaMin, m_config.thetaMax)* DEG_TO_RAD;
    float phi = RandomHelper::GetFloat( m_config.phiMin, m_config.phiMax)* DEG_TO_RAD;


    Vector3f velocity(
                speed*cos(theta)*cos(phi),
                speed*sin(phi),
                speed*sin(theta)*cos(phi));


    qint64 lifeSpan = RandomHelper::GetFloat(m_config.lifeSpanMin, m_config.lifeSpanMax) * 1000;

    particle.Init(position, velocity, m_config.acceleration, m_config.colorStart, m_config.colorEnd, m_config.sizeStart,m_config.sizeEnd, lifeSpan, now);
}


void ParticleEngine::Render(qint64 now)
{
    //cout << "In Render" << endl;
    //qint64 timeSinceStart = now - m_startTime;

    qint64 timeDelta = 0;
    if(m_lastUpdate > 0)
    {
        timeDelta = now - m_lastUpdate;
    }

    float spawnDelayMs = 1000 / (float)m_config.particlesPerSec; // time between spawns in ms

    qint64 spawnDelta = timeDelta;
    if(m_lastSpawn > 0)
    {
        spawnDelta = now - m_lastSpawn;
    }

    // Add particles

    int numToGenerate = spawnDelta/spawnDelayMs;
    //cout<< "numToGenerate == " << numToGenerate << endl;
    int numGenerated = 0;
    bool done = false;


    list<Particle>::iterator particle_iterator = m_particles.begin();
    while(!done)
    {
        if(particle_iterator != m_particles.end())
        {
            bool isDead = particle_iterator->IsDead(now);

            if(isDead)
            {
                if(numGenerated < numToGenerate)
                {
                    numGenerated++;

                    qint64 particleStartTime = now - spawnDelta + (numGenerated*spawnDelayMs);// distribute new particle's "now" over time since last update (avoid 'lag bursts')
                    //cout << now << ", " << particleStartTime << ", " << now - particleStartTime << endl;
                    InitParticle(*particle_iterator, particleStartTime );
                    m_lastSpawn = particleStartTime;

                    particle_iterator->Update(now);
                    particle_iterator->Render();

                    particle_iterator++;
                }
                else
                {
                    //particle->Reset();
                    particle_iterator = m_particles.erase(particle_iterator); // also advances the iterator
                }
            }
            else
            {
                particle_iterator->Update(now);
                particle_iterator->Render();

                particle_iterator++;
            }
        }
        else
        {
            if(numGenerated < numToGenerate)
            {
                // Make new particle
                Particle p;

                numGenerated++;

                clock_t particleStartTime = now - spawnDelta + (numGenerated*spawnDelayMs);// distribute new particle's "now" over time since last update (avoid 'lag bursts')
                //cout << now << ", " << particleStartTime << ", " << now - particleStartTime << endl;
                InitParticle(p, particleStartTime);
                m_lastSpawn = particleStartTime;

                p.Update(now);
                p.Render();

                m_particles.push_back(p);
            }
            else
            {
                done = true;
            }
        }

    }

    m_lastUpdate = now;
}

