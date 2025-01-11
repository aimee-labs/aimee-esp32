#include "voice_chat_client.h"

#include "voice_chat_session.h"

VoiceChatClient::VoiceChatClient() {}

VoiceChatSession* VoiceChatClient::startSession(const char* agentId) {
  _session = new VoiceChatSession(agentId);
  return _session;
}

void VoiceChatClient::update() {
  if (_session) {
    _session->update();
  }
}
