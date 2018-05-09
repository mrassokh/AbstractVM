/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 09:42:26 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/02 09:42:28 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"



template <class T, eOperandType operandType> Operand<T,operandType>::Operand()
{
    this->init();
	m_operand = new T(0);
}

template <class T, eOperandType operandType> Operand<T,operandType>::Operand(std::string value)
{
    this->init();
    m_operand = static_cast<T*>(createMOperand(value));
}


template <class T, eOperandType operandType> Operand<T,operandType>::Operand(Operand const & rhs)
{
    delete m_operand;

	first_step_init();

    m_toValueFunc = rhs.getToValueFunction();
	m_operandFactory = rhs.getOperandFactory();
	m_resultFunc = rhs.getResultFunction();
	m_operand = static_cast<T*>(createMOperand(rhs.toString()));
}

template <class T, eOperandType operandType> Operand<T,operandType>& Operand<T,operandType>::operator = (Operand const & rhs)
{
    if (this == &rhs)
        return *this;

    delete m_operand;

	first_step_init();

    m_toValueFunc = rhs.getToValueFunction();
	m_operandFactory = rhs.getOperandFactory();
	m_resultFunc = rhs.getResultFunction();
	m_operand = static_cast<T*>(createMOperand(rhs.toString()));

    return *this;
}

template <class T, eOperandType operandType> Operand<T,operandType>::~Operand()
{
    delete m_operand;
}

template <class T, eOperandType operandType> void Operand<T,operandType>::first_step_init()
{
    m_operandType = operandType;
    m_precision = static_cast<int>(operandType);
    m_toStringOutput = "";
}

template <class T, eOperandType operandType> void Operand<T,operandType>::init()
{
	first_step_init();

    m_toValueFunc.push_back(&toInt8);
    m_toValueFunc.push_back(&toInt16);
    m_toValueFunc.push_back(&toInt32);
    m_toValueFunc.push_back(&toFloat);
    m_toValueFunc.push_back(&toDouble);

	m_resultFunc.push_back(&resultAdd);
	m_resultFunc.push_back(&resultSub);
	m_resultFunc.push_back(&resultMult);
	m_resultFunc.push_back(&resultDiv);
	m_resultFunc.push_back(&resultMod);
}

template <class T, eOperandType operandType> int	Operand<T,operandType>::getPrecision( void ) const
{
    return m_precision;
}

template <class T, eOperandType operandType> eOperandType	Operand<T,operandType>::getType( void ) const
{
    return m_operandType;
}

template <class T, eOperandType operandType> std::vector<void* (*)(std::string const & value)>	Operand<T,operandType>::getToValueFunction() const
{
    return m_toValueFunc;
}

template <class T, eOperandType operandType> std::vector<std::string (*)(double const & leftValue, double const & rightValue)>	Operand<T,operandType>::getResultFunction() const
{
	return m_resultFunc;
}

template <class T, eOperandType operandType> OperandFactory		*Operand<T,operandType>::getOperandFactory() const
{
    return m_operandFactory;
}

template <class T, eOperandType operandType> T 	Operand<T,operandType>::getValue() const
{
    return *m_operand;
}

template <class T, eOperandType operandType> void 	Operand<T,operandType>::setOperandFactory(const OperandFactory* operandFactory)
{
    m_operandFactory = const_cast<OperandFactory*>(operandFactory);
}

template <class T, eOperandType operandType> IOperand const * Operand<T,operandType>:: operator + ( IOperand const & rhs ) const
{
    eOperandType    newOperandType;
    std::string     newOperandValue;

    newOperandType = std::max(this->getType(), rhs.getType());
    newOperandValue = m_resultFunc[ADD](std::stold(this->toString()), std::stold(rhs.toString()));
    return m_operandFactory->createOperand(newOperandType, newOperandValue);
}

template <class T, eOperandType operandType> IOperand const * Operand<T,operandType>:: operator - ( IOperand const & rhs ) const
{
	eOperandType    newOperandType;
    std::string     newOperandValue;

    newOperandType = std::max(this->getType(), rhs.getType());
	newOperandValue = m_resultFunc[SUB](std::stold(this->toString()), std::stold(rhs.toString()));

	return  m_operandFactory->createOperand(newOperandType, newOperandValue);
}

template <class T, eOperandType operandType> IOperand const * Operand<T,operandType>:: operator * ( IOperand const & rhs ) const
{
	eOperandType    newOperandType;
    std::string     newOperandValue;

	newOperandType = std::max(this->getType(), rhs.getType());
	newOperandValue = m_resultFunc[MUL](std::stold(this->toString()), std::stold(rhs.toString()));

	return m_operandFactory->createOperand(newOperandType, newOperandValue);
}

template <class T, eOperandType operandType> IOperand const * Operand<T,operandType>:: operator / ( IOperand const & rhs ) const
{
	eOperandType    newOperandType;
	std::string     newOperandValue;

	newOperandType = std::max(this->getType(), rhs.getType());
	newOperandValue = m_resultFunc[DIV](std::stold(this->toString()), std::stold(rhs.toString()));

	return m_operandFactory->createOperand(newOperandType, newOperandValue);
}

