/*****************************************************************************
 * Truco class, this is where all the magic happens
 *************************************************************************** */
function Truco(userName) {
    let user = {
        name: userName,
        hand:[],
        score: 0,
        gamesWon: 0,
    };
    let pc = {
        hand:[],
        score: 0,
        gamesWon: 0,
    };
    let roundValue = 2;//starts at 2, raises to 4, 6, 10, 12
    let dealer = true;//true = user, false = pc. used at start of round
    let nextPlayer = false;//true = user. used at start of trick
    let trick = 0;//0 = first trick
    let trickWinner = [];//bool[3], index = trick, true = user
    let cardPlayed = [null,null];//card at table for each trick
    let trucoCall = false;//true = must accept or fold

    this.setBtns = function(input){
        switch (input) {
            case 'play':
                document.getElementById('usrCrd1').style.display = "inline";
                break;
            default:

        }
    }
}
