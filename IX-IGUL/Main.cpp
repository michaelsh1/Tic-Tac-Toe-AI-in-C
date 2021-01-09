#include "Engine.h"
#include "Game.h"

void main()
{
	while (1)
	{
		Play();

		printf("Play another game? YES[Y \ y] \ NO[N \ n]\n");
		char input = ' ';
		while (input != '\0')
		{
			scanf(" %c", &input);
			switch (input)
			{
				case 'N':
				case 'n':
					printf("Thanks for playing!\n");
					return;
				case 'Y':
				case 'y':
					input = '\0';
					break;
				default:
					printf("Invalid input. Only use: YES[Y \ y] or NO[N \ n].\n");
					break;
			}
		}
	}
}