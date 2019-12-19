#include "AllGame.h"

BattleGame b;
GeneralKnowledgeQuiz gkq;
LiarGame lie;
Question q;
MathPuzzle mp;
Dungeon d;
Professor p;
UpDownGame ud;
wordPuzzle wp;

int main()
{

	while (1)
	{
		TitleScene();
		int MenuCord = SelectMenu();
		if (MenuCord == 0)
		{
			system("cls");

			// 게임 시작
			b.BattleGameStart(10, 1);
			if (b.check)
			{
				system("cls");

				lie.LiarGameStart();
				if (lie.check)
				{
					system("cls");
					srand((unsigned int)time(NULL));

					q.mathstart(q.getq1());
					q.mathstart(q.getq2());
					q.mathstart(q.getq3());
					cin.ignore();

					if (q.check)
					{
						system("cls");
						srand((unsigned int)time(NULL));
						q.nonsensestart(q.getq());

						if (q.check)
						{
							system("cls");
							mp.GameStart();
							if (mp.check)
							{
								cout << "탈출하셨습니다!" << endl;
								exit(1);
							}
							else
							{
								cout << "실패!" << endl;
								break;
							}
						}
					}

				}

			}
			else
			{
				break;
			}
			

		}
		else if (MenuCord == 1)
		{
			// 게임 정보
			infomenu();

		}
		else if (MenuCord == 2)
		{
			// 게임 종료
			return 0;
		}
		system("cls");
	}

	return 0;
}
