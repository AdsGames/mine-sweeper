#include "./Intro.h"

#include <asw/asw.h>

#include "../Controls.h"

// Constructor
void Intro::init() {
  timer = 0.0F;

  // Intro
  intro = create_object<asw::game::Sprite>();
  intro->set_texture(asw::assets::load_texture("assets/images/intro.png"));

  // Title
  title = create_object<asw::game::Sprite>();
  title->set_texture(asw::assets::load_texture("assets/images/title.png"));
}

void Intro::update(float dt) {
  Scene::update(dt);
  timer += dt;

  const auto keyboard = asw::input::get_keyboard();

  intro->active = timer < 1.0F;
  title->active = timer > 1.0F;

  if (timer < 0.2F) {
    intro->alpha =
        asw::util::lerp(0.0F, 1.0F, static_cast<float>(timer) / 0.2F);
  } else if (timer > 0.8F && timer < 1.0F) {
    intro->alpha =
        asw::util::lerp(1.0F, 0.0F, static_cast<float>(timer - 0.8F) / 0.2F);
  } else if (timer > 1.0F && timer < 1.2F) {
    title->alpha =
        asw::util::lerp(0.0F, 1.0F, static_cast<float>(timer - 1.0F) / 0.2F);
  } else if (timer > 2.8F && timer < 3.0F) {
    title->alpha =
        asw::util::lerp(1.0F, 0.0F, static_cast<float>(timer - 2.8F) / 0.2F);
  }

  if (timer >= 3.0F || keyboard.any_pressed ||
      asw::input::get_action_down(controls::UI_CONFIRM) ||
      asw::input::get_action_down(controls::UI_BACK)) {
    manager.set_next_scene(States::Menu);
  }
}

void Intro::draw() {
  Scene::draw();
}