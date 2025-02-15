// Fill out your copyright notice in the Description page of Project Settings.


#include "Mytast01Actor.h"

// Sets default values
AMytast01Actor::AMytast01Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMytast01Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMytast01Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

