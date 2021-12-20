/*
 *   Copyright 2009 Francisco Javier Lopez
 *   e-mail: lane.mastodon@gmail.com
 *
 *   This file is part of InPAWS.
 *
 *   InPAWS is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   InPAWS is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with InPAWS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

//-----------------------------------------------------------------
// Códigos para las letras acentuadas y la eñe:
// ñ -> \244
// Ñ -> \245
// á -> \240
// é -> \202
// í -> \241
// ó -> \242
// ú -> \243
//------------------------------------------------------------------

#ifndef MSGAPLICACION_H_
#define MSGAPLICACION_H_

#ifdef MSG_ESPANOL
// Errores de ejecucion
#define MSG_FALTAN_PARAMETROS "Faltan par\240metros"
#define MSG_ARCHIVO_NO_EXISTE "El archivo especificado no existe o est\240 corrupto"
#define MSG_ARCHIVO_NO_64K "El archivo especificado no es un volcado de memoria de 64K"
#define MSG_TIPONOREC "Tipo de archivo no reconocido"
#define MSG_ARCHIVO_NO_SNA "El archivo no es un volcado .SNA de 48k"
#define MSG_ARCHIVO_NO_Z80_48k "El archivo no es un volcado .Z80 de 48k"
#define MSG_NOBDPAW "No se encontr\242 la firma de una base de datos PAW en el fichero"

// Tipos de vocabulario
#define MSG_VERB "VERB"
#define MSG_ADVERB "ADVERB"
#define MSG_NOUN "NOUN"
#define MSG_ADJECTIVE "ADJECTIVE"
#define MSG_PREPOSITION "PREPOSITION"
#define MSG_CONJUNCTION "CONJUNCTION"
#define MSG_PRONOUN "PRONOUN"
#define MSG_RESERVED "RESERVED"

// Palabras reservadas
#define RSV_VOCABULARY "VOCABULARY"
#define RSV_LOCATIONS "LOCATIONS"
#define RSV_MESSAGES "MESSAGES"
#define RSV_SYSMESSAGES "SYSMESSAGES"
#define RSV_OBJECTS "OBJECTS"
#define RSV_CONNECTIONS "CONNECTIONS"
#define RSV_OBJWORDS "OBJWORDS"
#define RSV_INITIALLYAT "INITIALLYAT"
#define RSV_OBJWEIGHT "OBJWEIGHT"
#define RSV_PROCESS_TABLE "PROCESS_TABLE"
#define RSV_PROCESS "PROCESS"
#define RSV_RESPONSE "RESPONSE"
#define RSV_ABBREVIATIONS "ABBREVIATIONS"
#define RSV_CHARACTERS "CHARACTERS"
#define RSV_GRAPHICS "GRAPHICS"
#define RSV_DEFAULTS "DEFAULTS"
#define RSV_CHARSET "CHARSET"
#define RSV_INK "INK"
#define RSV_PAPER "PAPER"
#define RSV_FLASH "FLASH"
#define RSV_BRIGHT "BRIGHT"
#define RSV_INVERSE "INVERSE"
#define RSV_OVER "OVER"
#define RSV_BORDER "BORDER"
// Palabras reservadas del preprocesador
#define RSV_LOCATION "LOCATION"
#define RSV_OBJECT "OBJECT"
#define RSV_NOTCREATED "NOTCREATED"
#define RSV_WORN "WORN"
#define RSV_CARRIED "CARRIED"
#define RSV_WORDS "WORDS"
#define RSV_WEIGHT "WEIGHT"
#define RSV_PROPERTY "PROPERTY"
#define RSV_CONTAINER "CONTAINER"
#define RSV_CLOTHING "CLOTHING"
#define RSV_FLAG "FLAG"
#define RSV_SUBCHAR "SUBCHAR"
#define RSV_CONSTANT "CONSTANT"
#define RSV_INCLUDE "INCLUDE"
#define RSV_IFDEF "IFDEF"
#define RSV_IFNDEF "IFNDEF"
#define RSV_ENDIF "ENDIF"
#define RSV_DEFINE "DEFINE"

// Errores de sintaxis
#define MSG_PALAB_RESERV_NO_ENCONTRADA "esperado, pero encontrado "
#define MSG_FIN_DE_ARCHIVO "fin de archivo"
#define MSG_CODIGO_DE_PALABRA "c\242digo de palabra de diccionario"
#define MSG_LITERAL_DE_TIPO_DE_PALABRA "literal de tipo de palabra"
#define MSG_LITERAL_ENTRECOMILLADO "literal entrecomillado"
#define MSG_NUMERO_TEXTO_ESPERADO "n\243mero de mensaje de texto"
#define MSG_NUMERO_LOCALIDAD "n\243mero de localidad"
#define MSG_NUMERO_OBJETO "n\243mero de objeto"
#define MSG_DATO_ATRIBUTO_OBJETO "dato de atributo de objeto"
#define MSG_NOMBRE_CONDACTO "nombre de condacto"
#define MSG_PARAMETRO_CONDACTO "par\240metro de condacto"
#define MSG_CODIGO_ABREVIATURA "c\242digo de abreviatura (164-254)"
#define MSG_NOMBRE_ENTRADA_PROCESO "c\242digo de nombre en la entrada de procesos"
#define MSG_CODIGO_DECIMAL "c\242digo decimal"
#define MSG_ATRIBUTO_CHARSET "literal de atributo o juego de caracteres"
#define MSG_NOMBRE_MODULO_PAW "literal de modulo de PAW"

// Otros errores
#define MSG_FUERA_DE_LIMITE "Acceso a estructura de datos fuera de l\241mite"
#define MSG_CODIGO_NO_NUMERICO "C\242digo de control no num\202rico"
#define MSG_ATRIBUTOS_OBJ_INSUFICIENTES "Faltan objetos por asignar atributo"
#define MSG_COD_CONDACTO_MUY_GRANDE "C\242digo de condacto fuera de l\241mite (0-107)"
#define MSG_ARG_CONDACTO_MUY_GRANDE "Argumento de Condacto demasiado grande"
#define MSG_CONDACTO_INEXISTENTE "No existe un condacto con ese nombre"
#define MSG_NO_VERBO_UNO "Los verbos con c\242odigo 1 generan inconsistencias en las tablas de procesos y respuestas de PAW"
#define MSG_MAINTOP_NO_DEF "Maintop no definido, fija su valor con la funcion setMaintop()"
#define MSG_ATRIBUTO_MUY_GRANDE "c\242digo de atributo demasiado grande"
#define MSG_NUMLOCS_NO_DEF "debes definir el n\243mero de localidades con la funcion setNumLocs antes de volcar"
#define MSG_CADENA_MAL_FORMADA "cadena de caracteres mal formada"
#define MSG_SINTAXIS "Sintaxis: inpaws128 <comando> <fichero de entrada> [opciones]\n\n\
  Comandos:\n\
    (Generaci\242n para ZX Spectrum 48k):\n\
      c:  Compilar a fichero .tap\n\n\
    (Generaci\242n para PAW CP/M y PC):\n\
      cd: Compilar a fichero fuente .SCE de PAW-PC\n\
      cf: Compilar a fichero fuente .DSF de PAW-PC\n\
      cm: Compilar a fichero fuente .SCE de PAW-CPM (Amstrad CPC)\n\n\
    (Generaci\242n para Superglus[Glulx]):\n\
      cs: Compilar a fichero fuente .SCE de Superglus sin s\241mbolos\n\
      ct: Compilar a fichero fuente .TXP de Superglus/txtPaws con s\241mbolos\n\n\
    (Otros comandos):\n\
      e:  Extraer fuente de .SNA o .Z80 con una aventura de PAW 48k\n\
      cp: S\242lo generar fichero preprocesado, sin compilar (DEPURACION)\n\
      eg: Extraer graficos de .SNA o .Z80 con una aventura de PAW 48k\n\
      ec: Extraer juegos de caracteres de .SNA o .Z80\n\n\
  Opciones:\n\
      -o <fichero de salida>: Nombre dado al fichero generado por inpaws\n\
      -s : Listado detallado de s\241mbolos tras la compilaci\242n\n
      -z <0 - 100>: Mover <0 - 100> por ciento de los mensajes a la página 1 de ram"
#define MSG_SINTAXISINC "Sintaxis incorrecta"
#define MSG_ERRORFICHERO "Error al abrir el fichero"
#define MSG_MEMLIBRE "Memoria libre tras compilaci\242n: "
#define MSG_SINMEMORIA "Compilaci\242n fallida: l\241mite de memoria de PAW superado"

// Resumen de una compilacion
#define MSG_RESUMEN_LOCALIDADES "localidades"
#define MSG_RESUMEN_OBJETOS "objetos"
#define MSG_RESUMEN_MENSAJES "mensajes"
#define MSG_RESUMEN_SISMENSAJES "mensajes del sistema"
#define MSG_RESUMEN_PROCESOS "procesos"
#define MSG_RESUMEN_CARACTERES "juegos de caracteres"
#define MSG_RESUMEN_VERSION "Versi\242n de la base de datos:"
#define MSG_RESUMEN_ABREVIATURAS "Ahorro por compresi\242n:"
#define MSG_RESUMEN_COMPILOK "Proceso de compilaci\242n finalizado correctamente\nArchivo generado: "
#define MSG_RESUMEN_EXTRAEOK "Base de datos PAW correctamente extraida al archivo: "
#define MSG_SIMBOLOSUSADOS "S\241mbolos usados en la compilaci\242n:"
#define MSG_SCEPORINPAWS "Archivo generado automáticamente por Inpaws, a partir de una sintaxis Inpaws"

#else
// MENSAJES EN INGLES

// Errores de ejecucion
#define MSG_FALTAN_PARAMETROS "Too few parameters"
#define MSG_ARCHIVO_NO_EXISTE "The specified file doesn't exists, or is corrupt"
#define MSG_ARCHIVO_NO_64K "The specified file is not a 64K memory dump"
#define MSG_ARCHIVO_NO_SNA "The specified file is not a .SNA snapshot"
#define MSG_ARCHIVO_NO_Z80_48k "The specified file is not a 48k .Z80 snapshot"
#define MSG_TIPONOREC "Unrecognized file type"
#define MSG_NOBDPAW "PAW DataBase signature not found in file"

// Tipos de vocabulario
#define MSG_VERB "VERB"
#define MSG_ADVERB "ADVERB"
#define MSG_NOUN "NOUN"
#define MSG_ADJECTIVE "ADJECTIVE"
#define MSG_PREPOSITION "PREPOSITION"
#define MSG_CONJUNCTION "CONJUNCTION"
#define MSG_PRONOUN "PRONOUN"
#define MSG_RESERVED "RESERVED"

// Palabras reservadas
#define RSV_VOCABULARY "VOCABULARY"
#define RSV_LOCATIONS "LOCATIONS"
#define RSV_MESSAGES "MESSAGES"
#define RSV_SYSMESSAGES "SYSMESSAGES"
#define RSV_OBJECTS "OBJECTS"
#define RSV_CONNECTIONS "CONNECTIONS"
#define RSV_OBJWORDS "OBJWORDS"
#define RSV_INITIALLYAT "INITIALLYAT"
#define RSV_OBJWEIGHT "OBJWEIGHT"
#define RSV_PROCESS_TABLE "PROCESS_TABLE"
#define RSV_PROCESS "PROCESS"
#define RSV_RESPONSE "RESPONSE"
#define RSV_ABBREVIATIONS "ABBREVIATIONS"
#define RSV_CHARACTERS "CHARACTERS"
#define RSV_GRAPHICS "GRAPHICS"
#define RSV_DEFAULTS "DEFAULTS"
#define RSV_CHARSET "CHARSET"
#define RSV_INK "INK"
#define RSV_PAPER "PAPER"
#define RSV_FLASH "FLASH"
#define RSV_BRIGHT "BRIGHT"
#define RSV_INVERSE "INVERSE"
#define RSV_OVER "OVER"
#define RSV_BORDER "BORDER"
// Palabras reservadas del preprocesador
#define RSV_LOCATION "LOCATION"
#define RSV_OBJECT "OBJECT"
#define RSV_NOTCREATED "NOTCREATED"
#define RSV_WORN "WORN"
#define RSV_CARRIED "CARRIED"
#define RSV_WORDS "WORDS"
#define RSV_WEIGHT "WEIGHT"
#define RSV_PROPERTY "PROPERTY"
#define RSV_CONTAINER "CONTAINER"
#define RSV_CLOTHING "CLOTHING"
#define RSV_FLAG "FLAG"
#define RSV_SUBCHAR "SUBCHAR"
#define RSV_CONSTANT "CONSTANT"
#define RSV_INCLUDE "INCLUDE"
#define RSV_IFDEF "IFDEF"
#define RSV_IFNDEF "IFNDEF"
#define RSV_ENDIF "ENDIF"
#define RSV_DEFINE "DEFINE"

// Errores de sintaxis
#define MSG_PALAB_RESERV_NO_ENCONTRADA "expected, but found "
#define MSG_FIN_DE_ARCHIVO "end of file"
#define MSG_CODIGO_DE_PALABRA "dictionary word code"
#define MSG_LITERAL_DE_TIPO_DE_PALABRA "word type"
#define MSG_LITERAL_ENTRECOMILLADO "quotation marked literal"
#define MSG_NUMERO_TEXTO_ESPERADO "text message number"
#define MSG_NUMERO_LOCALIDAD "location number"
#define MSG_NUMERO_OBJETO "object number"
#define MSG_DATO_ATRIBUTO_OBJETO "object attribute data"
#define MSG_NOMBRE_CONDACTO "condact name"
#define MSG_PARAMETRO_CONDACTO "condact parameter"
#define MSG_CODIGO_ABREVIATURA "abbreviature code (164-254)"
#define MSG_NOMBRE_ENTRADA_PROCESO "noun code in process entry"
#define MSG_CODIGO_DECIMAL "decimal code"
#define MSG_ATRIBUTO_CHARSET "attribute/charset literal"
#define MSG_NOMBRE_MODULO_PAW "PAW module literal"

// Otros errores
#define MSG_FUERA_DE_LIMITE "Out of bounds data access"
#define MSG_CODIGO_NO_NUMERICO "Not numeric control code"
#define MSG_ATRIBUTOS_OBJ_INSUFICIENTES "Not all objects have attribute"
#define MSG_COD_CONDACTO_MUY_GRANDE "Condact code out of range (0-107)"
#define MSG_ARG_CONDACTO_MUY_GRANDE "Condact argument too big"
#define MSG_CONDACTO_INEXISTENTE "The named condact does no exists"
#define MSG_NO_VERBO_UNO "Verbs with code 1 produce inconsistencies with Response/Process tables in PAW"
#define MSG_MAINTOP_NO_DEF "Maintop not defined, set it with setMaintop() function"
#define MSG_ATRIBUTO_MUY_GRANDE "c\242digo de atributo demasiado grande"
#define MSG_NUMLOCS_NO_DEF "location number not defined, set it with setNumLocs"
#define MSG_CADENA_MAL_FORMADA "character string bad formed"

#define MSG_SINTAXIS "Syntax: inpaws128 <command> <input file> [options]\n\n\
Commands:\n\
    (Target ZX Spectrum 48k):\n\
      c:  Compile to .tap file\n\n\
    (Target PAW CP/M, PC and DAAD):\n\
      cd: Compile to PAW-PC .SCE source file\n\
      cf: Compile to DAAD .DSF source file\n\
      cm: Compile to PAW CPM(Amstrad CPC) .SCE source file\n\n\
    (Target Superglus[Glulx]):\n\
      cs: Compile to Superglus .SCE source file (without symbols)\n\
      ct: Compile to Superglus/txtPaws .TXP source file (with symbols)\n\n\
    (Other commands):\n\
      e:  Extract source from a 48k PAW .SNA or .Z80\n\
      cp: Only generate preprocesed file, without compiling (DEBUGGING)\n\
      eg: Extract graphics code from a 48k PAW .SNA or .Z80\n\
      ec: Extract character info from a 48k PAW .SNA or .Z80\n\n\
  Options:\n\
      -o <output file>: Output file name\n\
      -s : detailed symbol list after compilation\n\
      -z <0-100>: move <0-100> percent of messages to ram page 1\n"
#define MSG_SINTAXISINC "Incorrect syntax"
#define MSG_ERRORFICHERO "Error opening file"
#define MSG_MEMLIBRE "Free memory (in standard 48K memory) after compile: "
#define MSG_SINMEMORIA "Compile failed: PAW memory limit reached"

// Resumen de una compilacion
#define MSG_RESUMEN_LOCALIDADES "locations"
#define MSG_RESUMEN_OBJETOS "objects"
#define MSG_RESUMEN_MENSAJES "messages"
#define MSG_RESUMEN_SISMENSAJES "system messages"
#define MSG_RESUMEN_PROCESOS "processes"
#define MSG_RESUMEN_CARACTERES "character sets"
#define MSG_RESUMEN_VERSION "Database version:"
#define MSG_RESUMEN_ABREVIATURAS "Saved by compression:"
#define MSG_RESUMEN_COMPILOK "Compilation successfully finished\nResulting file: "
#define MSG_RESUMEN_EXTRAEOK "PAW Database successfully extracted to file: "
#define MSG_SIMBOLOSUSADOS "Used symbols in compilation process:"
#define MSG_SCEPORINPAWS "File automatically generated by Inpaws, from an Inpaws syntax"
#define MSG_DSFPORINPAWS "; --- Please don\'t remove the following code, it makes sure the game works correctly for all supported targets \n\
#ifndef \"tape\"\n\
#extern \"MALUVA\"\n\
#endif\n\
\n\
#ifdef \"pcw\"\n\
#define nativeraster 1\n\
#endif\n\
#ifdef \"amiga\"\n\
#define nativeraster 1\n\
#endif\n\
#ifdef \"pc\"\n\
#define nativeraster 1\n\
#endif\n\
#ifdef \"st\"\n\
#define nativeraster 1\n\
#endif\n\
\n\
#ifdef \"uno\"\n\
#int \"MLV_UNO_INT.BIN\"\n\
#define hasSplitMode 1\n\
#define canBoostSpeed 1\n\
#endif\n\
\n\
#ifdef \"next\"\n\
#define canBoostSpeed 1\n\
#endif\n\
\n\
#ifdef \"cpc\"\n\
#int \"MLV_CPC_INT.BIN\"\n\
#define hasSplitMode 1\n\
#endif\n\
\n\
#ifdef \"c64\"\n\
#define hasSplitMode 1\n\
#endif\n\
; -- - Please don't remove the code above, it makes sure the game works correctly for all supported targets \n\
\n\
\n\
#define TIMEOUT   87            ;If Timeout last frame\n\
; System flags 0 - 63\n\
#define fDark               0\n\
#define fObjectsCarried     1\n\
#define fDarkF              28\n\
#define fGFlags             29     ; This is best tested using HASAT GMODE\n\
#define fScore              30\n\
#define fTurns              31    ; 2 bytes\n\
#define fTurnsHi            32\n\
\n\
#define fVerb               33\n\
#define fNoun               34\n\
#define fAdject1            35\n\
#define fAdverb             36\n\
#define fMaxCarr            37\n\
#define fPlayer             38\n\
#define fPrep               43\n\
#define fNoun2              44\n\
#define fAdject2            45\n\
#define fCPronounNoun       46\n\
#define fCPronounAdject     47\n\
#define fTimeout            48\n\
#define fTimeoutFlags       49\n\
#define fDoallObjNo         50\n\
#define fRefObject          51\n\
#define fStrength           52\n\
#define fObjFlags           53\n\
#define fRefObjLoc          54\n\
#define fRefObjWeight       55\n\
#define fRefObjIsContainer  56\n\
#define fRefObjisWearable   57\n\
#define fRefObjAttr1        58\n\
#define fRefObjAttr2        59\n\
#define fInkeyKey1          60\n\
#define fInkeyKey2          61\n\
#define fScreenMode         62     ; 2=Text, 4=CGA, 13=EGA, 141=VGA\n\
#define fCurrentWindow      63     ; Which window is active at the moment\n"

#endif

#define MSG_PROTOP ";------------------------------------------------------------------------------\n\
/PRO 0; Main Location Loop\n\
\n\
> _       _     AT      0; Starting game\n\
\t#ifdef \"canBoostSpeed\"\n\
\t#echo \"Target using boosted CPU speed\"\n\
\tXSPEED  1; if a boostable target, boost CPU speed to 7Mhz\n\
\t#endif\n\
\t#ifdef \"hasSplitMode\"    ; If a split screen target, set split screen\n\
\t#echo \"Target using split mode\"\n\
\tXSPLITSCR 1\n\
\t#endif"

#define MSG_PROTOP2 "\n\
> _       _     WINDOW  0; Select graphics window\n\
\tCLEAR   fDarkF; Assume light\n\
;               MINUS   2       1; Decrement flag 2    (See notes)\n\
\tNOTZERO 0\n\
;               MINUS   3       1; &Flag 3 if Dark(See notes)\n\
\tABSENT  0\n\
;               MINUS   4       1; &Flag 4 if No Lamp(See notes)\n\
\tSET     fDarkF; Dark\n\
\n\
> _       _     #ifndef \"tape\"\n\
\tXPICTURE @fPlayer; If there is a picture, Load it\n\
\t#endif\n\
\t#ifdef \"tape\"\n\
\tCLS\n\
\t#endif\n\
\t#ifdef \"nativeraster\"\n\
\tDISPLAY @fDarkF; &Display it if not dark, else CLS\n\
\t#endif\n\
\t#ifdef \"next\"\n\
\tGT  20 127; Clear the screen if there was an error loading the image\n\
\tXNEXTCLS; Disable and clear Layer2\n\
\t#endif\n\
\n\
> _       _     PICTURE	@fPlayer\n\
\tDISPLAY @fDarkF\n\
\n\
> _       _     WINDOW  1\n\
\tNOTZERO fDarkF; Dark \n\
\tSYSMESS 0 \n\
\n\
> _       _     ZERO    fDarkF\n\
\tDESC    @fPlayer; Doesn't exit loop now\n\
\n\
> _       _     PROCESS 3\n\
\n\
; Now we use Process 1 as the main code loop, a return from it is the end\n\
; of the game\n\
\n\
\n\> _       _     PROCESS 1\n\
\n\
; ------------------------------------------------------------------------------\n\
/PRO 1\n\
> _       _     PROCESS 4; Do process 2 stuff here\n\
\n\
 > _       _     MINUS   5       1; Update auto flags\n\
                MINUS   6       1; These are not supported anymore\n\
                MINUS   7       1; as we use the low section as\n\
                MINUS   8       1; a small stack\n\
                NOTZERO 0; But should you need them\n\
                MINUS   9       1; this is the Version 1 DAAD code!\n\
                ABSENT  0\n\
                MINUS   10      1\n\
;   If converting a PAW or Quill game, the above flags will\n\
;   probably need to be uncommented\n\
;   Yes, InPaws128 has uncommented them!\n\
\n\
> _       _     PARSE   0; Get next LS from current buffer\n\
\tPROCESS 2; Failed cos of invalid or timeout\n\
\tREDO\n\
\n\
> _       _     EQ      fTurns   255; Max for one byte\n\
\tPLUS    fTurnsHi 1\n\
\tCLEAR   fTurns\n\
\tSKIP    1\n\
\n\
> _       _     PLUS    fTurns   1\n\
\n\
> _       _     PROCESS 5; Do any commands\n\
\tISDONE; Done something\n\
\tREDO\n\
\n\
> _       _     MOVE    fPlayer; No so try to move player\n\
\tRESTART; Absolute jump to start process 0\n\
\n\
> _       _     NEWTEXT\n\
\tLT      fVerb    14\n\
\tSYSMESS 7\n\
\tREDO\n\
\n\
> _       _     SYSMESS 8\n\
\tREDO\n\
\n\
\n\
; ------------------------------------------------------------------------------\n\
/PRO 2\n\
> _       _     HASAT TIMEOUT\n\
\tSYSMESS 35\n\
\tDONE\n\
\n\
> _       _     SYSMESS 6; I didn\'t understand\"\n\
\n\
; ------------------------------------------------------------------------------"

#define MSG_PROBOT "\n\
> _       _     WINDOW  1; Windows are random\n\
\n\
> _       _     #ifndef \"tape\"\n\
\tWINAT   14       0\n\
\t#endif\n\
\t#ifdef \"tape\"\n\
\tWINAT   0       0\n\
\t#endif\n\
\tWINSIZE 25      127; Maximum window\n\
\t;Commented out by InPaws128 as it is assumed that\n\
\t;your converted game handles what happens when\n\
\t;the game starts at location 0. Uncomment the below as required.\n\
\t;CLS\n\
\t;DESC    0; Introduction\n\
\t;ANYKEY\n\
\t;CLS\n\
\tSET   255\n\
\n\
> _       _     MINUS  255 1; Clear all flags\n\
\tNOTEQ   255  fGFlags; except fGFlags!!!\n\
\tCLEAR   @255\n\
\n\
> _       _     NOTZERO 255\n\
\tSKIP -2\n\
\n\
> _       _     RESET; Set objects to start location& Flag 1\n\
\tLET     fStrength 10\n\
\tLET     fMaxCarr  4\n\
\tSET     fCPronounNoun\n\
\tSET     fCPronounAdject\n\
\tGOTO    0; Main game"

#endif
