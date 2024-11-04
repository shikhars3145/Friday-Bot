#include<bits/stdc++.h>
using namespace std;
#include <string>

//X means empty block
//b means block on my boundary, i cant place
//c means my corners, i have to chose one where to  // rather than thinking of them as corners call them overlap points

// given a piece and a corner point, find the coordinate where to put origin of that (optimisation)

vector<vector <char> > board = vector<vector <char> >(14, vector<char> (14,'X')); 


vector<vector<pair<int,int> > > piecesVect;

// todo: write make move function to push to usedPieces.
vector<int> usedPieces;

//  vector<pair<int, int>> vect1 = {{0,0}};
//  piecesVect.push_back({{0,0}});
// piecesVect.push_back({{0,0},{0,-1}});
// piecesVect.push_back({{0,0},{0,-1},{0,-2}});
// piecesVect.push_back({{0,0},{0,-1},{0,-2},{0,-3}});
// piecesVect.push_back({{0,0},{0,-1},{0,-2},{0,-3},{0,-4}}); //5th piece
// piecesVect.push_back({{0,0},{0,-1},{1,0}});
// piecesVect.push_back({{0,0},{0,-1},{1,0},{0,-2}});
// piecesVect.push_back({{0,0},{0,-1},{-1,0},{1,-1}});
// piecesVect.push_back({{0,0},{0,-1},{1,-1},{1,0}});
// piecesVect.push_back({{0,0},{0,-1},{1,0},{2,0},{3,0}}); //10th piece
// piecesVect.push_back({{0,0},{-1,0},{1,0},{0,-1},{0,-2}});
// piecesVect.push_back({{0,0},{0,-1},{0,-2},{1,0},{2,0}});
// piecesVect.push_back({{0,0},{0,1},{-1,1},{1,0},{2,0}});
// piecesVect.push_back({{0,0},{-1,0},{1,0},{-1,1},{1,-1}});
// piecesVect.push_back({{0,0},{1,0},{-1,0},{0,-1}}); //15th piece
// piecesVect.push_back({{0,0},{1,0},{0,1},{0,2},{1,1}});
// piecesVect.push_back({{0,0},{0,-1},{-1,0},{1,-1},{-1,1}});
// piecesVect.push_back({{0,0},{0,1},{0,-1},{1,-1},{1,1}});
// piecesVect.push_back({{0,0},{0,-1},{0,1},{-1,0},{1,-1}});
// piecesVect.push_back({{0,0},{0,-1},{0,1},{1,0},{-1,0}}); //20th piece
// piecesVect.push_back({{0,0},{1,0},{-1,0},{0,-1},{2,0}});

vector<pair<int,int> > rotateFn(vector<pair<int,int> > selectedPiece){
	vector<pair<int,int> > rotatedPiece;
	for(int i=0; i<selectedPiece.size(); i++)
	{
		pair<int,int> block = selectedPiece[i];
		int x = -block.second;  // x = -y;
		int y = block.first; // y = x
		rotatedPiece.push_back({x,y});
	}

	return rotatedPiece;
}

vector<pair<int, int> > flipFn(vector<pair<int,int> > selectedPiece){
	vector<pair<int,int> > flippedPiece;
	for(int i=0; i<selectedPiece.size(); i++)
	{
		pair<int,int> block = selectedPiece[i];
		int x = -block.first;  // x = -x;
		int y = block.second; // y = y
		flippedPiece.push_back({x,y});
	}

	return flippedPiece;
}

void printBoard(){
	cout<<"  ";
	for(int i=0; i< board.size(); i++){
		if(i<10) cout<<" ";
		cout<<i<<" ";
	}
	cout<<endl;
	for(int y=0; y<board.size(); y++)
	{
		cout<<y<<" ";
		if(y<10) cout<<" ";
		for(int x=0; x<board[0].size(); x++)
		{
			cout<<board[x][y]<<" "; cout<<" ";
		}
			
		cout<<endl;
	}
}


