/*****************************************************************************
 * Deck class. contains array of cards and function to deal cards
 * INPUT: Objects: user, pc, with hand[3] array
 * OUTPUT: array of three random cards for each player
 *************************************************************************** */
function deck() {
    let cards = [
        // cards sorted by value
        {pic: 'cards/4C.svg', value: 12},
        {pic: 'cards/7H.svg', value: 11},
        {pic: 'cards/AS.svg', value: 10},
        {pic: 'cards/7D.svg', value: 9},

        {pic: 'cards/3C.svg', value: 8},
        {pic: 'cards/3H.svg', value: 8},
        {pic: 'cards/3S.svg', value: 8},
        {pic: 'cards/3D.svg', value: 8},

        {pic: 'cards/2C.svg', value: 7},
        {pic: 'cards/2H.svg', value: 7},
        {pic: 'cards/2S.svg', value: 7},
        {pic: 'cards/2D.svg', value: 7},

        {pic: 'cards/AC.svg', value: 6},
        {pic: 'cards/AH.svg', value: 6},
        {pic: 'cards/AD.svg', value: 6},

        {pic: 'cards/KC.svg', value: 5},
        {pic: 'cards/KH.svg', value: 5},
        {pic: 'cards/KS.svg', value: 5},
        {pic: 'cards/KD.svg', value: 5},

        {pic: 'cards/JC.svg', value: 4},
        {pic: 'cards/JH.svg', value: 4},
        {pic: 'cards/JS.svg', value: 4},
        {pic: 'cards/JD.svg', value: 4},

        {pic: 'cards/QC.svg', value: 3},
        {pic: 'cards/QH.svg', value: 3},
        {pic: 'cards/QS.svg', value: 3},
        {pic: 'cards/QD.svg', value: 3},

        {pic: 'cards/5C.svg', value: 2},
        {pic: 'cards/5H.svg', value: 2},
        {pic: 'cards/5S.svg', value: 2},
        {pic: 'cards/5D.svg', value: 2},

        {pic: 'cards/4H.svg', value: 1},
        {pic: 'cards/4S.svg', value: 1},
        {pic: 'cards/4D.svg', value: 1},
    ];

    //selects 6 unique random cards and sets it to user.hand and pc.hand
    this.deal = function(user, pc){
        let cardIdx = [];//will contain index of 6 random cards
        while(cardIdx.length < 6){
            let i = Math.floor(Math.random()*cards.length);
            if(cardIdx.indexOf(i) === -1) cardIdx.push(i);
        }
        for (let i = 0; i < 3; i++) {
            user.hand[i] = cards[ cardIdx[i] ];
            pc.hand[i] = cards[ cardIdx[i+3] ];
        }
    }
}
