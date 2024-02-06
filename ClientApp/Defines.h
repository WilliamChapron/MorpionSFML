#pragma once

#define PRINT(x) std::cout << (x) << std::endl;

#define CALCULATE_CELL_SIZE(widthOrHeight, rowOrCol, spacing) static_cast<float>(widthOrHeight - (rowOrCol - 1) * (spacing)) / rowOrCol
#define CALCULATE_MOUSE_TO_INDEX(mousePos, spacing, cellSize) static_cast<int>((mousePos + spacing) / (cellSize + spacing))