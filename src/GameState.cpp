#include "GameState.h"
#include "StateMachine.h"
#include "ELevelData.h"
#include "Tile.h"

#include "GridManager.h"
#include "HUDManager.h"
#include "SoundManager.h"
#include "BackgroundManager.h"

#include <iostream>
#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

GameState::GameState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }
{
    SetupSound();

    InitialiseGrid(sf::Vector2f(window.getSize()));
	
    InitialiseHUD(sf::Vector2f(window.getSize()));
	
    InitialiseBackground();
    
    m_elapsedBaseTime = sf::Time::Zero;

	std::cout << "PlayState Init\n";
}

GameState::~GameState()
{
	delete m_gridManager;
    delete m_soundManager;
    delete m_backgroundManager;
}

void GameState::SetupSound()
{
    m_soundManager = new SoundManager();
    m_soundManager->LoadSound("Assets/Sound/click.wav", "clickSound", 1.0, 50.0f);
    m_soundManager->LoadMusic("Assets/Music/Bossanova.mp3", "backgroundMusic", 1.0f, 50.0f, true);
    m_soundManager->LoadMusic("Assets/Music/Reload.mp3", "victoryMusic", 1.0f, 50.0f, true);
}

void GameState::InitialiseHUD(const sf::Vector2f& window)
{
    m_guiManager = std::make_unique <HUDManager>(window.x, window.y, "Assets/Fonts/SolerinMagica.otf", sf::Color::White);
    m_guiManager->CreateText(sf::Color::White, { 0 , 0 }, "Timer: ", "timerText", 24, baseVisibility);
    m_guiManager->CreateText(sf::Color::White, { window.x / 8 * 5, window.y / 10 * 7 }, "Longest Combo", "longComboText", 20, baseVisibility);
    m_guiManager->CreateText(sf::Color::White, { window.x / 8 - window.x / 8, window.y / 10 * 7 }, "Current Combo", "currComboText", 20, baseVisibility);

    m_guiManager->CreateText(sf::Color::White, { (window.x / 12) - 10.0f, window.y / 2 - 25.0f }, "Well Done! Your highest combo was ", "congratMsg", 20, baseVisibility = false);
    m_guiManager->CreateText(sf::Color::White, { (window.x / 2) - 80.0f, window.y / 2 + 20.0f }, "0", "highScoreMsg", 48, baseVisibility = false);
}

void GameState::InitialiseGrid(const sf::Vector2f& window)
{
    const float tileSize = window.x / 6;
    const float tileSpacing = 5.0f;

    switch (m_machine.GetDifficulty())
    {
    case EDifficultyLevel::eEasy:
        m_gridManager = new GridManager(m_rows = 4, m_cols = 4, sf::Vector2f(window.x / 8, window.y / 5), tileSize, tileSpacing);
        //std::make_unique<GridManager>(m_rows = 4, m_cols = 4, sf::Vector2f((float)window.getSize().x / 10, (float)window.getSize().y / 5), tileSize, tileSpacing);
        break;
    case EDifficultyLevel::eMedium:
        m_gridManager = new GridManager(m_rows = 4, m_cols = 6, sf::Vector2f(window.x / 10, window.y / 5), tileSize, tileSpacing);
        break;
    default:
        break;
    }
}

void GameState::InitialiseBackground()
{
    m_backgroundManager = new BackgroundManager(5.0f, "Assets/Background/Image.jpg");
}

void GameState::Pause()
{
	std::cout << "PlayState Pause\n";
}

void GameState::Resume()
{
	std::cout << "PlayState Resume\n";
}

void GameState::Update()
{
    const sf::Time dt = m_deltaTime.restart();

	while (const std::optional event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_machine.Quit();
			break;
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			switch (keyPressed->scancode)
			{
			case sf::Keyboard::Scancode::Escape:
				m_machine.Quit();
				break;
			
			default:
				break;
			}
		}
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left)
            {
                std::cout << "The right mouse button was pressed\n";

                std::pair<int, int> firstCoords = m_gridManager->GetTileCoords(sf::Vector2i(mouseButtonPressed->position.x, mouseButtonPressed->position.y));

                if (firstCoords.first == -1) { // Clicked out of bounds of tiles
                    std::cout << "No tile selected\n";
                    continue;
                }

                int rows = firstCoords.first;
                int cols = firstCoords.second;
                std::cout << "The cell selected is " << rows << " : " << cols << "\n";
                Tile* clickedTile = m_gridManager->m_gameBoard[rows][cols];

                if (clickedTile == nullptr || clickedTile == selectedTile) { // Clicked an empty space or the same tile
                    std::cout << "Cell selected is null or the same\n";
                    clickedTile = nullptr;
                    continue;
                }

                if (!selectedTile) { // This is the first tile being selected
                    //m_soundManager->PlaySound("clickSound");

                    selectedTile = clickedTile;
                    selectedTile->isHighlighted = true;
                    selectedCoords = { rows, cols };

                }
                else { // This is the second tile, attempt a match


                    Tile* secondTile = clickedTile;
                    sf::Vector2i secondCoords = { rows, cols };

                    if (m_gridManager->ResolveMatches(*selectedTile, *secondTile)) {

                        m_soundManager->PlaySound("clickSound");
                        // Match was successful. Deselect the first tile
                        selectedTile->isHighlighted = false;
                        m_guiManager->IncrementComboScore(1);
                        m_guiManager->UpdateLongComboScore(m_guiManager->GetComboScore());
                        // Check if tiles are fully cleared and delete them if they are
                        bool secondTileWasCleared = false;

                        if (selectedTile->IsFullyInvisible()) {
                            m_gridManager->RemoveTile(selectedCoords.x, selectedCoords.y);
                        }
                        if (secondTile->IsFullyInvisible()) {
                            m_gridManager->RemoveTile(secondCoords.x, secondCoords.y);
                            secondTileWasCleared = true;
                        }

                        if (!secondTileWasCleared) {
                            selectedTile = secondTile;
                            selectedCoords = secondCoords;
                            selectedTile->isHighlighted = true;
                        }
                        else {
                            // The second tile was cleared, so nothing is selected
                            selectedTile->isHighlighted = false;
                            selectedTile = nullptr;

                            secondTile->isHighlighted = false;
                            secondTile = nullptr;
                        }
                    }
                    else {
                        m_guiManager->UpdateComboScore(0);
                        // There were no matches
                        secondTile->isHighlighted = false;
                        secondTile = nullptr;

                        selectedTile->isHighlighted = false;
                        selectedTile = nullptr;
                    }

                }
            }
        }
	}

    m_backgroundManager->ScrollingBackground(dt);

    // --- Timer Logic (remains the same) ---
    if (m_machine.IsRunning()) {
        m_currentTime = m_elapsedBaseTime + m_clock.getElapsedTime();
    }
    else {
        m_currentTime = m_elapsedBaseTime;
    }

    int minutes = static_cast<int>(m_currentTime.asSeconds() / 60);
    int seconds = static_cast<int>(m_currentTime.asSeconds()) % 60;

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << seconds;

    const std::string timerText = ss.str();
    m_guiManager->UpdateTimerAmount("Timer: " + timerText);

}

void GameState::Draw()
{
	m_window.clear(sf::Color(9, 9, 10));

    
    m_backgroundManager->Draw(m_window);

	m_guiManager->DisplayElements(m_window);
	m_gridManager->DrawTiles(m_window);

	m_window.display();

}
