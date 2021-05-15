#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include "cpputils/graphics/image.h"

class GameElement {
 public:
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}

  GameElement() : GameElement(0, 0, 50, 50) {}

  int GetX() const { return x_; }
  void SetX(int x) { x_ = x; }

  int GetY() const { return y_; }
  void SetY(int y) { y_ = y; }

  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  bool GetIsActive() const { return is_active; }
  void SetIsActive(bool active) { is_active = active; }

  virtual void Draw(graphics::Image &my_screen) = 0;

  virtual void Move(const graphics::Image &object) = 0;

  bool IntersectsWith(GameElement* element) {
    if (x_ >= element->GetX() && x_ <= element->GetX() + element->GetWidth()) {
      return true;
    } else if (y_ >= element->GetY() &&
               y_ <= element->GetY() + element->GetHeight()) {
      return true;
    } else {
      return false;
    }
  }

  bool IsOutOfBounds(const graphics::Image &object) {
    if (x_ + width_ < object.GetWidth() &&
        x_ > object.GetWidth() - object.GetWidth()) {
      if (y_ + height_ < object.GetHeight() &&
          y_ > object.GetHeight() - object.GetHeight()) {
        return false;
      } else {
        return true;
      }
    } else {
      return true;
    }
  }

 protected:
  int width_ = 50;
  int height_ = 50;

 private:
  int x_ = 0;
  int y_ = 0;
  bool is_active = true;
};

#endif
