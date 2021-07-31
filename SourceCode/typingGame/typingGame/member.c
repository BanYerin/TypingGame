/*
모듈의 기능 : 회원정보 관리
버전 : v5.0
개발자 : 반예린
최종수정일 : 2018. 6. 5
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "member.h"

/*
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
*/

Member *head = NULL;		//회원정보구조체 노드 가리키는 포인터
Member *current_user = NULL; //현재 로그인되어있는 사용자의 회원정보가 들어있는 노드를 가리키는 포인터
FILE *fp_member = NULL; //회원정보파일을 가리키는 포인터

						/*
						int main(void) {
						Member *ptr = NULL;
						int menunum; //테스트용 메뉴 번호
						int level = 300; //테스트용 임시 점수

						load_member(); //회원정보 불러옴

						while (1) {
						printf("1번: 회원가입\n2번: 로그인\n3번: 로그아웃\n4번: 회원탈퇴\n5번: 랭킹보기\n6번: 비밀번호 변경\n7번: 게임종료\n\n메뉴 선택: ");
						scanf("%d", &menunum);
						switch(menunum) {
						case 1:
						input_data(fp_member); //회원가입정보 입력받는 함수 실행
						break;
						case 2:
						login(); //로그인 함수 실행
						break;
						case 3:
						logout(level); //로그아웃 함수 실행
						break;
						case 4:
						remov_member(); //회원탈퇴 함수 실행
						break;
						case 5:
						print_rank();
						break;
						case 6:
						change_pass();
						break;
						case 7:
						save_member(); //게임종료 전에 연결리스트에 들어있는 회원정보들을 파일에 출력하여 저장
						free(head); //동적할당한 회원정보 구조체 배열 메모리 해제
						return 0;
						break;
						default:
						printf("잘못입력했습니다. 다시 입력하세요.\n");
						}
						}
						}
						*/

						//회원정보 파일 열고 회원정보를 구조체에 저장하여 연결리스트로 만듦
void load_member(void) {
	Member *ptr = NULL;
	fp_member = fopen("member.txt", "r");		//회원정보 파일을 읽기 모드로 열기

												//회원정보 파일열기에 실패하면 오류메시지 출력후 프로그램 종료
	if (fp_member == NULL) {
		printf("오류! 회원정보 파일 열기 실패. member.txt파일이 없습니다.\n");
		exit(1);
	}

	fseek(fp_member, 0L, SEEK_SET); //정보를 읽어오기위해 파일포인터를 파일의 맨 앞으로 옮김

									//fp_member가 파일 끝이 아닌동안 반복
	while (!feof(fp_member)) {
		ptr = (Member*)malloc(sizeof(Member));		//회원정보 구조체 한개 동적할당하여 ptr에 연결

													//회원정보 구조체 동적할당 실패시 오류메시지 출력후 종료
		if (ptr == NULL) {
			printf("오류! 회원정보 구조체 동적할당 실패.\n");
			exit(1);
		}

		//회원정보파일에서 %s %s %d형식 순으로 데이터를 읽어서 순서대로 회원정보 구조체의 아이디, 비번, 최대점수에 저장
		fscanf(fp_member, "%s %s %d\n", ptr->id, ptr->password, &ptr->score);
		//정보를 저장한 새로운 구조체를 기존의 연결리스트에 연결
		ptr->next = head;
		head = ptr;
	}
	close_member(); //회원정보파일 닫음
}

//회원정보파일 닫음
void close_member(void) {
	fclose(fp_member);
}

//회원가입 정보 입력받는 함수
void input_data(FILE *fp_member) {
	char input_id[10];		//아이디 입력받을 변수
	char input_password[15];		//비밀번호 입력받을 변수
	Member* check_id = NULL;		//아이디 중복 확인위한 포인터
	int check; //아이디 또는 비밀번호가 중복이면 1, 중복 아니면 0
	int id_len = 0, password_len = 0;		//아이디 길이 변수, 비밀번호 길이 변수

	printf("★회원가입★\n");

	do {
		check = 0;
		printf("아이디 입력(영문, 숫자 조합으로 4~8자): ");
		scanf("%s", input_id); //아이디 입력받음
		id_len = strlen(input_id); //입력받은 아이디 길이 구해서 id_len에 저장

								   //아이디 길이가 4~8글자가 아니면 다시입력하라는 메시지 출력
		if ((id_len < 4) || (id_len > 8))
			printf("아이디가 4글자 미만이거나 8글자 초과했습니다. 다시 입력하세요.\n");

		//아이디가 중복이면 다시 입력하라는 메시지 출력
		for (check_id = head; check_id != NULL; check_id = check_id->next) {
			if (strcmp(input_id, check_id->id) == 0) {
				printf("아이디가 중복입니다. 다른 아이디를 입력하세요.\n");
				check = 1; //아이디가 중복이면 1
				break;
			}
		}
	} while ((id_len < 4) || (id_len > 8) || (check == 1)); //아이디 길이가 4글자 미만이거나 8글자 초과인동안 또는 아이디가 중복인동안 반복

															//제한조건 내에서 비밀번호 입력받기
	do {
		printf("비밀번호 입력(영문, 숫자 조합으로 5~13자): ");
		scanf("%s", input_password);
		password_len = strlen(input_password);
		if ((password_len < 5) || (password_len > 13))
			printf("비밀번호가 5글자 미만이거나 13글자 초과했습니다. 다시 입력하세요.\n");
	} while ((password_len < 5) || (password_len > 13));

	printf("계정 생성에 성공했습니다.\n");

	add_member(input_id, input_password); //입력받은 회원정보를 인자로 넘겨주어 회원정보를 구조체에 저장하고 파일에 저장
}

