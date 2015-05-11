//
//  Brush.cpp
//  Running-Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#include "Brush.h"

Brush::Brush() {}

Brush::Brush(SheetTexture* sheet, float x, float y, bool visible):
sheet(sheet),
x(x),
y(y),
rotation(0),
width(0.05),
height(0.05),
visible(visible)
{ load(); }

Brush::Brush(GLuint texture, float x, float y, bool visible):
texture(texture),
x(x),
y(y),
rotation(0),
width(0.05),
height(0.05),
visible(visible)
{ load(); }

Brush::Brush(float x, float y, bool visible):
sheet(NULL),
x(x),
y(y),
rotation(0),
width(0.05),
height(0.05),
visible(visible)
{ load(); }

void Brush::Update(float elapsed) {
    
}

void Brush::draw() {
    if (sheet != NULL) { drawSheet(); }
    else if (texture != 0) { drawTexture(); }
    else { drawShape(); }
}

void Brush::drawTexture() {
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

void Brush::drawSheet() {
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

void Brush::drawShape() {
    if(!visible){ return; }
    
    GLfloat shape[] = {x-width, (y+height), x-width, (y-height), x+width, (y-height), x+width, (y+height)};
    glVertexPointer(2, GL_FLOAT, 0, shape);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_QUADS, 0, 4);
}

void Brush::load() {
    
}