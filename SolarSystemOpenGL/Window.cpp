#include "include/Window.h"

Window::Window()
	: WIDTH(DEFAULT_WIDTH)
	, HEIGHT(DEFAULT_HEIGHT)
	, mWindow(nullptr)
	, mBufferWidth(0)
	, mBufferHeight(0)
	, mLastX(0.f)
	, mLastY(0.f)
	, mXChange(0.f)
	, mYChange(0.f)
	, mMouseFirstMoved(true) {
	//memset(mKeys, false, 512);
	for (int i = 0; i < 512; ++i) {
		mKeys[i] = false;
	}
}

Window::Window(const GLint windowWidth, const GLint windowHeight)
	: WIDTH(windowWidth)
	, HEIGHT(windowHeight)
	, mWindow(nullptr)
	, mBufferWidth(0)
	, mBufferHeight(0), mLastX(0.f)
	, mLastY(0.f)
	, mXChange(0.f)
	, mYChange(0.f)
	, mMouseFirstMoved(true) {
	//memset(mKeys, false, 512);
	for (int i = 0; i < 512; ++i) {
		mKeys[i] = false;
	}
}

Window::~Window() {
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

int Window::Initialise() {
	// Initialise GLFW

	if (!glfwInit()) {
		SPDLOG_ERROR("GLFW initialisation failed!");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Core profile = No Backwards compatiblity
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create window
	mWindow = glfwCreateWindow(WIDTH, HEIGHT, "Main window", NULL, NULL);
	if (!mWindow) {
		SPDLOG_ERROR("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get Buffer size information
	glfwGetFramebufferSize(mWindow, &mBufferWidth, &mBufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mWindow);

	// Handle key + mouse input
	CreateCallbacks();

	// Hide mouse cursor in window
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow mordern extension features
	glewExperimental = GL_TRUE;

	// Initialise GLEW
	if (glewInit() != GLEW_OK) {
		SPDLOG_ERROR("GLEW initialisation failed!");;
		glfwDestroyWindow(mWindow);
		glfwTerminate();
		return 1;
	}

	// Depth test
	glEnable(GL_DEPTH_TEST);

	// Setup viewport size
	glViewport(0, 0, mBufferWidth, mBufferHeight);

	// Set window user pointer
	glfwSetWindowUserPointer(mWindow, this);

	return 0;
}

bool Window::GetShouldClose() {
	return glfwWindowShouldClose(mWindow);
}

void Window::SwapBuffers() {
	glfwSwapBuffers(mWindow);
}

GLint Window::GetBufferWidth() const {
	return mBufferWidth;
}

GLint Window::GetBufferHeight() const {
	return mBufferHeight;
}

bool* Window::GetKeys()
{
	return mKeys;
}

GLfloat Window::GetXChange() {
	GLfloat theChange = mXChange;
	mXChange = 0;
	return theChange;
}

GLfloat Window::GetYChange() {
	GLfloat theChange = mYChange;
	mYChange = 0;
	return theChange;
}

void Window::CreateCallbacks(){
	glfwSetKeyCallback(mWindow, HandleKeys);
	glfwSetCursorPosCallback(mWindow, HandleMouse);
}

void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (0 <= key && key < 512) {
		if (action == GLFW_PRESS) {
			theWindow->mKeys[key] = true;
			SPDLOG_INFO("Pressed {}", key);
		}
		else if (action == GLFW_RELEASE) {
			theWindow->mKeys[key] = false;
			SPDLOG_INFO("Released {}", key);
		}
	}
}

void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mMouseFirstMoved) {
		theWindow->mLastX = static_cast<GLfloat>(xPos);
		theWindow->mLastY = static_cast<GLfloat>(yPos);
		theWindow->mMouseFirstMoved = false;
	}

	theWindow->mXChange = static_cast<GLfloat>(xPos - theWindow->mLastX);
	theWindow->mYChange = static_cast<GLfloat>(theWindow->mLastY - yPos);

	theWindow->mLastX = static_cast<GLfloat>(xPos);
	theWindow->mLastY = static_cast<GLfloat>(yPos);

	//SPDLOG_INFO("x: {}, y: {}", theWindow->mXChange, theWindow->mYChange);
	printf("x: %.6f, y: %.6f\n", theWindow->mXChange, theWindow->mYChange);
}
