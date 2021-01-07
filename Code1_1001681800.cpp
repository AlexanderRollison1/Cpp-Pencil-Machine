//Alexander Rollison 1001681800
#include <iostream>
#define Pencil 60

using namespace std;

bool BuyPencil(int PencilNum, int &StatusMessage,int &PencilInventory, long &ChangeInventory, int RubricRequirement, long amount);
void DisplayMoney(long amount);
void PrintMenu(int &Choice);

enum Status // outside of main as said in FAQ
{
	FAILLetter,//0
	FAILTooMuch,
	FAILTooLittle,
	PASSCorrectInventory,
	FAILLittlePayment,
	FAILBigPayment,
	PASSCorrectAmount,
	PASSCorrectChange,
    FAILInventory//8
};

int main()
{
	int Choice{};
	int PencilNum;
	int StatusMessage{};
    int FLG1{1};
    int FLG2{0};
	long amount{0};
	int PencilInventory{100};
	long ChangeInventory{500};
	int RubricRequirement{0};
    long FinalChange{};

    cout<<"Welcome to my Pencil Machine"<<endl;

	do
	{
		PrintMenu(Choice);
		
		switch(Choice)
		{
			default: 
				cout<<"Invalid menu choice. Please choose again."<<endl;
				break;
			case 0: 
				cout<<"Exiting . . ."<<endl;
				break;
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////				
			case 1: 
				do
				{
                    FLG1 = 1;
                    FLG2 = 0;
                    RubricRequirement = 0;
				    cout<<"\nA pencil costs $0."<<Pencil<<endl;
				    cout<<"\nHow many pencils would you like to purchase? ";
				    cin.clear();
                    cin>>PencilNum;
                    getchar();
                    
				    RubricRequirement = (int)BuyPencil(PencilNum,StatusMessage, PencilInventory, ChangeInventory, RubricRequirement, amount);

					switch(StatusMessage)
					{
						case FAILLetter:
					        do
					        {
						        cout<<"\nInput must be numeric. Please reenter ";
                                cin.clear();
						        cin>>PencilNum;
                                getchar();
						        RubricRequirement = BuyPencil(PencilNum,StatusMessage, PencilInventory, ChangeInventory, RubricRequirement, amount);
					        }
					        while(StatusMessage == FAILLetter);
                            FLG1 = 0;
                            FLG2 = 1;
						    break;
						case FAILTooMuch:
						    cout<<"\nThe machine does not have that many pencils - buy "<<PencilInventory<<" or fewer."<<endl;
                            FLG1 = 0;
                            FLG2 = 0;
						    break;
						case FAILTooLittle:
                            cout<<"\nYou must purchase at least one pencil."<<endl;
                            FLG1 = 0;
                            FLG2 = 0;
                            break;
						case PASSCorrectInventory:
                            FLG1 = 0;
                            FLG2 = 1;
						    break;
                        case FAILInventory:
                        cout<<"\nThe Pencil machine has run out of pencils!"<<endl;
                        break;
					}
				}
				while(StatusMessage != PASSCorrectInventory && RubricRequirement == 0 && FLG1 == 1 && StatusMessage != FAILInventory);
				
                if(FLG1 == 0 && FLG2 == 1)
                {
                    RubricRequirement = 1;
				    cout<<"\nYour total is $";
				    DisplayMoney((long)PencilNum*Pencil);
				    cout<<"\nEnter your payment (in cents) ";
				    cin>>amount;
                    getchar();

				    BuyPencil(PencilNum,StatusMessage, PencilInventory, ChangeInventory, RubricRequirement, amount);

				    switch(StatusMessage)
				    {
					    case FAILLittlePayment:
					        cout<<"\nYou did not enter a sufficient payment. No pencils for you."<<endl;
					        break;
					    case FAILBigPayment:
					        cout<<"\nThis Pencil Dispenser does not have enough change and cannot accept your payment."<<endl;
					        break;
                        case PASSCorrectAmount:
                            cout<<"\nYou bought "<< PencilNum << " pencils for ";
                            DisplayMoney((long)Pencil*PencilNum);
                            cout<<""<<endl;
						    break;
						case PASSCorrectChange:
                            cout<<"\nYou bought "<< PencilNum << " pencils for ";
                            DisplayMoney((long)Pencil*PencilNum);
                            cout<<" with a change of $";
                            FinalChange = amount-(Pencil*PencilNum);
                            DisplayMoney((long)FinalChange);
                            cout<<""<<endl;
				    }
                }
				break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////				
			case 2:
				cout<<"\nThe current inventory is "<<PencilInventory<<endl;
				break;
				
			case 3:
				cout<<"\nThe current change inventory is $";
				DisplayMoney(ChangeInventory);
				break;
		}
	}
	while(Choice!=0);
	
	return 0;
}


bool BuyPencil(int PencilNum, int &StatusMessage,int &PencilInventory, long &ChangeInventory, int RubricRequirement, long amount)
{
    if(PencilInventory == 0)
    {
        StatusMessage = FAILInventory;
        return 0;
    }

	if(RubricRequirement == 0)
	{
		
		if(cin.fail() == 1)
		{
			StatusMessage = FAILLetter;
		}
		else if(PencilNum > PencilInventory)
		{
			StatusMessage = FAILTooMuch;
		}
		else if(PencilNum <= 0 || PencilInventory == 0)
		{
			StatusMessage = FAILTooLittle;
		}
		else if(PencilNum>0 && PencilNum<=PencilInventory)
		{
			StatusMessage = PASSCorrectInventory;
            return 1;
		}
        else
        {
            cout<<"";;
        }
	}
	else if(RubricRequirement == 1)
	{
		if((amount-(Pencil*PencilNum))<0)
		{
			StatusMessage = FAILLittlePayment;
		}
		else if((amount-((Pencil*PencilNum)))>0 && (ChangeInventory - (amount-(Pencil*PencilNum))) < 0)
		{
			StatusMessage = FAILBigPayment;
		}
		else if ((amount-((Pencil*PencilNum)))>0 && (ChangeInventory - (amount-(Pencil*PencilNum))) > 0)
		{
            PencilInventory = PencilInventory - PencilNum;
            ChangeInventory = ChangeInventory - (amount-(Pencil*PencilNum));
		    StatusMessage = PASSCorrectChange;
		}
        else if((amount-(Pencil*PencilNum)) == 0)
		{
            PencilInventory = PencilInventory - PencilNum;
            ChangeInventory = ChangeInventory - (amount-(Pencil*PencilNum));
		    StatusMessage = PASSCorrectAmount;
		}
        else
        {
            return 0;
        }
	}
	return 1;
}

void DisplayMoney(long amount)
{
	string dollars{to_string(amount/100)};
	string cents{to_string(amount%100)};
	cout << dollars << "." << (cents.size() == 1 ? "0" : "") + cents;
	
}

void PrintMenu(int &Choice)
{
	cout<<"\nPlease choose from the following options"<<endl;
		cout<<"\n0. No pencils for me today\n1. Purchase pencils\n2. Check inventory level\n3. Check change level"<<endl;
		cout<<"\nChoice : ";
		cin>>Choice;
}