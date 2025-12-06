# Project
Building Project using C
1. Introduction :
Street lighting consumes a significant portion of urban electrical energy, and traditional systems keep lights fully ON regardless of actual need.
A smart street light controller improves energy efficiency by turning lights ON only when required and by adjusting their intensity according to ambient light and motion.
This project simulates such a smart street light controller using C, with virtual sensors for ambient light and motion.

2. Problem Statement :
Conventional street lights typically operate at a fixed intensity during nighttime, wasting energy when there is sufficient ambient light or no traffic.
There is a need for an automatic system that can decide when to turn street lights ON or OFF and how bright they should be, based on environmental conditions.
The problem is to design and implement a C program that simulates this smart control behaviour for a set of street lights.

3. Objectives :
	To simulate an automatic street lighting system using C.
	To use ambient light level and motion detection as inputs for controlling each street light.
	To turn lights ON only when light is low or motion is detected.
	To dynamically adjust light intensity according to ambient light conditions.

4. Proposed System :
The proposed system considers each street light as an object with attributes such as ID, status (ON/OFF), intensity, motion detection flag, and ambient light level.
Random values are used to simulate ambient light (0–100) and occasional motion detection events.
Based on these simulated sensor readings, the system updates the state of each light and displays the overall system status in the console at fixed time intervals. This can be also improved by giving a database to the system of the any location to increase its effectiveness. This can be done using File management systems.

5. Methodology / Algorithm :
High-level algorithm :
	Initialize all street lights with default values (OFF, zero intensity, no motion, default ambient light).
	Repeat forever:
	Generate a random ambient light level.
	For each light, update its ambient light level and randomly decide if motion is detected.
	For each light, decide ON/OFF based on ambient light and motion.
	For each light that is ON, compute its intensity.
	Clear the screen and display the current status of all lights.
	Wait for a fixed delay before the next update.
Decision logic :
	If ambient light is below a threshold OR motion is detected → light status = ON.
	If ambient light is above or equal to the threshold AND no motion → light status = OFF.
	If ON and motion is detected → intensity = 100%.
	If ON and no motion → intensity = 100-"ambientLight" , clamped between 30% and 100%.
	If OFF → intensity = 0%.

6. Program Design (Flowchart, Pseudocode) :
Pseudocode :
Define enum LightStatus { OFF, ON }
Define struct StreetLight
    int id
    LightStatus status
    int intensity
    int motionDetected
    int ambientLightLevel
Define constants:
    NUM_LIGHTS = 5
    AMBIENT_LIGHT_THRESHOLD = 40
    SIMULATION_DELAY_S = 1
Function initializeLights(lights[], numLights):
    for i from 0 to numLights-1:
        lights[i].id = i + 1
        lights[i].status = OFF
        lights[i].intensity = 0
        lights[i].motionDetected = 0
        lights[i].ambientLightLevel = 70
Function simulateSensorInputs(lights[], numLights):
    currentAmbientLight = random integer from 0 to 100
    for i from 0 to numLights-1:
        lights[i].ambientLightLevel = currentAmbientLight
        lights[i].motionDetected = (random integer 0–4 == 0) ? 1 : 0
Function updateLightStatus(light):
    if light.ambientLightLevel < AMBIENT_LIGHT_THRESHOLD OR light.motionDetected == 1:
        light.status = ON
    else:
        light.status = OFF
Function adjustLightIntensity(light):
    if light.status == OFF:
        light.intensity = 0
    else:
        if light.motionDetected == 1:
            light.intensity = 100
        else:
            light.intensity = 100 - light.ambientLightLevel
            if light.intensity > 100: light.intensity = 100
            if light.intensity < 30:  light.intensity = 30
Function displaySystemStatus(lights[], numLights):
    clear screen
    print table header
    for each light:
        print id, status (ON/OFF), intensity, motion, ambientLightLevel
Main:
    seed random number generator
    declare array streetLights[NUM_LIGHTS]
    initializeLights(streetLights, NUM_LIGHTS)
    loop forever:
        simulateSensorInputs(streetLights, NUM_LIGHTS)
        for each light in streetLights:
            updateLightStatus(light)
            adjustLightIntensity(light)
        displaySystemStatus(streetLights, NUM_LIGHTS)
        sleep for SIMULATION_DELAY_S seconds

Flowchart Description :
	Start
	Initialize Lights
Initialize all street lights with default values (OFF, 0 intensity, no motion, ambient light = 70)
	Loop Start (Start of infinite loop)
	Simulate Sensor Inputs
Generate a random ambient light level (0-100)
For each light: update ambient light, randomly set motion detected (true/false)
	For Each Light:
	Update Light Status:
If ambient light < threshold OR motion detected → status = ON
Else → status = OFF
	Adjust Intensity:
