#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor)
{
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_card1)
{
    Card card;
    ASSERT_EQUAL(TWO, card.get_rank());
    ASSERT_EQUAL(SPADES, card.get_suit());
}

/*
TEST(test_card2)
{
    Card card(TWO, SPADES);
    ASSERT_EQUAL(TWO, card.get_rank());
    ASSERT_EQUAL(SPADES, card.get_suit());
}

TEST(test_card3)
{
    Card card(QUEEN, HEARTS);
    ASSERT_EQUAL(QUEEN, card.get_rank());
    ASSERT_EQUAL(HEARTS, card.get_suit());
}


TEST(test_card4)
{
    Card card(TEN, SPADES);
    ASSERT_EQUAL(TEN, card.get_rank());
    ASSERT_EQUAL(SPADES, card.get_suit());
}
*/
TEST(test_get_rank1)
{
    Card card(KING, SPADES);
    ASSERT_EQUAL(KING, card.get_rank());
}

TEST(test_get_rank2)
{
    Card card(NINE, CLUBS);
    ASSERT_EQUAL(NINE, card.get_rank());
}

TEST(test_get_suit1)
{
    Card card(KING, SPADES);
    ASSERT_EQUAL(SPADES, card.get_suit());
}


TEST(test_get_suit2)
{
    Card card(NINE, CLUBS);
    ASSERT_EQUAL(CLUBS, card.get_suit());
}

TEST(test_get_suit3)
{
    Card card(JACK, SPADES);
    ASSERT_EQUAL(CLUBS, card.get_suit(CLUBS));
}

TEST(test_get_suit4)
{
    Card card(JACK, HEARTS);
    ASSERT_EQUAL(HEARTS, card.get_suit(HEARTS));
}

TEST(test_get_suit5)
{
    Card card(TEN, CLUBS);
    ASSERT_EQUAL(CLUBS, card.get_suit(HEARTS));
}

TEST(test_get_suit6)
{
    Card card(JACK, HEARTS);
    ASSERT_EQUAL(HEARTS, card.get_suit(CLUBS));
}

TEST(test_is_face_or_ace1)
{
    Card card(JACK, CLUBS);
    ASSERT_EQUAL(true, card.is_face_or_ace());
}

TEST(test_is_face_or_ace2)
{
    Card card(TEN, HEARTS);
    ASSERT_EQUAL(false, card.is_face_or_ace());
}

TEST(test_is_face_or_ace3)
{
    Card card(ACE, SPADES);
    ASSERT_EQUAL(true, card.is_face_or_ace());
}

TEST(test_is_right_bower1)
{
    Card card(JACK, DIAMONDS);
    ASSERT_EQUAL(false, card.is_right_bower(HEARTS));
}

TEST(test_is_right_bower2)
{
    Card card(JACK, SPADES);
    ASSERT_EQUAL(true, card.is_right_bower(SPADES));
}

TEST(test_is_right_bower3)
{
    Card card(ACE, CLUBS);
    ASSERT_EQUAL(false, card.is_right_bower(CLUBS));
}

TEST(test_is_left_bower1)
{
    Card card(JACK, HEARTS);
    ASSERT_EQUAL(true, card.is_left_bower(DIAMONDS));
}

/*
TEST(test_is_left_bower2)
{
    Card card(JACK, DIAMONDS);
    ASSERT_EQUAL(true, card.is_left_bower(HEARTS));
}

TEST(test_is_left_bower3)
{
    Card card(JACK, SPADES);
    ASSERT_EQUAL(true, card.is_left_bower(CLUBS))
}

TEST(test_is_left_bower4)
{
    Card card(JACK, CLUBS);
    ASSERT_EQUAL(false, card.is_left_bower(CLUBS));
}
*/
TEST(test_is_left_bower5)
{
    Card card(NINE, HEARTS);
    ASSERT_EQUAL(false, card.is_left_bower(DIAMONDS));
}

TEST(test_is_trump1)
{
    Card card(TEN, CLUBS);
    ASSERT_EQUAL(true, card.is_trump(CLUBS));
}

TEST(test_is_trump2)
{
    Card card(QUEEN, DIAMONDS);
    ASSERT_EQUAL(false, card.is_trump(SPADES));
}

/*
TEST(test_is_trump3)
{
    Card card(JACK, HEARTS);
    ASSERT_EQUAL(true, card.is_trump(HEARTS));
}

TEST(test_is_trump4)
{
    Card card(JACK, CLUBS);
    ASSERT_EQUAL(true, card.is_trump(SPADES))
}

TEST(test_is_trump5)
{
    Card card(JACK, DIAMONDS);
    ASSERT_EQUAL(false, card.is_trump(SPADES))
}

TEST(test_is_trump6)
{
    Card card(JACK, SPADES);
    ASSERT_EQUAL(true, card.is_trump(CLUBS))
}



TEST(test_greater_than_operator1)
{
    Card card1(KING, SPADES);
    Card card2(ACE,SPADES);
    ASSERT_TRUE(card2 > card1);
}
*/

TEST(test_greater_than_operator2)
{
    Card card1(NINE, SPADES);
    Card card2(JACK,SPADES);
    ASSERT_TRUE(card2 > card1);
}

TEST(test_greater_than_operator3)
{
    Card card1(QUEEN, SPADES);
    ASSERT_FALSE(card1 > card1);
}

TEST(test_less_than_operator1)
{
    Card card2(KING, SPADES);
    Card card1(ACE,SPADES);
    ASSERT_TRUE(card2 < card1);
}

