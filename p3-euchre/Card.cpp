// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"

// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

using namespace std;

// add your code below

//EFFECTS Initializes Card to the Two of Spades
Card::Card():rank(RANK_TWO),suit(SUIT_SPADES){
}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const string &rank_in, const string &suit_in):rank(rank_in),suit(suit_in){
    assert(rank_in == "Two"||rank_in == "Three"||rank_in == "Four"
    ||rank_in == "Five"||rank_in == "Six"
    ||rank_in == "Seven"||rank_in == "Eight"
    ||rank_in == "Nine"||rank_in == "Ten"||rank_in == "Jack"
    ||rank_in == "Queen"||rank_in == "King"||rank_in == "Ace");
    assert(suit_in == "Spades"|| suit_in == "Hearts"
           ||suit_in == "Clubs"||suit_in == "Diamonds");
}

//EFFECTS Returns the rank
string Card::get_rank() const{
    return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
string Card::get_suit() const{
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
string Card::get_suit(const string &trump) const{
    assert(trump == "Spades"||trump == "Hearts"||
           trump == "Clubs"||trump == "Diamonds");
    if(is_left_bower(trump) ){
        return trump;
    }
    return suit;
}


//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const{
    return rank==Card::RANK_JACK || rank==Card::RANK_QUEEN
    || rank==Card::RANK_KING || rank==Card::RANK_ACE;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const string &trump) const{
    assert(trump == "Spades"||trump == "Hearts"||
           trump == "Clubs"||trump == "Diamonds");
    return rank==Card::RANK_JACK && suit==trump;
}


//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const string &trump) const{
    assert(trump == "Spades"||trump == "Hearts"||
           trump == "Clubs"||trump == "Diamonds");
    return rank==Card::RANK_JACK && suit==Suit_next(trump);
}


//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const string &trump) const{
    assert(trump == "Spades"||trump == "Hearts"||
           trump == "Clubs"||trump == "Diamonds");
    return suit == trump || is_left_bower(trump);
}


static int inuse_rank(const Card &card){
    string card_rank = card.get_rank();
    if(card_rank == Card::RANK_NINE){
        return 9;}
    else if(card_rank == Card::RANK_TEN){
        return 10;}
    else if(card_rank == Card::RANK_JACK){
        return 11;}
    else if(card_rank == Card::RANK_QUEEN){
        return 12;}
    else if(card_rank == Card::RANK_KING){
        return 13;}
    else if(card_rank == Card::RANK_ACE){
        return 14;}
    else{
        return -1;}
}


static int determine_rank(const Card &card){
    string cardrank = card.get_rank();
    if(cardrank == Card::RANK_TWO){
        return 2;}
    else if(cardrank == Card::RANK_THREE){
        return 3;}
    else if(cardrank == Card::RANK_FOUR){
        return 4;}
    else if(cardrank == Card::RANK_FIVE){
        return 5;}
    else if(cardrank == Card::RANK_SIX){
        return 6;}
    else if(cardrank == Card::RANK_SEVEN){
        return 7;}
    else if(cardrank == Card::RANK_EIGHT){
        return 8;}
    else{
        return inuse_rank(card);
    }
    
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs){
    if(lhs.get_rank()!=rhs.get_rank()){
        return determine_rank(lhs)<determine_rank(rhs);
    } else{
        if(lhs.get_suit()==Card::SUIT_DIAMONDS){
            return false;
        } else if(rhs.get_suit()==Card::SUIT_DIAMONDS){
            return true;
        } else if(lhs.get_suit()==Card::SUIT_CLUBS){
            return false;
        } else if(rhs.get_suit()==Card::SUIT_CLUBS){
            return true;
        } else if(lhs.get_suit()==Card::SUIT_HEARTS){
            return false;
        } else if(rhs.get_suit()==Card::SUIT_HEARTS){
            return true;
        } else{
            return false;
        }
    }
    
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs){
    if(lhs.get_rank()!=rhs.get_rank()){
        return determine_rank(lhs)<determine_rank(rhs);
    } else{
        if (lhs.get_suit()==rhs.get_suit()){
            return true;
        }
        else{return (lhs<rhs);}
    }
}
//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs){
    return !(lhs<=rhs);
}


//EFFECTS Returns true if lhs is higher
//value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
    return !(lhs<rhs);
}


//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
    return (!(lhs<rhs))&&(!(lhs>rhs));
}


//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
    return !(lhs==rhs);
}



//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
string Suit_next(const string &suit){
    assert(suit == "Spades"||suit == "Hearts"||
           suit == "Clubs"||suit == "Diamonds");
    string nextsuit;
    if(suit == "Spades"){
        nextsuit = Card::SUIT_CLUBS;
    } else if(suit == "Hearts"){
        nextsuit = Card::SUIT_DIAMONDS;
    } else if(suit == "Clubs"){
        nextsuit = Card::SUIT_SPADES;
    } else{
        nextsuit = Card::SUIT_HEARTS;
    }
    return nextsuit;
}


//EFFECTS Prints Card to stream, for example "Two of Spades"
ostream & operator<<(ostream &os, const Card &card){
    os<<card.get_rank()<<" of "<<card.get_suit();
    return os;
}


//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const string &trump){
    assert(trump == "Spades"||trump == "Hearts"||
           trump == "Clubs"||trump == "Diamonds");
    bool if_righta=a.is_right_bower(trump);
    bool if_lefta=a.is_left_bower((trump));
    bool if_rightb=b.is_right_bower(trump);
    bool if_leftb=b.is_left_bower((trump));
    
    
    
    if(if_righta||(if_lefta&&!if_rightb)){
        return false;
    } else if(if_rightb||
              (!if_righta&&if_leftb)){
        return true;
    } else {
        if(a.is_trump(trump) && !b.is_trump(trump)){
            return false;
        } else if(!a.is_trump(trump) && b.is_trump(trump)){
            return true;
        } else{
            return a<b;
        }
    }
}


//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b,const Card &led_card,const string &trump){
    assert(trump == "Spades"||trump == "Hearts"
           ||trump == "Clubs"||trump == "Diamonds");

    if(led_card.is_trump(trump)){
        return Card_less(a, b, trump);
    }

    if(a.is_right_bower(trump)||
       (a.is_left_bower(trump)&&!b.is_right_bower(trump))){
        return false;
    } else if(b.is_right_bower(trump)||
              (!a.is_right_bower(trump)&&b.is_left_bower(trump))){
        return true;
    } else {
        if(a.is_trump(trump) && !b.is_trump(trump)){
            return false;
        } else if(!a.is_trump(trump) && b.is_trump(trump)){
            return true;
        } else if(a.get_suit()==led_card.get_suit()
                  && b.get_suit()!=led_card.get_suit()){
            return false;
        } else if(a.get_suit()!=led_card.get_suit()
                  && b.get_suit()==led_card.get_suit()){
            return true;
        } else{
            return a<b;
        }
    }
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
