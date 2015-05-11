//
//  brush.h
//  Running-Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#ifndef __NYUCodebase__Brush__
#define __NYUCodebase__Brush__

#include <stdio.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Texture.h"
#include <vector>

class Brush {
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
    int trigger;
    float friction;
    
    Brush();
    void Update(float elapsed);
    Brush(SheetTexture* sheet, float x, float y, bool visible=true, bool collideable = true);
    Brush(GLuint texture, float x, float y, bool visible=true, bool collideable = true);
    Brush(float x, float y, bool visible=true, bool collideable = true);
    void draw();
    void drawTexture();
    void drawSheet();
    void drawShape();
    void load();
};

#endif /* defined(__NYUCodebase__Brush__) */
