#pragma once
#include <iostream>

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <time.h>
#include <vector>
#include <Windows.h>  

// 메인화면 방향키
#define Up 0
#define Down 1
#define Left 2
#define Right 3
#define submit 4

using namespace std;

// 첫 시작화면
void Gamesize()
{
	system(" mode  con lines=20   cols=80 | title Cube Game ");
}

int keyControl()
{
	int temp = _getch();

	if (temp == 'w' || temp == 'W')
	{
		return Up;

	}
	if (temp == 's' || temp == 'S')
	{
		return Down;

	}
	if (temp == ' ')
	{
		return submit;
	}
}

void  TitleScene()
{

	printf("\n\n\n\n");
	printf("                      *--------------------------------*                        \n");
	printf("                          ####  #   #  ####   #####                             \n");
	printf("                         #      #   #  #   #  #                                 \n");
	printf("                         #      #   #  #####  #####                             \n");
	printf("                         #      #   #  #   #  #                                 \n");
	printf("                          ####  #####  ####   #####                             \n");
	printf("                      *--------------------------------*                        \n");
	printf("\n\n\n\n");

}

void gotoxy(int x, int y)
{
	HANDLE consolHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consolHandle, pos);

}

int SelectMenu()
{

	int x = 33;
	int y = 12;

	gotoxy(x - 2, y);
	printf(">  게임 시작");
	gotoxy(x, y + 1);
	printf(" 게임 정보");
	gotoxy(x, y + 2);
	printf(" 종료");

	while (1)
	{
		int n = keyControl();
		switch (n)
		{
		case Up:
		{
			if (y > 12)
			{
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");

			}
			break;
		}
		case Down:
		{
			if (y < 14)
			{
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");

			}
			break;
		}
		case submit:
		{
			return y - 12;
		}
		}
	}
	return 0;
}

void infomenu()
{
	system("cls");

	while (1)
	{
		printf("\n\n\n");
		printf("             당신은 큐브에 갇혀있습니다!\n");
		printf("             각방의 퀴즈를 풀거나 장애물을 무사히 통과하여\n");
		printf("             큐브를 탈출 하십시오!\n");
		printf("\n\n\n");
		printf("             행운을 빕니다.\n\n");
		printf("             메인화면으로 돌아가려면 space키를 눌러주세요.\n");

		if (keyControl() == submit)
		{
			break;

		}
	}

}



class BattleGame 
{
public:
	int HP;
	bool check;

public:
	BattleGame() {};
	void GetHp() { cout << "♥ 당신의 체력 : " << HP << endl; } // 플레이어의 남은 HP를 출력하는 함수
	void GetEnemyHp() { cout << "⊙ 괴물의 체력 : " << HP << endl; } // 적의 남은 HP를 출력하는 함수
	void damage(int x) { HP = HP - x; } // 객체의 HP를 감소시키는 함수
	void BattleGameStart(int x, int y) // 게임 실행 함수 (첫 번째 인수는 플레이어의 체력, 두 번째 인수는 적의 체력)
	{
		// 스토리 및 룰 설명
		cout << "---------------------------------------------------------------------------------------\n" << endl;
		cout << "당신은 어둡고 불쾌한 통로를 지나 다음 방의 입구에 도착했습니다." << endl;
		cout << "문이 소리없이 열리더니 또다시 칠흑과 같은 어둠이 펼쳐집니다." << endl;
		cout << "당신은 조심스럽게 방 안으로 들어갑니다." << endl;
		cout << "눈이 점점 어둠에 적응하자 저 멀리 방의 출구쪽에 커다란 형체가 보이기 시작합니다." << endl;
		cout << "괴물이 출구를 막은 채로 잠들어 있었습니다. 당신은 괴물을 처치하고 다음 방으로 나아가기로 결심합니다.\n" << endl;

		cout << "방의 규칙 1. 네 개의 주사위 중 하나를 선택해 굴린다." << endl;
		cout << "방의 규칙 2. 규칙 1을 두 번 더 반복한다." << endl;
		cout << "방의 규칙 3. 세 주사위 값을 모두 더한만큼 괴물에게 다가갈 수 있다. (최대 10걸음)" << endl;
		cout << "방의 규칙 4. 가까이 갈수록 괴물에게 큰 피해를 준다. 단, 걸음 수가 너무 적거나 (1~6), 10을 넘으면 당신의 체력이 감소한다.\n" << endl;
		cout << "---------------------------------------------------------------------------------------\n" << endl;

		// 플레이어와 적 객체 생성, 함수 호출 시 받은 인수를 체력으로 설정
		BattleGame player;
		BattleGame enemy;
		player.HP = x;
		enemy.HP = y;

		// 게임 진행에 필요한 변수들
		int selectNum = 0; // 주사위 번호 선택
		int diceSum = 0; // 주사위 총합
		int diceTry = 0; // 주사위 굴린 횟수 (3이 되면 주사위 굴리기 반복 종료)
		int randResult; // 랜덤값을 여기에 저장 (0~4 주사위는 나온 값 바로 사용, 1/2 확률 주사위는 경우의 수로 사용)
		int diceResult; // 경우의 수에 의해 선택된 주사위 결과값을 여기에 저장

		srand((unsigned int)time(NULL)); // 무작위성 극대화를 위한 시드값 설정

		// 아래 코드는 주사위 3회 선택 및 총합 계산
		while (player.HP > 0 && enemy.HP > 0)
		{
			player.GetHp();
			enemy.GetEnemyHp();
			diceSum = 0;

			while (diceTry < 3)
			{
				diceTry++;
				cout << "\n[굴릴 주사위의 번호를 입력하세요.]\n" << endl;
				cout << "▷남은 주사위 횟수 : " << 4 - diceTry << " 회" << endl;
				cout << "▶현재 주사위의 합 : " << diceSum << "\n" << endl;
				cout << "1. 0 ~ 4 주사위 " << endl;
				cout << "2. 1 or 6 주사위 " << endl;
				cout << "3. 0 or 3 주사위 " << endl;
				cout << "4. 모든 면이 5인 주사위\n " << endl;
				cout << "굴릴 주사위 번호 : " << endl;
				cin >> selectNum;

				if (selectNum == 1) // 1번 주사위를 선택할 경우
				{
					diceResult = (rand() % 5);
					diceSum = diceSum + diceResult;
					cout << "\n\n\n=====================================" << endl;
					cout << "주사위를 굴려 " << diceResult << " 이(가) 나왔습니다." << endl;
					cout << "=====================================" << endl;
				}
				else if (selectNum == 2) // 2번 주사위를 선택할 경우
				{
					randResult = (rand() % 2);
					if (randResult == 0)
					{
						diceResult = 1;
					}
					else
					{
						diceResult = 6;
					}

					diceSum = diceSum + diceResult;
					cout << "\n\n\n\n=====================================" << endl;
					cout << "주사위를 굴려 " << diceResult << " 이(가) 나왔습니다." << endl;
					cout << "=====================================" << endl;
				}
				else if (selectNum == 3) // 3번 주사위를 선택할 경우
				{

					randResult = (rand() % 2);
					if (randResult == 0)
					{
						diceResult = 0;
					}
					else
					{
						diceResult = 3;
					}

					diceSum = diceSum + diceResult;
					cout << "\n\n\n\n=====================================" << endl;
					cout << "주사위를 굴려 " << diceResult << " 이(가) 나왔습니다." << endl;
					cout << "=====================================" << endl;
				}
				else if (selectNum == 4) // 4번 주사위를 선택할 경우
				{
					diceSum = diceSum + 5;
					cout << "\n\n\n=====================================" << endl;
					cout << "주사위를 굴려 5 가 나왔습니다." << endl;
					cout << "=====================================" << endl;
				}
				else
				{
					cout << "\n\n\n==========================================" << endl;
					cout << "\nERROR : 잘못된 번호입니다. 다시 입력하세요.\n" << endl;
					cout << "==========================================" << endl;
					diceTry--;
					selectNum = 0;
				}

			}

			cout << "\n주사위의 총합은 " << diceSum << " 입니다." << endl;
			diceTry = 0;

			// 아래로 주사위 총합에 따른 데미지 판정 코드

			if (diceSum > 12) // 주사위 총합이 13이상일 경우
			{
				player.damage(2);
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
				cout << "너무 가까이 다가가서 괴물에게 강하게 공격당했습니다. 당신이 겨우 입구까지 도망가자 괴물은 다시 자리로 돌아가 잠들었습니다." << endl;
				cout << "당신의 체력이 2 감소합니다." << endl;
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
			}
			else if (diceSum == 12 || diceSum == 11) // 주사위 총합이 11~12일 경우
			{
				player.damage(1);
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
				cout << "다가가던 도중 괴물에게 들켜 공격당했습니다. 당신이 입구까지 도망가자 괴물은 다시 자리로 돌아가 잠들었습니다." << endl;
				cout << "당신의 체력이 1 감소합니다." << endl;
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
			}
			else if (diceSum == 10) // 주사위 총합이 10일 경우
			{
				enemy.damage(30);
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
				cout << "들키지않고 괴물에게 다가가 있는 힘껏 공격했습니다. 괴물은 고통에 몸부림치다가 다시 잠들었습니다." << endl;
				cout << "괴물의 체력이 30 감소합니다." << endl;
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
			}
			else if (diceSum == 9) // 주사위 총합이 9일 경우
			{
				enemy.damage(15);
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
				cout << "잠든 괴물의 몸통을 공격했습니다. 괴물은 주변에 화풀이를 하더니 다시 잠들었습니다." << endl;
				cout << "괴물의 체력이 15 감소합니다." << endl;
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
			}
			else if (diceSum == 8) // 주사위 총합이 8일 경우
			{
				enemy.damage(10);
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
				cout << "잠든 괴물의 꼬리를 공격했습니다. 괴물은 깜짝 놀라서 일어나 주변을 경계하더니 다시 잠들었습니다." << endl;
				cout << "괴물의 체력이 10 감소합니다." << endl;
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
			}
			else if (diceSum < 7) // 주사위 총합이 6이하일 경우
			{
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
				cout << "너무 조심스럽게 다가간 나머지 발을 헛디뎌 넘어졌습니다." << endl;
				cout << "당신의 체력이 1 감소합니다." << endl;
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
				player.damage(1);
			}
			else // 나머지 : 주사위 총합이 7일 경우
			{
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
				cout << "공격하기엔 너무 멉니다. 조금 더 다가가야 할 것 같습니다." << endl;
				cout << "\n----------------------------------------------------------------------------------------------------------------\n" << endl;
			}
		}

		// 게임 엔딩 (둘 중 하나의 체력이 0이 됐을 때, 주사위 반복문을 빠져나와서 엔딩 조건문)

		if (player.HP <= 0) // 패배
		{
			cout << "**********************************************************************" << endl;
			cout << "당신은 괴물을 쓰러트리지 못하고 큐브안에서 비참하게 생을 마감했습니다." << endl;
			cout << "**********************************************************************\n\n" << endl;

			check = false;
		
		}
		else // 승리
		{
			cout << "******************************************************" << endl;
			cout << "괴물은 고통에 몸부림치다가 마침내 움직임을 멈췄습니다. " << endl;
			cout << "******************************************************\n\n" << endl;

			check = true;

		}

	}
};

