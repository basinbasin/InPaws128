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

#include "include/Textos.h"
#include "include/defines.h"
#include "include/MsgAplicacion.h"
#include "include/Excepcion.h"
#include "include/UtilTexto.h"
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace Inpaws;
using namespace std;

Textos::Textos(PtrBuffer ptrIndice, SpWord offNumText,
               const std::string& titulo)
 : PawPart(ptrIndice), _offNumText (offNumText), _titulo (titulo)
{
}

Textos::~Textos()
{

}

PtrBuffer
Textos::volcarDeMemoria ()
{
    getInicioDatos();                 // Fijar desde donde hay que leer

    SpByte numTextos = SPBUFFER->bytePeek(SPBUFFER->wordPeek(PTR_MAINTOP) + _offNumText);
    SpWord ultimaPos(0); // Última posicion leida

    _textos.clear();               // Limpiamos lo anterior

    for (unsigned char i = 0; i < numTextos; i++)
    {

        // DEBUG ***
        /*    PtrBuffer ptr = SPBUFFER->wordPeek(ptrIndice + 2*i);
            cout << (unsigned int)i << ": ";
            while (SPBUFFER->charPeek(ptr) != 31)
                cout << (int)(unsigned char)SPBUFFER->charPeek(ptr++) << " ";
            cout << endl;*/
        // <- DEBUG

        string texto;
        ultimaPos =
          _leerTextoMemoria (texto,
                             SPBUFFER->wordPeek(ptrDatos() + 2*i));

        anadirTexto (i, texto);



    }
    return ultimaPos + numTextos*2; // Ultima posicion detras de los indices
}


