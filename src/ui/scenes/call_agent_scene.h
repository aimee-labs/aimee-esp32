#pragma once

#include <mx.h>

#include "agents/agents.h"

class CallAgentScene : public MXScene {
 public:
  enum ConnectionStatus {
    CONNECTING,
    CONNECTED,
  };

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
  ConnectionStatus connectionStatus = CONNECTING;
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
  void setConnectionStatus(ConnectionStatus status);
};

extern CallAgentScene *callAgentScene;
