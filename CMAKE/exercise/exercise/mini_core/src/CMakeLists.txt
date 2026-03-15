add_library(core_library SHARED
  utils/blob.cpp 

  # TODO add other .cpp files
  utils/identifiable.cpp    
  utils/property_container.cpp	      
  utils/property_eigen.cpp	 
  utils/serialization_context.cpp
  utils/deserializer.cpp  
  utils/id_placeholder.cpp  
  utils/property_container_manager.cpp  
  utils/property_identifiable.cpp  
  utils/serializer.cpp
  utils/id_context.cpp	  
  utils/object_data.cpp     
  utils/property.cpp		      
  utils/serializable.cpp

  messages/base_sensor_message.cpp  
  messages/odometry_message.cpp
  messages/pose_message.cpp

)
