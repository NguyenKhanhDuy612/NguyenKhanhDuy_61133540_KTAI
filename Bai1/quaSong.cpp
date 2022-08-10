#include <stdio.h>
#include <iostream>
#include <queue>
#include <conio.h>
#include <unistd.h>
#include <string>
#include <algorithm>
using namespace std;
struct State{
	int stt;
	string bankStart;
	string bankDes;
};
queue <State> OPEN;
State CLOSE[1000];
int nCLOSE = 0;
int STT = 0;
State start;
State vet[1000];
State duongdi[1000];
void setup()
{
	start.stt = 1;
	start.bankStart = "ctbm";// c: la cao, t là tho, b là bap cai, m là nguoi
	start.bankDes = "";
	STT++;
}
bool KTClose (State t)
{
	for (int i = 0; i < nCLOSE; i++)
		if (CLOSE[i].bankStart.compare(t.bankStart) == 0 && CLOSE[i].bankDes.compare(t.bankDes) == 0)
			return true;
	return false;
}

bool check(string bank)
{
	if ((bank.find("t")<5 && bank.find("b")<5 && bank.find("c")>5 && bank.find("m")>5) ||
		 (bank.find("t")<5 && bank.find("c")<5 && bank.find("b")>5 && bank.find("m")>5))
		return false;
	return true;
}

void display(State t)
{
	cout<<t.bankStart<<endl<<"----"<<endl;	
	cout<<endl<<"----"<<endl;
	cout<<t.bankDes<<endl<<endl<<endl;
}

void RiverCrossing()
{
	OPEN.push(start);
	State current = start;
	int n = 0;
	while (OPEN.empty() == false && current.bankStart != "")
	{
		OPEN.pop();
		CLOSE[nCLOSE] = current;
		nCLOSE++;
		
		
		if (current.bankStart.find("m") < 5)
		{
			
			State tam;		
			for (int i = 0; i < current.bankStart.length()-1; i++)
			{
				tam = current;
				tam.bankDes += tam.bankStart[i];
				tam.bankStart.erase(i,1);
				tam.bankStart.erase(tam.bankStart.find("m"),1);
				tam.bankDes += 'm';
				sort(tam.bankStart.begin(),tam.bankStart.end());
				sort(tam.bankDes.begin(),tam.bankDes.end()-1);
				if (KTClose(tam) == false && check(tam.bankStart) == true)
				{
					STT++;
					tam.stt = STT;
					vet[STT] = current;
					OPEN.push(tam);
				}					
			}
			tam = current;	
			tam.bankStart.erase(tam.bankStart.find("m"),1);
			tam.bankDes += 'm';	
			sort(tam.bankStart.begin(),tam.bankStart.end());
			sort(tam.bankDes.begin(),tam.bankDes.end()-1);
			if (KTClose(tam) == false && check(tam.bankStart) == true)
			{
				STT++;
				tam.stt = STT;
				vet[STT] = current;
				OPEN.push(tam);
			}		
		}
		else
		{
			if (current.bankDes.find("m") < 5)
			{
				
				State tam;			
				for (int i = 0; i < current.bankDes.length()-1; i++)
				{
					tam = current;
					tam.bankStart += tam.bankDes[i];
					tam.bankDes.erase(i,1);
					tam.bankDes.erase(tam.bankDes.find("m"),1);
					tam.bankStart += 'm';
					sort(tam.bankStart.begin(),tam.bankStart.end()-1);
					sort(tam.bankDes.begin(),tam.bankDes.end());
					if (KTClose(tam) == false  && check(tam.bankDes) == true)
					{
						STT++;
						tam.stt = STT;
						vet[STT] = current;
						OPEN.push(tam);
					}
				}
				tam = current;	
				tam.bankDes.erase(tam.bankDes.find("m"),1);
				tam.bankStart += 'm';	
				sort(tam.bankStart.begin(),tam.bankStart.end()-1);
				sort(tam.bankDes.begin(),tam.bankDes.end());
				if (KTClose(tam) == false && check(tam.bankDes) == true)
				{
					STT++;
					tam.stt = STT;
					vet[STT] = current;
					OPEN.push(tam);
				}
			}
				
		}
		n++;		
		current = OPEN.front();		
	}
	State t = current;
	duongdi[0] = current;
	int step = 1;
	do
	{
		t = vet[t.stt];
		duongdi[step] = t;
		step++;
	}
	while (start.bankStart.compare(t.bankStart) != 0 && start.bankDes.compare(t.bankDes) != 0);
	for (int j = step - 1; j >= 0; j--)
	{
		system("cls");
		display(duongdi[j]);
		sleep(5);		
	}
		
}
int main()
{
	setup();
	RiverCrossing();	
}

