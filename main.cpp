/*
Connect 4
Author: Vivian Nguyen
This is a Connect 4 game designed with C++.
*/
#include <iostream>
#include <string>
using namespace std;

const static int ROWS=6;
const static int COLS=7;
const static int EMPTY_VAL=0;
const static int P1_VAL=1;
const static int P2_VAL=2;
const char X_TOKEN='X';
const char O_TOKEN='O';


class Connect4{
public:
/**
 * Connect 4 constructor
 **/

    Connect4();

/**
 * prints the corresponding letter based on the int value of the gameBoard grid
 * 0: Represents an empty space
 * 1: Represents an X (Player 1)
 * 2: Represents an O (Player 2)
 **/

    void printLet(int value);

/**
 * displays the game grid and placed spaces
 **/
    void printGameGrid();

/**
 * counts number of pieces in a row, in the specified x and y directions.    
**/

    bool countPieces(int piece, int x_pos, int y_pos, int x_inc, int y_inc);

 /** 
  * checks if there is a winner during game
 **/

    bool checkWin(int piece);

/**
 * begins a connect 4 game
 **/

    void playGame();

/**
 * resets the state of the game, removing all pieces
 **/

    void resetGame();

private:

/*
    Levels: For each col, pieces are dropped into the bottommost spot of each slot.
    Each slot has an initial value of row-1, the bottom of the grid.
    When a piece is inserted into a slot s, levels[s] decrements to place the next piece in s on top.
    When slot==-1, the slot is full and pieces can no longer be placed in it.
*/
    int levels[COLS]={};
/*
    A 6 piece tall, 7 piece wide gameboard 
    To the right: Cols larger
    Moving downwards: Rows larger
*/

    int gameBoard[ROWS][COLS]={};
/*
    tells if player 1 or 2 won
*/

    bool play1Win;
    bool play2Win;

/*
    determines if game is continuing
*/
    bool keepPlaying;

/*
    a turn number representing which player's turn it is, even # if player 1 and odd # if player 2
*/
    int turn=0;
};

int main()
{
    Connect4 c4Game=Connect4();
    c4Game.playGame();
    return 0;
}

Connect4::Connect4(){
    resetGame();
}

void Connect4::resetGame(){
    //initialize all pieces to 0= empty piece
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            gameBoard[i][j]=EMPTY_VAL;
        }
    }
    //initialize all levels to ROWS-1 (bottom of the board)
    for (int i=0; i<COLS;i++){
        levels[i]=ROWS-1;
    }
    //set both winners to false
    play1Win=false;
    play2Win=false;

    //set keepPlaying to true

    keepPlaying=true;

    //reset to player 1 first

    turn=0;
}

void Connect4::printLet(int value){
    if (value==P1_VAL){
        cout<<X_TOKEN<<" ";
    }
    else if (value==P2_VAL){
        cout<<O_TOKEN<<" ";
    }
    else if (value==EMPTY_VAL){
        cout<<"  ";
    }
}

void Connect4::printGameGrid(){
    //PRINTING THE HEADER
    //initial spacing
    cout<<"    ";
    //print the #s corresponding to each column
    for (int i=0; i<COLS; i++){
        cout<<i+1<<"   ";
    }
    cout<<endl;
    //PRINTING THE GRID
    for (int i=0; i<ROWS; i++){
        cout<<"  ";
        cout<<"|";
        cout<<" ";

        for (int j=0; j<COLS; j++){
            //print the corresponding gameBoard element based on gameBoard's int value
             printLet(gameBoard[i][j]);
             cout<<"|";
             cout<<" ";
        }
        cout<<endl;
        cout<<" ";
        //for any row that isn't the last, place a divider
        if (i!=ROWS-1){
            cout<<"- - - - - - - - - - - - - - - -"<<endl;
        }

    }

}

bool Connect4:: countPieces(int piece, int r_pos, int c_pos, int r_inc, int c_inc){
    int count=0;

   //check if index is in bounds and if the piece appears 4 times consecutively in given direction
    while (r_pos>=0 && r_pos<ROWS && c_pos>=0 && c_pos<COLS && gameBoard[r_pos][c_pos]==piece){
        //cout<<r_pos<<" "<<c_pos<<endl;
        //cout<<"Count: "<<count<<endl;
        count++;
        r_pos+=r_inc;
        c_pos+=c_inc;
        if (count==4){
            return true;
        }
    }
    return false;
}

bool Connect4::checkWin(int piece) {
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLS; j++){
            if (gameBoard[i][j]==piece){

                //start counting at the matching piece
                int rowStart=i;
                int colStart=j;

                //check up, down, left, right, and diagonally in all directions for 4 in a row

                if (countPieces(piece, rowStart ,colStart,0,1) || countPieces(piece, rowStart ,colStart,0,-1) || countPieces(piece, rowStart ,colStart,-1,0) 
                || countPieces(piece,rowStart,colStart, 1,0) || countPieces(piece, rowStart ,colStart,-1,1)  || countPieces(piece, rowStart ,colStart,1,-1) 
                || countPieces(piece, rowStart ,colStart,-1,-1) || countPieces(piece, rowStart ,colStart, 1,1)){
                    return true;
                }
            }
        }
    }
    return false;
}

void Connect4::playGame(){

    int space=-1;

    bool loop=true;

    while (loop){
        while (keepPlaying){

           printGameGrid();

           if (turn%2==0){
                cout<<"Player 1: Enter a space # : ";
           }   
           else{
                cout<<"Player 2: Enter a space # : ";
           }
            do{
                cin>>space;
                //space is not valid if 0 or less or 8 or greater, or if the level is full
                if (space<=0 || space >=8 || levels[space-1]<0){
                    cout<<"Please enter a valid space #: " ;
                 } 
            } while (space<=0 || space >=8 || levels[space-1]<0);

            if (turn%2==0){
                gameBoard [(levels[space-1])] [space-1]=1;
            }
            else{
                 gameBoard [(levels[space-1])] [space-1]=2;
            }

            bool toEnd=true;
            //raise level of column
            levels[space-1]--;
            for (int i=0; i<COLS; i++){
                if (levels[i]>=0){
                    toEnd=false;
                }
            }

            //check if there is 4 in a row of the current piece

            int winPiece=2-((turn+1)%2);
            if (checkWin(winPiece)){

                if (turn%2==0){
                    play1Win=true;
                }
                else{
                    play2Win=true;
                }
                keepPlaying=false;
            }

            if (toEnd){
                keepPlaying=false;
            }

            //change turn

            turn++;
            space=-1;

        }

        //when keepPlaying=false, check if there's a winner or a tie  
        if (play1Win){

            printGameGrid();
            cout<<"Player 1 wins! "<<endl;
        }     

        else if (play2Win){

            printGameGrid();
            cout<<"Player 2 wins! "<<endl;
        }

        else{

            printGameGrid();
            cout<<"It's a tie "<<endl;
        }

        //ask the user if they want to play again.
        string response="";
        cin.ignore(100, '\n');
        cout<<"Want to play again? y/n ";
        cin>>response;

        while (response!="y" && response!="n" || cin.fail()){

            cin.clear();
            string garbage;
            getline(cin,garbage);
            cout<<"Please enter a valid response y/n: ";
            cin>>response;
        }

        if (response=="n"){
            loop=false;
        }
        resetGame();

    }
    cout<<"Thanks for playing!"<<endl;
}







