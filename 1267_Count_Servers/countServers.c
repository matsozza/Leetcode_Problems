// Solution by Matheus Sozza
https://leetcode.com/problems/count-servers-that-communicate/description
// Tried to solve with minimum memory usage, avoiding to create auxiliary variables or counters. 
// STILL NOT GOOD, TO BE IMPROVED - SOLUTION WORKS BUT IS TOO LONG AND COMPLEX :(

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int countServers(int** grid, int gridSize, int* gridColSize) 
{
    // Accumulate total sum of connections
    int totConn = 0;
    // Sweep all pivots in main diagonal, limited by number of cols
    int idxPivot = 0;
    while(idxPivot<gridSize || idxPivot<gridColSize[MIN(gridSize-1, idxPivot)])
    {
        
        if(idxPivot < gridColSize[MIN(gridSize-1, idxPivot)] || idxPivot < gridSize)
        {
            // Get pivot indices with limitation
            int idxPivotCol = MIN(gridSize-1, idxPivot);
            int idxPivotRow = MIN(gridColSize[MIN(gridSize-1, idxPivot)]-1, idxPivot);
            
            // Sweep cols / horizontally around pivot
            int sumHorzBack1=0, sumHorzFwd1=0;
            int sumHorzBack2=0, sumHorzFwd2=0;
            for(int idxCol = 0; idxCol<gridSize; idxCol++)
            {
                if(idxCol < idxPivotCol)
                {
                    if(grid[idxCol][idxPivotRow] == 1)
                    {
                        sumHorzBack1+=1;
                    } 
                    else if(grid[idxCol][idxPivotRow] == 2)
                    {
                        sumHorzBack2+=1;
                    }
                }
                else if(idxCol > idxPivotCol)
                {
                    if(grid[idxCol][idxPivotRow]==1)
                    {
                        sumHorzFwd1+=1;
                    }                    
                }
            }

            // Sweep rows / vertically around pivot
            int sumVertBack1=0, sumVertFwd1=0;
            int sumVertBack2=0, sumVertFwd2=0;
            for(int idxRow = 0; idxRow<gridColSize[MIN(gridSize-1, idxPivot)]; idxRow++)
            {
                if(idxRow < idxPivotRow)
                {
                    if(grid[idxPivotCol][idxRow]==1)
                    {
                        sumVertBack1+=1;
                    }
                    else if(grid[idxPivotCol][idxRow]==2)
                    {
                        sumVertBack2+=1;
                    }
                }
                else if(idxRow > idxPivotRow)
                {
                    if(grid[idxPivotCol][idxRow]==1)
                    {
                        sumVertFwd1+=1;
                    }                   
                }
            }

            // Process values and add to total count
            if(grid[idxPivotCol][idxPivotRow]==1 && 
            (sumVertFwd1>0 || sumVertBack1>0 || sumHorzFwd1>0 || sumHorzBack1>0 || 
            sumVertFwd2>0 || sumVertBack2>0 || sumHorzFwd2>0 || sumHorzBack2>0))
            {
                
                totConn += 1+(sumVertFwd1+sumHorzFwd1+sumVertBack1+sumHorzBack1);
                // Transform all the Fwd and Back '1s' in '2s'.
                for(int idxCol=0; idxCol< gridSize; idxCol++) 
                {
                    grid[idxCol][idxPivotRow] += grid[idxCol][idxPivotRow] == 1? 1 : 0;
                }
                
                // Transform all the Fwd and Back '1s' in '2s'.
                for(int idxRow=0; idxRow< gridColSize[idxPivotCol]; idxRow++)
                {
                    grid[idxPivotCol][idxRow] += grid[idxPivotCol][idxRow] == 1? 1 : 0;
                } 
            }
            else if(grid[idxPivotCol][idxPivotRow]==2 && 
            (sumVertFwd1>0 || sumVertBack1>0 || sumHorzFwd1>0 || sumHorzBack1>0 || 
            sumVertFwd2>0 || sumVertBack2>0 || sumHorzFwd2>0 || sumHorzBack2>0))
            {
                totConn += (sumVertFwd1+sumHorzFwd1+sumVertBack1+sumHorzBack1);
                // Transform all the Fwd and Back '1s' in '2s'.
                for(int idxCol=0; idxCol< gridSize; idxCol++) 
                {
                    grid[idxCol][idxPivotRow] += grid[idxCol][idxPivotRow] == 1? 1 : 0;
                }
                
                // Transform all the Fwd and Back '1s' in '2s'.
                for(int idxRow=0; idxRow< gridColSize[idxPivotCol]; idxRow++)
                {
                    grid[idxPivotCol][idxRow] += grid[idxPivotCol][idxRow] == 1? 1 : 0;
                } 

            }
            else if(grid[idxPivotCol][idxPivotRow]==0)
            {
                if(sumHorzFwd1 + sumHorzFwd2 + sumHorzBack1 + sumHorzBack2 > 1)
                {
                    totConn+=sumHorzFwd1 + sumHorzBack1;
                    // Transform all the Fwd and Back '1s' in '2s'.
                    for(int idxCol=0; idxCol< gridSize; idxCol++) 
                    {
                        grid[idxCol][idxPivotRow] += grid[idxCol][idxPivotRow] == 1? 1 : 0;
                    }
                } 

                if(sumVertFwd1 + sumVertFwd2 + sumVertBack1 + sumVertBack2 > 1) 
                {
                    totConn+=sumVertFwd1 + sumVertBack1;
                    // Transform all the Fwd and Back '1s' in '2s'.
                    for(int idxRow=0; idxRow<gridColSize[idxPivotCol]; idxRow++)
                    {
                        grid[idxPivotCol][idxRow] += grid[idxPivotCol][idxRow] == 1? 1 : 0;
                    } 
                }
            }
        }
        idxPivot++;
    }
    return totConn;