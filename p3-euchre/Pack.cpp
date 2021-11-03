// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.h"
#include <cassert>
using namespace std;

//static const int PACK_SIZE = 24;
//std::array<Card, PACK_SIZE> cards;
//int next; //index of next card to be dealt

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function

Pack::Pack(){
    Card newcard;
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 6; ++j){
            newcard = Card(RANK_NAMES_BY_WEIGHT[j+7],SUIT_NAMES_BY_WEIGHT[i]);
            cards[i*6+j] = newcard;
        }
    }
    next=0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(istream& pack_input){
    string rank;
    string of;
    string suit;
    Card newcard;
    int idx = 0;
    while(pack_input>>rank>>of>>suit){
        newcard = Card(rank,suit);
        cards[idx] = newcard;
        idx++;
    }
    next=0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one(){
    assert(!cards.empty());
    next++;
    return cards[next-1];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset(){
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle(){
    Card tempcards[Pack::PACK_SIZE];
    for(int time = 0; time < 7;++time){
        for(int i=0;i<Pack::PACK_SIZE;++i){
            tempcards[i] = cards[i];
        }
        for(int j=0;j<Pack::PACK_SIZE;++j){
            if(j%2==0){
                cards[j]=tempcards[12+(j/2)];
            } else{
                cards[j]=tempcards[j/2];
            }
        }
    }
    
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const{
    return next>Pack::PACK_SIZE-1;
}