class GeneralKnowledgeQuiz
{
	string c;
	string p;

public:
	
bool check;

	GeneralKnowledgeQuiz() {}
	void set(string c, string p) { this->c = c; this->p = p; }
	string getC() { return c; }
	string getP() { return p; }
	void letsQuiz_President()
	{
		int correct = 0;
		int wrong = 0;
		srand((unsigned)time(0));
		vector<GeneralKnowledgeQuiz> v;
		string sC[] = { "대한민국","미국","일본","중국","독일","프랑스","영국","필리핀","러시아" };
		string sP[] = { "문재인","트럼프","아베","시진핑","메르켈","마크롱","존슨","두테르테","푸틴" };
		for (int i = 0; i < 9; ++i)
		{
			GeneralKnowledgeQuiz n;
			v.push_back(n);
			v[i].set(sC[i], sP[i]);
		}
		cout << "***** 대통령 이름 맞추기 게임을 시작합니다. *****" << endl;
		for (;;)
		{
			cout << "퀴즈 : 1, 종료 : 2 >>";
			int num; cin >> num;
			if (num == 1)
			{
				for (;;)
				{
					int r = rand() % v.size();
					cout << endl;
					cout << v[r].getC() << "의 국가원수는?";
					string answer;
					cin >> answer;
					if (answer == "again")
						break;
					if (v[r].getP() == answer)
					{
						cout << endl;
						cout << "정답 !!" << endl;
						correct++;
						if (correct > 2)
							check = true;
					}
					else
					{
						cout << endl;
						cout << "읍읍!! 당신들 누구야 ?! ...(이미 잡혀간 도전자입니다.)" << endl;
						check = false;
					}
				}
			}
			else if (num == 2)
			{
				break;
			}
			else
			{
				cout << "입력 오류" << endl;
				break;
			}
		}

	}

	void letsQuiz_Keyword()
	{
		int correct = 0;
		int wrong = 0;
		srand((unsigned)time(0));
		vector<GeneralKnowledgeQuiz> v;
		string sC[] = { "true 혹은 false를 반환하는 자료형 ||","전 범위에서 접근가능한 접근지정자 ||","vector, set, list 중 시퀀스 컨테이너가 아닌것 ||","가상함수를 선언할 때 사용하는 키워드 ||","스마트 포인터를 쓰기위해 포함시켜야 하는 헤더 ||" };
		string sP[] = { "bool","public","set","virtual","memory" };
		for (int i = 0; i < 5; ++i)
		{
			GeneralKnowledgeQuiz n;
			v.push_back(n);
			v[i].set(sC[i], sP[i]);
		}
		cout << "***** 1분반 door에 로그인 했지? *****" << endl;
		for (;;)
		{
			cout << "퀴즈 : 1, 종료 : 2 >>";
			int num; cin >> num;
			if (num == 1)
			{
				for (;;)
				{
					int r = rand() % v.size();
					cout << endl;
					cout << v[r].getC() << " 이 문제에 해당하는 것은?";
					string answer;
					cin >> answer;
					if (answer == "again")
						break;
					if (v[r].getP() == answer)
					{
						cout << endl;
						cout << "정답 !!" << endl;
						correct++;
						if (correct > 2)
							exit(1);
					}
					else
					{
						cout << endl;
						cout << "??? : 교수가 퀴즈 본다고 했는데도 공부를 안해오네?" << endl;
						check = false;
						exit(1);
					}
				}
			}
			else if (num == 2) {
				break;
			}
			else
			{
				cout << "입력 오류" << endl;
				break;
			}
		}

	}
};

class LiarGame
{
public:
	int questionCount;
	int rage;

