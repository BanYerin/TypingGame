/*********************
ȭ�� ���÷���
������
v.1.07
2018.5.28
*********************/

//����� ���� ���(����� ���, ����� ���� ����, Ż�� ��)
//����ں� ���ھ�, ���� ���� ��� ��

//�ڵ� ���� �� ���� �����, ����, ������, ���������� �ּ� �ޱ�

//���� - �α���, ���� �����, Ż��, ȭ�� ��ȯ, ����
//�α��� - ���� ����, ��ü ��ŷ �� ���, Ż��, ����

/********************�޸���********************
���� : Ÿ�� ����
!��â���̰� �������� ��Ҹ� �־�ڢ�
���� ���丮 �߰�?
���̵��
gotoxy(29, 5); �׸� �߽�
������ ȸ������ �����ϰ� ������
save_member(void) ���� �����ϱ�
��� �ҽ� �����ϱ�
**********************************************/

#include "header.h"
#include "display.h"
#include "member.h"
#include "game.h"

static int square_type = 3; //ȭ�� �׵θ� Ÿ�� ��ȯ ���� ���� 

extern Member *ptr, *head;		//ȸ����������ü ��� ����Ű�� ������
extern Member *current_user; //���� �α��εǾ��ִ� ������� ȸ�������� ����ִ� ��带 ����Ű�� ������
extern FILE *fp_member; //ȸ������������ ����Ű�� ������

extern score;

void draw_square()
{
	unsigned char square1, square2[7];
	int x, y;

	switch (square_type)
	{
	case 1: square1 = 0xa6; for (int i = 1; i < 7; i++) square2[i] = 0xa0 + i; break; // �� 0xa6 0xa1~0xa7
	case 2: square1 = 0xa1; for (int i = 0; i < 7; i++) square2[i] = 0xe0; break; // �� 0xa1 0xe0
	case 3: square1 = 0xa1; for (int i = 0; i < 7; i++) square2[i] = 0xe1; break; // �� 0xa1 0xe1
	default: break;
	}

	printf("%c%c", square1, square2[3]);
	for (x = 0; x < 27; x++)
	{
		printf("%c%c", square1, square2[1]);
	}
	printf("%c%c", square1, square2[4]);
	printf("\n"); //����

	for (y = 0; y < 15; y++)
	{
		printf("%c%c", square1, square2[2]);
		for (x = 0; x < 27; x++)
			printf("  ");
		printf("%c%c", square1, square2[2]);
		printf("\n");
	} //����

	printf("%c%c", square1, square2[6]);
	for (x = 0; x < 27; x++)
		printf("%c%c", square1, square2[1]);
	printf("%c%c", square1, square2[5]);
	printf("\n"); //����

	printf("%c%c", square1, square2[3]);
	for (x = 0; x < 12; x++)
	{
		printf("%c%c", square1, square2[1]);
	}
	printf("%c%c", square1, square2[4]);
	printf("  ");
	printf("%c%c", square1, square2[3]);
	for (x = 0; x < 12; x++)
	{
		printf("%c%c", square1, square2[1]);
	}
	printf("%c%c", square1, square2[4]);
	printf("\n");//����2

	for (y = 0; y < 6; y++)
	{
		printf("%c%c", square1, square2[2]);
		for (x = 0; x < 12; x++)
			printf("  ");
		printf("%c%c", square1, square2[2]);
		printf("  ");
		printf("%c%c", square1, square2[2]);
		for (x = 0; x < 12; x++)
			printf("  ");
		printf("%c%c", square1, square2[2]);
		printf("\n");
	} //����2

	printf("%c%c", square1, square2[6]);
	for (x = 0; x < 12; x++)
		printf("%c%c", square1, square2[1]);
	printf("%c%c", square1, square2[5]);
	printf("  ");
	printf("%c%c", square1, square2[6]);
	for (x = 0; x < 12; x++)
		printf("%c%c", square1, square2[1]);
	printf("%c%c", square1, square2[5]);
	printf("\n"); //����2
}

void Print_Menu()
{
	int num = 0; //������ ��ȣ

	draw_square();
	popcorn(); ///

	if (current_user == NULL) //�α��� ���� ���¸� //�α��� ���� Ȯ�ιٶ�
	{
		gotoxy(40, 5); ///
		printf("���� ȭ��\n\n"); //��������
		gotoxy(3, 20);
		printf(" 1.�α����ϱ�\n");
		gotoxy(3, 21);
		printf(" 2.���� ����\n");
		gotoxy(3, 22);
		printf(" 3.���� ����\n");
		gotoxy(3, 23);
		printf(" 4.���� ����\n");
	}
	else //�α��� �� ���¸�
	{
		gotoxy(40, 5); ///
		printf("���� ȭ��\n\n"); //��������
		gotoxy(3, 19);
		printf(" 1.���� ����\n");
		gotoxy(3, 20);
		printf(" 2.��ŷ ����\n");
		gotoxy(3, 21);
		printf(" 3.��й�ȣ ����\n");
		gotoxy(3, 22);
		printf(" 4.�α׾ƿ�\n");
		gotoxy(3, 23);
		printf(" 5.�׵θ� ����\n");
		gotoxy(3, 24);
		printf(" 6.���� ����\n");
	}

	num = _getch() - '0';

	if (current_user == NULL)
	{
		Before_Log_in_Menu(num);
	}
	else
	{
		After_Log_in_Menu(num);
	}
}

