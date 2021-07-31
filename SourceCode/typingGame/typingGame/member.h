/*
모듈의 기능 : 회원정보 관리
버전 : v5.0
개발자 : 반예린
최종수정일 : 2018. 6. 5
*/
#pragma once

//회원정보 구조체
typedef struct member {
	char id[10];		//아이디
	char password[15];		//비밀번호
	int score; //최대점수
	struct Member *next;		//다음노드 주소 저장할 포인터
}Member;

void input_data(FILE *fp_member); //회원가입 정보 입력 함수
void remov_member(void);		//회원탈퇴 함수
void load_member(void); //회원정보 파일 열고 회원정보를 구조체에 저장하여 연결리스트로 만듦
void close_member(void); //회원정보파일 닫음
void input_data(FILE *fp_member); //회원가입 정보 입력받는 함수
void add_member(char input_id[10], char input_password[15]); //회원가입함수에서 받은 정보를 새로 동적할당한 회원정보 구조체에 저장하고 그 구조체를 기존 연결리스트에 연결하는 함수
int login(void); //로그인 함수
void logout(int level); //로그아웃 함수: 현재 로그인되어있는 사용자의 회원정보를 업데이트 한 후 로그아웃
void level_update(int level); //게임 결과에 대한 최대점수를 해당 회원정보에 업데이트하는 함수
void save_member(void); //연결리스트에 들어있는 회원정보들을 회원정보 파일에 출력하여 저장하는 함수
void print_rank(void); //회원들의 랭킹 출력하는 함수
void sort(Member *a, int size); //점수 높은 순서로 정렬하는 함수
void change_pass(void); 	//비밀번호 변경 함수