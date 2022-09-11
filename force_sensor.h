#ifndef INC_FORCE_SENSOR_H_
#define INC_FORCE_SENSOR_H_

typedef struct {
	ADC_HandleTypeDef *adc;
} ForceSensor;

/** PUBLIC FUNCTIONS **/

// REQUIRES: hadc is the adc channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created ForceSensor object
ForceSensor *new_force_sensor(ADC_HandleTypeDef *hadc);

// REQUIRES: ForceSensor is an object
// MODIFIES: nothing
// EFFECTS: Returns a force detected in Newtons
double get_force_sensor_data(ForceSensor *force_sensor);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/

#endif /* INC_PRESSURE_SENSOR_H_ */