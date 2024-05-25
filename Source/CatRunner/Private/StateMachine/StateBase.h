// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * StateMachine: StateBase
 * @tparam TOwner
 */
template<class TOwner>
class ZStateBase
{
public:
	ZStateBase();
	virtual ~ZStateBase() = default;
	virtual void OnBegin(TOwner* StateOwner);
	virtual void OnTick(TOwner* StateOwner, float DeltaTime);
	virtual void OnEnd(TOwner* StateOwner);

};

template <class TOwner>
ZStateBase<TOwner>::ZStateBase()
{
}

template <class TOwner>
void ZStateBase<TOwner>::OnBegin(TOwner* StateOwner)
{
}

template <class TOwner>
void ZStateBase<TOwner>::OnTick(TOwner* StateOwner, float DeltaTime)
{
}

template <class TOwner>
void ZStateBase<TOwner>::OnEnd(TOwner* StateOwner)
{
}