	bool check;

public:
	LiarGame() : questionCount(0), rage(0) {};
	void countUp() { questionCount++; }
	void rageUp(int x) { rage = rage + x; }
	void LiarGameStart()
	{
		cout << "---------------------------------------------------------------------------------------\n" << endl;
		cout << "당신은 싸늘한 통로를 지나 다음 방의 입구에 도착했습니다." << endl;
		cout << "방 너머에서 누군가가 대화하는 소리가 들립니다." << endl;
		cout << "문이 열리자 당신은 방 안으로 들어갑니다. 다섯명의 사람들이 제각기 다른 표정을 지은채로 대화하고 있습니다." << endl;
		cout << "당신이 들어가자 그들은 대화를 멈추고 일제히 당신을 쳐다봅니다. 그리고 그 중 무표정한 남자가 당신에게 이렇게 말합니다." << endl;
		cout << " \"이봐, 우리 지금 곤란한 상황에 빠져있는데 당신이 해결해 줄 수 있을까?\"" << endl;
		cout << "그는 당신에게 사정을 설명합니다..\n" << endl;
		// 룰 설명
		cout << "방의 규칙 1. 5명 중에 1명은 이 방을 나갈 수 있는 열쇠를 숨기고 있다." << endl;
		cout << "방의 규칙 2. 5명은 각자 당신에게 열쇠의 행방에 대한 힌트를 줄 것이다." << endl;
		cout << "방의 규칙 3. 그러나 이들 중 단 한 명은 거짓말을 하고있다." << endl;
		cout << "방의 규칙 4. 당신은 거짓말을 하는 사람과 열쇠를 갖고 있는 사람을 모두 찾아야 한다." << endl;
		cout << "---------------------------------------------------------------------------------------\n\n" << endl;

		LiarGame Person1;
		LiarGame Person2;
		LiarGame Person3;
		LiarGame Person4;
		LiarGame Person5;
		int selectNum = 0;

		while (Person1.questionCount == 0 || Person2.questionCount == 0 || Person3.questionCount == 0 || Person4.questionCount == 0 || Person5.questionCount == 0)
		{
			cout << "★ 누구의 말을 들어보시겠습니까?\n" << endl;
			cout << "1) 무표정한 남자" << endl;
			cout << "2) 미소를 짓고 있는 여자" << endl;
			cout << "3) 불안한 표정을 짓고 있는 남자" << endl;
			cout << "4) 화난 표정을 짓고 있는 노인" << endl;
			cout << "5) 졸린 표정을 짓고 있는 소녀" << endl;
			cout << "6) 범인 지목하기\n" << endl;

			cin >> selectNum;

			if (selectNum == 1)
			{
				if (Person1.questionCount == 0)
				{
					Person1.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "무표정한 남자는 표정 하나 바꾸지 않고 말합니다." << endl;
					cout << "\"나한테는 열쇠가 없어. 누가 가져간 것을 본 적도 없고 말이야.\"" << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "☆ 다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person1.questionCount == 1)
				{
					Person1.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "무표정한 남자는 무미건조하게 말합니다." << endl;
					cout << "\"뭐야? 나한테는 열쇠가 없다니까? 자꾸 귀찮게 굴지 말라고.\"" << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "☆ 다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person1.questionCount == 2)
				{
					Person1.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "무표정한 남자는 조금 화가난 표정으로 말합니다." << endl;
					cout << "\"난 열쇠도 없고, 너한테 관심도 없으니까 이제 다른 사람한테 가서 물어봐!\"" << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "☆ 다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person1.questionCount >= 3)
				{
					Person1.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "무표정한 남자는 더이상 당신을 상대하려 하지 않습니다." << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "☆ 다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}

			}
			else if (selectNum == 2)
			{
				if (Person2.questionCount == 0)
				{
					Person2.countUp();
					cout << "\n---------------------------------------------------------------------------" << endl;
					cout << "여자는 즐거운 일이라도 있는 듯이 웃으며 말합니다." << endl;
					cout << "\"내가 아까부터 쭉 보고 있었는데, 저기 불안한 표정을 짓고 있는 남자는 열쇠가 없을거야.\"" << endl;
					cout << "---------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person2.questionCount == 1)
				{
					Person2.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "여자는 여전히 웃으며 말합니다." << endl;
					cout << "\"하하, 저 불안한 표정의 남자는 열쇠가 없을거라니까? 내기해도 좋아.\"" << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person2.questionCount == 2)
				{
					Person2.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "여자는 곤란한 듯 웃으며 말합니다." << endl;
					cout << "\"어머, 너 지금 나 의심하는 거야? 정말 저기 불안해 보이는 남자는 열쇠가 없을거야!\"" << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person2.questionCount >= 3)
				{
					Person2.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "여자는 난처한 듯이 웃을 뿐, 더이상 당신을 상대해 주지 않습니다." << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
			}
			else if (selectNum == 3)
			{
				if (Person3.questionCount == 0)
				{
					Person3.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "남자는 금방이라도 울어버릴 것 같은 표정으로 말합니다." << endl;
					cout << "\"저 무서운 노인은 절대 열쇠가 없을거야...\"" << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person3.questionCount == 1)
				{
					Person3.countUp();
					cout << "\n-------------------------------------------------------------------------------------" << endl;
					cout << "남자는 주위의 눈치를 보며 말합니다." << endl;
					cout << "\"저 영감님 아까부터 화만 내고 계셔서 열쇠따윈 관심도 없을거야. 저 사람한테는 없는게 분명해...\"" << endl;
					cout << "-------------------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person3.questionCount == 2)
				{
					Person3.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "남자는 이제 당신에게 짜증내며 말합니다." << endl;
					cout << "\"나한테 왜 그래? 저 노인에게는 열쇠가 없다고 말해줬잖아? 저리 좀 가!\"" << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person3.questionCount >= 3)
				{
					Person3.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "남자는 당신을 노려볼 뿐, 아무 말도 하지 않습니다." << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
			}
			else if (selectNum == 4)
			{
				if (Person4.questionCount == 0)
				{
					Person4.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "노인은 불같이 화를 내며 말합니다." << endl;
					cout << "\"저 싱글거리는 여자는 거짓말을 하고 있어!\"" << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person4.questionCount == 1)
				{
					Person4.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "노인은 길길이 날뛰며 말합니다." << endl;
					cout << "\"저 여자는 거짓말을 하고 있다, 이말이야! 내 말을 못믿는게야?\"" << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person4.questionCount == 2)
				{
					Person4.countUp();
					cout << "\n---------------------------------------------------------------------------" << endl;
					cout << "노인은 길길이 날뛰며 말합니다." << endl;
					cout << "\"젊은 놈이 귀가 먹었어? 저 여자가 거짓말을 하고 있다니까! 이제 썩 꺼져!\"" << endl;
					cout << "---------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person4.questionCount >= 3)
				{
					Person4.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "당신은 노인에게 혼나는 것이 무서워 더이상 말을 걸지 못합니다." << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
			}
			else if (selectNum == 5)
			{
				if (Person5.questionCount == 0)
				{
					Person5.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "소녀은 금방이라도 잠들 것 같은 목소리로 말합니다." << endl;
					cout << "\"열쇠는 저기 웃고 계신 여자분이 들고있어요...\"" << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person5.questionCount == 1)
				{
					Person5.countUp();
					cout << "\n-------------------------------------------------------------------------" << endl;
					cout << "소녀은 당신이 귀찮은 듯이 말합니다." << endl;
					cout << "\"여자분이 열쇠를 들고 있다니까요... 거짓말을 하고 있는 사람은 잘 모르겠고.\"" << endl;
					cout << "-------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person5.questionCount == 2)
				{
					Person5.countUp();
					cout << "\n----------------------------------------------------------------------------------------" << endl;
					cout << "소녀은 눈살을 마구 찌푸리며 말합니다." << endl;
					cout << "\"당신 뭐하는 사람이에요? 같은 말 반복하게 만들지 말고 열쇠 찾고 싶으면 여자분한테 물어보세요.\"" << endl;
					cout << "----------------------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
				else if (Person5.questionCount >= 3)
				{
					Person5.countUp();
					cout << "\n----------------------------------------------------------------------------------------" << endl;
					cout << "소녀은 졸고있는 듯 합니다. 아무래도 깨우면 안될 것 같습니다." << endl;
					cout << "----------------------------------------------------------------------------------------\n" << endl;
					cout << "★다른 사람에게 말을 걸려면 \'엔터키\'를 누르세요." << endl;
					cin.ignore();
					cin.get();
				}
			}
			else if (selectNum == 6)
			{
				Person1.questionCount = 1;
				Person2.questionCount = 1;
				Person3.questionCount = 1;
				Person4.questionCount = 1;
				Person5.questionCount = 1;
				selectNum = 0;
			}
			else
			{
				cout << "잘못된 번호입니다. 다시 입력하세요.\n" << endl;
			}


		}

		do
		{
			cout << "\n==================================================================" << endl;
			cout << "★ 모든 사람의 말을 종합했을 때, 거짓말을 하는 사람은 누구입니까?" << endl;
			cout << "1) 무표정한 남자" << endl;
			cout << "2) 미소를 짓고 있는 여자" << endl;
			cout << "3) 불안한 표정을 짓고 있는 남자" << endl;
			cout << "4) 화난 표정을 짓고 있는 노인" << endl;
			cout << "5) 졸린 표정을 짓고 있는 소녀" << endl;
			cout << "\n==================================================================" << endl;
			cin >> selectNum;

			if (selectNum == 1)
			{
				cout << "\n-------------------------------------------------------------------------" << endl;
				cout << "무표정한 남자는 지목당하자 어이가 없는 표정을 짓습니다." << endl;
				cout << "\"내가 거짓말을 하고 있다고? 아무래도 내가 부탁할 사람을 잘못 고른 것 같군!\"" << endl;
				cout << "-------------------------------------------------------------------------\n" << endl;
				cout << "☆ 지목 실패 : 당신은 방에서 쫓겨나 싸늘한 복도에서 보잘 것 없는 생을 마감했습니다." << endl;

				check = false;
			}
			else if (selectNum == 2)
			{
				cout << "\n-------------------------------------------------------------------------" << endl;
				cout << "미소를 짓던 여자는 지목당하자 표정이 싸늘하게 변합니다." << endl;
				cout << "\"너 미쳤구나? 내가 너한테 웃어주니까 네가 뭐라도 된 것 같지?\"" << endl;
				cout << "-------------------------------------------------------------------------\n" << endl;
				cout << "☆ 지목 실패 : 당신은 방에서 쫓겨나 싸늘한 복도에서 보잘 것 없는 생을 마감했습니다." << endl;

				check = false;
			}
			else if (selectNum == 3)
			{
				cout << "\n-------------------------------------------------------------------------" << endl;
				cout << "불안한 표정의 남자는 지목당하자 당신을 죽일 듯이 노려봅니다." << endl;
				cout << "\"내가 만만해? 네 잘난 탐정 놀이도 여기까지야.\"" << endl;
				cout << "-------------------------------------------------------------------------\n" << endl;
				cout << "☆ 지목 실패 : 당신은 방에서 쫓겨나 싸늘한 복도에서 보잘 것 없는 생을 마감했습니다." << endl;

				check = false;
			}
			else if (selectNum == 4)
			{
				cout << "\n----------------------------------------------------------------------------------------------------------------" << endl;
				cout << "노인은 지목당하자 갑자기 화내기를 멈췄습니다. 이윽고 기괴한 표정을 짓더니 소름끼치는 웃음소리를 내며 어디론가 도망쳤습니다." << endl;
				cout << "\"저건 도대체 뭐였던거지...?\"" << endl;
				cout << "방에 남은 사람들은 저마다 놀란 반응을 보이며 다시 당신에게 주목합니다." << endl;
				cout << "----------------------------------------------------------------------------------------------------------------\n" << endl;
				cout << "☆ 지목 성공! : 생존자들의 큐브 탈출을 방해하는 의문의 존재를 쫓아냈습니다!" << endl;

				check = true;
			}
			else if (selectNum == 5)
			{
				cout << "\n-------------------------------------------------------------------------" << endl;
				cout << "졸린 표정의 소녀는 당신을 비웃습니다." << endl;
				cout << "\"이럴 줄 알았지. 역시 똑똑한 척 하는 것들은 하는 짓도 다 똑같다니깐?\"" << endl;
				cout << "-------------------------------------------------------------------------\n" << endl;
				cout << "☆ 지목 실패 : 당신은 방에서 쫓겨나 싸늘한 복도에서 보잘 것 없는 생을 마감했습니다." << endl;

				check = false;
			}
			else
			{
				cout << "잘못된 번호입니다. 다시 입력하세요.\n" << endl;
			}

		} while (selectNum > 5 || selectNum < 0);

		do
		{
			cout << "\n==================================================================" << endl;
			cout << "★ 모든 사람의 말을 종합했을 때, 열쇠를 가진 사람은 누구입니까?" << endl;
			cout << "1) 무표정한 남자" << endl;
			cout << "2) 미소를 짓고 있는 여자" << endl;
			cout << "3) 불안한 표정을 짓고 있는 남자" << endl;
			cout << "4) 도망친 노인" << endl;
			cout << "5) 졸린 표정을 짓고 있는 소녀" << endl;
			cout << "\n==================================================================" << endl;
			cin >> selectNum;

			if (selectNum == 1)
			{
				cout << "\n-------------------------------------------------------------------------" << endl;
				cout << "무표정한 남자는 지목당하자 어이가 없는 표정을 짓습니다." << endl;
				cout << "\"뭐야? 나한텐 열쇠가 없다고 분명히 말했을텐데? 제정신이 아니군.\"" << endl;
				cout << "-------------------------------------------------------------------------\n" << endl;
				cout << "☆ 지목 실패 : 당신은 방에서 쫓겨나 싸늘한 복도에서 보잘 것 없는 생을 마감했습니다." << endl;

				check = false;
			}
			else if (selectNum == 2)
			{
				cout << "\n---------------------------------------------------------------------------------------------" << endl;
				cout << "미소를 짓던 여자는 지목당하자 미소를 거두고 당황한 기색을 보입니다." << endl;
				cout << "\"무슨 소리야? 내가 열쇠를 숨겼다는 말이야?\"" << endl;
				cout << "여자는 당신을 엉터리라며 매도하기 시작합니다. 그 순간, 여자의 주머니에서 반짝이는 것이 떨어졌습니다." << endl;
				cout << "떨어진 물건은 열쇠였습니다! 당신은 떨어진 열쇠를 낚아채서 방의 출구를 개방했습니다." << endl;
				cout << "---------------------------------------------------------------------------------------------\n" << endl;
				cout << "☆ 탈출 성공! : 여자를 추궁하는 사람들을 남겨둔 채 당신은 다음방으로 통하는 복도를 나아갑니다.\n" << endl;

				check = true;
			}
			else if (selectNum == 3)
			{
				cout << "\n-------------------------------------------------------------------------" << endl;
				cout << "불안한 표정의 남자는 지목당하자 " << endl;
				cout << "\"당신 똑똑한 줄 알았는데, 이제보니 영 아니잖아?\"" << endl;
				cout << "-------------------------------------------------------------------------\n" << endl;
				cout << "☆ 지목 실패 : 당신은 방에서 쫓겨나 싸늘한 복도에서 보잘 것 없는 생을 마감했습니다." << endl;

				check = false;
			}
			else if (selectNum == 4)
			{
				cout << "\n----------------------------------------------------------------------------------------------------------------" << endl;
				cout << "당신은 도망친 노인이 열쇠를 가지고 있다고 말했습니다." << endl;
				cout << "\"뭐? 그게 말이 되는 소리라고 생각해?\"" << endl;
				cout << "----------------------------------------------------------------------------------------------------------------\n" << endl;
				cout << "☆ 지목 실패 : 당신은 방에서 쫓겨나 싸늘한 복도에서 보잘 것 없는 생을 마감했습니다." << endl;

				check = false;
			}
			else if (selectNum == 5)
			{
				cout << "\n-------------------------------------------------------------------------" << endl;
				cout << "졸린 표정의 소녀는 당신을 업신여기며 말합니다." << endl;
				cout << "\"정말 멍청한 사람이 따로 없네요.\"" << endl;
				cout << "-------------------------------------------------------------------------\n" << endl;
				cout << "☆ 지목 실패 : 당신은 방에서 쫓겨나 싸늘한 복도에서 보잘 것 없는 생을 마감했습니다." << endl;

				check = true;
			}
			else
			{
				cout << "잘못된 번호입니다. 다시 입력하세요.\n" << endl;
			}
		} while (selectNum < 0 || selectNum > 5);
	}
};

class Question_Math
{
private:
	int num1, num2, num3, answer, randnum;
	char oper1, oper2;

public:
	Question_Math()
	{
		num1 = rand() % 15 + 1;
		num2 = rand() % 15 + 1;
		num3 = rand() % 15 + 1;

		setoper1();
		setoper2();

		setanswer();
	}

	int getnum1()
	{
		return num1;
	}
	int getnum2()
	{
		return num2;
	}
	int getnum3()
	{
		return num3;
	}
	char getoper1()
	{
		return oper1;
	}
	char getoper2()
	{
		return oper2;
	}
	int getrandnum()
	{
		return randnum;
	}

	void setnum1()
	{

	}
	void setnum2()
	{

	}
	void setnum3()
	{

	}
	void setoper1()
	{
		randnum = rand() % 2;
		if (randnum == 0) oper1 = '+';
		else if (randnum == 1) oper1 = '-';
	}
	void setoper2()
	{
		randnum = rand() % 2;
		if (randnum == 0) oper2 = '+';
		else if (randnum == 1) oper2 = '-';
	}
	void setanswer()
	{
		if (oper1 == '+')
		{
			if (oper2 == '+') answer = num1 + num2 + num3;
			else if (oper2 == '-') answer = num1 + num2 - num3;
		}
		else if (oper1 == '-')
		{
			if (oper2 == '+') answer = num1 - num2 + num3;
			else if (oper2 == '-') answer = num1 - num2 - num3;
		}

	}

	//문제 보기
	void printquestion()
	{
		cout << num1 << " " << "□" << " " << num2 << " " << "□" << " " << num3 << " " << " = " << answer << endl;
	}

	//정답 보기
	void printanswer()
	{
		cout << num1 << " " << oper1 << " " << num2 << " " << oper2 << " " << num3 << " " << " = " << answer;
	}

};

class Question_Nonsense
{
private:
	string question[6];
	string answer[6];
	int randnum;

public:
	Question_Nonsense()
	{
		setquestion();
		setanswer();
		randnum = rand() % 4 + 1;
	}
	string getquestion()
	{
		return *question;
	}
	string getanswer(int num)
	{
		return answer[num];
	}
	int getrandnum()
	{
		return randnum;
	}
	//문제초기화
	void setquestion()
	{
		question[0] = "모든 사람을 일으키는 숫자는? ";
		question[1] = "곰들이 목욕하는 곳은? ";
		question[2] = "(나는 5살이 아니야)를 다섯 글자로(힌트 : 나라이름) ";
		question[3] = "사람들이 가장 좋아하는 영화는 ";
		question[4] = "오백에서 백을 빼면 ";
		question[5] = "할아버지가 제일 좋아하는 돈은? ";
	}
	//정답초기화
	void setanswer()
	{
		answer[0] = "다섯";
		answer[1] = "곰탕";
		answer[2] = "오세아니아";
		answer[3] = "부귀영화";
		answer[4] = "오";
		answer[5] = "할머니";
	}

	void printquestion(int num)
	{
		cout << "문제 : " << question[num] << endl;
	}

	void printanswer(int num)
	{
		cout << "정답 : " << answer[num] << endl;
	}

};

class Question
{
private:
	Question_Math q1;
	Question_Math q2;
	Question_Math q3;
	char mathanswer1, mathanswer2;

	Question_Nonsense qn;
	string nonsenseanswer;

public:
	bool check;

	Question()
	{

	}
	Question_Math getq1()
	{
		return q1;
	}
	Question_Math getq2()
	{
		return q2;
	}
	Question_Math getq3()
	{
		return q3;
	}
	Question_Nonsense getq()
	{
		return qn;
	}

	char getmathanswer1()
	{
		return mathanswer1;
	}
	char getmathanswer2()
	{
		return mathanswer2;
	}
	string getnonanswer()
	{
		return nonsenseanswer;
	}

	void setmathanswer1()
	{
		cin >> mathanswer1;
	}
	void setmathanswer2()
	{
		cin >> mathanswer2;
	}
	void setnoneanswer()
	{
		getline(cin, nonsenseanswer);
	}

	//수학문제보기
	void showmathquestion(Question_Math q)
	{
		q.printquestion();
	}
	//넌센스문제보기
	void shownonsensequestion(Question_Nonsense q, int num)
	{
		q.printquestion(num);
	}

	//수학정답 보기
	void showmathanswer(Question_Math q)
	{
		q.printanswer();
	}
	//넌센스정답 보기
	void shownonsenseanswer(Question_Nonsense q, int num)
	{
		q.printanswer(num);
	}

	//수학정답 입력
	void mathsolution()
	{
		cout << "첫번째 정답 : ";
		setmathanswer1();
		cout << "두번째 정답 : ";
		setmathanswer2();
	}
	//넌센스 정답 입력
	void nonsensesoulution()
	{
		cout << "정답 : ";
		setnoneanswer();
	}

	//수학정답 판별
	void mathresult(Question_Math q)
	{
		if (q.getoper1() == mathanswer1 && q.getoper2() == mathanswer2)
		{
			cout << endl << "*********";
			q.printanswer();
			cout << "*********" << endl;
			cout << "**********정답입니다!!!**********" << endl << endl;

			check = true;
		}
		else {
			cout << endl << "*********";
			q.printanswer();
			cout << "*********" << endl;
			cout << "**********틀렸습니다!!!**********" << endl << endl;

			check = false;
		}
	}
	//넌센스 정답 판별
	void nonsenseresult(Question_Nonsense q, int num)
	{

		if (q.getanswer(num).compare(nonsenseanswer) == 0)
		{
			cout << "**********정답입니다!!!**********" << endl << endl;

			check = true;
		}
		else {
			cout << "**********틀렸습니다!!!**********" << endl << endl;

			check = false;
		}
	}

	//수학게임 시작
	void mathstart(Question_Math q)
	{
		showmathquestion(q);			//문제 제출
		mathsolution();					//문제 풀기
		mathresult(q);					//정답 판별
	}
	//넌센스 게임 시작
	void nonsensestart(Question_Nonsense q)
	{
		shownonsensequestion(q, q.getrandnum());
		nonsensesoulution();
		nonsenseresult(q, q.getrandnum());

		shownonsensequestion(q, q.getrandnum() - 1);
		nonsensesoulution();
		nonsenseresult(q, q.getrandnum() - 1);

		shownonsensequestion(q, q.getrandnum() + 1);
		nonsensesoulution();
		nonsenseresult(q, q.getrandnum() + 1);
	}

};

class MathPuzzle
{
	int puzzleNum[5][5]; //5X5 사이즈의 퍼즐 

	int inputNum;
	int inputCount = 0; //움직인 횟수  
	int number = 1;
	bool congratulation = false;

	int rememberA, rememberB; // Zero 값 위치를 찾아보고 [4][4]에 있지 않으면 0이 들어있는 위치랑 스왑
public:

	bool check;

	void Random()
	{
		srand((unsigned int)time(NULL)); //난수 생성을 위해 현재 시간(초)를 입력 
	}
	void Initialization()
	{
		for (int i = 0; i < 5; i++) //초기 5행 5열의 배열을 1부터 25까지 초기화
		{
			for (int j = 0; j < 5; j++)
			{
				puzzleNum[i][j] = number;
				number++;
			}
		}

		puzzleNum[4][4] = 0; //25가 들어있는[4][4] 번째 위치를 0 값으로 만듦 
	}
	void ShakeNum()
	{
		for (int i = 0; i < 100; i++) //숫자들을 섞음  
		{
			int dest1 = rand() % 5;
			int sour1 = rand() % 5;
			int dest2 = rand() % 5;
			int sour2 = rand() % 5;

			int temp = puzzleNum[dest1][sour1];
			puzzleNum[dest1][sour1] = puzzleNum[dest1][sour2];
			puzzleNum[dest1][sour2] = puzzleNum[dest2][sour1];
			puzzleNum[dest2][sour1] = puzzleNum[dest2][sour2];
			puzzleNum[dest2][sour2] = temp;
			//매번 다른 숫자들로 채움  
		}
	}
	void StarPoint()
	{
		if (puzzleNum[4][4] != 0) //즉 ★의 위치를 결정 
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (puzzleNum[i][j] == 0)
					{
						rememberA = i;
						rememberB = j;
						int temp = puzzleNum[4][4];
						puzzleNum[4][4] = puzzleNum[i][j];
						puzzleNum[i][j] = temp;
					}
				}
			}
		}
	}
	void GameStart()
	{
		while (true) //게임 시작  
		{
			for (int i = 0; i < 5; i++) //★이 행, 렬을 움직이는것처럼 만듦 
			{
				for (int j = 0; j < 5; j++)
				{
					if (puzzleNum[i][j] == 0) //0인 곳을 ★로 대체해 움직이는것처럼 만듦 
					{
						cout << "★" << "\t"; // '/t'는 수평으로 tab을 누른것과 같은 기능 
					}
					else cout << puzzleNum[i][j] << "\t";
				}
				cout << endl;
				cout << endl;
			}

			int checkNumber = 1;
			int checkCount = 0;
			if (!congratulation) //게임이 끝나지 않은경우 
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (puzzleNum[i][j] == checkNumber)
						{
							checkNumber++;
							checkCount++;
						}
					}
				}
				if (checkCount % 25 == 0)
				{
					congratulation = true;
					check = true;
					break;
				}
			}
			else break;

			cout << "현재까지 움직인 횟수 : " << inputCount << endl;
			cout << "움직일 방향의 숫자를 입력하세요." << endl;
			cout << "←(4), ↑(8), →(6), ↓(5)" << endl;
			cin >> inputNum;

			while (true)
			{
				if (!cin.good() || inputNum != 8 && inputNum != 6 && inputNum != 5 && inputNum != 4)
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "다시 입력하세요." << endl;
					cout << "←(4), ↑(8), →(6), ↓(5)" << endl;
					cin >> inputNum;
					cout << endl;
					continue;
				}
				else break;
			}



			if (inputNum == 4) //왼쪽으로 이동 
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (puzzleNum[i][j] == 0 && j > 0)
						{
							int temp = puzzleNum[i][j];
							puzzleNum[i][j] = puzzleNum[i][j - 1];
							puzzleNum[i][j - 1] = temp;
						}
					}
				}
			}

			if (inputNum == 8) //오른쪽으로 이동  
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (puzzleNum[i][j] == 0 && i > 0)
						{
							int temp = puzzleNum[i][j];
							puzzleNum[i][j] = puzzleNum[i - 1][j];
							puzzleNum[i - 1][j] = temp;
						}
					}
				}
			}

			if (inputNum == 6) //위쪽으로 이동 
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (puzzleNum[i][j] == 0 && j < 4)
						{
							int temp = puzzleNum[i][j];
							puzzleNum[i][j] = puzzleNum[i][j + 1];
							puzzleNum[i][j + 1] = temp;
							break;
						}
					}
				}
			}

			if (inputNum == 5) //아래쪽으로 이동 
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (puzzleNum[i][j] == 0 && i < 4)
						{
							int temp = puzzleNum[i][j];
							puzzleNum[i][j] = puzzleNum[i + 1][j];
							puzzleNum[i + 1][j] = temp;
							break;
						}
					}
				}
			}
			system("cls");
			inputCount++;



		}
	}
};

