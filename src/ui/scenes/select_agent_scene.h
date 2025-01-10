#pragma once

#include <mx.h>

#include "agents/agents.h"

class SelectAgentScene : public MXScene {
 protected:
  MXObject* pageContainer;
  Agent* selectedAgent = &agent_amy;

  void onInit() override;
};

extern SelectAgentScene* selectAgentScene;
