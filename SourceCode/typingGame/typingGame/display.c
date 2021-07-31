/*********************
화면 디스플레이
조중훈
v.1.07
2018.5.28
*********************/

//사용자 관리 기능(사용자 등록, 사용자 정보 관리, 탈퇴 등)
//사용자별 스코어, 레벨 관리 기능 등

//코드 파일 맨 위에 모듈기능, 버전, 개발자, 최종수정일 주석 달기

//메인 - 로그인, 계정 만들기, 탈퇴, 화면 전환, 종료
//로그인 - 게임 실행, 전체 랭킹 및 기록, 탈퇴, 종료

/********************메모장********************
게임 : 타자 게임
!독창적이고 개성적인 요소를 넣어보자¡
게임 스토리 추가?
아이디어
gotoxy(29, 5); 네모 중심
끝낼때 회원정보 저장하고 끝내기
save_member(void) 오류 수정하기
멤버 소스 연결하기
**********************************************/

#include "header.h"
#include "display.h"
#include "member.h"
#include "game.h"

static int square_type = 3; //화면 테두리 타입 변환 전역 변수 

extern Member *ptr, *head;		//회원정보구조체 노드 가리키는 포인터
extern Member *current_user; //현재 로그인되어있는 사용자의 회원정보가 들어있는 노드를 가리키는 포인터
extern FILE *fp_member; //회원정보파일을 가리키는 포인터

extern score;

void draw_square()
{
	unsigned char square1, square2[7];
	int x, y;

	switch (square_type)
	{
	case 1: square1 = 0xa6; for (int i = 1; i < 7; i++) square2[i] = 0xa0 + i; break; // 선 0xa6 0xa1~0xa7
	case 2: square1 = 0xa1; for (int i = 0; i < 7; i++) square2[i] = 0xe0; break; // □ 0xa1 0xe0
	case 3: square1 = 0xa1; for (int i = 0; i < 7; i++) square2[i] = 0xe1; break; // ■ 0xa1 0xe1
	default: break;
	}

	printf("%c%c", square1, square2[3]);
	for (x = 0; x < 27; x++)
	{
		printf("%c%c", square1, square2[1]);
	}
	printf("%c%c", square1, square2[4]);
	printf("\n"); //상층

	for (y = 0; y < 15; y++)
	{
		printf("%c%c", square1, square2[2]);
		for (x = 0; x < 27; x++)
			printf("  ");
		printf("%c%c", square1, square2[2]);
		printf("\n");
	} //중층

	printf("%c%c", square1, square2[6]);
	for (x = 0; x < 27; x++)
		printf("%c%c", square1, square2[1]);
	printf("%c%c", square1, square2[5]);
	printf("\n"); //하층

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
	printf("\n");//상층2

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
	} //중층2

	printf("%c%c", square1, square2[6]);
	for (x = 0; x < 12; x++)
		printf("%c%c", square1, square2[1]);
	printf("%c%c", square1, square2[5]);
	printf("  ");
	printf("%c%c", square1, square2[6]);
	for (x = 0; x < 12; x++)
		printf("%c%c", square1, square2[1]);
	printf("%c%c", square1, square2[5]);
	printf("\n"); //하층2
}

void Print_Menu()
{
	int num = 0; //선택할 번호

	draw_square();
	popcorn(); ///

	if (current_user == NULL) //로그인 안한 상태면 //로그인 여부 확인바람
	{
		gotoxy(40, 5); ///
		printf("메인 화면\n\n"); //수정예정
		gotoxy(3, 20);
		printf(" 1.로그인하기\n");
		gotoxy(3, 21);
		printf(" 2.계정 생성\n");
		gotoxy(3, 22);
		printf(" 3.계정 삭제\n");
		gotoxy(3, 23);
		printf(" 4.게임 종료\n");
	}
	else //로그인 한 상태면
	{
		gotoxy(40, 5); ///
		printf("메인 화면\n\n"); //수정예정
		gotoxy(3, 19);
		printf(" 1.게임 실행\n");
		gotoxy(3, 20);
		printf(" 2.랭킹 보기\n");
		gotoxy(3, 21);
		printf(" 3.비밀번호 변경\n");
		gotoxy(3, 22);
		printf(" 4.로그아웃\n");
		gotoxy(3, 23);
		printf(" 5.테두리 변경\n");
		gotoxy(3, 24);
		printf(" 6.게임 종료\n");
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
	case 1:gotoxy(33, 21); printf("로그인하기\n"); Sleep(500); system("cls"); login(); Sleep(500); system("cls"); Print_Menu(); break; ///수정
	case 2:gotoxy(33, 21); printf("계정 생성\n"); Sleep(500); system("cls"); input_data(fp_member); Sleep(500); system("cls"); Print_Menu(); break;
	case 3:gotoxy(33, 21); printf("계정 삭제\n"); Sleep(500); system("cls"); remov_member(); Sleep(500); system("cls"); Print_Menu(); break;
	case 4:gotoxy(33, 21); printf("게임 종료\n"); Sleep(500); system("cls"); save_member(); free(head); close_member(); break;
	default:gotoxy(33, 21); printf("잘못된 입력 입니다.\n"); Sleep(50); system("cls"); Print_Menu(); break;
	}
}