class Dungeon
{
public:
	Dungeon() {};
	void battle()
	{
		int myHp = 800, myAttack = 30, myMp = 10;
		int bossHp = 500, bossAttack = 60, bossMp = 5;
		int myTurn = 0, bossTurn = 0, gamerandom = 0;

		srand(unsigned(time(NULL)));
		while (true)
		{
			system("cls");
			cout << "*******************************************************" << endl;
			cout << "야생의 보스가 출현했습니다." << endl;
			cout << endl;
			cout << endl;
			cout << "나의 체력 : " << myHp << "    " << "보스의 체력 : " << bossHp << endl;
			cout << "나의 공격력 : " << myAttack << "    " << "보스의 공격력 : " << bossAttack << endl;
			cout << "나의 에너지 : " << myMp << "    " << "보스의 에너지 : " << bossMp << endl;
			cout << "1. 공격" << endl;
			cout << "2. 회피" << endl;
			cout << "3. 강화" << endl;
			cout << "4. 회복" << endl;
			cout << "5. 필살기" << endl;
			cout << endl;
			cout << "※ 필살기는 에너지가 50이상 모여야 사용가능하며 회피가 불가능합니다." << endl;
			cout << "※ 공격, 강화, 에너지가 50아래일 때의 필살기를 사용하면 에너지가 10씩 충전됩니다." << endl;
			cout << "※ 공격시 20%의 확률로 추가로 데미지를 줄 수 있습니다.." << endl;
			cout << endl;
			cout << "하나를 선택하세요 : ";
			cin >> myTurn;
			cout << endl;
			bossTurn = rand() % 3 + 1;
			gamerandom = rand() % 5;

			if (myTurn > 5)
			{
				cout << "입력 오류" << endl;
				break;
			}
			else
			{
				switch (myTurn)
				{
				case 1:
					if (gamerandom != 1)
					{
						cout << "플레이어가 보스를 공격했습니다." << endl;
						cout << "-------------------------------------------------------" << endl;
						if (bossTurn == 2)
						{
							cout << endl;
							cout << endl;
							continue;
						}
						else
						{
							bossHp -= myAttack;
						}
						cout << endl;
						cout << endl;
						myMp += 10;
						continue;
					}
					else
					{
						cout << "플레이어가 지원군을 불러옵니다." << endl;
						cout << "-------------------------------------------------------" << endl;
						bossHp -= (myAttack + 10);
						cout << endl;
						cout << endl;
						continue;
					}
				case 2:
					cout << "플레이어가 공격을 방어합니다." << endl;
					cout << "-------------------------------------------------------" << endl;
					cout << endl;
					cout << endl;
					continue;
				case 3:
					cout << "플레이어의 공격력이 10 상승합니다." << endl;
					cout << "-------------------------------------------------------" << endl;
					myAttack += 10;
					cout << endl;
					cout << endl;
					myMp += 10;
					continue;
				case 4:
					cout << "플레이어가 체력을 30 회복합니다." << endl;
					cout << "-------------------------------------------------------" << endl;
					myHp += 30;
					cout << endl;
					cout << endl;
					continue;
				case 5:
					cout << "플레이어가 필살기를 준비합니다." << endl;
					if (myMp >= 50)
					{
						myMp -= 50;
						bossHp -= (myAttack * 3);
					}
					else
					{
						cout << "에너지가 부족하여 충전합니다." << endl;
						myMp += 5;
					}
					cout << "-------------------------------------------------------" << endl;
					cout << endl;
					cout << endl;
					continue;
				}
				switch (bossTurn)
				{
				case 1:
					if (myTurn != 2)
					{
						cout << "보스가 플레이어를 공격했습니다." << endl;
						cout << "-------------------------------------------------------" << endl;
						myHp -= bossAttack;
						bossMp += 5;
						cout << endl;
						cout << endl;
						continue;
					}
					if (myTurn == 2)
					{
						cout << "보스가 플레이어를 공격했습니다." << endl;
						cout << "-------------------------------------------------------" << endl;
						myHp -= (bossAttack - 20);
						cout << endl;
						cout << endl;
						continue;
					}
				case 2:
					cout << "보스가 공격을 방어했습니다." << endl;
					cout << "-------------------------------------------------------" << endl;
					cout << endl;
					cout << endl;
					continue;
				case 3:
					cout << "보스가 필살기를 사용했습니다." << endl;
					cout << "-------------------------------------------------------" << endl;
					if (bossMp >= 50)
					{
						bossMp -= 50;
						myHp -= (bossAttack * 3);
						cout << endl;
						cout << endl;
					}
					else
					{
						cout << "에너지가 부족하여 충전합니다." << endl;
						bossMp += 5;
						cout << endl;
						cout << endl;
					}
					continue;
				}

				system("pause");
				if (bossHp <= 0)
				{
					cout << "☆☆☆☆☆ 승리했습니다. ☆☆☆☆☆" << endl;
					cout << endl;
					break;
				}
				else if (myHp <= 0)
				{
					cout << "††††† 패배했습니다. †††††" << endl;
					cout << endl;
					break;
				}
			}
		}
	}
};

