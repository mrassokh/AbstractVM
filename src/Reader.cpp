/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:53:13 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/04 12:53:17 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reader.hpp"

Reader *Reader::m_reader = 0;

Reader::Reader()
{

}

Reader::~Reader()
{

}

Reader* 	Reader::getReader()
{
	if (!m_reader)
		m_reader = new Reader();
	return m_reader;

}

void 			Reader::read(int argc, char** argv, std::shared_ptr<std::vector<std::string>> readedLines)
{
	std::string inputLine = "";
	size_t	f = std::string::npos;
	if (argc == 1)
	{
		while (1)
		{
			if (!std::getline (std::cin, inputLine))
				break;
			trim(inputLine);
			f = inputLine.find(";;");
			if (f != std::string::npos)
			{
				inputLine = std::string(inputLine.begin(), inputLine.begin() + f);
				if (f)
					readedLines->push_back(std::string(inputLine));
				break;
			}
			readedLines->push_back(std::string(inputLine));
		}
	}
	else if (argc == 2)
	{
		std::ifstream myfile (argv[1]);
  		if (myfile.is_open())
  		{
    		while (getline(myfile,inputLine))
    		{
				trim(inputLine);
      			readedLines->push_back(std::string(inputLine));
    		}
    		myfile.close();
		}
		else
			throw std::runtime_error("Could not open file");
	}
	else
		throw m_wrongInput;
}

void 			Reader::print(std::shared_ptr<std::vector<std::string>> readedLines)
{
	if (!readedLines)
		return;
	auto line = readedLines->begin();
	while (line != readedLines->end())
	{
		std::cout << *line << std::endl;
		line++;
	}
}

void 			Reader::trim(std::string& s)
 {
   	size_t p = s.find_first_not_of(" \t");
  	s.erase(0, p);
    p = s.find_last_not_of(" \t");
  	if (std::string::npos != p)
  		s.erase(p + 1);
 }
