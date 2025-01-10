#pragma once

#include <mx.h>

class WiFiMulti;

class WiFiConnectionScene : public MXScene {
 protected:
  uint8_t updateTimes = 0;
  MXObject* icon;
  MXObject* label;
  WiFiMulti* wifiMulti;

  void onInit() override;
  void onShown() override;
  void onUpdate() override;
};

extern WiFiConnectionScene* wifiConnectionScene;
