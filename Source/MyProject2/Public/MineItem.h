// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"


UCLASS()
class MYPROJECT2_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
public:
    AMineItem();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
    USphereComponent* ExplosionCollision;

    // ���߱��� �ɸ��� �ð� (5��)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
    float ExplosionDelay;
    // ���� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
    float ExplosionRadius;
    // ���� ������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
    float ExplosionDamage;

    FTimerHandle ExplosionTimerHandle;

    virtual void ActivateItem(AActor* Activator) override;

    void Explode();
};
