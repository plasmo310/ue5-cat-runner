// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CatAnimInstance.generated.h"

/**
 * ねこ: AnimInstance
 */
UCLASS()
class UCatAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	/** update event */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "CatRunner: Cat")
	bool bIsRunState;

	UPROPERTY(BlueprintReadOnly, Category = "CatRunner: Cat")
	bool bIsJumpState;

	UPROPERTY(BlueprintReadOnly, Category = "CatRunner: Cat")
	bool bIsRotateLState;

	UPROPERTY(BlueprintReadOnly, Category = "CatRunner: Cat")
	bool bIsRotateRState;

	UPROPERTY(BlueprintReadOnly, Category = "CatRunner: Cat")
	bool bIsSquatState;

};
