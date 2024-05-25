// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Audio/AudioService.h"
#include "Engine/GameInstance.h"
#include "CatRunnerGameInstance.generated.h"

/**
 * CatRunnerGameInstance
 * シーンをまたいで永続的に扱うオブジェクトを定義する
 */
UCLASS()
class UCatRunnerGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UCatRunnerGameInstance(const FObjectInitializer& ObjectInitializer);

public:
	static UCatRunnerGameInstance* GetInstance();
	static TObjectPtr<UAudioService> GetAudioService() { return GetInstance()->AudioService; }

	// TODO サービスロケータを作ろうとして諦めた形跡
	// template<class ServiceType>
	// static void ServiceRegister(ServiceType* Service);
	//
	// template<class ServiceType>
	// static std::shared_ptr<ServiceType> ServiceResolve();

private:
	UPROPERTY()
	TObjectPtr<UAudioService> AudioService;

	// static std::map<size_t, std::shared_ptr<void>> ServiceInstanceMap;

};