void After_Log_in_Menu(int num)
{
	switch (num)
	{
	case 1:gotoxy(33, 21); printf("게임 실행\n"); Sleep(500); system("cls"); game(); break;
	case 2:gotoxy(33, 21); printf("랭킹 보기\n"); Sleep(500); system("cls"); print_rank(); system("cls");  Print_Menu(); break; ///Print_Menu()빠져있어서 추가했음
	case 3:gotoxy(33, 21); printf("비밀번호 변경\n"); Sleep(500); system("cls"); change_pass(); Sleep(500); system("cls"); Print_Menu(); break; ///
	case 4:gotoxy(33, 21); printf("로그아웃\n"); Sleep(500); system("cls"); logout(score); Sleep(500); system("cls"); Print_Menu(); break; ///score 넣음
	case 5:gotoxy(33, 21); printf("테두리 변경\n"); Sleep(500); system("cls"); Change_Square(); break;
	case 6:gotoxy(33, 21); printf("게임 종료\n"); Sleep(500); system("cls"); save_member(); free(head); break;
	default:gotoxy(33, 21); printf("잘못된 입력 입니다.\n"); Sleep(100); system("cls"); Print_Menu(); break;
	}
}

void Change_Square()
{
	int change = 1;

	draw_square();

	do {
		heart();

		gotoxy(3, 19);
		printf("1. 선"); // 선 0xa6 0xa1~0xa7
		gotoxy(3, 20);
		printf("2. 빈 네모"); // □ 0xa1 0xe0
		gotoxy(3, 21);
		printf("3. 네모"); // ■ 0xa1 0xe1
		gotoxy(3, 22);
		printf("4. 되돌아가기");

		change = _getch() - '0';

		switch (change)
		{
		case 1: square_type = 1; system("cls"); draw_square(); gotoxy(44, 21); printf("1"); break;
		case 2: square_type = 2; system("cls"); draw_square(); gotoxy(44, 21); printf("2"); break;
		case 3: square_type = 3; system("cls"); draw_square(); gotoxy(44, 21); printf("3"); break;
		case 4: system("cls"); Print_Menu();  break;
		default: gotoxy(33, 21); printf("잘못된 입력 입니다.\n"); Sleep(100); system("cls"); draw_square(); break;
		}
	} while (change != 4);
}

void heart()
{
	gotoxy(12, 3);
	printf("    ▩▩▩                ▩▩▩");
	gotoxy(12, 4);
	printf("  ▩▩▩▩▩▩        ▩▩▩▩▩▩");
	gotoxy(12, 5);
	printf("▩▩▩▩▩▩▩▩    ▩▩▩▩▩▩▩▩");
	gotoxy(12, 6);
	printf("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	gotoxy(12, 7);
	printf("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	gotoxy(12, 8);
	printf("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	gotoxy(12, 9);
	printf("  ▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	gotoxy(12, 10);
	printf("    ▩▩▩▩▩▩▩▩▩▩▩▩▩▩  ");
	gotoxy(12, 11);
	printf("      ▩▩▩▩▩▩▩▩▩▩▩▩");
	gotoxy(12, 12);
	printf("         ▩▩▩▩▩▩▩▩▩");
	gotoxy(12, 13);
	printf("            ▩▩▩▩▩▩");
	gotoxy(12, 14);
	printf("               ▩▩▩");
	gotoxy(12, 15);
	printf("                 ▩");
}

void popcorn()
{
	gotoxy(6, 3);
	printf("    □    □□  □□    ");
	gotoxy(6, 4);
	printf("  □  □□  □□  □□  ");
	gotoxy(6, 5);
	printf("□  □  □□  □□  □□");
	gotoxy(6, 6);
	printf("▩▩▩▩▩▩▩▩▩▩▩▩");
	gotoxy(6, 7);
	printf("□□■■■□□▩▩▩□□");
	gotoxy(6, 8);
	printf("□□■▩▩■□▩▩▩□□");
	gotoxy(6, 9);
	printf("□□■■■□□▩▩▩□□");
	gotoxy(6, 10);
	printf("□□■▩▩□□■■■□□");
	gotoxy(6, 11);
	printf("□□■▩■■□■▩▩■□");
	gotoxy(6, 12);
	printf("□□▩▩■■□■■■□□");
	gotoxy(6, 13);
	printf("□□▩▩▩□□■▩▩□□");
	gotoxy(6, 14);
	printf("□□▩▩▩□□■▩▩□□");
	gotoxy(6, 15);
	printf("□□▩▩▩□□▩▩▩□□");
}

void word()
{
	gotoxy(6, 5);
	printf("□□□□□□□□□□");
	gotoxy(6, 6);
	printf("□    □    □    □");
	gotoxy(6, 7);
	printf("□ Q  □ W  □ E  □");
	gotoxy(6, 8);
	printf("□□□□□□□□□□□");
	gotoxy(6, 9);
	printf("  □    □    □    □");
	gotoxy(6, 10);
	printf("  □ A  □ S  □ D  □");
	gotoxy(6, 11);
	printf("  □□□□□□□□□□□");
	gotoxy(6, 12);
	printf("    □    □    □    □");
	gotoxy(6, 13);
	printf("    □ Z  □ X  □ C  □");
	gotoxy(6, 14);
	printf("    □□□□□□□□□□");
}