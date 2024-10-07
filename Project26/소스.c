#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

const int NMBR_CARDS = 53;
typedef struct card Card;
typedef struct player Player;
struct card {
	int c;
	Card* next;
	Card* prev;
};

struct player {
	int i;
	Card* card;
	int card_count;
	Player* next;
	Player* prev;
};

Player* player_head = NULL;
Card* pFreeCard = NULL;
Player * pFreePlayer = NULL;
// �迭�� ���� �Լ��̴�
void shuffle(int* arr) {
	srand(time(NULL));
	int temp;
	int rn;
	for (int i = 0; i < NMBR_CARDS; i++)
	{
		rn = rand() % NMBR_CARDS;
		temp = arr[i];
		arr[i] = arr[rn];
		arr[rn] = temp;
	}
}

void printrealcard(int num) {

	int rcard_quot, rcard_remain;
	rcard_quot = num / 13;
	rcard_remain = num % 13;
	switch (rcard_quot) {
	case 1: printf("%-3s", "��"); break;
	case 2: printf("%-3s", "��"); break;
	case 3:	printf("%-3s", "��"); break;
	case 4:	printf("%-3s", "��"); break;
	case 5:	printf("%-5s", "��"); break;
	}

	if (rcard_quot == 5) {}
	else {
		switch (rcard_remain) {
		case 0: printf("%-2s", "A"); break;
		case 1: printf("%-2s", "2"); break;
		case 2: printf("%-2s", "3"); break;
		case 3: printf("%-2s", "4"); break;
		case 4: printf("%-2s", "5"); break;
		case 5: printf("%-2s", "6"); break;
		case 6: printf("%-2s", "7"); break;
		case 7: printf("%-2s", "8"); break;
		case 8: printf("%-2s", "9"); break;
		case 9: printf("%-2s", "10"); break;
		case 10:printf("%-2s", "J"); break;
		case 11:printf("%-2s", "Q"); break;
		case 12:printf("%-2s", "K"); break;
		}
	}
	printf(" || ");
	Sleep(200);// ������. 
}
// arr = �� �÷��̾��� ī��
/*void throw_card(int* arr) {
	int i = 0;
	int card_num[13] = { 0 };
	int card_overtwo[13] = { '\0' };
	int overtwo = 0;
	while (arr[i] != '\0') {
		card_num[arr[i] % 13]++;
		i++;
	}
	for (i = 0; i < 13; i++) {
		if (card_num[i] >= 2) {
			card_overtwo[overtwo] = i;
			overtwo++;
		}
	}

	int j = 0;
	//card_overtwo = 2�� �̻��� ������ ���
	while (card_overtwo[j] != '\0') {
		for (int k = 0; k < 2; k++) {
			int l = 0;
			while (arr[l] != '\0') {
				if (arr[l] % 13 == card_overtwo[j]) {
					int m = l;
					while (arr[m] != '\0') {
						arr[m] = arr[m + 1];
						m++;
					}
				}
				l++;
			}
		}
		printf("%d ī�� 2���� ���Ƚ��ϴ�.\n", card_overtwo[j] + 1);
		j++;
	}
}*/

