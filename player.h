#ifndef PLAYER_H
#define PLAYER_H

#include "game_element.h"
#include "opponent.h"

class Player : public GameElement {
 public:
  Player(int x, int y) : GameElement(x, y, 5, 5) {}

  Player() : Player(0, 0) {}

  void Draw(graphics::Image &image);

  void Move(const graphics::Image &object) {}

 private:
  int x_;
  int y_;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  PlayerProjectile() : PlayerProjectile(0, 0) {}

  void Draw(graphics::Image &image);

  void Move(const graphics::Image &object) {
    SetY(GetY() - 3);
    if (IsOutOfBounds(object)) {
      SetIsActive(false);
    } else {
      SetIsActive(true);
    }
  }

 private:
  int x_;
  int y_;
};

#endif
