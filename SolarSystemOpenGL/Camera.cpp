#include "include/Camera.h"

Camera::Camera(const glm::vec3& startPosition, const glm::vec3& startWorldUp,
	GLfloat startYaw, GLfloat startPitch,
	GLfloat startMoveSpeed, GLfloat startTurnSpeed)
	: mPosition(startPosition)
	, mWorldUp(startWorldUp)
	, mYaw(startYaw)
	, mPitch(startPitch)
	, mMovementSpeed(startMoveSpeed)
	, mTurnSpeed(startTurnSpeed)
	, mFront(glm::vec3(0.f, 0.f, 0.f))
	, mUp(glm::vec3(0.f, 0.f, 0.f))
	, mRight(glm::vec3(0.f, 0.f, 0.f)) {
	Update();
}

Camera::~Camera() {

}

void Camera::KeyControl(bool* keys, GLfloat deltaTime) {
	GLfloat velocity = mMovementSpeed * deltaTime;

	if (keys[GLFW_KEY_W]) {
		mPosition += mFront * velocity;
	}

	if (keys[GLFW_KEY_S]) {
		mPosition -= mFront * velocity;
	}

	if (keys[GLFW_KEY_A]) {
		mPosition -= mRight * velocity;
	}

	if (keys[GLFW_KEY_D]) {
		mPosition += mRight * velocity;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange) {
	xChange *= mTurnSpeed;
	yChange *= mTurnSpeed;

	mYaw += xChange;
	mPitch += yChange;

	if (mPitch > 89.f) {
		mPitch = 89.f;
	}

	if (mPitch < -89.f) {
		mPitch = -89.f;
	}

	Update();
}

glm::mat4 Camera::CalcViewMatrix() {
	return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

glm::vec3 Camera::GetCameraPosition() const {
	return mPosition;
}

glm::vec3 Camera::GetCameraDirection() const {
	return mFront;
}

void Camera::Update() {
	mFront.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	mFront.y = sin(glm::radians(mPitch));
	mFront.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	mFront = glm::normalize(mFront);

	mRight = glm::normalize(glm::cross(mFront, mWorldUp));
	mUp = glm::normalize(glm::cross(mRight, mFront));
}
