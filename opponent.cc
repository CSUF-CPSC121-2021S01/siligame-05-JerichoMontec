#include "opponent.h"

void Opponent::Draw(graphics::Image& image) {
  image.DrawRectangle(GetX(), GetY() + 5, GetWidth() - 15, GetHeight() - 10,
                      255, 220, 155);
  image.DrawRectangle(GetX() + 35, GetY() + 5, GetWidth() - 35,
                      GetHeight() - 10, 255, 220, 155);
  image.DrawRectangle(GetX() + 15, GetY(), GetWidth() - 30, GetHeight(), 178,
                      50, 50);
}

void OpponentProjectile::Draw(graphics::Image& image) {
  image.DrawCircle(GetX() + 2, GetY() + 2, 2, 213, 208, 93);
}
