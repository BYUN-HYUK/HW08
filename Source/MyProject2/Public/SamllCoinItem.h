
#pragma once

#include "CoreMinimal.h"
#include "CoinItem.h"
#include "SamllCoinItem.generated.h"


UCLASS()
class MYPROJECT2_API ASamllCoinItem : public ACoinItem
{
	GENERATED_BODY()

public:
	ASamllCoinItem();

	virtual void ActivateItem(AActor* Activator) override;
};
