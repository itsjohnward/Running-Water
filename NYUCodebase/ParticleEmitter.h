//
//  Running Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#ifndef __Running_Water__ParticleEmitter__
#define __Running_Water__ParticleEmitter__

#include <stdio.h>
#include <vector>
#include "Helper-Functions.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Entity.h"


class Particle: public Entity{
public:
    Particle();
    Vector position;
    Vector velocity;
    float lifetime;
};

class ParticleEmitter: public Entity {
public:
    ParticleEmitter(unsigned int particleCount);
    ParticleEmitter();
    ~ParticleEmitter();
    void Update(float elapsed);
    void Render();
    Vector position;
    Vector gravity;
    float maxLifetime;
    std::vector<Particle> particles;
};

#endif /* defined(__Running_Water__ParticleEmitter__) */
