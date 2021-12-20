
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


#include "../include/prep/PrepUtilTexto.h"
#include "../include/prep/MsgPrep.h"
#include <sstream>
#include <cstdlib>

using namespace Inpaws;
using namespace std;

PrepUtilTexto::PrepUtilTexto()
 : _posactual(0)
{
}

PrepUtilTexto::~PrepUtilTexto()
{
}

bool
PrepUtilTexto::textoCorrecto (const string& texto)
{
    _posactual = 0;
    _errorStr = "";

    Item item = _siguienteItem(texto);
    while (item.tipo != ERROR && item.tipo != FIN)
    {
        item = _siguienteItem(texto);
        if (item.tipo == ERROR)
        {
            ostringstream ostr;
            ostr << MSGPREP_LITERALINCORRECTO << " (pos. " << _posactual << ")";
            _errorStr = ostr.str();
        }
    }

    if (item.tipo == ERROR)
        return false;
    else
        return true;
}

int
PrepUtilTexto::expandirAbreviaturas (string& texto, const PrepAbreviaturas& abreviaturas)
{
	//jm - vs said this had to return a value???? so have made it return 0
	return 0;
}

int
PrepUtilTexto::sustituirCaracteres (string& texto, const map<char, string>& diccionario)
{
    if (diccionario.empty())
    {
        return 0;
    }
    int cuenta = 0;
    _posactual = 0;

    ostringstream textoFinal;

    Item item = _siguienteItem(texto);
    while (item.tipo != FIN)
    {
        if (item.tipo == CARACTER && diccionario.count(item.caracter))
        {
            textoFinal << (*diccionario.find(item.caracter)).second;
            cuenta++;
        }
        else if (item.tipo == CODIGO)
        {
            textoFinal << "{" << item.codigo << "}";
        }
        else if (item.tipo == ERROR)
        {
            textoFinal << "ERROR"; // Esto no deber�a ocurrir
        }
        else  // CARACTER
        {
            textoFinal << item.caracter;
            if (item.caracter == '{') textoFinal << "{"; // Literal de apertura de parentesis
        }

        item = _siguienteItem(texto);
    }
    texto = textoFinal.str();

    return cuenta;
}

PrepUtilTexto::Item
PrepUtilTexto::_siguienteItem(const string& texto)
{
    Item itemRet;

    if (_posactual >= texto.size())
    {
        itemRet.tipo = FIN;
        itemRet.codigo = 0;
    }
    else
    {
        switch (texto[_posactual])
        {
            case '{':
                if (_posactual + 1 < texto.size())
                {
                    _posactual++;
                    if (texto[_posactual] == '{')
                    {
                        itemRet.tipo = CARACTER;
                        itemRet.caracter = texto[_posactual];
                    } else _leerCodigo ( itemRet, texto);
                }
                else // El texto no puede terminar en un solo '{'
                {
                    itemRet.tipo = ERROR;
                    itemRet.codigo = 0;
                }
                break;
            default:
                itemRet.tipo = CARACTER;
                itemRet.caracter = texto[_posactual];
                break;
        };
    }

    _posactual++;
    return itemRet;
}

void
PrepUtilTexto::_leerCodigo (Item& item, const string& texto)
{
    // Empezamos en la posici�n tras el "{"
    size_t posCierre = texto.find("}", _posactual);
    if (posCierre == string::npos || posCierre == _posactual)
    {
        item.tipo = ERROR;
        item.codigo = 0;
    }
    else
    {
        string codigoStr = texto.substr(_posactual, posCierre - _posactual);
        if (codigoStr.length() > 3)
        {
            item.tipo = ERROR;
            item.codigo = 0;
        }
        else
        {
            // Comprobamos que todo sean cifras
            for (size_t i = 0; i < codigoStr.length(); i++)
            {
                if (codigoStr[i] < '0' || codigoStr[i] > '9')
                {
                    item.tipo = ERROR;
                    item.codigo = 0;
                    return;
                }
            }

            int codigo = atoi(codigoStr.c_str());
            if (codigo < 0 || codigo > 255)
            {
                item.tipo = ERROR;
                item.codigo = 0;
            }
            else
            {
                item.tipo = CODIGO;
                item.codigo = codigo;
                _posactual = posCierre;
            }
        }
    }
}
