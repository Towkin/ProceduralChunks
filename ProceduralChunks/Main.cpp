//#include "ChunkManager.h"
#include "Chunk.h"
#include "ChunkFactory.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>

int main() {
	//ChunkManager Manager;

	Chunk* BaseChunk = ChunkFactory::GenerateChunk(0, 0, 100000.f, 512, 4);


	sf::RenderWindow MainWindow(sf::VideoMode(1024, 800), "Chunks!!!");
	MainWindow.setFramerateLimit(60);
	
	Camera MainCamera(&MainWindow);
	
	sf::Texture mChunkTexture;
	mChunkTexture.loadFromImage(BaseChunk->GetImage());

	sf::RectangleShape MapDraw(sf::Vector2f(BaseChunk->GetSize(), BaseChunk->GetSize()));
	MapDraw.setTexture(&mChunkTexture);

	int MouseDelta = 0;

	while (MainWindow.isOpen()) {
		sf::Event WindowEvent;
		while (MainWindow.pollEvent(WindowEvent)) {
			if (WindowEvent.type == sf::Event::Closed) {
				MainWindow.close();
			}
			if (WindowEvent.type == sf::Event::MouseWheelMoved) {
				MainCamera.Zoom(WindowEvent.mouseWheel.delta);
			}
		}

		MainWindow.clear();
		
		MainCamera.Update();
		MainWindow.setView(MainCamera.GetView());

		BaseChunk->Draw(&MainWindow, sf::FloatRect(MainCamera.GetView().getCenter() - (MainCamera.GetView().getSize() / 2.f), MainCamera.GetView().getSize()));

		//MainWindow.draw(MapDraw);
		//MainWindow.draw(bleh);

		MainWindow.display();
	}

	return 0;
}