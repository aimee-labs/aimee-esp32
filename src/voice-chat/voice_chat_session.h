#pragma once

class VoiceChatSession {
 public:
  enum ConnectionState {
    CONNECTION_STATE_INITIAL,
    CONNECTION_STATE_CONNECTING,
    CONNECTION_STATE_CONNECTED,
    CONNECTION_STATE_DISCONNECTED,
  };

  enum SessionState {
    SESSION_STATE_IDLE,
    SESSION_STATE_USER_SPEAKING,
    SESSION_STATE_AGENT_SPEAKING,
  };

  VoiceChatSession(const char* agentId);

  inline ConnectionState connectionState() const { return _connectionState; }
  inline SessionState state() const { return _state; }

  void start();
  void stop();
  void update();

 private:
  const char* _agentId;
  ConnectionState _connectionState = CONNECTION_STATE_INITIAL;
  SessionState _state = SESSION_STATE_IDLE;

  inline void _setState(SessionState state) {
    if (_state != state) {
      _state = state;
    }
  }

  inline void _setConnectionState(ConnectionState state) {
    if (_connectionState != state) {
      _connectionState = state;
    }
  }
};
