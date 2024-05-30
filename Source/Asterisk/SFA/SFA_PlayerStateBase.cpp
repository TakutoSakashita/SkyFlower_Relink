// Fill out your copyright notice in the Description page of Project Settings.


#include "SFA_PlayerStateBase.h"

//debug
#include "../DebugHelpers.h"
#define LOG_PRINT 1
#define DEBUG_PRINT(text) if(LOG_PRINT) Debug::Print(text);
#define DEBUG_FIXED(text,num) if(LOG_PRINT) Debug::PrintFixedLine(text, num);


//
//void USFA_PlayerStateBase::TickState(float DeltaTime)
//{
//	DEBUG_FIXED("USFA_PlayerStateBase::TickState", 600)
//}
