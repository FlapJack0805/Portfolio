#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include "Player.hpp"
#include "Card.hpp"
#include "Pack.hpp"
#include <cmath>

using namespace std;

bool error_msg(int argc, char *argv[]) {
    string error_message;
    error_message = "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
      "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
      "NAME4 TYPE4";

         if (argc != 12) {
        cout << error_message << endl;
        return true;
    }
    else if (atoi(argv[3]) < 1 || atoi(argv[3]) > 100) {
        cout << error_message << endl;
        return true;
    }
    else if (string(argv[2]) != "shuffle" && 
    string(argv[2]) != "noshuffle") {
        cout << error_message << endl;
        return true;
    }
    else if (string(argv[5]) != "Simple" && 
    string(argv[5]) != "Human") {
        cout << error_message << endl;
        return true;
    }
    else if (string(argv[7]) != "Simple" &&
    string(argv[7]) != "Human") {
        cout << error_message << endl;
        return true;
    }
    else if (string(argv[9]) != "Simple" &&
    string(argv[9]) != "Human") {
        cout << error_message << endl;
        return true;
    }
    else if (string(argv[11]) != "Simple" &&
    string(argv[11]) != "Human") {
        cout << error_message << endl;
        return true;
    }
    else
    {
        return false;
    }

}

class Game {
    public:

    //constructor
    Game(string names[], istream& packtype, 
    string shuffletype, int winningpoints)
         : players({Player_factory(names[0], names[1]), 
         Player_factory(names[2], names[3]), 
         Player_factory(names[4], names[5]), 
         Player_factory(names[6], names[7])}), 
         scoretowin(winningpoints), team1score(0), team2score(0), 
         shuffle(shuffletype), pack_of_cards(packtype) {}

    void shuffledeck() {
        pack_of_cards.shuffle();
    }

    //function to delete players
    void delete_all_players() {

    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
    }

    void deal_and_upcard(int dealerposition) {
        pack_of_cards.reset();
        int cardsdealt = 1;
        int playerreceiving = dealerposition + 1;

        //dealing out the first batch of cards

        for (int i = 0; i < 4; i++) {
            if (playerreceiving > 3) {playerreceiving = 0;}

            if (cardsdealt % 2 == 1) {
                players[playerreceiving]->add_card(pack_of_cards.deal_one());
                players[playerreceiving]->add_card(pack_of_cards.deal_one());
                players[playerreceiving]->add_card(pack_of_cards.deal_one());
            }
            if (cardsdealt % 2 == 0) {
                players[playerreceiving]->add_card(pack_of_cards.deal_one());
                players[playerreceiving]->add_card(pack_of_cards.deal_one());
            }

            playerreceiving++;
            cardsdealt++;
        }

        //dealing out second batch
        cardsdealt = 1;

        for (int i = 0; i < 4; i++) {
            if (pack_of_cards.empty()) {
                pack_of_cards.reset();
        }
            if (playerreceiving > 3) {playerreceiving = 0;}

            if (cardsdealt % 2 == 1) {
                players[playerreceiving]->add_card(pack_of_cards.deal_one());
                players[playerreceiving]->add_card(pack_of_cards.deal_one());

            }
            if (cardsdealt % 2 == 0) {
                players[playerreceiving]->add_card(pack_of_cards.deal_one());
                players[playerreceiving]->add_card(pack_of_cards.deal_one());
                players[playerreceiving]->add_card(pack_of_cards.deal_one());
            }

        playerreceiving++;
        cardsdealt++;
    }

        if (pack_of_cards.empty()) {
            pack_of_cards.reset();
        }

        //get and print the upcard;
        upcard = pack_of_cards.deal_one();
        cout << upcard.get_rank() << " of " << 
        upcard.get_suit() << " turned up" << endl;
    }

    Suit maketrump() {
    int dealertruth = 0;

    // Single loop iterating 8 times (equivalent to 2 rounds of 4 players)
    for (int i = 0; i < 8; i++) {
        int j = i % 4;  // Player index based on the current iteration
        int round = ceil((i + 1) / 4.0);  // Determine which round we are in (1 or 2)

        // Check if the current player is the dealer
        if ((dealerposition + 1 + j) % 4 == dealerposition) {
            dealertruth = 1;
        } else {
            dealertruth = 0;
        }

        // Call make_trump and check if the player orders up the trump
        if (players[(dealerposition + 1 + j) % 4]->make_trump(upcard, 
        dealertruth, round, orderupsuit)) {
            if (round == 1) {
                cout << players[(dealerposition + 1 + j) % 4]->get_name() 
                << " orders up " << orderupsuit << endl << endl;
                players[(dealerposition)]->add_and_discard(upcard);
            }

            // Assign teamthatordered based on the player index
            if ((dealerposition+ 1 + j) % 4 == 0 || (dealerposition + 1 + j) % 4 == 2) {
                teamthatordered = 1;
            } 
            else {
                teamthatordered = 2;
            }

            trump = orderupsuit;
            if (round == 2)
            {
                cout << players[(dealerposition + 1 + j) % 4]->get_name() 
                << " orders up " << orderupsuit << endl << endl;
            }
            
            return orderupsuit;
        } else {
            cout << players[(dealerposition + 1 + j) % 4]->get_name() 
            << " passes" << endl;
        }
    }

    if (dealerposition == 0 || dealerposition == 2) 
    {
    teamthatordered = 1;
    } 
    else 
    {
    teamthatordered = 2;
    }

    return orderupsuit;
}


