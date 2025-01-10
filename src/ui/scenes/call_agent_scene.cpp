#include "call_agent_scene.h"

void CallAgentScene::onInit() {
  MXScene::onInit();

  statusLabel = root()->add_label("Calling...")->text_secondary();
  nameLabel = root()->add_label(agent->name, MX_FONT_SIZE_2XL);
  ring = root()->add_object();
  avatarImage = root()->add_image(agent->avatar);
  callButton = root()->add_button(LV_SYMBOL_CALL, MX_FONT_SIZE_3XL);
}

void CallAgentScene::onLayout() {
  statusLabel->center_x(0, 28);
  nameLabel->center_x(0, 54);
  ring->rounded_full(160 - 8)
      ->center()
      ->border(4, lv_color_white())
      ->opacity(0.6);
  avatarImage->size(160)->center();
  int32_t buttonSize = 80;
  callButton->rounded_full(buttonSize)
      ->bg(rgb(0xFF3B2F))
      ->center_x()
      ->y(height() - buttonSize - 12);
}
