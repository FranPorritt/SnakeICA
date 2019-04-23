#include "Pause.h"

Pause::Pause()
{
}

Pause::~Pause()
{
}

void Pause::Render(sf::RenderWindow& window)
{
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	// Pause Text
	pauseText.setFont(font);
	pauseText.setCharacterSize(85);
	pauseText.setPosition(500, 100);
	pauseText.setString("PAUSED");
	pauseText.setFillColor(fontColor);
	pauseText.setOrigin(floor(pauseText.getLocalBounds().width / 2), floor(pauseText.getLocalBounds().height / 2));

	// Resume Text
	resumeText.setFont(font);
	resumeText.setCharacterSize(fontSize);
	resumeText.setPosition(500, 400);
	resumeText.setString("Esc - Resume");
	resumeText.setFillColor(fontColor);
	resumeText.setOrigin(floor(resumeText.getLocalBounds().width / 2), floor(resumeText.getLocalBounds().height / 2));

	// Quit Text
	quitText.setFont(font);
	quitText.setCharacterSize(fontSize);
	quitText.setPosition(500, 500);
	quitText.setString("Q - Quit");
	quitText.setFillColor(fontColor);
	quitText.setOrigin(floor(quitText.getLocalBounds().width / 2), floor(quitText.getLocalBounds().height / 2));

	window.draw(pauseText);
	window.draw(resumeText);
	window.draw(quitText);
}
