#include "ui/scenes/wifi_connection_scene.h"

#include <WiFi.h>
#include <WiFiMulti.h>

void WiFiConnectionScene::onInit() {
  MXScene::onInit();

  icon = root()
             ->add_label(LV_SYMBOL_WIFI, MX_FONT_SIZE_3XL)
             ->center(0, -21)
             ->text_primary();
  wifiMulti = new WiFiMulti();

  label = root()
              ->add_label("Connecting to WiFi...", MX_FONT_SIZE_XL)
              ->center(0, 21)
              ->text_center();
}

void WiFiConnectionScene::onShown() {
  MXScene::onShown();

  wifiMulti->addAP("Henry's iPhone 14 Pro", "13913954971");
  wifiMulti->addAP("Henry's Living Room 2.4GHz", "13913954971");
}

void WiFiConnectionScene::onUpdate() {
  if (updateTimes < 15) {
    updateTimes++;
    return;
  }

  if (WiFi.status() != WL_CONNECTED) {
    wifiMulti->run(10 * 60 * 1000);
  } else {
    label->text("WiFi connected");
  }
}

WiFiConnectionScene *wifiConnectionScene = new WiFiConnectionScene();
