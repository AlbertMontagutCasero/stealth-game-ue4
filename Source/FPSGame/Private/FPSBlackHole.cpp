// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereCompSuck = CreateDefaultSubobject<USphereComponent>(TEXT("SphereSuck"));
	SphereCompSuck->SetSphereRadius(3000);
	SphereCompSuck->SetupAttachment(MeshComp);
	/*
	SphereCompSuck->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCompSuck->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCompSuck->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	*/

	SphereCompDestroy = CreateDefaultSubobject<USphereComponent>(TEXT("SphereDestroy"));
	SphereCompDestroy->SetSphereRadius(200);
	SphereCompDestroy->SetupAttachment(MeshComp);

	SphereCompDestroy->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::OverlapDestroyerSphere);
	/*
	SphereCompSuck->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCompSuck->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCompSuck->SetCollisionResponseToChannel( ECC_PhysicsBody, ECR_Overlap);
	*/
}

void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSBlackHole::OverlapDestroyerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<UPrimitiveComponent*> OverlappingComps;
	SphereCompSuck->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); i++)
	{
		UPrimitiveComponent* PrimComp = OverlappingComps[i];
		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			const float SphereRadius = SphereCompSuck->GetScaledSphereRadius();
			const float ForceStrenght = -2000;

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrenght, ERadialImpulseFalloff::RIF_Linear, true);
		}

	}
}

