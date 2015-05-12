//
//  Running Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#ifndef __NYUCodebase__Texture__
#define __NYUCodebase__Texture__

#include <stdio.h>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class SheetTexture{
public:
    SheetTexture();
    SheetTexture(GLuint texture_sheet, float u, float v, float width, float height, float texture_sheet_width, float texture_sheet_height);
    GLuint texture_sheet;
    float u;
    float v;
    float width;
    float height;
    float texture_sheet_width;
    float texture_sheet_height;
};

GLuint LoadTexture(const char *image_path);

void DrawText(GLuint fontTexture, std::string text, float size, float spacing, float r, float g, float b, float a, float x, float y);

#endif /* defined(__NYUCodebase__Texture__) */
