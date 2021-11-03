// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Card.h"
#include "Pack.h"
#include "Player.h"
#include <fstream>
#include <iostream>
#include <array>
#include <cassert>
using namespace std;

class Game{
    private:
        int numHand;
        Player* dealer;
        Player* eldest;
        Player* player3;
        Player* player4;
        int scorelist[2];
        int orderupteam;
        Pack gamePack;
        int round;
        string trumpsuit;
        int trickscore[2];
        Player* playerlist[4];
        const string playername[4];

    public:
        Game(const string ginput[8],ifstream &pack_in,const int &ptwin):
            numHand(0),
            dealer(Player_factory(ginput[0], ginput[1])),
            eldest(Player_factory(ginput[2], ginput[3])),
            player3(Player_factory(ginput[4], ginput[5])),
            player4(Player_factory(ginput[6], ginput[7])),
            scorelist{0,0}, gamePack(pack_in),round(1), trickscore{0,0},
            playerlist{eldest, player3, player4, dealer},
            playername{ginput[0],ginput[2],ginput[4],ginput[6]}{}
    
        void change_trump_suit(string newsuit){
            trumpsuit = newsuit;}
    
        string get_trump_suit(){
            return trumpsuit;}

        int get_score(int n) const{
            assert(n==0||n==1);
            return scorelist[n];}
    
        string get_player_name(int index) const{
            return playername[index];}

        void initialPack(string shufflestatus){
            if(shufflestatus=="noshuffle"){
                gamePack.reset();
            } else{
                gamePack.reset();
                gamePack.shuffle();}
        }

        string get_dealer_name(){
            return dealer->get_name();}

        Card get_upcard(){
            return gamePack.deal_one();}

        int get_numHand(){
            return numHand;}

        void change_dealer(){
            dealer = playerlist[0];
            eldest = playerlist[1];
            player3 = playerlist[2];
            player4 = playerlist[3];
            playerlist[0]=eldest;
            playerlist[1]=player3;
            playerlist[2]=player4;
            playerlist[3]=dealer;
            
        }
        
        void initialDeal(){
            for(int i=0; i<3;++i){
                eldest->add_card(gamePack.deal_one());}
            for(int i=0; i<2;++i){
                player3->add_card(gamePack.deal_one());}
            for(int i=0; i<3;++i){
                player4->add_card(gamePack.deal_one());}
            for(int i=0; i<2;++i){
                dealer->add_card(gamePack.deal_one());}
            for(int i=0; i<2;++i){
                eldest->add_card(gamePack.deal_one());}
            for(int i=0; i<3;++i){
                player3->add_card(gamePack.deal_one());}
            for(int i=0; i<2;++i){
                player4->add_card(gamePack.deal_one());}
            for(int i=0; i<3;++i){
                dealer->add_card(gamePack.deal_one());}
            
        }

        void count_trick_score(string win_name){
            if(win_name==playerlist[1]->get_name()||
               win_name==playerlist[3]->get_name()){
                trickscore[1-numHand%2]++;
            } else{
                trickscore[numHand%2]++;}
        }

        void order_up_process(const Card in_upcard,int numH,Game playgame){
            bool ordered=false;
            while(playgame.round<=2 && !ordered){
                for(int i=0;i<4;++i){
                if(playgame.round==1 &&
                    playerlist[i]->
                    make_trump(in_upcard,false,playgame.round,trumpsuit)){
                    cout<<playerlist[i]->get_name()
                    <<" orders up " << trumpsuit<<endl;
                    playerlist[3]->add_and_discard(in_upcard);
                    orderupteam = (i+numHand)%2;
                    ordered=true;
                    break;
                } else if(playgame.round==2 &&
                    playerlist[i]->
                    make_trump(in_upcard,false,playgame.round,trumpsuit)){
                    cout<<playerlist[i]->get_name()
                    <<" orders up " << trumpsuit<<endl;
                    orderupteam = (i+numHand)%2;
                    ordered=true;
                    break;}
                cout<<playerlist[i]->get_name()
                    <<" passes"<<endl;
                }
                playgame.round++;}
        }
    
        int largestVal(Card* cardlist[4],const Card& led_card,const string& trump){
            Card result=*cardlist[0];
            int index=0;
            for (int i=1; i<4;++i){
                if(Card_less(result, *cardlist[i],led_card, trump)){
                    result = *cardlist[i];
                    index = i;}
            }
            return index;
        }

