/*
����� ��� : ȸ������ ����
���� : v5.0
������ : �ݿ���
���������� : 2018. 6. 5
*/
#pragma once

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