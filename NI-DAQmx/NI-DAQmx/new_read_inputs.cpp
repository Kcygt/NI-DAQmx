#include <iostream>
#include "NIDAQmx.h"

#define MAX_NAME_LENGTH 100
#define MAX_SAMPLES 1000

int main()
{
    // Variables for DAQmx
    int32 error = 0;
    TaskHandle taskHandle = 0;
    int32 numRead = 0;
    float64 data[MAX_SAMPLES];

    // Create a task
    DAQmxCreateTask("", &taskHandle);

    // Configure the task to read analog input
    DAQmxCreateAIVoltageChan(taskHandle, "Dev1/ai0:5", "", DAQmx_Val_RSE, -10.0, 10.0, DAQmx_Val_Volts, NULL);
    DAQmxCfgSampClkTiming(taskHandle, "", 1000.0, DAQmx_Val_Rising, DAQmx_Val_ContSamps, MAX_SAMPLES);

    // Start the task
    DAQmxStartTask(taskHandle);

    // Read analog input data
    while (true)
    {
        DAQmxReadAnalogF64(taskHandle, MAX_SAMPLES, 10.0, DAQmx_Val_GroupByChannel, data, MAX_SAMPLES, &numRead, NULL);

        // Process the acquired data
        if (numRead > 0)
        {
            for (int i = 0; i < numRead; i++)
            {
                std::cout << "Channel " << i << ": " << data[i] << " Volts" << std::endl;
            }
        }
    }

    // Stop and clear the task
    DAQmxStopTask(taskHandle);
    DAQmxClearTask(taskHandle);

    return 0;
}
