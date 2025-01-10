#include "ui/scenes/select_agent_scene.h"

#include <Arduino.h>

#include "agents/agents.h"
#include "ui/scenes/call_agent_scene.h"

LV_IMAGE_DECLARE(img_call);

void SelectAgentScene::onInit() {
  MXScene::onInit();

  uint32_t avatarSize = width() / 2;
  uint32_t buttonSize = 80;
  uint32_t paddingBottom = 12;

  pageContainer = mx(lv_tileview_create(root()->lv_object()))
                      ->size_full()
                      ->scroll_bar_hidden()
                      ->on(LV_EVENT_VALUE_CHANGED, [this](MXEvent *event) {
                        lv_obj_t *activeTile = lv_tileview_get_tile_active(
                            pageContainer->lv_object());
                        auto index = lv_obj_get_index(activeTile);
                        selectedAgent = &agents[index];
                      });
  const lv_dir_t dir = (lv_dir_t)(LV_DIR_TOP | LV_DIR_BOTTOM);
  for (int i = 0; i < sizeof(agents) / sizeof(agents[0]); i++) {
    auto page = mx(lv_tileview_add_tile(pageContainer->lv_object(), 0, i, dir))
                    ->size_full();
    auto label =
        page->add_label(agents[i].name, MX_FONT_SIZE_2XL)->center_x()->y(22);
    auto avatar = page->add_image(agents[i].avatar)
                      ->size(avatarSize, avatarSize)
                      ->scale(avatarSize / 160.0f)
                      ->center(0, -20);
  }
  MXObject *button = root()
                         ->add_button()
                         ->rounded_full(buttonSize)
                         ->bg(rgb(0x40D05B))
                         ->center_x()
                         ->y(height() - buttonSize - paddingBottom)
                         ->onClick([this](MXEvent *event) {
                           callAgentScene->setAgent(selectedAgent);
                           callAgentScene->show();
                         });
  button->add_image(&img_call)->center();
}

SelectAgentScene *selectAgentScene = new SelectAgentScene();
