/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:39:14 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/04 16:39:17 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser():
				m_push_regex("((\\s|\\t|\\r)+)?(push)((\\s|\\t|\\r)+)?"),
				m_pop_regex("((\\s|\\t|\\r)+)?(pop)((\\s|\\t|\\r)+)?"),
				m_dump_regex("((\\s|\\t|\\r)+)?(dump)((\\s|\\t|\\r)+)?"),
				m_assert_regex("((\\s|\\t|\\r)+)?(assert)((\\s|\\t|\\r)+)?"),
				m_addition_regex("((\\s|\\t|\\r)+)?(add)((\\s|\\t|\\r)+)?"),
				m_subtract_regex("((\\s|\\t|\\r)+)?(sub)((\\s|\\t|\\r)+)?"),
				m_multiply_regex("((\\s|\\t|\\r)+)?(mul)((\\s|\\t|\\r)+)?"),
				m_divide_regex("((\\s|\\t|\\r)+)?(div)((\\s|\\t|\\r)+)?"),
				m_modulo_regex("((\\s|\\t|\\r)+)?(mod)((\\s|\\t|\\r)+)?"),
				m_print_regex("((\\s|\\t|\\r)+)?(print)((\\s|\\t|\\r)+)?"),
				m_exit_regex("((\\s|\\t|\\r)+)?(exit)((\\s|\\t|\\r)+)?"),
				m_power_regex("((\\s|\\t|\\r)+)?(pow)((\\s|\\t|\\r)+)?"),
				m_root_regex("((\\s|\\t|\\r)+)?(root)((\\s|\\t|\\r)+)?"),
				m_revert_regex("((\\s|\\t|\\r)+)?(rev)((\\s|\\t|\\r)+)?"),
				m_min_regex("((\\s|\\t|\\r)+)?(min)((\\s|\\t|\\r)+)?"),
				m_max_regex("((\\s|\\t|\\r)+)?(max)((\\s|\\t|\\r)+)?"),
				m_int8_regex("((\\s|\\t|\\r)+)?(int8)((\\s|\\t|\\r)+)?(\\()((\\s|\\t|\\r)+)?(\\+|-)?[\\d]+((\\s|\\t|\\r)+)?(\\))((\\s|\\t|\\r)+)?"),
				m_int16_regex("((\\s|\\t|\\r)+)?(int16)((\\s|\\t|\\r)+)?(\\()((\\s|\\t|\\r)+)?(\\+|-)?[\\d]+((\\s|\\t|\\r)+)?(\\))((\\s|\\t|\\r)+)?"),
				m_int32_regex("((\\s|\\t|\\r)+)?(int32)((\\s|\\t|\\r)+)?(\\()((\\s|\\t|\\r)+)?(\\+|-)?[\\d]+((\\s|\\t|\\r)+)?(\\))((\\s|\\t|\\r)+)?"),
				m_float_regex("((\\s|\\t|\\r)+)?(float)((\\s|\\t|\\r)+)?(\\()((\\s|\\t|\\r)+)?(\\+|-)?[\\d]+(\\.[\\d]+)?((\\s|\\t|\\r)+)?(\\))((\\s|\\t|\\r)+)?"),
				m_double_regex("((\\s|\\t|\\r)+)?(double)((\\s|\\t|\\r)+)?(\\()((\\s|\\t|\\r)+)?(\\+|-)?[\\d]+(\\.[\\d]+)?((\\s|\\t|\\r)+)?(\\))((\\s|\\t|\\r)+)?"),
				m_digit_regex("(\\+|-)?[\\d]+(\\.[\\d]+)?")
{
	m_instr_regex.push_back(m_push_regex);
	m_instr_regex.push_back(m_pop_regex);
	m_instr_regex.push_back(m_dump_regex);
	m_instr_regex.push_back(m_assert_regex);
	m_instr_regex.push_back(m_addition_regex);
	m_instr_regex.push_back(m_subtract_regex);
	m_instr_regex.push_back(m_multiply_regex);
	m_instr_regex.push_back(m_divide_regex);
	m_instr_regex.push_back(m_modulo_regex);
	m_instr_regex.push_back(m_print_regex);
	m_instr_regex.push_back(m_exit_regex);
	m_instr_regex.push_back(m_power_regex);
	m_instr_regex.push_back(m_root_regex);
	m_instr_regex.push_back(m_revert_regex);
	m_instr_regex.push_back(m_min_regex);
	m_instr_regex.push_back(m_max_regex);

	m_value_regex.push_back(m_int8_regex);
	m_value_regex.push_back(m_int16_regex);
	m_value_regex.push_back(m_int32_regex);
	m_value_regex.push_back(m_float_regex);
	m_value_regex.push_back(m_double_regex);

	m_fill_command_func.push_back(&Parser::fillPush);
	m_fill_command_func.push_back(&Parser::fillPop);
	m_fill_command_func.push_back(&Parser::fillDump);
	m_fill_command_func.push_back(&Parser::fillAssert);
	m_fill_command_func.push_back(&Parser::fillAdd);
	m_fill_command_func.push_back(&Parser::fillSub);
	m_fill_command_func.push_back(&Parser::fillMul);
	m_fill_command_func.push_back(&Parser::fillDiv);
	m_fill_command_func.push_back(&Parser::fillMod);
	m_fill_command_func.push_back(&Parser::fillPrint);
	m_fill_command_func.push_back(&Parser::fillExit);
	m_fill_command_func.push_back(&Parser::fillPower);
	m_fill_command_func.push_back(&Parser::fillRoot);
	m_fill_command_func.push_back(&Parser::fillRevert);
	m_fill_command_func.push_back(&Parser::fillMin);
	m_fill_command_func.push_back(&Parser::fillMax);
}

