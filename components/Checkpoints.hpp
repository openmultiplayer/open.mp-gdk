#pragma once
#include "../main.hpp"

namespace ompgdk
{
	inline bool SetPlayerCheckpoint(int playerid, float x, float y, float z, float size)
	{
		IPlayerCheckpointData* playerCheckpointData = GetPlayerData<IPlayerCheckpointData>(playerid);
		if (playerCheckpointData)
		{
			IPlayerStandardCheckpointData& cp = playerCheckpointData->getStandardCheckpoint();
			cp.setPosition({ x, y, z });
			cp.setRadius(size); //samp native receives radius not diameter
			cp.enable();
			return true;
		}
		return false;
	}

	inline bool DisablePlayerCheckpoint(int playerid)
	{
		IPlayerCheckpointData* playerCheckpointData = GetPlayerData<IPlayerCheckpointData>(playerid);
		if (playerCheckpointData)
		{
			IPlayerStandardCheckpointData& cp = playerCheckpointData->getStandardCheckpoint();
			cp.disable();
			return true;
		}
		return false;
	}

	inline bool IsPlayerInCheckpoint(int playerid)
	{
		IPlayerCheckpointData* playerCheckpointData = GetPlayerData<IPlayerCheckpointData>(playerid);
		if (playerCheckpointData)
		{
			IPlayerStandardCheckpointData& cp = playerCheckpointData->getStandardCheckpoint();
			if (cp.isEnabled())
			{
				return cp.isPlayerInside();
			}
		}
		return false;
	}

	inline bool SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, float nextx, float nexty, float nextz, float size)
	{
		IPlayerCheckpointData* playerCheckpointData = GetPlayerData<IPlayerCheckpointData>(playerid);
		if (playerCheckpointData)
		{
			IPlayerRaceCheckpointData& cp = playerCheckpointData->getRaceCheckpoint();
			if (type >= 0 && type <= 8)
			{
				cp.setType(RaceCheckpointType(type));
				cp.setPosition({ x, y, z });
				cp.setNextPosition({ nextx, nexty, nextz });
				cp.setRadius(size); // samp native receives radius unlike standard checkpoints
				cp.enable();
				return true;
			}
		}
		return false;
	}

	inline bool DisablePlayerRaceCheckpoint(int playerid)
	{
		IPlayerCheckpointData* playerCheckpointData = GetPlayerData<IPlayerCheckpointData>(playerid);
		if (playerCheckpointData)
		{
			IPlayerRaceCheckpointData& cp = playerCheckpointData->getRaceCheckpoint();
			cp.disable();
			return true;
		}
		return false;
	}

	inline bool IsPlayerInRaceCheckpoint(int playerid)
	{
		IPlayerCheckpointData* playerCheckpointData = GetPlayerData<IPlayerCheckpointData>(playerid);
		if (playerCheckpointData) 
		{
			IPlayerRaceCheckpointData& cp = playerCheckpointData->getRaceCheckpoint();
			if (cp.getType() != RaceCheckpointType::RACE_NONE && cp.isEnabled()) {
				return cp.isPlayerInside();
			}
		}
		return false;
	}

	inline bool IsPlayerCheckpointActive(int playerid)
	{
		IPlayerCheckpointData* playerData = GetPlayerData<IPlayerCheckpointData>(playerid);
		if (playerData) 
		{
			return playerData->getStandardCheckpoint().isEnabled();
		}
		return false;
	}

	inline bool GetPlayerCheckpoint(int playerid, float* x, float* y, float* z, float* size)
	{
		IPlayerCheckpointData* playerData = GetPlayerData<IPlayerCheckpointData>(playerid);
		if (playerData) 
		{
			const IPlayerStandardCheckpointData& data = playerData->getStandardCheckpoint();
			Vector3 pos = data.getPosition();
			*x = pos.x;
			*y = pos.y;
			*z = pos.z;
			*size = data.getRadius();
			return true;
		}
		return false;
	}

	inline bool IsPlayerRaceCheckpointActive(int playerid)
	{
		IPlayerCheckpointData* playerData = GetPlayerData<IPlayerCheckpointData>(playerid);
		if (playerData) 
		{
			return playerData->getRaceCheckpoint().isEnabled();
		}
		return false;
	}

	inline bool GetPlayerRaceCheckpoint(int playerid, float* x, float* y, float* z, float* nx, float* ny, float* nz, float* size)
	{
		IPlayerCheckpointData* playerData = GetPlayerData<IPlayerCheckpointData>(playerid);
		if (playerData) 
		{
			const IPlayerRaceCheckpointData& data = playerData->getRaceCheckpoint();
			Vector3 pos = data.getPosition();
			*x = pos.x;
			*y = pos.y;
			*z = pos.z;

			Vector3 next = data.getNextPosition();
			*nx = next.x;
			*ny = next.y;
			*nz = next.z;

			*size = data.getRadius();
			return true;
		}
		return false;
	}

}
