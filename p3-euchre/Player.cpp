//Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;
vector<Card> sort_helper(vector<Card> cards);
//computer-controlled player that uses the basic strategy described earlier.
class Simple: public Player{     public:
        Simple(const string &name):simname(name){}
    
        const string & get_name() const override;
    
        void add_card(const Card &c) override;
    
        bool make_trump(const Card &upcard, bool is_dealer,
                          int round, string &order_up_suit) const override;
    
        void add_and_discard(const Card &upcard) override;

        Card lead_card(const string &trump) override;

        Card play_card(const Card &led_card, const std::string &trump) override;
        
        bool has_trump(const string& trump);
    
        bool has_led(const Card& led_card,const string& trump);
    
    private:
        std::string simname;
        vector<Card> simplehand;
};
//human-controlled player that reads instructions from cin.
class Human: public Player{
    public:
        Human(const string &name):huname(name){
        }
        const string & get_name() const override;

        void add_card(const Card &c) override;

        bool make_trump(const Card &upcard, bool is_dealer,
                          int round, string &order_up_suit) const override;

        void add_and_discard(const Card &upcard) override;

        Card lead_card(const string &trump) override;

        Card play_card(const Card &led_card, const std::string &trump) override;
    
        void print_cards();
        
    private:
        std::string huname;
        vector<Card> humanhand;
};

const string & Simple::get_name() const{
    return simname;}

const string & Human::get_name() const{
    return huname;}

//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand
void Simple::add_card(const Card &c){
    int size=simplehand.size();
    assert(size < MAX_HAND_SIZE);
    simplehand.push_back(c);}

void Human::add_card(const Card &c){
    int size=humanhand.size();
    assert(size < MAX_HAND_SIZE);
    humanhand.push_back(c);}

void Human::print_cards(){
    for (int index=0;index<humanhand.size();++index){
        cout<<"Human player "<<huname<<"'s hand: "
        <<"["<<index<<"] "<<humanhand[index]<<endl;}
}

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
bool Simple::make_trump(const Card &upcard, bool is_dealer,
                          int round, string &order_up_suit) const{
    assert(round == 1||round == 2);
    int trumpface=0;
    if(round == 1){
        for(int i = 0; i < simplehand.size(); ++i){
            if(simplehand[i].is_face() &&
               simplehand[i].is_trump(upcard.get_suit())){
                trumpface++;}
        }
        if(trumpface >= 2){
            order_up_suit = upcard.get_suit();
            return true;}
        else {
            return false;}
    } else{
        string newtrump = Suit_next(upcard.get_suit());
        for(int i = 0; i < simplehand.size(); ++i){
            if(simplehand[i].is_face() && simplehand[i].is_trump(newtrump)){
                trumpface++;}
        }
        if(trumpface>=1 || is_dealer){
            order_up_suit = newtrump;
            return true;}
        else{
            return false;}
    }
}

bool Human::make_trump(const Card &upcard, bool is_dealer,
                          int round, string &order_up_suit) const{
    assert(round == 1||round == 2);
    vector<Card>cards=sort_helper(humanhand);
    for (int index=0;index<cards.size();++index){
        cout<<"Human player "<<huname<<"'s hand: "
        <<"["<<index<<"] "<<cards[index]<<endl;
    }
    cout<<"Human player "<<huname
    <<", please enter a suit, or \"pass\":"<<endl;
    string plrchoice;
    cin>>plrchoice;
    assert(plrchoice == "Spades" ||plrchoice == "Hearts" ||
           plrchoice == "Clubs" ||plrchoice == "Diamonds" ||
           plrchoice == "pass" );
    if(plrchoice!="pass"){
        order_up_suit = plrchoice;
        return true;}
    else{
        return false;}
}

//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
void Simple::add_and_discard(const Card &upcard){
    int size=simplehand.size();
    assert(size>=1);
    sort(simplehand.begin(), simplehand.end());
    //case:non-trump cards existed in hand
    for(int index=0;index<simplehand.size();++index){
        if (!simplehand[index].is_trump(upcard.get_suit())){
            simplehand.erase(simplehand.begin()+index);
            simplehand.push_back(upcard);
            return;}
    }
    //case:all cards are trump card (upcard is right bower;
    //upcard is a regular trump card
    if (upcard.is_right_bower(upcard.get_suit())){
        for(int index=0;index<simplehand.size();++index){
            if(!simplehand[index].is_left_bower(upcard.get_suit())){
                simplehand.erase(simplehand.begin()+index);
                simplehand.push_back(upcard);
                return;}
        }
    }
    else{
        for(int index=0;index<simplehand.size();++index){
            if(Card_less(simplehand[index],upcard,upcard.get_suit())){
                simplehand.erase(simplehand.begin()+index);
                simplehand.push_back(upcard);
                return;}
            }
    }
}