class Professor
{
public:
	Professor() {};
	void villain()
	{
		int myHp = 800, myAttack = 30, myMp = 10;
		int bossHp = 500, bossAttack = 60, bossMp = 5;
		int myTurn = 0, bossTurn = 0, gamerandom = 0;
		srand(unsigned(time(NULL)));
		while (true)
		{
			system("cls");
			cout << "*******************************************************" << endl;
			cout << "주말의 적 김근형교수의 컴퓨터를 해킹하라" << endl;
			cout << "감히 교수한테 도전을 해?" << endl;
			cout << endl;
			cout << endl;
			cout << "우리의 체력 : " << myHp << "    " << "교수님의 체력 : " << bossHp << endl;
			cout << "우리의 공격력 : " << myAttack << "    " << "교수님의 공격력 : " << bossAttack << endl;
			cout << "우리의 에너지 : " << myMp << "    " << "교수님의 에너지 : " << bossMp << endl;
			cout << "1. 공격" << endl;
			cout << "2. 회피" << endl;
			cout << "3. 강화" << endl;
			cout << "4. 회복" << endl;
			cout << "5. 필살기" << endl;
			cout << endl;
			cout << "※ 필살기는 에너지가 50이상 모여야 사용가능하며 회피가 불가능합니다." << endl;
			cout << "※ 공격, 강화, 에너지가 50아래일 때의 필살기를 사용하면 에너지가 10씩 충전됩니다." << endl;
			cout << "※ 공격시 20%의 확률로 추가로 데미지를 줄 수 있습니다.." << endl;
			cout << endl;
			cout << "하나를 선택하세요 : ";
			cin >> myTurn;
			cout << endl;
			bossTurn = rand() % 3 + 1;
			gamerandom = rand() % 5;
			if (myTurn > 5)
			{
				cout << "입력 오류" << endl;
				break;
			}
			else
			{
				switch (myTurn)
				{
				case 1:
					if (gamerandom != 1)
					{
						cout << "김동현이 해킹을 시도합니다." << endl;
						cout << "-------------------------------------------------------" << endl;
						if (bossTurn == 2)
						{
							cout << endl;
							cout << endl;
							break;
						}
						else
						{
							bossHp -= myAttack;
						}
						cout << endl;
						cout << endl;
						myMp += 10;
						break;
					}
					else
					{
						cout << "김동현이 어나니머스에 지원을 요청합니다." << endl;
						cout << "-------------------------------------------------------" << endl;
						cout << endl;
						cout << endl;
						bossHp -= (myAttack + 10);
						break;
					}
				case 2:
					cout << "박재성이 방어벽을 건설합니다." << endl;
					cout << "-------------------------------------------------------" << endl;
					cout << endl;
					cout << endl;
					break;
				case 3:
					cout << "손경수의 버프로 코딩실력이 10 상승합니다." << endl;
					cout << "-------------------------------------------------------" << endl;
					myAttack += 10;
					cout << endl;
					cout << endl;
					myMp += 10;
					break;
				case 4:
					cout << "성시영이 망가진 소스코드를 복구합니다." << endl;
					cout << "-------------------------------------------------------" << endl;
					myHp += 30;
					cout << endl;
					cout << endl;
					break;
				case 5:
					cout << "김민솔이 바이러스프로그램을 준비합니다." << endl;
					if (myMp >= 50)
					{
						myMp -= 50;
						bossHp -= (myAttack * 3);
					}
					else
					{
						cout << "바이러스가 덜 완성되어 제작을 계속합니다." << endl;
						myMp += 5;
					}
					cout << "-------------------------------------------------------" << endl;
					cout << endl;
					cout << endl;
					break;
				}
				switch (bossTurn)
				{
				case 1:
					if (myTurn != 2)
					{
						cout << "교수님이 해킹을 시도합니다." << endl;
						cout << "-------------------------------------------------------" << endl;
						myHp -= bossAttack;
						bossMp += 5;
						cout << endl;
						cout << endl;
						break;
					}
					if (myTurn == 2)
					{
						cout << "교수님이 해킹을 시도합니다." << endl;
						cout << "-------------------------------------------------------" << endl;
						myHp -= 0;
						cout << endl;
						cout << endl;
						break;
					}
				case 2:
					cout << "교수님이 과제 추가로 협박을 시도합니다." << endl;
					cout << "-------------------------------------------------------" << endl;
					cout << endl;
					cout << endl;
					break;
				case 3:
					cout << "교수님이 백신프로그램을 준비합니다." << endl;
					cout << "-------------------------------------------------------" << endl;
					if (bossMp >= 50)
					{
						cout << "Door에 가면 교수가 폭탄을 심어놨어" << endl;
						cout << endl;
						cout << endl;
						bossMp -= 50;
						myHp -= (bossAttack * 3);
					}
					else
					{
						cout << "백신이 덜 완성되어 제작을 계속합니다." << endl;
						cout << "기다려봐 교수가 곧 너희 조 정리할거야." << endl;
						bossMp += 5;
						cout << endl;
						cout << endl;
					}
					break;
				}

				system("pause");
				if (bossHp <= 0)
				{
					cout << "☆☆☆☆☆ 김민솔 조가 무사히 종강을 맞이했습니다. ☆☆☆☆☆" << endl;
					cout << endl;
					break;
				}
				else if (myHp <= 0)
				{
					cout << "††††† 건방지게 교수한테 도전했으니까 레포트 3장씩 써와 †††††" << endl;
					cout << endl;
					break;
				}
			}
		}
	}
};

