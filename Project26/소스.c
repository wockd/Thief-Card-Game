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
// 배열을 섞는 함수이다
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
	case 1: printf("%-3s", "♠"); break;
	case 2: printf("%-3s", "◆"); break;
	case 3:	printf("%-3s", "♥"); break;
	case 4:	printf("%-3s", "♣"); break;
	case 5:	printf("%-5s", "★"); break;
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
	Sleep(200);// 수정함. 
}
// arr = 한 플레이어의 카드
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
	//card_overtwo = 2개 이상인 숫자의 목록
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
		printf("%d 카드 2장을 버렸습니다.\n", card_overtwo[j] + 1);
		j++;
	}
}*/

int throw_card(Player* p,int* playernum){//,Card* pFreeCard) {
	Card* move = p->card;//card가 가리키는 것과 숫자가 같은 나머지 하나를 찾을 포인터
	Card* card = p->card;//전체 카드를 순회할 포인터
	int card_arr[13] = { 0, };
	int n = p->card_count;
	int count = 0;
	for (int i = 0; i <= n - 1; i++) {
		if (card->c == 65) {//조커
			card = card->next;
			continue;
		}
		card_arr[(card->c) % 13] += 1;
		if (card_arr[(card->c) % 13] == 2) {
			for (int j = 0; j <= i - count - 1; j++) {
				if ((move->c) % 13 == (card->c) % 13) {
					if (move->prev == NULL) {//뺄카드 중 한 장이 제일 처음에 있을 때
						p->card->next->prev = NULL;//플레이어의 카드 포인터를 옮겨줘야 함
						p->card = p->card->next;
						if (card->next == NULL) {//뺄 카드 중 한 장이 제일 끝에 있을 때
							if (card->prev == NULL) {//뺄 카드만 2장 남았을 때
							}
							else {
								card->prev->next = NULL;
							}
						}
						else {
							card->next->prev = card->prev;
							if (card->prev != NULL)//카드 두 장이 붙어 있지 않을 때
								card->prev->next = card->next;
							else {//앞에서 2장이 붙어 있으므로 플레이어 카드 포인터 또 옮겨 줘야 함.
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
						else {//끝에서 붙어있을 때
							move->prev->next = NULL;
						}
					}
					else {
						move->prev->next = move->next;
						move->next->prev = move->prev;

						card->prev->next = card->next;
						card->next->prev = card->prev;
					}
					
					printf("%d 카드 2장을 버렸습니다.\n\n", (card->c) % 13 + 1);
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
					move->prev = pFreeCard;//이런 거 때문에 전역변수로 정의
					pFreeCard = move;
					move->next = NULL;
					card->prev = pFreeCard;
					if (p->card_count == 0) {
						p->prev->next = p->next;
						p->next->prev = p->prev;
						if (p == player_head) {
							player_head = player_head->next;
						}
						printf("player %d님은 카드를 모두 소진하였습니다.\n",p->i);
						printf("player %d님은 승자입니다!\n\n", p->i);
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
			move = p->card;//card포인터가 옮겨가면 move는 초기화

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

	if (card->prev == NULL) {//첫번째 카드일 때
		if (card->next != NULL) {//한 장만 남은 경우가 아닐 때

			pPlayer->card = card->next;
			card->next = NULL;
		}
		else {
			printf("player%d님은 카드를 모두 소진했습니다.\n", pPlayer->i);
			printf("player%d님은 승자입니다!\n\n", pPlayer->i);
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
	else if (card->next == NULL) {//마지막 카드
		card->prev->next = NULL;
		card->prev = NULL;
	}
	else {
		card->prev->next = card->next;
		card->next->prev = card->prev;
	}

	card->next = p->card;//뽑은 카드의 next를 현재 플레이어의 첫번째 카드를 가리키게 함
	card->prev = NULL;
	p->card->prev = card;//현재 플레이어의 첫번째 카드의 prev가 뽑은 카드를 가리키게 함
	p->card = card;//플레이어의 card포인터가 뽑은 카드를 가리키게 함

}

typedef struct Node {
	int* playerarr;
	struct Node* next;
}Node;

int main(void)
{
	// 카드계산을 위한 몫과 나머지
	int card_quot, card_remain;
	int playernum = 0;
	int usernum = 0;
	int count = 0;
	int life = 1;
	Card* temp = (Card *)malloc(sizeof(Card));
	pFreeCard = temp;
	pFreeCard->prev = NULL;
	pFreeCard->c = -1;
	// 카드 분배를 위한 선언
	int allcard[53] = { 0 };
	// 10=최대 플레이어 27=카드의 최대 개수
	//int player[10][27] = { '\0' };

	// A는 1로 대체, 10은 T로 대체하여 저장
	// 몫		: 1=spade, 2=diamond, 3=heart, 4=clover, 5=joker
	// 나머지	: 0~9=A~10, 10=J, 11=Q, 12=K
	puts("도둑잡기 게임");
	for (int i = 0; i < NMBR_CARDS; i++)
		allcard[i] = i + 13;

	// 카드를 섞는다
	shuffle(allcard);
	printf("플레이어는 몇 명 입니까? \n");
	scanf_s("%d", &playernum);
	usernum = playernum;
	card_quot = NMBR_CARDS / playernum;
	card_remain = NMBR_CARDS % playernum;

	//printf("quot : %d\nremain : %d\n", card_quot, card_remain);
	printf("사용자는 player%d입니다.\n", playernum - 1);

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


	puts("카드 버리는 시간입니다.\n");
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
	// 각 노드에 원주소 할당
	//Node node_arr[10] = { '\0' };
	//for (int i = 0; i < playernum; i++) {
	//	node_arr[i].playerarr = player[i];
	//}
	Player* pl = player_head;
	int rn;
	puts("카드 뽑기를 시작하겠습니다.\n");
	Sleep(1000);

	while (playernum != 1) {
		printf("현재 플레이어 수 :%d\n\n", playernum);
		Sleep(600);

		for (int i = 0; i < (playernum - life); i++) {
			printf("<player%d 차례>\n\n", pl->i);
			Sleep(1000);
			if (i == playernum - life - 1 && me->card_count != 0) {
				printallcard(playernum, me);
				Sleep(600);
			}

			rn = rand() % pl->next->card_count;
			printf("player%d님이 player%d님의 카드를 뽑았습니다.\n\n", pl->i, pl->next->i);
			Sleep(1000);

			pick_card(pl, rn + 1,&playernum);
			//printallcard(playernum, player_head);

			if (throw_card(pl, &playernum)) {//pick_card로 남을 소진시킬 때는 playernum이 줄면서 현재 턴에서 남은 인원도 줄여서 상관없지만
				i--;//thorw_card로 버리면서 소진하면 playernum은 줄고 남은 인원은 그대로 이므로 횟수를 차감시켜야 한다.
			}
			printf("player%d님의 카드는 %d장 남았습니다\n\n", pl->i, pl->card_count);

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

			printf("<player%d 차례>\n\n", pl->i);
			Sleep(900);

			printf("player%d님의 카드는 %d장입니다.\n\n", pl->next->i, pl->next->card_count);
			Sleep(900);
			printf("몇 번째 카드를 뽑겠습니까?");
			Sleep(900);
			int p_n = -1;
			scanf("%d", &p_n);
			puts("\n");
			pick_card(pl, p_n, &playernum);
			//printallcard(playernum, player_head);
			printf("player%d님이 player%d님의 카드를 뽑았습니다.\n\n", pl->i, pl->next->i);
			Sleep(900);
			throw_card(pl, &playernum);//위의 for문과 상관없음
			printf("player%d님의 카드는 %d장 남았습니다\n\n", pl->i, pl->card_count);
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
	printf("player %d님이 패배했습니다.\n", player_head->i);
	if (player_head->i != usernum - 1) {
		if(me->card_count!=0)
			printallcard(playernum, me);
		printf("사용자는 승리자입니다!");
	}
	else
		printf("사용자는 패배자입니다!");
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