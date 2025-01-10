#pragma once

#include <mx.h>

#include "agents/agents.h"

class CallAgentScene : public MXScene {
 protected:
  Agent *agent = &agent_amy;

  MXObject *statusLabel;
  MXObject *nameLabel;
  MXObject *ring;
  MXObject *avatarImage;
  MXObject *callButton;

  void onInit() override;
  void onLayout() override;
};