PtrBuffer
Textos::volcarAMemoria(PtrBuffer ptrInicioDatos) const
{
	// El formato de los mesajes es, primero volcamos todos los mensajes
	// a partir de ptrInicioDatos. A continuación van todos los indices
	// La direccion del primer indice va a _ptrIndice


	// The format of the messages is, first we dump all the messages
	// from ptrInicioDatos. Below are all the indices
	// The address of the first index goes to _ptr Index

	vector<SpWord> punterosAMensajes;
	vector<SpWord> page1Messages;
	vector<SpWord> page1Locations;
	PtrBuffer ptrTextos = ptrInicioDatos;

	//PtrBuffer ptrPage1Text = PAGE_1_MSGS;//40000 less than actual location

	// this is now going to point to the start of the ram page 0 LOCATION start point
	// this is no longer accurate as the location of  PAGE_1_MSGS will move dependent on the size of the page 1 locations
	//so initialise here, but we'll need to define it later on.
	// use zxmemory location 101-102 to store this value

	PtrBuffer ptrPage1Text= SPBUFFER->wordPeek(101); //= PAGE_1_MSGS;//40000 less than actual location
	PtrBuffer ptrPage1Locs = PAGE_1_LOCS;//40000 less than actual location

	// We write the number of messages in PTR_MAINTOP + displacement
	SPBUFFER->bytePoke(SPBUFFER->wordPeek(PTR_MAINTOP) + _offNumText,
		_textos.size());
	//printf("Output: %d, %d \n", SPBUFFER->wordPeek(PTR_MAINTOP) + _offNumText, _textos.size());
	// Y tambien en cierta direccion de memoria, para que funcione
	// el editor (comprobación empírica)


	// And also in a certain memory address, so that it works
	// the editor (empirical verification)

	int test = 1; //change to 1 to run page1 stuff
	int index = 0;
	int setpercent = SPBUFFER->bytePeek(0);

	int standardLocationSize = 0;
	
	double messagepercent = (double(_textos.size()) / 100) * (100- setpercent);

	messagepercent = int(messagepercent);

	if (test == 1 && ptrIndice() == PTR_MENSAJES) {
		//do nothing, value already altered above
		// run as normal for the moment!, put all messages through page0
		// messagepercent = _textos.size() - 1;
	}
	else if (test == 1 && ptrIndice() == PTR_LOCALIDADES) {
		// put all but the final location through standard memory
		standardLocationSize = _textos.size() - 1;
		//printf("standardLocationSize: %d , all: %d \n", standardLocationSize,_textos.size());
	}
	else {
		// run as normal, put all messages and locations through page0
		messagepercent = _textos.size();
		standardLocationSize = _textos.size();
	}

	int messagepercentInt = messagepercent;

	switch (ptrIndice())
	{

		// the following values are poked with the number of items in ram page 0 (standard memory)

	case PTR_MENSAJES:
		// SPBUFFER->bytePoke(65528, _textos.size());
		 // JM part of testing for ram page
		SPBUFFER->bytePoke(65528, messagepercentInt);
		break;
	case PTR_SYSMENSAJES:
		SPBUFFER->bytePoke(65529, _textos.size());
		break;
	case PTR_OBJETOS:
		SPBUFFER->bytePoke(65530, _textos.size());
		break;
		// locations
	case PTR_LOCALIDADES:
		SPBUFFER->bytePoke(65531, standardLocationSize);
		break;
	}

	// 	First we write the messages

	for (TTextos::const_iterator it = _textos.begin();
		it != _textos.end();
		it++, index++)
	{		

		// amended from <= messagepercentInt to < messagepercentInt because of array being 0-based
		
		if ((ptrIndice() != PTR_MENSAJES && ptrIndice() != PTR_LOCALIDADES)|| ptrIndice() == PTR_MENSAJES && index < messagepercentInt || ptrIndice() == PTR_LOCALIDADES && index < standardLocationSize) {
		

			// First the pointer to the message in the index
			punterosAMensajes.push_back(ptrTextos);
			// 		We go through the message and start writing
			for (string::const_iterator itTexto = (*it).second.begin();
				itTexto != (*it).second.end();
				itTexto++)
			{
				if (*itTexto == '^')
				{
					SPBUFFER->charPoke(ptrTextos, 7);
				}
				else if (*itTexto == '{')
				{
					itTexto++;
					if (itTexto == (*it).second.end())
						break;

					SPBUFFER->charPoke(ptrTextos, _valueOf(itTexto));
				}
				else if (*itTexto == '\\')
				{
					itTexto++;
					if (itTexto == (*it).second.end())
						break;
					if (*itTexto == '{')
						SPBUFFER->charPoke(ptrTextos, 0x7B); // literal de llave abierta en PAW
					else if (*itTexto == '^')
						SPBUFFER->charPoke(ptrTextos, '^'); // literal de ^ en PAW
					else if (*itTexto == '\\')
						SPBUFFER->charPoke(ptrTextos, '\\'); // literal de barra invertida en PAW
					else throw Excepcion("\"" + (*it).second + "\": " + MSG_CADENA_MAL_FORMADA);

				}
				else
				{
					SPBUFFER->charPoke(ptrTextos, *itTexto);
				}
				ptrTextos++;


			}
			//indicates the end of a message
			SPBUFFER->charPoke(ptrTextos++, 31);

			/*if (ptrIndice() == PTR_LOCALIDADES) {
				printf("Loc Standard Index: %d: \n", index);
			}

			if (ptrIndice() == PTR_MENSAJES) {
				printf("Msg Standard Index: %d: \n", index);
			}*/

			

			//printf("Msg Index: %d: \n", index);
			//printf("messagepercentInt: %d: \n", messagepercentInt);
		}

		//new logic just for final location text to be pushed to ram page1
		else if (ptrIndice() == PTR_LOCALIDADES && index == standardLocationSize) {

			//printf("Loc Index: %d: ,%d \n", index, standardLocationSize);
			// First the pointer to the location in the index
			page1Locations.push_back(ptrPage1Locs);
			// 		We go through the message and start writing
			for (string::const_iterator itTexto = (*it).second.begin();
				itTexto != (*it).second.end();
				itTexto++)
			{
				if (*itTexto == '^')
				{
					SPBUFFER->charPoke(ptrPage1Locs, 7);
				}
				else if (*itTexto == '{')
				{
					itTexto++;
					if (itTexto == (*it).second.end())
						break;

					SPBUFFER->charPoke(ptrPage1Locs, _valueOf(itTexto));
				}
				else if (*itTexto == '\\')
				{
					itTexto++;
					if (itTexto == (*it).second.end())
						break;
					if (*itTexto == '{')
						SPBUFFER->charPoke(ptrPage1Locs, 0x7B); // literal de llave abierta en PAW
					else if (*itTexto == '^')
						SPBUFFER->charPoke(ptrPage1Locs, '^'); // literal de ^ en PAW
					else if (*itTexto == '\\')
						SPBUFFER->charPoke(ptrPage1Locs, '\\'); // literal de barra invertida en PAW
					else throw Excepcion("\"" + (*it).second + "\": " + MSG_CADENA_MAL_FORMADA);

				}
				else
				{
					SPBUFFER->charPoke(ptrPage1Locs, *itTexto);
				}
				ptrPage1Locs++;


			}
			//indicates the end of a location
			SPBUFFER->charPoke(ptrPage1Locs++, 31);
			//printf("Msg Index: %d: \n", index);
			//printf("messagepercentInt: %d: \n", messagepercentInt);
		}
		else {


			// First the pointer to the message in the index
			page1Messages.push_back(ptrPage1Text);
			// 		We go through the message and start writing
			for (string::const_iterator itTexto = (*it).second.begin();
				itTexto != (*it).second.end();
				itTexto++)
			{
				if (*itTexto == '^')
				{
					SPBUFFER->charPoke(ptrPage1Text, 7);
				}
				else if (*itTexto == '{')
				{
					itTexto++;
					if (itTexto == (*it).second.end())
						break;

					SPBUFFER->charPoke(ptrPage1Text, _valueOf(itTexto));
				}
				else if (*itTexto == '\\')
				{
					itTexto++;
					if (itTexto == (*it).second.end())
						break;
					if (*itTexto == '{')
						SPBUFFER->charPoke(ptrPage1Text, 0x7B); // literal de llave abierta en PAW
					else if (*itTexto == '^')
						SPBUFFER->charPoke(ptrPage1Text, '^'); // literal de ^ en PAW
					else if (*itTexto == '\\')
						SPBUFFER->charPoke(ptrPage1Text, '\\'); // literal de barra invertida en PAW
					else throw Excepcion("\"" + (*it).second + "\": " + MSG_CADENA_MAL_FORMADA);

				}
				else
				{
					SPBUFFER->charPoke(ptrPage1Text, *itTexto);
				}
				ptrPage1Text++;
				//printf("Msg: %d: \n", ptrTextos);

			}
			SPBUFFER->charPoke(ptrPage1Text++, 31);


		}
	}

	// And then the indices

	// Primero almacenamos el inicio de los indices en ptrIndice
	// First we store the beginning of the indices in ptr Index


	//reset the index for the indices loop
	index = 0;



	// this bit points to the END of the block of message text
	// actually 1 byte ahead of that - to the start of the index of the messages (see below)
	// and pokes that location to 65503/4 (for messages)

	SPBUFFER->wordPoke(_ptrIndice, ptrTextos);
	// Y luego la lista de indices uno tras otro
	//printf("_ptrIndice %d, ptrTextos %d \n", _ptrIndice, ptrTextos);
	//And then the index list one after the other

	// So, at the end of the block of messages, we now have the block of pointers,
	// 2-byte location of each message
	// Will need to replicate this for page1


	for (vector<SpWord>::const_iterator itIndices = punterosAMensajes.begin();
		itIndices != punterosAMensajes.end();
		itIndices++, index++)
	{
		SPBUFFER->wordPoke(ptrTextos, *itIndices);
		//printf("ptrTextos %d, *itIndices %d \n", ptrTextos, *itIndices);
		ptrTextos += 2;

	}


	//feb 2020 - new bit for page 1 location text
	// this is the version to poke the page1 version in 
	if (ptrIndice() == PTR_LOCALIDADES && page1Locations.size() > 0)
	{

		// we're going to build the B file for page 1 at 00484 
		// and it'll be loaded in at 65484

	// tell the page 1 location store where the end of the page1textstore is
		// need to poke the actual location with the value of where the 
		// page1 store will end up being!
		SPBUFFER->wordPoke(_ptrIndice - 65000, ptrPage1Locs + 40000);		

		
		//And then the index list one after the other

		// So, at the end of the block of messages, we now have the block of pointers,
		// 2-byte location of each message
		// Will need to replicate this for page1


		for (vector<SpWord>::const_iterator itIndices = page1Locations.begin();
			itIndices != page1Locations.end();
			itIndices++)
		{
		
			SPBUFFER->wordPoke(ptrPage1Locs, *itIndices + 40000);
			//printf("ptrPage1Locs: %d, *itIndices: %d \n", ptrPage1Locs, *itIndices + 40000);
			ptrPage1Locs += 2;
		}

		//get the end pointer of the location data and indexes, and now add the message location start flag at the end
		int page1LocOffset = ptrPage1Locs;

		SPBUFFER->bytePoke(page1LocOffset, 146);	//146 flag to denote messages start here...
		// now set the pointer for the messages
		ptrPage1Text = page1LocOffset + 1;
		// store this value in zx memory so it won't be overwritten
		SPBUFFER->wordPoke(101, ptrPage1Text);
		//printf("ptrPage1Text: %d \n", ptrPage1Text);
	}


	// this is the version to poke the page1 version in 
	if (ptrIndice() == PTR_MENSAJES && page1Messages.size() > 0)
	{
		//printf("X-ptrPage1Text: %d \n", ptrPage1Text);
		// we're going to build the B file for page 1 at 00484 
		// and it'll be loaded in at 65484

	// tell the page 1 location store where the end of the page1textstore is
		// need to poke the actual location with the value of where the 
		// page1 store will end up being!
		SPBUFFER->wordPoke(_ptrIndice - 65000, ptrPage1Text+40000 );

		//printf("_ptrIndice-65000: %d, ptrPage1Text+40000: %d \n", _ptrIndice - 65000, ptrPage1Text + 40000);

		// Y luego la lista de indices uno tras otro

		//And then the index list one after the other

		// So, at the end of the block of messages, we now have the block of pointers,
		// 2-byte location of each message
		// Will need to replicate this for page1


		for (vector<SpWord>::const_iterator itIndices = page1Messages.begin();
			itIndices != page1Messages.end();
			itIndices++)
		{
			// this isn't pointing to the right place and needs fixing!
			SPBUFFER->wordPoke(ptrPage1Text , *itIndices+40000);
			//printf("ptrPage1Text: %d, *itIndices: %d \n", ptrPage1Text, *itIndices + 40000);
			ptrPage1Text += 2;
		}

		//this contains the start of the rest of the page1 data
		int page1offset = ptrPage1Text;

		//this will eventually be the working code
		//for now is a wip and will be over-written by the code below
		//create the page1 data (the c file) that contains the actual messages
		SPBUFFER->bytePoke(9152, 255);
		SPBUFFER->bytePoke(9153, 0);
		SPBUFFER->bytePoke(9154, 0);
		SPBUFFER->bytePoke(9155, 0);
		SPBUFFER->bytePoke(9156, 192);
		SPBUFFER->bytePoke(9157, 1);
		SPBUFFER->bytePoke(9158, 192);
		SPBUFFER->bytePoke(9159, 224);
		SPBUFFER->bytePoke(9160, 7);
		SPBUFFER->bytePoke(9161, 192);
		SPBUFFER->bytePoke(9162, 147);  //147 flag to denote locations start here...

		//feb 2020 the next 4 bytes will need to be commented out, because the code will sort the locations out

		//SPBUFFER->bytePoke(9163, 206);	//one byte of location text	
		//SPBUFFER->bytePoke(9164, 224);	//end of location neg31
		//SPBUFFER->bytePoke(9165, 10);	//start of location pointer
		//SPBUFFER->bytePoke(9166, 192);	//end of location pointer i.e 10+(192*256)
		//SPBUFFER->bytePoke(9167, 146);	//146 flag to denote messages start here...

		// the above code will have populated:
		// page 1 messages
		// page 1 message indices

		//sysmessages
		SPBUFFER->bytePoke(page1offset, 224);//sysmessage end neg31
		SPBUFFER->wordPoke(page1offset+1, page1offset + 40000); //eventual location of page1 sysmessages

		//poke this value into the d file for sysmessages
		SPBUFFER->wordPoke(505, page1offset + 1 + 40000);

		//connections
		SPBUFFER->bytePoke(page1offset+3, 255);//sysmessage end neg31
		SPBUFFER->wordPoke(page1offset + 4, page1offset+3 + 40000); //eventual location of page1 connections

		//poke this value into the d file for connections
		SPBUFFER->wordPoke(507, page1offset + 4 + 40000);

		//vocab - 5 bytes of 0
		SPBUFFER->bytePoke(page1offset + 6, 0);
		SPBUFFER->bytePoke(page1offset + 7, 0);
		SPBUFFER->bytePoke(page1offset + 8, 0);
		SPBUFFER->bytePoke(page1offset + 9, 0);
		SPBUFFER->bytePoke(page1offset + 10, 0);

		//poke this value into the d file for vocab
		SPBUFFER->wordPoke(509, page1offset + 6 + 40000);

		//initially at - 1 byte of 252
		SPBUFFER->bytePoke(page1offset + 11, 252);

		//poke this value into the d file for initially at
		SPBUFFER->wordPoke(511, page1offset + 11 + 40000);


		//offset + 12 is poked with 255, but doesn't appear to be used with a lookup
		SPBUFFER->bytePoke(page1offset + 12, 255);

		//objwords - 1 byte of 255
		SPBUFFER->bytePoke(page1offset + 13, 255);

		//no pointer in the c file, so just poke this value into the d file for objwords
		SPBUFFER->wordPoke(513, page1offset + 13 + 40000);
		
		//offset + 14 is poked with 0, but doesn't appear to be used with a lookup
		SPBUFFER->bytePoke(page1offset + 14, 0);

		//objweight - 1 byte of 1
		SPBUFFER->bytePoke(page1offset + 15, 1);

		//no pointer in the c file, so just poke this value into the d file for objweight
		SPBUFFER->wordPoke(515, page1offset + 15 + 40000);		

		// ADD THESE BACK IN TO COMPLETE THE DATA FOR PAGE 1
		// THESE VALUES MEAN THAT THE LOCATION IN PAGE 1 CANNOT HAVE GRAPHICS
		//now the d file
		SPBUFFER->bytePoke(484, 7);  // EMPTY GRAPHIC DATA FOR THE LOCATION IN PAGE 1
		SPBUFFER->bytePoke(485, 204); // 2 BYTE POINTER BACK TO THE 7 ABOVE
		SPBUFFER->bytePoke(486, 255);
		SPBUFFER->bytePoke(487, 205); // 2 BYTE POINTER BACK TO OFFGRAPH
		SPBUFFER->bytePoke(488, 255);
		SPBUFFER->bytePoke(489, 255); // 2 BYTES OF 255 SIGNIFY END OF GRAPHICS MARKER
		SPBUFFER->bytePoke(490, 255);
		SPBUFFER->bytePoke(491, 7); // ATTR VALUE FOR GRAPHIC FOR LOCATION IN PAGE 1
		SPBUFFER->bytePoke(492, 255); // 255 - END OF ATTR FLAG
		SPBUFFER->bytePoke(493, 0);
		SPBUFFER->bytePoke(494, 0);
		SPBUFFER->bytePoke(495, 0);
		SPBUFFER->bytePoke(496, 0);
		SPBUFFER->bytePoke(497, 5);	//OffProcess
		SPBUFFER->bytePoke(498, 192);
		SPBUFFER->bytePoke(499, 8);	//OffObj
		SPBUFFER->bytePoke(500, 192);

		//and these values at the end never change
		SPBUFFER->bytePoke(page1offset + 19, 0);
		SPBUFFER->bytePoke(page1offset + 20, 0);
		SPBUFFER->bytePoke(page1offset + 21, 0);
		SPBUFFER->bytePoke(page1offset + 22, 0);
		SPBUFFER->bytePoke(page1offset + 23, 0);
		SPBUFFER->bytePoke(page1offset + 24, 252);
		SPBUFFER->bytePoke(page1offset + 25, 255);
		SPBUFFER->bytePoke(page1offset + 26, 255);
		SPBUFFER->bytePoke(page1offset + 27, 0);
		SPBUFFER->bytePoke(page1offset + 28, 1);
		
		//the address of the end of the page1 file must be poked into 65517
		SPBUFFER->wordPoke(517, page1offset + 29 + 40000);


		// remainder of the code ending at 65535
		SPBUFFER->bytePoke(519, 204); // 2 BYTE POINTER TO 65484 - START OF GRAPHICS
		SPBUFFER->bytePoke(520, 255); 
		SPBUFFER->bytePoke(521, 205); // 2 BYTE POINTER TO OFFGRAPH
		SPBUFFER->bytePoke(522, 255);
		SPBUFFER->bytePoke(523, 211); // 2 BYTE POINTER TO ATTR
		SPBUFFER->bytePoke(524, 255);
		SPBUFFER->bytePoke(525, 212); // 2 BYTE POINTER TO END OF ATTR 255 FLAG
		SPBUFFER->bytePoke(526, 255);
		SPBUFFER->bytePoke(527, 0);
		SPBUFFER->bytePoke(528, page1Messages.size());	// number of messages in page 1
		SPBUFFER->bytePoke(529, 1);
		SPBUFFER->bytePoke(530, 1);
		SPBUFFER->bytePoke(531, 1);	// number of locations in page 1, which'll always be 1
		SPBUFFER->bytePoke(532, 1);
		SPBUFFER->bytePoke(533, 0);	//maintop low
		SPBUFFER->bytePoke(534, 192);	//maintop high
		SPBUFFER->bytePoke(535, 1); //this seems to be the page number?


		//amend this value to NOT poke the standard c/d pokes in....
		// so set to 1 or whatever, once we want to test the above....

		int tryit = 1;


		if (tryit == 0) {		

			// ============================================================================================================
			// XX
			//test to create the c and d files
			//leave this in, and eventually comment out to test if the other bit is working
			//c file
			SPBUFFER->bytePoke(9152, 255);
			SPBUFFER->bytePoke(9153, 0);
			SPBUFFER->bytePoke(9154, 0);
			SPBUFFER->bytePoke(9155, 0);
			SPBUFFER->bytePoke(9156, 192);
			SPBUFFER->bytePoke(9157, 1);
			SPBUFFER->bytePoke(9158, 192);
			SPBUFFER->bytePoke(9159, 224);
			SPBUFFER->bytePoke(9160, 7);
			SPBUFFER->bytePoke(9161, 192);
			SPBUFFER->bytePoke(9162, 147); //location desc starts here...
			SPBUFFER->bytePoke(9163, 206);

			//revised end of c file
			SPBUFFER->bytePoke(9164, 224);	//... and ends here with neg31
			SPBUFFER->bytePoke(9165, 10);	//start of location pointer
			SPBUFFER->bytePoke(9166, 192);	//end of location pointer
			SPBUFFER->bytePoke(9167, 146);	//start of message text
			SPBUFFER->bytePoke(9168, 206);	
			SPBUFFER->bytePoke(9169, 224);	//end of message neg31
			SPBUFFER->bytePoke(9170, 15);	//start of message pointer
			SPBUFFER->bytePoke(9171, 192);
			SPBUFFER->bytePoke(9172, 224);
			SPBUFFER->bytePoke(9173, 20);
			SPBUFFER->bytePoke(9174, 192);
			SPBUFFER->bytePoke(9175, 255);
			SPBUFFER->bytePoke(9176, 23);
			SPBUFFER->bytePoke(9177, 192);
			SPBUFFER->bytePoke(9178, 0);
			SPBUFFER->bytePoke(9179, 0);
			SPBUFFER->bytePoke(9180, 0);
			SPBUFFER->bytePoke(9181, 0);
			SPBUFFER->bytePoke(9182, 0);
			SPBUFFER->bytePoke(9183, 252);
			SPBUFFER->bytePoke(9184, 255);
			SPBUFFER->bytePoke(9185, 255);
			SPBUFFER->bytePoke(9186, 0);
			SPBUFFER->bytePoke(9187, 1);



			//now the d file
			SPBUFFER->bytePoke(484, 7);
			SPBUFFER->bytePoke(485, 204);
			SPBUFFER->bytePoke(486, 255);
			SPBUFFER->bytePoke(487, 205);
			SPBUFFER->bytePoke(488, 255);
			SPBUFFER->bytePoke(489, 255);
			SPBUFFER->bytePoke(490, 255);
			SPBUFFER->bytePoke(491, 7);
			SPBUFFER->bytePoke(492, 255);
			SPBUFFER->bytePoke(493, 0);
			SPBUFFER->bytePoke(494, 0);
			SPBUFFER->bytePoke(495, 0);
			SPBUFFER->bytePoke(496, 0);
			SPBUFFER->bytePoke(497, 5);	//OffProcess
			SPBUFFER->bytePoke(498, 192);
			SPBUFFER->bytePoke(499, 8);	//OffObj
			SPBUFFER->bytePoke(500, 192);


			//revised code to modify the above
			SPBUFFER->bytePoke(501, 13);	//Locations
			SPBUFFER->bytePoke(502, 192);
			SPBUFFER->bytePoke(503, 18);	//Messages
			SPBUFFER->bytePoke(504, 192);
			SPBUFFER->bytePoke(505, 21);	//SysMessages
			SPBUFFER->bytePoke(506, 192);
			SPBUFFER->bytePoke(507, 24);	//Connections
			SPBUFFER->bytePoke(508, 192);
			SPBUFFER->bytePoke(509, 26);	//Vocab
			SPBUFFER->bytePoke(510, 192);
			SPBUFFER->bytePoke(511, 31);	//InitiallyAt
			SPBUFFER->bytePoke(512, 192);
			SPBUFFER->bytePoke(513, 33);
			SPBUFFER->bytePoke(514, 192);
			SPBUFFER->bytePoke(515, 35);
			SPBUFFER->bytePoke(516, 192);
			SPBUFFER->bytePoke(517, 36);
			SPBUFFER->bytePoke(518, 192);
			SPBUFFER->bytePoke(519, 204);
			SPBUFFER->bytePoke(520, 255);
			SPBUFFER->bytePoke(521, 205);
			SPBUFFER->bytePoke(522, 255);
			SPBUFFER->bytePoke(523, 211);
			SPBUFFER->bytePoke(524, 255);
			SPBUFFER->bytePoke(525, 212);
			SPBUFFER->bytePoke(526, 255);
			SPBUFFER->bytePoke(527, 0);
			SPBUFFER->bytePoke(528, 1);	// number of messages in page 1
			SPBUFFER->bytePoke(529, 1);
			SPBUFFER->bytePoke(530, 1);
			SPBUFFER->bytePoke(531, 1);	// number of locations in page 1
			SPBUFFER->bytePoke(532, 1);
			SPBUFFER->bytePoke(533, 0);	//maintop low
			SPBUFFER->bytePoke(534, 192);	//maintop high
			SPBUFFER->bytePoke(535, 1);

		}

	}

	return ptrTextos - 1;
}


