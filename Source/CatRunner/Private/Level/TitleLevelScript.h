// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TitleLevelUiData.h"
#include "Engine/LevelScriptActor.h"
#include "TitleLevelScript.generated.h"

/**
 * Titleレベルクラス
 */
UCLASS()
class ATitleLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ATitleLevelScript();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	/** TitleレベルUIデータ */
	UPROPERTY()
	TObjectPtr<UTitleLevelUiData> TitleLevelUiData;

	/** TitleUI */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> TitleWidget;

	/** BGM: Title */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> BgmTitle;

};
