//
//  Sprite.cpp
//  Running-Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#include "Sprite.h"

Sprite::Sprite() {}

Sprite::Sprite(GLuint texture, float x, float y, float rotation, float width, float height, bool visible):
    texture(texture),
    x(x),
    y(y),
    rotation(rotation),
    width(width),
    height(height),
    visible(visible)
{  }

Sprite::Sprite(SheetTexture* sheet, float x, float y, float rotation, float width, float height, bool visible):
    sheet(sheet),
    x(x),
    y(y),
    rotation(rotation),
    width(width),
    height(height),
    visible(visible)
{  }

Sprite::Sprite(float x, float y, float rotation, float width, float height, bool visible):
    x(x),
    y(y),
    rotation(rotation),
    width(width),
    height(height),
    visible(visible)
{  }

void Sprite::FixedUpdate(float FIXED_TIMESTEP, std::vector<Brush*> brushes) {
    x_speed = lerp(x_speed, 0.0f, FIXED_TIMESTEP * x_friction);
    y_speed = lerp(y_speed, 0.0f, FIXED_TIMESTEP * y_friction);
    x_speed += x_acceleration * FIXED_TIMESTEP;
    y_speed += y_acceleration * FIXED_TIMESTEP;
    
    top_collided = false;
    bottom_collided = false;
    left_collided = false;
    right_collided = false;
    x_friction = 1;
    y_friction = 1;
    
    //std::cout << x << std::endl;
    x += x_speed * FIXED_TIMESTEP;
    for(int p = 0; p < brushes.size(); p++) {
        if (brushes[p]->collideable) {
            left_right_collision_response(brushes[p]);
        }
    }
    y += y_speed * FIXED_TIMESTEP;
    for(int p = 0; p < brushes.size(); p++) {
        if (brushes[p]->collideable) {
            top_bottom_collision_response(brushes[p]);
        }
    }
}

bool Sprite::top_bottom_collision_response(Brush* brush) {
    if (top_collision(brush)) {
        y = brush->y - brush->height - height;
        y_speed = 0;
        x_friction = brush->friction;
        top_collided = true;
    }
    if (bottom_collision(brush)) {
        y = brush->y + brush->height + height;
        y_speed = 0;
        x_friction = brush->friction;
        bottom_collided = true;
    }
    return (top_collided || bottom_collided);
}

bool Sprite::left_right_collision_response(Brush* brush) {
    if( x < -1.0 + width) {
        x = -1.0 + width;
        x_speed = 0;
        left_collided = true;
    }
    if( x > 1.0 - width) {
        x = 1.0 - width;
        x_speed = 0;
        right_collided = true;
    }
    if (left_collision(brush)) {
        x = brush->x + brush->width + width;
        x_speed = 0;
        y_friction = brush->friction;
        left_collided = true;
    }
    if (right_collision(brush)) {
        x = brush->x - brush->width - width;
        x_speed = 0;
        y_friction = brush->friction;
        right_collided = true;
    }
    return (left_collided || right_collided);
}

bool Sprite::collision(Brush* brush) {
    return (top_bottom_collision_response(brush) || left_right_collision_response(brush) );
}

bool Sprite::top_collision (Brush* brush) {
    if (
        ( (y + height) > ( brush->y - brush->height ) ) &&
        ( (y + height) < ( brush->y + brush->height ) ) &&
        ( (x + width) > ( brush->x - brush->width ) ) &&
        ( (x - width) < ( brush->x + brush->width ) ) ) {
        return true;
    }
    return false;
}

bool Sprite::bottom_collision(Brush* brush) {
    if (
        ( (y - height) < ( brush->y + brush->height ) ) &&
        ( (y - height) > ( brush->y - brush->height ) ) &&
        ( (x + width) > ( brush->x - brush->width ) ) &&
        ( (x - width) < ( brush->x + brush->width ) ) ) {
        return true;
    }
    return false;
}

bool Sprite::left_collision(Brush* brush) {
    if (
        ( (x - width) > ( brush->x - brush->width ) ) &&
        ( (x - width) < ( brush->x + brush->width ) ) &&
        ( (y + height) > ( brush->y - brush->height ) ) &&
        ( (y - height) < ( brush->y + brush->height ) )
        ) {
        return true;
    }
    return false;
}

bool Sprite::right_collision(Brush* brush) {
    if (
        ( (x + width) < ( brush->x + brush->width ) ) &&
        ( (x + width) > ( brush->x - brush->width ) ) &&
        ( (y + height) > ( brush->y - brush->height ) ) &&
        ( (y - height) < ( brush->y + brush->height ) )
    ) {
        return true;
    }
    return false;
}

void Sprite::draw() {
    if (sheet != NULL) { drawSheet(); }
    else if (texture != 0) { drawTexture(); }
    else { drawShape(); }
}

void Sprite::drawTexture() {
    if(!visible){ return; }
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
    GLfloat quad[] = {  -width, height,
        -width, -height,
        width, -height,
        width, height
    };
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    GLfloat quadUVs[] = {
        0.0, 0.0,  0.0, 1.0,
        1.0, 1.0,   1.0, 0.0};
    
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
}

void Sprite::drawSheet() {
    if(!visible){ return; }
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sheet->texture_sheet);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
    GLfloat quad[] = {
        -width, height,
        -width, -height,
        width, -height,
        width, height
    };
    
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {
        sheet->u, sheet->v,
        sheet->u, sheet->v+sheet->height,
        sheet->u+sheet->width, sheet->v+sheet->height,
        sheet->u+sheet->width, sheet->v
    };
    
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
}

void Sprite::drawShape() {
    if(!visible){ return; }
    
    GLfloat shape[] = {x-width, (y+height), x-width, (y-height), x+width, (y-height), x+width, (y+height)};
    glVertexPointer(2, GL_FLOAT, 0, shape);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_QUADS, 0, 4);
}


void Sprite::moveLeft() {
    x_acceleration = -move_speed;
}
void Sprite::moveRight() {
    x_acceleration = move_speed;
}

float Sprite::lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}