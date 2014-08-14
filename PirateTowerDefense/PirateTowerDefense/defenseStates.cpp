#include "defenseStates.h"
#include "defense.h"
#include <iostream>

using namespace std;

// ----- IDLE STATE -----
Idle* Idle::Instance()
{
	static Idle instance;

	return &instance;
}

void Idle::Enter(Defense* entity)
{
	cout << "Entered IDLE state" << endl;
}

void Idle::Execute(Defense* entity)
{
	cout << "Executing IDLE state" << endl;
}

void Idle::Exit(Defense* entity)
{
	cout << "Exited IDLE state" << endl;
}

// ----- AIMING STATE -----
Aiming* Aiming::Instance()
{
	static Aiming instance;

	return &instance;
}

void Aiming::Enter(Defense* entity)
{
	cout << "Entered AIMING state" << endl;
}

void Aiming::Execute(Defense* entity)
{
	cout << "Executing AIMING state" << endl;
}

void Aiming::Exit(Defense* entity)
{
	cout << "Exited AIMING state" << endl;
}

// ----- FIRING STATE -----
Firing* Firing::Instance()
{
	static Firing instance;

	return &instance;
}

void Firing::Enter(Defense* entity)
{
	cout << "Entered FIRING state" << endl;
}

void Firing::Execute(Defense* entity)
{
	cout << "Executing FIRING state" << endl;
}

void Firing::Exit(Defense* entity)
{
	cout << "Exited FIRING state" << endl;
}