        void trick_process(const string& trump,int numH,Game playgame){
            int winnum=0;
            Card* cardplay[4];
            Player* temp[4];
            Player* temp2[4];
            for(int z=0;z<4;++z){
                temp[z]=playerlist[z];
            }

            for(int trick=0;trick<5;++trick){
                for(int y=0;y<4;++y){
                    temp2[y]=temp[(winnum+y)%4];
                }

                for(int j=0;j<4;++j){
                    temp[j]=temp2[j];
                }

                Card a=temp[0]->lead_card(trump);
                cardplay[0]=&a;
                cout<<a<<" led by "<<*temp[0]<<endl;
                Card b=temp[1]->play_card(a,trump);
                cardplay[1]=&b;
                cout<<b<<" played by "<<*temp[1]<<endl;
                Card c=temp[2]->play_card(a,trump);
                cardplay[2]=&c;
                cout<<c<<" played by "<<*temp[2]<<endl;
                Card d=temp[3]->play_card(a,trump);
                cardplay[3]=&d;
                cout<<d<<" played by "<<*temp[3]<<endl;

                winnum = largestVal(cardplay, *cardplay[0], trump);

                cout<<temp[winnum]->get_name()<<" takes the trick"<<endl;
                cout<<endl;
                count_trick_score(temp[winnum]->get_name());
            }
            hand_count();
            trickscore[0] = 0;
            trickscore[1] = 0;
        }

        void hand_count(){
            int winteam = 0;
            if(trickscore[0]>trickscore[1]){
                winteam=0;
            } else{
                winteam=1;
            }
            cout<<playername[1-winteam]<<" and "<<
            playername[3-winteam]<<" win the hand"<<endl;
       
            if(winteam==orderupteam){
            
            if(trickscore[orderupteam]==3||trickscore[orderupteam]==4){
                scorelist[orderupteam]++;
                
                cout<<playername[0]<<" and "<< playername[2]
                <<" have "<<scorelist[1]<<" points"<<endl;
                cout<<playername[1]<<" and "<< playername[3]
                <<" have "<<scorelist[0]<<" points"<<endl;
                
            } else{
                scorelist[orderupteam]+=2;
                cout<<"march!"<<endl;
                cout<<playername[0]<<" and "<< playername[2]
                <<" have "<<scorelist[1]<<" points"<<endl;
                cout<<playername[1]<<" and "<< playername[3]
                <<" have "<<scorelist[0]<<" points"<<endl;
                }
            } else{
            scorelist[winteam]+=2;
            cout<<"euchred!"<<endl;
            cout<<playername[0]<<" and "<< playername[2]
            <<" have "<<scorelist[1]<<" points"<<endl;
            cout<<playername[1]<<" and "<< playername[3]
            <<" have "<<scorelist[0]<<" points"<<endl;
            }
            numHand++;
            change_dealer();
        }
    
        void run_delete(){
            delete dealer;
            delete eldest;
            delete player3;
            delete player4;
        }
    };

int main(int argc, char* argv[]){
    ifstream fin;
    for(int i=0;i<argc;i++){
        cout<<argv[i]<<" ";}
    fin.open("pack.in");
    if(!fin.is_open()){
        cout << "Error opening " << argv[1] << endl;
        return -1;}
    const string input[8] ={argv[4], argv[5] ,argv[6],argv[7],
    argv[8],argv[9],argv[10],argv[11]};
    Game playgame(input,fin,atoi(argv[3]));

    while(playgame.get_score(0)< atoi(argv[3])
          && playgame.get_score(1)<atoi(argv[3])){
        playgame.initialPack(argv[2]);
        playgame.initialDeal();
        cout<<endl;
        cout<<"Hand "<< playgame.get_numHand()<< endl;
        cout<<playgame.get_dealer_name()<< " deals"<< endl;
        Card upcard = playgame.get_upcard();
        playgame.change_trump_suit(upcard.get_suit());
        cout<< upcard << " turned up" << endl;
        playgame.order_up_process(upcard,playgame.get_numHand(),playgame);
        cout<<endl;
        playgame.trick_process(playgame.get_trump_suit(),
                               playgame.get_numHand(),playgame);
    }
    cout<<endl;
    if(playgame.get_score(0)>=atoi(argv[3])){
        cout<< playgame.get_player_name(1) <<" and "
        <<playgame.get_player_name(3)<<" win!"<<endl;
    } else{
        cout<< playgame.get_player_name(0)<<" and "
        <<playgame.get_player_name(2)<<" win!"<<endl;}
    playgame.run_delete();
}