void insertInBoard(vector<pair<int,int>> piece, int x, int y, bool me){
	for(int i=0; i<piece.size(); i++)
	{
		pair<int, int> block = piece[i];
		int bx = block.first+x;
		int by = block.second+y;


		board[bx][by] = me ? '1' : '2';

		
	}

	for(int i=0; i<piece.size(); i++)
	{
		pair<int, int> block = piece[i];
		int bx = block.first+x;
		int by = block.second+y;


		// this is a block, mark its boundary cells as b if its empty before
		for(int i = -1; i <= 1; ++i) {
			for(int j = -1; j <= 1; ++j) {
				if((i == 0 && j != 0) || (i != 0 && j == 0)) { // Horizontal or vertical check
					int newX = bx + i;
					int newY = by + j;
					
					if(newX >= 0 && newX < 14 && newY >= 0 && newY < 14 && (board[newX][newY] == 'X' || (me && board[newX][newY] == 'C') || board[newX][newY] == 'c' || (me && board[newX][newY] == 'I') || (me && board[newX][newY] == 'b') )) {
						if(me)
							board[newX][newY] = 'B';
						else board[newX][newY] = 'b';
					}
				}
			}
		}

		}

	

	for(int i=0; i<piece.size(); i++)
	{
		pair<int, int> block = piece[i];
		int bx = block.first+x;
		int by = block.second+y;


		for(int i = -1; i <= 1; i += 2) {
        for(int j = -1; j <= 1; j += 2) {
            int newX = bx + i;
            int newY = by + j;
            
            if(newX >= 0 && newX < 14 && newY >= 0 && newY < 14) {
				if(board[newX][newY]=='X' || (me && board[newX][newY]=='b')){  // I is a corner for both so its better to use it first as it will cause disadvantage for opp
                	if(me)
					{
						board[newX][newY] = 'C';
					}	
					else
						board[newX][newY] = 'c';
				}
				else if((board[newX][newY]=='C' && !me) || (board[newX][newY]=='c' && me))
				{
					board[newX][newY]='I';
				}
            }
        }
    	}
	}

	
}

void clearBoard(){
	for(int x=0; x<board.size(); x++)
	{
		for(int y=0; y<board[x].size(); y++)
			board[x][y]='X';
	}

	

	board[4][4] = 'C';
	board[9][9] = 'C';
}

// function to take a piecename and rotation and flip value and update the boards state. 
void placepiece(int pieceNumber, int flip, int rotate, int x, int y, int me){
	// cout<<"placepiece inputs: "<<pieceNumber<<" "<<flip<<" "<<rotate<<" "<<x<<" "<<y<<" "<<me;
	vector<pair<int,int>> piece = piecesVect[pieceNumber];
	if(flip)
	{
		piece = flipFn(piece);
	}
	for(int i=0; i<rotate; i++)
	{
		piece = rotateFn(piece);
	}

	// cout<<"reached insert board";
	insertInBoard(piece, x, y, me);

}

int countMyCorners(){
	int c = 0;
	for(int i=0; i<14; i++)
	{
		for(int j=0; j<14; j++)
		{
			if(board[i][j]=='C' || board[i][j]=='I'){
				c++;
			}
		}
	}

	return c;
}

pair<bool,int> isPiecePlacementValid(vector<pair<int,int>> piece, int x, int y)
{
	int score = 0;  // 50 for each block in piece, 20 for opponent Corner covered, -5 for my corners covered more than one, 10 for additional corners created, 30 for Imp corner covered
	int myCornerOverlap = 0;
	int impCornerOverlap = 0;
	int opponentCornerOverlap = 0;
	for(int i=0; i<piece.size(); i++)
	{
		pair<int, int> block = piece[i];
		int newX = block.first+x;
		int newY = block.second+y;
		if(newX < 0 || newX >= 14 || newY < 0 || newY >= 14){
			return {false,0};
		}
		if(board[newX][newY] == '1' || board[newX][newY] == '2' || board[newX][newY] == 'B'){
			return {false,0};
		}
		if(board[newX][newY]=='C'){
			myCornerOverlap++;
		}
		if(board[newX][newY]=='c'){
			opponentCornerOverlap++;
		}

		if( board[newX][newY]=='I'){
			impCornerOverlap++;
		}
	}

	if(impCornerOverlap+myCornerOverlap==0){
		return {false,0};
	}
	vector<vector <char> > boardBackup = vector<vector <char> >(board);
	int myCornersPrev = countMyCorners();
	insertInBoard(piece, x, y, true);
	int myCornersNow = countMyCorners();
	board = boardBackup;
	int newCornersAdded = myCornersNow - myCornersPrev;

	int myCornerOverlapNeeded = 1;
	if(impCornerOverlap)
	{
		myCornerOverlapNeeded=0;
	}

	score = 50*piece.size()+newCornersAdded*10+impCornerOverlap*30+opponentCornerOverlap*20-(myCornerOverlap-myCornerOverlapNeeded)*5;
	return {true,score};
}

