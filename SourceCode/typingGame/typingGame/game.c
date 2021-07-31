/*
모듈의 기능 : 게임 플레이
버전 : v1.5
개발자 : 안현종
최종수정일 : 2018. 6. 8.
*/

#include "game.h"
#include "header.h"

int combo;
int score;

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void game()
{
	/*int level = 0;*/
	int after_game = 0;
	srand(time(NULL)); // 난수 생성

	while (1)
	{
		/*level = printmenu();

		playgame(level);

		after_game = showresult();

		if (after_game == 2)
		{
		system("cls"); Print_Menu(); break;
		}
		if (after_game == 3)
		break; */

		playgame(printmenu()); /// 단순화

		after_game = showresult(); /// 받는 부분에서 showresult()로 받으니 여러변 실행되서 after_game 으로 다시 복구

		if (after_game == 2) ///
		{
			system("cls"); Print_Menu(); break;
		}
		else if (after_game == 3) /// 
			break;
		system("cls");
	}

	system("cls");
}

int printmenu()
{
	int level = 0; ///레벨 변수 초기화

	do ///레벨 오류 발생 디폴트 값을 위한 반복문 삽입
	{
		system("cls"); draw_square(); ///화면 틀에 맞추는 작업중

		gotoxy(17, 5); ///

		printf("어느 키로 플레이하겠습니까?\n\n");
		gotoxy(3, 20); /// 좌표 이동 및 텍스트 일부 수정
		printf("1. 상단부\n");
		gotoxy(3, 21); ///
		printf("2. 중단부\n");
		gotoxy(3, 22); ///
		printf("3. 하단부\n");
		gotoxy(3, 23);
		printf("4. 테스트용(1만 나옴)\n");

		/*gotoxy(29, 1);
		scanf("%d", &level);*/
		level = _getch() - '0'; ///엔터 없이 바로 입력 받을 수 있게 수정

		switch (level)
		{
		case 1:gotoxy(33, 21); printf("1.상단부"); Sleep(200); break;
		case 2:gotoxy(33, 21); printf("2.중단부"); Sleep(200); break;
		case 3:gotoxy(33, 21); printf("3.하단부"); Sleep(200); break;
		default: gotoxy(33, 21); printf("잘못된 입력 입니다.\n"); Sleep(100); break;
		}
	} while (level > 4 || level < 1);

	return level;
}