void
Textos::anadirTexto (SpByte codigo,const std::string& texto)
{
    if (_textos.find(codigo) != _textos.end())
        _textos.erase(codigo);

    _textos.insert (pair<SpByte, std::string>(codigo, texto));
}

const std::string&
Textos::obtenerTexto (SpByte codigo) const
{
    TTextos::const_iterator it = _textos.find (codigo);
    if (it != _textos.end())
        return (*it).second;
    else
        throw (Excepcion ("Textos: " + string(MSG_FUERA_DE_LIMITE)));
}

SpWord
Textos::_leerTextoMemoria (std::string& texto, SpWord posicion) const
{
    // Sigue la estructura de unpaws
    int colorCodes = 0;
    SpByte c = SPBUFFER->charPeek(posicion);

    // El valor de retorno es la última posición leida
    texto.clear();
    while (c != 31)
    {
        if (colorCodes)
        {
            texto.append ("{");
            texto.append (_numeroAString(c));
            texto.append ("}");
            colorCodes--;
        }
        else
        {
            if (c > 15 && c < 22) colorCodes = 1;
                else if (c == 22 || c== 23) colorCodes = 2;
                else colorCodes = 0;

            if (c == 0X7B)
            {
                texto.append("\\{"); // Si hay realmente un caracter '{' en el mensaje
            }
            else if (c == 0x5E) // El caracter ^ en PAW
            {
                texto.append("\\^");
            }
            else if (c == '\\') // El caracter de la barra invertida en PAW (que por cierto es la Ñ en el español)
            {
                texto.append("\\\\");
            }
            else if (c==22 || c== 23)
            {
                texto.append(1, 32);

            }
            else if (c > 31 && c != '^' && c < 127 && c != 96)
            {
                texto.append(1, c);
            }
            else if (c > 164) // Abreviaturas
            {
                texto.append ("{");
                texto.append (_numeroAString(c));
                texto.append ("}");
            }
            else if (c == 7)
            {
                texto.append(1, '^');
            }
            else
            {
                texto.append ("{");
                texto.append (_numeroAString(c));
                texto.append ("}");

            }
        }
        posicion++;
        c = SPBUFFER->charPeek (posicion);
    }

    return posicion;
}

