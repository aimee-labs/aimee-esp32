#include "voice_chat_session.h"

#include <audio.h>

VoiceChatSession::VoiceChatSession(WebsocketsClient* ws) : _ws(ws) {
  _ws->onMessage([this](WebsocketsMessage message) {
    if (message.isText()) {
      JsonDocument json;
      DeserializationError error = deserializeJson(json, message.c_str());
      if (error) {
        ESP_LOGE("VoiceChatSession", "Failed to deserialize message: %s",
                 error.c_str());
        return;
      }

      String type = json["type"].as<String>();
      if (type == "event") {
        _handleEventMessage(json);
      }
    } else if (message.isBinary()) {
      ESP_LOGI("VoiceChatSession", "Received binary message");

      auto raw = message.c_str();
      _handleBinaryMessage((uint8_t*)raw, message.length());
    }
  });
}

VoiceChatSession::~VoiceChatSession() {
  _state = SESSION_STATE_INITIAL;
  _connectionState = CONNECTION_STATE_DISCONNECTED;
  _ws = nullptr;
}

void VoiceChatSession::start() {
  _setConnectionState(CONNECTION_STATE_CONNECTED);
  _sendStartCommand();
}

void VoiceChatSession::stop() {
  _setConnectionState(CONNECTION_STATE_DISCONNECTING);
  _ws->close();
}

void VoiceChatSession::update() {
  if (isReady()) {
    if (Audio.in()->available()) {
      uint8_t frameBuffer[AUDIO_IN_FRAME_SIZE];
      size_t bytesRead =
          Audio.in()->readBytes((char*)frameBuffer, AUDIO_IN_FRAME_SIZE);
      _ws->sendBinary((char*)frameBuffer, bytesRead);
    }
  }
}

void VoiceChatSession::_sendStartCommand() {
  const char* json = R"({
  "type": "command",
  "name": "start-session",
  "payload": {}
})";
  _ws->send(json);
}

void VoiceChatSession::_handleEventMessage(JsonDocument& eventJSON) {
  String eventName = eventJSON["name"].as<String>();
  ESP_LOGI("VoiceChatSession", "Received event message type: %s",
           eventName.c_str());
  if (eventName == "session-started") {
    _handleSessionStartedEvent();
  }
}

void VoiceChatSession::_handleBinaryMessage(uint8_t* data, size_t size) {
  if (_state == SESSION_STATE_IDLE || _state == SESSION_STATE_AGENT_SPEAKING) {
    Audio.out()->write(data, size);
  }
}

void VoiceChatSession::_handleSessionStartedEvent() {
  _setState(SESSION_STATE_IDLE);
}
