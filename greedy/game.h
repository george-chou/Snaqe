#pragma once
class game
{
public:
	game();
	~game();

	void Direction(int v);
	int InitDir(int x, int y);
	void CreateFood(void);
	bool MissionImpossible(int);
	void RandCoord(int *F_x, int *F_y);

private:

	bool Covered(int x, int y);

};

