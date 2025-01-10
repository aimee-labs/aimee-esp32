#pragma once

#include <mx.h>

#include "agents/agents.h"

class CallAgentScene : public MXScene {
 public:
  enum ConnectionStatus {
    CONNECTING,
    CONNECTED,
  };

 protected:
  ConnectionStatus connectionStatus = CONNECTING;
  Agent *agent = &agent_amy;
  time_t callStartTime = 0;

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