/*
TEST(test_less_than_operator2)
{
    Card card1(TEN, DIAMONDS);
    Card card2(JACK,SPADES);
    ASSERT_TRUE(card1 < card2);
}

TEST(test_less_than_operator3)
{
    Card card1(ACE, HEARTS);
    ASSERT_FALSE(card1 < card1);
}
*/
TEST(test_greater_than_or_equal_operator1)
{
    Card card1(KING, SPADES);
    Card card2(ACE,SPADES);
    ASSERT_TRUE(card2 >= card1);
}
/*
TEST(test_greater_than_or_equal_operator2)
{
    Card card1(NINE, SPADES);
    Card card2(JACK,SPADES);
    ASSERT_TRUE(card2 >= card1);
}

*/
TEST(test_greater_than_or_equal_operator3)
{
    Card card1(QUEEN, SPADES);
    ASSERT_TRUE(card1 >= card1);
}

TEST(test_less_than_or_equal_operator1)
{
    Card card2(KING, SPADES);
    Card card1(ACE,SPADES);
    ASSERT_TRUE(card2 <= card1);
}

TEST(test_less_than_or_equal_operator2)
{
    Card card1(TEN, DIAMONDS);
    Card card2(JACK,SPADES);
    ASSERT_TRUE(card1 <= card2);
}

TEST(test_less_than_or_equal_operator3)
{
    Card card1(ACE, HEARTS);
    ASSERT_TRUE(card1 <= card1);
}

TEST(test_equal_to_operator1)
{
    Card card1(QUEEN, CLUBS);
    Card card2(NINE, HEARTS);
    ASSERT_FALSE(card1 == card2);
}

TEST(test_equal_to_operator2)
{
    Card card1(ACE, SPADES);
    Card card2(ACE, SPADES);
    ASSERT_TRUE(card1 == card2)
}

TEST(test_not_equal_to_operator1)
{
    Card card1(QUEEN, CLUBS);
    Card card2(NINE, HEARTS);
    ASSERT_TRUE(card1 != card2);
}


TEST(test_not_equal_to_operator2)
{
    Card card1(ACE, SPADES);
    Card card2(ACE, SPADES);
    ASSERT_FALSE(card1 != card2)
}

TEST(test_suit_next1)
{
    Suit suit(CLUBS);
    ASSERT_EQUAL(Suit_next(suit), SPADES);
}

TEST(test_suit_next2)
{
    Suit suit(SPADES);
    ASSERT_EQUAL(Suit_next(suit), CLUBS);
}

TEST(test_suit_next3)
{
    Suit suit(DIAMONDS);
    ASSERT_EQUAL(Suit_next(suit), HEARTS);
}

TEST(test_suit_next4)
{
    Suit suit(HEARTS);
    ASSERT_EQUAL(Suit_next(suit), DIAMONDS);
}

TEST(test_card_less)
{
    Card card1(ACE, SPADES);
    Card card2(JACK, HEARTS);
    Suit trump = CLUBS;
    ASSERT_FALSE(Card_less(card1, card2, trump));
}

TEST(test_card_less2)
{
    Card card1(JACK, SPADES);
    Card card2(JACK, CLUBS);
    Suit trump = CLUBS;
    ASSERT_TRUE(Card_less(card1, card2, trump));
}

TEST(test_card_less3)
{
    Card card1(JACK, DIAMONDS);
    Card card2(ACE, HEARTS);
    Suit trump = HEARTS;
    ASSERT_FALSE(Card_less(card1, card2, trump));
}

TEST(test_card_less4)
{
    Card card1(JACK, SPADES);
    Card card2(JACK, CLUBS);
    Suit trump = CLUBS;
    ASSERT_TRUE(Card_less(card1, card2, trump));
}

TEST(test_card_less_with_lead1)
{
    Card card1(ACE, HEARTS);
    Card card2(NINE, SPADES);
    Suit trump = SPADES;
    Card lead_card(KING, SPADES);
    ASSERT_TRUE(Card_less(card1, card2, lead_card, trump));
}

TEST(test_card_less_with_lead2)
{
    Card card1(JACK, SPADES);
    Card card2(JACK, CLUBS);
    Suit trump = CLUBS;
    Card lead_card(QUEEN, DIAMONDS);
    ASSERT_TRUE(Card_less(card1, card2, lead_card, trump));
}

TEST(test_card_less_with_lead3)
{
    Card card1(KING, HEARTS);
    Card card2(QUEEN, HEARTS);
    Suit trump = CLUBS;
    Card lead_card(KING, SPADES);
    ASSERT_FALSE(Card_less(card1, card2, lead_card, trump));
}

TEST(test_suit_next_full_cycle) {
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
}

TEST(test_right_bower_greater_than_left_bower) {
    Card card1(JACK, SPADES);  // Right bower
    Card card2(JACK, CLUBS);   // Left bower (assuming SPADES is trump)
    ASSERT_FALSE(card1 > card2);
}

TEST(test_left_bower_trump) {
    Card card1(JACK, CLUBS);
    Suit trump = SPADES;
    ASSERT_TRUE(card1.is_trump(trump));
}

TEST(test_comparison_operator_trump) {
    Card card1(JACK, SPADES);
    Card card2(TEN, SPADES);
    ASSERT_TRUE(card1 > card2);
}
TEST(test_card_input_operator) {
    std::istringstream iss("Jack of Hearts");
    Card card;
    iss >> card;
    ASSERT_EQUAL(card.get_rank(), JACK);
    ASSERT_EQUAL(card.get_suit(), HEARTS);
}

TEST(test_card_output_operator) {
    std::ostringstream oss;
    Card card(ACE, DIAMONDS);
    oss << card;
    ASSERT_EQUAL(oss.str(), "Ace of Diamonds");
}

TEST(test_default_constructor) {
    Card card;
    ASSERT_EQUAL(card.get_rank(), TWO);
    ASSERT_EQUAL(card.get_suit(), SPADES);
}


TEST_MAIN()