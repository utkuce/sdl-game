#ifndef PLAYER_H
#define PLAYER_H

#include "../myengine/src/Shape.h"
#include "../myengine/src/EventHandler.h"

class Player;

class Shield : public Circle
{
  public:
    Shield(Player*);
    Player* player;
    bool on = false;

    void update() override;
    void draw() override;
};

class Player : public Rectangle
{
  friend class Shield;
    
  public:
    Player();
    ~Player();
    void update() override;

  protected:
    struct { float x = 0, y = 0; } velocity;
    float acceleration = 0, gravity = 0;

  private:
    const int speed_limit = 1000, jump_limit = 3000;
    Shield* shield;

    struct {
      bool goRight = false, goLeft = false, jump = false;
    } playerValues;
    
};

#endif