void
Textos::generarCodigo (std::ostream& os)
{
    os << _titulo << endl << "{" << endl;
    for (SpByte i=0; i < _textos.size(); i++)
    {
        os << '\t' << (unsigned int) i << ": \"";

        _generarTexto(os, _textos[i]);

        os << "\";" << endl;
    }
    os << "}" << endl;
}

void
Textos::generarCodigoDisco (std::ostream& os, uint16_t flags)
{
    UtilTexto utilTexto;

    if (_titulo == RSV_SYSMESSAGES)
        os << "/STX";
    else if (_titulo == RSV_MESSAGES)
        os << "/MTX";
    else if (_titulo == RSV_LOCATIONS)
        os << "/LTX";
    else if (_titulo == RSV_OBJECTS)
        os << "/OTX";

    os << "\t; " << _titulo << endl;

    for (SpByte i=0; i < _textos.size(); i++)
    {
        os << "/" << (unsigned int) i << endl;
        if (flags & VERGLULX)
            os << utilTexto.filtrarParaSuperglus(_textos[i]) << endl;
		else if (flags & CONVERTDSF)
			os << utilTexto.filtrarParaDSF(_textos[i]) << endl;
        else
            os << utilTexto.filtrarParaSCE(_textos[i]) << endl;
    }
}