class UpDownGame
{
	int com;
	int count;
	int chance;
	int min;
	int max;
	int num;


public:
	UpDownGame() {}
	void UpDownNum()
	{
		srand(time(NULL));
		count = 0;
		chance = 5;
		min = 1;
		max = 50;
		com = rand() % max + min;
		cout << "*************** 업/다운 게임 **************" << endl;
		cout << "숫자의 범위 " << min << " " << max << endl;
		cout << "총 " << chance << "번의 기회가 있습니다." << endl;
		cout << "0을 입력하면 프로그램이 종료됩니다." << endl;
		while (count < chance)
		{
			cout << "숫자를 입력하세요 : ";
			cin >> num;
			if (num == 0)
			{
				cout << "게임을 종료합니다." << endl;
				exit(1);
			}
			else if (num<min || num>max)
				cout << "범위 내의 숫자를 입력하시오" << endl;
			else
			{
				count++;
				if (num == com)
				{
					cout << count << "번 시도 끝에 승리했습니다." << endl;
				}
				else if (num > com)
				{
					cout << "틀렸습니다.ㅋ   " << count << "번째 시도 : " << "다운" << endl;
				}
				else if (num < com)
				{
					cout << "틀렸습니다.ㅋ   " << count << "번째 시도 : " << "업" << endl;
				}
				else
					cout << "오류" << endl;
			}
		}
		cout << "패배했습니다... 정답은 : " << com << endl;
		exit(1);
	}

