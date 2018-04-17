#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctTextures.h"
#include "ctAudio.h"
#include "ctRender.h"
#include "ctWindow.h"
#include "ctEntities.h"
#include "ctInputCombo.h"
#include "InputEvent.h"

#include "ctMap.h"

#include "ctFadeToBlack.h"

#include <list>
#include <vector>



ctMap::ctMap() : ctModule()
{
	name = "map";
}

// Destructor
ctMap::~ctMap()
{}

// Called before render is available

bool ctMap::Awake(pugi::xml_node& conf)
{
	
	bool ret = true;

	

	return ret;
}

// Called before the first frame
bool ctMap::Start()
{
	bool ret = true;



	return ret;
}

// Called each loop iteration
bool ctMap::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool ctMap::Update(float dt)
{

	


	return true;
}

// Called each loop iteration
bool ctMap::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool ctMap::CleanUp()
{
	

	return true;
}

bool ctMap::Load(pugi::xml_node& load)
{
	bool ret = true;

	return ret;
}

bool ctMap::Save(pugi::xml_node& save) const
{
	bool ret = true;

	return ret;
}

void ctMap::OnUITrigger(UIElement* elementTriggered, UI_State ui_state)
{
}


void ctMap::LoadRect(pugi::xml_node rect_node, SDL_Rect* rect)
{
	rect->x = rect_node.attribute("x").as_float();
	rect->y = rect_node.attribute("y").as_float();
	rect->w = rect_node.attribute("width").as_float();
	rect->h = rect_node.attribute("height").as_float();
}


