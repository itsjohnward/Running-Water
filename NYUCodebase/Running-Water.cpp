//
//  Running-Water.cpp
//  Running-Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#include "Running-Water.h"

// 60 FPS (1.0f/60.0f)
float FIXED_TIMESTEP = 0.0166666f;
int MAX_TIMESTEPS = 6;
float timeLeftOver = 0.0f;

ClassDemoApp::ClassDemoApp(): state(0), done(false), lastFrameTicks(0.0f), score(0), time(0) {
    Init();
}

void ClassDemoApp::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Running Water", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    //SDL_SetWindowFullscreen( displayWindow, SDL_WINDOW_FULLSCREEN_DESKTOP );
    
    texture_sheet = LoadTexture("tiles_spritesheet.png");
    floor_texture = new SheetTexture(texture_sheet, 144,576,70,70, 914, 936);
    floor_texture2 = LoadTexture("Floor Texture_0.JPG");
    water_texture = LoadTexture("glass-of-water-hi.png");
    
    zeroLevel();
    buildLevel();
    
    sprites.push_back(new Sprite(water_texture, 0.0, 0.0, 0.0, 0.05, 0.05, true));
    sprites[0]->y_acceleration = -5;
    sprites[0]->move_speed = 2;
}

ClassDemoApp::~ClassDemoApp() {
    SDL_Quit();
}

void ClassDemoApp::Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    drawLevel();
    drawSprites();

    SDL_GL_SwapWindow(displayWindow);
}

void ClassDemoApp::Update(float elapsed) {
    for(int i = 0; i < sprites.size(); i++) {
        
        sprites[i]->FixedUpdate(FIXED_TIMESTEP, brushes);
        
    }

    playerControls();
    
    
}

bool ClassDemoApp::UpdateAndRender() {
    
    ticks = (float)SDL_GetTicks()/1000.0f;
    elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    float fixedElapsed = (elapsed + timeLeftOver);
    if(fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
        fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
    }
    while (fixedElapsed >= FIXED_TIMESTEP ) {
        fixedElapsed -= FIXED_TIMESTEP;
        Update(fixedElapsed);
    }
    timeLeftOver = fixedElapsed;
    
    
    
    
    
    Render();
    
    return done;
}

void ClassDemoApp::zeroLevel() {
    level.clear();
    for( int row = 0; row < LEVEL_SCALE * 2-1; row++) {
        std::vector<int> col;
        for( int column = 0; column < LEVEL_SCALE * 2-1; column++ ) {
            col.push_back(0);
        }
        level.push_back(col);
    }
    
    for( int column = 0; column < level[0].size(); column++ ) {
        level[0][column] = 1; // floor
        level[level.size()-1][column] = 1; //ceiling
    }
}

void ClassDemoApp::buildLevel() {
    brushes.clear();
    for(int row = 0; row < level.size(); row++) {
        for(int column = 0; column < level[row].size(); column++) {
            if(level[row][column]==0) {
                brushes.push_back(new Brush(floor_texture2, (float)column/LEVEL_SCALE-(float)(1-(float)1/LEVEL_SCALE), (float)row/LEVEL_SCALE-(float)(1-(float)1/LEVEL_SCALE), true, false));
            }
            if(level[row][column]==1) {
                brushes.push_back(new Brush(floor_texture, (float)column/LEVEL_SCALE-(float)(1-(float)1/LEVEL_SCALE), (float)row/LEVEL_SCALE-(float)(1-(float)1/LEVEL_SCALE)));
            }
        }
    }
    for(int i = 0; i < brushes.size(); i++) {
        brushes[i]->friction = 5;
    }
}

void ClassDemoApp::drawLevel() {
    for( int i = 0; i < brushes.size(); i++ ) {
        brushes[i]->draw();
    }
}

void ClassDemoApp::drawSprites() {
    for( int i = 0; i < sprites.size(); i++ ) {
        sprites[i]->draw();
    }
}

void ClassDemoApp::playerControls() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        else if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_SPACE && (sprites[0]->bottom_collided)) {
                sprites[0]->y_speed = 2.5;
            }
        }
    }
    
    sprites[0]->x_acceleration = 0;
    keys = SDL_GetKeyboardState(NULL);
    if(keys[SDL_SCANCODE_A]) {
        sprites[0]->moveLeft();
    }
    if(keys[SDL_SCANCODE_D]) {
        sprites[0]->moveRight();
    }
}
