#include "grid.h"

using namespace std;

class PLAY{
private:
	int player1=1;
	int player2=-1;
	int nbr_p;
	grid game;
public:
	//construct
	PLAY(int n_p);

	//destructor
	~PLAY();

	//algorithms to decide the column to input
	int smart_dec(int player);

	//add token by the player
	bool add_token(int player,int col);

	//judge whether the player has won the game with the latest added token
	bool judge_winner(int player, int col);

	void start_game();
};
