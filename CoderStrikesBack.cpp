#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

enum Turns { FirstTurn, OtherTurns };

class Point
{
public:
	void setX(int x);
	int getX();
	void setY(int x);
	int getY();
	Point(int x, int y);
	Point();

	bool operator == (Point p)
	{
		return (x == p.getX()) && (y == p.getY());
	}

	bool operator != (Point p)
	{
		return (x != p.getX()) || (y != p.getY());
	}

private:
	int x;
	int y;
};

Point::Point(int x, int y) : x(x), y(y) {}

Point::Point()
{
	x = 0;
	y = 0;
}

void Point::setX(int x)
{
	this->x = x;
}
int  Point::getX()
{
	return x;
}
void Point::setY(int y)
{
	this->y = y;
}
int  Point::getY()
{
	return y;
}



//Class made to contain info about checkpoints, allowing me to store the checkpoints seen
class Checkpoint
{
public:
	Checkpoint(int x, int y);
	Point GetPosition();
	void SetPosition(int x, int y);
	void SetDist(int value);
	int GetDist();

	bool operator == (Checkpoint c)
	{
		return (position == c.GetPosition()) && (position == c.GetPosition());
	}

	bool operator != (Checkpoint c)
	{
		return (position != c.GetPosition()) || (position != c.GetPosition());
	}
	int Dist(Checkpoint previousPoint);

private:
	Point position;
	int dist;
};

Checkpoint::Checkpoint(int x, int y)
{
	position = Point(x, y);
}

Point Checkpoint::GetPosition()
{
	return position;
}

void Checkpoint::SetPosition(int x, int y)
{
	position.setX(x);
	position.setY(y);
}

void Checkpoint::SetDist(int value)
{
	dist = value;
}

int Checkpoint::GetDist()
{
	return dist;
}

int Checkpoint::Dist(Checkpoint previousPoint)
{
	return (sqrt(pow(position.getX() - previousPoint.position.getX(), 2) + pow(position.getY() - previousPoint.position.getY(), 2)));
}

class Pod
{
public:
	void SetCoordinates(int x, int y);
	Point GetCoordinates();
	void SetOldCoordinates(int x, int y);
	Point GetOldCoordinates();
	Point GetPointToGo();
	void SetPointToGo(int x, int y);
	int GetSpeed();
	void Aim(Checkpoint currentCheckpoint, Checkpoint nextCheckpoint, int nextCheckpointDist);
	void InitPod(int x, int y);
	Pod();

private:
	Point coordinates;
	Point oldCoordinates;
	Point pointToGo;
	int speed;
};

Pod::Pod()
{
	speed = 0;
}

void Pod::SetCoordinates(int x, int y) {
	coordinates.setX(x);
	coordinates.setY(y);
}

Point Pod::GetCoordinates() {
	return coordinates;
}

void Pod::SetOldCoordinates(int x, int y) {
	oldCoordinates.setX(x);
	oldCoordinates.setY(y);
}

Point Pod::GetOldCoordinates() {
	return oldCoordinates;
}

Point Pod::GetPointToGo() {
	return pointToGo;
}

void Pod::SetPointToGo(int x, int y)
{
	pointToGo.setX(x);
	pointToGo.setY(y);
}

int Pod::GetSpeed() {
	return speed;
}

void Pod::InitPod(int x, int y)
{
	oldCoordinates.setX(coordinates.getX());
	oldCoordinates.setY(coordinates.getY());
	coordinates.setX(x);
	coordinates.setY(y);
	speed = sqrt(pow((coordinates.getX() - oldCoordinates.getX()), 2) + pow((coordinates.getY() - oldCoordinates.getY()), 2));
}

