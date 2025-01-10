#pragma once

#include <Arduino.h>

struct Agent {
  const char* agentId;
  const char* name;
  const void* avatar;
};

extern Agent agent_amy;
extern Agent agent_lisa;
extern Agent agent_sam;
extern Agent agent_tony;

extern Agent agents[4];
