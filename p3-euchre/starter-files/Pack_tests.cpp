#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(test_reset)
{
    Pack pack;
    Card junk_card;
    junk_card = pack.deal_one();
    junk_card = pack.deal_one();
    junk_card = pack.deal_one();
    pack.reset();
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
    
}

TEST(test_deal_one1)
{
    Pack pack;
    Card junk_card;
    junk_card = pack.deal_one();
    junk_card = pack.deal_one();
    junk_card = pack.deal_one();
    Card fourth_card = pack.deal_one();
    ASSERT_EQUAL(pack.get_next(), 4);
    ASSERT_EQUAL(fourth_card.get_rank(), QUEEN);
    ASSERT_EQUAL(fourth_card.get_suit(), SPADES)
    
}

// Add more tests here

TEST_MAIN()
