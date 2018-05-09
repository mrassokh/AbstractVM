/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:39:25 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/04 16:39:27 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer		*Lexer::m_lexer = 0;

Lexer::Lexer()
{

}

Lexer::~Lexer()
{

}

Lexer		*Lexer::getLexer()
{
	if (!m_lexer)
		m_lexer = new Lexer();

	return m_lexer;
}

void 		Lexer::getTokens(std::shared_ptr<std::vector<std::string>> readedLines,
	 					std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::string>>>> tokenLines)
{
	if (!readedLines->size())
		throw m_emptyFile;

	auto line = readedLines->begin();
	while (line != readedLines->end())
	{
		std::shared_ptr<std::vector<std::string>> tokenLine =  std::shared_ptr<std::vector<std::string>>(new std::vector<std::string>);
		fillTokenLine(tokenLine,*line);
		tokenLines->push_back(tokenLine);
		line++;
	}
}

void 		Lexer::fillTokenLine(std::shared_ptr<std::vector<std::string>> tokenLine, std::string const & inputLine)
{
	size_t	f = std::string::npos;
	std::string line = "";
	std::string instr = "";
	std::string value = "";

	//take string before comment char ';'
	f = inputLine.find(";");
	if (f != std::string::npos)
		line = std::string(inputLine.begin(), inputLine.begin() + f);
	else
		line = inputLine;

	//split string to instruction and value
	f = line.find(" ");
	std::size_t found = line.find_first_of(" \t\n\r\f\v");
	if (found != std::string::npos)
	{
		instr = std::string(line.begin(), line.begin() + found);
		value = std::string(line.begin() + found + 1, line.begin() + line.size());
	}
	else
		instr = line;
	tokenLine->push_back(instr);
	tokenLine->push_back(value);
}

void 		Lexer::printTokenLines(std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::string>>>> tokenLines)
{
	int counter = 0;
	auto line = tokenLines->begin();
	while (line != tokenLines->end())
	{
		std::cout << "PRINT line number " << counter++ << std::endl;
		auto token = (*line)->begin();
		while (token != (*line)->end())
		{
			std::cout << *token << std::endl;
			token++;
		}
		std::cout << std::endl;
		line++;
	}
}
