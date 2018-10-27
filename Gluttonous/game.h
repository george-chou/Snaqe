#pragma once
class game
{
public:
	game();
	~game();

	void Direction(int);
	int InitDir(QPoint);
	void CreateFood(void);
	bool MissionImpossible(int);
	QPoint RandCoord(void);

private:

	bool Covered(QPoint);

};