//회원가입함수에서 받은 정보를 새로 동적할당한 회원정보 구조체에 저장하고 그 구조체를 기존 연결리스트에 연결 
void add_member(char input_id[10], char input_password[15]) {
	Member *ptr = NULL;
	ptr = (Member*)malloc(sizeof(Member));		//회원정보 구조체 한개 동적할당하여 ptr에 연결

												//회원가입 함수에서 넘겨받은 인자정보를 새로 동적할당한 구조체에 저장
	strcpy(ptr->id, input_id);
	strcpy(ptr->password, input_password);
	ptr->score = 0; //초기 점수는 0으로 지정

					//정보를 저장한 새로운 구조체를 기존의 연결리스트에 연결
	ptr->next = head;
	head = ptr;

	save_member(); //연결리스트에 들어있는 회원정보들을 파일에 출력하여 저장
}

//연결리스트에 들어있는 회원정보들을 회원정보 파일에 출력하여 저장하는 함수
void save_member(void) {
	Member *ptr = NULL;
	fp_member = fopen("member.txt", "w"); //회원정보 파일을 쓰기 모드로 열기

										  //연결리스트를 처음부터 끝까지(temp가 NULL을 가리키기 전까지) 따라가면서 전체 회원정보를 파일에 저장
	for (ptr = head; ptr != NULL; ptr = ptr->next) {
		fprintf(fp_member, "%s %s %d\n", ptr->id, ptr->password, ptr->score);
	}
	close_member(); //회원정보파일 닫음
}


//회원탈퇴 함수
void remov_member(void) {
	char key_id[10]; //탈퇴할 회원 아이디 입력받을 변수
	Member *remove = NULL, *prev = NULL; //지울 노드를 가리키는 포인터, 지울 노드의 이전 노드를 가리키는 포인터

	printf("★회원탈퇴★\n");

	printf("탈퇴하실 회원 아이디를 입력하세요: ");
	scanf("%s", key_id);

	prev = head;
	remove = prev->next;

	if (strcmp(key_id, prev->id) == 0) {
		//삭제할 노드가 첫번째 노드이면: head가 두번째 노드(두번째 노드가 없는 경우에는 삭제할 노드가 가리키는 주소인 NULL)를 가리키도록 하고 첫번째 노드 메모리 해제
		head = prev->next;
		free(prev);
		prev = NULL;
		printf("회원 탈퇴가 완료되었습니다.\n");
		save_member(); //연결리스트에 들어있는 회원정보들을 파일에 출력하여 저장
		return; //탈퇴할 회원 찾아서 탈퇴성공하면 탈퇴함수 종료
	}
	else {
		//삭제할 노드가 첫번째 노드가 아니면: 삭제할 노드의 전 노드가 삭제할 노드의 다음 노드를 가리키도록 하고 삭제할 노드 메모리 해제
		while (remove != NULL) {
			if (strcmp(key_id, remove->id) == 0) {
				prev->next = remove->next;
				free(remove);
				remove = NULL;
				printf("회원 탈퇴가 완료되었습니다.\n");
				save_member(); //연결리스트에 들어있는 회원정보들을 파일에 출력하여 저장
				return; //탈퇴할 회원 찾아서 탈퇴성공하면 탈퇴함수 종료
			}
			else {
				prev = remove;
				remove = remove->next;
			}
		}
	}
	printf("존재하지 않는 아이디입니다.\n"); //입력받은 탈퇴할 회원 아이디가 존재하지 않으면 알림메시지 출력
}

