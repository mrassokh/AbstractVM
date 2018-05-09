/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:43:39 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/09 10:43:41 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVM.hpp"

AbstractVM::AbstractVM()
{
	m_readedLines = std::shared_ptr<std::vector<std::string>>(new std::vector<std::string>);
	m_tokenLines = std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::string>>>>(new std::vector<std::shared_ptr<std::vector<std::string>>>);
	m_commandStack = std::shared_ptr<std::vector<Command *>>(new std::vector<Command *>);
	m_operandStack = std::shared_ptr<std::vector<IOperand *>>(new std::vector<IOperand *>);
	m_outputLog = std::shared_ptr<std::string>(new std::string);
	m_errorLog = std::shared_ptr<std::string>(new std::string);
	m_validFlag = std::shared_ptr<int>(new int);
	*m_outputLog = "";
	*m_errorLog = "";
	*m_validFlag = 1;
	m_reader = Reader::getReader();
	m_lexer = Lexer::getLexer();
	m_parser = Parser::getParser();
	m_executor = Executor::getExecutor();
}


AbstractVM::~AbstractVM()
{

}

AbstractVM					&AbstractVM::Instance()
{
	static AbstractVM instance;
	return instance;
}

void 						AbstractVM::procesing(int argc, char** argv)
{
	read(argc,argv);
	lexing();
	parsing();
   	execute();
	printResults();
}

void 						AbstractVM::read(int argc, char** argv)
{
	try
	{
		m_reader->read(argc, argv, m_readedLines);
	}
	catch (std::exception& e)
	{
		errorLog(e);
	}
}

void 						AbstractVM::lexing()
{
	if (!*m_validFlag)
		return;

	try
	{
		m_lexer->getTokens(m_readedLines, m_tokenLines);
	}
	catch (std::exception& e)
	{
		errorLog(e);
	}
}

void 						AbstractVM::parsing()
{
	if (!*m_validFlag)
		return;
	m_parser->parse(m_tokenLines, m_commandStack, m_errorLog, m_validFlag);
}

void 						AbstractVM::execute()
{
	if (!*m_validFlag)
		return;

	try
	{
		m_executor->execute(m_commandStack, m_operandStack, m_errorLog, m_validFlag, m_outputLog);
	}
	catch (std::exception& e)
	{
		errorLog(e);
	}
}

void 						AbstractVM::printResults()
{
	if (!*m_validFlag)
		std::cout << *m_errorLog;
	else
		std::cout << *m_outputLog;
}

void 						AbstractVM::errorLog(std::exception& e)
{
	std::stringstream ss;
	ss <<  "ERROR : " << e.what() <<  std::endl;
	*m_errorLog += ss.str() ;
	*m_validFlag = 0;
}
