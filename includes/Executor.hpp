/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:02:59 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/02 16:03:02 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_HPP
# define EXECUTOR_HPP

# include "Operand.hpp"
# include "Command.hpp"
# include <vector>
# include <algorithm>
# include <string>
# include <cctype>
# include <iostream>
# include "Operand.hpp"
# include "Exceptions.hpp"

class Executor
{
public:
	static Executor* 	getExecutor();
	void 				execute(std::shared_ptr<std::vector<Command *>> commandStack,
								std::shared_ptr<std::vector<IOperand *>> operandStack,
								std::shared_ptr<std::string> errorLog,
								std::shared_ptr<int> validFlag,
								std::shared_ptr<std::string> outputLog);
private:
	Executor();
	Executor(Executor const & rhs) = delete;
	Executor & operator = (Executor const & rhs) = delete;
	virtual ~Executor();

	static Executor       											*m_executor;

	std::vector<void (Executor::*)(Command *command,
		std::shared_ptr<std::vector<IOperand *>> operandStack)>		m_commandFunctions;
	int																m_exitHappen;

	//Exceptions
	StackIsEmpty													m_stackIsEmpty;
	AssertFail														m_assertFail;
	TopStackIsNotINT8												m_topStackIsNotINT8;
	StackSizeLessTwo												m_stackSizeLessTwo;
	CharIsNotPrintable												m_charIsNotPrintable;
	ExitNotFind														m_exitNotFind;
	Exit															m_exit;

	void 				pushFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				dumpFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				popFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				assertFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				addFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				subFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				mulFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				divFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				modFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				printFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				exitFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				powerFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				rootFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				revertFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				minFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				maxFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack);
	void 				calculation(eCommandType type, std::shared_ptr<std::vector<IOperand *>> operandStack);
};

#endif
