/*
����� ��� : ȸ������ ����
���� : v5.0
������ : �ݿ���
���������� : 2018. 6. 5
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "member.h"

/*
//ȸ������ ����ü
typedef struct member {
char id[10];		//���̵�
char password[15];		//��й�ȣ
int score; //�ִ�����
struct Member *next;		//������� �ּ� ������ ������
}Member;

void input_data(FILE *fp_member); //ȸ������ ���� �Է� �Լ�
void remov_member(void);		//ȸ��Ż�� �Լ�
void load_member(void); //ȸ������ ���� ���� ȸ�������� ����ü�� �����Ͽ� ���Ḯ��Ʈ�� ����
void close_member(void); //ȸ���������� ����
void input_data(FILE *fp_member); //ȸ������ ���� �Է¹޴� �Լ�
void add_member(char input_id[10], char input_password[15]); //ȸ�������Լ����� ���� ������ ���� �����Ҵ��� ȸ������ ����ü�� �����ϰ� �� ����ü�� ���� ���Ḯ��Ʈ�� �����ϴ� �Լ�
int login(void); //�α��� �Լ�
void logout(int level); //�α׾ƿ� �Լ�: ���� �α��εǾ��ִ� ������� ȸ�������� ������Ʈ �� �� �α׾ƿ�
void level_update(int level); //���� ����� ���� �ִ������� �ش� ȸ�������� ������Ʈ�ϴ� �Լ�
void save_member(void); //���Ḯ��Ʈ�� ����ִ� ȸ���������� ȸ������ ���Ͽ� ����Ͽ� �����ϴ� �Լ�
void print_rank(void); //ȸ������ ��ŷ ����ϴ� �Լ�
void sort(Member *a, int size); //���� ���� ������ �����ϴ� �Լ�
void change_pass(void); 	//��й�ȣ ���� �Լ�
*/

Member *head = NULL;		//ȸ����������ü ��� ����Ű�� ������
Member *current_user = NULL; //���� �α��εǾ��ִ� ������� ȸ�������� ����ִ� ��带 ����Ű�� ������
FILE *fp_member = NULL; //ȸ������������ ����Ű�� ������

						/*
						int main(void) {
						Member *ptr = NULL;
						int menunum; //�׽�Ʈ�� �޴� ��ȣ
						int level = 300; //�׽�Ʈ�� �ӽ� ����

						load_member(); //ȸ������ �ҷ���

						while (1) {
						printf("1��: ȸ������\n2��: �α���\n3��: �α׾ƿ�\n4��: ȸ��Ż��\n5��: ��ŷ����\n6��: ��й�ȣ ����\n7��: ��������\n\n�޴� ����: ");
						scanf("%d", &menunum);
						switch(menunum) {
						case 1:
						input_data(fp_member); //ȸ���������� �Է¹޴� �Լ� ����
						break;
						case 2:
						login(); //�α��� �Լ� ����
						break;
						case 3:
						logout(level); //�α׾ƿ� �Լ� ����
						break;
						case 4:
						remov_member(); //ȸ��Ż�� �Լ� ����
						break;
						case 5:
						print_rank();
						break;
						case 6:
						change_pass();
						break;
						case 7:
						save_member(); //�������� ���� ���Ḯ��Ʈ�� ����ִ� ȸ���������� ���Ͽ� ����Ͽ� ����
						free(head); //�����Ҵ��� ȸ������ ����ü �迭 �޸� ����
						return 0;
						break;
						default:
						printf("�߸��Է��߽��ϴ�. �ٽ� �Է��ϼ���.\n");
						}
						}
						}
						*/

						//ȸ������ ���� ���� ȸ�������� ����ü�� �����Ͽ� ���Ḯ��Ʈ�� ����
void load_member(void) {
	Member *ptr = NULL;
	fp_member = fopen("member.txt", "r");		//ȸ������ ������ �б� ���� ����

												//ȸ������ ���Ͽ��⿡ �����ϸ� �����޽��� ����� ���α׷� ����
	if (fp_member == NULL) {
		printf("����! ȸ������ ���� ���� ����. member.txt������ �����ϴ�.\n");
		exit(1);
	}

	fseek(fp_member, 0L, SEEK_SET); //������ �о�������� ���������͸� ������ �� ������ �ű�

									//fp_member�� ���� ���� �ƴѵ��� �ݺ�
	while (!feof(fp_member)) {
		ptr = (Member*)malloc(sizeof(Member));		//ȸ������ ����ü �Ѱ� �����Ҵ��Ͽ� ptr�� ����

													//ȸ������ ����ü �����Ҵ� ���н� �����޽��� ����� ����
		if (ptr == NULL) {
			printf("����! ȸ������ ����ü �����Ҵ� ����.\n");
			exit(1);
		}

		//ȸ���������Ͽ��� %s %s %d���� ������ �����͸� �о ������� ȸ������ ����ü�� ���̵�, ���, �ִ������� ����
		fscanf(fp_member, "%s %s %d\n", ptr->id, ptr->password, &ptr->score);
		//������ ������ ���ο� ����ü�� ������ ���Ḯ��Ʈ�� ����
		ptr->next = head;
		head = ptr;
	}
	close_member(); //ȸ���������� ����
}

//ȸ���������� ����
void close_member(void) {
	fclose(fp_member);
}

//ȸ������ ���� �Է¹޴� �Լ�
void input_data(FILE *fp_member) {
	char input_id[10];		//���̵� �Է¹��� ����
	char input_password[15];		//��й�ȣ �Է¹��� ����
	Member* check_id = NULL;		//���̵� �ߺ� Ȯ������ ������
	int check; //���̵� �Ǵ� ��й�ȣ�� �ߺ��̸� 1, �ߺ� �ƴϸ� 0
	int id_len = 0, password_len = 0;		//���̵� ���� ����, ��й�ȣ ���� ����

	printf("��ȸ�����ԡ�\n");

	do {
		check = 0;
		printf("���̵� �Է�(����, ���� �������� 4~8��): ");
		scanf("%s", input_id); //���̵� �Է¹���
		id_len = strlen(input_id); //�Է¹��� ���̵� ���� ���ؼ� id_len�� ����

								   //���̵� ���̰� 4~8���ڰ� �ƴϸ� �ٽ��Է��϶�� �޽��� ���
		if ((id_len < 4) || (id_len > 8))
			printf("���̵� 4���� �̸��̰ų� 8���� �ʰ��߽��ϴ�. �ٽ� �Է��ϼ���.\n");

		//���̵� �ߺ��̸� �ٽ� �Է��϶�� �޽��� ���
		for (check_id = head; check_id != NULL; check_id = check_id->next) {
			if (strcmp(input_id, check_id->id) == 0) {
				printf("���̵� �ߺ��Դϴ�. �ٸ� ���̵� �Է��ϼ���.\n");
				check = 1; //���̵� �ߺ��̸� 1
				break;
			}
		}
	} while ((id_len < 4) || (id_len > 8) || (check == 1)); //���̵� ���̰� 4���� �̸��̰ų� 8���� �ʰ��ε��� �Ǵ� ���̵� �ߺ��ε��� �ݺ�

															//�������� ������ ��й�ȣ �Է¹ޱ�
	do {
		printf("��й�ȣ �Է�(����, ���� �������� 5~13��): ");
		scanf("%s", input_password);
		password_len = strlen(input_password);
		if ((password_len < 5) || (password_len > 13))
			printf("��й�ȣ�� 5���� �̸��̰ų� 13���� �ʰ��߽��ϴ�. �ٽ� �Է��ϼ���.\n");
	} while ((password_len < 5) || (password_len > 13));

	printf("���� ������ �����߽��ϴ�.\n");

	add_member(input_id, input_password); //�Է¹��� ȸ�������� ���ڷ� �Ѱ��־� ȸ�������� ����ü�� �����ϰ� ���Ͽ� ����
}

//ȸ�������Լ����� ���� ������ ���� �����Ҵ��� ȸ������ ����ü�� �����ϰ� �� ����ü�� ���� ���Ḯ��Ʈ�� ���� 
void add_member(char input_id[10], char input_password[15]) {
	Member *ptr = NULL;
	ptr = (Member*)malloc(sizeof(Member));		//ȸ������ ����ü �Ѱ� �����Ҵ��Ͽ� ptr�� ����

												//ȸ������ �Լ����� �Ѱܹ��� ���������� ���� �����Ҵ��� ����ü�� ����
	strcpy(ptr->id, input_id);
	strcpy(ptr->password, input_password);
	ptr->score = 0; //�ʱ� ������ 0���� ����

					//������ ������ ���ο� ����ü�� ������ ���Ḯ��Ʈ�� ����
	ptr->next = head;
	head = ptr;

	save_member(); //���Ḯ��Ʈ�� ����ִ� ȸ���������� ���Ͽ� ����Ͽ� ����
}

