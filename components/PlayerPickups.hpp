#pragma once
#include "../main.hpp"

namespace ompgdk
{
	static IPickup* TryGetPickup(IPlayer& player, int pickupID) noexcept
	{
		auto data = queryExtension<IPlayerPickupData>(player);
		auto pool = GDKManager::Get()->GetPickups();
		if (data && pool)
		{
			return pool->get(data->fromLegacyID(pickupID));
		}
		return nullptr;
	}

	inline int CreatePlayerPickup(int playerid, int model, int type, float x, float y, float z, int virtualWorld)
	{
		IPickupsComponent* component = GDKManager::Get()->GetPickups();
		GET_PLAYER_CHECKED(player, playerid, INVALID_PICKUP_ID);
		IPlayerPickupData* data = GetPlayerData<IPlayerPickupData>(playerid);
		if (component && data)
		{
			int id = data->reserveLegacyID();
			if (id == INVALID_PICKUP_ID)
			{
				return INVALID_PICKUP_ID;
			}

			IPickup* pickup = component->create(model, type, { x, y, z }, virtualWorld, false);
			if (pickup)
			{
				data->setLegacyID(id, pickup->getID());
				pickup->setLegacyPlayer(player);
				return id;
			}
			else
			{
				data->releaseLegacyID(id);
			}
		}
		return INVALID_PICKUP_ID;
	}

	inline bool DestroyPlayerPickup(int playerid, int pickupid)
	{
		IPickupsComponent* component = GDKManager::Get()->GetPickups();
		IPlayerPickupData* data = GetPlayerData<IPlayerPickupData>(playerid);
		if (component && data)
		{
			int realid = data->fromLegacyID(pickupid);
			if (realid)
			{
				component->release(realid);
				data->releaseLegacyID(pickupid);
				return true;
			}
		}
		return false;
	}
}
