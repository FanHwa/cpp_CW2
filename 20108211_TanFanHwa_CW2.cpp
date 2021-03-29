#include <stdio.h>      
#include <stdlib.h>    
#include <time.h> 
#include <iostream>
#include <string>
#include <iomanip>

//Name: Tan Fan Hwa
//ID: 20108211
//OWA: sayft1

using namespace std;

// Struct for the information of the User
struct Information{
    string name;
    string id;
    string edu_level;
    string program;
    string grade;
    string year_completion;
};

// Struct to generate the block
struct Block {
    int block_num;
    string prev_block_hash;
    string curr_block_hash;
    string next_block_hash;
    string timestamp;
    struct Information info;
};

// Declare Global variable used in the program
const int MAX = 50;
string hashArr[MAX];
Block blockArr[MAX];

// Declare functions that used in the program
void printMenu();
Block createNewBlock(int *block_count);
string generate_random_hash();
void printBlock(Block block);
void printAllBlock(int *block_count);
string generateInfoString(Information info);
void editBlock(int *block_count);
string getCurrentTime();
void deleteBlock(int *block_count);


// Main program
int main(){
    //Declare variable used Main
    int menu;
    bool end=true, addBlock;
    char check_end = 'y', check_add = 'y';
    int block_count = 0;

    srand(20108211);
    system("cls");

    // Main Code for the program
    while (end) {

        //Printing out menu
        printMenu();
        cin>>menu;

        system("cls");

        // If the user input is '1' the program will create a new block for the user to input information
        // If the user input is '2' the program will print out all the blocks
        // If the user input is '3' the program will ask th user which block top edit
        // If the user input is '4' the program will quit
        if(menu==1){
            addBlock = true;
            while(addBlock) {
                //Creating new block
                blockArr[block_count]=createNewBlock(&block_count);
                block_count++;
                system("cls");
                
                cout<<"Do you want to continue to add block?  (ENTER 'y' to continue add new block, ENTER others keys return to menu)"<<endl;
                cin>>check_add;

                if(check_add == 'y' || check_add == 'Y') {
                    addBlock = true;
                }
                else addBlock = false;
                
                system("cls");

            }

        }
        else if (menu==2){

            editBlock(&block_count);

            system("cls");

        }
        else if (menu==3) {

            deleteBlock(&block_count);
            block_count = block_count -1 ;

            system("cls");
        }
        else if(menu==4) {

            //Print out all the blocks
            printAllBlock(&block_count);

            //Ask user whether want to continue or quit the program
            cout<<"\n\nDo you want to continue? (ENTER 'y' to back to menu, ENTER others keys to quit program)\n";
            cin>>check_end;
            if((check_end == 'y' || check_end == 'Y') ){
                end = true;
            }
            else end =false;
        
            system("cls");
        }
        else if(menu==5){
            end=false;
        }
        else {
            //Notify user that the input is invalid
            cout<<"Invalid Input !!! Please Choose again\n";
        }

    }

    // Notify user already quit the program
    system("cls");
    cout<<"You already quit the program\n"<<endl;
    return 0;
}

// Void function to print out the menu
void printMenu(){
    cout<<"1.Add new block"<<endl;
    cout<<"2.Edit Block"<<endl;
    cout<<"3.Delete Block"<<endl;
    cout<<"4.Print out all blocks"<<endl;
    cout<<"5.Quit program"<<endl;
    cout<<"Please choose your option: ";
}

