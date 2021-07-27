#include <ros.h>
#include <std_msgs/Float32.h>
#include <Dps310.h>

// Dps310 Opject
Dps310 Dps310PressureSensor = Dps310();
ros::NodeHandle  nh;
std_msgs::Float32 flt_msg;
ros::Publisher pressure_pub("pressure", &flt_msg);

void setup() {
  
//    Serial.begin(9600);
//    while (!Serial);

    //Call begin to initialize Dps310PressureSensor
    //The parameter 0x76 is the bus address. The default address is 0x77 and does not need to be given.
    //Dps310PressureSensor.begin(Wire, 0x76);
    //Use the commented line below instead of the one above to use the default I2C address.
    //if you are using the Pressure 3 click Board, you need 0x76
    Dps310PressureSensor.begin(Wire);

//    Serial.println("Init complete!");

    nh.initNode();
    nh.advertise(pressure_pub);
//    Serial.println("ros init complte!");

}

void loop() {
//    float temperature;
    float pressure;
    uint8_t oversampling = 7;
    int16_t ret;
//    Serial.println();

    //lets the Dps310 perform a Single temperature measurement with the last (or standard) configuration
    //The result will be written to the paramerter
    //oversampling can be a value from 0 to 7
    //the Dps 310 will perform 2^oversampling internal pressure measurements and combine them to one result with higher precision
    //measurements with higher precision take more time, consult datasheet for more information

    //ret = Dps310PressureSensor.measurePressureOnce(pressure);
    ret = Dps310PressureSensor.measurePressureOnce(pressure, oversampling);
//    if (ret != 0) {
//        //Something went wrong.
//        //Look at the library code for more information about return codes
//        Serial.print("FAIL! ret = ");
//        Serial.println(ret);
//    } else {
//        Serial.print("Pressure: ");
//        Serial.print(pressure);
//        Serial.println(" Pascal");
//    }
    
    flt_msg.data = pressure;
    pressure_pub.publish(&flt_msg);
    nh.spinOnce();

    //Wait some time
    delay(1000);
}
