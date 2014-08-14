#ifndef DEF_STATE_H
#define DEF_STATE_H

#include "State.h"

/* States - 
Idle, Radius Check,
Aiming, Firing, 
Reloading, Inactive, 
Boarded, Building?, 
Upgrading?
*/
class Defense;

// --------- IDLE STATE ----------
class Idle : public State<Defense>
{
private:
	Idle(){}
public:
	static Idle* Instance();

	virtual void Enter(Defense* entity);
	virtual void Execute(Defense* entity);
	virtual void Exit(Defense* entity);
};

// --------- AIMING STATE ----------
class Aiming : public State<Defense>
{
private:
	Aiming(){}
public:
	static Aiming* Instance();

	virtual void Enter(Defense* entity);
	virtual void Execute(Defense* entity);
	virtual void Exit(Defense* entity);
};

// --------- FIRING STATE ----------
class Firing : public State<Defense>
{
private:
	Firing(){}
public:
	static Firing* Instance();

	virtual void Enter(Defense* entity);
	virtual void Execute(Defense* entity);
	virtual void Exit(Defense* entity);
};

#endif