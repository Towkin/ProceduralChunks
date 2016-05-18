#pragma once
#include "SFML/Graphics/View.hpp"
#include "SFML/Window/Window.hpp"

class Camera {
private:

	const sf::Window* mWindow;
	sf::View mView;

	sf::Vector2f mVelocity;
	sf::Vector2f mAspectRatio;
	float mViewSize;

	bool mMouseIsHeld;
	sf::Vector2i mMouseHeldLocation;

protected:
	void UpdateAspectRatio();
	const sf::Vector2f& GetAspectRatio() const { return mAspectRatio; }

	void SetViewSize(float aNewViewSize);
	float GetViewSize() const { return mViewSize; }

public:
	Camera() = delete;
	Camera(const sf::Window* aWindow);
	~Camera();

	virtual void Update();
	const sf::View& GetView() const { return mView; }

	void Zoom(int aDelta);
};

