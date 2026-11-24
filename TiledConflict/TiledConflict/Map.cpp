#include "Map.h"

Map::Map()
{
    Init();
}

Map::~Map()
{
}

void Map::Init()
{
    m_tiles.clear();

    for (int y = 0; y < m_rows; y++)
    {
        for (int x = 0; x < m_columns; x++)
        {
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
    for (Tile& tile : m_tiles)
    {
        tile.Draw();
    }
    DrawMapGrid();
}

Tile* Map::GetTile(int t_x, int t_y)
{
    if (t_x < 0 || t_x >= m_columns || 
        t_y < 0 || t_y >= m_rows)
        
    {
        return nullptr;
    }

    int index = t_y * m_columns + t_x;

    return &m_tiles[index];
}

void Map::SetTileTerrain(int t_x, int t_y, TerrainType t_terrain)
{
    Tile* tile = GetTile(t_x, t_y);

    if (tile != nullptr)
    {
        tile->SetTerrain(t_terrain);
    }
}

void Map::DrawMapGrid()
{
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
