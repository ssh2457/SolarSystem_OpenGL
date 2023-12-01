#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

#include "Common.h"

class Window {
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
public:
	Window();
	Window(const GLint windowWidth, const GLint windowHeight);
	virtual ~Window();

	int Initialise();

	bool GetShouldClose();
	void SwapBuffers();

	GLint GetBufferWidth() const;
	GLint GetBufferHeight() const;

	bool* GetKeys();
	GLfloat GetXChange();
	GLfloat GetYChange();

private:
	GLFWwindow* mWindow;

	// Window dimensions
	const GLint WIDTH, HEIGHT;
	GLint mBufferWidth, mBufferHeight;

	bool mKeys[512];
	GLfloat mLastX, mLastY, mXChange, mYChange;
	bool mMouseFirstMoved;

	void CreateCallbacks();
};