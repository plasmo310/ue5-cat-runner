// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Gimmick/BlockGimmick.h"

#include "Camera/CameraComponent.h"
#include "Cat/CatCharacter.h"
#include "GameInstance/CatRunnerGameInstance.h"
#include "Kismet/GameplayStatics.h"

ABlockGimmick::ABlockGimmick()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABlockGimmick::BeginPlay()
{
	Super::BeginPlay();
}

void ABlockGimmick::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsValid(this))
	{
		return;
	}

	// カメラがある程度近づいたら破棄する
	// 徐々に半透明にするなどした方が見栄えがよさそうだが、時間がないので暫定対処.
	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	const ACatCharacter* PlayerCharacter = Cast<ACatCharacter>(PlayerPawn);
	if (PlayerCharacter != nullptr
		&& PlayerCharacter->GetCurrentState() != ECatState::TurnCorner)
	{
		const FVector CameraLocation = PlayerCharacter->GetFollowCamera()->GetComponentLocation();
		if (((CameraLocation - GetActorLocation()) * GetActorForwardVector()).GetAbs().Length() < HideCameraDistance)
		{
			Destroy();
		}
	}
}

FHitInfo ABlockGimmick::OnHit(AActor* HitActor)
{
	// エフェクト、サウンド再生
	const FVector PlayerLocation = HitActor->GetActorLocation();
	if (PlayerDestroyEffect != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), PlayerDestroyEffect, PlayerLocation);
	}
	if (PlayerDestroySound != nullptr)
	{
		UCatRunnerGameInstance::GetAudioService()->PlaySe3d(PlayerDestroySound, PlayerLocation);
	}

	// ヒット対象を破棄する
	FHitInfo HitInfo;
	HitInfo.bIsTargetDestroy = true;
	return HitInfo;
}