void Human::add_and_discard(const Card &upcard){
    int size=humanhand.size();
    assert(size >= 1);
    sort(humanhand.begin(),humanhand.end());
    for (int index=0;index<humanhand.size();++index){
        cout<<"Human player "<<huname<<"'s hand: "
        <<"["<<index<<"] "<<humanhand[index]<<endl;
    }
    
    cout<<"Discard upcard: [-1]"<<endl;
    int userchoice;
    cout<<"Human player "<<huname
    <<", please select a card to discard:"<<endl;
    cin>>userchoice;
    if(userchoice == -1){
        return;
    } else{
        humanhand.erase(humanhand.begin()+userchoice);
        humanhand.push_back(upcard);
    }
}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card Simple::lead_card(const string &trump){
    int size=simplehand.size();
    assert(size >= 1);
    assert(trump == "Spades"||trump == "Hearts"||
           trump == "Clubs"||trump == "Diamonds");
    Card result;
    //only has one card, lead it
    if (simplehand.size()==1){
        result=simplehand[0];
        simplehand.erase(simplehand.begin());
        return result;}
    
    sort(simplehand.begin(),simplehand.end());
    // has non-trump cards, lead the highest
    for (int index=simplehand.size()-1;index>=0;--index){
        if (!simplehand[index].is_trump(trump)){
            result=simplehand[index];
            simplehand.erase(simplehand.begin()+index);
            return result;}
    }
    // have only trump cards, play the highest
    for (int index=simplehand.size()-1;index>=0;--index){
        for (int index_in=simplehand.size()-1;index_in>=0;--index_in){
            if(index_in==0&&index==0){
                result=simplehand[0];
                simplehand.erase(simplehand.begin());
                return result;}
            
            else if (index==index_in){
                continue;}
            
            else if(index_in==0&&
            !Card_less(simplehand[index],simplehand[index_in],trump)){
                result=simplehand[index];
                simplehand.erase(simplehand.begin()+index);
                return result;}
            
            else if(!Card_less(simplehand[index],simplehand[index_in],trump)){
                continue;}
            
            else{
                break;}
        }
    }
    return result;
}

Card Human::lead_card(const std::string &trump){
    int size=humanhand.size();
    assert(size >= 1);
    assert(trump == "Spades"||trump == "Hearts"||
           trump == "Clubs"||trump == "Diamonds");
    sort(humanhand.begin(), humanhand.end());
    Card result;
    print_cards();
    cout<<"Human player "<<huname<<", please select a card:"<<endl;
    int selected;
    cin>>selected;
    //cout<<humanhand[selected]<<" led by "<<huname<<endl;
    result=humanhand[selected];
    humanhand.erase(humanhand.begin()+selected);
    return result;
}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.

bool Simple::has_trump(const string& trump){
    bool res=false;
    int size=simplehand.size();
    for (int index=0;index<size;++index){
        if (simplehand[index].is_trump(trump)){
            res=true;
            break;}
    }
    return res;
}
bool Simple::has_led(const Card& led_card,const string& trump){
    bool res=false;
    int size=simplehand.size();
    for (int index=0;index<size;++index){
        if(!(simplehand[index].is_left_bower(trump))&&
           simplehand[index].get_suit()==led_card.get_suit()){
            res=true;}
    }
    return res;
}


Card Simple::play_card(const Card &led_card, const string &trump){
    int size=simplehand.size();
    assert(size>= 1);
    assert(trump == "Spades"||trump == "Hearts"||
           trump == "Clubs"||trump == "Diamonds");
    sort(simplehand.begin(), simplehand.end());
    bool if_trump=has_trump(trump);
    bool if_led=has_led(led_card, trump);
    
    Card res;
    int res_index;
    if (led_card.is_trump(trump)&&if_trump){
        res=simplehand[size-1];
        res_index=size-1;
        for (int index=size-1;index>0;--index){
            if(Card_less(res, simplehand[index-1], led_card, trump)){
                res_index=index-1;}
        }
    }
    else if(led_card.is_trump(trump)&&!if_trump){
        res_index=0;}
    
    else if(!led_card.is_trump(trump)&&if_led){
        res=simplehand[size-1];
        res_index=size-1;
        for (int index=size-1;index>=0;--index){
            if((!(simplehand[index].is_left_bower(trump))&&
                simplehand[index].get_suit()==led_card.get_suit())){
                res_index=index;
                break;}
        }
    }
    else if(!led_card.is_trump(trump)&&!if_led){
        res=simplehand[0];
        res_index=0;
        for (int index=0;index<size-1;++index){
            if(!Card_less(res, simplehand[index+1],trump)){
                res=simplehand[index+1];
                res_index=index+1;}
        }
    }
    else{
        res_index=0;}
    res=simplehand[res_index];
    simplehand.erase(simplehand.begin()+res_index);
    return res;
}


Card Human::play_card(const Card &led_card, const std::string &trump){
    assert(trump == "Spades"||trump == "Hearts"||
           trump == "Clubs"||trump == "Diamonds");
    int size=humanhand.size();
    assert(size >= 1);
    sort(humanhand.begin(), humanhand.end());
    Card result;
    print_cards();
    cout<<"Human player "<<huname<<", please select a card:"<<endl;
    int selected;
    cin>>selected;
    result=humanhand[selected];
    humanhand.erase(humanhand.begin()+selected);
    return result;
}

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy){
    if(strategy == "Simple"){
        return new Simple(name);}
    else if(strategy == "Human"){
        return new Human(name);}
    assert(false);
    return nullptr;
}

vector<Card> sort_helper(vector<Card> cards){
    sort(cards.begin(),cards.end());
    return cards;
}

std::ostream & operator<<(std::ostream &os, const Player &p){
    os<<p.get_name();
    return os;
}