// Aims for the point that reates the shortest turn using alkashi
void Pod::Aim(Checkpoint nextCheckpoint, Checkpoint furtherCheckpoint, int nextCheckpointDist)
{
	double furtherCheckpointDist = sqrt(pow(coordinates.getX() - furtherCheckpoint.GetPosition().getX(), 2) + pow(coordinates.getY() - furtherCheckpoint.GetPosition().getY(), 2));
	double cosAngle = (pow(furtherCheckpoint.GetDist(), 2) + pow(nextCheckpointDist, 2) - pow(furtherCheckpointDist, 2)) / (2 * furtherCheckpoint.GetDist() * nextCheckpointDist);
	cerr << cosAngle << endl;
	//Taking into account the truncatures due to int usage
	if (cosAngle > 1)
	{
		cosAngle = 1;
	}
	else if (cosAngle < -1)
	{
		cosAngle = -1;
	}
	//Taking into account the rotation's direction to decide the angle's sign
	double desiredAngle = 0;
	if (coordinates.getX() < nextCheckpoint.GetPosition().getX() && furtherCheckpoint.GetPosition().getX() > nextCheckpoint.GetPosition().getX())
	{
		if (coordinates.getY() < furtherCheckpoint.GetPosition().getY())
		{
			desiredAngle = -(acos(cosAngle)) / 2;
		}
		else {
			desiredAngle = (acos(cosAngle)) / 2;
		}
	}
	else if (coordinates.getX() > nextCheckpoint.GetPosition().getX() && furtherCheckpoint.GetPosition().getX() < nextCheckpoint.GetPosition().getX())
	{
		if (coordinates.getY() > furtherCheckpoint.GetPosition().getY())
		{
			desiredAngle = -(acos(cosAngle)) / 2;
		}
		else {
			desiredAngle = (acos(cosAngle)) / 2;
		}
	}
	else if (coordinates.getX() > nextCheckpoint.GetPosition().getX() && coordinates.getX() < furtherCheckpoint.GetPosition().getX())
	{
		desiredAngle = (acos(cosAngle)) / 2;
	}
	else if (coordinates.getX() < nextCheckpoint.GetPosition().getX() && coordinates.getX() > furtherCheckpoint.GetPosition().getX())
	{
		desiredAngle = (acos(cosAngle)) / 2;
	}
	else {
		cerr << "coucou" << endl;
		desiredAngle = -(acos(cosAngle)) / 2;
	}
	//desiredAngle = -(acos(cosAngle)) / 2;
	cerr << "desired angle " << desiredAngle << endl;
	// rotation of the current pod possition around the next checkpoint axis to find the vector of the bisector using rotation matrix
	vector<int> podVector{ coordinates.getX() - nextCheckpoint.GetPosition().getX(), coordinates.getY() - nextCheckpoint.GetPosition().getY() };
	cerr << "pod Vector" << podVector[0] << " " << podVector[1] << endl;
	//normalized vetor of the desired direction
	vector<double> desiredVector
	{
		(podVector[0] * cos(desiredAngle) - podVector[1] * sin(desiredAngle)) / nextCheckpointDist,
		(podVector[0] * sin(desiredAngle) + podVector[1] * cos(desiredAngle)) / nextCheckpointDist
	};
	cerr << "desired Vector" << desiredVector[0] << " " << desiredVector[1] << endl;
	int desiredX = desiredVector[0] * 500 + nextCheckpoint.GetPosition().getX();
	int desiredY = desiredVector[1] * 500 + nextCheckpoint.GetPosition().getY();
	cerr << "desiredX " << desiredX << " desiredY " << desiredY << endl;
	SetPointToGo(desiredX, desiredY);
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
	bool boostAvailable = true;


	Turns turn = FirstTurn;
	vector<Checkpoint> checkpoints;
	Pod myPod;
	Pod ennemyPod;

	int maxDist = 0;

	int nextCheckpointID = 0;
	int furtherCheckpointID = 0;

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
		bool boostOn = false;
		int thrust = 100;

		myPod.InitPod(x, y);
		myPod.SetPointToGo(nextCheckpointX, nextCheckpointY);
		ennemyPod.InitPod(opponentX, opponentY);

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;
		cerr << nextCheckpointAngle << " " << nextCheckpointDist << endl;
		cerr << maxDist << endl;
		//Creates a vector containing every checkpoint
		Checkpoint nextCheckpoint(nextCheckpointX, nextCheckpointY);
		if (turn == FirstTurn)
		{
			if (checkpoints.size() == 0)
			{
				nextCheckpoint.SetDist(0);
				checkpoints.push_back(nextCheckpoint);
				cerr << checkpoints.size() << endl;

			}
			else
			{
				if (checkpoints.back() != nextCheckpoint) {
					int dist = nextCheckpoint.Dist(checkpoints.back());
					cerr << dist << endl;
					nextCheckpoint.SetDist(dist);
					checkpoints.push_back(nextCheckpoint);
					cerr << "adding element" << endl;
					if (checkpoints.front() == nextCheckpoint) {
						turn = OtherTurns;
						checkpoints.erase(checkpoints.begin());
						nextCheckpointID = checkpoints.size() - 1;
						for (int i = 0; i < checkpoints.size(); i++) {
							if (checkpoints[i].GetDist() > maxDist) {
								maxDist = checkpoints[i].GetDist();
							}
						}
					}
				}
			}
		}

		//Where to go?
		if (turn == OtherTurns)
		{
			if (checkpoints[nextCheckpointID] != nextCheckpoint)
			{
				if (nextCheckpointID == checkpoints.size() - 1)
				{
					nextCheckpointID = 0;
					furtherCheckpointID = 1;
				}
				else
				{
					nextCheckpointID++;
					if (furtherCheckpointID == checkpoints.size() - 1) {
						furtherCheckpointID = 0;
					}
					else {
						furtherCheckpointID++;
					}
				}
			}
			cerr << nextCheckpointID << " " << furtherCheckpointID << endl;
			//myPod.Aim(checkpoints[nextCheckpointID], checkpoints[furtherCheckpointID], nextCheckpointDist);  //Line to comment or un comment to modif algorythm
			cerr << "point to go" << myPod.GetPointToGo().getX() << " " << myPod.GetPointToGo().getY() << endl;
		}

		//Should I boost?
		if (turn == OtherTurns && boostAvailable == true
			&& nextCheckpointDist < maxDist + 2000 && nextCheckpointDist > maxDist - 2000
			&& nextCheckpointAngle < 3 && nextCheckpointAngle > -3)
		{
			cerr << "boost" << endl;
			boostAvailable = false;
			boostOn = true;
			cout << nextCheckpointX << " " << nextCheckpointY << " " << "BOOST" << endl;
			continue;
		}

		//How fast?
		if (nextCheckpointDist < 1500)
		{
			thrust = 70;
		}
		if (nextCheckpointDist < 2500)
		{
			//reduction of orbitation
			cerr << thrust << endl;
			thrust *= abs((90 - abs(nextCheckpointAngle)) / (float)90);

			cerr << (float)abs(90 - abs(nextCheckpointAngle)) / 90 << " " << thrust << endl;
		}
		else
		{
			//quicker turn
			if (nextCheckpointAngle > 90 || nextCheckpointAngle < -90)
			{
				thrust = 0;
			}
			else if (nextCheckpointAngle > 70 || nextCheckpointAngle < -70)
			{
				thrust = 50;
			}
		}

		// You have to output the target position
		// followed by the power (0 <= thrust <= 100)
		// i.e.: "x y thrust"

		cout << myPod.GetPointToGo().getX() << " " << myPod.GetPointToGo().getY() << " " << thrust << endl;
	}
}
