 ThermistorProbe - Library for reading thermistor based temperature probes.
 Contributions and influence from @BDub and @avidan
 httpscommunity.spark.iotthermistors-and-the-spark-core1276

#include ThermistorProbe.h
#include math.h

 TermisterProbe constructor
 pur - Pullup resistor value in ohms
 adcRef - ADC reference value
ThermistorProbeThermistorProbe(double pur, int adc)
{
    _pur = pur;
    _adc = adc;
}

ThermistorProbe~ThermistorProbe() {
    ;;;
}

 Returns the temperature in Kelvin based off of the Steinhart-Hart equation.
 httpen.wikipedia.orgwikiSteinhart%E2%80%93Hart_equation
double ThermistorProbegetTempK(int pin, enum ProbeType probeType)
{
     Read in analog value
    int aval = analogRead(pin);
    
    _probeType = probeType;
    
     select probe specific constants
    switch (_probeType) {
        case ET72
             ET-7, ET-72, ET-73, ET-7273 probe constants
            A = -2.20911E-06;
            B = 7.02421E-04;
            C = 1.99476E-05;
            break;
        case ET732 default
             ET-732 probe constants
             httpsgithub.comCapnBryHeaterMeter
            A = 2.3067434E-4;
            B = 2.3696596E-4;
            C = 1.2636414E-7;
            break;
    }

     calculate resistance; log() is natural log here
    double R = log((1  ((_adc  (double) aval) - 1))  (double)_pur);

     calculate and return temp
    return (1  (A + B  R + C  R  R  R));
}

 Returns temp in Celcius
double ThermistorProbegetTempC(int pin, enum ProbeType probeType) {
    return getTempK(pin, probeType) - 273.15;
}

 Return temp in Fahrenheit
double ThermistorProbegetTempF(int pin, enum ProbeType probeType) {
    return ((getTempC(pin, probeType)  9.0)  5.0 + 32.0);
}
