/*******************************************************************************
* Author:       Shylton Matta
* Date:         12 Aug 2019
* Description:  just a cool card game
*******************************************************************************/
#include "truco.hpp"

/*******************************************************************************
Default constructor, sets a couple of variables
inputs: nothing
return: nothing
*******************************************************************************/
Truco::Truco() {

  resetVariables();
  gameScore = 0;
  gamesPlayed = 0;

}

/*******************************************************************************
cleanup for new game
inputs: nothing
return: nothing
*******************************************************************************/
void Truco::resetVariables() {
  round = 0;
  gameWinner = notSet;
  roundWinner[0] = notSet;
  roundWinner[1] = notSet;
  roundWinner[2] = notSet;
  p1Played[0] = noCrd;
  p1Played[1] = noCrd;
  p1Played[2] = noCrd;
  pcPlayed[0] = noCrd;
  pcPlayed[1] = noCrd;
  pcPlayed[2] = noCrd;
}

/*******************************************************************************
cout relevant variables, good for troubleshooting
inputs: nothing
return: nothing
*******************************************************************************/
void Truco::printVariables() {

  std::cout << "Accumulated game score: " << gameScore << '\n';
  std::cout << "Games played: " << gamesPlayed << '\n';
/* for peaking at the pc's hand
  std::cout << "\nPC hand-> ";
  coutCards(pcHand);
*/
  std::cout << "\nrd winners:  " << winnerMap.at(roundWinner[0]) << ", "
            << winnerMap.at(roundWinner[1]) << ", "
            << winnerMap.at(roundWinner[2]) << '\n';

  std::cout << "player played: " << cardMap.at(p1Played[0]) << ' '
            << cardMap.at(p1Played[1]) << ' '
            << cardMap.at(p1Played[2]) << '\n';

  std::cout << "Kronos played: " << cardMap.at(pcPlayed[0]) << ' '
            << cardMap.at(pcPlayed[1]) << ' '
            << cardMap.at(pcPlayed[2]) << "\n\n";

}

/*******************************************************************************
Prints round header
inputs: nothing
return: nothing
*******************************************************************************/
void Truco::printHeader() {
  std::cout << '\n' << std::string(64,'-') << '\n'
            << std::string(28,' ') << "ROUND: " << round+1 << '\n'
            << std::string(64,'-') << "\n\n";//centered Round title
  printVariables();
}

/*******************************************************************************
prints to screen a given list of cards
inputs: list<card> by ref: the cards to be printed
return: void
*******************************************************************************/
void Truco::coutCards(std::vector<card> &crds) {

  for (auto it = crds.begin(); it != crds.end(); ++it) {
    std::cout << ' ' << cardMap.at(*it) << ' ' << '|';
  }
  std::cout << std::endl;
}

/*******************************************************************************
Setup the deck with 4x each numbered card, one empty card, and the four face
  cards. clears up the deck beforehand
inputs: nothing
return: void
*******************************************************************************/
void Truco::setDeck() {

  deck.clear();

  deck.push_back(cJ);
  deck.push_back(cQ);
  deck.push_back(cK);
  deck.push_back(cA);

  deck.push_back(c2);
  deck.push_back(c2);
  deck.push_back(c2);
  deck.push_back(c2);

  deck.push_back(c3);
  deck.push_back(c3);
  deck.push_back(c3);
  deck.push_back(c3);

  deck.push_back(c4);
  deck.push_back(c4);
  deck.push_back(c4);
  deck.push_back(c4);

  deck.push_back(c5);
  deck.push_back(c5);
  deck.push_back(c5);
  deck.push_back(c5);

}

/*******************************************************************************
shuffles the deck
inputs: nothing
return: void
*******************************************************************************/
/* random generator function:
source: http://www.cplusplus.com/reference/algorithm/random_shuffle/
*/
int myrandom (int i) {
  return std::rand()%i;
}