int throw_card(Player* p,int* playernum){//,Card* pFreeCard) {
	Card* move = p->card;//card�� ����Ű�� �Ͱ� ���ڰ� ���� ������ �ϳ��� ã�� ������
	Card* card = p->card;//��ü ī�带 ��ȸ�� ������
	int card_arr[13] = { 0, };
	int n = p->card_count;
	int count = 0;
	for (int i = 0; i <= n - 1; i++) {
		if (card->c == 65) {//��Ŀ
			card = card->next;
			continue;
		}
		card_arr[(card->c) % 13] += 1;
		if (card_arr[(card->c) % 13] == 2) {
			for (int j = 0; j <= i - count - 1; j++) {
				if ((move->c) % 13 == (card->c) % 13) {
					if (move->prev == NULL) {//��ī�� �� �� ���� ���� ó���� ���� ��
						p->card->next->prev = NULL;//�÷��̾��� ī�� �����͸� �Ű���� ��
						p->card = p->card->next;
						if (card->next == NULL) {//�� ī�� �� �� ���� ���� ���� ���� ��
							if (card->prev == NULL) {//�� ī�常 2�� ������ ��
							}
							else {
								card->prev->next = NULL;
							}
						}
						else {
							card->next->prev = card->prev;
							if (card->prev != NULL)//ī�� �� ���� �پ� ���� ���� ��
								card->prev->next = card->next;
							else {//�տ��� 2���� �پ� �����Ƿ� �÷��̾� ī�� ������ �� �Ű� ��� ��.
								p->card = p->card->next;
							}

						}
					}
					else if (card->next == NULL) {
						card->prev->next = NULL;
						if (move->next != NULL) {
							move->prev->next = move->next;
							move->next->prev = move->prev;
						}
						else {//������ �پ����� ��
							move->prev->next = NULL;
						}
					}
					else {
						move->prev->next = move->next;
						move->next->prev = move->prev;

						card->prev->next = card->next;
						card->next->prev = card->prev;
					}
					
					printf("%d ī�� 2���� ���Ƚ��ϴ�.\n\n", (card->c) % 13 + 1);
					Sleep(600);
					card_arr[(card->c) % 13] = 0;
					p->card_count -= 2;
					count += 2;
					/*if (pFreeCard != NULL) {
						move->prev = pFreeCard;
						pFreeCard = move;
						move->next = NULL;
					}
					else {
						pFreeCard = move;
						move->prev = NULL;
						move->next = NULL;
					}*/
					move->prev = pFreeCard;//�̷� �� ������ ���������� ����
					pFreeCard = move;
					move->next = NULL;
					card->prev = pFreeCard;
					if (p->card_count == 0) {
						p->prev->next = p->next;
						p->next->prev = p->prev;
						if (p == player_head) {
							player_head = player_head->next;
						}
						printf("player %d���� ī�带 ��� �����Ͽ����ϴ�.\n",p->i);
						printf("player %d���� �����Դϴ�!\n\n", p->i);
						if (pFreePlayer != NULL) {
							p->prev = pFreePlayer;
							pFreePlayer = p;
						}
						else {
							pFreePlayer = p;
							p->prev = NULL;
						}
						*playernum-=1;
						return 1;
					}
					break;
				}
				move = move->next;
			}
			move = p->card;//card�����Ͱ� �Űܰ��� move�� �ʱ�ȭ

		}
		if (card->prev == pFreeCard) {
			//card->prev = pFreeCard;
			pFreeCard = card;
			card = card->next;
			pFreeCard->next = NULL;
		}
		else {
			card = card->next;
		}
	}
	return 0;

}

void printallcard(int playernum, Player* p) {
	Player* player = p;
	//for (int i = 0; i < playernum; i++) {
		int idx = 0;
		printf("[DECK]\n");
		Sleep(300);
		Card* ca = player->card;
		while (ca != NULL) {
			printrealcard(ca->c);
			ca = ca->next;
		}
		printf("\n\n");
		//player = player->next;
	//}
}

void pick_card(Player* p, int n,int* playernum) {
	Card* card;
	Player* pPlayer = p->next;

	card = pPlayer->card;
	if (n != 1) {

		for (int i = 0; i < n - 1; i++)
			card = card->next;
	}
	p->card_count++;
	p->next->card_count--;

	if (card->prev == NULL) {//ù��° ī���� ��
		if (card->next != NULL) {//�� �常 ���� ��찡 �ƴ� ��

			pPlayer->card = card->next;
			card->next = NULL;
		}
		else {
			printf("player%d���� ī�带 ��� �����߽��ϴ�.\n", pPlayer->i);
			printf("player%d���� �����Դϴ�!\n\n", pPlayer->i);
			if (pPlayer == player_head) {
				player_head = player_head->next;
			}
			pPlayer->next->prev = p;
			p->next = pPlayer->next;
			if (pFreePlayer != NULL) {
				pPlayer->prev = pFreePlayer;
				pFreePlayer = pPlayer;
			}
			else {
				pFreePlayer = pPlayer;
				pPlayer->prev = NULL;
			}
			*playernum -= 1;
		}

	}
	else if (card->next == NULL) {//������ ī��
		card->prev->next = NULL;
		card->prev = NULL;
	}
	else {
		card->prev->next = card->next;
		card->next->prev = card->prev;
	}

	card->next = p->card;//���� ī���� next�� ���� �÷��̾��� ù��° ī�带 ����Ű�� ��
	card->prev = NULL;
	p->card->prev = card;//���� �÷��̾��� ù��° ī���� prev�� ���� ī�带 ����Ű�� ��
	p->card = card;//�÷��̾��� card�����Ͱ� ���� ī�带 ����Ű�� ��

}