If OFF → intensity = 0
Else if motion detected → intensity = 100
Else → intensity = 100 - ambient light (clamped between 30 and 100)
	Display System Status:
Show table of all lights with their status, intensity, motion, and ambient light
	Delay (Sleep 1 second) 
	Loop Back to "Simulate Sensor Inputs"
	(No end - continuous simulation)

7. Implementation (C Code) :
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#define sleep(seconds) Sleep(seconds * 1000)
#else
#include <unistd.h>
#endif
#define NUM_LIGHTS 5              
#define AMBIENT_LIGHT_THRESHOLD 40 
#define SIMULATION_DELAY_S 1     
typedef enum 
{
    OFF,
    ON
} LightStatus;
typedef struct 
{
    int id;                 
    LightStatus status;     
    int intensity;          
    int motionDetected;     
    int ambientLightLevel;  
} StreetLight;
void initializeLights(StreetLight lights[], int numLights);
void simulateSensorInputs(StreetLight lights[], int numLights);
void updateLightStatus(StreetLight *light);
void adjustLightIntensity(StreetLight *light);
void displaySystemStatus(const StreetLight lights[], int numLights);
int main() 
{
    srand(time(NULL));
    StreetLight streetLights[NUM_LIGHTS];
    initializeLights(streetLights, NUM_LIGHTS);
    while (1) 
    {
        simulateSensorInputs(streetLights, NUM_LIGHTS);
        for (int i = 0; i < NUM_LIGHTS; i++) 
        {
            updateLightStatus(&streetLights[i]);
            adjustLightIntensity(&streetLights[i]);
        }
        displaySystemStatus(streetLights, NUM_LIGHTS);
        sleep(SIMULATION_DELAY_S);
    }
    return 0;
}
void initializeLights(StreetLight lights[], int numLights) 
{
    for (int i = 0; i < numLights; i++) 
    {
        lights[i].id = i + 1;
        lights[i].status = OFF;
        lights[i].intensity = 0;
        lights[i].motionDetected = 0;
        lights[i].ambientLightLevel = 70;
    }
}
void simulateSensorInputs(StreetLight lights[], int numLights) 
{
    int currentAmbientLight = rand() % 101;

    for (int i = 0; i < numLights; i++) 
    {
        lights[i].ambientLightLevel = currentAmbientLight;
        lights[i].motionDetected = (rand() % 5 == 0) ? 1 : 0;
    }
}
void updateLightStatus(StreetLight *light) 
{
    if (light->ambientLightLevel < AMBIENT_LIGHT_THRESHOLD || light->motionDetected) 
    {
        light->status = ON;
    } 
    else 
    {
        light->status = OFF;
    }
}
void adjustLightIntensity(StreetLight *light) 
{
    if (light->status == OFF) 
    {
        light->intensity = 0;
    } 
    else 
    {
        if (light->motionDetected) 
        {
            light->intensity = 100;
        } 
        else 
        {
            light->intensity = 100 - light->ambientLightLevel;
            if (light->intensity > 100) light->intensity = 100;
            if (light->intensity < 30) light->intensity = 30;
        }
    }
}
void displaySystemStatus(const StreetLight lights[], int numLights) 
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("===== Smart Street Light Controller Simulation =====\n");
    printf("Threshold for Darkness: <%d\n", AMBIENT_LIGHT_THRESHOLD);
    printf("------------------------------------------------------\n");
    printf(" ID | Status | Intensity | Motion | Ambient Light\n");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < numLights; i++) 
    {
        printf(" %-3d| %-7s| %6d%%   | %-7d| %-d\n",
               lights[i].id,
               (lights[i].status == ON ? "ON" : "OFF"),
               lights[i].intensity,
               lights[i].motionDetected,
               lights[i].ambientLightLevel);
    }
    printf("------------------------------------------------------\n");
    printf("...Updating in %d second(s)...\n", SIMULATION_DELAY_S);
}
*/
8. Output :
The program clears the screen at each step and prints a table showing:
	Light ID.
	Status (ON/OFF).
	Intensity in percentage.
	Motion detected (0/1).
	Current ambient light level.
As the program runs, the user can observe how lights turn ON/OFF and how intensity changes according to ambient light and motion. 

9. Conclusion : 
The smart street light controller simulation successfully demonstrates automatic control of street lights based on ambient light and motion detection.
The system turns lights ON only when necessary and adjusts intensity dynamically, showing the potential for significant energy savings in real-world deployments.
This console-based model provides a simple yet effective way to study and test control logic before moving to actual hardware.

10. Future Scope :
	Interfacing with real sensors (LDR, PIR) and microcontrollers for hardware implementation.
	Adding communication between lights to create coordinated behaviour along a road.
	Implementing advanced control strategies, such as time-based profiles or machine learning based on traffic patterns.
	Providing a graphical user interface (GUI) or web dashboard for monitoring and configuration.