	void UpDownAlphabet()
	{
		char MinAlpa('A');
		char MaxAlpa('Z');
		char alpha;

		srand(time(NULL));

		count = 0;
		chance = 5;
		com = rand() % 26 + 65;
		cout << "*************** 업/다운 게임 **************" << endl;
		cout << "알파벳(대문자)의 범위 " << MinAlpa << " " << MaxAlpa << endl;
		cout << "총 " << chance << "번의 기회가 있습니다." << endl;
		cout << "0을 입력하면 프로그램이 종료됩니다." << endl;
		while (count < chance)
		{
			cout << "알파벳(대문자)을 입력하세요 : ";
			cin >> alpha;
			if (alpha == 'a')
			{
				cout << "게임을 종료합니다." << endl;
				exit(1);
			}
			else if (alpha<MinAlpa || alpha>MaxAlpa)
				cout << "범위 내의 알파벳(대문자)를 입력하시오" << endl;
			else
			{
				count++;
				if (alpha == com)
				{
					cout << count << "번 시도 끝에 승리했습니다." << endl;
				}
				else if (alpha > com)
				{
					cout << "틀렸습니다.ㅋ   " << count << "번째 시도 : " << "다운" << endl;
				}
				else if (alpha < com)
				{
					cout << "틀렸습니다.ㅋ   " << count << "번째 시도 : " << "업" << endl;
				}
				else
					cout << "오류" << endl;
			}
		}
		cout << "패배했습니다... 정답은 : " << com << endl;
		exit(1);
	}

};

