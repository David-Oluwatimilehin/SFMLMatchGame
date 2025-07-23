#include "Game.h"
#include "Tile.h"

#include "GridManager.h"
#include "SoundManager.h"
#include "StateMachine.h"
#include "HUDManager.h"
#include "MenuState.h"

#include <iostream>
#include <sstream>
#include <iomanip>




void Game::Start(unsigned int width, unsigned int height, const char* windowTitle, unsigned int rows, unsigned int columns)
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

	std::cout << "Starting a game with a " << rows << "x" << columns<<"\n";
    std::cout << "\n";
    
    m_rows = rows;
    m_columns = columns;

    m_screenWidth = width;
    m_screenHeight = height;

    m_window = new sf::RenderWindow(sf::VideoMode({ width, height }), windowTitle, sf::Style::Default, sf::State::Windowed, settings);
    const bool baseVisibility = true;
    
    m_hudManager = new HUDManager(m_screenWidth, m_screenHeight, "Assets/Fonts/SolerinMagica.otf", sf::Color::White);
    m_hudManager->CreateText(sf::Color::White, { 0 , 0 }, "Timer: ", "timerText", 24, baseVisibility);
    m_hudManager->CreateText(sf::Color::White, { float(m_screenWidth / 8) * 5 - 5, float(m_screenHeight / 10) * 7 }, "Longest Combo", "longComboText", 20, baseVisibility);
    m_hudManager->CreateText(sf::Color::White, { float(m_screenWidth / 8) - float(m_screenWidth / 8), float(m_screenHeight / 10) * 7 }, "Current Combo", "currComboText", 20, baseVisibility);

    m_hudManager->CreateText(sf::Color::White, { float(m_screenWidth / 12) - 10.0f, float(m_screenHeight / 2) - 25.0f }, "Well Done! Your highest combo was ", "congratMsg", 20, false);
    m_hudManager->CreateText(sf::Color::White, { float(m_screenWidth / 2) - 80.0f, float(m_screenHeight / 2) + 20.0f }, "0", "highScoreMsg", 48, false);
    //m_hudManager->CreateText(sf::Color::White, { float(width / 8) * 7 + 10, float(height / 10) * 7 + 40 }, "0", "longComboAmount", 50); // The record combo
    //m_hudManager->CreateText(sf::Color::White, { float(width / 8) - float(width / 8), float(height / 10) * 7 + 40 }, "0", "currComboAmount", 50);
}

void Game::Run(unsigned int width, unsigned int height, unsigned int frameRate, const char* windowTitle, unsigned int rows, unsigned int columns)
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    m_window = new sf::RenderWindow(sf::VideoMode({ width, height }), windowTitle, sf::Style::Default, sf::State::Windowed, settings);
    m_window->setFramerateLimit(frameRate);

    m_machine.Run(StateMachine::build<MenuState>(m_machine, *m_window, true));

    while (m_machine.IsRunning()) {
        m_machine.NextState();
        m_machine.Update();
        m_machine.Draw();
    }


}

