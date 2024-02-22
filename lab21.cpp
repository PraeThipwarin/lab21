#include "lab21.h"
  
int main(){
	srand(time(0));
	
	string name;	
	cout << "Please input your name: ";
	getline(cin,name);	
	Unit hero("Hero",name);
	
	Equipment sword(0,8,4);
	Equipment axes(0,16,-3);
	Equipment shield(0,-1,7);
	Equipment armor(25,-2,2);
	
	char eq;	
	cout << " [1] Sword \n [2] Axes \n [3] Shield \n [4] Armor \n";
	cout << "Please selet your equipment: ";
	cin >> eq;
	switch (eq)
	{case '1':hero.equip(&sword);
		break;
	case '2':hero.equip(&axes);
		break;
	case '3':hero.equip(&shield);
		break;
	case '4':hero.equip(&armor);
		break;
	default:break;
	}
	
	
	Unit mons("Monster","Kraken");
	
	int turn_count = 1;
	char player_action = '\0',monster_action = '\0';
	int p = 0, m = 0;
	while(true){
		mons.newTurn();	
		hero.newTurn();			
		mons.showStatus();
		drawScene(player_action,p,monster_action,m);
		hero.showStatus();		
		cout << "[A] Attack [H] Heal [G] Guard [D] Dodge [C] Change Equipment [E] Exit";
		cout << "\n[Turn " << turn_count << "] Enter your action: ";
		cin >> player_action;
		player_action = toupper(player_action);
		if(player_action == 'E') break; 
		
		int temp = rand()%5;
		if(temp <= 1) monster_action = 'A';
		else if(temp == 2) monster_action = 'G';
		else if(temp == 3) monster_action = 'D';
		else if(temp == 4) monster_action = 'U';
		
		if(player_action == 'G') hero.guard();
		if(monster_action == 'G') mons.guard();
		
		if(player_action == 'D') hero.dodge();
		if(monster_action == 'D') mons.dodge();
		
		if(player_action == 'H') p = hero.heal();
		
		if(player_action == 'C'){
			char eq;	
			cout << " [1] Sword \n [2] Axes \n [3] Shield \n [4] Armor \n";
			cout << "Please select your equipment: ";
			cin >> eq;
				switch (eq)
				{case '1':hero.equip(&sword);
					break;
				case '2':hero.equip(&axes);
					break;
				case '3':hero.equip(&shield);
					break;
				case '4':hero.equip(&armor);
					break;
				}
		}
		
		if(player_action == 'A') p = hero.attack(mons); 
		if(monster_action == 'A') m = mons.attack(hero); 
		if(monster_action == 'U') m = mons.ultimateAttack(hero); 
		
		if(hero.isDead()){
			drawScene(player_action,p,monster_action,m);
			playerLose();
			break; 
		}
		
		if(mons.isDead()){
			drawScene(player_action,p,monster_action,m);
			playerWin();
			break; 
		}
		
		turn_count++;
	}
	return 0;
}
