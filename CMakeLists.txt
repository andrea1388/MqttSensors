idf_component_register(SRCS     
Base.cpp BinarySensor.cpp Sensor.cpp Switch.cpp                   
INCLUDE_DIRS .
REQUIRES mqtt esp_timer driver Esp32MqttComponent)
target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLOG_LOCAL_LEVEL=ESP_LOG_DEBUG")
