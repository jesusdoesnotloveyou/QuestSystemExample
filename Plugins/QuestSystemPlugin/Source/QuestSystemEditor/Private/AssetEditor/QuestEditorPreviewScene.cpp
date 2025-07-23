// Quest System by JDNLY. All Rights Reserved


#include "AssetEditor/QuestEditorPreviewScene.h"
#include "Components/DirectionalLightComponent.h"
#include "GameFramework/WorldSettings.h"

FQuestEditorPreviewScene::FQuestEditorPreviewScene(ConstructionValues CVS) : FPreviewScene(CVS)
{
    // World settings
    GetWorld()->GetWorldSettings()->NotifyBeginPlay();
    GetWorld()->GetWorldSettings()->NotifyMatchStarted();
    GetWorld()->GetWorldSettings()->SetActorHiddenInGame(false);
    GetWorld()->bBegunPlay = true;;

    // Set light options
    DirectionalLight->SetRelativeLocation(FVector(-1024.0f, 1024.0f, 2048.0f));
    DirectionalLight->SetRelativeScale3D(FVector(15.f));
    
    SetLightBrightness(4.f);
    DirectionalLight->InvalidateLightingCache();
    DirectionalLight->RecreateRenderState_Concurrent();
    
    UStaticMeshComponent* SkyComponent = NewObject<UStaticMeshComponent>();
    UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/MapTemplates/Sky/SM_SkySphere.SM_SkySphere"), NULL, LOAD_None, NULL);
    UMaterial* SkyMaterial = LoadObject<UMaterial>(NULL, TEXT("/Engine/EditorMaterials/PersonaSky.PersonaSky"), NULL, LOAD_None, NULL);
    SkyComponent->SetStaticMesh(StaticMesh);
    SkyComponent->SetMaterial(0, SkyMaterial);

    constexpr float SkySphereScale = 1000.f;
    const FTransform SkyTransform(FRotator(0.0f), FVector(0.0f), FVector(SkySphereScale));

    AddComponent(SkyComponent, SkyTransform);

    // Now add floor
    UStaticMesh* FloorMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EditorMeshes/EditorCube.EditorCube"), NULL, LOAD_None, NULL);
    UStaticMeshComponent* FloorComp = NewObject<UStaticMeshComponent>();
    FloorComp->SetStaticMesh(FloorMesh);
    AddComponent(FloorComp, FTransform::Identity);
    FloorComp->SetRelativeScale3D(FVector(3.f, 3.f, 1.f));
    UMaterial* Material = LoadObject<UMaterial>(NULL, TEXT("/Engine/EditorMaterials/PersonaFloorMat.PersonaFloorMat"), NULL, LOAD_None, NULL);
    FloorComp->SetMaterial(0, Material);
    FloorComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    FloorComp->SetCollisionObjectType(ECC_WorldStatic);
}

FQuestEditorPreviewScene::~FQuestEditorPreviewScene()
{
}
