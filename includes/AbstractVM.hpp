/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:15:03 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/02 12:15:05 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP
#include "Operand.hpp"
#include "Command.hpp"
#include "Executor.hpp"
#include "Reader.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

class AbstractVM
{
public:
	static	AbstractVM					&Instance();
	void 							procesing(int argc, char** argv);
	void 							read(int argc, char** argv);
	void 							lexing();
	void 							parsing();
	void 							execute();
	void 							printResults();
	void 							errorLog(std::exception& e);

private:
	AbstractVM();
	AbstractVM(AbstractVM const & rhs) = delete;
	AbstractVM & operator = (AbstractVM const & rhs) = delete;
	~AbstractVM();

	Reader							*m_reader;
	Lexer							*m_lexer;
	Parser							*m_parser;
	Executor						*m_executor;

	std::shared_ptr<std::vector<std::string>> 		m_readedLines;
	std::shared_ptr<std::vector
	<std::shared_ptr<std::vector<std::string>>>> 		m_tokenLines;
	std::shared_ptr<std::vector<Command *>> 		m_commandStack;
	std::shared_ptr<std::vector<IOperand *>> 		m_operandStack;
	std::shared_ptr<std::string>				m_errorLog;
	std::shared_ptr<std::string>				m_outputLog;
	std::shared_ptr<int>					m_validFlag;
};

#endif // ABSTRACTVM_HPP
