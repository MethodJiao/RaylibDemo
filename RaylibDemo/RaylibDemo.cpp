// RaylibDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include <iostream>
#include "raylib.h"
#include <stdlib.h>
#include <vector>

using namespace std;
#define CUBECOUNT 500
#define SPEED 30

struct CubeInfo
{
	Vector3 cubePosition;
	float alpha;
};
#ifdef _DEBUG
int main()
#endif
#ifndef _DEBUG
int WinMain()
#endif
{

	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "RaylibDemo");

	// Define the camera to look into our 3d world
	Camera3D camera = { 0 };
	camera.position = Vector3{ 35.0f, 35.0f, 35.0f }; // Camera position
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

	//Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
	vector<CubeInfo> cubeInfoVec;

	for (size_t i = 0; i < CUBECOUNT; i++)
	{
		CubeInfo info;
		Vector3 cubePosition;
		cubePosition.x = float(rand() % 30 + 1);
		cubePosition.y = float(rand() % 30 + 1);
		cubePosition.z = float(rand() % 30 + 1);
		info.cubePosition = cubePosition;
		info.alpha = float((rand() % 10) / 10.0);
		cubeInfoVec.push_back(info);
	}
	SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

	SetTargetFPS(144);                   // Set our game to run at 240 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())        // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		UpdateCamera(&camera);

		if (IsKeyDown('Z')) camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		for (size_t i = 0; i < CUBECOUNT; i++)
		{
			if (cubeInfoVec[i].alpha < 0.05)
			{
				cubeInfoVec[i].alpha = float((rand() % 10) / 10.0);
				cubeInfoVec[i].cubePosition.x = float(rand() % 30 + 1);
				cubeInfoVec[i].cubePosition.y = float(rand() % 30 + 1);
				cubeInfoVec[i].cubePosition.z = float(rand() % 30 + 1);
			}
			else
			{
				cubeInfoVec[i].alpha -= float(0.1 / SPEED);
			}
			DrawCube(cubeInfoVec[i].cubePosition, 2.0f, 2.0f, 2.0f, Fade(VIOLET, cubeInfoVec[i].alpha));
			//DrawCubeWires(cubeInfoVec[i].cubePosition, 2.0f, 2.0f, 2.0f, Fade(BLACK, cubeInfoVec[i].alpha));
		}

		//DrawGrid(10, 1.0f);

		EndMode3D();

		DrawRectangle(10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(10, 10, 320, 133, BLUE);

		DrawText("Free camera default controls:", 20, 20, 10, BLACK);
		DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
		DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
		DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
		DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
		DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);
		DrawFPS(10, 10);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