// Funtion to get the information input from the user the store them into a block
Block createNewBlock(int *block_count) {
    Block newBlock;
    Information newInformation;
    string newHash; 
    bool checkValid=true;
    char tempChar ='y';

    //Generate a new hash and store in the hashArr for the use to track the sequence of the blocks
    hashArr[*block_count] = generate_random_hash();
    
    while(checkValid){
        cout<<"Enter new Block\n\n";

        //Get input from the user
        cout<<"Please Enter Your Name: \n";
        cin.ignore();
        getline(cin, newInformation.name);

        cout<<"Please Enter Your ID: \n";;
        getline(cin, newInformation.id);
    
        cout<<"Please Enter the edu level (eg. Grade 10 (Form 4), Grade 12(A-Level), UG Semester 1...): \n";
        getline(cin, newInformation.edu_level);

        cout<<"Please Enter Your Major (e.g. Sciene, BSC Computer Science...): \n";
        getline(cin, newInformation.program);

        cout<<"Please Enter Your Grade (e.g. 89% / 3.80 for CGPA): \n";
        getline(cin, newInformation.grade);
    
        cout<<"Date of completion (2020-08-04): \n";
        getline(cin, newInformation.year_completion);

        system("cls");

    
        newBlock.block_num = blockArr[*block_count-1].block_num + 1;
    
        newBlock.curr_block_hash = hashArr[*block_count];

        //Update next block hash on previous block
        blockArr[*block_count-1].next_block_hash = newBlock.curr_block_hash;
    
        //If the current block id the first block the previous hash will be the current hash
        newBlock.prev_block_hash = blockArr[*block_count-1].curr_block_hash;
        if(*block_count==0) {
            newBlock.prev_block_hash=newBlock.curr_block_hash;
        }

        newBlock.next_block_hash = newBlock.curr_block_hash;

        newBlock.timestamp = getCurrentTime();

        newBlock.info = newInformation;


        system("cls");

        printBlock(newBlock);
        cout<<"\nAre the information enter correct? (ENTER 'y' if correct, ENTER other keys to re-enter information)\n";
        cin>>tempChar;

        if(tempChar == 'y' || tempChar == 'Y') {
            checkValid = false;
        }
        else checkValid = true;
        system("cls");

    }
    
    return newBlock;
}

// Function to generate a random hash
string generate_random_hash() {
    int tempNum;
    char tempChar;
    string newHash;

    
    //The first two and last two of the hash string will be alphabet, others will be number
    for(int i=0; i<8; i++) {
        tempNum = rand()% 9 + 0;

        if(i<2 || i>5) {
            tempChar = 'A' + tempNum;
            newHash += tempChar ;
        }
        else {
            newHash += to_string(tempNum);
        }
    }
    

    return newHash;
}

void printBlock(Block block) {

    cout<<"Block "<<block.block_num<<" \t|";
    cout<<block.prev_block_hash<<" \t|";
    cout<<block.curr_block_hash<<" \t|";
    cout<<block.next_block_hash<<" \t|";
    cout<<"Timestamp: "<<block.timestamp<<" \t|";
    cout<< generateInfoString(block.info) <<" \t|"<<endl;

}

//Funtion to print oot all the blocks
void printAllBlock(int *block_count){
    cout<<*block_count<<endl;
    string nextHash = blockArr[0].curr_block_hash;
    string currHash = blockArr[0].curr_block_hash;
    int count=0;
    //The program will print out the block by referring the sequence of the hash in HashArr

    for(int i=0; i<*block_count; i++) {
        
        for(int j=0; j<*block_count; j++) {
            if(blockArr[j].curr_block_hash == nextHash && blockArr[j].prev_block_hash == currHash) {
                nextHash = blockArr[j].next_block_hash;
                currHash = blockArr[j].curr_block_hash;
                printBlock(blockArr[j]);
                count++;
            }
            
        }
        if(count == *block_count) {
                break;
        }
    }
    
}

string generateInfoString(Information tempInfo) {
    
    string infoString;
    infoString = tempInfo.name + ", " + tempInfo.id + ", " + tempInfo.edu_level + ", Major: " + tempInfo.program + ", Grade/CGPA: " + tempInfo.grade + 
                    ", Completion Date: " + tempInfo.year_completion;
    
    return infoString;
}

