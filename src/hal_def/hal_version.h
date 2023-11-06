#ifndef HAL_VERSION_H_
#define HAL_VERSION_H_

#define HAL_VERSION_MAJOR       1                       
#define HAL_VERSION_MINOR       4                       
#define HAL_VERSION_REVISION    0                       

#define HAL_VERSION_NAME        BUILD_VERSION_STRING(HAL_VERSION_MAJOR,HAL_VERSION_MINOR,HAL_VERSION_REVISION) 

#define QUOTE(x) #x  
#define     BUILD_VERSION_STRING(x,y,z) QUOTE(x) "." QUOTE(y) "." QUOTE(z)   
#endif

