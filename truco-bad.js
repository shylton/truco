

let dealtCards = [];
//readies the deck for another hand
function resetDeck() {
    for (crd of deck) {
        crd.selected = false;
    }
}

//deals random cards to player and pc opponent
function deal(){
    //select 6 random cards
    for (var i = 0; i < 6; i++) {
        let idx = Math.floor(Math.random()*1000) % 33;//33 cards in deck
        //loop to avoid selecting the same card twice
        while (deck[idx].selected) {
            idx++;
            if (idx == 33) {
                idx = 0;
            }
        }
        dealtCards.push(deck[idx]);
        deck[idx].selected = true;
    }
}
deal();
document.getElementById('pc3').src = dealtCards[2].pic;
document.getElementById('pc1').src = dealtCards[0].pic;;
document.getElementById('pc2').src = dealtCards[1].pic;
document.getElementById('pc3').src = dealtCards[2].pic;
document.getElementById('usr1').src = dealtCards[3].pic;
document.getElementById('usr2').src = dealtCards[4].pic;
document.getElementById('usr3').src = dealtCards[5].pic;
