#include <iostream>
#include <limits>

#include "bookexample.h"
#include "tcpexample.h"
#include "chatbot.h"
#include "nosingleton.h"

int main()
{
	std::cout << "Choose a demo option\n1. Book Example"
		"\n2. ChatBot\n3. No Singleton" << std::endl;

	int option{};
	std::cin >> option;
	// Ensure there is no extraneous input left in the buffer including newline
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	switch (option)
	{
	case 1:
	{
		book::run_book_demo();
		break;
	}
	case 2:
	{
		chat::run_chat_demo();
		break;
	}
	case 3:
	{
		nosingleton::run_nosingleton_demo();
		break;
	}
	/* case 4:
	{
		// Work in progress
		tcp::run_tcp_demo();
		break;
	} */
	default:
	{
		std::cout << "Invalid Option" << std::endl;
		break;
	}
	}

	return 0;
}
