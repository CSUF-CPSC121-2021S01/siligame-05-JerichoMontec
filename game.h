#ifndef GAME_H
#define GAME_H

#include <vector>

#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game(int width, int height) : my_screen(width, height) {}

  Game() : Game(800, 600) {}

  graphics::Image &GetGameScreen() { return my_screen; }

  std::vector<std::unique_ptr<Opponent>>* GetOpponents() { return &opponents; }

  std::vector<std::unique_ptr<OpponentProjectile>>* GetOpponentProjectiles() {
    return &o_projectiles;
  }

  std::vector<std::unique_ptr<PlayerProjectile>>* GetPlayerProjectiles() {
    return &p_projectiles;
  }

  Player &GetPlayer() { return my_player; }

  void CreateOpponents() {
    std::unique_ptr<Opponent> opponent_;
    for (int i = 0; i < 5; i++) {
      opponent_ = std::make_unique<Opponent>(100 * i, 20);
      opponents.push_back(std::move(opponent_));
    }
  }

  /*void CreateOpponentProjectiles() {
    for (int i = 0; i < 5; i++) {
      OpponentProjectile my_opponent_projectile(100 * i, 100);
      o_projectiles.push_back(my_opponent_projectile);
    }
  }

  void CreatePlayerProjectiles() {
    for (int i = 0; i < 5; i++) {
      PlayerProjectile my_player_projectile(100 * i, 450);
      p_projectiles.push_back(my_player_projectile);
    }
  }*/

  void Init() {
    my_player.SetX(375);
    my_player.SetY(500);
    /*CreateOpponents();
    CreateOpponentProjectiles();
    CreatePlayerProjectiles();*/
    my_screen.AddMouseEventListener(*this);
    my_screen.AddAnimationEventListener(*this);
  }

  void MoveGameElements() {
    for (int i = 0; i < opponents.size(); i++) {
      opponents[i] = std::make_unique<Opponent>();
      if (opponents[i]->GetIsActive()) {
        opponents[i]->Move(my_screen);
      }
    }

    for (int i = 0; i < o_projectiles.size(); i++) {
      o_projectiles[i] = std::make_unique<OpponentProjectile>();
      if (o_projectiles[i]->GetIsActive()) {
        o_projectiles[i]->Move(my_screen);
      }
    }

    for (int i = 0; i < p_projectiles.size(); i++) {
      p_projectiles[i] = std::make_unique<PlayerProjectile>();
      if (p_projectiles[i]->GetIsActive()) {
        p_projectiles[i]->Move(my_screen);
      }
    }
  }

  void FilterIntersections() {
    for (int i = 0; i < opponents.size(); i++) {
      opponents[i] = std::make_unique<Opponent>();
      if (my_player.IntersectsWith(opponents[i])) {
        my_player.SetIsActive(false);
        opponents[i]->SetIsActive(false);
      }
    }

    for (int i = 0; i < p_projectiles.size(); i++) {
      p_projectiles[i] = std::make_unique<PlayerProjectile>();
      if (p_projectiles[i]->IntersectsWith(opponents[i])) {
        p_projectiles[i]->SetIsActive(false);
        opponents[i]->SetIsActive(false);
      }
    }

    for (int i = 0; i < o_projectiles.size(); i++) {
      o_projectiles[i] = std::make_unique<OpponentProjectile>();
      if (my_player.IntersectsWith(o_projectiles[i])) {
        my_player.SetIsActive(false);
        o_projectiles[i]->SetIsActive(false);
      }
    }
  }

  void UpdateScreen() {
    my_screen.DrawRectangle(0, 0, 800, 600, graphics::Color(0, 0, 0));
    if (my_player.GetIsActive()) {
      my_player.Draw(my_screen);
    }

    for (int i = 0; i < opponents.size(); i++) {
      opponents[i] = std::make_unique<Opponent>();
      if (opponents[i]->GetIsActive()) {
        opponents[i]->Draw(my_screen);
      }
    }

    for (int i = 0; i < o_projectiles.size(); i++) {
      o_projectiles[i] = std::make_unique<OpponentProjectile>();
      if (o_projectiles[i]->GetIsActive()) {
        o_projectiles[i]->Draw(my_screen);
      }
    }

    for (int i = 0; i < p_projectiles.size(); i++) {
      p_projectiles[i] = std::make_unique<PlayerProjectile>();
      if (p_projectiles[i]->GetIsActive()) {
        p_projectiles[i]->Draw(my_screen);
      }
    }
  }

  void OnAnimationStep() {
    MoveGameElements();
    FilterIntersections();
    UpdateScreen();
    my_screen.Flush();
  }

  void OnMouseEvent(const graphics::MouseEvent &event) {
    if (event.GetMouseAction() == graphics::MouseAction::kMoved ||
        event.GetMouseAction() == graphics::MouseAction::kDragged) {
      if (event.GetX() < 800 && event.GetY() < 600) {
        my_player.SetX(event.GetX());
        my_player.SetY(event.GetY());
      }
    }
  }

  int GetScore() const { return score_; }

  bool HasLost() const {
    if (lost_) {
      return true;
    } else {
      return false;
    }
  }

  void LaunchProjectiles() {
    for (int i = 0; i < opponents[i].size(); i++) {
      if (opponents[i]->LaunchProjectile() != nullptr) {
        opponents.push_back(std::move(opponents[i]->LaunchProjectile()));
      }
    }
  }

  void Start() { my_screen.ShowUntilClosed(); }

 private:
  graphics::Image my_screen;
  std::vector<std::unique_ptr<Opponent>> opponents;
  std::vector<std::unique_ptr<OpponentProjectile>> o_projectiles;
  std::vector<std::unique_ptr<PlayerProjectile>> p_projectiles;
  Player my_player;
  int width_;
  int height_;
  int score_ = 0;
  bool lost_;
};

#endif
