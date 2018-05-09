/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 13:27:03 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/02 13:27:05 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command()
{
	m_commandType = DEFAULT;
	m_operandType = DEF;
	m_value = "";
	m_isValid = 0;
	m_commandOutput = std::shared_ptr<std::string>(new std::string);
	*m_commandOutput = "";
}

Command::Command(eCommandType commandType, eOperandType operandType,
					std::string const & value, int isValid, int line)
						: m_commandType(commandType),
						  m_operandType(operandType),
						  m_value(value),
						  m_line(line),
						  m_isValid(isValid)
{
	m_commandOutput = std::shared_ptr<std::string>(new std::string);
	*m_commandOutput = "";
}

Command::Command(Command const & rhs)
{
	m_commandType = rhs.getCommandType();
	m_operandType = rhs.getOperandType();
	m_value = rhs.getValue();
	m_isValid = rhs.getValid();
	m_commandOutput = std::shared_ptr<std::string>(new std::string);
	*m_commandOutput = *(rhs.getCommandOutput());
}

Command& Command::operator = (Command const & rhs)
{
	if (this == &rhs)
		return *this;

	m_commandType = rhs.getCommandType();
	m_operandType = rhs.getOperandType();
	m_value = rhs.getValue();
	m_isValid = rhs.getValid();
	m_commandOutput = std::shared_ptr<std::string>(new std::string);
	*m_commandOutput = *(rhs.getCommandOutput());

	return *this;
}

Command::~Command()
{

}

std::string const & 			Command::getValue() const
{
	return m_value;
}

eCommandType const & 			Command::getCommandType() const
{
	return m_commandType;
}

eOperandType const & 			Command::getOperandType() const
{
	return m_operandType;
}

int const & 					Command::getValid() const
{
	return m_isValid;
}

int const & 					Command::getLine() const
{
	return m_line;
}

void 							Command::toString() const
{
	std::cout << "Command with type " << getCommandType() << " value is " << getValue() << " operand type is"
				<< getOperandType()<< " and valid is " << getValid()<< " in line " << getLine() << std::endl;
}

std::shared_ptr<std::string>	Command::getOutput()
{
	return 	m_commandOutput;
}

std::shared_ptr<std::string>	Command::getCommandOutput() const
{
	return 	m_commandOutput;
}
