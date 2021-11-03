// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    
    Player * bob=Player_factory("Bob","Human");
    ASSERT_EQUAL("Bob", bob->get_name());
                                
    delete alice;
    delete bob;
}

TEST(test_player_add_lead_card){
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_EIGHT, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    
    Card upcard=Card(Card::RANK_TWO,Card::SUIT_DIAMONDS);
    string trump;
    ASSERT_TRUE(alice->make_trump(upcard, true, 1, trump));
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
    
    Card upcard1=Card(Card::RANK_TWO,Card::SUIT_HEARTS);
    string trump2;
    ASSERT_FALSE(alice->make_trump(upcard1, true, 1, trump2));
    ASSERT_TRUE(alice->make_trump(upcard1,false,2,trump2));
    ASSERT_EQUAL(trump2, Card::SUIT_DIAMONDS);
    
    Card upcard3=Card(Card::RANK_TEN,Card::SUIT_CLUBS);
    string trump3;
    ASSERT_FALSE(alice->make_trump(upcard3, false, 2, trump3));
    ASSERT_TRUE(alice->make_trump(upcard3, true, 2, trump3));
    ASSERT_EQUAL(trump3, Card::SUIT_SPADES);
    
    delete alice;
}

//TEST(test_player_add_lead_card_human){
//    Player * bob = Player_factory("Bob", "Human");
//    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
//    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
//    bob->add_card(Card(Card::RANK_EIGHT, Card::SUIT_SPADES));
//    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
//    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
//    Card upcard=Card(Card::RANK_TWO,Card::SUIT_DIAMONDS);
//    string trump;
//    ASSERT_TRUE(bob->make_trump(upcard, true, 1, trump));
//    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
//
//    Card upcard1=Card(Card::RANK_TEN,Card::SUIT_CLUBS);
//    string trump1;
//    ASSERT_FALSE(bob->make_trump(upcard1, true, 1, trump1));
//
//    delete bob;
//
//}

TEST(test_player_add_discard_lead){
    //has non-trump cards
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_EIGHT, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    Card upcard=Card(Card::RANK_TWO,Card::SUIT_DIAMONDS);
    alice->add_and_discard(upcard);
    //9 spade is discarded
    ASSERT_TRUE((alice->lead_card(Card::SUIT_SPADES))==Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    
    
   //all cards are trump cards
    Player * amy = Player_factory("Amy", "Simple");
    amy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    amy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    amy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    amy->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    amy->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    //upcard is right bower
    Card upcard1=Card(Card::RANK_JACK,Card::SUIT_DIAMONDS);
    amy->add_and_discard(upcard1);
    //9 diamonds is discarded
    ASSERT_TRUE((amy->play_card((Card(Card::RANK_TWO,Card::SUIT_CLUBS)),Card::SUIT_DIAMONDS))==Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    
    //upcard is normal trump card
    Player * helen = Player_factory("helen", "Simple");
    helen->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    helen->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    helen->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    helen->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    helen->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    Card upcard2=Card(Card::RANK_EIGHT,Card::SUIT_DIAMONDS);
    helen->add_and_discard(upcard2);
    //king hearts is discarded
    ASSERT_TRUE((helen->play_card((Card(Card::RANK_TWO,Card::SUIT_CLUBS)),Card::SUIT_DIAMONDS))==Card(Card::RANK_EIGHT, Card::SUIT_DIAMONDS));
    
    delete alice;
    delete amy;
    delete helen;
}
// Add more tests here

//TEST(test_player_add_discard_lead_play_card_human){
//    Player * alice = Player_factory("Alice", "Human");
//    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
//    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
//    alice->add_card(Card(Card::RANK_EIGHT, Card::SUIT_DIAMONDS));
//    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
//    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
//    Card upcard=Card(Card::RANK_TWO,Card::SUIT_DIAMONDS);
//    alice->add_and_discard(upcard);
//    //9 spade is discarded
//    ASSERT_TRUE((alice->lead_card(Card::SUIT_SPADES))==Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
//
//    Player * bob = Player_factory("Bob", "Human");
//    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
//    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
//    bob->add_card(Card(Card::RANK_EIGHT, Card::SUIT_SPADES));
//    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
//    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
//    Card upcard1=Card(Card::RANK_EIGHT,Card::SUIT_DIAMONDS);
//    bob->add_and_discard(upcard1);
//    //8 spades is discarded
//    ASSERT_TRUE((bob->play_card((Card(Card::RANK_TWO,Card::SUIT_CLUBS)),Card::SUIT_DIAMONDS))==Card(Card::RANK_NINE, Card::SUIT_SPADES));
//
//    delete bob;
//
//}
TEST(test_player_lead){
    //has only one card
    Player* bob=Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    ASSERT_TRUE((bob->lead_card(Card::SUIT_SPADES))==Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    ASSERT_TRUE((bob->lead_card(Card::SUIT_CLUBS))==Card(Card::RANK_NINE, Card::SUIT_SPADES));
    
    //has non-trump cards
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_EIGHT, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    ASSERT_TRUE((alice->lead_card(Card::SUIT_SPADES))==Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    
    //has only trump cards
    Player * amy = Player_factory("Amy", "Simple");
    amy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    amy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    amy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    amy->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    amy->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    ASSERT_TRUE((amy->lead_card(Card::SUIT_DIAMONDS))==Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    
    delete bob;
    delete alice;
    delete amy;
}

TEST(test_player_play){
    //has only one card
    Player* bob=Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    ASSERT_TRUE((bob->play_card(Card(Card::RANK_TWO,Card::SUIT_SPADES),Card::SUIT_SPADES))==Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    ASSERT_TRUE((bob->play_card(Card(Card::RANK_TWO,Card::SUIT_CLUBS),Card::SUIT_DIAMONDS))==Card(Card::RANK_NINE, Card::SUIT_SPADES));
    
    //led suit!=trump suit
    
    //have led suit cards, play the highest led suit card
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_EIGHT, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    ASSERT_TRUE((alice->play_card(Card(Card::RANK_TWO,Card::SUIT_DIAMONDS),Card::SUIT_HEARTS))==Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    
    //have no led suit cards, play the lowest card
    Player * amy = Player_factory("Amy", "Simple");
    amy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    amy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    amy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    amy->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    amy->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    ASSERT_TRUE((amy->play_card(Card(Card::RANK_TWO,Card::SUIT_CLUBS),Card::SUIT_DIAMONDS))==Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    
    Player * helen = Player_factory("helen", "Simple");
    helen->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    helen->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    helen->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    helen->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    helen->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    Card upcard2=Card(Card::RANK_EIGHT,Card::SUIT_DIAMONDS);
    ASSERT_TRUE((helen->play_card(Card(Card::RANK_TWO,Card::SUIT_CLUBS),Card::SUIT_HEARTS))==Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    helen->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    Card res=helen->play_card(Card(Card::RANK_TWO,Card::SUIT_CLUBS),Card::SUIT_DIAMONDS);
    ASSERT_TRUE(res==Card(Card::RANK_KING, Card::SUIT_HEARTS));
    delete bob;
    delete alice;
    delete amy;
    delete helen;
}
TEST_MAIN()
