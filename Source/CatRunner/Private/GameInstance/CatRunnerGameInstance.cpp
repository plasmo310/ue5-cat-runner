// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "GameInstance/CatRunnerGameInstance.h"

#include "Audio/AudioService.h"

UCatRunnerGameInstance::UCatRunnerGameInstance(const FObjectInitializer& ObjectInitializer)
	:AudioService(nullptr)
{
	AudioService = NewObject<UAudioService>();
}

UCatRunnerGameInstance* UCatRunnerGameInstance::GetInstance()
{
	UCatRunnerGameInstance* Instance = nullptr;

	if (GEngine != nullptr)
	{
		const FWorldContext* CurrentWorldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
		Instance = Cast<UCatRunnerGameInstance>(CurrentWorldContext->World()->GetGameInstance());
	}
	return Instance;
}

// TODO サービスロケータを作ろうとして諦めた痕跡
// template <class ServiceType>
// void UCatRunnerGameInstance::ServiceRegister(ServiceType* Service)x
// {
// 	ServiceInstanceMap[typeid(ServiceType).hash_code()] = std::shared_ptr<void>(Service);
// }
//
// template <class ServiceType>
// std::shared_ptr<ServiceType> UCatRunnerGameInstance::ServiceResolve()
// {
// 	const size_t Key = typeid(ServiceType).hash_code();
// 	if (!ServiceInstanceMap.contains(Key))
// 	{
// 		return nullptr;
// 	}
// 	return Cast<ServiceType>(ServiceInstanceMap[Key]);
// }
