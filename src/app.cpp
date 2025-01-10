#include "ui/scenes/wifi_connection_scene.h"

WiFiConnectionScene *wifiConnectionScene;

void app_main() {
  wifiConnectionScene = new WiFiConnectionScene();
  wifiConnectionScene->show();
}
