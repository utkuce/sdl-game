#include "Player.h"

#include <string.h>
#include <math.h>


Player::Player() : Rectangle(0,0,50,50) 
{
  shield = new Shield(this);
}

Player::~Player()
{
  delete shield;
}

bool jump_on_queue = false;

void Player::update()
{
  // player control shortcuts
  playerValues.goRight = EventHandler::keystate[SDL_SCANCODE_D] ||
                         EventHandler::keystate[SDL_SCANCODE_RIGHT];

  playerValues.goLeft = EventHandler::keystate[SDL_SCANCODE_A] ||
                        EventHandler::keystate[SDL_SCANCODE_LEFT];

  playerValues.jump = EventHandler::keystate[SDL_SCANCODE_W] || 
                      EventHandler::keystate[SDL_SCANCODE_UP] ||
                      EventHandler::keystate[SDL_SCANCODE_SPACE];
                    
  shield->on = EventHandler::keystate[SDL_SCANCODE_LSHIFT];

  // acceleration and gravity dependent of framerate
  acceleration = 60*50 / Renderer::frameRate;
  gravity = 3*acceleration;

  
  Interface::debugChannel += "\nacceleration: " + std::to_string(acceleration) + 
                             "\ngravity: " + std::to_string(gravity) +
                             "\nvelocity.y " + std::to_string(velocity.y) +
                             "\nplayer.y: " + std::to_string(y) +
                             "\nplayer.x: " + std::to_string(x);
  

  // go right
  if (playerValues.goRight && velocity.x < speed_limit)
    velocity.x += acceleration;
  
  // go left
  else if (playerValues.goLeft && velocity.x > -speed_limit)
    velocity.x -= acceleration;

  //friction
  else if (velocity.x && y <= 200)
  {
    float velocity_old = velocity.x;
    velocity.x += velocity.x > 0 ? -acceleration : acceleration;
    if (velocity_old * velocity.x < 0) // if velocity changes sign, stop friction
      velocity.x = 0;
  }

  // borders
  if (x < 0 || x + w > rendererWidth) // bounce back from walls
  {  
    x = x < 0 ? 0 : rendererWidth - w;
    velocity.x *= -0.5;
  }

  // jump
  if ( y < 100 && velocity.y <= 0 && playerValues.jump)
    jump_on_queue = true;

  if ( y <= 0 )
  {
    if (jump_on_queue)
    {  
      velocity.y = jump_limit;
      jump_on_queue = false;
    }
    else
      velocity.y *=  fabs(velocity.y) > 200 ? -0.2 : 0; // floor bounce and friction

    y = 0;
  }
  else
    velocity.y = y > 0 ? velocity.y - gravity : 0; // gravity doing its thing

	// update position
  x += velocity.x / Renderer::frameRate;
  y += velocity.y / Renderer::frameRate;

  Rectangle::update();
}

Shield::Shield(Player* player)
{
  this->player = player;
  r = player->w * 2;
}

void Shield::update()
{
  if (on)
  {
    x = player->x + player->w / 2;
    y = player->y + player->h / 2;
  }

  Circle::update();
}

void Shield::draw()
{
  if (on)
    Circle::draw();
}
