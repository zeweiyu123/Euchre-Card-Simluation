// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>
using namespace std;

TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());

    Card d(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card::RANK_NINE, d.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, d.get_suit());
}


// Add more test cases here
TEST(test_card_is_face){
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(true, c.is_face());

    Card d(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(false, d.is_face());
    
    Card e(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(true, e.is_face());
}

TEST(test_card_rightbower){
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(true, c.is_right_bower("Spades"));

    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(false, d.is_right_bower("Clubs"));

    Card e(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(false, e.is_right_bower("Spades"));
    
    Card f(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(false, f.is_right_bower("Hearts"));
}

TEST(test_card_leftbower){
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(false, c.is_left_bower("Spades"));

    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(true, d.is_left_bower("Diamonds"));

    Card e(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(false, e.is_left_bower("Clubs"));
    
    Card f(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(false, f.is_left_bower("Diamonds"));
}

TEST(test_card_is_trump){
    Card c(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(true, c.is_trump("Spades"));

    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(true, d.is_trump("Diamonds"));

    Card e(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(false, e.is_trump("Hearts"));
    
    Card f(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(true, f.is_trump("Spades"));
    
    Card g(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(false, g.is_trump("Hearts"));
    
    Card h(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(false, h.is_trump("Hearts"));
}

TEST(test_overloaded_operator){
    Card a(Card::RANK_NINE, Card::SUIT_SPADES);
    Card b(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(true, a<b);
    ASSERT_EQUAL(true, a!=b);
    ASSERT_EQUAL(false,a>b);
    ASSERT_EQUAL(false,a>=b);
    ASSERT_EQUAL(true,a<=b);
    ASSERT_EQUAL(false,a==b);
    
    Card c(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card d(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_EQUAL(true, c<d);
    ASSERT_EQUAL(true, c!=d);
    ASSERT_EQUAL(false,c>d);
    ASSERT_EQUAL(false,c>=d);
    ASSERT_EQUAL(true,c<=d);
    ASSERT_EQUAL(false,c==d);
    
    Card e(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card f(Card::RANK_QUEEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(false, e<f);
    ASSERT_EQUAL(true, e!=f);
    ASSERT_EQUAL(true,e>f);
    ASSERT_EQUAL(false,e==f);
    ASSERT_EQUAL(false, e<=f);
    ASSERT_EQUAL(true, e>=f);
    
    Card g(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card h(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(false, g<h);
    ASSERT_EQUAL(false, g!=h);
    ASSERT_EQUAL(false,g>h);
    ASSERT_EQUAL(true, g<=h);
    ASSERT_EQUAL(true, g>=h);
    ASSERT_EQUAL(true, g==h);
    
    Card i(Card::RANK_JACK, Card::SUIT_SPADES);
    Card j(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_EQUAL(true, i<j);
    ASSERT_EQUAL(true, i!=j);
    ASSERT_EQUAL(false,i>j);
    ASSERT_EQUAL(false,i>=j);
    ASSERT_EQUAL(true,i<=j);
    ASSERT_EQUAL(false,i==j);
    
    Card k(Card::RANK_JACK, Card::SUIT_SPADES);
    Card l(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(true, k<l);
    ASSERT_EQUAL(true, k!=l);
    ASSERT_EQUAL(false,k>l);
    ASSERT_EQUAL(false,k>=l);
    ASSERT_EQUAL(true,k<=l);
    ASSERT_EQUAL(false,k==l);
    
    Card m(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card n(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(false, m<n);
    ASSERT_EQUAL(false, m!=n);
    ASSERT_EQUAL(false,m>n);
    ASSERT_EQUAL(true, m<=n);
    ASSERT_EQUAL(true, m>=n);
    ASSERT_EQUAL(true, m==n);
}
 
TEST(test_card_less){
    Card a(Card::RANK_NINE, Card::SUIT_SPADES);
    Card b(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(true, Card_less(a, b, "Hearts"));

    Card c(Card::RANK_NINE, Card::SUIT_SPADES);
    Card d(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(false, Card_less(c, d, "Spades"));

    Card e(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card f(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(false, Card_less(e, f, "Diamonds"));

    Card g(Card::RANK_JACK, Card::SUIT_SPADES);
    Card h(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(false, Card_less(g, h,"Spades"));
    ASSERT_EQUAL(false, Card_less(g, h,"Diamonds"));

    Card x(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card y(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(true, Card_less(x, y,"Spades"));
    ASSERT_EQUAL(false, Card_less(x, y,"Clubs"));
    
    Card ir(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card ec(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_EQUAL(false, Card_less(ir, ec,"Clubs"));
    ASSERT_EQUAL(false, Card_less(ir, ec,"Spades"));
    
    Card z(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card w(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(true, Card_less(z, w,"Diamonds"));
    ASSERT_EQUAL(true, Card_less(z, w,"Hearts"));
    ASSERT_EQUAL(false, Card_less(z, w,"Spades"));
    
    Card ro(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card zh(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(false, Card_less(ro, zh,"Diamonds"));
    
    Card cky(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card ang(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(false, Card_less(cky, ang,"Diamonds"));
    ASSERT_EQUAL(false, Card_less(cky, ang,"Hearts"))
}

TEST(test_card_less_2){
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK, Card::SUIT_SPADES);
    Card x(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(false, Card_less(a, b, x, "Clubs"));

    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card d(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card y(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(false, Card_less(c, d, y, "Clubs"));

    Card e(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card f(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card z(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(false, Card_less(e, f, z, "Clubs"));

    Card ro(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card cky(Card::RANK_KING, Card::SUIT_HEARTS);
    Card zh(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(false, Card_less(ro, cky, zh, "Clubs"));
    
    Card qd(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jz(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card zyd(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(false, Card_less(qd, jz, zyd, "Clubs"));
    
    Card g(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card h(Card::RANK_KING, Card::SUIT_CLUBS);
    Card s(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(false, Card_less(g, h, s, "Clubs"));
    
    Card i(Card::RANK_JACK, Card::SUIT_SPADES);
    Card l(Card::RANK_KING, Card::SUIT_CLUBS);
    Card k(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(false, Card_less(i, l, k, "Spades"));
    
    Card ii(Card::RANK_JACK, Card::SUIT_SPADES);
    Card ll(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card kk(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(false, Card_less(ii, ll, kk, "Clubs"));
    
    Card iii(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card lll(Card::RANK_KING, Card::SUIT_SPADES);
    Card kkk(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(true, Card_less(iii, lll, kkk, "Clubs"));
    
    Card iiii(Card::RANK_TEN, Card::SUIT_SPADES);
    Card llll(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card kkkk(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(true, Card_less(iiii, llll, kkkk, "Clubs"));
    
    Card iiiii(Card::RANK_TEN, Card::SUIT_SPADES);
    Card lllll(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card kkkkk(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_EQUAL(false, Card_less(iiiii, lllll, kkkkk, "Clubs"));
}

TEST(test_insertion_operator){
    Card Jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    ostringstream oss;
    oss<<Jack_hearts;
    ASSERT_EQUAL(oss.str(),"Jack of Hearts");
}

TEST_MAIN()