void Truco::shuffleDeck () {
  int i = std::rand()%1000;
  std::random_shuffle(deck.begin(), deck.end(), myrandom);
}

/*******************************************************************************
Shuffles the deck then deals three cards from the deck to each player.
inputs: nothing
return: void
*******************************************************************************/
void Truco::dealCards() {
  shuffleDeck();

  p1Hand.clear();
  pcHand.clear();

  //deal alternating cards, odd to player, even to pc
  p1Hand.push_back(deck.at(1));
  p1Hand.push_back(deck.at(3));
  p1Hand.push_back(deck.at(5));

  pcHand.push_back(deck.at(2));
  pcHand.push_back(deck.at(4));
  pcHand.push_back(deck.at(6));
}

/*******************************************************************************
Shows menu for user selection, validates input, returns card selected by player
inputs: nothing
return: card: the player selection
*******************************************************************************/
void Truco::p1Choice() {
  unsigned playCard;
  card rtn;

  std::cout << " your  |1st|2nd|3rd|\n"
            << " hand->|";
  coutCards(p1Hand);
  std::cout << "Choose a card to play [1st, 2nd or 3rd]: ";
  do {
    playCard = getInt(1,3);
    playCard--;//decrement to get the correct index
    rtn = p1Hand.at(playCard);

    if (noCrd == rtn) {
      std::cout << "invalid choice. try again: ";
    }
  } while(noCrd == rtn);//error: chose an empty card slot

  p1Hand.at(playCard) = noCrd;
  p1Played[round] = rtn;

}

/*******************************************************************************
Chooses a card from the pc hand. AI algo for the three scenarios:
  A. pick lowest if none can beat player's (discarding low)
  B. if cannot do better than tie, pick at random (Not sure theres a best strat)
  C. pick lowest that can beat (even if its the highest, rd 1 is tiebreaker so
    its the most important to win)
precondition: player's rd1 choice saved in p1Played[0]
inputs: nothing
return: card: the pc choice
*******************************************************************************/
void Truco::pcChoiceRd1() {
  std::vector<int> diffs;
  card rtn;//pc's chosen card
  bool luckyPC;
  int index = -1,//will increment before use
      cmp,//used to compare player vs pc card
      randCard,//used to pick a random card from pc hand
      diff1,//difference in value between the 1st-3rd pc card vs player played
      diff2,
      diff3;

  std::sort( pcHand.begin(), pcHand.end() );//sort PC cards to help choose

  if (noCrd == p1Played[0]) {
    /* player has not played, ie pc goes first. Choosing random card */
    randCard = (rand()%3);
    rtn = pcHand.at(randCard);
    pcHand.at(randCard) = noCrd;
  } else {
    /* PC going after the player */
    diff1 = pcHand.at(0) - p1Played[0];
    diff2 = pcHand.at(1) - p1Played[0];
    diff3 = pcHand.at(2) - p1Played[0];

    diffs.push_back(diff1);
    diffs.push_back(diff2);
    diffs.push_back(diff3);

    std::sort( diffs.begin(), diffs.end() );//sort the differences

    /* A. no pc card can beat the player's, choose lowest non-blank */
    if (diffs.back() < 0)
    {
      rtn = pcHand.at(0);
      pcHand.at(0) = noCrd;
    }/* B. best we can do is tie, randomly choose to tie or lowest
        (not sure whats the best strat) */
    else if (0 == diffs.back())
    {
      luckyPC = ((rand()%1000)>499);
      if (luckyPC) {
        rtn = pcHand.at(2);
        pcHand.at(2) = noCrd;
      } else {
        rtn = pcHand.at(0);
        pcHand.at(0) = noCrd;
      }
    } /* C. choose lowest card that can beat player's */
    else
    {
      do {
        index++;
        cmp = pcHand.at(index) - p1Played[round];
        rtn = pcHand.at(index);
      } while(cmp <= 0);//exit loop once higher than zero card found
      pcHand.at(index) = noCrd;
    }// end if, else if, else
  }//end of pc going after player

  pcPlayed[0] = rtn;
  std::cout << "## Kronos Played Card -> " <<  cardMap.at(rtn) << " ##\n\n";
  diffs.clear();//need this if multiples games are to be played

}

