#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using intvec = std::vector<int>;

struct fighter {
	int hp;
	int armor;
	int damage;
	int mana;
	int shield_count;
	int poison_count;
	int recharge_count;
};

enum result { YOU, BOSS, NEITHER };

int spellcosts[] = {53,73,113,173,229};

bool hard = false;

void apply_effects(fighter &you, fighter &boss) {
	if (you.shield_count) {
		you.shield_count -= 1;
		if (you.shield_count == 0)
				you.armor -= 7;
	}
	if (you.poison_count) {
		you.poison_count -= 1;
		boss.hp -= 3;
	}
	if (you.recharge_count) {
		you.recharge_count -= 1;
		you.mana += 101;
	}
}

// One round.
result fight(fighter &you, fighter &boss, int spell, int &cost) {
	if (hard) {
		you.hp -= 1;
		if (you.hp <= 0)
			return BOSS;
	}
	apply_effects(you, boss);
	if (boss.hp <= 0)
		return YOU;
	if (you.mana < spellcosts[spell]) {
		return BOSS;
	}

	you.mana -= spellcosts[spell];
	cost += spellcosts[spell];
	switch (spell) {
	case 0: // Magic missile
		boss.hp -= 4;
		break;
	case 1: // Drain
		boss.hp -= 2;
		you.hp += 2;
		break;
	case 2: // Shield
		you.armor += 7;
		you.shield_count = 6;
		break;
	case 3: // Poison
		you.poison_count = 6;
		break;
	case 4: // Recharge
		you.recharge_count = 5;
		break;
	}
	if (boss.hp <= 0)
		return YOU;
	
	apply_effects(you, boss);
	if (boss.hp <= 0)
		return YOU;
	you.hp -= std::max(1, boss.damage - you.armor);
	if (you.hp <= 0)
		return BOSS;

	return NEITHER;
}

void play(fighter you, fighter boss, int mana, intvec &mana_win) {
	for (int s = 0; s < 5; s += 1) {
		if (s == 2 && you.shield_count > 1) {
			continue;
		} else if (s == 3 && you.poison_count > 1) {
			continue;
		} else if (s == 4 && you.recharge_count > 1) {
			continue;
		} else {
			fighter savedyou = you, savedboss = boss;
			int savedmana = mana;
			result r = fight(you, boss, s, mana);
			if (r == YOU) {
				mana_win.push_back(mana);
			} else if (r == BOSS) {
			} else if (r == NEITHER) {
				play(you, boss, mana, mana_win);
			}
			you = savedyou; boss = savedboss; mana = savedmana;
		}
	}
}

int main(int argc, char **argv) {
	// Probably should read the boss's stats from stdin, but...
	fighter you = {50, 0, 0, 500, 0, 0, 0}, boss = {58,0,9,0,0,0,0};
	intvec mana_win;
	hard = argc == 2;
	play(you, boss, 0, mana_win);
	auto m = std::min_element(mana_win.begin(), mana_win.end());
	if (m != mana_win.end()) 
		std::cout << "Minimum mana expenditure: " << *m << '\n';
	else
		std::cout << "No winner!\n";
	
	return 0;
}