//Funtion to edit existing Block
void editBlock(int *block_count){
    int option, x, y=*block_count;
    bool checkValid = true, checkEdit=true;
    char tempChar = 'y';
    Block tempBlock;
    Information tempInfomation;
    
    while(checkValid) {

        //Print out all blocks
        printAllBlock(&y); 

        //Let user choose which block to edit
        cout<<"\nWhich block do you want to edit? (1,2,3...)\n";
        cin>>x;

        //Check whether the block choose is exist or not.
        if(x>y || x<=0) {
            checkValid = true;
            system("cls");
            cout<<"Invalid input Plase choose again !!!"<<endl;
        }
        //Input new data to the chosen block
        else{
            system("cls");
            checkEdit = true;
            tempInfomation = blockArr[x-1].info;
            while(checkEdit) {
                cout<<"Edit Block "<<x<<"\n\n";
                cout<<"1. Name: "<<tempInfomation.name<<endl;
                cout<<"2. Studenty ID: "<<tempInfomation.id<<endl;
                cout<<"3. Edu Level: "<<tempInfomation.edu_level<<endl;
                cout<<"4. Program: "<<tempInfomation.program<<endl;
                cout<<"5. Grade: "<<tempInfomation.grade<<endl;
                cout<<"6. Date of completion: "<<tempInfomation.year_completion<<endl;

                cout<<"\nWhich data do you want to edit?\n";
                cin>>option;

                switch(option) {
                    case 1:
                        cout<<"\nPlease Enter New Name: \n";
                        cin.ignore();
                        getline(cin, tempInfomation.name);
                        checkEdit = false;
                        break;
                    case 2:
                        cout<<"Please Enter New ID: \n";
                        cin.ignore();
                        getline(cin, tempInfomation.id);
                        checkEdit = false;
                        break;
                    case 3:
                        cout<<"Please Enter new edu level (eg. Grade 10 (Form 4), Grade 12(A-Level), UG Semester 1...): \n";
                        cin.ignore();
                        getline(cin, tempInfomation.edu_level);
                        checkEdit = false;
                        break;
                    case 4:
                        cout<<"Please Enter new Major (e.g. Sciene, BSC Computer Science...): \n";
                        cin.ignore();
                        getline(cin, tempInfomation.program);
                        checkEdit = false;
                        break;
                    case 5:
                        cout<<"Please Enter new Grade (e.g. 89% / 3.80 for CGPA): \n";
                        cin.ignore();
                        getline(cin, tempInfomation.grade);
                        checkEdit = false;
                        break;
                    case 6:
                        cout<<"New Date of completion (2020-08-04): \n";
                        cin.ignore();
                        getline(cin, tempInfomation.year_completion);
                        checkEdit = false;
                        break;
                    default:
                        system("cls");
                        cout<<"Invalid input Please choose again !!!"<<endl;
                        break;
                }
                
                
                    
            }
            
            blockArr[x-1].info = tempInfomation;

            blockArr[x-1].timestamp = getCurrentTime();

            system("cls");
                cout<<"Block edited successfully !!"<<endl;
                cout<<"Do you want to edit others data? (Enter 'y' to continue edit, Enter others key to retrun main menu)"<<endl;
                cin>>tempChar;

                if(tempChar == 'y' || tempChar == 'Y') {
                    checkValid = true;
                } 
                else {
                    checkValid = false;
                }
                system("cls");
            
            
        } 


    }  

}

string getCurrentTime() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    std::string str(buffer);

    return str;
}

void deleteBlock(int *block_count) {
    int x , y=*block_count;
    bool checkValid=true;
    char tempChar='y';

    while(checkValid) {

        printAllBlock(&y);

        cout<<"\nWhich block do you want to delete?"<<endl;
        cin>>x;

        if( x>y || x<=0) {
            checkValid = true;
            system("cls");
            cout<<"Invalid input Plase choose again !!!"<<endl;
        }
        else {
                blockArr[x-2].next_block_hash = blockArr[x-1].next_block_hash;
                blockArr[x].prev_block_hash = blockArr[x-1].prev_block_hash;
                for(int i=x-1; i<y; i++) {
                    blockArr[i] = blockArr[i+1];
                }
        }
    }
}