//���Ḯ��Ʈ�� ����ִ� ȸ���������� ȸ������ ���Ͽ� ����Ͽ� �����ϴ� �Լ�
void save_member(void) {
	Member *ptr = NULL;
	fp_member = fopen("member.txt", "w"); //ȸ������ ������ ���� ���� ����

										  //���Ḯ��Ʈ�� ó������ ������(temp�� NULL�� ����Ű�� ������) ���󰡸鼭 ��ü ȸ�������� ���Ͽ� ����
	for (ptr = head; ptr != NULL; ptr = ptr->next) {
		fprintf(fp_member, "%s %s %d\n", ptr->id, ptr->password, ptr->score);
	}
	close_member(); //ȸ���������� ����
}


//ȸ��Ż�� �Լ�
void remov_member(void) {
	char key_id[10]; //Ż���� ȸ�� ���̵� �Է¹��� ����
	Member *remove = NULL, *prev = NULL; //���� ��带 ����Ű�� ������, ���� ����� ���� ��带 ����Ű�� ������

	printf("��ȸ��Ż���\n");

	printf("Ż���Ͻ� ȸ�� ���̵� �Է��ϼ���: ");
	scanf("%s", key_id);

	prev = head;
	remove = prev->next;

	if (strcmp(key_id, prev->id) == 0) {
		//������ ��尡 ù��° ����̸�: head�� �ι�° ���(�ι�° ��尡 ���� ��쿡�� ������ ��尡 ����Ű�� �ּ��� NULL)�� ����Ű���� �ϰ� ù��° ��� �޸� ����
		head = prev->next;
		free(prev);
		prev = NULL;
		printf("ȸ�� Ż�� �Ϸ�Ǿ����ϴ�.\n");
		save_member(); //���Ḯ��Ʈ�� ����ִ� ȸ���������� ���Ͽ� ����Ͽ� ����
		return; //Ż���� ȸ�� ã�Ƽ� Ż�𼺰��ϸ� Ż���Լ� ����
	}
	else {
		//������ ��尡 ù��° ��尡 �ƴϸ�: ������ ����� �� ��尡 ������ ����� ���� ��带 ����Ű���� �ϰ� ������ ��� �޸� ����
		while (remove != NULL) {
			if (strcmp(key_id, remove->id) == 0) {
				prev->next = remove->next;
				free(remove);
				remove = NULL;
				printf("ȸ�� Ż�� �Ϸ�Ǿ����ϴ�.\n");
				save_member(); //���Ḯ��Ʈ�� ����ִ� ȸ���������� ���Ͽ� ����Ͽ� ����
				return; //Ż���� ȸ�� ã�Ƽ� Ż�𼺰��ϸ� Ż���Լ� ����
			}
			else {
				prev = remove;
				remove = remove->next;
			}
		}
	}
	printf("�������� �ʴ� ���̵��Դϴ�.\n"); //�Է¹��� Ż���� ȸ�� ���̵� �������� ������ �˸��޽��� ���
}

//�α��� �Լ�
int login(void) {
	char log_id[10], log_pass[15]; //�α����Ҷ� �Է¹��� ���̵�, ����� ���� ����
	Member *check = head;

	printf("�ڷα��Ρ�\n");

	//���̵�� ��й�ȣ�� �Է¹���
	printf("���̵�: ");
	scanf("%s", log_id);
	printf("��й�ȣ: ");
	scanf("%s", log_pass);

	//check
	for (check = head; check != NULL; check = check->next) {
		if (strcmp(log_id, check->id) == 0) {
			if (strcmp(log_pass, check->password) == 0) {
				printf("���������� �α����߽��ϴ�.\n");
				current_user = check;
				return 1; //�α��� ����: 1 ��ȯ
			}
			printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n"); //��ġ�ϴ� ���̵�� ������ ��й�ȣ�� Ʋ����� �˸��޽��� ���
			return 0; //�α��� ����: 0 ��ȯ
		}
	}

	printf("�������� �ʴ� ���̵��Դϴ�.\n"); //��ġ�ϴ� ���̵� ������� �˸��޽��� ���
	return 0; //�α��� ����: 0 ��ȯ
}

