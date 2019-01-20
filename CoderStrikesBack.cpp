#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum Turns{FirstTurn, OtherTurns};
//Class made to contain info about checkpoints, allowing me to store the checkpoints seen
class Checkpoint
{
public:
	Checkpoint(int x, int y);
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();
	bool Compare(int x, int y);
private:
	int xCoordinate;
	int yCoordinate;
};

Checkpoint::Checkpoint(int x, int y) : xCoordinate(x), yCoordinate(y) {}

void Checkpoint::setX(int x)
{
	xCoordinate = x;
}
int  Checkpoint::getX()
{
	return xCoordinate;
}
void Checkpoint::setY(int y)
{
	yCoordinate = y;
}
int  Checkpoint::getY()
{
	return yCoordinate;
}

bool Checkpoint::Compare(int x, int y)
{
	if (x == xCoordinate && y == yCoordinate)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{

	// game loop
	while (1) {
		int x;
		int y;
		int nextCheckpointX; // x position of the next check point
		int nextCheckpointY; // y position of the next check point
		int nextCheckpointDist; // distance to the next checkpoint
		int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
		cin >> x >> y >> nextCheckpointX >> nextCheckpointY >> nextCheckpointDist >> nextCheckpointAngle; cin.ignore();
		int opponentX;
		int opponentY;
		cin >> opponentX >> opponentY; cin.ignore();
		bool boostAvailable = true;
		bool boostOn = false;
		int thrust;
		Turns turn = FirstTurn;
		vector<Checkpoint> checkpoints;
		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		//Creates a vector containing every checkpoint and it's location
		if (turn = FirstTurn)
		{
			if (checkpoints.size == 0)
			{
				checkpoints.add(new Checkpoint(nextCheckpointX, nextCheckpointY);
			}
			else
			{
				for each (Checkpoint checkpoint in checkpoints)
				{
					exist = false;
					exist = checkpoint.Compare(nextCheckpointX, nextCheckpointY);
					if (exist = true && checkpoint != checkpoints.back)
					{
						turn = OtherTurns;
					}
				}
			}
		}

		if (nextCheckpointDist > 10000 && boostAvailable == true && nextCheckpointAngle < 10 && nextCheckpointAngle > -10)
		{
			boostAvailable = false;
			boostOn = true;
		}

		if (boostOn == true && nextCheckpointDist < 1000)
		{
			boostOn = false;
		}

		if (nextCheckpointAngle > 90 || nextCheckpointAngle < -90)
		{
			thrust = 0;
		}
		else
		{
			thrust = 100;
		}

		// You have to output the target position
		// followed by the power (0 <= thrust <= 100)
		// i.e.: "x y thrust"
		if (boostOn == true)
		{
			cout << nextCheckpointX << " " << nextCheckpointY << " " << "BOOST" << endl;
		}
		else
		{
			cout << nextCheckpointX << " " << nextCheckpointY << " " << thrust << endl;
		}
	}
}
