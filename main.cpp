#include "./main.hpp"

using namespace ompgdk;

void GDKManager::Init(ICore* c, IComponentList* clist)
{
	core = c;
	componentList = clist;
	players = &core->getPlayers();

    actors = GetComponent<IActorsComponent>();
    objects = GetComponent<IObjectsComponent>();
    pickups = GetComponent<IPickupsComponent>();
    textlabels = GetComponent<ITextLabelsComponent>();
    vehicles = GetComponent<IVehiclesComponent>();
}
