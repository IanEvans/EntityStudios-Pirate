#ifndef STATE_H
#define STATE_H

template <class entity>

class State
{
	public:
		//executed when state is first entered
		virtual void Enter(entity*) = 0;
		//executed when an update function of an entity called
		virtual void Execute(entity*) = 0;
		//executed when the state is exited
		virtual void Exit(entity*) = 0;

		virtual ~State(){}
};

#endif