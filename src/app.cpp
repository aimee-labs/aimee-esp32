#include <WiFi.h>

#include "ui/scenes/call_agent_scene.h"
#include "ui/scenes/select_agent_scene.h"
#include "ui/scenes/wifi_connection_scene.h"

void app_setup() { wifiConnectionScene->show(); }

void app_loop() {
  if (WiFi.status() == WL_CONNECTED &&
      MXScene::activeScene() == wifiConnectionScene) {
    selectAgentScene->show();
  }
}
