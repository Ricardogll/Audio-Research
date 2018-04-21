#ifndef __ctMap_H__
#define __ctMap_H__

#include "ctModule.h"

#include "ctGui.h"
#include "Player.h"

class ctMap : public ctModule
{
public:

	ctMap();

	// Destructor
	virtual ~ctMap();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	void OnUITrigger(UIElement* elementTriggered, UI_State ui_state);

private:
	
	void LoadRect(pugi::xml_node rect_node, SDL_Rect* rect);

	

private:

	
	Player* player=nullptr;
};


#endif 