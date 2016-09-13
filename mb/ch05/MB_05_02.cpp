#include <stdexcept>

#include "MB_05_02.hpp"

double TemperatureConverter::celsiusToKelvin(const double& celsius)
{
	if(celsius < CESIUS_MIN)
	{
		std::out_of_range error("Celsius temperature should be at least " 
		                        + std::to_string(CESIUS_MIN));
		throw error;
	}
	
	double kelvin = celsius + 273.15;
	return kelvin;
}

double TemperatureConverter::kelvinToCelsius(const double& kelvin)
{
	if(kelvin < KELVIN_MIN)
	{
		std::out_of_range error("Kelvin temperature should be at least" 
		                        + std::to_string(KELVIN_MIN));
		throw error;
	}
	
	double celsius = kelvin - 273.15;
	return celsius;
}

double TemperatureConverter::celsiusToFahrenheit(const double& celsius)
{
	if(celsius < CESIUS_MIN)
	{
		std::out_of_range error("Celsius temperature should be at least" 
		                        + std::to_string(CESIUS_MIN));
		throw error;
	}
	
	double fahrenheit = 32.0 + (1.8 * celsius);
	return fahrenheit;
}

double TemperatureConverter::fahrenheitToCelsius(const double& fahrenheit)
{
	if(fahrenheit < FAHRENHEIT_MIN)
	{
		std::out_of_range error("Fahrenheit temperature should be at least" 
		                        + std::to_string(FAHRENHEIT_MIN));
		throw error;
	}
	double celsius = (fahrenheit - 32.0) / 1.8;
	return celsius;
}
