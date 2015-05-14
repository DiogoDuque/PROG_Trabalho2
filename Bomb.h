#ifndef _Bomb
#define _Bomb
#include "types.h"
class Bomb
{
public:
	Bomb() {};
	Bomb(PositionChar targetPosition);
	PositionChar getTargetPosition(void) const;
	PositionChar offsettargetposition(void);

	void show() const; // shows the attributes of the bomb (for debugging)
private:
	char targetLine, targetColumn;
};
#endif // !_Bomb
