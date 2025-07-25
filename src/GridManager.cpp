#include "GridManager.h"
#include "Tile.h"
#include <random>

GridManager::GridManager(int rows, int columns, sf::Vector2f startPos, const float tileSize, const float tileSpacing) :
    m_rows(rows),
    m_columns(columns),
    m_startPos(startPos),
    m_tileSize(tileSize),
    m_tileSpacing(tileSpacing),
    m_gameBoard(columns,std::vector<Tile*>(rows)),
    m_randEngine(std::random_device()())
{  
    GeneratePatterns();
};


void GridManager::GeneratePatterns()
{

    const int totalTiles = m_rows * m_columns;
    
    if (totalTiles % 2 != 0) {
        throw std::runtime_error("Error: The game board must have an even number of tiles.");
    }

    const int numPairs = totalTiles / 2;
    const int numPatternValues = 4;

    std::vector<int> basePairedList(totalTiles);
    for (int i = 0; i < numPairs; ++i) {
        int patternValue = i % numPatternValues;

        basePairedList[i * 2] = patternValue; // The first number of the pair
        basePairedList[i * 2 + 1] = patternValue; // The second number of the pair
        
    }

    /*for (size_t i = 0; i < totalTiles - 1; i++) {
        std::cout << basePairedList[i] <<"\n";
    }*/

    std::vector<int> backgroundNum = basePairedList;
    std::vector<int> middleNum = basePairedList;
    std::vector<int> frontNum = basePairedList;

    
    std::shuffle(backgroundNum.begin(), backgroundNum.end(), m_randEngine);
    std::shuffle(middleNum.begin(), middleNum.end(), m_randEngine);
    std::shuffle(frontNum.begin(), frontNum.end(), m_randEngine);

    
    int index = 0;
    for (int i = 0; i < m_columns; i++) {
        for (int j = 0; j < m_rows; j++) {
            index = i * m_rows + j;
            
            m_gameBoard[i][j] = new Tile(backgroundNum[index], middleNum[index], frontNum[index], m_tileSize);
        }
    }

}

void GridManager::RemoveTile(int x, int y)
{
    m_gameBoard[x][y] = nullptr;
    delete m_gameBoard[x][y];
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

    for (int i = 0; i < m_columns; i++) {
        for (int j = 0; j < m_rows; j++) {
            float tileX = m_startPos.x + i * (m_tileSize + m_tileSpacing);
            float tileY = m_startPos.y + j * (m_tileSize + m_tileSpacing);

            sf::FloatRect tileBounds(sf::Vector2f(tileX, tileY), sf::Vector2f(m_tileSize, m_tileSize)); // Create a rectangle area representing the tile
            
            if (tileBounds.contains(static_cast<sf::Vector2f>(mousePos))) 
            {
                x = i;
                y = j;

                if (m_gameBoard[x][y] != nullptr) {
                    return { x,y };
                }
            }
        }
    }
    return { x,y };
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

//bool GridManager::HandleTileSelection(const sf::Vector2i mousePressed)
//{
    

//    std::pair<int, int> firstCoords = GetTileCoords(sf::Vector2i(mousePressed.x, mousePressed.y));
//
//    if (firstCoords.first == -1 && firstCoords.second == -1) { // Clicked out of bounds of tiles
//        std::cout << "No tile selected\n";
//        return false;
//    }
//
//    int rows = firstCoords.first;
//    int cols = firstCoords.second;
//    std::cout << "The cell selected is " << rows << " : " << cols << "\n";
//    Tile* clickedTile = m_gameBoard[rows][cols];
//
//    if (clickedTile == nullptr || clickedTile == selectedTile) { // Clicked an empty space or the same tile
//        std::cout << "Cell selected is null or the same\n";
//        clickedTile = nullptr;
//        return false;
//    }
//
//    if (!selectedTile) { // This is the first tile being selected
//        //soundManager.PlaySound("clickSound");
//
//        selectedTile = clickedTile;
//        selectedTile->isHighlighted = true;
//        firstCoords = { rows, cols };
//
//    }
//    else { // This is the second tile, attempt a match
//
//
//        Tile* secondTile = clickedTile;
//        sf::Vector2i secondCoords = { rows, cols };
//
//        if (ResolveMatches(*selectedTile, *secondTile)) {
//
//            //soundManager.PlaySound("clickSound");
//            // Match was successful. Deselect the first tile.
//            selectedTile->isHighlighted = false;
//            //IncrementComboScore(1);
//            //m_hudManager->UpdateLongComboScore(m_hudManager->GetComboScore());
//            // Check if tiles are fully cleared and delete them if they are.
//            bool secondTileWasCleared = false;
//
//            if (selectedTile->IsFullyInvisible()) {
//                RemoveTile(firstCoords.x, firstCoords.y);
//            }
//            if (secondTile->IsFullyInvisible()) {
//                RemoveTile(secondCoords.x, secondCoords.y);
//                secondTileWasCleared = true;
//            }
//
//            if (!secondTileWasCleared) {
//                selectedTile = secondTile;
//                selectedCoords = secondCoords;
//                selectedTile->isHighlighted = true;
//            }
//            else {
//                // The second tile was cleared, so nothing is selected.
//                selectedTile->isHighlighted = false;
//                selectedTile = nullptr;
//
//                secondTile->isHighlighted = false;
//                secondTile = nullptr;
//            }
//        }
//        else {
//            //m_hudManager->UpdateComboScore(0);
//            // There were no matches
//            secondTile->isHighlighted = false;
//            secondTile = nullptr;
//
//            selectedTile->isHighlighted = false;
//            selectedTile = nullptr;
//        }
//
//    }
//    return true;
//    
//    
//}

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
