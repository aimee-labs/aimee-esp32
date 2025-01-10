#include "ui/scenes/select_agent_scene.h"

#include <Arduino.h>

#include "agents/agents.h"

void SelectAgentScene::onInit() {
  MXScene::onInit();

  auto pageContainer = mx(lv_tileview_create(root()->lv_object()))
                           ->size_full()
                           ->bg_transparent()
                           ->scroll_bar_active();
  const lv_dir_t dir = (lv_dir_t)(LV_DIR_LEFT | LV_DIR_RIGHT);
  uint32_t avatarSize = width() / 2;
  for (int i = 0; i < sizeof(agents) / sizeof(agents[0]); i++) {
    auto page = mx(lv_tileview_add_tile(pageContainer->lv_object(), i, 0, dir))
                    ->size_full();
    auto label =
        page->add_label(agents[i].name, MX_FONT_SIZE_2XL)->center_x()->y(22);
    auto avatar = page->add_image(agents[i].avatar)
                      ->size(avatarSize, avatarSize)
                      ->scale(avatarSize / 160.0f)
                      ->center(0, -20);
  }
  uint32_t buttonSize = 80;
  root()
      ->add_button(LV_SYMBOL_CALL, MX_FONT_SIZE_3XL)
      ->rounded_full(buttonSize)
      ->bg(rgb(0x40D05B))
      ->center_x()
      ->y(height() - buttonSize - 12);
}
