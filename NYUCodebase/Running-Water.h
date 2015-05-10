//
//  Running-Water.h
//  Running-Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#ifndef __NYUCodebase__ClassDemoApp__
#define __NYUCodebase__ClassDemoApp__

#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "Texture.h"
#include "Sprite.h"
#include "Brush.h"
const int LEVEL_SCALE = 20;


class ClassDemoApp {
public:
    ClassDemoApp();
    ~ClassDemoApp();
    void Init();
    bool UpdateAndRender();
    void Render();
    void Update(float elapsed);
    void FixedUpdate(float fixedElapsed);
    void zeroLevel();
    void buildLevel();
    void drawLevel();
    void drawSprites();
    void playerControls();
    
    enum GameState { STATE_GAME, STATE_MENU_END };
    int state;
    
    bool done;
    
    float ticks;
    float elapsed;
    float lastFrameTicks;
    int time;
    int score;
    
    SDL_Window* displayWindow;
    SDL_Event event;
    GLuint texture_font;
    
    const Uint8 *keys;
    std::vector<std::vector<int>> level;
    std::vector<Brush*> brushes;
    std::vector<Sprite*> sprites;
};

#endif /* defined(__NYUCodebase__ClassDemoApp__) */