//�α׾ƿ� �Լ�: ���� �α��εǾ��ִ� ������� ȸ�������� ������Ʈ �� �� �α׾ƿ�
void logout(int level) {
	if (current_user == NULL) {
		printf("�̹� �α׾ƿ� �Ǿ��ų� �α����� �Ǿ����� �ʽ��ϴ�.\n");
		return;
	}
	level_update(level); //���� �α��� �Ǿ��ִ� ������� ������ ������Ʈ
	current_user = NULL; //�α׾ƿ��� ���� ���� �α��� �Ǿ��ִ� ����ڸ� ����Ű�� �����͸� NULL������ ��
	printf("�α׾ƿ��� �Ϸ�Ǿ����ϴ�.\n");
}

//���� ����� ���� �ִ������� �ش� ȸ�������� ������Ʈ�ϴ� �Լ�
void level_update(int level) {
	//���� �α��ε� ������ ���� �������� ���ڷ� ���� ������ �� Ŭ��� �� ������ ȸ������ ������Ʈ
	if (current_user->score < level) {
		current_user->score = level; //���ڷ� �Ѱܹ��� ������ ���� �α��� �Ǿ��ִ� ������� ȸ�������� �־������ν� ���� ������Ʈ 
		save_member(); //���Ḯ��Ʈ�� ����ִ� ȸ���������� ���Ͽ� ����Ͽ� ����
	}
}

//ȸ������ ��ŷ ����ϴ� �Լ�
void print_rank(void) {
	Member *p = head;
	Member *ptr = NULL;

	int mem_num = 0; //ȸ�� ��
	int i;

	for (; p != NULL; p = p->next) {
		mem_num++;
	}

	ptr = (Member*)malloc(sizeof(Member)*mem_num); //ȸ������ŭ�� ȸ������ü �迭 �����Ҵ�

												   //ȸ������ ����ü �迭 �����Ҵ� ���н� �����޽��� ����� ����
	if (ptr == NULL) {
		printf("����! ȸ������ ����ü �迭 �����Ҵ� ����.\n");
		exit(1);
	}

	p = head;
	for (i = 0; i < mem_num; i++) {
		strcpy(ptr[i].id, p->id);
		strcpy(ptr[i].password, p->password);
		ptr[i].score = p->score;
		p = p->next;
	}

	sort(ptr, mem_num); //�迭�� ���� ���������� ����

						//��ŷ ���
	printf("����ü ��ŷ��\n");
	printf("����				���̵�					����\n");
	printf("-------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < mem_num; i++) {
		//score�� 0 �̻��϶��� ���. Ȥ�� 0 �̸��� ���� ���� �����Ⱚ���� �߸��� ȸ�� ���ñ��..
		if (ptr[i].score >= 0) {
			printf("%d��				%s					%d��\n", i + 1, ptr[i].id, ptr[i].score);
		}
	}
	printf("\n\n�޴��� ���ư����� �ƹ� Ű�� ��������.\n");
	getch(); //�ƹ� Ű�� �Է¹����� �Լ� ����
}


//���� ���� ������ �����ϴ� �Լ�
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

//��й�ȣ ���� �Լ�
void change_pass(void) {
	int password_len = 0;
	if (current_user == NULL) {
		printf("��й�ȣ�� �����Ͻ÷��� ���� �α��� �� �ּ���.\n");
		return;
	}
	else {
		printf("�ں�й�ȣ �����\n");
		printf("���� ��й�ȣ: %s\n", current_user->password);
		//�������� ������ ��й�ȣ �Է¹ޱ�
		do {
			printf("�����Ͻ� ��й�ȣ�� �Է��ϼ���(����, ���� �������� 5~13��): ");
			scanf("%s", current_user->password);
			password_len = strlen(current_user->password);
			if ((password_len < 5) || (password_len > 13))
				printf("��й�ȣ�� 5���� �̸��̰ų� 13���� �ʰ��߽��ϴ�. �ٽ� �Է��ϼ���.\n");
		} while ((password_len < 5) || (password_len > 13));
		printf("��й�ȣ ���� �Ϸ�!\n");
	}
	save_member();
}