class wordPuzzle
{
public:
	wordPuzzle() {};
	int puzzleNum = 0; //정답 갯수를 저장하는 변수 생성  
	char answer[11]; //한글 최대 5글자를 저장할 수 있는 문자열 배열 생성  
	void intro()
	{
		cout << endl;
		cout << "당신의 눈앞에 낱말 퍼즐이 나타났습니다." << endl;
		cout << "자세히 보니 익숙한 단어들이 보이는 것 같습니다." << endl;
		cout << "눈에 띄는 단어를 찾아 입력하면 탈출할 수 있습니다." << endl;
		cout << endl;
		cout << endl;

	}

	void PuzzleMake()
	{
		cout << "	******************************" << endl;
		string puzz1("	멤  아  메  개  맙  편  작  드");  //문자열 배열에 낱말퍼즐 생성  
		string puzz2("	버  루  오  버  로  딩  리  래");
		string puzz3("	함  프  가  느  홀  독  변  수");
		string puzz4("	수  헤  연  웬  다  형  성  조");
		string puzz5("	광  월  산  주  예  배  열  적");
		string puzz6("	일  케  자  셩  슬  체  더  타");
		string puzz7("	주  화  즈  융  생  성  자  사");
		string puzz8("	석  갤  집  퍄  료  웃  표  중");
		cout << puzz1 << endl; cout << endl;
		cout << puzz2 << endl; cout << endl;
		cout << puzz3 << endl; cout << endl;
		cout << puzz4 << endl; cout << endl;
		cout << puzz5 << endl; cout << endl;
		cout << puzz6 << endl; cout << endl;
		cout << puzz7 << endl; cout << endl;
		cout << puzz8 << endl;
		cout << "	******************************" << endl;
		cout << endl;
	}

	void puzzleAnswering()
	{

		cout << "정답을 입력하세요." << endl;
		cout << endl;
		while (true)
		{
			cout << "정답 : ";
			cin >> answer;
			if (strcmp(answer, "멤버함수") == 0) //strcmp(a, b) -> a, b가 같으면 0을, 다르면 0이 아닌 값 출력  
			{
				cout << "정답입니다!" << endl;
				cout << endl;
				puzzleNum++;
			}

			if (strcmp(answer, "오버로딩") == 0)
			{
				cout << "정답입니다!" << endl;
				cout << endl;
				puzzleNum++;
			}

			if (strcmp(answer, "변수") == 0)
			{
				cout << "정답입니다!" << endl;
				cout << endl;
				puzzleNum++;
			}

			if (strcmp(answer, "연산자") == 0)
			{
				cout << "정답입니다!" << endl;
				cout << endl;
				puzzleNum++;
			}

			if (strcmp(answer, "다형성") == 0)
			{
				cout << "정답입니다!" << endl;
				cout << endl;
				puzzleNum++;
			}

			if (strcmp(answer, "배열") == 0)
			{
				cout << "정답입니다!" << endl;
				cout << endl;
				puzzleNum++;
			}

			if (strcmp(answer, "주석") == 0)
			{
				cout << "정답입니다!" << endl;
				cout << endl;
				puzzleNum++;
			}

			if (strcmp(answer, "생성자") == 0)
			{
				cout << "정답입니다!" << endl;
				cout << endl;
				puzzleNum++;
			}

			if (puzzleNum > 7) //정답 8개를 맞추는 순간 반복문 탈출  
				break;

		}

	}

	void puzzleEnd()
	{
		if (puzzleNum > 3)
		{
			system("cls");
			cout << "모든 정답을 맞췄습니다. 다음 방으로 넘어갑니다." << endl;
			Sleep(1000);
		}
	}

};
