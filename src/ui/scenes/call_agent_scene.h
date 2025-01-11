#pragma once

#include <mx.h>

#include "agents/agents.h"

class VoiceChatSession;

class CallAgentScene : public MXScene {
 public:
  inline void setAgent(Agent *value) {
    agent = value;
    if (nameLabel) {
      nameLabel->text(agent->name);
    }
    if (avatarImage) {
      avatarImage->src(agent->avatar);
    }
  }

 protected:
  Agent *agent = &agent_amy;
  time_t connectionStartTime = 0;

  MXObject *statusLabel;
  MXObject *nameLabel;
  MXObject *ring;
  MXObject *avatarImage;
  MXObject *callImage;
  MXObject *callButton;

  void onInit() override;
  void onLayout() override;
  void onShown() override;
  void onUpdate() override;

 private:
  VoiceChatSession *_session = nullptr;
  bool _readyState = false;
  void _setReadyState(bool readyState);
};

extern CallAgentScene *callAgentScene;
