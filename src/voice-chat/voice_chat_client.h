#pragma once

#include <ArduinoWebsockets.h>

class VoiceChatSession;

class VoiceChatClient {
 public:
  VoiceChatClient();

  VoiceChatSession* startSession(const char* agentId);
  void update();

 private:
  VoiceChatSession* _session = nullptr;
};
