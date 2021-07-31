/*
모듈의 기능 : 게임 플레이
버전 : v1.4
개발자 : 안현종
최종수정일 : 2018. 6. 8.
*/

#pragma once

void gotoxy(int x, int y);
void game();
int printmenu();
void playgame(int level);
int showresult();
void textcolor(int color_number);

/*
0 - 검정색
1 - 파랑색
2 - 초록색
3 - 옥색
4 - 빨간색
5 - 자주색
6 - 노랑색
7 - 흰색
8 - 회색
9 - 연한 파랑색
A - 연한 초록색
B - 연한 옥색
C - 연한 빨간색
D - 연한 자주색
E - 연한 노랑색
F - 밝은 흰색
*/