Parser::~Parser()
{

}

Parser* Parser::getParser()
{
	static Parser instance;
	return &instance;
}

void 				Parser::fillPush(std::string const & value,
									std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	fillValue(value, commandStack, counter, PUSH);
}

void 				Parser::fillPop(std::string const & value,
									std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(POP, DEF, value , 1, counter);
	commandStack->push_back(command);
}

void 				Parser::fillDump(std::string const & value,
									 std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(DUMP, DEF, value , 1, counter);
	commandStack->push_back(command);
}

void 				Parser::fillAssert(std::string const & value,
										std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	fillValue(value, commandStack, counter, ASSERT);
}

void 				Parser::fillAdd(std::string const & value,
									std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(ADDITION, DEF, value , 1, counter);
	commandStack->push_back(command);
}

void 				Parser::fillSub(std::string const & value,
									std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(SUBTRACT, DEF, value , 1, counter);
	commandStack->push_back(command);
}

void 				Parser::fillMul(std::string const & value,
									std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(MULTIPLY, DEF, value , 1, counter);
	commandStack->push_back(command);
}

void 				Parser::fillDiv(std::string const & value,
									std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(DIVIDE, DEF, value , 1, counter);
	commandStack->push_back(command);
}

void 				Parser::fillMod(std::string const & value,
									std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(MODULO, DEF, value , 1, counter);
	commandStack->push_back(command);
}

void 				Parser::fillPrint(std::string const & value,
									  std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(PRINT, DEF, value , 1, counter);
	commandStack->push_back(command);

}

void 				Parser::fillExit(std::string const & value,
									std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(EXIT, DEF, value , 1, counter);
	commandStack->push_back(command);
}

void 				Parser::fillPower(std::string const & value,
										std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(POWER, DEF, value , 1, counter);
	commandStack->push_back(command);
}

void 				Parser::fillRoot(std::string const & value,
									std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(ROOT, DEF, value , 1, counter);
	commandStack->push_back(command);
}

void 				Parser::fillRevert(std::string const & value,
										std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(REVERT, DEF, value , 1, counter);
	commandStack->push_back(command);
}


void 				Parser::fillMin(std::string const & value,
									std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	if (value.size())
		throw m_valueAfterCommand;

	Command* command = new Command(MIN, DEF, value , 1, counter);
	commandStack->push_back(command);
}

void 				Parser::fillMax(std::string const & value,
									std::shared_ptr<std::vector<Command *>> commandStack, int counter)
{
	Command* command = new Command(MAX, DEF, value , 1, counter);
	commandStack->push_back(command);
}

void 						Parser::fillValue(std::string const & value,
											  std::shared_ptr<std::vector<Command *>> commandStack, int counter, eCommandType type)
{
	Command* command;

	size_t	f = std::string::npos;
	int		findFlag = 0;
	std::smatch base_match;

	for (size_t i = 0; i < m_value_regex.size(); i++) {
		if (std::regex_match(value, m_value_regex[i])) {
			findFlag = 1;
			f = value.find("(");
			std::string valueCore = std::string(value.begin() + f + 1, value.begin() + value.size());
			if (std::regex_search(valueCore, base_match, m_digit_regex)){
				command = new Command(type, static_cast<eOperandType>(i), base_match[0].str() , 1, counter);
				commandStack->push_back(command);
			}
		}
	}
	if (!findFlag)
		throw m_wrongValueFormat;
}

void Parser::parse(std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::string>>>> 	tokenLines,
										std::shared_ptr<std::vector<Command *>> commandStack,
										std::shared_ptr<std::string> errorLog,
										std::shared_ptr<int> validFlag)
{
	int counter = 0;
	auto line = tokenLines->begin();
	std::string instr = "";
	std::string value = "";
	int findFlag;

	while (line != tokenLines->end())
	{
		if ((*line)->size() != 2 )
			continue ;
		findFlag = 0;
		instr = (*line)->at(0);
		value = (*line)->at(1);
		try
		{
			for (size_t i = 0; i < m_instr_regex.size(); i++) {
				if (std::regex_match(instr, m_instr_regex[i])) {
					findFlag = 1;
					(this->*m_fill_command_func[i])(value, commandStack, counter + 1);
				}
			}
			if (instr.size() && !findFlag)
				throw m_wrongInstrFormat;
		}
		catch (std::exception& e)
		{
			std::stringstream ss;
			ss <<  "ERROR in line " << counter + 1 << " : " << e.what() <<  std::endl;
			*errorLog += ss.str() ;
			*validFlag = 0;
		}
		line++;
		counter++;
	}
}
