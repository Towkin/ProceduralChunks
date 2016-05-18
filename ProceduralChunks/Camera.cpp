#include "Camera.h"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <math.h>

Camera::Camera(const sf::Window* aWindow) :
	mWindow(aWindow),
	mView(),
	mViewSize(100000.f)
{
	UpdateAspectRatio();
	mView.setCenter(50000.f, 50000.f);
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
	mViewSize = aNewViewSize;
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
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		SetViewSize(GetViewSize() * 0.95f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		SetViewSize(GetViewSize() * 1.033f);
	}

	mView.setCenter(mView.getCenter() + mVelocity);
	
}

void Camera::Zoom(int aDelta) {
	SetViewSize(GetViewSize() * std::powf(0.95f, aDelta));
}
