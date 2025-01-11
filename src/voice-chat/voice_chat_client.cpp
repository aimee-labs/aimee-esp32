#include "voice_chat_client.h"

#include "voice_chat_session.h"

#define VOICE_CHAT_URL "ws://192.168.2.2:8080/api/voice-chat/realtime"

VoiceChatClient::VoiceChatClient() {}

VoiceChatSession* VoiceChatClient::startSession(const char* agentId) {
  _ws = new WebsocketsClient();
  _ws->onEvent([this](WebsocketsEvent event, String data) {
    if (event == WebsocketsEvent::ConnectionOpened) {
      _handleConnectionOpened();
    } else if (event == WebsocketsEvent::ConnectionClosed) {
      _handleConnectionClosed();
    }
  });

  _session = new VoiceChatSession(_ws);
  if (_ws->connect(VOICE_CHAT_URL)) {
    return _session;
  } else {
    ESP_LOGE("VoiceChatClient", "Failed to connect to voice chat server %s",
             VOICE_CHAT_URL);
    return nullptr;
  }
}

void VoiceChatClient::update() {
  if (_ws != nullptr) {
    _ws->poll();
  }
  if (_session != nullptr) {
    _session->update();
  }
}

void VoiceChatClient::_handleConnectionOpened() {
  ESP_LOGI("VoiceChatClient", "Connection opened");
  if (_session != nullptr) {
    _session->start();
  }
}

void VoiceChatClient::_handleConnectionClosed() {
  ESP_LOGI("VoiceChatClient", "Connection closed");
  delete _session;
  _session = nullptr;
  delete _ws;
  _ws = nullptr;
}
