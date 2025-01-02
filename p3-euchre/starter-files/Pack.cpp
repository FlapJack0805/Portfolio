#include "Pack.hpp"
#include <cassert>
#include <iostream>
#include <array>

using namespace std;

// EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on. 
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  // NOTE: The pack is initially full, with no cards dealt.
Pack::Pack()
{
    next = 0;
    for (size_t i=0; i<4; i++)
    {
        for (size_t j=0; j<6; j++)
        {
            Suit suit = Suit(i);
            Rank rank = Rank(j+7);
            cards[i*6+j] = Card(rank, suit);
        }
    }
}

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  // NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(std::istream& pack_input)
{
    next = 0;
    for (int i=0; i<24; i++)
    {
        Suit suit;
        Rank rank;
        string filler;
        pack_input >> rank >> filler >> suit;
        cards[i] = Card(rank, suit);
    }
}


  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one() 
  {
    next++;;
    return cards[next - 1];
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset() 
  {
    next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
 void Pack::shuffle()
{
    int mid = PACK_SIZE/2;
    std::array<Card, PACK_SIZE> new_cards;
    for (int j=0; j<7; j++)
    {
        for (int i=0; i<mid; i++)
        {
            new_cards[2*i] = cards[mid+i]; //Cards from second half of deck
            new_cards[2*i + 1] = cards[i]; //Cards from first half of deck
        }
        cards = new_cards;
    }
}

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const
  {
    if (next == PACK_SIZE) {
        return true;
    }
    return false;
  }