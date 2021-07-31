/*
����� ��� : ���� �÷���
���� : v1.5
������ : ������
���������� : 2018. 6. 8.
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
	srand(time(NULL)); // ���� ����

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

		playgame(printmenu()); /// �ܼ�ȭ

		after_game = showresult(); /// �޴� �κп��� showresult()�� ������ ������ ����Ǽ� after_game ���� �ٽ� ����

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
	int level = 0; ///���� ���� �ʱ�ȭ

	do ///���� ���� �߻� ����Ʈ ���� ���� �ݺ��� ����
	{
		system("cls"); draw_square(); ///ȭ�� Ʋ�� ���ߴ� �۾���

		gotoxy(17, 5); ///

		printf("��� Ű�� �÷����ϰڽ��ϱ�?\n\n");
		gotoxy(3, 20); /// ��ǥ �̵� �� �ؽ�Ʈ �Ϻ� ����
		printf("1. ��ܺ�\n");
		gotoxy(3, 21); ///
		printf("2. �ߴܺ�\n");
		gotoxy(3, 22); ///
		printf("3. �ϴܺ�\n");
		gotoxy(3, 23);
		printf("4. �׽�Ʈ��(1�� ����)\n");

		/*gotoxy(29, 1);
		scanf("%d", &level);*/
		level = _getch() - '0'; ///���� ���� �ٷ� �Է� ���� �� �ְ� ����

		switch (level)
		{
		case 1:gotoxy(33, 21); printf("1.��ܺ�"); Sleep(200); break;
		case 2:gotoxy(33, 21); printf("2.�ߴܺ�"); Sleep(200); break;
		case 3:gotoxy(33, 21); printf("3.�ϴܺ�"); Sleep(200); break;
		default: gotoxy(33, 21); printf("�߸��� �Է� �Դϴ�.\n"); Sleep(100); break;
		}
	} while (level > 4 || level < 1);

	return level;
}

void playgame(int level)
{
	char input = 0; // Ű �Է�
	char alphabet[11] = { NULL };
	char key[10] = { NULL }; // ���� ���߿� �Է��ؾ� �ϴ� ��
	int i;
	int life; // ���
	char heart[10] = "������";
	int how_many_key;
	int hp;
	int hit = 0;
	char health[22] = "�����������";
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

	system("cls"); draw_square(); ///ȭ�� ����� Ʋ ���

	life = 3; // ����� 3��
	score = 0;
	combo = 0;
	hp = 100;

	while (1)
	{
		switch (life) // ��� �ð�ȭ
		{
		case 3:
			strcpy(heart, "������");
			break;
		case 2:
			strcpy(heart, "������");
			break;
		case 1:
			strcpy(heart, "������");
			break;
		default:
			break;
		}

		switch (hp / 10)
		{
		case 9:
			strcpy(health, "�����������");
			break;
		case 8:
			strcpy(health, "�����������");
			break;
		case 7:
			strcpy(health, "�����������");
			break;
		case 6:
			strcpy(health, "�����������");
			break;
		case 5:
			strcpy(health, "�����������");
			break;
		case 4:
			strcpy(health, "�����������");
			break;
		case 3:
			strcpy(health, "�����������");
			break;
		case 2:
			strcpy(health, "�����������");
			break;
		case 1:
			strcpy(health, "�����������");
			break;
		case 0:
			strcpy(health, "�����������");
			break;
		default:
			break;
		}

		if (hp == 0)
			strcpy(health, "                     ");

		gotoxy(20, 5); /// ��ġ ����
		for (i = 0; i < 10; i++) //�Է¹��� �� ǥ��
			printf("%c ", key[i]);

		gotoxy(20, 8);
		printf("%s", health);

		gotoxy(4, 20); ///��ġ ����
		printf("Score : %d", score); // ���� ǥ��

		gotoxy(4, 22); ///��ġ ����
		if (combo >= 50)
			textcolor(5);
		else if (combo >= 30 && combo < 50)
			textcolor(1);
		else if (combo >= 10 && combo < 30)
			textcolor(9);
		printf("%d Combo %s", combo, bonus);
		textcolor(7);

		gotoxy(42, 20);  ///��ġ ����
		printf("~Life~"); ///��� ǥ��
		gotoxy(42, 22);
		textcolor(4);
		printf("%s", heart); ///��� ǥ��
		textcolor(7);

		old_time = clock();

		gotoxy(20, 6); ///��ġ ����
		input = getch(); // Ű �Է¹ޱ�
		cur_time = clock();
		gotoxy(19, 11);
		printf("                                ");
		gotoxy(29, 11); ///��ġ ���� 
		printf("%c", input); ///�Է¹����� ���

		if (((double)(cur_time - old_time) / CLOCKS_PER_SEC) > 5)
		{
			gotoxy(19, 11);
			printf("�Է½ð� �ʰ�! ��� -1");
			life--;
			combo = 0;
		}

		if (input == key[0]) // ������
		{
			for (i = 0; i < 9; i++)
				key[i] = key[i + 1]; // Ű �迭 ��ĭ�� ������ �����
			key[9] = alphabet[rand() % how_many_key];
			combo++; // �޺� +1
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
					printf("���� ��ġ ����! ���ʽ� +100�� Ȯ��!");
					score += 100;
				}
			}


		}
		else
		{
			for (i = 0; i < 9; i++) //Ʋ������
				key[i] = key[i + 1]; // Ű �迭 ��ĭ�� ������ �����
			key[9] = alphabet[rand() % how_many_key];
			combo = 0; // �޺� �ʱ�ȭ
			gotoxy(3, 22); ///��ġ ����
			printf("                    "); //�޺�ǥ�� �߸��°� ����
			life--; // ��� -1
		}
		if (life == 0) // ��� 0�̸�
			break; // ���� ����
	}
}

int showresult()
{
	int menu = 0;///

	do {
		system("cls"); draw_square(); ///����� Ʋ ���

		gotoxy(22, 5); ///��ǥ ����
		printf("���� ���� : %d\n\n", score);

		gotoxy(3, 20); ///
		printf("1. ���� �ٽ��ϱ�\n");
		gotoxy(3, 21); ///
		printf("2. �޴��� ���ư���\n");
		gotoxy(3, 22); ///
		printf("3. ���� ����\n");

		/*scanf("%d", &menu);*/
		menu = _getch() - '0'; ///���� ���� �ٷ� �Է� ���� �� �ְ� ����

		switch (menu) ///����ġ�� �߰�
		{
		case 1:	gotoxy(33, 21); printf("���� �ٽ��ϱ�\n"); Sleep(500); break;
		case 2: gotoxy(33, 21); printf("�޴��� ���ư���\n"); Sleep(500); break;
		case 3:	gotoxy(33, 21); printf("���� ����\n"); Sleep(500); break;
		default:gotoxy(33, 21); printf("�߸��� �Է� �Դϴ�.\n"); Sleep(100); break;
		}

		level_update(score);

	} while (menu > 3 || menu < 1); ///�޴� ���� ����Ʈ ���� ���� �ݺ��� �߰�

	return menu;
}

void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
