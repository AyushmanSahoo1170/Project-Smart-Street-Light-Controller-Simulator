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