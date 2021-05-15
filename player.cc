#include "player.h"

void Player::Draw(graphics::Image &image) {
  image.DrawRectangle(GetX() + 10, GetY() + 8, GetWidth() - 20, GetHeight() - 8,
                      255, 0, 0);
  image.DrawRectangle(GetX() + 22, GetY(), GetWidth() - 45, GetHeight() - 32,
                      255, 0, 0);
}

void PlayerProjectile::Draw(graphics::Image &image) {
  image.DrawCircle(GetX() + 2, GetY() + 2, 2, 255, 0, 0);
}
