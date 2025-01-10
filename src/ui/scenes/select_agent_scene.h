#pragma once

#include <mx.h>

class SelectAgentScene : public MXScene {
 protected:
  MXObject* pageContainer;

  void onInit() override;
};
