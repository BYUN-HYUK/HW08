// Fill out your copyright notice in the Description page of Project Settings.


#include "SamllCoinItem.h"

ASamllCoinItem::ASamllCoinItem()
{
	PointValue = 10;
	ItemType = "SmallCoin";
}

void ASamllCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}