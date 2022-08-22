// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTargetDummp.h"
#include "Components/StaticMeshComponent.h"
#include "MyAttributeComponent.h"

// Sets default values
AMyTargetDummp::AMyTargetDummp()
{
    AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>("AttributeComp");
    AttributeComp->OnHealthChanged.AddDynamic(this, &AMyTargetDummp::OnHealthChanged);

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
    RootComponent = MeshComp;
}

void AMyTargetDummp::OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta)
{
    if (Delta < 0.0f)
    {
        MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
    }
}




