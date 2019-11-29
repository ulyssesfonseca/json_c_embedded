#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "JSON/inc/JSON.h"



/*char json[] = "{\"pincd\":\"8U4L\",\"dvctk\":\"KE3LPBI3-W3G1-M1VV-LI6S-YEFT4W64J7SX\",\"retorno\":\"OK\"}";
//char json[] = "{\"version\":\"0\",\"dados_dwn\":\"false\",\"return\":\"OK\"}";
//char json[] = "{\"return\":\"true\",\"communication\":{\"qtdgr\":\"5\",\"qtdrc\":\"6\"}}";
//char json[] = "{\"return\":true,\"qtdgr\":5,\"status\":\"OK\"}";
*/
char json[] = "[{\"variable\":\"cam\",\"value\":\"10\"},{\"variable\":\"ir\",\"value\":\"10\"},{\"variable\":\"board\",\"value\":\"10\"}]";

void json_callback(char* pVar, char* pValue, char pType){

    switch(pType){
        case JSON_Invalid:  printf("JSON_Invalid");break;
        case JSON_False:    printf("JSON_False");break;
        case JSON_True:     printf("JSON_True");break;
        case JSON_Empty:    printf("JSON_Empty");break;
        case JSON_NULL:     printf("JSON_NULL");break;
        case JSON_Number:   printf("JSON_Number");break;
        case JSON_String:   printf("JSON_String");break;
        case JSON_Array:    printf("JSON_Array");break;
        case JSON_Object:   printf("JSON_Object");break;
        case JSON_Array_End: printf("JSON_Array_End");break;
        case JSON_Object_End: printf("JSON_Object_End");break;
    }
    if(pType!=JSON_Invalid || pType!=JSON_Array_End || pType!=JSON_Object_End)
    printf(" '%s' - '%s' ", pVar, pValue);
    printf("\n");
}


int main()
{
    json_init(40,20,4*1024);

    json_parse(json);

    json_clear();
    json_open();
    json_insertInt("numero", 2);
    json_insertIntToStr("number", 2);
    json_insertStr("nome", "Albert");
    json_insertValue("retorno", "true");
    json_insertValue("status", "false");
    json_insertValue("endereco", "null");
    json_close();

    printf("\n\n%s\n\n",json_get_body());

    json_parse(json_get_body());

    json_deinit();
    printf("\nMemoria liberada");

    return 0;
}