    void tricktaking() {
        Card playedcard;
        Card ledcard;
        Card highestcard;
        int eldestplayer = dealerposition + 1;
        if (eldestplayer > 3) {eldestplayer = 0;}
        int winneroftrick = eldestplayer;
        int highestplayer = eldestplayer;

        team1trick = 0;
        team2trick = 0;

        
        //loop through 5 times
        for (int i = 0; i < 5; i++) {
            ledcard = players[winneroftrick]->lead_card(trump);

            highestcard = ledcard;
            
            cout << ledcard.get_rank() << " of " << ledcard.get_suit() << " led by "
                 << players[winneroftrick]->get_name() << endl;

            for (int j = 1; j < 4; j++) {
                playedcard = players[((winneroftrick) + j) % 4]->
                play_card(ledcard, trump);
                cout << playedcard.get_rank() << " of " <<
                 playedcard.get_suit() << " played by " <<
                     players[((winneroftrick) + j) % 4]->get_name() << endl;

                if (Card_less(highestcard, playedcard, ledcard, trump))
                {
                    highestcard = playedcard;
                    
                    highestplayer = (winneroftrick + j) % 4;
                }
                
            //assign trick points
            }
            if (highestplayer == 1 || highestplayer == 3) {
                team2trick++;
            }
            else {
                team1trick++;
            }
            
            winneroftrick = highestplayer;
            cout << players[winneroftrick]->get_name() << 
            " takes the trick" << endl << endl;

        }
    }


    void scoring() {
        if (team1trick < team2trick) // If team 2 wins
        { 
            cout << players[1]->get_name() << " and " << 
            players[3]->get_name() << " win the hand" << endl;

            if (teamthatordered == 1) {
                team2score += 2;
                cout << "euchred!" << endl;
            }

            if (teamthatordered == 2) {
                if (team2trick == 5) {
                    team2score += 2;
                    cout << "march!" << endl;
                }
                else {
                    team2score++;
                }
            }
        }
        else {
            cout << players[0]->get_name() << " and " << 
            players[2]->get_name() << " win the hand" << endl;

            if (teamthatordered == 2) {
                team1score += 2;
                cout << "euchred!" << endl;
            }
            if (teamthatordered == 1) {
                if (team1trick == 5) {
                    team1score += 2;
                    cout << "march!" << endl;
                }
                else {
                    team1score++;
                }
            }
        }

        cout << players[0]->get_name() << " and " << 
        players[2]->get_name() << " have " << team1score << " points" << endl;
        cout << players[1]->get_name() << " and " << 
        players[3]->get_name() << " have " << team2score << " points" << endl << endl;
    }

    void rungame() {
        int hand = 0;

        //loop to play the game
        while (team1score < scoretowin && team2score < scoretowin) {

            dealerposition = hand % 4;

            cout << "Hand " <<  hand << endl;
            cout << players[dealerposition]->get_name() << " deals" << endl;

            if (shuffle == "shuffle") {
                shuffledeck();
            }
            //call all of our necessary functions
            deal_and_upcard(dealerposition);
            trump = maketrump();
            tricktaking();
            scoring();
            hand++;

        }
        //print out the winners once loop ends
        if (team1score > team2score) {
            cout << players[0]->get_name() << " and " << 
            players[2]->get_name() << " win!" << endl;
        }
        else if (team2score > team1score) 
        {
            cout << players[1]->get_name() << " and " << 
            players[3]->get_name() << " win!" << endl;
        }
        
    }

    private:
    vector<Player*> players; // 0 and 2 are team 1, 1 and 3 are team 2
    int scoretowin;
    int team1score;
    int team2score;
    Suit trump;
    string shuffle;
    Suit orderupsuit;
    int dealerposition;
    int team1trick = 0;
    int team2trick = 0;
    int teamthatordered;
    Card upcard;
    Pack pack_of_cards;
};

int main(int argc, char *argv[]) {
    //error messages
    
    if (error_msg(argc, argv)) {return -1;}

    for (int i = 0; i < 12; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;


    //file checking
    string file = argv[1];

    ifstream fin(file);

    if(!fin.is_open()) {
        cout << "Error opening " << file << endl;
        return 1;
    }

    string names[8] = {argv[4], argv[5], argv[6], 
    argv[7], argv[8], argv[9], argv[10], argv[11]};
    Game euchre(names, fin, argv[2], atoi(argv[3]));

    euchre.rungame();

    fin.close();
    
    euchre.delete_all_players();
}