void playgame(int level)
{
	char input = 0; // 키 입력
	char alphabet[11] = { NULL };
	char key[10] = { NULL }; // 게임 도중에 입력해야 하는 것
	int i;
	int life; // 목숨
	char heart[10] = "♥♥♥";
	int how_many_key;
	int hp;
	int hit = 0;
	char health[22] = "■■■■■■■■■■";
	char bonus[3] = "x1";
	clock_t old_time, cur_time;

	switch (level)
	{
	case 1:
		how_many_key = 10;
		strcpy(alphabet, "qwertyuiop");
		for (i = 0; i < 10; i++)
			key[i] = alphabet[rand() % how_many_key];
		break;
	case 2:
		how_many_key = 9;
		strcpy(alphabet, "asdfghjkl ");
		for (i = 0; i < 10; i++)
			key[i] = alphabet[rand() % how_many_key];
		break;
	case 3:
		how_many_key = 7;
		strcpy(alphabet, "zxcvbnm   ");
		for (i = 0; i < 10; i++)
			key[i] = alphabet[rand() % how_many_key];
		break;
	default:
		break;
	}

	system("cls"); draw_square(); ///화면 지우고 틀 출력

	life = 3; // 목숨은 3개
	score = 0;
	combo = 0;
	hp = 100;

	while (1)
	{
		switch (life) // 목숨 시각화
		{
		case 3:
			strcpy(heart, "♥♥♥");
			break;
		case 2:
			strcpy(heart, "♥♥♡");
			break;
		case 1:
			strcpy(heart, "♥♡♡");
			break;
		default:
			break;
		}

		switch (hp / 10)
		{
		case 9:
			strcpy(health, "■■■■■■■■■■");
			break;
		case 8:
			strcpy(health, "■■■■■■■■■□");
			break;
		case 7:
			strcpy(health, "■■■■■■■■□□");
			break;
		case 6:
			strcpy(health, "■■■■■■■□□□");
			break;
		case 5:
			strcpy(health, "■■■■■■□□□□");
			break;
		case 4:
			strcpy(health, "■■■■■□□□□□");
			break;
		case 3:
			strcpy(health, "■■■■□□□□□□");
			break;
		case 2:
			strcpy(health, "■■■□□□□□□□");
			break;
		case 1:
			strcpy(health, "■■□□□□□□□□");
			break;
		case 0:
			strcpy(health, "■□□□□□□□□□");
			break;
		default:
			break;
		}

		if (hp == 0)
			strcpy(health, "                     ");

		gotoxy(20, 5); /// 위치 변경
		for (i = 0; i < 10; i++) //입력받을 거 표기
			printf("%c ", key[i]);

		gotoxy(20, 8);
		printf("%s", health);

		gotoxy(4, 20); ///위치 변경
		printf("Score : %d", score); // 점수 표기

		gotoxy(4, 22); ///위치 변경
		if (combo >= 50)
			textcolor(5);
		else if (combo >= 30 && combo < 50)
			textcolor(1);
		else if (combo >= 10 && combo < 30)
			textcolor(9);
		printf("%d Combo %s", combo, bonus);
		textcolor(7);

		gotoxy(42, 20);  ///위치 변경
		printf("~Life~"); ///목숨 표기
		gotoxy(42, 22);
		textcolor(4);
		printf("%s", heart); ///목숨 표기
		textcolor(7);

		old_time = clock();

		gotoxy(20, 6); ///위치 변경
		input = getch(); // 키 입력받기
		cur_time = clock();
		gotoxy(19, 11);
		printf("                                ");
		gotoxy(29, 11); ///위치 변경 
		printf("%c", input); ///입력받은거 출력

		if (((double)(cur_time - old_time) / CLOCKS_PER_SEC) > 5)
		{
			gotoxy(19, 11);
			printf("입력시간 초과! 목숨 -1");
			life--;
			combo = 0;
		}

		if (input == key[0]) // 맞으면
		{
			for (i = 0; i < 9; i++)
				key[i] = key[i + 1]; // 키 배열 한칸씩 앞으로 땡기기
			key[9] = alphabet[rand() % how_many_key];
			combo++; // 콤보 +1
			if (hp > 0)
				if (combo % 10 == 0)
					hp--;
			if (combo >= 50)
			{
				score = score + 4;
				strcpy(bonus, "x4");
			}
			else if (combo >= 30 && combo < 50)
			{
				score = score + 3;
				strcpy(bonus, "x3");
			}
			else if (combo >= 10 && combo < 30)
			{
				score = score + 2;
				strcpy(bonus, "x2");
			}
			else
				score++;

			if (hp > 0)
				hit++;
			if (hit == 2)
			{
				hp--;
				hit = 0;
				if (hp <= 0) {
					gotoxy(13, 10);
					printf("몬스터 퇴치 성공! 보너스 +100점 확정!");
					score += 100;
				}
			}


		}
		else
		{
			for (i = 0; i < 9; i++) //틀렸으면
				key[i] = key[i + 1]; // 키 배열 한칸씩 앞으로 땡기기
			key[9] = alphabet[rand() % how_many_key];
			combo = 0; // 콤보 초기화
			gotoxy(3, 22); ///위치 변경
			printf("                    "); //콤보표시 잘리는걸 방지
			life--; // 목숨 -1
		}
		if (life == 0) // 목숨 0이면
			break; // 게임 종료
	}
}

int showresult()
{
	int menu = 0;///

	do {
		system("cls"); draw_square(); ///지우고 틀 출력

		gotoxy(22, 5); ///좌표 수정
		printf("게임 점수 : %d\n\n", score);

		gotoxy(3, 20); ///
		printf("1. 게임 다시하기\n");
		gotoxy(3, 21); ///
		printf("2. 메뉴로 돌아가기\n");
		gotoxy(3, 22); ///
		printf("3. 게임 종료\n");

		/*scanf("%d", &menu);*/
		menu = _getch() - '0'; ///엔터 없이 바로 입력 받을 수 있게 수정

		switch (menu) ///스위치문 추가
		{
		case 1:	gotoxy(33, 21); printf("게임 다시하기\n"); Sleep(500); break;
		case 2: gotoxy(33, 21); printf("메뉴로 돌아가기\n"); Sleep(500); break;
		case 3:	gotoxy(33, 21); printf("게임 종료\n"); Sleep(500); break;
		default:gotoxy(33, 21); printf("잘못된 입력 입니다.\n"); Sleep(100); break;
		}

		level_update(score);

	} while (menu > 3 || menu < 1); ///메뉴 오류 디폴트 값을 위한 반복문 추가

	return menu;
}

void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
