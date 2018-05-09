/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:46:42 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/09 10:46:43 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"

OperandFactory* OperandFactory::m_operandFactory = 0;


OperandFactory::OperandFactory()
{
    m_createFunctions.push_back(&OperandFactory::createInt8);
    m_createFunctions.push_back(&OperandFactory::createInt16);
    m_createFunctions.push_back(&OperandFactory::createInt32);
    m_createFunctions.push_back(&OperandFactory::createFloat);
    m_createFunctions.push_back(&OperandFactory::createDouble);
}

OperandFactory::~OperandFactory()
{

}

OperandFactory* OperandFactory::getOperandFactory()
{
    if (!m_operandFactory)
        m_operandFactory = new OperandFactory();
    return m_operandFactory;
}


IOperand const * OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
    return (this->*m_createFunctions[type])(value);
}

IOperand const * OperandFactory::createInt8(std::string const & value)  const
{
    Operand<char, INT8> *newOperand = new Operand<char, INT8>(value);
    newOperand->setOperandFactory(this);
    return newOperand;
}

IOperand const * OperandFactory::createInt16(std::string const & value ) const
{
    Operand<short int, INT16> *newOperand = new Operand<short int, INT16>(value);
    newOperand->setOperandFactory(this);
    return newOperand;
}

IOperand const * OperandFactory::createInt32(std::string const & value) const
{
    Operand<int, INT32> *newOperand = new Operand<int, INT32>(value);
    newOperand->setOperandFactory(this);
    return newOperand;
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const
{
    Operand<float, FLOAT> *newOperand = new Operand<float, FLOAT>(value);
    newOperand->setOperandFactory(this);
    return newOperand;

}

IOperand const * OperandFactory::createDouble( std::string const & value ) const
{
    Operand<double, DOUBLE> *newOperand = new Operand<double, DOUBLE>(value);
    newOperand->setOperandFactory(this);
    return newOperand;
}