//로그인 함수
int login(void) {
	char log_id[10], log_pass[15]; //로그인할때 입력받을 아이디, 비번에 대한 변수
	Member *check = head;

	printf("★로그인★\n");

	//아이디와 비밀번호를 입력받음
	printf("아이디: ");
	scanf("%s", log_id);
	printf("비밀번호: ");
	scanf("%s", log_pass);

	//check
	for (check = head; check != NULL; check = check->next) {
		if (strcmp(log_id, check->id) == 0) {
			if (strcmp(log_pass, check->password) == 0) {
				printf("성공적으로 로그인했습니다.\n");
				current_user = check;
				return 1; //로그인 성공: 1 반환
			}
			printf("비밀번호가 일치하지 않습니다.\n"); //일치하는 아이디는 있지만 비밀번호가 틀릴경우 알림메시지 출력
			return 0; //로그인 실패: 0 반환
		}
	}

	printf("존재하지 않는 아이디입니다.\n"); //일치하는 아이디가 없을경우 알림메시지 출력
	return 0; //로그인 실패: 0 반환
}

//로그아웃 함수: 현재 로그인되어있는 사용자의 회원정보를 업데이트 한 후 로그아웃
void logout(int level) {
	if (current_user == NULL) {
		printf("이미 로그아웃 되었거나 로그인이 되어있지 않습니다.\n");
		return;
	}
	level_update(level); //현재 로그인 되어있는 사용자의 점수를 업데이트
	current_user = NULL; //로그아웃을 위해 현재 로그인 되어있는 사용자를 가리키는 포인터를 NULL값으로 함
	printf("로그아웃이 완료되었습니다.\n");
}

//게임 결과에 대한 최대점수를 해당 회원정보에 업데이트하는 함수
void level_update(int level) {
	//현재 로그인된 유저의 기존 점수보다 인자로 받은 점수가 더 클경우 그 점수로 회원정보 업데이트
	if (current_user->score < level) {
		current_user->score = level; //인자로 넘겨받은 점수를 현재 로그인 되어있는 사용자의 회원정보에 넣어줌으로써 점수 업데이트 
		save_member(); //연결리스트에 들어있는 회원정보들을 파일에 출력하여 저장
	}
}

//회원들의 랭킹 출력하는 함수
void print_rank(void) {
	Member *p = head;
	Member *ptr = NULL;

	int mem_num = 0; //회원 수
	int i;

	for (; p != NULL; p = p->next) {
		mem_num++;
	}

	ptr = (Member*)malloc(sizeof(Member)*mem_num); //회원수만큼의 회원구조체 배열 동적할당

												   //회원정보 구조체 배열 동적할당 실패시 오류메시지 출력후 종료
	if (ptr == NULL) {
		printf("오류! 회원정보 구조체 배열 동적할당 실패.\n");
		exit(1);
	}

	p = head;
	for (i = 0; i < mem_num; i++) {
		strcpy(ptr[i].id, p->id);
		strcpy(ptr[i].password, p->password);
		ptr[i].score = p->score;
		p = p->next;
	}

	sort(ptr, mem_num); //배열을 점수 높은순으로 정렬

						//랭킹 출력
	printf("★전체 랭킹★\n");
	printf("순위				아이디					점수\n");
	printf("-------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < mem_num; i++) {
		//score가 0 이상일때만 출력. 혹시 0 미만의 점수 가진 쓰레기값으로 잘못들어간 회원 나올까봐..
		if (ptr[i].score >= 0) {
			printf("%d위				%s					%d점\n", i + 1, ptr[i].id, ptr[i].score);
		}
	}
	printf("\n\n메뉴로 돌아가려면 아무 키나 누르세요.\n");
	getch(); //아무 키나 입력받으면 함수 종료
}


//점수 높은 순서로 정렬하는 함수
void sort(Member *a, int size) {
	int i, j;
	Member temp;
	for (i = 0; i < size; i++) {
		for (j = i + 1; j < size; j++) {
			if (a[i].score < a[j].score) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

//비밀번호 변경 함수
void change_pass(void) {
	int password_len = 0;
	if (current_user == NULL) {
		printf("비밀번호를 변경하시려면 먼저 로그인 해 주세요.\n");
		return;
	}
	else {
		printf("★비밀번호 변경★\n");
		printf("현재 비밀번호: %s\n", current_user->password);
		//제한조건 내에서 비밀번호 입력받기
		do {
			printf("변경하실 비밀번호를 입력하세요(영문, 숫자 조합으로 5~13자): ");
			scanf("%s", current_user->password);
			password_len = strlen(current_user->password);
			if ((password_len < 5) || (password_len > 13))
				printf("비밀번호가 5글자 미만이거나 13글자 초과했습니다. 다시 입력하세요.\n");
		} while ((password_len < 5) || (password_len > 13));
		printf("비밀번호 변경 완료!\n");
	}
	save_member();
}