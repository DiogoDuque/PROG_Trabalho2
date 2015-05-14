#include "Bomb.h"
#include "types.h"
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

 PositionChar Bomb::getTargetPosition() const
{
	PositionChar targetposition;
	targetposition.lin = targetLine;
	targetposition.col = targetColumn;

	return targetposition;
}

 PositionChar Bomb::offsettargetposition() 
{
	srand((int)time(NULL));
	PositionChar targetposition;
	targetposition.lin =  targetLine - 'A'  + 1;
	targetposition.col =  targetColumn - 'a'+ 1;


	int exatas = { 0 || 5 || 6 || 7 };
	int Norte = 1;
	int Sul = 2;
	int Oeste = 3;
	int Este = 4;

	int coordinates = rand() % 8;
	if (coordinates = exatas)
	{
		return targetposition;
	}
	else
	{
		if (coordinates == Norte)
		{
			targetposition.lin = targetposition.lin - 1;
			return targetposition;
		}
		else if (coordinates == Sul)
		{
			targetposition.lin = targetposition.lin + 1;
			return targetposition;
		}
		else if (coordinates == Este)
		{
			targetposition.col = targetposition.col + 1;
			return targetposition;
		}
		else if (coordinates == Oeste)
		{
			targetposition.col = targetposition.col - 1;
			return targetposition;
		}
	}
}
