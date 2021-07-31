/*********************
메인 실행
조중훈
v.1.02
2018.5.15
*********************/

///여기서 모든 프로그램이 실행될 예정

#include "header.h"
#include "display.h" //중훈
#include "member.h" //예린
#include "game.h" //현종

int main()
{
	load_member(); //회원정보 불러오기
	Print_Menu(); //화면 출력

	return 0;
}