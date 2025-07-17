#include "GridManager.h"
#include "Tile.h"
#include <random>

GridManager::GridManager(unsigned int rows, unsigned int columns, sf::Vector2f startPos, const float tileSize, const float tileSpacing) :
    m_rows(rows),
    m_columns(columns),
    m_startPos(startPos),
    m_tileSize(tileSize),
    m_tileSpacing(tileSpacing),
    m_gameBoard(columns,std::vector<Tile*>(rows)),
    m_randEngine(std::random_device()())
{  

};


void GridManager::GeneratePatterns()
{

    const int totalTiles = m_rows * m_columns;
    // Generates Back Numbers List
    std::vector<int> backgroundNum(totalTiles);
    std::vector<int> middleNum(totalTiles);
    std::vector<int> frontNum(totalTiles);

    for (size_t i = 0; i < totalTiles; ++i)
    {
        backgroundNum[i] = i % 4;
        middleNum[i] = i % 4;
        frontNum[i] = i % 4;
    }
    
    std::shuffle(backgroundNum.begin(), backgroundNum.end(), m_randEngine);    
    std::shuffle(middleNum.begin(), middleNum.end(), m_randEngine);
    std::shuffle(frontNum.begin(), frontNum.end(), m_randEngine);

    
    int index = 0;
    // Adds the tiles to the 2d Array 
    for (int i = 0; i < m_columns; ++i)
    {
        for (int j = 0; j < m_rows; ++j)
        {
            index = i * m_rows + j; // Example mapping for column-major storage in flat list
            
            // Create Tile using make_unique and store it
            m_gameBoard[i][j] = new Tile(backgroundNum[index], middleNum[index], frontNum[index], m_tileSize);
        }
    }

}

void GridManager::RemoveTile(int x, int y)
{
    m_gameBoard[x][y] = nullptr;
}

void GridManager::DrawTiles(sf::RenderWindow& window)
{
    for (size_t i = 0; i < m_columns; i++)
    {
        for (size_t j = 0; j < m_rows; j++)
        {
            Tile* currTile = m_gameBoard[i][j];

            float tileX = m_startPos.x + i * (m_tileSize + m_tileSpacing);
            float tileY = m_startPos.y + j * (m_tileSize + m_tileSpacing);

            if (currTile != nullptr) 
            {
                currTile->Draw(window, sf::Vector2f(tileX, tileY));
            }

        }
    }

}

std::pair<int, int> GridManager::GetTileCoords(const sf::Vector2i& mousePos)
{
    int x = -1;
    int y = -1;

    for (int i = 0; i < m_columns; ++i) {
        for (int j = 0; j < m_rows; ++j) {
            float tileX = m_startPos.x + i * (m_tileSize + m_tileSpacing);
            float tileY = m_startPos.y + j * (m_tileSize + m_tileSpacing);

            sf::FloatRect tileBounds(sf::Vector2f(tileX, tileY), sf::Vector2f(m_tileSize, m_tileSize)); // Create a rectangle area representing the tile

            if (tileBounds.contains(static_cast<sf::Vector2f>(mousePos))) {
                x = j;
                y = i;
                if (m_gameBoard[y][x] != nullptr) {
                    return { y, x };

                }
            }
        }
    }
    return { y,x };
}


GridManager::~GridManager()
{

    for (int i = 0; i < m_columns; i++)
    {
        for (int j = 0; j < m_rows; j++)
        {
            m_gameBoard[i][j] = nullptr;
            delete m_gameBoard[i][j];
            
        }
    }
}