void Game::Update(unsigned int fpsLimit)
{

    // Sets the Games Framerate
	m_window->setFramerateLimit(fpsLimit);

    constexpr float tileSize = 50.0f;
    constexpr float tileSpacing = 5.0f;
    
    const float startX = (float)m_screenWidth / 10; /* (m_window->getSize().x - (m_rows * (tileSize + tileSpacing))) / 2.f;*/
    const float startY = (float)m_screenHeight / 4; /*(m_window->getSize().y - (m_columns * (tileSize + tileSpacing))) / 2.f;*/
    
    sf::Vector2f initPos{ startX,startY };
    m_gridManager = new GridManager(m_rows, m_columns, initPos, tileSize, 5.0f);
    m_gridManager->GeneratePatterns();
    
    sf::Texture texture;
    if (!texture.loadFromFile("Assets/Background/menuBackground.jpg")) {
        return;
    }
    //texture.setSmooth(true);
    texture.setRepeated(true);

    sf::Vector2f targetSize( m_screenWidth, m_screenHeight);
    sf::Sprite background(texture, sf::IntRect({ 0, 0 }, { m_screenWidth, m_screenHeight }));

    //background.setScale(sf::Vector2f(
    //    targetSize.x / background.getLocalBounds().size.x,
    //    targetSize.y / background.getLocalBounds().size.y));
    //background.set

    Tile* selectedTile = nullptr;
    sf::Vector2i selectedCoords = { -1,-1 };
    
    SoundManager soundManager;
    soundManager.LoadSound("Assets/Sound/click.wav", "clickSound", 1.0, 50.0f);
    soundManager.LoadMusic("Assets/Music/Bossanova.mp3", "backgroundMusic", 1.0f, 50.0f, true);
    soundManager.LoadMusic("Assets/Music/Reload.mp3", "victoryMusic", 1.0f, 50.0f, true);
    //soundManager.PlaySong("backgroundMusic");
    
    sf::Clock clock;
    sf::Time currentTime;
    sf::Time elapsedBaseTime = sf::Time::Zero; // To store time when paused
    
    bool isRunning = true;
    std::string stopWatch;

    while (m_window->isOpen())
    {
        while (const std::optional event = m_window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window->close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    std::cout << "Window Closed\n";
                    m_window->close();
                }

                if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                    std::cout << "GAME WON\n";
                    
                   
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
                        //soundManager.PlaySound("clickSound");

                        selectedTile = clickedTile;
                        selectedTile->isHighlighted = true;
                        selectedCoords = { rows, cols };

                    }
                    else { // This is the second tile, attempt a match


                        Tile* secondTile = clickedTile;
                        sf::Vector2i secondCoords = { rows, cols };

                        if (m_gridManager->ResolveMatches(*selectedTile, *secondTile)) {

                            soundManager.PlaySound("clickSound");
                            // Match was successful. Deselect the first tile
                            selectedTile->isHighlighted = false;
                            m_hudManager->IncrementComboScore(1);
                            m_hudManager->UpdateLongComboScore(m_hudManager->GetComboScore());
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
                            m_hudManager->UpdateComboScore(0);
                            // There were no matches
                            secondTile->isHighlighted = false;
                            secondTile = nullptr;

                            selectedTile->isHighlighted = false;
                            selectedTile = nullptr;
                        }

                    }
                    // Checks the Win Condition
                    if (m_gridManager->HasWonGame()) {
                        isRunning = false;
                        soundManager.StopSong("backgroundMusic");
                        soundManager.PlaySong("victoryMusic");
                        
                        m_hudManager->SetAllTextInvisible();

                        m_hudManager->SetNewVisibility("congratMsg", true);
                        m_hudManager->UpdateText("highScoreMsg", stopWatch);
                        m_hudManager->SetNewVisibility("highScoreMsg", true);
                    }
                
                }
            }

        }

        
        if (isRunning) {
            currentTime = elapsedBaseTime + clock.getElapsedTime();
        }
        else {
            currentTime = elapsedBaseTime;
        }
        
        int minutes = static_cast<int>(currentTime.asSeconds() / 60);
        int seconds = static_cast<int>(currentTime.asSeconds()) % 60;
        
        std::stringstream ss;
        ss  << std::setfill('0') << std::setw(2) << minutes << ":"
            << std::setfill('0') << std::setw(2) << seconds;
        
        stopWatch = ss.str();
        m_hudManager->UpdateTimerAmount("Timer: " + stopWatch);
        
        
        
        m_window->clear(sf::Color(9,9,10));
        
        m_window->draw(background);
        m_gridManager->DrawTiles(*m_window);
        m_hudManager->DisplayElements(*m_window);        
        //m_hudManager->SetNewVisibility();// SHOW VICTORY MESSAGE WITH TIME COMPLETED
        

        m_window->display();

    }

    End(); // Delete Window
}


void Game::End()
{
    delete m_hudManager;
    delete m_gridManager;
	delete m_window;
}
