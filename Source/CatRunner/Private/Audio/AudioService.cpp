// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "AudioService.h"

#include "Kismet/GameplayStatics.h"

UAudioService::UAudioService()
	:BgmAudioComponent(nullptr)
{
}

void UAudioService::PlayBgm(USoundBase* PlayBgm)
{
	if (PlayBgm == nullptr)
	{
		return;
	}

	// 初回orシーン遷移後はAudioComponentを生成する
	if (BgmAudioComponent == nullptr || !IsValid(BgmAudioComponent))
	{
		const UWorld* CurrentWorld = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();
		BgmAudioComponent = UGameplayStatics::SpawnSound2D(CurrentWorld, PlayBgm);
		return;
	}

	// 再生する音源を差し替える
	BgmAudioComponent->Stop();
	BgmAudioComponent->SetSound(PlayBgm);
	BgmAudioComponent->Play();
}

void UAudioService::StopBgm() const
{
	if (BgmAudioComponent == nullptr)
	{
		return;
	}
	BgmAudioComponent->Stop();
}

void UAudioService::PlaySe2d(USoundBase* PlaySe)
{
	if (PlaySe == nullptr)
	{
		return;
	}
	const UWorld* CurrentWorld = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();
	UGameplayStatics::PlaySound2D(CurrentWorld, PlaySe);
}

void UAudioService::PlaySe3d(USoundBase* PlaySe, const FVector& PlayLocation)
{
	if (PlaySe == nullptr)
	{
		return;
	}
	const UWorld* CurrentWorld = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();
	UGameplayStatics::PlaySoundAtLocation(CurrentWorld, PlaySe, PlayLocation);
}
