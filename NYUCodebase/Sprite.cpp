//
//  Running Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#include "Sprite.h"

Sprite::Sprite() {}

Sprite::Sprite(GLuint texture, float x, float y, float height, float width, float rotation, bool visible):
    Entity(texture, x, y, height, width, rotation, visible, collideable)
{  }

Sprite::Sprite(SheetTexture* sheet, float x, float y,  float height, float width, float rotation, bool visible):
    Entity(sheet, x, y, height, width, rotation, visible, collideable)
{  }

Sprite::Sprite(float x, float y, float height, float width, float rotation, bool visible):
    Entity(x, y, height, width, rotation, visible, collideable)
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

bool Sprite::top_bottom_collision_response(Brush* entity) {
    if (top_collision(entity)) {
        y = entity->y - entity->height - height;
        y_speed = 0;
        x_friction = entity->friction;
        top_collided = true;
    }
    if (bottom_collision(entity)) {
        y = entity->y + entity->height + height;
        y_speed = 0;
        x_friction = entity->friction;
        bottom_collided = true;
    }
    return (top_collided || bottom_collided);
}

bool Sprite::left_right_collision_response(Brush* entity) {
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
    if (left_collision(entity)) {
        x = entity->x + entity->width + width;
        x_speed = 0;
        y_friction = entity->friction;
        left_collided = true;
    }
    if (right_collision(entity)) {
        x = entity->x - entity->width - width;
        x_speed = 0;
        y_friction = entity->friction;
        right_collided = true;
    }
    return (left_collided || right_collided);
}

void Sprite::moveLeft() {
    x_acceleration = -move_speed;
}
void Sprite::moveRight() {
    x_acceleration = move_speed;
}