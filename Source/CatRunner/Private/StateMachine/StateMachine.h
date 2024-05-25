// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"

/**
 * StateMachine
 * @tparam TOwner
 */
template<class TOwner>
class ZStateMachine
{
public:
	ZStateMachine(TOwner* Owner) :
		Owner_(Owner),
		CurrentStateId(-1),
		CurrentState(nullptr),
		PreviousState(nullptr),
		StateMap({})
	{}

	void OnBegin(int StateId);
	void OnTick(float DeltaTime);
	template<class TState>
	void Add(int StateId);
	void ChangeState(int StateId);
	int GetCurrentStateId() const { return CurrentStateId; }

private:
	TOwner* Owner_;
	int CurrentStateId;
	TSharedPtr<ZStateBase<TOwner>> CurrentState;
	TSharedPtr<ZStateBase<TOwner>> PreviousState;
	TMap<int, TSharedPtr<ZStateBase<TOwner>>> StateMap;

};

template <class TOwner>
void ZStateMachine<TOwner>::OnBegin(int StateId)
{
	if (!StateMap.Contains(StateId))
	{
		UE_LOG(LogTemp, Error, TEXT("not set stateId => %d"), StateId);
		return;
	}

	CurrentState = StateMap[StateId];
	CurrentStateId = StateId;
	CurrentState->OnBegin(Owner_);
}

template <class TOwner>
void ZStateMachine<TOwner>::OnTick(float DeltaTime)
{
	if (CurrentState == nullptr)
	{
		return;
	}
	CurrentState->OnTick(Owner_, DeltaTime);
}

template <class TOwner>
template <class TState>
void ZStateMachine<TOwner>::Add(int StateId)
{
	StateMap.Emplace(StateId, MakeShared<TState>());
}

template <class TOwner>
void ZStateMachine<TOwner>::ChangeState(int StateId)
{
	if (!StateMap.Contains(StateId))
	{
		UE_LOG(LogTemp, Error, TEXT("not set stateId => %d"), StateId);
		return;
	}

	PreviousState = CurrentState;
	CurrentState->OnEnd(Owner_);

	const auto NewState = StateMap[StateId];
	CurrentState = NewState;
	CurrentStateId = StateId;
	CurrentState->OnBegin(Owner_);
}
