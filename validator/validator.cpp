#include<iostream>
#include<fstream>

using namespace std;

class SudokoGrid{
	
	int sudoko[9][9];
	
	public: SudokoGrid(){
		menu();
	}
	
	private:
		void menu(){
			
			cout<<"\n---------------------------\n";
			cout<<"			Sudoko Solver          ";
			cout<<"\n----------------------------\n";
			
			cout<<"Before we start, please provide an Input\n\n";
			cout<<"Either, \n";
			cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
			cout<<"\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";
			cout<<"\t The file must not have a name more than 20 characters.\n";
			cout<<"\t The file must be in the same directory as this C++ file. \n";
			cout<<"\t The files must have all 81 values seperated with spaces\n";
			cout<<"\t Blank cells must be filled in as 0 (eg: 1 0 0 2 0 0..). \n";
			
			int opt;
			cin>>opt;
			
			if(opt == 1){
				readValue();
			}
			else if(opt == 2){
				readValueFile();
			}
			else{
				while(true){
					cout<<"\n you may have entered an invalid option. Try again/. \n";
					cout<<"\t";
					
					cin>>opt;
					if(opt == 1){
						readValue();
					}
					else if(opt == 2){
						readValueFile();
					}
					else{
						continue;
					}
					break;
				}
			}
		}
		
		void readValue(){
			cout<<"\n Enter the specified value when prompted. \n";
			cout<<"Enter 0 if cell is empty.\n\n";
			
			int rowI, colI;
			
			for(rowI = 0;rowI < 9;rowI++){
				
				for(colI = 0;colI < 9;colI++){
					
					int enteredValue;
					
					cout<<"Enter value for cell["<<rowI+1<<"]["<<colI+1<<"]";
					cin>>enteredValue;
					
					if(!(enteredValue >= 1 and enteredValue <= 9)){
						while(true){
							cout<<"You have entered the wrong value. Try again. \n";
							cout<<"Enter value for cell ["<<rowI+1<<"]["<<colI+1<<"] ";
							cin>>enteredValue;
						}
						
						if(enteredValue >= 1  and enteredValue <= 9){
							break;
						}
					}
					
					sudoko[rowI][colI] = enteredValue;
				}
				
				cout<<"---------\n";
			}
		}
		
		void readValueFile()
		{
			char filename[30];
			
			cout<<"Enter the name of the file that contains the Sudoko puzzle. \n";
			cin>>filename;
			
			ifstream sudokoFile;
			sudokoFile.open(filename, ios::in);
			
			int rowI, colI;
			
			for(rowI = 0;rowI < 9;rowI++){
				
				for(colI = 0;colI < 9;colI++){
					
					int readValue;
					sudokoFile>>readValue;
					
					sudoko[rowI][colI] = readValue;
					
					if(sudokoFile.eof()){
						break;
					}
				}
			}
			
			if(colI*rowI != 81){
				cout<<"The file does not have the required amount of values. \n";
				cout<<"Try again. \n";
				exit(0);
			}
			sudokoFile.close();
		}
		
	public: 
		int getValue(int r, int c){
			return sudoko[r][c];
		}
};

class SudokoValidator{
	
	SudokoGrid grid;
	
	public:
		SudokoValidator(){
			validateGrid();
		}
		
	private:
		void validateGrid(){
			
			if(valueValid()){
				if(rowValid()){
					if(colValid()){
						if(ThreeByThreeValid()){
							cout<<"Your puzzle is valid. \n\n";
						}
						else{
							cout<<"Your puzzle is invalid. \n\n";
						}
					}
					else{
						cout<<"Your puzzle is invalid. \n\n";
					}
				}
				else{
					cout<<"Your puzzle is invalid. \n\n";
				}
			}
			else{
				cout<<"Your puzzle is invalid. \n\n";
			}
		}		
		
		bool valueValid(){
			int rowI, colI;
			
			for(rowI = 0;rowI < 9;rowI++){
				
				for(colI = 0;colI < 9;colI++){
					int cellVal = grid.getValue(rowI, colI);
					if(!(cellVal >= 0 and cellVal <= 9)){
						return false;
					}
				}
			}
			return true;
		}
		
		bool rowValid(){
			
			int rowI, colI, valI;
			
			for(rowI = 0;rowI < 9;rowI++){
				
				for(valI = 1;valI <= 9;valI++){
					if(rowHas(rowI, valI) == false){
						return false;
					}
				}
			}
			return true;
		}
		
		bool colValid(){
			
			int rowI, colI, valI;
			
			for(colI = 0;colI < 9;colI++){
				for(valI = 1;valI <= 9;valI++){
					if(!colHas(colI,valI)){
						return false;
					}
				}
			}
			return true;
		}
		
		bool ThreeByThreeValid(){
			int sqI, valI;
			
			for(sqI = 0;sqI < 9;sqI++){
				for(valI = 1;valI <= 9;valI++){
					if(!sqHas(sqI, valI)){
						return false;
					}
				}
			}
			return true;
		}
		
		bool rowHas(int r, int val){
			
			int colI;
			for(colI = 0;colI < 9;colI++){
				if(grid.getValue(r, colI) == val){
					return true;
				}
			}
			return false;
		}
		
		bool colHas(int c, int val){
			
			int rowI;
			
			for(rowI = 0;rowI < 9;rowI++){
				if(grid.getValue(rowI, c)==val){
					return true;
				}
			}
			return false;
		}
		
		bool sqHas(int sqNum, int val){
			int rowS = (sqNum/3)*3;
			int rowE = rowS + 2;
			
			int colS = (sqNum/3)*3;
			int colE = colS+2;
			
			int rowI, colI;
			for(rowI = rowS;rowI <= rowE;rowI++){
				for(colI = colS;colI <= colE;colI++){
					if(grid.getValue(rowI, colI) == val){
						return true;
					}
				}
			}
			
			return false;
		}
};

int main(){

	SudokoValidator SV;
	return 0;
}
