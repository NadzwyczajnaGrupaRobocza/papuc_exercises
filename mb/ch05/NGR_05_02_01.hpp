#pragma once

constexpr double CESIUS_MIN = -273.15;
constexpr double KELVIN_MIN = 0;
constexpr double FAHRENHEIT_MIN = -459.67;

class TemperatureConverter
{
public:
//	TemperatureConverter();

	double celsiusToKelvin(const double& celsius);
	double kelvinToCelsius(const double& celsius);
	double celsiusToFahrenheit(const double& celsius);
	double fahrenheitToCelsius(const double& celsius);
};