typedef struct Node {
	int* playerarr;
	struct Node* next;
}Node;

int main(void)
{
	// ī������ ���� ��� ������
	int card_quot, card_remain;
	int playernum = 0;
	int usernum = 0;
	int count = 0;
	int life = 1;
	Card* temp = (Card *)malloc(sizeof(Card));
	pFreeCard = temp;
	pFreeCard->prev = NULL;
	pFreeCard->c = -1;
	// ī�� �й踦 ���� ����
	int allcard[53] = { 0 };
	// 10=�ִ� �÷��̾� 27=ī���� �ִ� ����
	//int player[10][27] = { '\0' };

	// A�� 1�� ��ü, 10�� T�� ��ü�Ͽ� ����
	// ��		: 1=spade, 2=diamond, 3=heart, 4=clover, 5=joker
	// ������	: 0~9=A~10, 10=J, 11=Q, 12=K
	puts("������� ����");
	for (int i = 0; i < NMBR_CARDS; i++)
		allcard[i] = i + 13;

	// ī�带 ���´�
	shuffle(allcard);
	printf("�÷��̾�� �� �� �Դϱ�? \n");
	scanf_s("%d", &playernum);
	usernum = playernum;
	card_quot = NMBR_CARDS / playernum;
	card_remain = NMBR_CARDS % playernum;

	//printf("quot : %d\nremain : %d\n", card_quot, card_remain);
	printf("����ڴ� player%d�Դϴ�.\n", playernum - 1);

	Player* pPlayer=NULL;
	for (int i = 0; i < playernum; i++) {
		Player* p = (Player*)malloc(sizeof(Player));
		p->card_count = 0;
		p->card = NULL;
		p->next = NULL;
		p->prev = NULL;
		p->i = i;
		if (player_head == NULL) {
			player_head = p;
		}
		else {
			p->prev = pPlayer;
			pPlayer->next = p;
		}
		pPlayer = p;
		if (i == playernum - 1) {
			p->next = player_head;
			player_head->prev = p;
		}
	}
	Player* p = player_head;
	for (int i = 0; i < playernum; i++) {
		Card* cb = NULL;
		if (i < card_remain) {
			Card* pCard;
			for (int j = 0; j < card_quot + 1; j++) {
				pCard = (Card *)malloc(sizeof(Card));
				pCard->c = *(allcard + count++);
				pCard->next = NULL;
				pCard->prev = NULL;
				if (p->card == NULL) {
					p->card = pCard;
					cb = pCard;
				}
				else {
					cb->next = pCard;
					pCard->prev = cb;
					cb = cb->next;
				}
				p->card_count++;
			}
		}
		else {
			Card* pCard;
			for (int j = 0; j < card_quot; j++) {
				pCard = (Card *)malloc(sizeof(Card));
				pCard->c = *(allcard + count++);
				pCard->next = NULL;
				pCard->prev = NULL;
				if (p->card == NULL) {
					p->card = pCard;
					cb = pCard;
				}
				else {
					cb->next = pCard;
					pCard->prev = cb;
					cb = cb->next;
				}
				p->card_count++;
			}
		}
		p = p->next;
	}

	Player* me = player_head->prev;
	printallcard(playernum, me);
	Sleep(600);


	puts("ī�� ������ �ð��Դϴ�.\n");
	Sleep(600);

	Player* pr = player_head;
	for (int i = 0; i < playernum; i++) {
		printf("[player%d]\n\n", pr->i);
		Sleep(600);
		if (throw_card(pr, &playernum)) {
			i--;
		}
		pr = pr->next;
	}
	printallcard(playernum, me);
	Sleep(2000);

	//printallcard(playernum, player_head);
	// �� ��忡 ���ּ� �Ҵ�
	//Node node_arr[10] = { '\0' };
	//for (int i = 0; i < playernum; i++) {
	//	node_arr[i].playerarr = player[i];
	//}
	Player* pl = player_head;
	int rn;
	puts("ī�� �̱⸦ �����ϰڽ��ϴ�.\n");
	Sleep(1000);

	while (playernum != 1) {
		printf("���� �÷��̾� �� :%d\n\n", playernum);
		Sleep(600);

		for (int i = 0; i < (playernum - life); i++) {
			printf("<player%d ����>\n\n", pl->i);
			Sleep(1000);
			if (i == playernum - life - 1 && me->card_count != 0) {
				printallcard(playernum, me);
				Sleep(600);
			}

			rn = rand() % pl->next->card_count;
			printf("player%d���� player%d���� ī�带 �̾ҽ��ϴ�.\n\n", pl->i, pl->next->i);
			Sleep(1000);

			pick_card(pl, rn + 1,&playernum);
			//printallcard(playernum, player_head);

			if (throw_card(pl, &playernum)) {//pick_card�� ���� ������ų ���� playernum�� �ٸ鼭 ���� �Ͽ��� ���� �ο��� �ٿ��� ���������
				i--;//thorw_card�� �����鼭 �����ϸ� playernum�� �ٰ� ���� �ο��� �״�� �̹Ƿ� Ƚ���� �������Ѿ� �Ѵ�.
			}
			printf("player%d���� ī��� %d�� ���ҽ��ϴ�\n\n", pl->i, pl->card_count);

			//printallcard(playernum, player_head);
			//printf("\n");
			//Sleep(900);

			pl = pl->next;
			if (playernum == 1)
				break;
		}
		if (playernum == 1)
			break;
		if (pl->i == usernum - 1) {
			printallcard(playernum, me);
			Sleep(600);

			printf("<player%d ����>\n\n", pl->i);
			Sleep(900);

			printf("player%d���� ī��� %d���Դϴ�.\n\n", pl->next->i, pl->next->card_count);
			Sleep(900);
			printf("�� ��° ī�带 �̰ڽ��ϱ�?");
			Sleep(900);
			int p_n = -1;
			scanf("%d", &p_n);
			puts("\n");
			pick_card(pl, p_n, &playernum);
			//printallcard(playernum, player_head);
			printf("player%d���� player%d���� ī�带 �̾ҽ��ϴ�.\n\n", pl->i, pl->next->i);
			Sleep(900);
			throw_card(pl, &playernum);//���� for���� �������
			printf("player%d���� ī��� %d�� ���ҽ��ϴ�\n\n", pl->i, pl->card_count);
			if(me->card_count!=0)
				printallcard(playernum, me);
			Sleep(600);

			printf("\n");

			pl = pl->next;
		}
		else {
			life = 0;
		}
	}
	printf("player %d���� �й��߽��ϴ�.\n", player_head->i);
	if (player_head->i != usernum - 1) {
		if(me->card_count!=0)
			printallcard(playernum, me);
		printf("����ڴ� �¸����Դϴ�!");
	}
	else
		printf("����ڴ� �й����Դϴ�!");
	free(player_head->card);
	free(player_head);
	Card* c = NULL;
	while(pFreeCard!=NULL){
		c = pFreeCard;
		if(pFreeCard!=NULL)
			pFreeCard = pFreeCard->prev;
		//printf("%d ", c->c);
		free(c);
	}
	Player* player = NULL;
	while (pFreePlayer!=NULL) {
		player = pFreePlayer;
		//printf("%d ", player->i);
		if (pFreePlayer->prev != NULL)
			pFreePlayer = pFreePlayer->prev;
		else {
			pFreePlayer = NULL;
		}
		free(player);
	}
	return 0;
}