pair<bool,int> isValidMove(int pieceInd, int flip, int rotate,int x, int y){
	vector<pair<int,int>> selectedpiece = piecesVect[pieceInd];
	if(flip)
	{
		selectedpiece = flipFn(selectedpiece);
	}
	for(int i=0; i<rotate; i++)
	{
		selectedpiece = rotateFn(selectedpiece);
	}

	pair<bool,int> res = isPiecePlacementValid(selectedpiece,x,y);

	return res;
	
}


// returns valid moves (probably index of piece, x and y coords where to place, and points we get from them)
vector<vector<int>> getValidMoves(){
	vector<vector<int>> validMoves;
	for(int i=0; i<piecesVect.size(); i++)
	{
		std::vector<int>::iterator it;
		it = std::find(usedPieces.begin(), 
				usedPieces.end(), i);
		
		if(it != usedPieces.end())
		{
			continue;
		}
		for(int flip=0; flip<2; flip++){
			for(int rotate=0; rotate<4; rotate++){
				for(int x=0; x<14; x++){
					for(int y=0; y<14; y++){
						pair<bool,int> res= isValidMove(i,flip,rotate,x,y);  // should return a pair of <bool, int> bool is for valid, int is for score
						if(res.first)
						{
							validMoves.push_back({i,flip,rotate,x,y,res.second});
						}
					}
				}
			}
		}
	}

	return validMoves;
}

void makeBestMove(vector<vector<int>> validMoves){
	if(validMoves.size()==0){
		cout<<"PASS"<<endl;
		return;
	}
	int currentBestScore = -1000000;
	int currentBestIndex = 0;
	for(int i=0; i<validMoves.size(); i++){
		if(validMoves[i][5]>=currentBestScore){
			currentBestScore = validMoves[i][5];
			currentBestIndex = i;
		}
	}
	usedPieces.push_back(validMoves[currentBestIndex][0]);
	placepiece(validMoves[currentBestIndex][0],validMoves[currentBestIndex][1], validMoves[currentBestIndex][2], validMoves[currentBestIndex][3], validMoves[currentBestIndex][4], true);
	// for(int i=0; i<5; i++)
	// {
	// 	if(i==0)
	// 		cout<<validMoves[currentBestIndex][i]+1; // return piece number not index
	// 	else
	// 		cout<<validMoves[currentBestIndex][i];
	// 	if(i==4) cout<<endl;
	// 	else cout<<" ";
	// }

	cout<< validMoves[currentBestIndex][0]+1 <<" "<<validMoves[currentBestIndex][1] <<" "<< validMoves[currentBestIndex][2] <<" "<< validMoves[currentBestIndex][4]<<" "<< validMoves[currentBestIndex][3] <<'\n';
		
}