/*******************************************************************************
Chooses a card from the pc hand for Round 2. AI algo: (simpler than rd1)
  - if player won 1st round, must win second
  - if player lost 1st round, pick lowest (hoping that p1 will have to pick the
    highest from his hand in order to beat)
inputs: nothing
return: card: the pc choice
*******************************************************************************/
void Truco::pcChoiceRd2() {
  std::sort( pcHand.begin(), pcHand.end() );//sort PC cards to help choose
  card rtn;

  if (noCrd == p1Played[1]) {//noCrd means pc is first to act in rd2
    /* A. pc won round 1. going first, choose lowest  */
    rtn = pcHand.at(1);//index 0 shud b blank, 1 is lowest post sort
    pcHand.at(1) = noCrd;
  } else {
    /* B. pc lost round 1, choose lowest if beats player else choose highest
          since this round is a must win */
    if (pcHand.at(1) > p1Played[1]) {
      rtn = pcHand.at(1);//index 0 shud b blank, 1 is lowest post sort
      pcHand.at(1) = noCrd;
    } else {
      rtn = pcHand.at(2);//index 2 is highest post sort
      pcHand.at(2) = noCrd;
    }
  }//end if else

  std::cout << "## Kronos Played Card -> " <<  cardMap.at(rtn) << " ##\n\n";

  pcPlayed[1] = rtn;
}

/*******************************************************************************
sorts cards and picks the highest
inputs: nothing
return: card, highest from the hand given
*******************************************************************************/
card Truco::chooseHighest(std::vector<card> &crds) {
 card rtn;
  std::sort( crds.begin(), crds.end() );
  rtn = crds.back();
  crds.back() = noCrd;
  return rtn;
}

/*******************************************************************************
sets the round winner by comparing the cards
inputs: rd, player card, pc card
return: void
*******************************************************************************/
void Truco::setRdWinner(int rd, card plIn, card pcIn) {
  int cmp;
  winner rtn;

  cmp = plIn - pcIn;

  if (0 == cmp) {
    rtn = tie;
  } else if (cmp > 0) {
    rtn = player;
  } else if (cmp < 0) {
    rtn = pc;
  } else {
    std::cout << "oopsie, @ setRdWinner" << '\n';
  }

  roundWinner[rd] = rtn;
}

/*******************************************************************************
Updates the game score, +1 if player wins, -1 if pc wins, 0 otherwise
predondition: gameWinner set. SHOULD ONLY BE CALLED AT THE END OF A GAME
inputs: nothing
return: card: the pc choice
*******************************************************************************/
void Truco::updateGameScore(){
  if (player == gameWinner) {
    gameScore++;
  } else if (pc == gameWinner) {
    gameScore--;
  }
  gamesPlayed++;
}

