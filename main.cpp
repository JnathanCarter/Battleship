/**
	CS 231 Project 2 (Spring 2021)
	main.cpp
	Purpose: The main program file for the "Sea Battle!" game.
	
	@author <insert your name here>
	@version 1.0
*/
//adding comments but this is part 2
#include <ctime>
#include "util.h"
#include "grid.h"

using namespace std;

/* CONSTANT DEFINITIONS */

const int GRID_SIZE = 10;

/* FUNCTION DEFINITIONS */

int main(int argc, char** argv) {
	
	/* Seed pseudorandom number generator */

	srand( time(NULL) );
	
	/* Initialize grids and fleet data */

	const vector<char> ship_type = { 'A', 'B', 'C', 'C', 'S', 'S', 'P', 'P', 'P' };
	const vector<int> ship_size = { 5, 4, 3, 3, 3, 3, 2, 2, 2 };

	Grid primary(GRID_SIZE, "PRIMARY");						/* Primary Grid */
	Grid tracking(GRID_SIZE, "TRACKING");					/* Tracking Grid */
	
	/* Initialize state variables */

	int num_player_ships = ship_type.size();				/* Player's Ship Counter */
	int num_opponent_ships = ship_type.size();				/* Opponent's Ship Counter */

	int player_num = 0;										/* Player ID (1 or 2) */
	int player_first = 0;									/* First Player (1 or 2) */

	bool player_turn = false;								/* "Turn Over" Flag */
	bool game_over = false;									/* "Game Over" Flag */

	char player_input;										/* Holds Player Input */
	char opponent_target;									/* Holds Opponent Target Cell Contents */

	Cell cell;												/* Holds Player's Cell Input */

	/* Print Welcome Banner */

	cout << "Welcome to ...\n\n";
	
	cout << "            _____ _________       ____  ___  ______________    ________\n";
	cout << "           / ___// ____/   |     / __ )/   |/_  __/_  __/ /   / ____/ /\n";
	cout << "           \\__ \\/ __/ / /| |    / __  / /| | / /   / / / /   / __/ / /\n";
	cout << "          ___/ / /___/ ___ |   / /_/ / ___ |/ /   / / / /___/ /___/_/\n";
	cout << "         /____/_____/_/  |_|  /_____/_/  |_/_/   /_/ /_____/_____(_)\n\n\n";
	
	/* Get Player ID */
	
	while ( !player_num ) {
	
		cout << "Will you play as Player (1) or as Player (2)? ";
		player_num = get_int();
		
		if (player_num < 1 || player_num > 2 )
		
			player_num = 0;
		
	}
	
	/* Get First Player */
	
	while ( !player_first ) {
	
		cout << "Which player will take the first turn (1/2)? ";
		player_first = get_int();
		
		if (player_first < 1 || player_first > 2 )
		
			player_first = 0;
		
	}
	
	if ( player_num == player_first ) 
		
		player_turn = true;

	/* Deploy Fleet */

	primary.deploy_fleet(ship_type, ship_size);

	/* MAIN GAME LOOP */

	while ( !game_over ) {

		/* Print Grids */

		cout << '\n';

		primary.print();
		tracking.print();

		/* Print fleet counts for player and opponent */

		cout << "Player: " << num_player_ships << ", Opponent: " << num_opponent_ships << ".  ";

		/* Is it the player's turn? */

		if ( player_turn ) { // INSERT CODE HERE

			/* Prompt the player to enter target coordinates */
			cout<< "Please Choose Your Target ( In Tracking Grid): ";
			
			/* Get coordinates */
			cell = get_cell(10);

			/* Prompt for result */
			cout<< "Was This A (M)iss, A (H)it, Or A (S)ink? ";
			cin>>player_input;
			player_input = toupper(player_input);

			/* Was it a miss?  If so, place a splash mark into the tracking grid cell */
			if (player_input == 'M'){
				tracking.set(cell, '/');
			}

			/* Was it a hit or a sink?  If so, place a bang mark into the tracking grid cell */
			if (player_input == 'H'){
				tracking.set(cell, 'X');
			}

			/* Was it a sink?  If so, decrement the opponent's fleet count */
			if (player_input == 'S'){
				tracking.set(cell, 'X');
				num_opponent_ships= num_opponent_ships - 1;
			}

			/* It is now the opponent's turn */

			player_turn = false;

		} // end if()

		/* Is it the opponent's turn? */

		else { // INSERT CODE HERE

			/* Ask the opponent to select target coordinates */
			cout<<"Ask Opponent For Target :";
			cell = get_cell(10);

			/* Find out what was in the target cell */
			opponent_target = primary.get(cell);

			/* Was the cell occupied (does the cell contain something other than '-' or '/')? */

			/* If so, place a bang mark into the primary grid cell */
			if (opponent_target != '/' && opponent_target != '-'){
				primary.set(cell, 'X');
				/* Create an explosion */
				
				//There are different variations of booms that are commented out but i though would be fun to add :)
				//was having fun with the ascii art lol;
					
				cout << "*    *    *    *    B    O    O    M    *    *    *    *\n";
				/*
				
				cout<<"BBBBBBBBBBBBBBBBB        OOOOOOOOO          OOOOOOOOO     MMMMMMMM               MMMMMMMM\n";
				cout<<"B::::::::::::::::B     OO:::::::::OO      OO:::::::::OO   M:::::::M             M:::::::M\n";
				cout<<"B::::::BBBBBB:::::B  OO:::::::::::::OO  OO:::::::::::::OO M::::::::M           M::::::::M\n";
				cout<<"BB:::::B     B:::::BO:::::::OOO:::::::OO:::::::OOO:::::::OM:::::::::M         M:::::::::M\n";
  				cout<<"B::::B     B:::::BO::::::O   O::::::OO::::::O   O::::::OM::::::::::M       M::::::::::M\n";
  				cout<<"B::::B     B:::::BO:::::O     O:::::OO:::::O     O:::::OM:::::::::::M     M:::::::::::M\n";
  				cout<<"B::::BBBBBB:::::B O:::::O     O:::::OO:::::O     O:::::OM:::::::M::::M   M::::M:::::::M\n";
  				cout<<"B:::::::::::::BB  O:::::O     O:::::OO:::::O     O:::::OM::::::M M::::M M::::M M::::::M\n";
  				cout<<"B::::BBBBBB:::::B O:::::O     O:::::OO:::::O     O:::::OM::::::M  M::::M::::M  M::::::M\n";
  				cout<<"B::::B     B:::::BO:::::O     O:::::OO:::::O     O:::::OM::::::M   M:::::::M   M::::::M\n";
  				cout<<"B::::B     B:::::BO:::::O     O:::::OO:::::O     O:::::OM::::::M    M:::::M    M::::::M\n";
  				cout<<"B::::B     B:::::BO::::::O   O::::::OO::::::O   O::::::OM::::::M     MMMMM     M::::::M\n";
				cout<<"BB:::::BBBBBB::::::BO:::::::OOO:::::::OO:::::::OOO:::::::OM::::::M               M::::::M\n";
				cout<<"B:::::::::::::::::B  OO:::::::::::::OO  OO:::::::::::::OO M::::::M               M::::::M\n";
				cout<<"B::::::::::::::::B     OO:::::::::OO      OO:::::::::OO   M::::::M               M::::::M\n";
				cout<<"BBBBBBBBBBBBBBBBB        OOOOOOOOO          OOOOOOOOO     MMMMMMMM               MMMMMMMM\n";
				
				*/
				
				
				/* Did this hit sink a ship? (ask the player) */
				cout<<"Your Opponent Scored a hit! Did It Sink A Ship (Y/N)";
				cin>>player_input;
				player_input = toupper(player_input);

				/* If so, decrement player's fleet count */
				if (player_input == 'Y'){
					num_player_ships = num_player_ships - 1;
				}
			}
			/* Was the cell empty? */
			else{
				/* If so, place a splash mark into the primary grid cell */
				primary.set(cell, '/');
			}

			/* It is now the player's turn */

			player_turn = true;

		} // end else()

		/* Before starting the next turn, check if the game is over */

		if ( num_player_ships == 0 || num_opponent_ships == 0 )

			game_over = true;

	} // end while()

	/* GAME IS OVER */

	/* Did player win? */

	if ( num_player_ships == 0 )
		cout << "GAME OVER: Your opponent sank your fleet!\n\n";

	/* Did opponent win? */

	else if ( num_opponent_ships == 0 )
		cout << "CONGRATULATIONS!  You sank your opponent's fleet!\n\n";

	/* Print exit message; wait for input */

	cout << "Thanks for playing!  Enter X to exit:";
	cin >> player_input;

	/* EXIT */

	return 0;
	
} // end main()
