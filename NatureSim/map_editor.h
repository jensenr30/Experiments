//map editor

void setcell(int x, int y, int data)
{
    cellData[x/CELL_SIZE][y/CELL_SIZE] = data;
}

void deletecell(int x, int y, int data)
{
    cellData[x/CELL_SIZE][y/CELL_SIZE] = 0;
}