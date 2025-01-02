#include "Player.hpp"
using namespace std;
#include <algorithm>
  
class Simple : public Player {
    public:

    const std::string & get_name() const override {
        return name;
    }

    Simple(const string &inname) {
        name = inname;
    }
    

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        players_hand.push_back(c);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                            int round, Suit &order_up_suit) const override {
                                
                                
        if (round == 1) {
            int numtrumpcards = 0;
            for (int i = 0; i < players_hand.size(); i++) {

                if ((players_hand[i].is_trump(upcard.get_suit()) 
                && players_hand[i].is_face_or_ace())
                    || players_hand[i].is_left_bower(upcard.get_suit())) {
                    numtrumpcards++;
                }
            }
            if (numtrumpcards >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            else {
                return false;
            }
        }

        if (round == 2) {
            if(is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }

            for (int i = 0; i < players_hand.size(); i++) {
                if ((players_hand[i].is_trump(Suit_next(upcard.get_suit())) 
                && players_hand[i].is_face_or_ace())
                    || players_hand[i].is_left_bower(Suit_next(upcard.get_suit()))) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
                }
    
            }


        }
        return false;
    }


    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override
    {
        Suit trump = upcard.get_suit();
        Card lowest_card  = players_hand[players_hand.size()-1];
        int lowest_index = players_hand.size()-1;
        for (size_t i=0; i < players_hand.size()-1; i++)
        {
            if (Card_less(players_hand[i], lowest_card, trump)) 
            {
                lowest_card = players_hand[i];
                lowest_index = i;
            }
        }

        players_hand.erase(players_hand.begin() + lowest_index);
        players_hand.push_back(upcard);
        std::sort(players_hand.begin(), players_hand.end());
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump) override
    {
        int trumptrack = 0;
        int eraseindex = 0;
        Card highestcard;

        for (int i = 0; i < players_hand.size(); i++) {
            if (trumptrack == 0) {
                if (!players_hand[i].is_trump(trump))  {
                    highestcard = players_hand[i];
                    eraseindex = i;
                    trumptrack = 1;
                }
            }
            if (!players_hand[i].is_trump(trump) && players_hand[i] > highestcard) {
                eraseindex = i;
                highestcard = players_hand[i];
                
            }
        }
        
        if (trumptrack == 0) {
            for (int i = 0; i < players_hand.size(); i++) {
                if (!Card_less(players_hand[i], highestcard, trump)) {
                    highestcard = players_hand[i];
                    eraseindex = i;
                }
            }
        }
        players_hand.erase(players_hand.begin() + eraseindex);
        std::sort(players_hand.begin(), players_hand.end());
        return highestcard;
    }
        

    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override {
        bool suittruth = false; //initialize

        int index = 0;

        //suittofollow should be suit of led card
        Suit followsuit = led_card.get_suit(trump);
        

        for (int i = 0; i < players_hand.size(); i++)
        {
            if (players_hand[i].get_suit(trump) == followsuit)
            {
                suittruth = true;
                index = i;

                //break loop here if player has the followsuit
                break;
            }
        }

        if (suittruth)
        {
            for (int i = 0; i < players_hand.size(); i++)
            {
                if (Card_less(players_hand[index], players_hand[i], led_card, trump) && 
                    players_hand[i].get_suit(trump) == followsuit)
                {
                    index = i;
                }
            }
           
        }
        else
        {
            index = 0;
            
            for (int i = 0; i < players_hand.size(); i++)
            {
                if (Card_less(players_hand[i], players_hand[index], led_card, trump))
                {
                    index = i;
                }
            }
        }

        //make return card
        Card returned_card = players_hand[index];
        //erase card
        players_hand.erase(players_hand.begin() + index);

        return returned_card;
    }


    private:
        string name;
        vector<Card> players_hand;

};

class Human : public Player {
    public:

    Human(const string &inname) {
            name = inname;
    }

        
    void print_hand() const {
        vector<Card> temphold = players_hand;
        sort(temphold.begin(), temphold.end());

        for (int i = 0; i < temphold.size(); i++) {
            cout << "Human player " << name << "'s hand: "
                << "[" << i << "] " << temphold[i] << '\n';
        }
    }

    const std::string & get_name() const override {
        return name;
    }

    void add_card(const Card &c) override {
        players_hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                            int round, Suit &order_up_suit) const override {
        print_hand();

        string player_decision;
        cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
        cin >> player_decision;

        if (player_decision != "pass") {
            order_up_suit = string_to_suit(player_decision);
            return true;
        }

    return false;
} 
    

    void add_and_discard(const Card &upcard) override
    {
        int card_index;
        std::sort(players_hand.begin(), players_hand.end());


        print_hand();
        players_hand.push_back(upcard);

        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << ", please select a card to discard:\n";
        cout << endl;
        cin >> card_index;

        
        if (card_index == -1) {
            players_hand.pop_back();
        }
        else {
            players_hand.erase(players_hand.begin() + card_index);
        }

        
    }


    Card lead_card(Suit trump) override
    {
        int card_index;
        std::sort(players_hand.begin(), players_hand.end());
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        cin >> card_index;
        Card returned_card = players_hand[card_index];
        players_hand.erase(players_hand.begin() + card_index);
        
        return returned_card;
    }
    
    Card play_card(const Card &led_card, Suit trump) override
    {
        int card_index;
        std::sort(players_hand.begin(), players_hand.end());
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        cin >> card_index;
        Card returned_card = players_hand[card_index];
        players_hand.erase(players_hand.begin() + card_index);
        
        return returned_card;
    }


    private:
        string name;
        vector<Card> players_hand;
};      


//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy)
{
    if (strategy == "Simple")
    {
        return new Simple(name);
    }
    if (strategy == "Human")
    {
        return new Human(name);
    }

    return nullptr;
}
   

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}