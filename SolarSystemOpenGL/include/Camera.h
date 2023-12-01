#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera() = delete;
	Camera(glm::vec3& startPosition, glm::vec3& startWorldUp,
		GLfloat startYaw, GLfloat startPitch,
		GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	virtual ~Camera();

	void KeyControl(bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange);
	glm::mat4 CalcViewMatrix();
	glm::vec3 GetCameraPosition() const;
	glm::vec3 GetCameraDirection() const;
private:
	glm::vec3 mPosition, mFront, mUp, mRight, mWorldUp;

	GLfloat mYaw, mPitch;
	GLfloat mMovementSpeed, mTurnSpeed;

	void Update();

};