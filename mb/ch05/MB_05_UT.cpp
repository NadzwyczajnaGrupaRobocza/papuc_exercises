#include "gtest/gtest.h"

#include "../common/MB_Common.hpp"
#include "MB_05_02.hpp"

// Excercise 02
//==============
TEST(MBB_05_02, toLowCelsiusTemperatureWhileConvertingToKelvin)
{
	TemperatureConverter converter = TemperatureConverter();
	const double celsius = CESIUS_MIN - 0.01;
    EXPECT_THROW(converter.celsiusToKelvin(celsius), std::out_of_range);
}

TEST(MBB_05_02, convertingFromCelsiusToKelvin)
{
	TemperatureConverter converter = TemperatureConverter();
	const double celsius = 100.70;
    EXPECT_TRUE(mbcommon::doublesAreEqual(373.85, 
										  converter.celsiusToKelvin(celsius)));
}

TEST(MBB_05_02, toLowKelvinTemperature)
{
	TemperatureConverter converter = TemperatureConverter();
	const double kelvin = KELVIN_MIN -10.0;
    EXPECT_THROW(converter.kelvinToCelsius(kelvin), std::out_of_range);
}

TEST(MBB_05_02, convertKelvinToCelsius)
{
	TemperatureConverter converter = TemperatureConverter();
	const double kelvin = 100.0;
    EXPECT_TRUE(mbcommon::doublesAreEqual(-173.15, 
										  converter.kelvinToCelsius(kelvin)));
}

TEST(MBB_05_02, toLowCelsiusTemperatureWhileConvertingToFahrenheit)
{
	TemperatureConverter converter = TemperatureConverter();
	const double celsius = CESIUS_MIN - 0.01;
    EXPECT_THROW(converter.celsiusToFahrenheit(celsius), std::out_of_range);
}

TEST(MBB_05_02, convertingFromCelsiusToFahrenheit)
{
	TemperatureConverter converter = TemperatureConverter();
	const double celsius = 50.0;
    EXPECT_TRUE(mbcommon::doublesAreEqual(122.0, 
										  converter.celsiusToFahrenheit(celsius)));
}

TEST(MBB_05_02, toLowFahrenheitTemperature)
{
	TemperatureConverter converter = TemperatureConverter();
	const double fahrenheit = FAHRENHEIT_MIN - 0.05;
    EXPECT_THROW(converter.fahrenheitToCelsius(fahrenheit), std::out_of_range);
}

TEST(MBB_05_02, convertFahrenheitToCelsius)
{
	TemperatureConverter converter = TemperatureConverter();
	const double fahrenheit = 69.8;
    EXPECT_TRUE(mbcommon::doublesAreEqual(21.0, 
										  converter.fahrenheitToCelsius(fahrenheit)));
}
