/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:03:35 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/02 16:03:40 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Executor.hpp"

Executor* Executor::m_executor = 0;

Executor::Executor()
{
	m_commandFunctions.push_back(&Executor::pushFunc);
	m_commandFunctions.push_back(&Executor::popFunc);
	m_commandFunctions.push_back(&Executor::dumpFunc);
	m_commandFunctions.push_back(&Executor::assertFunc);
	m_commandFunctions.push_back(&Executor::addFunc);
	m_commandFunctions.push_back(&Executor::subFunc);
	m_commandFunctions.push_back(&Executor::mulFunc);
	m_commandFunctions.push_back(&Executor::divFunc);
	m_commandFunctions.push_back(&Executor::modFunc);
	m_commandFunctions.push_back(&Executor::printFunc);
	m_commandFunctions.push_back(&Executor::exitFunc);
	m_commandFunctions.push_back(&Executor::powerFunc);
	m_commandFunctions.push_back(&Executor::rootFunc);
	m_commandFunctions.push_back(&Executor::revertFunc);
	m_commandFunctions.push_back(&Executor::minFunc);
	m_commandFunctions.push_back(&Executor::maxFunc);
	m_exitHappen = 0;
}

Executor::~Executor()
{

}

Executor* Executor::getExecutor()
{
    if (!m_executor)
        m_executor = new Executor();
    return m_executor;
}


void 		Executor::execute(std::shared_ptr<std::vector<Command *>> commandStack,
								std::shared_ptr<std::vector<IOperand *>> operandStack,
								std::shared_ptr<std::string> errorLog,
								std::shared_ptr<int> validFlag,
								std::shared_ptr<std::string> outputLog)
{
     auto command = commandStack->begin();
     while (command != commandStack->end())
     {
		try
		{
			(this->*m_commandFunctions[(*command)->getCommandType()])(*command, operandStack);
			if (*((*command)->getOutput()) != "")
				*outputLog += *((*command)->getOutput());
		}
		catch (Exit& e)
		{
			break;
		}
		catch (std::exception& e)
		{
			std::stringstream ss;
		    ss <<  "Error in line " << (*command)->getLine() << " : " << e.what() <<  std::endl;
			*errorLog += ss.str() ;
			*validFlag = 0;
		}
		*command++;
     }

	 if (!m_exitHappen)
		 throw m_exitNotFind;
	 else
		 m_exitHappen = 0;
}

void 		Executor::pushFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;

	OperandFactory* of = OperandFactory::getOperandFactory();
	IOperand* newOperand = const_cast<IOperand*>(of->createOperand(command->getOperandType(),command->getValue()));
	operandStack->push_back(newOperand);
}

void 		Executor::popFunc(Command *command,	std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;
	if (!operandStack->size())
		throw m_stackIsEmpty;

	delete (*operandStack)[operandStack->size() - 1];
	operandStack->pop_back();
}

void 		Executor::dumpFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;

	int counter = operandStack->size();
	while (counter)
	{
		*(command->getOutput()) += operandStack->at(--counter)->toString();
		*(command->getOutput()) += "\n";
	}
}


void 		Executor::assertFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;
	if (!operandStack->size())
		throw m_stackIsEmpty;
	if (operandStack->back()->getType() !=  command->getOperandType()
		||	operandStack->back()->toString() != command->getValue())
		{
			throw m_assertFail;
		}

}

void 		Executor::addFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;
	calculation(ADDITION, operandStack);
}

void 		Executor::subFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;
	calculation(SUBTRACT, operandStack);
}

void 		Executor::mulFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;
	calculation(MULTIPLY, operandStack);
}
void 		Executor::divFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;
	calculation(DIVIDE, operandStack);
}

void 		Executor::modFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;
	calculation(MODULO, operandStack);
}

void 		Executor::printFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;
	if (!operandStack->size())
		throw m_stackIsEmpty;
	if (operandStack->back()->getType() != INT8)
		throw m_topStackIsNotINT8;

	char printString[2];
	char print = static_cast<Operand<char, INT8> *>(operandStack->back())->getValue();

	printString[0] = print;
	printString[1] = '\0';
	if (!isprint(print))
		throw m_charIsNotPrintable;
	*(command->getOutput()) += std::string(printString);
	*(command->getOutput()) += "\n";
}

void 		Executor::exitFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;

	operandStack->clear();
	m_exitHappen++;
	throw m_exit;
}

void 		Executor::powerFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;

	calculation(POWER, operandStack);
}

void 		Executor::rootFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;

	calculation(ROOT, operandStack);
}

void 		Executor::revertFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;
	if (operandStack->size() < 1)
		throw m_stackIsEmpty;

	IOperand *v1 = operandStack->back();
	double newValue = 1 / std::stold(v1->toString());

	delete v1;
	operandStack->pop_back();
	IOperand* newOperand = const_cast<IOperand*>(OperandFactory::getOperandFactory()->createOperand(DOUBLE, std::to_string(newValue)));
	operandStack->push_back(newOperand);
}

void 		Executor::minFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;
	if (operandStack->size() < 2)
		throw m_stackSizeLessTwo;

	IOperand *v1 = operandStack->back();
	IOperand *v2 = operandStack->at(operandStack->size() - 2);

	if (std::stold(v2->toString()) <= std::stold(v1->toString()))
	{
		delete v1;
		operandStack->pop_back();
	}
	else
	{
		delete v2;
		operandStack->erase(operandStack->begin() + operandStack->size() - 2);
	}
}

void 		Executor::maxFunc(Command *command, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (!command->getValid())
		return;
	if (operandStack->size() < 2)
		throw m_stackSizeLessTwo;

	IOperand *v1 = operandStack->back();
	IOperand *v2 = operandStack->at(operandStack->size() - 2);

	if (std::stold(v2->toString()) >= std::stold(v1->toString()))
	{
		delete v1;
		operandStack->pop_back();
	}
	else
	{
		delete v2;
		operandStack->erase(operandStack->begin() + operandStack->size() - 2);
	}
}


void 		Executor::calculation(eCommandType type, std::shared_ptr<std::vector<IOperand *>> operandStack)
{
	if (operandStack->size() < 2)
		throw m_stackSizeLessTwo;

	IOperand *newOperand = nullptr;
	IOperand *v1 = operandStack->back();
	IOperand *v2 = operandStack->at(operandStack->size() - 2);

	if (type == ADDITION)
		newOperand = const_cast<IOperand*>(*v2 + *v1);
	else if (type == SUBTRACT)
		newOperand = const_cast<IOperand*>(*v2 - *v1);
	else if (type == MULTIPLY)
		newOperand = const_cast<IOperand*>(*v2 * *v1);
	else if (type == DIVIDE)
		newOperand = const_cast<IOperand*>(*v2 / *v1);
	else if (type == MODULO)
		newOperand = const_cast<IOperand*>(*v2 % *v1);
	else if (type == POWER)
		newOperand = const_cast<IOperand*>(OperandFactory::getOperandFactory()->createOperand(std::max(v1->getType(), v2->getType()),
		 																std::to_string(pow(std::stold(v2->toString()), std::stold(v1->toString())))));
	else if (type == ROOT)
	{
		double root = 1 / std::stold(v1->toString());
		newOperand = const_cast<IOperand*>(OperandFactory::getOperandFactory()->createOperand(DOUBLE,
													std::to_string(pow(std::stold(v2->toString()), root))));
	}


	delete v1;
	delete v2;
	operandStack->pop_back();
	operandStack->pop_back();
	operandStack->push_back(newOperand);
}