template <class T, eOperandType operandType> IOperand const * Operand<T,operandType>:: operator % ( IOperand const & rhs ) const
{
	eOperandType    newOperandType;
	std::string     newOperandValue;

	newOperandType = std::max(this->getType(), rhs.getType());
	newOperandValue = m_resultFunc[MOD](std::stold(this->toString()), std::stold(rhs.toString()));

	return m_operandFactory->createOperand(newOperandType, newOperandValue);
}

template <class T, eOperandType operandType> std::string const & Operand<T,operandType>::toString( void ) const
{
    std::stringstream ss;

    ss <<  std::setprecision(12) << (operandType == INT8 ? static_cast<int>(getValue()): getValue());
	const_cast<std::string &>(m_toStringOutput) = ss.str();

    return m_toStringOutput;
}

template <class T, eOperandType operandType> void	*Operand<T,operandType>::createMOperand(std::string const & value) const
{
    return (*m_toValueFunc[operandType])(value);
}

template <class T, eOperandType operandType> void	*Operand<T,operandType>::toInt8(std::string const & value)
{
	long long int newInt8;

	try
	{
		newInt8 = std::stoll(value);
	}
	catch (std::exception& e)
	{
		throw  exceptUnderflowOverflow;
	}
	if (newInt8 > SCHAR_MAX)
		throw  exceptOverflow;
	else if (newInt8 < SCHAR_MIN)
		throw  exceptUnderflow;
    return new char(newInt8);
}

template <class T, eOperandType operandType> void	*Operand<T,operandType>::toInt16(std::string const & value)
{
	long long int newInt16 = 0;

	try
	{
		newInt16 = std::stoll(value);
	}
	catch (std::exception& e)
	{
		throw  exceptUnderflowOverflow;
	}
	if (newInt16 > SHRT_MAX)
		throw  exceptOverflow;
	else if (newInt16 < SHRT_MIN)
		throw  exceptUnderflow;

    return new short int(newInt16);
}

template <class T, eOperandType operandType> void	*Operand<T,operandType>::toInt32(std::string const & value)
{
	long long int newInt32;

	try
	{
		newInt32 = std::stoll(value);
	}
	catch (std::exception& e)
	{
		throw  exceptUnderflowOverflow;
	}
	if (newInt32 > INT_MAX)
		throw  exceptOverflow;
	else if (newInt32 < INT_MIN)
		throw  exceptUnderflow;
    return new int(newInt32);
}

template <class T, eOperandType operandType> void	*Operand<T,operandType>::toFloat(std::string const & value)
{
	double newFloat;

	try
	{
		newFloat = std::stold(value);
	}
	catch (std::exception& e)
	{
		throw  exceptUnderflowOverflow;
	}
	if (newFloat > FLT_MAX)
		throw  exceptOverflow;
	else if (newFloat < -FLT_MAX)
		throw  exceptUnderflow;
	return new float(newFloat);
}

template <class T, eOperandType operandType> void	*Operand<T,operandType>::toDouble(std::string const & value)
{
	long double newDouble;

	try
	{
		newDouble = std::stold(value);
	}
	catch (std::exception& e)
	{
		throw  exceptUnderflowOverflow;
	}

	if (newDouble > DBL_MAX)
		throw  exceptOverflow;
	else if (newDouble < -DBL_MAX)
		throw  exceptUnderflow;
    return new double(newDouble);
}

template <class T, eOperandType operandType>  std::string		Operand<T,operandType>::resultAdd(double const & leftValue, double const & rightValue)
{
	return (std::to_string(leftValue + rightValue));
}
template <class T, eOperandType operandType>  std::string		Operand<T,operandType>::resultSub(double const & leftValue, double const & rightValue)
{
	return (std::to_string(leftValue - rightValue));
}

template <class T, eOperandType operandType>  std::string		Operand<T,operandType>::resultMult(double const & leftValue, double const & rightValue)
{
	return (std::to_string(leftValue * rightValue));
}

template <class T, eOperandType operandType>  std::string		Operand<T,operandType>::resultDiv(double const & leftValue, double const & rightValue)
{
	if (rightValue == 0 || (rightValue < DBL_MIN && rightValue > -DBL_MIN))
		throw exceptDivideZero;
	return (std::to_string(leftValue / rightValue));
}
template <class T, eOperandType operandType>  std::string		Operand<T,operandType>::resultMod(double const & leftValue, double const & rightValue)
{
	if (rightValue == 0 || (rightValue < DBL_MIN && rightValue > -DBL_MIN))
		throw exceptModZero;
	return (std::to_string(std::fmod(leftValue , rightValue)));
}

template class Operand<char, INT8>;
template class Operand<short int, INT16>;
template class Operand<int, INT32>;
template class Operand<float, FLOAT>;
template class Operand<double, DOUBLE>;

template <class T, eOperandType operandType> ValueOverflowException Operand<T,operandType>:: exceptOverflow;
template <class T, eOperandType operandType> ValueUnderflowException Operand<T,operandType>:: exceptUnderflow;
template <class T, eOperandType operandType> DivideByZeroException Operand<T,operandType>:: exceptDivideZero;
template <class T, eOperandType operandType> ModByZeroException Operand<T,operandType>:: exceptModZero;
template <class T, eOperandType operandType> ValueUnderflowOrOverflowException Operand<T,operandType>:: exceptUnderflowOverflow;
