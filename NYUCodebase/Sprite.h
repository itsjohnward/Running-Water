//
//  Sprite.h
//  Running-Water
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

class Sprite {
public:
    float x;
    float y;
    SheetTexture* sheet;
    GLuint texture;
    float rotation;
    float width;
    float height;
    
    float move_speed;
    float x_speed;
    float y_speed;
    float x_acceleration;
    float y_acceleration;
    float x_friction;
    float y_friction;
    
    bool visible;
    bool top_collided;
    bool bottom_collided;
    bool left_collided;
    bool right_collided;
    
    Sprite();
    Sprite(GLuint texture, float x, float y, float rotation, float width, float height, bool visible=true);
    Sprite(SheetTexture* sheet, float x, float y, float rotation, float width, float height, bool visible=true);
    Sprite(float x, float y, float rotation, float width, float height, bool visible);
    
    
    void FixedUpdate(float elapsed, std::vector<Brush*> brushes);
    
    bool top_bottom_collision_response(Brush* brush);
    bool left_right_collision_response(Brush* brush);
    
    bool collision(Brush* brush);
    bool top_collision(Brush* brush);
    bool bottom_collision(Brush* brush);
    bool left_collision(Brush* brush);
    bool right_collision(Brush* brush);
    
    
    void draw();
    void drawSheet();
    void drawTexture();
    void drawShape();
    
    void moveLeft();
    void moveRight();
    
    float lerp(float v0, float v1, float t);

};

#endif /* defined(__NYUCodebase__Sprite__) */
