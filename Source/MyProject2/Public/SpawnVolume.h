// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"   
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT2_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    USceneComponent* Scene;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    UBoxComponent* SpawningBox;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    UDataTable* ItemDataTable;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    AActor* SpawnRandomItem();

    FVector GetRandomPointInVolume() const;
    FItemSpawnRow* GetRandomItem() const;
    AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
  

};
