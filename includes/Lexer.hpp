/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:39:50 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/04 16:39:52 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include <vector>
# include <algorithm>
# include <string>
# include <cctype>
# include <iostream>
# include "Exceptions.hpp"

class Lexer
{
public:
	static Lexer		*getLexer();

	void 			getTokens(std::shared_ptr<std::vector<std::string>> readedLines,
					std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::string>>>> tokenLines);
	void 			printTokenLines(std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::string>>>> tokenLines);

private:
	Lexer();
	Lexer(Lexer const & rhs) = delete;
	Lexer & operator = (Lexer const & rhs) = delete;
	virtual ~Lexer();

	static Lexer		*m_lexer;

	void 			fillTokenLine(std::shared_ptr<std::vector<std::string>> tokenLine,
						std::string const & inputLine);
	EmptyFile		m_emptyFile;
};


#endif
