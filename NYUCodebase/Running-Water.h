//
//  Running Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#ifndef __NYUCodebase__ClassDemoApp__
#define __NYUCodebase__ClassDemoApp__

#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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
    void MainMenu();
    void zeroLevel();
    void levelOne();
    void levelTwo();
    void levelThree();
    void playerSpawn();
    void buildLevel();
    void drawLevel();
    void levelComplete();
    void drawSprites();
    void playerControls();
    void debrisFall();
    
    enum GameState { STATE_MENU, STATE_GAME, STATE_DEAD, STATE_MENU_END };
    int state;
    int state_level;
    
    bool done;
    
    float ticks;
    float elapsed;
    float lastFrameTicks;
    int time;
    int score;
    
    SDL_Window* displayWindow;
    SDL_Event event;
    
    Mix_Music* music;
    Mix_Chunk* jump;
    
    GLuint texture_font;
    GLuint texture_sheet;
    SheetTexture* floor_texture;
    GLuint floor_texture2;
    GLuint water_texture;
    GLuint goal_texture;
    GLuint debris_texture;
    
    const Uint8 *keys;
    std::vector<std::vector<int>> level;
    std::vector<Brush*> brushes;
    std::vector<Sprite*> sprites;
    std::vector<Brush*> debris;
    Sprite* player;
};



#endif /* defined(__NYUCodebase__ClassDemoApp__) */
