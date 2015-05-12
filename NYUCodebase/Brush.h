//
//  Running Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#ifndef __NYUCodebase__Brush__
#define __NYUCodebase__Brush__

#include <stdio.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Texture.h"
#include <vector>
#include "Entity.h"

class Brush : public Entity {
public:
    int trigger;
    float friction;

    Brush(SheetTexture* sheet, float x, float y, float height, float width, float rotation, bool visible=true, bool collideable = true);
    Brush(GLuint texture, float x, float y, float height, float width, float rotation, bool visible=true, bool collideable = true);
    Brush(float x, float y, float height, float width, float rotation, bool visible=true, bool collideable = true);
};

#endif /* defined(__NYUCodebase__Brush__) */
