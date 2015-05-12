//
//  Running Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#ifndef __NYUCodebase__Sprite__
#define __NYUCodebase__Sprite__

#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Texture.h"
#include "Brush.h"
#include <vector>
#include "Helper-Functions.h"

class Sprite : public Entity {
public:
    
    float move_speed;
    float x_speed;
    float y_speed;
    float x_acceleration;
    float y_acceleration;
    float x_friction;
    float y_friction;
    
    bool top_collided;
    bool bottom_collided;
    bool left_collided;
    bool right_collided;
    
    Sprite();
    Sprite(GLuint texture, float x, float y, float width, float height, float rotation,bool visible=true);
    Sprite(SheetTexture* sheet, float x, float y, float width, float height, float rotation, bool visible=true);
    Sprite(float x, float y, float width, float height, float rotation, bool visible);
    
    
    void FixedUpdate(float elapsed, std::vector<Brush*> brushes);
    
    bool top_bottom_collision_response(Brush* brush);
    bool left_right_collision_response(Brush* brush);
    
    void moveLeft();
    void moveRight();

};

#endif /* defined(__NYUCodebase__Sprite__) */
