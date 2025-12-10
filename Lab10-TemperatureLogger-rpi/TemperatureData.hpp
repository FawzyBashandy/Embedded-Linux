#pragma once
#include <ctime>
class TemperatureData{
    private:
    float temperature_;
    std::time_t timestamp_;
    public:
    TemperatureData()=delete;
    explicit TemperatureData(float Temperature); // SO that the compiler don't do implicit casting
    TemperatureData(const TemperatureData&)=default;
    TemperatureData(TemperatureData&&) = default;

    TemperatureData& operator=(const TemperatureData&)=default;
    TemperatureData& operator=(TemperatureData&&)=default;

    void ChangeTemperature(float temperature);
    float getTemperature() const;
    std::time_t getTimeStamp()const;
    
};