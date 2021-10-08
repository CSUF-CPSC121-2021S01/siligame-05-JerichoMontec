#ifndef OPPONENT_H
#define OPPONENT_H

#include "game_element.h"

class Opponent : public GameElement {
 public:
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}

  Opponent() : Opponent(0, 0) {}

  void Move(const graphics::Image &object) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
    if (IsOutOfBounds(object)) {
      SetIsActive(false);
    } else {
      SetIsActive(true);
    }
  }

  void Draw(graphics::Image &image);

  OpponentProjectile* LaunchProjectile() {
    counter++;
    if (counter == 10) {
      return std::unique_ptr<OpponentProjectile> o_p;
    } else {
      return nullptr;
    }
  }

 private:
  int x_;
  int y_;
  int counter;
};

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  OpponentProjectile() : OpponentProjectile(0, 0) {}

  void Move(const graphics::Image &object) {
    SetY(GetY() + 3);
    if (IsOutOfBounds(object)) {
      SetIsActive(false);
    } else {
      SetIsActive(true);
    }
  }

  void Draw(graphics::Image &image);

 private:
  int x_;
  int y_;
};

#endif
