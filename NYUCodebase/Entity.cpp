//
//  Running Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#include "Entity.h"

Entity::Entity() {}

Entity::Entity(SheetTexture* sheet, float x, float y, float height, float width, float rotation, bool visible, bool collideable):
sheet(sheet),
x(x),
y(y),
rotation(rotation),
width(width),
height(height),
visible(visible),
collideable(collideable)
{  }

Entity::Entity(GLuint texture, float x, float y, float height, float width, float rotation, bool visible, bool collideable):
texture(texture),
x(x),
y(y),
rotation(rotation),
width(width),
height(height),
visible(visible),
collideable(collideable)
{  }

Entity::Entity(float x, float y, float height, float width, float rotation, bool visible, bool collideable):
sheet(NULL),
x(x),
y(y),
rotation(rotation),
width(width),
height(height),
visible(visible),
collideable(collideable)
{  }

void Entity::Update(float elapsed) {
    
}

void Entity::draw() {
    if (sheet != NULL) { drawSheet(); }
    else if (texture != 0) { drawTexture(); }
    else { drawShape(); }
}

void Entity::drawTexture() {
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
        1.0, 1.0,   1.0, 0.0
    };
    
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
}

void Entity::drawSheet() {
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

void Entity::drawShape() {
    if(!visible){ return; }
    
    GLfloat shape[] = {x-width, (y+height), x-width, (y-height), x+width, (y-height), x+width, (y+height)};
    glVertexPointer(2, GL_FLOAT, 0, shape);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_QUADS, 0, 4);
}

bool Entity::collision(Entity* entity) {
    return (top_collision(entity) || bottom_collision(entity) || left_collision(entity) || right_collision(entity));
}

bool Entity::top_collision (Entity* entity) {
    if (
        ( (y + height) > ( entity->y - entity->height ) ) &&
        ( (y + height) < ( entity->y + entity->height ) ) &&
        ( (x + width) > ( entity->x - entity->width ) ) &&
        ( (x - width) < ( entity->x + entity->width ) ) ) {
        return true;
    }
    return false;
}

bool Entity::bottom_collision(Entity* entity) {
    if (
        ( (y - height) < ( entity->y + entity->height ) ) &&
        ( (y - height) > ( entity->y - entity->height ) ) &&
        ( (x + width) > ( entity->x - entity->width ) ) &&
        ( (x - width) < ( entity->x + entity->width ) ) ) {
        return true;
    }
    return false;
}

bool Entity::left_collision(Entity* entity) {
    if (
        ( (x - width) > ( entity->x - entity->width ) ) &&
        ( (x - width) < ( entity->x + entity->width ) ) &&
        ( (y + height) > ( entity->y - entity->height ) ) &&
        ( (y - height) < ( entity->y + entity->height ) )
        ) {
        return true;
    }
    return false;
}

bool Entity::right_collision(Entity* entity) {
    if (
        ( (x + width) < ( entity->x + entity->width ) ) &&
        ( (x + width) > ( entity->x - entity->width ) ) &&
        ( (y + height) > ( entity->y - entity->height ) ) &&
        ( (y - height) < ( entity->y + entity->height ) )
        ) {
        return true;
    }
    return false;
}