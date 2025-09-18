#pragma once
#include <asteroid/asteroid.h>
#include <entity/entity.h>
#include <player/player.h>
#include <uiElement/uiElement.h>
#include <utils/gameUtils.h>

int InitGame(GameOptions options);

int RunGame(GameOptions options);

int ShutdownGame(GameOptions options);
