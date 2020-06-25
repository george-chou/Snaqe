#pragma once
class game
{
public:
	game();
	~game();

	void Direction(int);
	int InitDir(QPoint);
	void CreateFood(void);
	void CreateHead(void);
	bool MissionImpossible(int);
	
private:

	bool Covered(QPoint);
	int randNum(int);
	QPoint randPoint(int); 
};

