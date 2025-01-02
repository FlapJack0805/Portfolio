#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  delete bob;
}

TEST(test_simple_player_play_card2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(JACK, DIAMONDS));

  // Bob plays a card
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    DIAMONDS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));
  delete bob;
}

TEST(test_simple_player_play_card3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(JACK, HEARTS));

  // Bob plays a card
  Card nine_hearts(NINE, HEARTS);
  Card card_played = bob->play_card(
    nine_hearts,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(JACK, HEARTS));
  delete bob;
}

TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}


TEST(simple_lead_card1)
{
  Player * simple = Player_factory("NotRobot", "Simple");
  Card card1(ACE, HEARTS);
  Suit trump = SPADES;
  simple->add_card(card1);
  Card card_played = simple->lead_card(trump);
  ASSERT_EQUAL(card_played, card1);

  delete simple;
}

TEST(simple_lead_card2)
{
  Player * simple = Player_factory("NotRobot", "Simple");
  simple->add_card(Card(NINE, SPADES));
  simple->add_card(Card(TEN, SPADES));
  simple->add_card(Card(QUEEN, SPADES));
  simple->add_card(Card(KING, SPADES));
  simple->add_card(Card(JACK, HEARTS));
  Suit trump = SPADES;
  Card card_played1 = simple->lead_card(trump);
  Card card_played2 = simple->lead_card(trump);
  ASSERT_EQUAL(card_played1, Card(JACK, HEARTS));
  ASSERT_EQUAL(card_played2, Card(KING, SPADES));

  delete simple;
}

TEST(simple_lead_card3)
{
  Player * simple = Player_factory("NotRobot", "Simple");
  simple->add_card(Card(NINE, SPADES));
  simple->add_card(Card(TEN, SPADES));
  simple->add_card(Card(QUEEN, SPADES));
  simple->add_card(Card(KING, SPADES));
  simple->add_card(Card(JACK, CLUBS));
  Suit trump = SPADES;
  Card card_played1 = simple->lead_card(trump);
  Card card_played2 = simple->lead_card(trump);
  ASSERT_EQUAL(card_played1, Card(JACK, CLUBS));
  ASSERT_EQUAL(card_played2, Card(KING, SPADES));

  delete simple;
}

TEST(simple_play_card1)
{
  Player * simple = Player_factory("NotRobot", "Simple");
  simple->add_card(Card(NINE, SPADES));
  simple->add_card(Card(TEN, SPADES));
  simple->add_card(Card(QUEEN, SPADES));
  simple->add_card(Card(KING, SPADES));
  simple->add_card(Card(JACK, CLUBS));
  Suit trump = CLUBS;
  Card card_lead = Card(ACE, SPADES);
  Card card_played1 = simple->play_card(card_lead, trump);
  Card card_played2 = simple->play_card(card_lead, trump);
  ASSERT_EQUAL(card_played1, Card(KING, SPADES));
  ASSERT_EQUAL(card_played2, Card(QUEEN, SPADES));

  delete simple;
}

TEST(simple_play_card2)
{
  Player * simple = Player_factory("NotRobot", "Simple");
  simple->add_card(Card(TEN, CLUBS));
  simple->add_card(Card(TEN, SPADES));
  simple->add_card(Card(JACK, HEARTS));
  simple->add_card(Card(KING, SPADES));
  simple->add_card(Card(QUEEN, HEARTS));
  Suit trump = CLUBS;
  Card card_lead = Card(NINE, DIAMONDS);
  Card card_played1 = simple->play_card(card_lead, trump);
  Card card_played2 = simple->play_card(card_lead, trump);
  ASSERT_EQUAL(card_played1, Card(TEN, SPADES));
  ASSERT_EQUAL(card_played2, Card(JACK, HEARTS));

  delete simple;
}

TEST(test_add_discard) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(JACK, HEARTS));

  bob->add_and_discard(Card(JACK, DIAMONDS));

  Card lead_card = Card(NINE, DIAMONDS);
  Suit trump = DIAMONDS;

  ASSERT_EQUAL(bob->play_card(lead_card, trump), Card(JACK, DIAMONDS));

  delete bob;


}

TEST(human_get_name) {
  Player * alice = Player_factory("Alice", "Human");
  ASSERT_EQUAL(alice->get_name(), "Alice");
  delete alice;
}

TEST(test_simple_player_make_trump2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}



TEST(test_simple_player_make_trump_second_round_not_dealer) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(QUEEN, HEARTS));
    
    // Bob is not the dealer in the second round
    Card upcard(NINE, HEARTS);
    Suit trump;
    bool orderup = bob->make_trump(upcard, false, 2, trump); // Bob is not the dealer

    // Verify Bob's order up and trump suit
    ASSERT_FALSE(orderup);

    delete bob;
}

TEST(test_simple_player_make_trump_second_round_with_no_trump_cards) {
    // Bob's hand with no trump cards
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(TEN, HEARTS));

    // Bob is not the dealer in the second round
    Card upcard(NINE, SPADES);
    Suit trump;
    bool orderup = bob->make_trump(upcard, false, 2, trump); // Bob is not the dealer

    // Verify Bob's order up and trump suit
    ASSERT_FALSE(orderup);

    delete bob;
}

TEST(test_simple_player_make_trump10) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_hearts(NINE, HEARTS);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_hearts,    // Upcard
    true,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, DIAMONDS);

  delete bob;
}

TEST(test_simple_player_make_trump11) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_hearts(NINE, HEARTS);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_hearts,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);

  delete bob;
}

TEST(test_simple_player_make_trump12) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(JACK, CLUBS));
  bob->add_card(Card(TEN, DIAMONDS));

  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(simple_play_card22)
{
  Player * simple = Player_factory("NotRobot", "Simple");
  simple->add_card(Card(NINE, SPADES));
  simple->add_card(Card(TEN, DIAMONDS));
  simple->add_card(Card(ACE, SPADES));
  simple->add_card(Card(KING, SPADES));
  simple->add_card(Card(QUEEN, SPADES));
  Suit trump = HEARTS;
  
  Card card_lead = Card(NINE, DIAMONDS);
  Card card_played1 = simple->play_card(card_lead, trump);
  ASSERT_EQUAL(card_played1, Card(TEN, DIAMONDS));

  delete simple;
}

TEST(test_add_discard20) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(NINE, HEARTS));

  bob->add_and_discard(Card(ACE, SPADES));

  Card lead_card = Card(NINE, DIAMONDS);
  Suit trump = DIAMONDS;

  ASSERT_EQUAL(bob->play_card(lead_card, trump), Card(NINE, SPADES));

  delete bob;
}

TEST(test_add_discard21) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(NINE, HEARTS));

  bob->add_and_discard(Card(ACE, DIAMONDS));

  Card lead_card = Card(NINE, DIAMONDS);
  Suit trump = DIAMONDS;

  ASSERT_EQUAL(bob->play_card(lead_card, trump), Card(ACE, DIAMONDS));

  delete bob;
}

TEST(test_add_discard23) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(NINE, HEARTS));

  bob->add_and_discard(Card(JACK, SPADES));

  Card lead_card = Card(NINE, DIAMONDS);
  Suit trump = SPADES;

  ASSERT_EQUAL(bob->play_card(lead_card, trump), Card(NINE, SPADES));

  delete bob;
}



TEST_MAIN()

