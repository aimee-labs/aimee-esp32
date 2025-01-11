#pragma once

#include <ArduinoWebsockets.h>

using namespace websockets;

class VoiceChatSession;

class VoiceChatClient {
 public:
  VoiceChatClient();

  VoiceChatSession* startSession(const char* agentId);
  void update();

 private:
  WebsocketsClient* _ws = nullptr;
  VoiceChatSession* _session = nullptr;

  void _handleConnectionOpened();
  void _handleConnectionClosed();
};
