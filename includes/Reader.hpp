/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:52:53 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/04 12:52:55 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef READER_HPP
# define READER_HPP
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
#include <algorithm>
# include "Exceptions.hpp"

class Reader
{
public:
	static Reader* 	getReader();

	void 							read(int argc, char** argv,
		 								std::shared_ptr<std::vector<std::string>> readedLines);
	void 							trim(std::string& s);
	void 							print(std::shared_ptr<std::vector<std::string>> readedLines);

private:
	Reader();
	Reader(Reader const & rhs) = delete;
	Reader & operator = (Reader const & rhs) = delete;
	virtual ~Reader();

	static Reader					*m_reader;

	WrongInputArgumentCount			m_wrongInput;
};

#endif// READER_HPP
