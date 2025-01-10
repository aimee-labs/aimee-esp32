#include <WiFi.h>

#include "ui/scenes/call_agent_scene.h"
#include "ui/scenes/select_agent_scene.h"
#include "ui/scenes/wifi_connection_scene.h"

WiFiConnectionScene *wifiConnectionScene;
SelectAgentScene *selectAgentScene;
CallAgentScene *callAgentScene;

void app_setup() {
  wifiConnectionScene = new WiFiConnectionScene();
  selectAgentScene = new SelectAgentScene();
  callAgentScene = new CallAgentScene();

  MXScene *FIRST_SCENE = callAgentScene;
  FIRST_SCENE->show();
}

void app_loop() {
  if (WiFi.status() == WL_CONNECTED &&
      MXScene::activeScene() == wifiConnectionScene) {
    selectAgentScene->show();
  }
}
