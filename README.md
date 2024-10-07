# Thief-Card-Game
Project Overview: Thief Card Game

This project is a simple implementation of a Thief Card Game using C. The game is designed for multiple players, where players draw and discard cards until one remains. The goal is to eliminate all cards by discarding matching pairs, with a unique card left at the end that determines the loser.

Key Features:

Card Shuffling and Distribution: The cards are shuffled and distributed evenly among players. One player will be left with an extra card, the Joker.

Gameplay Mechanics: Players take turns drawing cards from each other and discarding pairs until no pairs remain. The last player with cards loses the game.

Player and Card Management: The game uses linked lists to manage players and their cards, allowing for dynamic addition and removal during gameplay.

Data Structures:

Card Struct: Represents each card, with pointers to the next and previous cards in the player's hand. Each card has a value (int c), and the pointers (Card* next and Card* prev) help maintain the linked list structure for the player's hand.

Player Struct: Represents each player, with a linked list of cards and counters for the number of cards held. The int i variable is used to identify the player, and Card* card points to the head of the player's card list. The linked list structure (Player* next and Player* prev) allows easy traversal between players.

Important Variables and Implementation Details:

player_head: This is a pointer to the first player in the circular linked list of players. It helps in managing the sequence of turns during gameplay.

pFreeCard and pFreePlayer: These pointers are used to keep track of cards and players that have been removed from the game. By reusing these nodes, the program manages memory efficiently and avoids repeated allocations.

Shuffling Cards: The shuffle function takes an array of card values and randomly swaps elements to simulate shuffling. The srand(time(NULL)) call ensures that the shuffle is different each time the game runs.

Drawing and Discarding Cards: The core gameplay involves players drawing cards from the next player and then discarding any matching pairs. The pick_card function is responsible for drawing a card from the next player, while throw_card identifies and removes pairs from a player's hand.

Linked List Management: The game relies heavily on linked list operations. For example, when a card is drawn or discarded, the pointers (next and prev) are updated to maintain the integrity of the linked list. This dynamic approach allows for flexible game mechanics where players can gain or lose cards seamlessly.

This project demonstrates fundamental C programming concepts such as linked lists, dynamic memory allocation, and game logic implementation. It provides a good example of how to manage complex relationships between game entities using pointers and data structures.
