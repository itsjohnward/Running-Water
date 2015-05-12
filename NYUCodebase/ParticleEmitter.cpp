//
//  Running Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(unsigned int particleCount) {
    
}
ParticleEmitter::ParticleEmitter() {
    
}
ParticleEmitter::~ParticleEmitter() {
    
}
void ParticleEmitter::Update(float elapsed) {
    for(int i=0; i < particles.size(); i++) {
        particles[i].position.x += particles[i].velocity.x * elapsed;
        particles[i].position.y += particles[i].velocity.y * elapsed;
    }
}
void ParticleEmitter::Render() {
    std::vector<float> particleVertices;
    for(int i=0; i < particles.size(); i++) {
        particleVertices.push_back(particles[i].position.x);
        particleVertices.push_back(particles[i].position.y);
    }
    glVertexPointer(2, GL_FLOAT, 0, particleVertices.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_POINTS, 0, particleVertices.size()/2);
}