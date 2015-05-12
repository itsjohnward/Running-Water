//
//  Running Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#include "Brush.h"

Brush::Brush(SheetTexture* sheet, float x, float y, float height, float width, float rotation, bool visible, bool collideable): Entity(sheet, x, y, height, width, visible, collideable),
    trigger(0) {}

Brush::Brush(GLuint texture, float x, float y, float height, float width, float rotation, bool visible, bool collideable): Entity(texture, x, y, height, width, rotation, visible, collideable),
    trigger(0) {}

Brush::Brush(float x, float y, float height, float width, float rotation, bool visible, bool collideable): Entity(x, y, height, width, visible, collideable),
    trigger(0) {}