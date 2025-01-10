#include "call_agent_scene.h"

#include "ui/scenes/select_agent_scene.h"
#include "utils/format_time.h"

LV_IMAGE_DECLARE(img_hang_up);
LV_IMAGE_DECLARE(img_hang_up_active);

void CallAgentScene::onInit() {
  MXScene::onInit();

  root()->bg(rgb(0xdf6962), 0);
  statusLabel = root()->add_label("Calling...")->text_secondary();
  nameLabel = root()->add_label(agent->name, MX_FONT_SIZE_2XL);
  ring = root()->add_object();
  avatarImage = root()->add_image(agent->avatar);
  callButton = root()->add_button();
  callImage = callButton->add_image(&img_hang_up)->center();
}

void CallAgentScene::onLayout() {
  MXScene::onLayout();

  if (height() >= 300) {
    // Large screen
    statusLabel->center_x(0, 28);
    nameLabel->center_x(0, 54);
    ring->rounded_full(144);
  } else {
    // Small screen
    statusLabel->center_x(0, 12);
    nameLabel->center_x(0, 40);
    ring->rounded_full(120);
  }

  ring->center()->border(4, lv_color_white())->opacity(0.6);

  avatarImage->size(160)->center();
  int32_t buttonSize = 80;
  callButton->rounded_full(buttonSize)
      ->bg(rgb(0xFF3B2F))
      ->border(4, rgb(0xFF3B2F))
      ->center_x()
      ->y(height() - buttonSize - 12)
      ->onClick([this](MXEvent *e) { selectAgentScene->show(); });
}

void CallAgentScene::onShown() {
  MXScene::onShown();

  callStartTime = millis();
  setConnectionStatus(CONNECTING);
}

void CallAgentScene::onUpdate() {
  MXScene::onUpdate();

  // TODO: remove this
  if (connectionStatus == CONNECTING && millis() - callStartTime > 1500) {
    callStartTime = millis();
    setConnectionStatus(CONNECTED);
  }
  // TODO: end of remove this

  if (connectionStatus == CONNECTED) {
    statusLabel->text(formatTimeSpan(millis() - callStartTime));
  }
}

void CallAgentScene::setConnectionStatus(ConnectionStatus status) {
  if (connectionStatus == status) return;

  connectionStatus = status;
  switch (status) {
    case CONNECTING:
      statusLabel->text("Connecting...");
      callImage->src(&img_hang_up);
      callButton->bg(rgb(0xFF3B2F));
      callButton->border(4, rgb(0xFF3B2F));
      root()->bg_opacity(0);
      break;
    case CONNECTED:
      callStartTime = time(nullptr);
      statusLabel->text("00:00");
      callImage->src(&img_hang_up_active);
      callButton->bg(lv_color_white());
      callButton->border(4, rgb(0xc45c57));

      lv_anim_t fadeIn;
      lv_anim_init(&fadeIn);
      lv_anim_set_var(&fadeIn, root()->lv_object());
      lv_anim_set_values(&fadeIn, 0, 255);
      lv_anim_set_duration(&fadeIn, 400);
      lv_anim_set_path_cb(&fadeIn, lv_anim_path_ease_out);
      lv_anim_set_exec_cb(&fadeIn, [](void *obj, int32_t opacity) {
        lv_obj_set_style_bg_opa((lv_obj_t *)obj, opacity, LV_PART_MAIN);
      });
      lv_anim_start(&fadeIn);

      break;
  }
}

CallAgentScene *callAgentScene = new CallAgentScene();
