#pragma once
/**
* CSC369 Assignment 2
*
* This is the header file for your safe traffic light submission code.
*/
#include "car.h"
#include "trafficLight.h"

/**
* @brief Structure that you can modify as part of your solution to implement
* proper synchronization for the traffic light intersection.
*
* This is basically a wrapper around TrafficLight, since you are not allowed to 
* modify or directly access members of TrafficLight.
*/
typedef struct _SafeTrafficLight {

	/**
	* @brief The underlying light.
	*
	* You are not allowed to modify the underlying traffic light or directly
	* access its members. All interactions must be done through the functions
	* you have been provided.
	*/
	TrafficLight base;

	// TODO: Add any members you need for synchronization here.
	//Mutexes used to synchronize the cars enter the lanes
	pthread_mutex_t lane_lock[TRAFFIC_LIGHT_LANE_COUNT];
	//Mutexes used to enter the traffic from different lanes
	pthread_mutex_t enter_lock[TRAFFIC_LIGHT_LANE_COUNT];
	// First should be used for left turn from N or E
	pthread_cond_t left_cond1;
	// Second should be used for left turn from S or W
	pthread_cond_t left_cond2;

	int enter_cound[TRAFFIC_LIGHT_LANE_COUNT];
	int exit_coune[TRAFFIC_LIGHT_LANE_COUNT];
	//Conditional variable for cars to exit the traffic light in order
	pthread_cond_t exit_cond[TRAFFIC_LIGHT_LANE_COUNT];

} SafeTrafficLight;

/**
* @brief Initializes the safe traffic light.
*
* @param light pointer to the instance of SafeTrafficLight to be initialized.
* @param eastWest total number of cars moving east-west.
* @param northSouth total number of cars moving north-south.
*/
void initSafeTrafficLight(SafeTrafficLight* light, int eastWest, int northSouth);

/**
* @brief Destroys the safe traffic light.
*
* @param light pointer to the instance of SafeTrafficLight to be destroyed.
*/
void destroySafeTrafficLight(SafeTrafficLight* light);

/**
* @brief Runs a car-thread in a traffic light scenario.
*
* @param car pointer to the car.
* @param light pointer to the traffic light intersection.
*/
void runTrafficLightCar(Car* car, SafeTrafficLight* light);
