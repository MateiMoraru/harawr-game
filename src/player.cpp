#include "player.h"

Player::Player(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem)
    : window(window),
      spritesheet(spritesheet),
      walk_animation_up(spritesheet, 3, 0.1f, PLAYER, soundsystem),
      walk_animation_down(spritesheet, 3, 0.1f, PLAYER_DOWN, soundsystem),
      walk_animation_left(spritesheet, 3, 0.1f, PLAYER_LEFT, soundsystem),
      walk_animation_right(spritesheet, 3, 0.1f, PLAYER_RIGHT, soundsystem),
      player(spritesheet.get_sprite(PLAYER), PLAYER)
{
    sf::Vector2u size = window.getSize();
    position = sf::Vector2f(size.x / 2 - (size.x / 2) % 64 - 16, size.y / 2 - (size.y / 2) % 64);
    float tileX = (size.x / 2 / 64) * 64;
    float tileY = (size.y / 2 / 64) * 64;

    player.get_sprite().setOrigin(8.f, 8.f);
    //position.x = size.x / 2;
    //position.y = size.y / 2;
    player.set_position(position.x, position.y);

    player.set_scale(sf::Vector2f(this->size / 16.f, this->size / 16.f));

    offset.x = player.get_x() - size.x / 2.f;
    offset.y = player.get_y() - size.y / 2.f;

    hitbox.width  = 64;
    hitbox.height = 64;
}

void Player::update()
{
    moved.x = 0;
    moved.y = 0;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        move(0.f, -speed);
        moved.y = -speed; 
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        move(-speed, 0.f);
        moved.x = -speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        move(0.f, speed);
        moved.y = speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move(speed, 0.f);
        moved.x = speed; 
    }

    if(moved.y < 0.f)
    {
        if(!walk_animation_up.get_started())
            walk_animation_up.start();
        walk_animation_up.update(FOOTSTEP);
        player.set_sprite(walk_animation_up.get_sprite(), PLAYER);
        player.get_sprite().setOrigin(12.f, 8.f);
        player.set_scale({ this->size / 16.f, this->size / 16.f });
    }
    else if(moved.y > 0.f)
    {
        if(!walk_animation_down.get_started())
            walk_animation_down.start();
        walk_animation_down.update(FOOTSTEP);
        player.set_sprite(walk_animation_down.get_sprite(), PLAYER);
        player.get_sprite().setOrigin(12.f, 8.f);
        player.set_scale({ this->size / 16.f, this->size / 16.f });
    }
    else if(moved.x < 0.f)
    {
        if(!walk_animation_left.get_started())
            walk_animation_left.start();
        walk_animation_left.update(FOOTSTEP);
        player.set_sprite(walk_animation_left.get_sprite(), PLAYER);
        player.get_sprite().setOrigin(12.f, 8.f);
        player.set_scale({ size / 16.f, size / 16.f });
    }
    else if(moved.x > 0.f)
    {
        if(!walk_animation_right.get_started())
            walk_animation_right.start();
        walk_animation_right.update(FOOTSTEP);
        player.set_sprite(walk_animation_right.get_sprite(), PLAYER);
        player.get_sprite().setOrigin(12.f, 8.f);
        player.set_scale({ size / 16.f, size / 16.f });
    }
    else
    {
        walk_animation_up.stop();
        walk_animation_down.stop();
        walk_animation_right.stop();
        walk_animation_left.stop();
        //player.set_sprite(spritesheet.get_sprite(PLAYER), PLAYER);
        player.get_sprite().setOrigin(12.f, 8.f);
        player.set_scale({ size / 16.f, size / 16.f });
    }
}

void Player::set_size(float x, float y)
{
    player.get_sprite().setScale(x / 16.f, y / 16.f);
}

void Player::move(float x, float y)
{
    position.x += x;
    position.y += y;

    player.set_position(position.x, position.y);
}

void Player::draw(sf::RenderStates states)
{
    window.draw(player.get_sprite(), states);
}

void Player::add_key(int id)
{
    inventory.push_back(id);
}