/*******************************************************************************
runs a 3 round game of truco
inputs: nothing
return: int: the running total score (could be multiple games)
*******************************************************************************/
int Truco::letsPlay() {
  int rtn;
  bool endNow = false, first2act;

  resetVariables();
  setDeck();
  dealCards();

  //ROUND 1. randomly select who goes first
  printHeader();

  first2act = ((rand()%1000)>499);
  if (first2act) {//player goes first
    std::cout << "You go first" << '\n';
    p1Choice();
    pcChoiceRd1();
  } else {
    std::cout << "Kronos goes first" << '\n';
    pcChoiceRd1();
    p1Choice();
  }

  setRdWinner(0, p1Played[0], pcPlayed[0]);
  std::cout << "First round winner: " << winnerMap.at(roundWinner[0]) << '\n';
  pressKey();
  round++;

  //ROUND 2
  printHeader();

  if (tie == roundWinner[0]) {
    /* round 1 tie => highest in rd 2 wins game or if tie again go to rd 3 */
    std::cout << "Playing the highest card..." << '\n';
    p1Played[1] = chooseHighest(p1Hand);
    pcPlayed[1] = chooseHighest(pcHand);
    setRdWinner(1, p1Played[1], pcPlayed[1]);
    std::cout << "Second round winner: " << winnerMap.at(roundWinner[1]) << '\n';
    pressKey();

    if (roundWinner[1] != tie) {
      /* rd1 tie, game ended in rd 2 */
      gameWinner = roundWinner[1];
      std::cout << winnerMap.at(gameWinner) << " won the Game!\n";
      endNow = true;
    } else {
      /* ROUND 3, tied in first and second round!  */
      round++;
      printHeader();
      std::cout << "Playing the highest card..." << '\n';
      p1Played[2] = chooseHighest(p1Hand);
      pcPlayed[2] = chooseHighest(pcHand);
      setRdWinner(2, p1Played[2], pcPlayed[2]);

      gameWinner = roundWinner[2];
      std::cout << winnerMap.at(gameWinner) << " won the Game!\n";
      endNow = true;
    }
  } else if (pc == roundWinner[0]) {
    /* pc won first round, pc goes first */
    pcChoiceRd2();
    p1Choice();
    setRdWinner(1, p1Played[1], pcPlayed[1]);
    std::cout << "Second round winner: " << winnerMap.at(roundWinner[1]) << '\n';
    pressKey();

    if (pcPlayed[1] >= p1Played[1]) {
      /* pc won first and tied or better on second round, end game */
      gameWinner = pc;
      std::cout << winnerMap.at(gameWinner) << " won the Game!\n";
      endNow = true;
    }
  } else if (player == roundWinner[0]) {
    /* player won first round, player goes first */
    p1Choice();
    pcChoiceRd2();
    setRdWinner(1, p1Played[1], pcPlayed[1]);
    std::cout << "Second round winner: " << winnerMap.at(roundWinner[1]) << '\n';
    pressKey();

    if (p1Played[1] >= pcPlayed[1]) {
      /* player won first and second round, end game */
      gameWinner = player;
      std::cout << winnerMap.at(gameWinner) << " won the Game!\n";
      endNow = true;
    }
  } else {
    /* shud not happen */
    std::cout << "oopsie, @ Round 2" << '\n';
  }

  if (!endNow) {
    //ROUND 3
    round++;
    printHeader();
    std::cout << "Playing the last card..." << '\n';
    p1Played[2] = chooseHighest(p1Hand);
    pcPlayed[2] = chooseHighest(pcHand);
    setRdWinner(2, p1Played[2], pcPlayed[2]);
    std::cout << "Third round winner: " << winnerMap.at(roundWinner[2]) << '\n';

    if (tie == roundWinner[2]) {
      /* first round winner wins on a tie */
      gameWinner = roundWinner[0];
      std::cout << winnerMap.at(gameWinner) << " won the Game!\n";
    } else{
      /* otherwise this round is the tiebreaker */
      gameWinner = roundWinner[2];
      std::cout << winnerMap.at(gameWinner) << " won the Game!\n";
    }
  }//end 3rd round

  //WRAP UP
  updateGameScore();
  std::cout << "\n   *** Final results ***" << '\n';
  printVariables();
  std::cout << "Full Deck:" << '\n';
  coutCards(deck);

  return gameScore;
}

/*******************************************************************************
MAIN for testing

int main() {
  srand(time(0));
  int mais1 = 0;
  int finalScore;

  Truco game1;

  do {
    finalScore = game1.letsPlay();
    std::cout << "press 1 to play again: ";
    mais1 = getInt(-1,5);
  } while(1 == mais1);

std::cout << "Final Score: " << finalScore << '\n'
          << "gracias...\n";

  return 0;
}

*******************************************************************************/
