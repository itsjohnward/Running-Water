//
//  Running Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#ifndef __Running_Water__Entity__
#define __Running_Water__Entity__

#include <stdio.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Texture.h"
#include <vector>

using namespace std;

class Entity {
public:
    float x;
    float y;
    SheetTexture* sheet;
    GLuint texture;
    
    float rotation;
    float width;
    float height;
    bool visible;
    bool collideable;
    
    Entity();
    void Update(float elapsed);
    Entity(SheetTexture* sheet, float x, float y, float height, float width, float rotation, bool visible=true, bool collideable = true);
    Entity(GLuint texture, float x, float y, float height, float width, float rotation, bool visible=true, bool collideable = true);
    Entity(float x, float y, float height, float width, float rotation, bool visible=true, bool collideable = true);
    void draw();
    void drawTexture();
    void drawSheet();
    void drawShape();
    
    bool collision(Entity* entity);
    bool top_collision(Entity* entity);
    bool bottom_collision(Entity* entity);
    bool left_collision(Entity* entity);
    bool right_collision(Entity* entity);
};

#endif /* defined(__Running_Water__Entity__) */