void Before_Log_in_Menu(int num)
{
	switch (num)
	{
	case 1:gotoxy(33, 21); printf("�α����ϱ�\n"); Sleep(500); system("cls"); login(); Sleep(500); system("cls"); Print_Menu(); break; ///����
	case 2:gotoxy(33, 21); printf("���� ����\n"); Sleep(500); system("cls"); input_data(fp_member); Sleep(500); system("cls"); Print_Menu(); break;
	case 3:gotoxy(33, 21); printf("���� ����\n"); Sleep(500); system("cls"); remov_member(); Sleep(500); system("cls"); Print_Menu(); break;
	case 4:gotoxy(33, 21); printf("���� ����\n"); Sleep(500); system("cls"); save_member(); free(head); close_member(); break;
	default:gotoxy(33, 21); printf("�߸��� �Է� �Դϴ�.\n"); Sleep(50); system("cls"); Print_Menu(); break;
	}
}

void After_Log_in_Menu(int num)
{
	switch (num)
	{
	case 1:gotoxy(33, 21); printf("���� ����\n"); Sleep(500); system("cls"); game(); break;
	case 2:gotoxy(33, 21); printf("��ŷ ����\n"); Sleep(500); system("cls"); print_rank(); system("cls");  Print_Menu(); break; ///Print_Menu()�����־ �߰�����
	case 3:gotoxy(33, 21); printf("��й�ȣ ����\n"); Sleep(500); system("cls"); change_pass(); Sleep(500); system("cls"); Print_Menu(); break; ///
	case 4:gotoxy(33, 21); printf("�α׾ƿ�\n"); Sleep(500); system("cls"); logout(score); Sleep(500); system("cls"); Print_Menu(); break; ///score ����
	case 5:gotoxy(33, 21); printf("�׵θ� ����\n"); Sleep(500); system("cls"); Change_Square(); break;
	case 6:gotoxy(33, 21); printf("���� ����\n"); Sleep(500); system("cls"); save_member(); free(head); break;
	default:gotoxy(33, 21); printf("�߸��� �Է� �Դϴ�.\n"); Sleep(100); system("cls"); Print_Menu(); break;
	}
}

void Change_Square()
{
	int change = 1;

	draw_square();

	do {
		heart();

		gotoxy(3, 19);
		printf("1. ��"); // �� 0xa6 0xa1~0xa7
		gotoxy(3, 20);
		printf("2. �� �׸�"); // �� 0xa1 0xe0
		gotoxy(3, 21);
		printf("3. �׸�"); // �� 0xa1 0xe1
		gotoxy(3, 22);
		printf("4. �ǵ��ư���");

		change = _getch() - '0';

		switch (change)
		{
		case 1: square_type = 1; system("cls"); draw_square(); gotoxy(44, 21); printf("1"); break;
		case 2: square_type = 2; system("cls"); draw_square(); gotoxy(44, 21); printf("2"); break;
		case 3: square_type = 3; system("cls"); draw_square(); gotoxy(44, 21); printf("3"); break;
		case 4: system("cls"); Print_Menu();  break;
		default: gotoxy(33, 21); printf("�߸��� �Է� �Դϴ�.\n"); Sleep(100); system("cls"); draw_square(); break;
		}
	} while (change != 4);
}

void heart()
{
	gotoxy(12, 3);
	printf("    �̢̢�                �̢̢�");
	gotoxy(12, 4);
	printf("  �̢̢̢̢̢�        �̢̢̢̢̢�");
	gotoxy(12, 5);
	printf("�̢̢̢̢̢̢̢�    �̢̢̢̢̢̢̢�");
	gotoxy(12, 6);
	printf("�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�");
	gotoxy(12, 7);
	printf("�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�");
	gotoxy(12, 8);
	printf("�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�");
	gotoxy(12, 9);
	printf("  �̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�");
	gotoxy(12, 10);
	printf("    �̢̢̢̢̢̢̢̢̢̢̢̢̢�  ");
	gotoxy(12, 11);
	printf("      �̢̢̢̢̢̢̢̢̢̢̢�");
	gotoxy(12, 12);
	printf("         �̢̢̢̢̢̢̢̢�");
	gotoxy(12, 13);
	printf("            �̢̢̢̢̢�");
	gotoxy(12, 14);
	printf("               �̢̢�");
	gotoxy(12, 15);
	printf("                 ��");
}

void popcorn()
{
	gotoxy(6, 3);
	printf("    ��    ���  ���    ");
	gotoxy(6, 4);
	printf("  ��  ���  ���  ���  ");
	gotoxy(6, 5);
	printf("��  ��  ���  ���  ���");
	gotoxy(6, 6);
	printf("�̢̢̢̢̢̢̢̢̢̢̢�");
	gotoxy(6, 7);
	printf("��������̢̢̡��");
	gotoxy(6, 8);
	printf("����̢̡��̢̢̡��");
	gotoxy(6, 9);
	printf("��������̢̢̡��");
	gotoxy(6, 10);
	printf("����̢̡�������");
	gotoxy(6, 11);
	printf("����̡����̢̡��");
	gotoxy(6, 12);
	printf("���̢̡��������");
	gotoxy(6, 13);
	printf("���̢̢̡���̢̡��");
	gotoxy(6, 14);
	printf("���̢̢̡���̢̡��");
	gotoxy(6, 15);
	printf("���̢̢̡��̢̢̡��");
}

void word()
{
	gotoxy(6, 5);
	printf("�����������");
	gotoxy(6, 6);
	printf("��    ��    ��    ��");
	gotoxy(6, 7);
	printf("�� Q  �� W  �� E  ��");
	gotoxy(6, 8);
	printf("������������");
	gotoxy(6, 9);
	printf("  ��    ��    ��    ��");
	gotoxy(6, 10);
	printf("  �� A  �� S  �� D  ��");
	gotoxy(6, 11);
	printf("  ������������");
	gotoxy(6, 12);
	printf("    ��    ��    ��    ��");
	gotoxy(6, 13);
	printf("    �� Z  �� X  �� C  ��");
	gotoxy(6, 14);
	printf("    �����������");
}