bool GridManager::ResolveMatches(Tile& tileOne, Tile& tileTwo)
{
    bool anyMatch = false;

    // Sets the Tiles Invisible if they match
    if (tileOne.GetFrontVis() && tileTwo.GetFrontVis() && tileOne.GetFrontNumber() == tileTwo.GetFrontNumber()) {
        tileOne.SetFrontInvisible(false);
        tileTwo.SetFrontInvisible(false);
        anyMatch = true;
    }
    if (tileOne.GetMiddleVis() && tileTwo.GetMiddleVis() && tileOne.GetMiddleNumber() == tileTwo.GetMiddleNumber()) {
        tileOne.SetMiddleInvisible(false);
        tileTwo.SetMiddleInvisible(false);
        anyMatch = true;
    }
    if (tileOne.GetBackVis() && tileTwo.GetBackVis() && tileOne.GetBackNumber() == tileTwo.GetBackNumber()) {
        tileOne.SetBackInvisible(false);
        tileTwo.SetBackInvisible(false);
        anyMatch = true;
    }

    return anyMatch;
}

bool GridManager::HandleTileSelection(const sf::Vector2i mousePressed)
{
    //std::cout << "The right mouse button was pressed" << std::endl;

    //std::pair<int, int> coords = GetTileCoords(sf::Vector2i(mousePressed.x, mousePressed.y));

    //if (coords.first == -1 && coords.second == -1) {
    //    std::cout << "No tile selected\n";

    //    /*if (selectedTile) {
    //        selectedTile->isHighlighted = false;
    //        selectedTile = nullptr;
    //    }*/
    //    //m_hudManager->UpdateComboScore(0);
    //    return false;
    //}

    //int rows = coords.first;
    //int cols = coords.second;
    //std::cout << "The cell selected is " << rows << " : " << cols << "\n";
    //Tile* clickedTile = m_gameBoard[rows][cols];

    //if (clickedTile == nullptr || clickedTile == selectedTile) { // Clicked an empty space or the same tile
    //    if (selectedTile) clickedTile->isHighlighted = true;
    //    clickedTile = nullptr;
    //    // Skips to the end of function.
    //}

    //if (!selectedTile) { // This is the first tile being selected
    //    //soundManager.PlaySound("clickSound");

    //    selectedTile = clickedTile;
    //    selectedTile->isHighlighted = true;
    //    selectedCoords = { rows, cols };

    //}
    //else { // This is the second tile, attempt a match


    //    Tile* secondTile = clickedTile;
    //    sf::Vector2i secondCoords = { rows, cols };

    //    if (ResolveMatches(*selectedTile, *secondTile)) {

    //        //soundManager.PlaySound("clickSound");
    //        // Match was successful. Deselect the first tile.
    //        selectedTile->isHighlighted = false;
    //        //IncrementComboScore(1);
    //        //m_hudManager->UpdateLongComboScore(m_hudManager->GetComboScore());
    //        // Check if tiles are fully cleared and delete them if they are.
    //        bool secondTileWasCleared = false;

    //        if (selectedTile->IsFullyInvisible()) {
    //            RemoveTile(selectedCoords.x, selectedCoords.y);
    //        }
    //        if (secondTile->IsFullyInvisible()) {
    //            RemoveTile(secondCoords.x, secondCoords.y);
    //            secondTileWasCleared = true;
    //        }

    //        if (!secondTileWasCleared) {
    //            selectedTile = secondTile;
    //            selectedCoords = secondCoords;
    //            selectedTile->isHighlighted = true;
    //        }
    //        else {
    //            // The second tile was cleared, so nothing is selected.
    //            selectedTile->isHighlighted = false;
    //            selectedTile = nullptr;

    //            secondTile->isHighlighted = false;
    //            secondTile = nullptr;
    //        }
    //    }
    //    else {
    //        //m_hudManager->UpdateComboScore(0);
    //        // There were no matches
    //        secondTile->isHighlighted = false;
    //        secondTile = nullptr;

    //        selectedTile->isHighlighted = false;
    //        selectedTile = nullptr;
    //    }

    //}
    return true;
    // Checks the Win Condition
    
}

bool GridManager::HasWonGame()
{
    for (size_t i = 0; i < m_columns; i++) {
        for (size_t j = 0; j < m_rows; j++) {

            if (m_gameBoard[i][j] != nullptr)
                return false;
            
        }
    }
    return true;
}