void
Textos::generarCodigoSuperglus (std::ostream& os, uint16_t flags,
                             Diccionario::TDiccionarioInverso diccionario)
{
    UtilTexto utilTexto;
    int tipo = -1;

    if (_titulo == RSV_SYSMESSAGES)
    {
        os << "/STX";
        tipo = SYSNO;
    }
    else if (_titulo == RSV_MESSAGES)
    {
        os << "/MTX";
        tipo = MESNO;
    }
    else if (_titulo == RSV_LOCATIONS)
    {
        os << "/LTX";
        tipo = LOCNO;
    }
    else if (_titulo == RSV_OBJECTS)
    {
        os << "/OTX";
        tipo = OBJNO;
    }

    os << endl;

    for (SpByte i=0; i < _textos.size(); i++)
    {
        os << "/" << (unsigned int) i;

        pair<int, int> indice((unsigned int) i, tipo);
        Diccionario::TDiccionarioInverso::const_iterator it = diccionario.find(indice);
        if (it != diccionario.end() && (*it).second[0] != '\"')
        {
            os << " = " << (*it).second;
        }
        os << endl;

        if (it == diccionario.end() || (*it).second[0] != '\"')
        {
            os << utilTexto.filtrarParaSuperglus(_textos[i]) << endl;
        }
        else
        {
            os << "; Este mensaje se muestra con WRITE, está definido por compatibilidad con Inpaws" << endl
               << "; y puedes reutilizarlo para tus propios fines" << endl
               << ";" << (*it).second << endl;
        }
    }
}

