#include <iostream>
#include <fstream>
#include <chrono>
#include "NIDAQmx.h"




int main()
{
    // Task handle
    TaskHandle taskHandle = 0;

    // Buffer size and data array
    const int bufferSize = 10;
    float64 data[bufferSize * 6];  // Increased buffer size to accommodate 6 channels
   

    // Error handling
    char errorBuffer[2048] = { 0 };

    // Create a task
    DAQmxCreateTask("", &taskHandle);

    // Configure the task for voltage measurement on 6 channels (ai0 to ai5)
    for (int channel = 0; channel < 6; ++channel)
    {
        char channelName[32];
        sprintf_s(channelName, sizeof(channelName), "Dev1/ai%d", channel);
        DAQmxCreateAIVoltageChan(taskHandle, channelName, "", DAQmx_Val_RSE, -10.0, 10.0, DAQmx_Val_Volts, NULL);
    }

    // Start the task
    DAQmxStartTask(taskHandle);

    // Set the desired duration (in seconds)
    const double duration = 10.0;

    // Record the start time
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

    // Read and save data until the desired duration is reached
    std::ofstream outputFile("data.txt");
     std::cout << "Starting collection" << std::endl;

    while (true)
    {   

       // std::cout << i << std::endl;
        int32 read = 0;
        DAQmxReadAnalogF64(taskHandle, bufferSize, 10.0, DAQmx_Val_GroupByScanNumber, data, bufferSize * 6, &read, NULL);

        // Save the acquired data to the file
        if (outputFile.is_open())
        {
            for (int i = 0; i < read * 6; ++i)
            {
                outputFile << data[i] << std::endl;
            }
        }
        else
        {
            std::cerr << "Error opening the file." << std::endl;
            break;
        }

        // Check if the desired duration is reached
        std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedDuration = currentTime - startTime;
        if (elapsedDuration.count() >= duration)
        {
            break;
        }
    }

    // Close the file
    outputFile.close();
    std::cout << "Data saved to data.txt" << std::endl;

    // Stop and clear the task
    DAQmxStopTask(taskHandle);
    DAQmxClearTask(taskHandle);

    return 0;
}
