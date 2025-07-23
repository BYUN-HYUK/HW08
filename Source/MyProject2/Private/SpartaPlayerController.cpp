
#include "SpartaPlayerController.h"
#include "SpartaGameStateBase.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"

ASpartaPlayerController::ASpartaPlayerController()
    : InputMappingContext(nullptr),
    MoveAction(nullptr),
    JumpAction(nullptr),
    LookAction(nullptr),
    SprintAction(nullptr),
    HUDWidgetClass(nullptr),
    HUDWidgetInstance(nullptr)
{
}

void ASpartaPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // ���� PlayerController�� ����� Local Player ��ü�� ������    
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        // Local Player���� EnhancedInputLocalPlayerSubsystem�� ȹ��
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
                // Subsystem�� ���� �츮�� �Ҵ��� IMC�� Ȱ��ȭ
                // �켱����(Priority)�� 0�� ���� ���� �켱����
                Subsystem->AddMappingContext(InputMappingContext, 0);
            }
        }

        // HUD ���� ���� �� ǥ��
        if (HUDWidgetClass)
        {
            HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
            if (HUDWidgetInstance)
            {
                HUDWidgetInstance->AddToViewport();
            }
        }
        ASpartaGameStateBase* SpartaGameStateBase = GetWorld() ? GetWorld()->GetGameState<ASpartaGameStateBase>() : nullptr;
        if (SpartaGameStateBase)
        {
            SpartaGameStateBase->UpdateHUD();
        }
    }   
}

UUserWidget* ASpartaPlayerController::GetHUDWidget() const
{
    return HUDWidgetInstance;
}