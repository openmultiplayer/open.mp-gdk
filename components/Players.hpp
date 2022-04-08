#pragma once
#include "../main.hpp"

namespace ompgdk
{
	inline bool RemovePlayerMapIcon(int playerid, int iconid)
	{
		GET_PLAYER_CHECKED(player, playerid, false);
		player->unsetMapIcon(iconid);
		return true;
	}

	inline bool SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, int color, int style)
	{
		GET_PLAYER_CHECKED(player, playerid, false); 
		player->setMapIcon(iconid, { x, y, z }, markertype, Colour::FromRGBA(color), MapIconStyle(style));
		return true;
	}

	inline bool IsPlayerNPC(int playerid)
	{
		GET_PLAYER_CHECKED(player, playerid, false); 
		return player->isBot();
	}

	inline bool TogglePlayerControllable(int playerid, bool toggle)
	{
		GET_PLAYER_CHECKED(player, playerid, false);
		player->setControllable(toggle);
		return true;
	}

	inline int GetPlayerInterior(int playerid)
	{
		GET_PLAYER_CHECKED(player, playerid, 0);
		return player->getInterior();
	}

	inline int GetPlayerVirtualWorld(int playerid)
	{
		GET_PLAYER_CHECKED(player, playerid, 0);
		return player->getVirtualWorld();
	}

	inline int GetPlayerState(int playerid)
	{
		GET_PLAYER_CHECKED(player, playerid, PlayerState::PlayerState_None);
		return player->getState();
	}

	inline bool IsPlayerInAnyVehicle(int playerid)
	{
		IPlayerVehicleData* data = GetPlayerData<IPlayerVehicleData>(playerid);
		if (data)
		{
			IVehicle* vehicle = data->getVehicle();
			if (vehicle)
			{
				return true;
			}
		}
		return false;
	}

	inline bool GetPlayerPos(int playerid, float* x, float* y, float* z)
	{
		GET_PLAYER_CHECKED(player, playerid, false);
		Vector3 pos = player->getPosition();
		*x = pos.x;
		*y = pos.y;
		*z = pos.z;
		return true;
	}

	inline bool GetPlayerVelocity(int playerid, float* x, float* y, float* z)
	{
		GET_PLAYER_CHECKED(player, playerid, false);
		Vector3 velocity = player->getVelocity();
		*x = velocity.x;
		*y = velocity.y;
		*z = velocity.z;
		return true;
	}

	inline bool GetPlayerFacingAngle(int playerid, float* angle)
	{
		GET_PLAYER_CHECKED(player, playerid, false);
		GTAQuat quat = player->getRotation();
		*angle = quat.ToEuler().z;
		return true;
	}

	inline int GetPlayerTargetActor(int playerid)
	{
		GET_PLAYER_CHECKED(player, playerid, INVALID_PLAYER_ID);
		IActor* target = player->getTargetActor();
		if (target)
		{
			return target->getID();
		}
		return INVALID_PLAYER_ID;
	}

	inline int GetPlayerCameraTargetActor(int playerid)
	{
		GET_PLAYER_CHECKED(player, playerid, INVALID_ACTOR_ID);
		IActor* target = player->getCameraTargetActor();
		if (target)
		{
			return target->getID();
		}
		return INVALID_ACTOR_ID;
	}

	inline bool GetPlayerCameraPos(int playerid, float* x, float* y, float* z)
	{
		GET_PLAYER_CHECKED(player, playerid, false);
		PlayerAimData data = player->getAimData();
		Vector3 pos = data.camPos;
		*x = pos.x;
		*y = pos.y;
		*z = pos.z;
		return true;
	}

	inline int GetPlayerVehicleID(int playerid)
	{
		IPlayerVehicleData* data = GetPlayerData<IPlayerVehicleData>(playerid);
		if (data) {
			IVehicle* vehicle = data->getVehicle();
			if (vehicle) {
				return vehicle->getID();
			}
		}
		return 0;
	}

	inline int GetPlayerCameraTargetObject(int playerid)
	{
		GET_PLAYER_CHECKED(player, playerid, INVALID_OBJECT_ID);
		IObject* target = player->getCameraTargetObject();
		if (target) 
		{
			return target->getID();
		}
		return INVALID_OBJECT_ID;
	}

	inline bool AttachCameraToPlayerObject(int playerid, int objectid)
	{
		GET_PLAYER_CHECKED(player, playerid, false);
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		player->attachCameraToObject(*object);
		return true;
	}

	inline bool SetPlayerPos(int playerid, float x, float y, float z)
	{
		GET_PLAYER_CHECKED(player, playerid, false);
		player->setPosition({ x, y, z });
		return true;
	}
}
