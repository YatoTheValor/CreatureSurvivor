// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenMessage.h"

void UScreenMessage::SetMessageText(FString Message)
{
	FText MessageText = FText::FromString(Message);
	
	if (!MessageTextBlock)
	{
		UE_LOG(LogTemp, Error, TEXT("MessageTextBlock is null! Check the ScreenMessage Widget Blueprint"));
		return;
	}
	MessageTextBlock->SetText(MessageText);
}
