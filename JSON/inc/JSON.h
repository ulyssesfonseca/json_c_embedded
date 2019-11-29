/*
 *	Biblioteca criada para criar e fazer parse de JSON em c.
 *
 *	author: Ulysses Fonseca
 * 	date: September 2019
 * 	version: 1.0.0
 */
#ifndef __JSON__
#define __JSON__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


#define JSON_VERSION 1.0.1

enum{
	OPEN_CONTAINER,
	CLOSE_CONTAINER,
	OPEN_MATRIX,
	CLOSE_MATRIX
};

enum{
    JSON_Invalid,
    JSON_False,
    JSON_True,
    JSON_Empty,
    JSON_NULL,
    JSON_Number,
    JSON_String,
    JSON_Array,
    JSON_Object,
    JSON_Array_End,
    JSON_Object_End,
    JSON_Raw
} eJSON_types;

/*
 * Esta funcao deve ser criada na aplicacao para sempre ser chamada quando uma nova variavel for identificada na string json.
 *
 * param:
 * char* pVar 	- variavel json
 * char* pValue - valor da variavel json
 * char pType	- retorna o tipo retornado definido em eJSON_types
 */
extern void json_callback(char* pVar, char* pValue, char pType);


/*
 * Funcao realiza o parse da string json.
 *
 * param:
 * char* pString 	- payload a ser analizado
 */
void json_parse(char* pString);



/*
 * Esta funcao deve ser chamada para inicializar os buffers de tratamento para json.
 *
 * param:
 * uint32_t pVariable - tamanho do buffer para salvar a variavel
 * uint32_t pValue - tamanho do buffer para salvar valor da variavel
 * uint32_t pBody - tamanho do buffer para alocar o objeto json
 */
void json_init(uint32_t pVariable, uint32_t pValue, uint32_t pBody);


/*
 * Desaloca os buffers da memoria RAM.
 */
void json_deinit(void);


/*
 * Retorna o conteudo do objeto json no formato de uma string.
 */
char * json_get_body(void);



/*
 * Limpa o buffer do body do json.
*/
void json_clear(void);
/*
 * Insere uma nova variavel com valor do tipo string.
 *
 * param:
 * char* pVariable	- nome da variavel
 * char* pValue	- valor da variavel
 */
void json_insertStr(char* pVariable, char* pValue);
/*
 * Insere uma nova variavel com valor do tipo inteiro convertendo para string.
 *
 * param:
 * char* pVariable	- nome da variavel
 * int pValue	- valor da variavel
 */
void json_insertIntToStr(char* pVariable, int pValue);
/*
 * Insere uma nova variavel com valor do tipo inteiro.
 *
 * param:
 * char* pVariable	- nome da variavel
 * int pValue	- valor da variavel
 */
void json_insertInt(char* pVariable, int pValue);
/*
 * Insere uma nova variavel com valor do tipo true,false,empty,null devendo ser passado como uma string.
 *
 * param:
 * char* pVariable	- nome da variavel
 * char* pValue	- valor da variavel em formato de string (utilizado para true, false, empty, null)
 */
void json_insertValue(char* pVariable, char* pValue);


/*
 * Abre uma variavel do tipo container para insercao.
 *
 * param:
 * char* pVariable	- nome da variavel
 */
void json_openObjectStr(char* pContainer);
/*
 * Abre uma variavel do tipo container para insercao.
 *
 */
void json_openObject(void);
/*
 * Fecha o container corrente.
 */
void json_closeObject(void);




/*
 * Abre uma variavel do tipo matriz para insercao.
 *
 * param:
 * char* pVariable	- nome da variavel
 */
void json_openArrayStr(char* pMatrix);
/*
 * Abre uma variavel do tipo container para insercao.
 *
 */
void json_openArray(void);
/*
 * Fecha o container corrente.
 */
void json_closeArray(void);



/*
 * Abre o objeto json.
 */
void json_open(void);
/*
 * Fecha o objeto json.
 */
void json_close(void);

#endif

