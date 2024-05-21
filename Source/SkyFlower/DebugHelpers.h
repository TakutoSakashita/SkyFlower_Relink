// ==================================================
// Filename	:	DebugHelpers.h
// Author	:	22cu0214 JinWener
// Description:	This file provides a collection of debugging utilities for displaying
//				messages and drawing shapes (e.g., spheres, lines, points) 
// Notes:		EXAMPLE
//				Debug::PrintFixedLine("Interact: " + ObjectiveID, 12);
//				DRAW_LINE(FVector, FVector);
// Update:		[date]		[name]		[memo]
//				2024/05/21	22cu0214	update, add #define DEBUG_ENABLE
//				2024/04/05	22cu0214	init 
// ==================================================

#pragma once



#include "DrawDebugHelpers.h"
#include "Engine/World.h"

#define DEBUG_LOG_ENABLE
#define DEBUG_SHAPE_ENABLE
//use #undef to disable the debug log and shape

namespace Debug {

	/// <summary>
	/// Print message Newer on top
	/// </summary>
	/// <param name="Mng"> "hello world" </param>
	/// <param name="Color"> = FColor::MakeRandomColor() </param>
	/// <param name="InKey"> = -1 </param>
	static void Print(const FString& Mng, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1) {
#ifdef DEBUG_LOG_ENABLE
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 5.f, Color, Mng);
		}

		UE_LOG(LogTemp, Warning, TEXT("%s"), *Mng);
#endif
	}

	//to avoid conflict, message orderKey start from 10 
	static void PrintFixedLine(const FString& Mng, int32 InKey = 10) {
#ifdef DEBUG_LOG_ENABLE
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 5.f, FColor::MakeRandomColor(), Mng);
		}
#endif
	}



    // Function to draw a sphere
    static void DrawSphere(UWorld* World, FVector Location)
    {
#ifdef DEBUG_SHAPE_ENABLE
        if (World)
        {
            DrawDebugSphere(World, Location, 25.f, 12, FColor::Red, true);
        }
#endif
    }

    // Function to draw a sphere with a specified color
    static void DrawSphereWithColor(UWorld* World, FVector Location, FColor Color)
    {
#ifdef DEBUG_SHAPE_ENABLE
        if (World)
        {
            DrawDebugSphere(World, Location, 8.f, 12, Color, false, 5.f);
        }
#endif
    }

    // Function to draw a sphere for a single frame
    static void DrawSphereSingleFrame(UWorld* World, FVector Location)
    {
#ifdef DEBUG_SHAPE_ENABLE
        if (World)
        {
            DrawDebugSphere(World, Location, 25.f, 12, FColor::Red, false, -1.f);
        }
#endif
    }

    // Function to draw a line
    static void DrawLine(UWorld* World, FVector StartLocation, FVector EndLocation)
    {
#ifdef DEBUG_SHAPE_ENABLE
        if (World)
        {
            DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.f);
        }
#endif
    }

    // Function to draw a line for a single frame
    static void DrawLineSingleFrame(UWorld* World, FVector StartLocation, FVector EndLocation)
    {
#ifdef DEBUG_SHAPE_ENABLE
        if (World)
        {
            DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f);
        }
#endif
    }

    // Function to draw a point
    static void DrawPoint(UWorld* World, FVector Location)
    {
#ifdef DEBUG_SHAPE_ENABLE
        if (World)
        {
            DrawDebugPoint(World, Location, 15.f, FColor::Red, true);
        }
#endif
    }

    // Function to draw a point for a single frame
    static void DrawPointSingleFrame(UWorld* World, FVector Location)
    {
#ifdef DEBUG_SHAPE_ENABLE
        if (World)
        {
            DrawDebugPoint(World, Location, 15.f, FColor::Red, false, -1.f);
        }
#endif
    }

    // Function to draw a vector (line and point)
    static void DrawVector(UWorld* World, FVector StartLocation, FVector EndLocation)
    {
#ifdef DEBUG_SHAPE_ENABLE
        if (World)
        {
            DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.f);
            DrawDebugPoint(World, EndLocation, 15.f, FColor::Red, true);
        }
#endif
    }

    // Function to draw a vector (line and point) for a single frame
    static void DrawVectorSingleFrame(UWorld* World, FVector StartLocation, FVector EndLocation)
    {
#ifdef DEBUG_SHAPE_ENABLE
        if (World)
        {
            DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f);
            DrawDebugPoint(World, EndLocation, 15.f, FColor::Red, false, -1.f);
        }
#endif
    }

}


/*

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
	
*/


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