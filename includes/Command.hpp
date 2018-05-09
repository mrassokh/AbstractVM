/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 13:26:36 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/02 13:26:40 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP
#include "IOperand.hpp"
#include <string>
#include <iostream>

enum eCommandType {
	PUSH,
	POP,
	DUMP,
	ASSERT,
	ADDITION,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	MODULO,
	PRINT,
	EXIT,
	POWER,
	ROOT,
	REVERT,
	MIN,
	MAX,
	DEFAULT
};

class Command
{
public:
	Command();
	Command(eCommandType commandType, eOperandType operandType,
			std::string const & value, int is_Valid, int line);
	Command(Command const & rhs);
	Command& operator = (Command const & rhs);
	virtual ~Command();

	std::string const 				& getValue() const;
	eCommandType const 				& getCommandType() const;
	eOperandType const 				& getOperandType() const;
	int const						& getValid() const;
	int const						& getLine() const;
	void 							toString() const;
	std::shared_ptr<std::string>	getOutput();
	std::shared_ptr<std::string>	getCommandOutput() const;
private:
	eCommandType					m_commandType;
	eOperandType					m_operandType;
	std::string						m_value;
	std::shared_ptr<std::string>	m_commandOutput;
	int								m_line;
	int								m_isValid;
};

#endif
