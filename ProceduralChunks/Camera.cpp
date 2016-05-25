#include "Camera.h"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <math.h>

Camera::Camera(const sf::Window* aWindow, float aWorldSize) :
	mWindow(aWindow),
	mView(),
	mMaxViewSize(aWorldSize),
	mMinViewSize(50.f),
	mViewSize(aWorldSize)
{
	UpdateAspectRatio();
	mView.setCenter(aWorldSize / 2, aWorldSize / 2);
}

Camera::~Camera() {}



void Camera::UpdateAspectRatio() {
	mAspectRatio = sf::Vector2f(
		std::fmaxf((float)mWindow->getSize().x / mWindow->getSize().y, 1.f),
		std::fmaxf((float)mWindow->getSize().y / mWindow->getSize().x, 1.f)
	);
	mView.setSize(GetViewSize() * mAspectRatio);
}

void Camera::SetViewSize(float aNewViewSize) {
	mViewSize = std::fmaxf(mMinViewSize, std::fminf(mMaxViewSize, aNewViewSize));
	mView.setSize(GetViewSize() * mAspectRatio);
}
void Camera::Update() {
	mVelocity = sf::Vector2f();
	UpdateAspectRatio();

	if (mMouseIsHeld != sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		mMouseIsHeld = !mMouseIsHeld;
		mMouseHeldLocation = sf::Mouse::getPosition();
	}

	if (mMouseIsHeld) {
		mVelocity = (sf::Vector2f)(mMouseHeldLocation - sf::Mouse::getPosition());
		mVelocity.x *= GetAspectRatio().x * (GetViewSize() / mWindow->getSize().x);
		mVelocity.y *= GetAspectRatio().y * (GetViewSize() / mWindow->getSize().y);
		mMouseHeldLocation = sf::Mouse::getPosition();
	}
	const float ZoomSpeed = 1.f - 0.05f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		SetViewSize(GetViewSize() * ZoomSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		SetViewSize(GetViewSize() / ZoomSpeed);
	}
	const float Speed = GetViewSize() * 0.015f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		mVelocity.x -= Speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		mVelocity.x += Speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		mVelocity.y -= Speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		mVelocity.y += Speed;
	}


	mView.setCenter(mView.getCenter() + mVelocity);
	
}

void Camera::Zoom(int aDelta) {
	SetViewSize(GetViewSize() * std::powf(0.95f, aDelta));
}
