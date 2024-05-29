// ==================================================
// Filename	:	DebugHelpers.h
// Author	:	22cu0214 JinWener
// Description:	This file provides a collection of debugging utilities for displaying
//				messages and drawing shapes (e.g., spheres, lines, points) 
// Notes:		EXAMPLE
//				Debug::PrintFixedLine("Interact: " + FString::SanitizeFloat(value), 12);
//				DRAW_LINE(FVector, FVector);
// Update:		2024/04/05 22cu0214 init 
// ==================================================


/*
* copy-paste following to your .cpp file

//debug
#include "../DebugHelpers.h"
#define LOG_PRINT 1
#define DEBUG_PRINT(text) if(LOG_PRINT) Debug::Print(text);
#define DEBUG_FIXED(text,num) if(LOG_PRINT) Debug::PrintFixedLine(text, num);

*/

#pragma once

namespace Debug {

	/// <summary>
	/// Print message from top
	/// </summary>
	static void Print(const FString& Mng, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1) {
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 5.f, Color, Mng);
		}

		UE_LOG(LogTemp, Warning, TEXT("%s"), *Mng);
	}

	static void PrintFixedLine(const FString& Mng, int32 InKey = 1) {
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 5.f, FColor::MakeRandomColor(), Mng);
		}
	}
}

#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, true);
#define DRAW_SPHERE_COLOR(Location, Color) DrawDebugSphere(GetWorld(), Location, 8.f, 12, Color, false, 5.f);
#define DRAW_SPHERE_SingleFrame(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, false, -1.f);
#define DRAW_LINE(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.f);
#define DRAW_LINE_SingleFrame(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f);
#define DRAW_POINT(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, true);
#define DRAW_POINT_SingleFrame(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, false, -1.f);
#define DRAW_VECTOR(StartLocation, EndLocation) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Red, true); \
	}
#define DRAW_VECTOR_SingleFrame(StartLocation, EndLocation) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Red, false, -1.f); \
	}


// ==================================================
// Filename	:	
// Author	:	22cu0214 JinWener
// Description:	
// Notes:		
// Update:		[date]		[name]		[memo]
//				2024/05/21	22cu0214	
// ==================================================


	///////////////// override function

	///////////////// custom function

	///////////////// custom parameter