void
Textos::leerDeCodigo (Tokeniser& tokeniser)
{
    // Al tratarse de un código ya preprocesado y supuestamente sin
    // errores, todo lo que no esté bien generará excepción

    Tokeniser::TTokenType token;

    // Primero aparece el literal LOCATIONS/MESSAGES/SYSMESSAGES/OBJECTS y el "{"
    saltarToken (tokeniser, Tokeniser::TK_IDENTIFICADOR, _titulo);
    saltarToken (tokeniser, Tokeniser::TK_CONTROL, "{");

    // Ahora leemos la lista de textos
    // en formato: Nº: "Cadena de texto" (ej: 131: "Te encuentras en un oscuro paraje.")
    SpByte numTexto;
    string textoLeido;
    token = tokeniser.leeToken();
    while (!(token == Tokeniser::TK_CONTROL &&
             tokeniser.lvalue().literal == "}"))
    {
        // Codigo

        if (token == Tokeniser::TK_NUMERO)
            numTexto = tokeniser.lvalue().valor;
        else
            throw ExcTokeniser(tokeniser.errorLeidoEsperado(MSG_NUMERO_TEXTO_ESPERADO));

        saltarToken (tokeniser, Tokeniser::TK_CONTROL, ":");

        // Literal de texto
        token = tokeniser.leeToken();
        if (token == Tokeniser::TK_LITERAL)
            textoLeido = tokeniser.lvalue().literal;
        else
            throw ExcTokeniser(tokeniser.errorLeidoEsperado(MSG_LITERAL_ENTRECOMILLADO));

        saltarToken (tokeniser, Tokeniser::TK_CONTROL, ";");

        // Añadimos el texto
        anadirTexto (numTexto, textoLeido);

        token = tokeniser.leeToken();
    }
}

std::string
Textos::_numeroAString(SpByte spbyte) const
{
    ostringstream osstr;

    osstr << (unsigned int)spbyte;

    return osstr.str();
}

SpByte
Textos::_valueOf (string::const_iterator& it) const
{
    string tmp;

    // Lo primero es un {, lo saltamos

    while (*it != '}')
    {
        if (*it >= '0' && *it <= '9' && tmp.size() < 3)
            tmp.append(1,*it);
        else
            throw Excepcion(tmp+":"+MSG_CODIGO_NO_NUMERICO);
        it++;
    }
    return atoi(tmp.c_str());
}

void
Textos::_generarTexto (std::ostream& os, const string& texto) const
{
    Tokeniser::imprimirLiteral(texto, os);
}