int main(){
	string command = "";
	piecesVect.push_back({{0,0}});
	piecesVect.push_back({{0,0},{0,-1}});
	piecesVect.push_back({{0,0},{0,-1},{0,-2}});
	piecesVect.push_back({{0,0},{0,-1},{0,-2},{0,-3}});
	piecesVect.push_back({{0,0},{0,-1},{0,-2},{0,-3},{0,-4}}); //5th piece
	piecesVect.push_back({{0,0},{0,-1},{1,0}});
	piecesVect.push_back({{0,0},{0,-1},{1,0},{0,-2}});
	piecesVect.push_back({{0,0},{0,-1},{-1,0},{1,-1}});
	piecesVect.push_back({{0,0},{0,-1},{1,-1},{1,0}});
	piecesVect.push_back({{0,0},{0,-1},{1,0},{2,0},{3,0}}); //10th piece
	piecesVect.push_back({{0,0},{-1,0},{1,0},{0,-1},{0,-2}});
	piecesVect.push_back({{0,0},{0,-1},{0,-2},{1,0},{2,0}});
	piecesVect.push_back({{0,0},{0,1},{-1,1},{1,0},{2,0}});
	piecesVect.push_back({{0,0},{-1,0},{1,0},{-1,1},{1,-1}});
	piecesVect.push_back({{0,0},{1,0},{-1,0},{0,-1}}); //15th piece
	piecesVect.push_back({{0,0},{1,0},{0,1},{0,2},{1,1}});
	piecesVect.push_back({{0,0},{0,-1},{-1,0},{1,-1},{-1,1}});
	piecesVect.push_back({{0,0},{0,1},{0,-1},{1,-1},{1,1}});
	piecesVect.push_back({{0,0},{0,-1},{0,1},{-1,0},{1,-1}});
	piecesVect.push_back({{0,0},{0,-1},{0,1},{1,0},{-1,0}}); //20th piece
	piecesVect.push_back({{0,0},{1,0},{-1,0},{0,-1},{2,0}});
	clearBoard();
	bool isMyFirstMove = true;

	// piecesVect.push_back(vect1);
	while(true){
		// cout<<"Give command:";
		getline(cin, command);
		if(command == "MAKE_MOVE")
		{
			// clearBoard();
			// vector<vector<int> > move {{12-1,0,1,4,4,10}};
			isMyFirstMove = false;
			vector<vector<int> > move {{20-1,0,0,4,4,10}};
			// vector<vector<int> > move {{20-1,0,0,10,10,10}};
			makeBestMove(move);  // nth piece index is n-1
			// printBoard();
		}

		else if(command == "PASS" || command == "0")
		{
			// opponent didnt played their piece
			// board state remains same
			// make your next move
			vector<vector<int>> validMoves = getValidMoves();
			makeBestMove(validMoves);
			// printBoard();
		}

		else
		{
				vector<string> v;
				stringstream ss(command);
				string s;
				while (getline(ss, s, ' ')){
					v.push_back(s);
				}
				// cout<<"reached opponent move"<<endl;
				// vector<string> params;
				// while ((pos = command.find(" ")) != std::string::npos) {
				// 	// cout<<"in while";
				// 	token = command.substr(0, pos);
    			// 	params.push_back(token);
    			// 	command.erase(0, pos + 1);
				// }

				// cout<<"got params "<<params.size()<<" "<<command<<endl;
				int opponent_piece = stoi(v[1])-1; // converting piece number to index
				int flip = stoi(v[2]);
				int rotate = stoi(v[3]);

				// cout<<"reached place piece"<<endl;
				int y = stoi(v[4]);
				int x = stoi(v[5]);
				// cout<<"reached place piece"<<endl;
				placepiece(opponent_piece,flip,rotate,x,y, false); // input do -1 here for 0 based
				// cout<<"BOARD AFTER OPPENENT MOVE"<<endl;
				if(isMyFirstMove){
					if(x == 4){
						// opponent played at 4,4
						vector<vector<int> > move {{20-1,0,0,9,9,10}};
						makeBestMove(move);  // nth piece index is n-1
					}
					else{
						// opp played at 9,9
						vector<vector<int> > move {{20-1,0,0,4,4,10}};
						makeBestMove(move);  // nth piece index is n-1
					}
					isMyFirstMove=false;
				}
				else{
					
					vector<vector<int>> validMoves = getValidMoves();
					makeBestMove(validMoves);
				}
				
				// printBoard();
			}

		
	}

	return 0;

}