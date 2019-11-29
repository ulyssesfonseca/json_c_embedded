
#include "../inc/JSON.h"



char* json_body=NULL;
char* json_variable=NULL;
char* json_value=NULL;

uint32_t _json_body_size = 0;
uint32_t _json_variable_size = 0;
uint32_t _json_value_size = 0;

char json_print_comma = 0;


void json_parse(char* pString){
	uint32_t i = 0;
	uint16_t j = 0;
	uint8_t start = 0;
	uint8_t value = 0;
	uint8_t wait = 0;
	uint8_t type = JSON_Invalid;
	uint8_t last_type = JSON_Invalid;
	uint8_t send = 0;

	json_value[0]='\0';
    json_variable[0]='\0';

    printf("%s\n", pString);

	for(i=0; i<strlen((char*)pString); i++){

		if      (pString[i]==':'){
            wait=1;
		    if      (pString[i+1]=='"'){type=JSON_String; wait=2;}
		    /*else if (pString[i+1]=='['){type=JSON_Array;  wait=3; send=1;}
            else if (pString[i+1]=='{'){type=JSON_Object; wait=3; send=1;}*/
		    else if (pString[i+1]=='t'){type=JSON_True;}
		    else if (pString[i+1]=='f'){type=JSON_False;}
		    else if (pString[i+1]=='n'){type=JSON_NULL;}
		    else if (pString[i+1]=='e'){type=JSON_Empty;}
		    else                       {type=JSON_Number;}
		    value = 1;
            start = 1;
            last_type=type;
        }
        else if (pString[i]=='"'){
            if  (type!=JSON_String){start = 1; value = 0;}
            else if(wait==0){start = !start; value = 0;}
            wait=1;
        }
        else if (pString[i]=='['){last_type=type=JSON_Array; send=1;}
        else if (pString[i]=='{'){last_type=type=JSON_Object; send=1;}
        else if (pString[i]==']' || pString[i]=='}' || pString[i]==',')  {
                start = 0; send = 1; last_type=type;
                type=JSON_Invalid;
                if      (pString[i]=='}'){type=JSON_Object_End;}
                else if (pString[i]==']'){type=JSON_Array_End;}
        }

		if(send == 1){
                json_callback(json_variable,json_value,last_type);
                json_value[0]='\0';
                json_variable[0]='\0';
                send = 0;
		}
		if(wait==0){
            if(start){
				if(value){ 	json_value[j] = pString[i]; json_value[j+1]='\0';}
				else{		json_variable[j] = pString[i]; json_variable[j+1]='\0';}
				j++;
				if      (value && j>=_json_value_size){j = _json_value_size-1;}
				else if (value && j>=_json_variable_size){j = _json_variable_size-1;}
			}
			else{ j=0;}
		}
		else{ j=0;}

		if(wait>0)wait--;
	}
	json_callback(json_variable,json_value,type);
}


void json_init(uint32_t pVariable, uint32_t pValue, uint32_t pBody){
    _json_variable_size = pVariable;
    _json_value_size = pValue;
    _json_body_size = pBody;

    json_variable = malloc(_json_variable_size);
    json_value = malloc(_json_value_size);
    json_body = malloc(_json_body_size);
}
void json_deinit(void){
    free(json_variable);
    free(json_value);
    free(json_body);
}

char * json_get_body(void){
    return json_body;
}


void json_clear(void){
	memset(json_body,0x00,sizeof(_json_body_size));
	json_print_comma = 0;
}

void _json_print_comma(void){
	char temp[3];
	if(json_print_comma){
		snprintf(temp,sizeof(temp),",");
		strncat(json_body,temp,_json_body_size);
	}
}

void json_insertStr(char* pVariable, char* pValue){
	char temp[100];
	snprintf(temp,sizeof(temp),"\"%s\"",pValue);
	json_insertValue(pVariable,temp);
}
void json_insertIntToStr(char* pVariable, int pValue){
	char temp[100];
	snprintf(temp,sizeof(temp),"\"%d\"",pValue);
	json_insertValue(pVariable,temp);
}
void json_insertInt(char* pVariable, int pValue){
	char temp[100];
	snprintf(temp,sizeof(temp),"%d",pValue);
	json_insertValue(pVariable,temp);
}
void json_insertValue(char* pVariable, char* pValue){
    char temp[100];

	_json_print_comma();
	snprintf(temp,sizeof(temp),"\"%s\":%s",pVariable,pValue);

	json_print_comma = 1;
	strncat(json_body,temp,_json_body_size);
}


void json_openObjectStr(char* pObjName){
	char temp[100];

	_json_print_comma();

	snprintf(temp,sizeof(temp),"\"%s\":{",pObjName);
	json_print_comma = 0;
	strncat(json_body,temp,_json_body_size);
}
void json_openObject(void){
	char temp[100];

	_json_print_comma();

	snprintf(temp,sizeof(temp),"{");
	json_print_comma = 0;
	strncat(json_body,temp,_json_body_size);
}
void json_closeObject(void){
	json_close();
}

void json_openArrayStr(char* pArray){
	char temp[100];

	_json_print_comma();

	snprintf(temp,sizeof(temp),"\"%s\":[",pArray);
	json_print_comma = 0;
	strncat(json_body,temp,_json_body_size);
}
void json_openArray(void){
	char temp[100];

	_json_print_comma();

	snprintf(temp,sizeof(temp),"[");
	json_print_comma = 0;
	strncat(json_body,temp,_json_body_size);
}
void json_closeArray(void){
	strncat(json_body,"]",_json_body_size);
	json_print_comma=1;
}

void json_open(void){
	strncat(json_body,"{",_json_body_size);
	json_print_comma=0;
}
void json_close(void){
	strncat(json_body,"}",_json_body_size);
	json_print_comma=1;
}



