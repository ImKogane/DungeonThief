// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_HasSeenPlayer.h"
#include "AIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"

void UBT_HasSeenPlayer::ScheduleNextTick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ScheduleNextTick(OwnerComp, NodeMemory);

	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();

		//Line to the player -> PlayerPos - Enemy
		//Normalize that
		//GetForward from enemy
		//Calculate the dot product between forward and the line
		//Use ACos(degrees) from the dot result
		//Check if this is less than a certain amount
		
		// If true : AI can see player
		// else : AI can't see player

		FVector EnemyLocation = AIController->GetPawn()->GetActorLocation();
		FVector PlayerLocation = FVector::ZeroVector;

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		if (PlayerPawn)
		{
			PlayerLocation = PlayerPawn->GetActorLocation();
		}

		FVector LineToPlayer = (PlayerLocation - EnemyLocation).GetSafeNormal();

		FVector EnemyForward = AIController->GetPawn()->GetActorForwardVector();
		float DotProduct = FVector::DotProduct(LineToPlayer, EnemyForward);
		float ACos = FMath::RadiansToDegrees(FMath::Acos(DotProduct));
		
		if (ACos < 55.f)
		{
			BlackboardComponent->SetValueAsVector("PlayerLocation", PlayerLocation);
			BlackboardComponent->SetValueAsInt("HasSeenPlayer", 1);
		}
		else
		{
			BlackboardComponent->SetValueAsInt("HasSeenPlayer", 0);
		}
		
	}
	
}
