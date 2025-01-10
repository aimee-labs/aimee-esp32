#include "agents.h"

#include <lvgl.h>

LV_IMAGE_DECLARE(img_avatar_amy);
LV_IMAGE_DECLARE(img_avatar_lisa);
LV_IMAGE_DECLARE(img_avatar_sam);
LV_IMAGE_DECLARE(img_avatar_tony);

Agent agent_amy = {
    "amy",
    "Amy",
    &img_avatar_amy,
};

Agent agent_lisa = {
    "lisa",
    "Lisa",
    &img_avatar_lisa,
};

Agent agent_sam = {
    "sam",
    "Sam",
    &img_avatar_sam,
};

Agent agent_tony = {
    "tony",
    "Tony",
    &img_avatar_tony,
};

Agent agents[] = {
    agent_amy,
    agent_lisa,
    agent_sam,
    agent_tony,
};
