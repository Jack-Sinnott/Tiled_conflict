#include "Map.h"

Map::Map()
{
    Init();
}

// Initial layout and assembly of grid
void Map::Init()
{
    // Clear any junk data before we assign tiles
    m_tiles.clear();

    // Nested loop to create rectangle shape background to tiles. defaulted to grass
    for (int y = 0; y < m_rows; y++)
    {
        for (int x = 0; x < m_columns; x++)
        {
            // Convert grid coordinates to grid coordinates
            float posX = x * m_cellWidth;
            float posY = y * m_cellHeight;

            Rectangle bounds = {
                posX,
                posY,
                m_cellWidth,
                m_cellHeight
            };

            m_tiles.emplace_back(bounds, TerrainType::Grass);
        }
    }

    //Specific tiles that are not grass
    SetTileTerrain(0, 0, TerrainType::Base);
    SetTileTerrain(5, 1, TerrainType::Mountain);
    SetTileTerrain(5, 2, TerrainType::Mountain);
    SetTileTerrain(6, 1, TerrainType::Mountain);
    SetTileTerrain(6, 2, TerrainType::Mountain);
    SetTileTerrain(2, 5, TerrainType::Forest);
    SetTileTerrain(2, 6, TerrainType::Forest);
    SetTileTerrain(3, 5, TerrainType::Forest);
    SetTileTerrain(3, 6, TerrainType::Forest);
    SetTileTerrain(9, 7, TerrainType::Base);
}

void Map::Draw()
{
    for (Tile& t_tile : m_tiles)
    {
        t_tile.Draw();
    }
    DrawMapGrid();
}

// Checks that we are asking for a tile in the grid and then returns that tile if so
Tile* Map::GetTile(int t_x, int t_y)
{
    if (t_x < 0 || t_x >= m_columns || 
        t_y < 0 || t_y >= m_rows)
        
    {
        return nullptr;
    }

    // Changes grid coordinates to a one dimensional vector index
    int t_index = t_y * m_columns + t_x;

    // Return a pointer to the tile at the specified index
    return &m_tiles[t_index];
}

// Allows us to change tiles
void Map::SetTileTerrain(int t_x, int t_y, TerrainType t_terrain)
{
    Tile* t_tile = GetTile(t_x, t_y);

    if (t_tile != nullptr)
    {
        t_tile->SetTerrain(t_terrain);
    }
}

// Draw the grid following column, row structure
void Map::DrawMapGrid()
{
    // We need 11 column lines to make 10 columnns
    for (int x = 0; x <= m_columns; x++)
    {
        int t_posX = x * m_cellWidth;
        DrawLine(t_posX, 0, t_posX, m_screenHeight, GRAY);
    }
    for (int y = 0; y <= m_rows; y++)
    {
        int t_posY = y * m_cellHeight;
        DrawLine(0, t_posY, m_screenWidth, t_posY, GRAY);
    }
}
