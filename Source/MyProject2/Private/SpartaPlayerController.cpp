
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

    // 현재 PlayerController에 연결된 Local Player 객체를 가져옴    
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        // Local Player에서 EnhancedInputLocalPlayerSubsystem을 획득
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
                // Subsystem을 통해 우리가 할당한 IMC를 활성화
                // 우선순위(Priority)는 0이 가장 높은 우선순위
                Subsystem->AddMappingContext(InputMappingContext, 0);
            }
        }

        // HUD 위젯 생성 및 표시
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