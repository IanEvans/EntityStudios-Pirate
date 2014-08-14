#ifndef STATEM_H
#define STATEM_H

#include "State.h"
template <class entity>

class StateMachine
{
private:
	entity* vOwner;
	State<entity>* vCurrentState;
	State<entity>* vPreviousState;
public:
	StateMachine(entity* owner):
	  vOwner(owner), vCurrentState(0), vPreviousState(0)
	  {}

	  void SetCurrentState(State<entity>* s){vCurrentState = s;}
	  void SetPreviousState(State<entity>* s){vPreviousState = s;}

	  virtual ~StateMachine(){}

	  void Update()const
	  {
		 // cout << "In StateMachine update" << endl;
		 // if (vGlobalState) vGlobalState->Execute(vOwner);
		  if (vCurrentState) vCurrentState->Execute(vOwner);
	  }

	  void ChangeState(State<entity>* vNewState)
	  {
		  vPreviousState = vCurrentState;
		  vCurrentState->Exit(vOwner);
		  vCurrentState = vNewState;
		  vCurrentState->Enter(vOwner);
	  }

	  void RevertToPreviousState()
	  {
		  ChangeState(vPreviousState);
	  }

	  State<entity>* CurrentState() const {return vCurrentState;}
	  State<entity>* PreviousState() const {return vPreviousState;}
};

#endif