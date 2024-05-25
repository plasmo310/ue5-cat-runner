// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Cat/CatCharacter.h"

void ACatCharacter::StateTurnCorner::OnBegin(ACatCharacter* StateOwner)
{
	ZStateBase::OnBegin(StateOwner);

	bIsArriveTurnCorner = false;
	TotalLookCameraDuration = 0.0f;

	// カメラをいい感じに視点に変更
	const FRotator LookCameraRotator = StateOwner->GetController()->GetControlRotation() + StateOwner->ChangeTurnCornerRotator.GetInverse() + LookCameraExtendRotator;
	StateOwner->GetController()->SetControlRotation(LookCameraRotator);
}

void ACatCharacter::StateTurnCorner::OnTick(ACatCharacter* StateOwner, float DeltaTime)
{
	ZStateBase::OnTick(StateOwner, DeltaTime);

	if (!bIsArriveTurnCorner)
	{
		// 曲がるポイントに到着したかのチェック
		constexpr float AllowDistance = 50.0f;
		const auto CurrentLocation = StateOwner->GetActorLocation();
		const auto DiffForwardLocation = (StateOwner->StartTurnCornerPoint - CurrentLocation).GetAbs() * StateOwner->GetActorForwardVector();
		if (DiffForwardLocation.Length() <= AllowDistance)
		{
			bIsArriveTurnCorner = true;

			// プレイヤーを回転させる
			const FVector NewActorLocation = CurrentLocation + DiffForwardLocation;
			StateOwner->SetActorLocation(NewActorLocation);
			const FRotator NewActorRotator = StateOwner->GetActorRotation() + StateOwner->ChangeTurnCornerRotator;
			StateOwner->SetActorRotation(NewActorRotator);
		}
	}
	else
	{
		// 一定時間経過したらカメラを戻す
		TotalLookCameraDuration += DeltaTime;
		if (TotalLookCameraDuration >= LookCameraDuration)
		{
			StateOwner->GetController()->SetControlRotation(StateOwner->GetActorRotation());
			StateOwner->ChangeState(ECatState::Run);
		}
	}
}

void ACatCharacter::StateTurnCorner::OnEnd(ACatCharacter* StateOwner)
{
	ZStateBase::OnEnd(StateOwner);
}
