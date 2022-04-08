#pragma once
#include "../main.hpp"

namespace ompgdk
{
	inline int CreatePickup(int model, int type, float x, float y, float z, int virtualworld)
	{
		IPickupsComponent* component = GDKManager::Get()->GetPickups();
		if (component)
		{
			IPickup* pickup = component->create(model, type, { x, y, z }, virtualworld, false);
			if (pickup)
			{
				return pickup->getID();
			}
		}
		return INVALID_PICKUP_ID;
	}

	inline bool DestroyPickup(int pickupid)
	{
		IPickup* pickup = GetEntity<IPickup>(pickupid);
		if (pickup) 
		{
			GDKManager::Get()->GetPickups()->release(pickup->getID());
			return true;
		}
		return false;
	}
}
